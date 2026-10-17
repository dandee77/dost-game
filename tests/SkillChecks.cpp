#include "TestAccess.hpp"
#include "EquipmentAccess.hpp"
#include "Augment.hpp"
#include "SkillSystem.hpp"
#include "Balance.hpp"
#include "Theme.hpp"
#include "raymath.h"
#include <set>
#include <stdexcept>

namespace {
    int checks = 0;
    void require(bool value, const char* message) { ++checks; if (!value) throw std::runtime_error(message); }
    void clear(Game& game)
    {
        EnemyManager::GetInstance().reset();
        BulletManager::GetInstance().reset();
        ScrapManager::GetInstance().reset();
        DamageIndicatorManager::GetInstance().reset();
        game.skills.reset();
        game.playerEntity.init();
        game.playerEntity.position = {};
        game.playerEntity.rect = {-2.0f, -2.0f, 4.0f, 4.0f};
        game.gameState = GAME_RUNNING;
        game.harvestedScrap = 0;
        game.killCounter.reset();
        utils::gameCamera = {{1920.0f, 1080.0f}, {}, 0.0f, 20.0f};
    }
    Enemy& enemy(const std::string& id, Vector2 at, int hp = 100)
    {
        auto object = std::make_unique<LowLevelEnemy>(id, LOW_LEVEL_ENEMY, at, Vector2{});
        object->health = hp;
        object->speed = 0.0f;
        object->velocity = object->knockbackVelocity = {};
        auto& result = *object;
        EnemyManager::GetInstance().getEnemies()[id] = std::move(object);
        return result;
    }
    int health(const std::string& id)
    {
        const auto& map = EnemyManager::GetInstance().getEnemies();
        const auto found = map.find(id);
        return found == map.end() ? 0 : found->second->getHealth();
    }
    void cast(Game& game, AbilityId id, Vector2 target = {0.0f, -30.0f}, float dt = 0.01f)
    {
        require(game.skills.queueCast(id, target), "Skill accepts first activation");
        EquipmentTestAccess::skillStep(game, dt, target);
    }
    void step(Game& game, float seconds, float dt = 0.01f)
    {
        const int frames = static_cast<int>(std::round(seconds / dt));
        for (int i = 0; i < frames; ++i) EquipmentTestAccess::skillStep(game, dt, {0.0f, -30.0f});
    }
}

int runSkillChecks(const std::string& artifactDirectory)
{
    checks = 0;
    Game game;
    game.onSwitch();
    auto& player = game.playerEntity;
    auto& bullets = BulletManager::GetInstance().getBullets();
    std::set<std::string> keys;
    for (const auto& info : augmentCatalog()) {
        require(keys.insert(info.key).second && findAugment(info.key) == info.id, "Unique augment command resolves");
        clear(game);
        if (info.id == AUG_NANO_REPAIR) player.health = 50;
        require(applyAugment(player, info.id), "All fourteen augments apply to a live player");
        if (info.id != AUG_NANO_REPAIR) require(player.getAugmentLevel(info.id) == 1, "Augment level recorded");
    }
    for (const auto& info : abilityCatalog()) {
        require(keys.insert(info.key).second && findAbility(info.key) == info.id, "Unique ability command resolves");
        clear(game);
        cast(game, info.id);
        require(!game.skills.queueCast(info.id, {}), "Recharge prevents immediate duplicate activation");
        const float cooldown = game.skills.cooldown(info.id);
        for (GameState state : {GAME_PAUSED, GAME_AUGMENT_SELECTION, GAME_OVER}) {
            game.gameState = state;
            EquipmentTestAccess::skillStep(game, 1.0f, {});
            require(game.skills.cooldown(info.id) == cooldown, "All skill timers freeze outside gameplay");
        }
        game.gameState = GAME_RUNNING;
        game.skills.unequip(info.id, player);
        game.skills.equip(info.id);
        require(!game.skills.queueCast(info.id, {}), "Unequip does not bypass recharge");
    }
    require(keys.size() == 32, "Exactly 32 unique skill commands");
    clear(game);
    require(!applyAugment(player, AUG_COUNT) && !game.skills.equip(ABILITY_COUNT), "Reject invalid typed IDs");
    require(!game.skills.queueCast(ABILITY_BLINK_DRIVE, {std::numeric_limits<float>::infinity(), 0.0f}), "Reject nonfinite target");
    for (int i = 0; i < Balance::AUG_MAX_LEVEL; ++i) applyAugment(player, AUG_WEAPONS_PAYLOAD);
    require(!applyAugment(player, AUG_WEAPONS_PAYLOAD), "Augment cap enforced");
    require(player.scaleAttackDamage(40) == 100, "Payload scales fixed-damage weapons");
    clear(game);
    applyAugment(player, AUG_REINFORCED_HULL);
    require(player.getMaxHealth() == 120 && player.getHealth() == 120, "Hull increases max/current health");
    player.health = 40;
    applyAugment(player, AUG_NANO_REPAIR);
    require(player.getHealth() == 70, "Nano repairs 25 percent of upgraded maximum");
    for (int i = 0; i < 10; ++i) applyAugment(player, AUG_NANO_REPAIR);
    require(player.getHealth() == 120 && !applyAugment(player, AUG_NANO_REPAIR), "Repair clamps and reports full hull");
    clear(game);
    applyAugment(player, AUG_CRITICAL_MATRIX);
    bool critical = false, normal = false;
    for (int i = 0; i < 2000; ++i) { const int damage = player.scaleAttackDamage(20); critical |= damage == 40; normal |= damage == 20; }
    require(critical && normal, "Critical Matrix actually produces both normal and doubled attacks");
    clear(game);
    applyAugment(player, AUG_OVERCLOCKED_CHAMBERS);
    require(std::abs(EquipmentTestAccess::weaponCooldown(player) - 0.45f) < 0.001f, "Overclock shortens cooldown");
    applyAugment(player, AUG_THRUSTER_OVERDRIVE); applyAugment(player, AUG_GYRO_CONTROL); applyAugment(player, AUG_PHASE_SHIFT);
    require(player.speed > Balance::PLAYER_SPEED && player.rotationSpeedMultiplier > 1.0f && player.iframeDuration > Balance::PLAYER_IFRAME_TIME, "Mobility, turn, iframes increase");
    for (PlayerWeapon weapon : {WEAPON_DEFAULT, WEAPON_CANNON, WEAPON_ROCKETS, WEAPON_HEAVY, WEAPON_LASER}) {
        clear(game); player.setWeapon(weapon);
        applyAugment(player, AUG_SCATTER_SHOT); applyAugment(player, AUG_BROADSIDE_CANNONS);
        applyAugment(player, AUG_TAIL_GUNNER); applyAugment(player, AUG_ARMOR_PIERCING); applyAugment(player, AUG_INERTIA_IMPACT);
        EquipmentTestAccess::updateWeapon(player, 0.001f, true);
        require(bullets.size() >= 4, "Every weapon supports scatter/side/rear fire");
        bool left = false, right = false, rear = false;
        for (const auto& bullet : bullets) {
            require(bullet.getPiercePower() >= 2 && bullet.getKnockbackPower() > 0.0f, "Every projectile inherits pierce/knockback");
            left |= bullet.getDirection().x < -0.8f; right |= bullet.getDirection().x > 0.8f; rear |= bullet.getDirection().y > 0.8f;
        }
        require(left && right && rear, "Side/rear shots face distinct directions");
    }
    clear(game); player.setWeapon(WEAPON_CANNON); applyAugment(player, AUG_RAPID_FIRE);
    EquipmentTestAccess::updateWeapon(player, 0.11f, true);
    require(bullets.size() == 2, "Rapid Fire adds a shot within the burst");
    clear(game); player.setWeapon(WEAPON_LASER); applyAugment(player, AUG_RAPID_FIRE);
    EquipmentTestAccess::updateWeapon(player, 0.001f, true);
    require(player.consumeLaserTicks() == 2, "Rapid Fire adds a laser pulse");

    clear(game); enemy("near", {0, -10}); enemy("far", {0, -100});
    cast(game, ABILITY_RADIANT_HALO);
    require(health("near") == 40 && health("far") == 100, "Halo damages nearby hostiles only");
    clear(game); enemy("target", {0, -30}, 5000);
    cast(game, ABILITY_NUCLEAR_MISSILE);
    require(health("target") == 5000, "Nuclear missile has travel time");
    step(game, 0.75f);
    require(health("target") == 0 && game.killCounter.getCount() == 1, "Nuclear missile obliterates standard targets once");
    require(ScrapManager::GetInstance().pendingValue() == Balance::SKILL_LOW_SCRAP, "Normal skill kill awards scrap");
    clear(game); enemy("target", {0, -30}, 5000);
    cast(game, ABILITY_SPACE_COLLAPSE);
    require(health("target") == 0 && ScrapManager::GetInstance().pendingValue() == 0, "Collapse erases with zero scrap");
    require(player.getScore() == Balance::LOW_SCORE && game.killCounter.getCount() == 1, "Collapse still awards score/kill");
    clear(game); auto& pulseEnemy = enemy("pushed", {0, -10});
    cast(game, ABILITY_REPULSOR_PULSE);
    require(pulseEnemy.getPosition().y < -30.0f && pulseEnemy.getHealth() == 100, "Repulsor creates space without damage");
    clear(game); enemy("ring", {25, 0}); enemy("center", {0, 0});
    cast(game, ABILITY_LIGHTNING_RING);
    require(health("ring") == 92 && health("center") == 100, "Lightning damages perimeter, not center");
    auto& shocked = *EnemyManager::GetInstance().getEnemies().at("ring");
    shocked.speed = 50.0f; const auto frozen = shocked.getPosition(); shocked.updateWithStatus(0.1f);
    require(shocked.isStunned() && Vector2Distance(frozen, shocked.getPosition()) == 0.0f, "Stun stops movement");
    shocked.updateWithStatus(1.0f); require(!shocked.isStunned(), "Stun expires");
    clear(game);
    cast(game, ABILITY_DEFLECTOR_SHIELD);
    for (int i = 0; i < Balance::SKILL_SHIELD_HITS; ++i) player.takeDamage(0.0f, {0, -1}, 1.0f);
    require(player.getHealth() == 100 && player.getDeflectorHits() == 0, "Deflector absorbs exactly three hits");
    player.takeDamage(0.0f, {0, -1}, 1.0f); require(player.getHealth() == 90, "Fourth hit damages hull");
    clear(game); cast(game, ABILITY_BLINK_DRIVE, {0, -1000});
    require(std::abs(player.getPosition().y + 35.0f) < 0.001f && player.getPlayerState() == PLAYER_IFRAME, "Blink caps range and grants short protection");
    clear(game); enemy("front", {0, -20}); enemy("behind", {0, 20});
    cast(game, ABILITY_PLASMA_BEAM); step(game, 0.3f);
    require(health("front") < 88 && health("behind") == 100, "Sustained plasma cone damages forward only");
    clear(game);
    for (int i = 0; i < 8; ++i) enemy("chain" + std::to_string(i), {static_cast<float>(i * 5), -10});
    cast(game, ABILITY_CHAIN_LIGHTNING);
    int damaged = 0;
    for (const auto& [id, object] : EnemyManager::GetInstance().getEnemies()) if (object->getHealth() == 65) ++damaged;
    require(damaged == 6, "Chain visits six distinct targets");
    clear(game); enemy("acid", {0, 8});
    cast(game, ABILITY_CORROSIVE_TRAIL);
    auto& corroded = *EnemyManager::GetInstance().getEnemies().at("acid");
    require(health("acid") == 94 && corroded.isCorroded(), "Acid deals damage and applies corrosion");
    require(corroded.getContactDamage() == 5, "Corrosion reduces combat damage");
    corroded.speed = 50.0f; const Vector2 acidPosition = corroded.getPosition(); corroded.updateWithStatus(0.1f);
    require(Vector2Distance(acidPosition, corroded.getPosition()) <= 2.501f, "Corrosion limits movement speed");
    corroded.updateWithStatus(2.0f); require(!corroded.isCorroded() && corroded.getContactDamage() == 10, "Corrosion restores stats after expiry");
    clear(game); enemy("pulled", {30, -30});
    cast(game, ABILITY_SINGULARITY, {0, -30});
    require(EnemyManager::GetInstance().getEnemies().at("pulled")->getPosition().x < 30.0f && health("pulled") == 90, "Singularity pulls and crushes");
    step(game, 2.0f);
    require(health("pulled") == 0 && ScrapManager::GetInstance().pendingValue() == 2, "Singularity kills with ordinary drops");
    clear(game);
    Bullet hostile({-60, 0}, {1, 0}, true); hostile.position = {60, 0};
    Bullet friendly({-60, 0}, {1, 0}, false); friendly.position = {60, 0};
    BulletManager::GetInstance().addBullet(hostile); BulletManager::GetInstance().addBullet(friendly);
    cast(game, ABILITY_INTERCEPTOR);
    require(bullets.size() == 1 && !bullets.front().isEnemyBullet(), "Interceptor catches swept hostile projectiles only");
    clear(game); enemy("rift", {0, -30});
    hostile.previousPosition = {-40, -30}; hostile.position = {40, -30}; BulletManager::GetInstance().addBullet(hostile);
    cast(game, ABILITY_REALM_BREAKER, {0, -30});
    require(bullets.empty() && health("rift") == 80, "Rift swallows crossing bullets and damages enemies");
    clear(game); ScrapManager::GetInstance().spawnScrap({1000, 1000}, 17);
    cast(game, ABILITY_SCRAP_MAGNET);
    require(game.harvestedScrap == 17 && ScrapManager::GetInstance().count() == 0, "Magnet collects battlefield-wide once");
    step(game, 0.5f); require(game.harvestedScrap == 17, "Magnet cannot duplicate scrap");
    clear(game); cast(game, ABILITY_HOLOGRAM_CLONE);
    require(game.skills.decoy() && !bullets.empty(), "Clone exists and mimics primary fire");
    enemy("lured", {0, -20});
    EnemyManager::GetInstance().update(player.getPosition(), game.gameTimer, game.skills.decoy(), 60.0f);
    require(Vector2Distance(EnemyManager::GetInstance().getEnemies().at("lured")->playerPosition, *game.skills.decoy()) == 0.0f, "Nearby enemy targets clone");
    step(game, 10.0f); require(!game.skills.decoy(), "Clone expires without dangling target");
    clear(game); player.setWeapon(WEAPON_HEAVY); applyAugment(player, AUG_RAPID_FIRE);
    cast(game, ABILITY_HOLOGRAM_CLONE);
    require(bullets.size() == 2 && bullets.front().getKind() == PROJECTILE_HEAVY, "Clone inherits weapon and burst upgrades");
    clear(game); player.setWeapon(WEAPON_LASER); enemy("clone-beam", {18, -20});
    cast(game, ABILITY_HOLOGRAM_CLONE);
    require(health("clone-beam") == 96, "Laser clone uses a damaging beam along primary facing");
    clear(game); enemy("drone-target", {0, -25}); cast(game, ABILITY_COMBAT_DRONE);
    require(!bullets.empty() && game.skills.states[ABILITY_COMBAT_DRONE].position.y < 0.0f, "Drone independently pursues and fires");
    clear(game); enemy("blade", {18, 0}); cast(game, ABILITY_LASER_RINGS);
    require(health("blade") == 88, "Orbiting laser blade deals contact damage");
    clear(game);
    for (int x = -80; x <= 80; x += 20) for (int y = -40; y <= 40; y += 20)
        enemy("barrage" + std::to_string(x) + "/" + std::to_string(y), {static_cast<float>(x), static_cast<float>(y)}, 10000);
    cast(game, ABILITY_ARMAGEDDON); step(game, 1.0f);
    int barrageHits = 0;
    for (const auto& [id, object] : EnemyManager::GetInstance().getEnemies()) if (object->getHealth() < 10000) ++barrageHits;
    require(barrageHits > 3, "Armageddon barrages multiple screen regions over time");
    // Continuous damage count should be independent of 30 vs 144 FPS.
    int referenceHealth = 0;
    for (int fps : {30, 144}) {
        clear(game); enemy("rate", {0, -20}, 10000); game.skills.queueCast(ABILITY_PLASMA_BEAM, {0, -20});
        step(game, 3.0f, 1.0f / fps);
        if (fps == 30) referenceHealth = health("rate");
        else require(health("rate") == referenceHealth, "Plasma tick damage is frame-rate independent");
    }
    clear(game);
    const auto invalid = game.skills.command("skill cast blink-drive trailing", &player);
    require(!game.skills.states[ABILITY_BLINK_DRIVE].queued && !invalid.empty(), "Malformed command never mutates state");
    game.skills.command("augment weapons-payload trailing", &player);
    require(player.getAugmentLevel(AUG_WEAPONS_PAYLOAD) == 0, "Extra augment arguments rejected");
    player.health = 0;
    game.skills.command("skill equip combat-drone", &player);
    require(!game.skills.states[ABILITY_COMBAT_DRONE].equipped, "Dead player cannot equip skills");
    clear(game);
#ifdef GAME_DEBUG
    game.executeDebugCommand("augment weapons-payload");
    game.executeDebugCommand("skill equip combat-drone");
    require(player.getAugmentLevel(AUG_WEAPONS_PAYLOAD) == 1 && game.skills.states[ABILITY_COMBAT_DRONE].equipped, "Real F5/startup command routing");
    game.debugTools.input = "skill equip ";
    require(game.debugTools.completions().size() == 18, "Autocomplete exposes all eighteen abilities");
#endif
    EquipmentTestAccess::restart(game);
    require(player.getMaxHealth() == 100 && player.getAugmentLevel(AUG_WEAPONS_PAYLOAD) == 0 &&
        !game.skills.states[ABILITY_COMBAT_DRONE].equipped && game.skills.flashes.empty() && game.skills.trails.empty(), "Real restart clears augments, abilities and effects");
    clear(game); cast(game, ABILITY_DEFLECTOR_SHIELD); game.onExit();
    require(player.getDeflectorHits() == 0 && !game.skills.isActive(ABILITY_DEFLECTOR_SHIELD), "Scene exit clears ability protection and effects");
    clear(game); cast(game, ABILITY_DEFLECTOR_SHIELD); player.health = 0; game.gameState = GAME_OVER; game.update();
    require(player.getDeflectorHits() == 0 && !game.skills.isActive(ABILITY_DEFLECTOR_SHIELD), "Death clears ability protection and effects");

    // Native placeholder gallery: one cell per skill, captured using production draw.
    RenderTexture2D preview = LoadRenderTexture(1800, 1200);
    BeginTextureMode(preview); ClearBackground(Theme::COLOR_PANEL);
    int index = 0;
    for (const auto& info : abilityCatalog()) {
        clear(game);
        enemy("preview", {20.0f, -20.0f});
        cast(game, info.id, {0.0f, -20.0f}, 0.05f);
        const float x = static_cast<float>((index % 6) * 300), y = static_cast<float>((index / 6) * 400);
        Camera2D camera = {{x + 150, y + 210}, {}, 0.0f, 2.0f};
        BeginMode2D(camera); game.skills.draw(); player.draw(); EndMode2D();
        DrawText(info.name, static_cast<int>(x + 10), static_cast<int>(y + 20), 15, WHITE);
        ++index;
    }
    EndTextureMode();
    Image capture = LoadImageFromTexture(preview.texture); ImageFlipVertical(&capture);
    require(ExportImage(capture, (artifactDirectory + "/skills-preview.png").c_str()), "Export native skills gallery");
    UnloadImage(capture); UnloadRenderTexture(preview);
    clear(game);
    TraceLog(LOG_WARNING, "PASS: %d skill checks", checks);
    return checks;
}
