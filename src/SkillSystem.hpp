#pragma once
#include "raylib.h"
#include <array>
#include <random>
#include <string>
#include <string_view>
#include <vector>

class Player;
enum AbilityId {
    ABILITY_LASER_RINGS, ABILITY_DEFLECTOR_SHIELD, ABILITY_LIGHTNING_RING, ABILITY_BLINK_DRIVE,
    ABILITY_NUCLEAR_MISSILE, ABILITY_SPACE_COLLAPSE, ABILITY_RADIANT_HALO, ABILITY_REPULSOR_PULSE,
    ABILITY_INTERCEPTOR, ABILITY_SCRAP_MAGNET, ABILITY_CHAIN_LIGHTNING, ABILITY_HOLOGRAM_CLONE,
    ABILITY_COMBAT_DRONE, ABILITY_PLASMA_BEAM, ABILITY_CORROSIVE_TRAIL, ABILITY_SINGULARITY,
    ABILITY_REALM_BREAKER, ABILITY_ARMAGEDDON, ABILITY_COUNT
};
struct AbilityInfo { AbilityId id; const char* key; const char* name; bool automatic; };
const std::array<AbilityInfo, ABILITY_COUNT>& abilityCatalog();
AbilityId findAbility(std::string_view key);
struct SkillHit { std::string enemyId; int damage; bool dropsScrap = true; };
struct SkillResult { std::vector<SkillHit> hits; int scrap = 0; bool teleported = false; };

// Game-owned simulation system. It reports damage; Game owns deaths and rewards.
class SkillSystem {
public:
    SkillSystem();
    void reset();
    bool equip(AbilityId id);
    void unequip(AbilityId id, Player& player);
    bool queueCast(AbilityId id, Vector2 target);
    SkillResult update(float dt, Player& player, Vector2 aim, bool activateSelected);
    void draw() const;
    void drawStatus() const;
    float cooldown(AbilityId id) const;
    bool isActive(AbilityId id) const;
    const Vector2* decoy() const;
    std::vector<std::string> command(const std::string& line, Player* player);
    static std::vector<std::string> commandCompletions();
private:
    struct State {
        bool equipped = false, queued = false;
        float cooldown = 0.0f, remaining = 0.0f, tick = 0.0f, elapsed = 0.0f;
        Vector2 position{}, target{}, direction{};
    };
    struct Trail { Vector2 position; float remaining; };
    struct Flash { Vector2 from, to; float radius, remaining; };
    void begin(AbilityId id, Player& player, SkillResult& result);
    void tick(AbilityId id, Player& player, SkillResult& result);
    void area(AbilityId id, Vector2 center, float radius, SkillResult& result);
    void flash(Vector2 center, float radius);
    void arc(Vector2 from, Vector2 to);
    std::array<State, ABILITY_COUNT> states{};
    AbilityId selected = ABILITY_COUNT;
    std::vector<Trail> trails;
    std::vector<Flash> flashes;
    float trailTick = 0.0f;
    Vector2 drawPlayerPosition{}, drawFacing{};
    std::mt19937 rng;
};
