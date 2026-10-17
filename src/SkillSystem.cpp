#include "SkillSystem.hpp"
#include "Augment.hpp"
#include "Balance.hpp"
#include "BulletManager.hpp"
#include "Config.hpp"
#include "EnemyManager.hpp"
#include "Player.hpp"
#include "ResourceManager.hpp"
#include "ScrapManager.hpp"
#include "Theme.hpp"
#include "Utils.hpp"
#include "raymath.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include <sstream>

const std::array<AbilityInfo, ABILITY_COUNT>& abilityCatalog()
{
    static constexpr std::array<AbilityInfo, ABILITY_COUNT> catalog = {{
        {ABILITY_LASER_RINGS, "laser-rings", "Laser Rings", true},
        {ABILITY_DEFLECTOR_SHIELD, "deflector-shield", "Deflector Shield", false},
        {ABILITY_LIGHTNING_RING, "lightning-ring", "Lightning Ring", true},
        {ABILITY_BLINK_DRIVE, "blink-drive", "Blink Drive", false},
        {ABILITY_NUCLEAR_MISSILE, "nuclear-missile", "Nuclear Missile", false},
        {ABILITY_SPACE_COLLAPSE, "space-collapse", "Space Collapse", false},
        {ABILITY_RADIANT_HALO, "radiant-halo", "Radiant Halo", false},
        {ABILITY_REPULSOR_PULSE, "repulsor-pulse", "Repulsor Pulse", true},
        {ABILITY_INTERCEPTOR, "point-defense-interceptor", "Point-Defense Interceptor", true},
        {ABILITY_SCRAP_MAGNET, "scrap-magnet", "Scrap Magnet", true},
        {ABILITY_CHAIN_LIGHTNING, "chain-lightning", "Chain Lightning", false},
        {ABILITY_HOLOGRAM_CLONE, "hologram-clone", "Hologram Clone", false},
        {ABILITY_COMBAT_DRONE, "combat-drone", "Combat Drone", true},
        {ABILITY_PLASMA_BEAM, "plasma-beam", "Plasma Beam", false},
        {ABILITY_CORROSIVE_TRAIL, "corrosive-trail", "Corrosive Trail", true},
        {ABILITY_SINGULARITY, "singularity", "Singularity", false},
        {ABILITY_REALM_BREAKER, "realm-breaker", "Realm Breaker", false},
        {ABILITY_ARMAGEDDON, "armageddon", "Armageddon", false}
    }};
    static_assert(Balance::ABILITIES.size() == ABILITY_COUNT);
    return catalog;
}

AbilityId findAbility(std::string_view key)
{
    for (const auto& info : abilityCatalog()) if (key == info.key) return info.id;
    return ABILITY_COUNT;
}

namespace {
    bool valid(AbilityId id) { return id >= 0 && id < ABILITY_COUNT; }
    Vector2 facing(const Player& player) { return Vector2Rotate({0.0f, -1.0f}, player.getRotation() * DEG2RAD); }
    Enemy* nearest(Vector2 center, float range, const std::vector<std::string>& excluded = {})
    {
        Enemy* best = nullptr;
        float bestDistance = range * range;
        for (const auto& [id, enemy] : EnemyManager::GetInstance().getEnemies()) {
            if (enemy->isDead() || std::find(excluded.begin(), excluded.end(), id) != excluded.end()) continue;
            const float distance = Vector2DistanceSqr(center, enemy->getPosition());
            if (distance < bestDistance || (distance == bestDistance && (!best || id < best->getEnemyID()))) {
                best = enemy.get(); bestDistance = distance;
            }
        }
        return best;
    }
    bool intersects(const Bullet& bullet, Vector2 center, float radius)
    {
        return Bullet::hitFraction(bullet.getPreviousPosition(), bullet.getPosition(), center, radius + bullet.getRadius()) >= 0.0f;
    }
}

SkillSystem::SkillSystem() { reset(); }
void SkillSystem::reset()
{
    states = {};
    selected = ABILITY_COUNT;
    trails.clear(); flashes.clear();
    trailTick = 0.0f;
    drawPlayerPosition = drawFacing = {};
    rng.seed(Balance::SKILL_SEED);
}
bool SkillSystem::equip(AbilityId id)
{
    if (!valid(id)) return false;
    states[id].equipped = true;
    if (!abilityCatalog()[id].automatic) selected = id;
    return true;
}
void SkillSystem::unequip(AbilityId id, Player& player)
{
    if (!valid(id)) return;
    // Keep recharge debt: unequip/re-equip must not bypass cooldowns.
    const float debt = states[id].cooldown;
    states[id] = {};
    states[id].cooldown = debt;
    if (selected == id) selected = ABILITY_COUNT;
    if (id == ABILITY_DEFLECTOR_SHIELD) player.setDeflectorHits(0);
    if (id == ABILITY_CORROSIVE_TRAIL) trails.clear();
}
bool SkillSystem::queueCast(AbilityId id, Vector2 target)
{
    if (!valid(id) || states[id].queued || states[id].cooldown > Config::TIMER_EPSILON ||
        !std::isfinite(target.x) || !std::isfinite(target.y)) return false;
    states[id].queued = true;
    states[id].target = target;
    return true;
}
float SkillSystem::cooldown(AbilityId id) const { return valid(id) ? states[id].cooldown : 0.0f; }
bool SkillSystem::isActive(AbilityId id) const { return valid(id) && states[id].remaining > 0.0f; }
const Vector2* SkillSystem::decoy() const
{
    return isActive(ABILITY_HOLOGRAM_CLONE) ? &states[ABILITY_HOLOGRAM_CLONE].position : nullptr;
}
void SkillSystem::flash(Vector2 center, float radius)
{
    if (flashes.size() < Config::SKILL_VISUAL_LIMIT)
        flashes.push_back({center, center, radius, Theme::SKILL_FLASH_TIME});
}
void SkillSystem::arc(Vector2 from, Vector2 to)
{
    if (flashes.size() < Config::SKILL_VISUAL_LIMIT)
        flashes.push_back({from, to, 0.0f, Theme::SKILL_FLASH_TIME});
}

void SkillSystem::area(AbilityId id, Vector2 center, float radius, SkillResult& result)
{
    for (const auto& [key, enemy] : EnemyManager::GetInstance().getEnemies()) {
        if (enemy->isDead() || Vector2Distance(center, enemy->getPosition()) > radius + enemy->getHitbox().width) continue;
        int damage = Balance::ABILITIES[id].damage;
        if (id == ABILITY_SPACE_COLLAPSE || (id == ABILITY_NUCLEAR_MISSILE && enemy->getEnemyType() != BOSS_LEVEL_ENEMY))
            damage = enemy->getHealth();
        result.hits.push_back({key, damage, id != ABILITY_SPACE_COLLAPSE});
    }
}

void SkillSystem::begin(AbilityId id, Player& player, SkillResult& result)
{
    auto& state = states[id];
    const auto& tuning = Balance::ABILITIES[id];
    state.queued = false;
    state.cooldown = tuning.cooldown;
    state.remaining = tuning.duration;
    state.tick = state.elapsed = 0.0f;
    state.position = player.getPosition();
    state.direction = facing(player);
    state.target = Vector2Add(state.position, Vector2ClampValue(Vector2Subtract(state.target, state.position),
        0.0f, Balance::SKILL_TARGET_RANGE));
    switch (id) {
    case ABILITY_BLINK_DRIVE: {
        Vector2 direction = Vector2Normalize(Vector2Subtract(state.target, state.position));
        if (Vector2LengthSqr(direction) == 0.0f) direction = state.direction;
        const float distance = std::min(tuning.radius, Vector2Distance(state.position, state.target));
        player.teleport(Vector2Add(state.position, Vector2Scale(direction, distance)));
        arc(state.position, player.getPosition());
        result.teleported = true;
        break;
    }
    case ABILITY_DEFLECTOR_SHIELD: player.setDeflectorHits(Balance::SKILL_SHIELD_HITS); break;
    case ABILITY_SPACE_COLLAPSE:
        state.position = state.target; area(id, state.position, tuning.radius, result); flash(state.position, tuning.radius); break;
    case ABILITY_RADIANT_HALO: area(id, state.position, tuning.radius, result); flash(state.position, tuning.radius); break;
    case ABILITY_REPULSOR_PULSE:
        for (auto& [key, enemy] : EnemyManager::GetInstance().getEnemies()) {
            if (enemy->getEnemyType() == BARRICADE_ENEMY || enemy->getEnemyType() == BOSS_LEVEL_ENEMY) continue;
            const Vector2 offset = Vector2Subtract(enemy->getPosition(), state.position);
            if (Vector2Length(offset) <= tuning.radius + enemy->getHitbox().width)
                enemy->applySeparation(Vector2Scale(Vector2LengthSqr(offset) > 0.0f ? Vector2Normalize(offset) : state.direction,
                    Balance::SKILL_REPULSE_DISTANCE));
        }
        flash(state.position, tuning.radius); break;
    case ABILITY_CHAIN_LIGHTNING: {
        Vector2 origin = state.position;
        std::vector<std::string> visited;
        for (int bounce = 0; bounce < Balance::SKILL_CHAIN_TARGETS; ++bounce) {
            Enemy* enemy = nearest(origin, tuning.radius, visited);
            if (!enemy) break;
            visited.push_back(enemy->getEnemyID());
            result.hits.push_back({enemy->getEnemyID(), tuning.damage});
            arc(origin, enemy->getPosition());
            origin = enemy->getPosition();
        }
        break;
    }
    case ABILITY_HOLOGRAM_CLONE:
        state.position = Vector2Add(state.position, Vector2Scale(Vector2Rotate(state.direction, PI / 2.0f), Balance::SKILL_CLONE_OFFSET)); break;
    case ABILITY_SINGULARITY: case ABILITY_REALM_BREAKER: state.position = state.target; break;
    default: break;
    }
}

void SkillSystem::tick(AbilityId id, Player& player, SkillResult& result)
{
    auto& state = states[id];
    const auto& tuning = Balance::ABILITIES[id];
    const Vector2 playerPos = player.getPosition();
    switch (id) {
    case ABILITY_LASER_RINGS:
        for (int blade = 0; blade < Balance::SKILL_BLADE_COUNT; ++blade) {
            const float angle = state.elapsed * Balance::SKILL_ORBIT_SPEED + blade * 2.0f * PI / Balance::SKILL_BLADE_COUNT;
            area(id, Vector2Add(playerPos, Vector2Rotate({tuning.radius, 0.0f}, angle)), Balance::SKILL_BLADE_RADIUS, result);
        }
        break;
    case ABILITY_LIGHTNING_RING:
        for (auto& [key, enemy] : EnemyManager::GetInstance().getEnemies()) {
            const float distance = Vector2Distance(playerPos, enemy->getPosition());
            if (std::abs(distance - tuning.radius) <= Balance::SKILL_RING_WIDTH + enemy->getHitbox().width) {
                enemy->applyStun(Balance::SKILL_STUN_TIME);
                result.hits.push_back({key, tuning.damage});
            }
        }
        break;
    case ABILITY_SCRAP_MAGNET:
        for (const auto& pickup : ScrapManager::GetInstance().getPickups()) arc(pickup->getPosition(), playerPos);
        result.scrap += ScrapManager::GetInstance().collectAll(); break;
    case ABILITY_HOLOGRAM_CLONE:
        if (player.getWeapon() == WEAPON_LASER) {
            const Vector2 end = Vector2Add(state.position, Vector2Scale(facing(player), Balance::LASER_RANGE));
            for (const auto& [key, enemy] : EnemyManager::GetInstance().getEnemies())
                if (Bullet::hitFraction(state.position, end, enemy->getPosition(), Balance::LASER_RADIUS + enemy->getHitbox().width) >= 0.0f)
                    result.hits.push_back({key, player.getLaserDamage()});
            arc(state.position, end);
        } else player.fireClone(state.position, facing(player));
        break;
    case ABILITY_COMBAT_DRONE:
        if (Enemy* enemy = nearest(state.position, Balance::SKILL_DRONE_FIRE_RANGE)) {
            const Vector2 direction = Vector2Normalize(Vector2Subtract(enemy->getPosition(), state.position));
            Bullet shot(state.position, direction, false);
            shot.configure(PROJECTILE_CANNON, tuning.damage, Balance::CANNON_RADIUS, Balance::CANNON_SPEED);
            BulletManager::GetInstance().addBullet(shot);
            arc(state.position, enemy->getPosition());
        }
        break;
    case ABILITY_PLASMA_BEAM:
        for (const auto& [key, enemy] : EnemyManager::GetInstance().getEnemies()) {
            const Vector2 offset = Vector2Subtract(enemy->getPosition(), playerPos);
            if (Vector2Length(offset) <= tuning.radius + enemy->getHitbox().width &&
                (Vector2LengthSqr(offset) == 0.0f || Vector2DotProduct(Vector2Normalize(offset), facing(player)) >= Balance::SKILL_PLASMA_DOT))
                result.hits.push_back({key, tuning.damage});
        }
        break;
    case ABILITY_CORROSIVE_TRAIL:
        if (trails.size() < Config::SKILL_TRAIL_LIMIT)
            trails.push_back({Vector2Subtract(playerPos, Vector2Scale(facing(player), tuning.radius)), Balance::SKILL_TRAIL_LIFETIME});
        break;
    case ABILITY_SINGULARITY: area(id, state.position, tuning.radius, result); break;
    case ABILITY_REALM_BREAKER:
        for (const auto& [key, enemy] : EnemyManager::GetInstance().getEnemies()) {
            const Vector2 side = Vector2Scale(Vector2Rotate(state.direction, PI / 2.0f), Balance::SKILL_RIFT_HALF_LENGTH);
            if (Bullet::hitFraction(Vector2Subtract(state.position, side), Vector2Add(state.position, side),
                enemy->getPosition(), Balance::SKILL_RIFT_WIDTH + enemy->getHitbox().width) >= 0.0f)
                result.hits.push_back({key, tuning.damage});
        }
        break;
    case ABILITY_ARMAGEDDON: {
        const float zoom = std::max(utils::gameCamera.zoom, Config::TIMER_EPSILON);
        const float halfWidth = utils::gameCamera.offset.x / zoom * Balance::SKILL_BARRAGE_VIEW_FRACTION;
        const float halfHeight = utils::gameCamera.offset.y / zoom * Balance::SKILL_BARRAGE_VIEW_FRACTION;
        const float x = std::uniform_real_distribution<float>(-halfWidth, halfWidth)(rng);
        const float y = std::uniform_real_distribution<float>(-halfHeight, halfHeight)(rng);
        const Vector2 center = Vector2Add(utils::gameCamera.target, {x, y});
        area(id, center, tuning.radius, result); flash(center, tuning.radius);
        break;
    }
    default: break;
    }
}

SkillResult SkillSystem::update(float dt, Player& player, Vector2 aim, bool activateSelected)
{
    SkillResult result;
    if (dt <= 0.0f || !std::isfinite(dt) || player.getHealth() <= 0) return result;
    for (auto& effect : flashes) effect.remaining -= dt;
    std::erase_if(flashes, [](const Flash& effect) { return effect.remaining <= 0.0f; });
    for (auto& trail : trails) trail.remaining -= dt;
    std::erase_if(trails, [](const Trail& trail) { return trail.remaining <= 0.0f; });
    if (activateSelected && valid(selected)) queueCast(selected, aim);
    for (const auto& info : abilityCatalog()) {
        auto& state = states[info.id];
        const auto& tuning = Balance::ABILITIES[info.id];
        state.cooldown = std::max(0.0f, state.cooldown - dt);
        if (state.equipped && info.automatic && state.cooldown <= Config::TIMER_EPSILON)
            queueCast(info.id, aim);
        if (state.queued) begin(info.id, player, result);
        if (state.remaining <= 0.0f) continue;
        const float activeDt = std::min(dt, state.remaining);
        state.elapsed += activeDt;
        if (info.id == ABILITY_COMBAT_DRONE) {
            const Enemy* target = nearest(player.getPosition(), tuning.radius);
            state.position = Vector2MoveTowards(state.position, target ? target->getPosition() : player.getPosition(),
                Balance::SKILL_DRONE_SPEED * activeDt);
        }
        if (info.id == ABILITY_SINGULARITY) {
            for (auto& [key, enemy] : EnemyManager::GetInstance().getEnemies()) {
                if (enemy->getEnemyType() == BARRICADE_ENEMY || enemy->getEnemyType() == BOSS_LEVEL_ENEMY) continue;
                if (Vector2Distance(state.position, enemy->getPosition()) <= tuning.radius) {
                    const Vector2 next = Vector2MoveTowards(enemy->getPosition(), state.position, Balance::SKILL_PULL_SPEED * activeDt);
                    enemy->applySeparation(Vector2Subtract(next, enemy->getPosition()));
                }
            }
        }
        // Swept interception runs each simulation frame, independently of damage ticks.
        if (info.id == ABILITY_INTERCEPTOR || info.id == ABILITY_REALM_BREAKER) {
            auto& bullets = BulletManager::GetInstance().getBullets();
            std::erase_if(bullets, [&](const Bullet& bullet) {
                if (!bullet.isEnemyBullet()) return false;
                bool caught = false;
                if (info.id == ABILITY_INTERCEPTOR) caught = intersects(bullet, player.getPosition(), tuning.radius);
                else {
                    const Vector2 side = Vector2Scale(Vector2Rotate(state.direction, PI / 2.0f), Balance::SKILL_RIFT_HALF_LENGTH);
                    // Capsule overlap including crossed segments and both rounded ends.
                    const Vector2 a = Vector2Subtract(state.position, side), b = Vector2Add(state.position, side);
                    const Vector2 from = bullet.getPreviousPosition(), to = bullet.getPosition();
                    Vector2 cross{};
                    caught = CheckCollisionLines(from, to, a, b, &cross) || intersects(bullet, a, Balance::SKILL_RIFT_WIDTH) ||
                        intersects(bullet, b, Balance::SKILL_RIFT_WIDTH) ||
                        Bullet::hitFraction(a, b, to, Balance::SKILL_RIFT_WIDTH) >= 0.0f ||
                        Bullet::hitFraction(a, b, from, Balance::SKILL_RIFT_WIDTH) >= 0.0f;
                }
                if (caught) arc(info.id == ABILITY_INTERCEPTOR ? player.getPosition() : state.position, bullet.getPosition());
                return caught;
            });
        }
        // Tick at activation, then strictly before duration end (no duplicate final tick).
        while (state.tick < state.elapsed - Config::TIMER_EPSILON) {
            tick(info.id, player, result);
            state.tick += info.id == ABILITY_HOLOGRAM_CLONE ? player.getPrimaryInterval() : tuning.interval;
        }
        state.remaining = std::max(0.0f, state.remaining - dt);
        if (state.remaining == 0.0f) {
            if (info.id == ABILITY_NUCLEAR_MISSILE) {
                area(info.id, state.target, tuning.radius, result); flash(state.target, tuning.radius);
            }
            if (info.id == ABILITY_DEFLECTOR_SHIELD) player.setDeflectorHits(0);
        }
    }
    // A target in overlapping acid pools takes one corrosion tick, not one per pool.
    if (!trails.empty()) {
        // Reuse a separate pool clock so pools keep damaging after the emitter ends.
        trailTick -= dt;
        while (trailTick <= Config::TIMER_EPSILON) {
            for (auto& [key, enemy] : EnemyManager::GetInstance().getEnemies()) {
                const bool inside = std::any_of(trails.begin(), trails.end(), [&](const Trail& trail) {
                    return Vector2Distance(trail.position, enemy->getPosition()) <=
                        Balance::ABILITIES[ABILITY_CORROSIVE_TRAIL].radius + enemy->getHitbox().width;
                });
                if (inside) {
                    enemy->applyCorrosion(Balance::SKILL_CORROSION_TIME);
                    result.hits.push_back({key, Balance::ABILITIES[ABILITY_CORROSIVE_TRAIL].damage});
                }
            }
            trailTick += Balance::ABILITIES[ABILITY_CORROSIVE_TRAIL].interval;
        }
    } else trailTick = 0.0f;
    drawPlayerPosition = player.getPosition();
    drawFacing = facing(player);
    return result;
}

void SkillSystem::draw() const
{
    const Color color = Theme::COLOR_ACCENT;
    for (const auto& trail : trails)
        DrawCircleLinesV(trail.position, Balance::ABILITIES[ABILITY_CORROSIVE_TRAIL].radius, Theme::COLOR_TOXIC);
    for (const auto& effect : flashes) {
        const Color tint = Fade(color, effect.remaining / Theme::SKILL_FLASH_TIME);
        if (effect.radius > 0.0f) DrawCircleLinesV(effect.from, effect.radius, tint);
        else DrawLineEx(effect.from, effect.to, Theme::SKILL_LINE_WIDTH, tint);
    }
    for (const auto& info : abilityCatalog()) {
        if (!isActive(info.id)) continue;
        const auto& state = states[info.id];
        const auto& tuning = Balance::ABILITIES[info.id];
        switch (info.id) {
        case ABILITY_LASER_RINGS:
            for (int blade = 0; blade < Balance::SKILL_BLADE_COUNT; ++blade) {
                const float angle = state.elapsed * Balance::SKILL_ORBIT_SPEED + blade * 2.0f * PI / Balance::SKILL_BLADE_COUNT;
                DrawCircleLinesV(Vector2Add(drawPlayerPosition, Vector2Rotate({tuning.radius, 0.0f}, angle)), Balance::SKILL_BLADE_RADIUS, color);
            }
            break;
        case ABILITY_HOLOGRAM_CLONE: case ABILITY_COMBAT_DRONE:
            if (info.id == ABILITY_HOLOGRAM_CLONE) {
                const auto& sprite = ResourceManager::GetInstance().GetTextureRef("player_deacceleration");
                if (sprite.id != 0) DrawTexturePro(sprite, {0.0f, 0.0f, static_cast<float>(Theme::ORIGINAL_PLAYER_FRAME),
                    static_cast<float>(Theme::ORIGINAL_PLAYER_FRAME)},
                    {state.position.x, state.position.y, Theme::ORIGINAL_PLAYER_SIZE, Theme::ORIGINAL_PLAYER_SIZE},
                    {Theme::ORIGINAL_PLAYER_SIZE / 2.0f, Theme::ORIGINAL_PLAYER_SIZE / 2.0f},
                    std::atan2(drawFacing.y, drawFacing.x) * RAD2DEG + 90.0f, color);
            }
            DrawCircleLinesV(state.position, Theme::SKILL_COMPANION_RADIUS, color);
            DrawLineEx(state.position, Vector2Add(state.position, Vector2Scale(drawFacing, Theme::SKILL_COMPANION_RADIUS)), Theme::SKILL_LINE_WIDTH, color);
            break;
        case ABILITY_NUCLEAR_MISSILE:
            DrawCircleLinesV(Vector2Lerp(state.position, state.target, state.elapsed / tuning.duration), Theme::SKILL_COMPANION_RADIUS, color);
            DrawCircleLinesV(state.target, tuning.radius, Fade(color, Theme::SKILL_FILL_ALPHA)); break;
        case ABILITY_REALM_BREAKER: {
            const Vector2 side = Vector2Scale(Vector2Rotate(state.direction, PI / 2.0f), Balance::SKILL_RIFT_HALF_LENGTH);
            DrawLineEx(Vector2Subtract(state.position, side), Vector2Add(state.position, side), Balance::SKILL_RIFT_WIDTH * 2.0f, Fade(color, Theme::SKILL_FILL_ALPHA)); break;
        }
        case ABILITY_PLASMA_BEAM: {
            const float angle = std::acos(Balance::SKILL_PLASMA_DOT);
            const Vector2 end = Vector2Add(drawPlayerPosition, Vector2Scale(drawFacing, tuning.radius));
            DrawLineEx(drawPlayerPosition, end, Theme::SKILL_LINE_WIDTH, color);
            for (const float sign : {-1.0f, 1.0f})
                DrawLineEx(drawPlayerPosition, Vector2Add(drawPlayerPosition, Vector2Scale(Vector2Rotate(drawFacing, sign * angle), tuning.radius)), Theme::SKILL_LINE_WIDTH, color);
            break;
        }
        case ABILITY_SINGULARITY: DrawCircleLinesV(state.position, tuning.radius, color); break;
        case ABILITY_SCRAP_MAGNET: DrawCircleLinesV(drawPlayerPosition, Theme::SKILL_MAGNET_RADIUS, Theme::COLOR_HARVEST); break;
        case ABILITY_LIGHTNING_RING: case ABILITY_DEFLECTOR_SHIELD: case ABILITY_INTERCEPTOR:
            DrawCircleLinesV(drawPlayerPosition, tuning.radius, color); break;
        default: break;
        }
    }
}

void SkillSystem::drawStatus() const
{
    if (!valid(selected) && std::none_of(states.begin(), states.end(), [](const State& state) { return state.equipped; })) return;
    const std::string text = valid(selected) ? std::string("Q: ") + abilityCatalog()[selected].name +
        (cooldown(selected) > 0.0f ? "  " + std::to_string(static_cast<int>(std::ceil(cooldown(selected)))) + "s" : "  READY") :
        "AUTOMATIC ABILITIES EQUIPPED";
    DrawTextEx(ResourceManager::GetInstance().GetFont(Theme::FONT_PRIMARY), text.c_str(), Theme::SKILL_STATUS_POSITION,
        Theme::TEXT_CAPTION, Theme::TEXT_SPACING, Theme::COLOR_ACCENT);
}

std::vector<std::string> SkillSystem::commandCompletions()
{
    std::vector<std::string> result = {"skill list", "skill status", "augment list"};
    for (const auto& info : augmentCatalog()) result.push_back(std::string("augment ") + info.key);
    for (const auto& info : abilityCatalog())
        for (const char* verb : {"equip", "cast", "unequip"}) result.push_back(std::string("skill ") + verb + " " + info.key);
    return result;
}

std::vector<std::string> SkillSystem::command(const std::string& line, Player* player)
{
    std::istringstream input(line);
    std::string group, verb, key, extra;
    input >> group >> verb >> key >> extra;
    if (!extra.empty()) return {"Too many arguments."};
    if (group == "augment" && key.empty()) {
        if (verb == "list") {
            std::vector<std::string> result;
            for (const auto& info : augmentCatalog()) result.push_back(std::string(info.key) + ": " + info.description);
            return result;
        }
        const auto id = findAugment(verb);
        if (id == AUG_COUNT) return {"Unknown augment. Use augment list."};
        if (!player || player->getHealth() <= 0) return {"Start a living run first."};
        return {applyAugment(*player, id) ? "Applied " + verb : "Already at cap or hull is full."};
    }
    if (group != "skill") return {"Usage: augment <key|list> or skill <list|status|equip|cast|unequip> [key]"};
    if ((verb == "list" || verb == "status") && key.empty()) {
        std::vector<std::string> result;
        for (const auto& info : abilityCatalog()) {
            const auto& state = states[info.id];
            result.push_back(std::string(info.key) + (info.automatic ? " [auto]" : " [Q]") +
                (state.equipped ? " equipped" : "") + (isActive(info.id) ? " active" : "") +
                " cooldown=" + std::to_string(static_cast<int>(std::ceil(state.cooldown))) + "s");
        }
        return result;
    }
    const auto id = findAbility(key);
    if (id == ABILITY_COUNT || (verb != "equip" && verb != "cast" && verb != "unequip"))
        return {"Usage: skill <equip|cast|unequip> <key>. Use skill list or Tab."};
    if (!player || player->getHealth() <= 0) return {"Start a living run first."};
    if (verb == "equip") { equip(id); return {"Equipped " + key + (abilityCatalog()[id].automatic ? " (automatic)." : " (press Q).")}; }
    if (verb == "unequip") { unequip(id, *player); return {"Unequipped " + key}; }
    const Vector2 aim = GetScreenToWorld2D(GetMousePosition(), utils::gameCamera);
    return {queueCast(id, aim) ? "Queued " + key + "; close the console to activate." : "Ability is cooling down or already queued."};
}
