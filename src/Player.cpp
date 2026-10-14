#include "Player.hpp"
#include "Animator.hpp"
#include "Balance.hpp"
#include "Config.hpp"
#include "ResourceManager.hpp"
#include "DamageOverlay.hpp"
#include "Theme.hpp"
#include "Utils.hpp"
#include "raymath.h"
#include <algorithm>
#include <cmath>

namespace {
    constexpr const char* weaponKeys[] = {"player_weapon_auto_cannon", "player_weapon_zapper",
        "player_weapon_rockets", "player_weapon_big_space_gun"};
    constexpr const char* engineKeys[] = {"player_engine_base_engine", "player_engine_big_pulse_engine",
        "player_engine_burst_engine", "player_engine_supercharged_engine"};
    constexpr const char* shieldKeys[] = {"", "player_shield_front_shield", "player_shield_front_and_side_shield",
        "player_shield_round_shield", "player_shield_invincibility_shield"};
    constexpr const char* weaponNames[] = {"CANNON", "LASER", "ROCKETS", "HEAVY", "DEFAULT"};
    constexpr const char* engineNames[] = {"BASE", "PULSE", "BURST", "SUPERCHARGED"};
    constexpr const char* shieldNames[] = {"NONE", "FRONT", "SIDES", "ROUND", "INVINCIBILITY"};

    void drawLayer(const std::string& key, int frameSize, float size, Vector2 position,
                   float rotation, float time, Color tint, float frameTime = Theme::EQUIPMENT_FRAME_TIME)
    {
        const auto& sheet = ResourceManager::GetInstance().GetTextureRef(key);
        if (sheet.id == 0 || sheet.width < frameSize) return;
        const int frames = sheet.width / frameSize;
        const int frame = static_cast<int>(time / frameTime) % frames;
        DrawTexturePro(sheet, {static_cast<float>(frame * frameSize), 0.0f,
            static_cast<float>(frameSize), static_cast<float>(frameSize)},
            {position.x, position.y, size, size}, {size / 2.0f, size / 2.0f}, rotation, tint);
    }
}

Player::Player() = default;

void Player::init()
{
#ifdef GAME_DEBUG
    debugInvincible = false;
#endif
    Animator::GetInstance().Remove("accelerating");
    Animator::GetInstance().Remove("deaccelerating");
    playerScore = totalDamageDealt = 0;
    position = Balance::PLAYER_SPAWN;
    rect = {position.x - Balance::PLAYER_RADIUS / 2.0f, position.y - Balance::PLAYER_RADIUS / 2.0f,
        Balance::PLAYER_RADIUS, Balance::PLAYER_RADIUS};
    origin = {rect.width / 2.0f, rect.height / 2.0f};
    speed = Balance::PLAYER_SPEED;
    health = Balance::PLAYER_MAX_HEALTH;
    damage = Balance::PLAYER_CONTACT_DAMAGE;
    rotation = 0.0f;
    velocity = {};
    playerAccelerating = autoShoot = false;
    playerState = PLAYER_DEFAULT;
    stateElapsed = timeStateEntered = animationTime = 0.0f;
    attackSpeed = Balance::PLAYER_ATTACK_COOLDOWN;
    iframeDuration = Balance::PLAYER_IFRAME_TIME;
    rotationSpeedMultiplier = 1.0f;
    burstCount = scatterCount = bulletPiercePower = 1;
    knockbackPower = 0.0f;
    minDamage = Balance::PLAYER_DAMAGE_MIN;
    maxDamage = Balance::PLAYER_DAMAGE_MAX;
    blasts.clear();
    setBuild(BUILD_DEFAULT);
    shotCooldown = attackSpeed;
}

void Player::setBuild(PlayerBuild build)
{
    switch (build) {
    case BUILD_DEFAULT: setEngine(ENGINE_BASE); setShield(SHIELD_NONE); setWeapon(WEAPON_DEFAULT); break;
    case BUILD_STARTER: setWeapon(WEAPON_CANNON); setEngine(ENGINE_BASE); setShield(SHIELD_NONE); break;
    case BUILD_CANNON: setWeapon(WEAPON_CANNON); setEngine(ENGINE_PULSE); setShield(SHIELD_FRONT); break;
    case BUILD_LASER: setWeapon(WEAPON_LASER); setEngine(ENGINE_SUPERCHARGED); setShield(SHIELD_SIDES); break;
    case BUILD_ROCKETS: setWeapon(WEAPON_ROCKETS); setEngine(ENGINE_BURST); setShield(SHIELD_ROUND); break;
    case BUILD_HEAVY: setWeapon(WEAPON_HEAVY); setEngine(ENGINE_PULSE); setShield(SHIELD_INVINCIBILITY); break;
    }
    autoShoot = false;
}

void Player::setWeapon(PlayerWeapon value)
{
    weapon = value;
    laserActive = isBurstActive = false;
    pendingLaserTicks = currentBurstShot = 0;
    laserClock = shotCooldown = weaponAnimationTime = weaponFlash = 0.0f;
}

void Player::setEngine(PlayerEngine value)
{
    if (weapon == WEAPON_DEFAULT) setWeapon(WEAPON_CANNON);
    engine = value;
    boostTime = boostCooldown = 0.0f;
}
void Player::setShield(PlayerShield value)
{
    if (weapon == WEAPON_DEFAULT) setWeapon(WEAPON_CANNON);
    shield = value;
    shieldCharge = static_cast<float>(Balance::SHIELD_CAPACITY[shield]);
    shieldDelay = invincibilityTime = invincibilityCooldown = 0.0f;
}

void Player::increasePlayerAttackSpeed() { attackSpeed *= Balance::AUG_ATTACK_MULT; }
void Player::increasePlayerHealth() { health = std::min(Balance::PLAYER_MAX_HEALTH, health + Balance::AUG_HEAL); }
void Player::increasePlayerMovementSpeed() { speed *= Balance::AUG_SPEED_MULT; }
void Player::increasePlayerIframeDuration() { iframeDuration *= Balance::AUG_IFRAME_MULT; }
void Player::increasePlayerRotationSpeed() { rotationSpeedMultiplier *= Balance::AUG_TURN_MULT; }
void Player::increaseTriggerHappyBurst() { ++burstCount; }
void Player::increaseScatterShot() { ++scatterCount; }
void Player::increasePiercingRounds() { ++bulletPiercePower; }
void Player::increaseInertiaImpact() { knockbackPower += Balance::AUG_KNOCKBACK; }
int Player::getRandomDamage() const { return GetRandomValue(minDamage, maxDamage); }
Vector2 Player::facing() const { return Vector2Rotate({0.0f, -1.0f}, rotation * DEG2RAD); }
Vector2 Player::getLaserStart() const { return Vector2Add(position, Vector2Scale(facing(), Balance::MUZZLE_OFFSET)); }
Vector2 Player::getLaserEnd() const { return Vector2Add(getLaserStart(), Vector2Scale(facing(), Balance::LASER_RANGE)); }
int Player::consumeLaserTicks() { const int ticks = pendingLaserTicks; pendingLaserTicks = 0; return ticks; }

float Player::weaponCooldown() const
{
    const float multiplier = attackSpeed / Balance::PLAYER_ATTACK_COOLDOWN;
    switch (weapon) {
    case WEAPON_HEAVY: return Balance::HEAVY_COOLDOWN * multiplier;
    case WEAPON_ROCKETS: return Balance::ROCKET_COOLDOWN * multiplier;
    case WEAPON_LASER: return Balance::LASER_TICK * multiplier;
    default: return attackSpeed;
    }
}

void Player::fireScatterBullets(Vector2 direction)
{
    for (int index = 0; index < scatterCount; ++index) {
        const float offset = (static_cast<float>(index) - static_cast<float>(scatterCount - 1) / 2.0f) * Balance::SCATTER_ANGLE;
        const Vector2 shotDirection = Vector2Rotate(direction, offset * DEG2RAD);
        int pierce = bulletPiercePower;
        if (weapon == WEAPON_HEAVY) pierce += Balance::HEAVY_PIERCE - 1;
        if (weapon == WEAPON_ROCKETS) pierce = 1;
        Bullet bullet(weapon == WEAPON_DEFAULT ? position : getLaserStart(), shotDirection, false, pierce, knockbackPower);
        switch (weapon) {
        case WEAPON_DEFAULT: break; // Original sprite and legacy collision/damage path.
        case WEAPON_HEAVY:
            bullet.configure(PROJECTILE_HEAVY, Balance::HEAVY_DAMAGE, Balance::HEAVY_RADIUS, Balance::HEAVY_SPEED); break;
        case WEAPON_ROCKETS:
            bullet.configure(PROJECTILE_ROCKET, Balance::ROCKET_DAMAGE, Balance::ROCKET_RADIUS, Balance::ROCKET_SPEED); break;
        default:
            bullet.configure(PROJECTILE_CANNON, getRandomDamage(), Balance::CANNON_RADIUS, Balance::CANNON_SPEED); break;
        }
        BulletManager::GetInstance().addBullet(bullet);
    }
    weaponAnimationTime = 0.0f;
    if (weapon != WEAPON_DEFAULT) {
        const auto& sheet = ResourceManager::GetInstance().GetTextureRef(weaponKeys[weapon]);
        weaponFlash = static_cast<float>(sheet.width / Theme::PLAYER_LAYER_FRAME) * Theme::EQUIPMENT_FRAME_TIME;
    }
    PlaySound(ResourceManager::GetInstance().GetSound("player_shoot"));
}

void Player::updateWeapon(float dt, bool firing)
{
    pendingLaserTicks = 0;
    laserActive = weapon == WEAPON_LASER && firing;
    if (weapon == WEAPON_LASER) {
        laserClock -= dt;
        if (laserActive) {
            while (laserClock <= Config::TIMER_EPSILON) { ++pendingLaserTicks; laserClock += weaponCooldown(); }
        } else laserClock = std::max(0.0f, laserClock);
        return;
    }
    shotCooldown -= dt;
    if (!firing && !isBurstActive) { shotCooldown = std::max(0.0f, shotCooldown); return; }
    while (shotCooldown <= Config::TIMER_EPSILON && (firing || isBurstActive)) {
        fireScatterBullets(facing());
        ++currentBurstShot;
        isBurstActive = currentBurstShot < burstCount;
        if (isBurstActive) shotCooldown += Balance::BURST_DELAY;
        else { currentBurstShot = 0; shotCooldown += weaponCooldown(); }
    }
}

void Player::updateEquipment(float dt, bool skillPressed)
{
    animationTime += dt;
    weaponAnimationTime += dt;
    weaponFlash = std::max(0.0f, weaponFlash - dt);
    boostTime = std::max(0.0f, boostTime - dt);
    boostCooldown = std::max(0.0f, boostCooldown - dt);
    invincibilityTime = std::max(0.0f, invincibilityTime - dt);
    invincibilityCooldown = std::max(0.0f, invincibilityCooldown - dt);
    if (skillPressed && engine == ENGINE_BURST && boostCooldown == 0.0f) {
        boostTime = Balance::BOOST_DURATION; boostCooldown = Balance::BOOST_COOLDOWN;
    }
    if (skillPressed && shield == SHIELD_INVINCIBILITY && invincibilityCooldown == 0.0f) {
        invincibilityTime = Balance::INVINCIBILITY_DURATION; invincibilityCooldown = Balance::INVINCIBILITY_COOLDOWN;
    }
    const float rechargeTime = std::max(0.0f, dt - shieldDelay);
    shieldDelay = std::max(0.0f, shieldDelay - dt);
    shieldCharge = std::min(static_cast<float>(Balance::SHIELD_CAPACITY[shield]),
        shieldCharge + rechargeTime * Balance::SHIELD_RECHARGE_RATE);
    for (auto& blast : blasts) blast.remaining -= dt;
    std::erase_if(blasts, [](const Blast& blast) { return blast.remaining <= 0.0f; });
}

bool Player::shieldCovers(Vector2 source) const
{
    if (shield == SHIELD_NONE) return false;
    if (shield == SHIELD_INVINCIBILITY) return invincibilityTime > 0.0f;
    if (shieldCharge < Balance::PLAYER_CONTACT_DAMAGE) return false;
    if (shield == SHIELD_ROUND) return true;
    const Vector2 direction = Vector2Normalize(Vector2Subtract(source, position));
    const float dot = Vector2DotProduct(facing(), direction);
    return dot >= (shield == SHIELD_FRONT ? Balance::SHIELD_FRONT_DOT : Balance::SHIELD_SIDE_DOT);
}

bool Player::tryBlockHit(Vector2 source)
{
    if (!shieldCovers(source)) return false;
    if (shield != SHIELD_INVINCIBILITY) {
        shieldCharge -= Balance::PLAYER_CONTACT_DAMAGE;
        shieldDelay = Balance::SHIELD_RECHARGE_DELAY;
    }
    return true;
}

void Player::update()
{
    const float dt = GetFrameTime();
    if (health <= 0) { playerState = PLAYER_DEAD; laserActive = false; pendingLaserTicks = 0; return; }
    stateElapsed += dt;
    if (playerState == PLAYER_STUNNED && stateElapsed >= Balance::PLAYER_STUN_TIME) {
        playerState = PLAYER_IFRAME; stateElapsed -= Balance::PLAYER_STUN_TIME;
    }
    if (playerState == PLAYER_IFRAME && stateElapsed >= iframeDuration) playerState = PLAYER_DEFAULT;
    updateEquipment(dt, IsKeyPressed(KEY_SPACE));
    const Vector2 direction = Vector2Subtract(GetScreenToWorld2D(GetMousePosition(), utils::gameCamera), position);
    if (Vector2Length(direction) > 0.0f) {
        const float target = std::atan2(direction.y, direction.x) * RAD2DEG + 90.0f;
        const float delta = std::remainder(target - rotation, 360.0f);
        const float turnSpeed = (Balance::PLAYER_TURN_BASE + Vector2Length(velocity) / speed *
            Balance::PLAYER_TURN_SPEED_BONUS) * rotationSpeedMultiplier;
        rotation = std::fmod(rotation + delta * (1.0f - std::exp(-turnSpeed * dt)) + 360.0f, 360.0f);
    }
    Vector2 input = {static_cast<float>(IsKeyDown(KEY_D) - IsKeyDown(KEY_A)),
                     static_cast<float>(IsKeyDown(KEY_S) - IsKeyDown(KEY_W))};
    input = Vector2Normalize(input);
    const float moveSpeed = speed * Balance::ENGINE_SPEED[engine] * (boostTime > 0.0f ? Balance::BOOST_SPEED : 1.0f);
    velocity = Vector2MoveTowards(velocity, Vector2Scale(input, moveSpeed),
        Balance::PLAYER_ACCELERATION * Balance::ENGINE_ACCELERATION[engine] * dt);
    position = Vector2Add(position, Vector2Scale(velocity, dt));
    playerAccelerating = Vector2Length(velocity) > 0.0f;
    rect.x = position.x - rect.width / 2.0f;
    rect.y = position.y - rect.height / 2.0f;
    if (IsKeyPressed(KEY_E)) autoShoot = !autoShoot;
    updateWeapon(dt, IsMouseButtonDown(MOUSE_BUTTON_LEFT) || autoShoot);
}

void Player::takeDamage(float entered, Vector2 source, float entitySize)
{
#ifdef GAME_DEBUG
    if (debugInvincible) return;
#endif
    if (tryBlockHit(source)) return;
    health = std::max(0, health - Balance::PLAYER_CONTACT_DAMAGE);
    playerState = health == 0 ? PLAYER_DEAD : PLAYER_STUNNED;
    timeStateEntered = entered;
    stateElapsed = 0.0f;
    velocity = Vector2Scale(Vector2Normalize(Vector2Subtract(position, source)), Balance::PLAYER_COLLISION_NUDGE * entitySize);
    if (health == 0) { laserActive = false; pendingLaserTicks = 0; }
    PlaySound(ResourceManager::GetInstance().GetSound("player_damaged"));
    PlaySound(ResourceManager::GetInstance().GetSound("player_damaged_2"));
    DamageOverlay::GetInstance().startDamageAnimation();
}

void Player::addBlast(Vector2 center) { blasts.push_back({center, Theme::EXPLOSION_TIME}); }

void Player::draw()
{
    for (const auto& blast : blasts) {
        DrawRing(blast.center, Balance::ROCKET_SPLASH_RADIUS - Theme::DEBUG_OUTLINE_WIDTH,
            Balance::ROCKET_SPLASH_RADIUS, 0.0f, 360.0f, Theme::EQUIPMENT_RING_SEGMENTS,
            Fade(Theme::COLOR_ACCENT, blast.remaining / Theme::EXPLOSION_TIME));
    }
    if (health <= 0) return;
    if (laserActive) {
        const auto& sheet = ResourceManager::GetInstance().GetTextureRef("player_projectile_zapper");
        if (sheet.id != 0) {
            const int frame = static_cast<int>(animationTime / Theme::EQUIPMENT_FRAME_TIME) % (sheet.width / Theme::PROJECTILE_FRAME);
            for (float distance = 0.0f; distance < Balance::LASER_RANGE; distance += Theme::LASER_TILE_LENGTH) {
                const float length = std::min(Theme::LASER_TILE_LENGTH, Balance::LASER_RANGE - distance);
                const Vector2 center = Vector2Add(getLaserStart(), Vector2Scale(facing(), distance + length / 2.0f));
                DrawTexturePro(sheet, {static_cast<float>(frame * Theme::PROJECTILE_FRAME) + Theme::LASER_SOURCE_X, 0.0f,
                    Theme::LASER_SOURCE_WIDTH, static_cast<float>(Theme::PROJECTILE_FRAME)},
                    {center.x, center.y, Balance::LASER_RADIUS * 2.0f, length},
                    {Balance::LASER_RADIUS, length / 2.0f}, rotation, WHITE);
            }
        }
    }
    const bool hurt = playerState != PLAYER_DEFAULT && static_cast<int>(stateElapsed * Theme::HURT_FLASH_RATE) % 2 == 0;
    const Color tint = hurt ? Theme::COLOR_DANGER : WHITE;
    if (weapon == WEAPON_DEFAULT) {
        drawLayer(playerAccelerating ? "player_acceleration" : "player_deacceleration",
            Theme::ORIGINAL_PLAYER_FRAME, Theme::ORIGINAL_PLAYER_SIZE, position, rotation,
            animationTime, tint, Theme::ORIGINAL_PLAYER_FRAME_TIME);
        return;
    }
    drawLayer(std::string(engineKeys[engine]) + (playerAccelerating ? "_powering" : "_idle"),
        Theme::PLAYER_LAYER_FRAME, Theme::PLAYER_LAYER_SIZE, position, rotation, animationTime, WHITE);
    drawLayer(engineKeys[engine], Theme::PLAYER_LAYER_FRAME, Theme::PLAYER_LAYER_SIZE, position, rotation, 0.0f, tint);
    const float fraction = static_cast<float>(health) / Balance::PLAYER_MAX_HEALTH;
    const char* hull = fraction <= Balance::HULL_CRITICAL_FRACTION ? "player_hull_very_damaged" :
        fraction <= Balance::HULL_DAMAGED_FRACTION ? "player_hull_damaged" :
        fraction <= Balance::HULL_SLIGHT_FRACTION ? "player_hull_slight_damage" : "player_hull_full_health";
    drawLayer(hull, Theme::PLAYER_LAYER_FRAME, Theme::PLAYER_LAYER_SIZE, position, rotation, 0.0f, tint);
    drawLayer(weaponKeys[weapon], Theme::PLAYER_LAYER_FRAME, Theme::PLAYER_LAYER_SIZE, position, rotation,
        laserActive ? animationTime : weaponFlash > 0.0f ? weaponAnimationTime : 0.0f, tint);
    if (shield != SHIELD_NONE) {
        const float capacity = static_cast<float>(Balance::SHIELD_CAPACITY[shield]);
        const float alpha = shield == SHIELD_INVINCIBILITY ? (invincibilityTime > 0.0f ? 1.0f : Theme::SHIELD_EMPTY_OPACITY) :
            shieldCharge < Balance::PLAYER_CONTACT_DAMAGE ? Theme::SHIELD_EMPTY_OPACITY :
            Theme::SHIELD_MIN_OPACITY + (1.0f - Theme::SHIELD_MIN_OPACITY) * shieldCharge / capacity;
        drawLayer(shieldKeys[shield], Theme::PLAYER_SHIELD_FRAME, Theme::PLAYER_SHIELD_SIZE,
            position, rotation, animationTime, Fade(WHITE, alpha));
    }
}

void Player::drawEquipmentStatus() const
{
    const Font font = ResourceManager::GetInstance().GetFont(Theme::FONT_PRIMARY);
    Vector2 at = Theme::EQUIPMENT_STATUS_POSITION;
    DrawTextEx(font, TextFormat("%s / %s", weaponNames[weapon], engineNames[engine]), at,
        Theme::TEXT_CAPTION, Theme::TEXT_SPACING, Theme::COLOR_ACCENT);
    at.y += Theme::EQUIPMENT_STATUS_LINE;
    const char* shieldStatus = shield == SHIELD_INVINCIBILITY ?
        TextFormat("GUARD %s %.1fs", invincibilityTime > 0.0f ? "ACTIVE" : invincibilityCooldown > 0.0f ? "RECHARGE" : "READY",
            invincibilityTime > 0.0f ? invincibilityTime : invincibilityCooldown) :
        TextFormat("SHIELD %s %.0f/%d", shieldNames[shield], shieldCharge, Balance::SHIELD_CAPACITY[shield]);
    DrawTextEx(font, shieldStatus, at,
        Theme::TEXT_CAPTION, Theme::TEXT_SPACING, Theme::COLOR_TEXT);
    at.y += Theme::EQUIPMENT_STATUS_LINE;
    if (engine == ENGINE_BURST)
        DrawTextEx(font, TextFormat("SPACE: BOOST %s %.1fs", boostTime > 0.0f ? "ACTIVE" : boostCooldown > 0.0f ? "RECHARGE" : "READY",
            boostTime > 0.0f ? boostTime : boostCooldown), at, Theme::TEXT_CAPTION, Theme::TEXT_SPACING, Theme::COLOR_TEXT);
    if (shield == SHIELD_INVINCIBILITY) {
        if (engine == ENGINE_BURST) at.y += Theme::EQUIPMENT_STATUS_LINE;
        DrawTextEx(font, "SPACE: ACTIVATE GUARD", at, Theme::TEXT_CAPTION, Theme::TEXT_SPACING, Theme::COLOR_TEXT);
    }
}

void Player::drawAttackHitboxes() const
{
    if (laserActive) {
        const Vector2 side = Vector2Scale(Vector2Rotate(facing(), PI / 2.0f), Balance::LASER_RADIUS);
        DrawLineV(Vector2Add(getLaserStart(), side), Vector2Add(getLaserEnd(), side), Theme::COLOR_ACCENT);
        DrawLineV(Vector2Subtract(getLaserStart(), side), Vector2Subtract(getLaserEnd(), side), Theme::COLOR_ACCENT);
        DrawCircleLinesV(getLaserStart(), Balance::LASER_RADIUS, Theme::COLOR_ACCENT);
        DrawCircleLinesV(getLaserEnd(), Balance::LASER_RADIUS, Theme::COLOR_ACCENT);
    }
    if (shield != SHIELD_NONE) {
        const float halfAngle = shield == SHIELD_FRONT ? Balance::SHIELD_FRONT_HALF_ANGLE :
            shield == SHIELD_SIDES ? Balance::SHIELD_SIDE_HALF_ANGLE : 180.0f;
        DrawRing(position, Balance::SHIELD_RADIUS, Balance::SHIELD_RADIUS + Theme::DEBUG_OUTLINE_WIDTH,
            rotation - 90.0f - halfAngle, rotation - 90.0f + halfAngle, Theme::EQUIPMENT_RING_SEGMENTS, Theme::COLOR_ACCENT);
    }
}
