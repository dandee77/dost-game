#pragma once
#include <array>
#include "raylib.h"
#include "DebrisKind.hpp"

// Player equipment prototypes. TUNE in playtests before adding progression.
namespace Balance {
    // Population-led endurance pacing. Seconds exclude pause/cards/hub. TUNE.
    struct SpawnPoint { double seconds, perSecond; int population; };
    inline constexpr std::array<SpawnPoint, 7> ENEMY_SPAWN_CURVE = {{
        {0, 0.7, 120}, {300, 1.5, 200}, {600, 4, 400}, {900, 8, 650},
        {1200, 12, 900}, {1500, 16, 1200}, {2100, 20, 1500}
    }};
    inline constexpr double ENEMY_HP_GRACE_SECONDS = 300;
    inline constexpr double ENEMY_HP_GROWTH_PER_SECOND = 0.025 / 60.0;
    inline constexpr double ENEMY_HP_MAX_MULTIPLIER = 2;
    inline constexpr double ENEMY_RANGED_START_SECONDS = 180;
    inline constexpr double ENEMY_RANGED_FULL_SECONDS = 1500;
    inline constexpr double ENEMY_RANGED_MAX_CHANCE = 0.15;
    inline constexpr int LOW_HEALTH = 30, MID_HEALTH = 50;
    inline constexpr int ENEMY_MAX_SPAWNS_PER_UPDATE = 32;
    inline constexpr int FIELD_XP_START = 100, FIELD_XP_STEP = 20, FIELD_XP_MAX = 600;
    inline constexpr int RETURN_CAPACITY = 1000, RETURN_REQUIRED = 500;
    inline constexpr std::array<int, 4> WEAPON_TIER_PRICES = {500, 1500, 4000, 10000};
    inline constexpr std::array<double, 5> BATTERY_FRACTIONS = {0.2, 0.5, 1, 1.5, 2};
    inline constexpr std::array<int, 5> BATTERY_PRICES = {100, 250, 500, 700, 900};
    inline constexpr int REPAIR_SCRAP_PER_HP = 10;
    inline constexpr unsigned int LOOT_SEED = 20261023;
    inline constexpr int LOW_TRADE_MIN = 1, LOW_TRADE_MAX = 3;
    inline constexpr int MID_TRADE_MIN = 3, MID_TRADE_MAX = 7;
    // P5 skills prototype. TUNE: acquisition and final balance intentionally deferred.
    inline constexpr int AUG_MAX_LEVEL = 10, AUG_HULL_BONUS = 20;
    inline constexpr float AUG_PAYLOAD_BONUS = 0.15f, AUG_CRIT_CHANCE = 0.05f;
    inline constexpr float AUG_CRIT_MULTIPLIER = 2.0f, AUG_REPAIR_FRACTION = 0.25f;
    inline constexpr int CRIT_ROLL_STEPS = 10000;
    inline constexpr unsigned int SKILL_SEED = 20261017;
    struct AbilityTuning { float cooldown, duration, radius; int damage; float interval; };
    // Order matches AbilityId. Radius is in world units; damage is per tick.
    inline constexpr std::array<AbilityTuning, 18> ABILITIES = {{
        {12.0f, 8.0f, 18.0f, 12, 0.2f}, // Laser Rings
        {16.0f, 8.0f, 8.0f, 0, 0.2f},  // Deflector Shield
        {14.0f, 8.0f, 25.0f, 8, 0.5f}, // Lightning Ring
        {4.0f, 0.2f, 35.0f, 0, 0.2f},  // Blink Drive
        {30.0f, 0.7f, 55.0f, 250, 0.7f}, // Nuclear Missile
        {35.0f, 0.2f, 32.0f, 300, 0.2f}, // Space Collapse
        {8.0f, 0.2f, 32.0f, 60, 0.2f}, // Radiant Halo
        {5.0f, 0.2f, 30.0f, 0, 0.2f},  // Repulsor Pulse
        {12.0f, 8.0f, 38.0f, 0, 0.1f}, // Point-Defense Interceptor
        {15.0f, 5.0f, 0.0f, 0, 0.2f},  // Scrap Magnet
        {7.0f, 0.2f, 45.0f, 35, 0.2f}, // Chain Lightning
        {18.0f, 10.0f, 60.0f, 0, 0.5f}, // Hologram Clone
        {20.0f, 15.0f, 90.0f, 15, 0.4f}, // Combat Drone
        {12.0f, 4.0f, 65.0f, 12, 0.15f}, // Plasma Beam
        {14.0f, 8.0f, 8.0f, 6, 0.3f}, // Corrosive Trail
        {22.0f, 6.0f, 42.0f, 10, 0.2f}, // Singularity
        {20.0f, 6.0f, 24.0f, 20, 0.2f}, // Realm Breaker
        {35.0f, 6.0f, 22.0f, 80, 0.3f} // Armageddon
    }};
    inline constexpr float SKILL_TARGET_RANGE = 90.0f, SKILL_RING_WIDTH = 5.0f;
    inline constexpr float SKILL_ORBIT_SPEED = 6.0f, SKILL_BLADE_RADIUS = 4.0f;
    inline constexpr int SKILL_BLADE_COUNT = 3, SKILL_SHIELD_HITS = 3, SKILL_CHAIN_TARGETS = 6;
    inline constexpr float SKILL_STUN_TIME = 0.6f, SKILL_CORROSION_TIME = 1.0f;
    inline constexpr float SKILL_SLOW_MULTIPLIER = 0.5f, SKILL_WEAKEN_MULTIPLIER = 0.5f;
    inline constexpr float SKILL_REPULSE_DISTANCE = 22.0f, SKILL_PULL_SPEED = 28.0f;
    inline constexpr float SKILL_PLASMA_DOT = 0.8660254f, SKILL_DRONE_SPEED = 70.0f;
    inline constexpr float SKILL_DRONE_FIRE_RANGE = 35.0f, SKILL_CLONE_OFFSET = 18.0f;
    inline constexpr float SKILL_TRAIL_LIFETIME = 3.0f, SKILL_BLINK_IFRAME = 0.25f;
    inline constexpr float SKILL_RIFT_HALF_LENGTH = 25.0f, SKILL_RIFT_WIDTH = 6.0f;
    inline constexpr float SKILL_BARRAGE_VIEW_FRACTION = 0.85f;
    inline constexpr int SKILL_LOW_SCRAP = 2, SKILL_MID_SCRAP = 5;
    // Repeat picks continue indefinitely; physical size stops growing at level five. TUNE.
    inline constexpr int ABILITY_SIZE_GROWTH_LEVEL = 5;
    inline constexpr std::size_t UPGRADE_OFFER_COUNT = 3;
    struct AbilityGrowth { float radius, damage, duration, recharge, frequency; };
    inline constexpr std::array<AbilityGrowth, 18> ABILITY_GROWTH = {{
        {0.08f, 0.25f, 0.10f, 0.0f, 0.0f}, // Rings: +1 blade too
        {0.0f, 0.0f, 0.15f, 0.0f, 0.0f},  // Shield: +1 hit too
        {0.10f, 0.25f, 0.10f, 0.0f, 0.0f},
        {0.15f, 0.0f, 0.0f, 0.10f, 0.0f}, // Blink: range and recharge
        {0.15f, 0.30f, 0.0f, 0.05f, 0.0f},
        {0.15f, 0.0f, 0.0f, 0.0f, 0.0f},  // Collapse: +1 distinct zone too
        {0.15f, 0.30f, 0.0f, 0.05f, 0.0f},
        {0.10f, 0.0f, 0.0f, 0.05f, 0.0f}, // Repulsor: stronger push too
        {0.10f, 0.0f, 0.15f, 0.0f, 0.0f},
        {0.0f, 0.0f, 0.20f, 0.05f, 0.10f}, // Magnet: uptime and collection rate
        {0.10f, 0.25f, 0.0f, 0.0f, 0.0f},  // Chain: +1 target too
        {0.0f, 0.0f, 0.15f, 0.0f, 0.15f}, // Clone: duration and fire rate
        {0.0f, 0.25f, 0.0f, 0.0f, 0.0f},  // Drones: +1 drone, +15 HP too
        {0.10f, 0.25f, 0.10f, 0.0f, 0.0f},
        {0.15f, 0.25f, 0.10f, 0.0f, 0.0f},
        {0.10f, 0.25f, 0.10f, 0.0f, 0.0f},
        {0.15f, 0.25f, 0.10f, 0.0f, 0.0f},
        {0.10f, 0.20f, 0.0f, 0.0f, 0.0f}   // Barrage: +1 blast per volley too
    }};
    inline constexpr int SKILL_CHAIN_TARGETS_PER_LEVEL = 1;
    inline constexpr float SKILL_FORCE_PER_LEVEL = 0.15f;
    inline constexpr float SKILL_COLLAPSE_SPACING = 1.5f;
    inline constexpr int SKILL_DRONE_HEALTH = 30, SKILL_DRONE_HEALTH_PER_LEVEL = 15;
    inline constexpr float SKILL_DRONE_RADIUS = 3.0f, SKILL_DRONE_SPACING = 10.0f;
    inline constexpr float SKILL_DRONE_STANDOFF = 15.0f, SKILL_DRONE_CONTACT_INTERVAL = 0.5f;
    // Fixed per-object sizes/rewards; no random scaling. TUNE in debris playtests.
    inline constexpr std::array<float, DEBRIS_KIND_COUNT> DEBRIS_RADII = {3.75f, 3.0f, 8.0f, 3.3f, 5.7f, 3.0f, 6.8f, 5.0f, 6.0f, 6.0f};
    inline constexpr std::array<int, DEBRIS_KIND_COUNT> DEBRIS_SCRAP_VALUES = {3, 2, 8, 2, 5, 2, 6, 4, 3, 5};
    inline constexpr int DEBRIS_ROT_SPEED_MIN = 5, DEBRIS_ROT_SPEED_MAX = 240;
    inline constexpr int DEBRIS_SPEED_MIN = 5, DEBRIS_SPEED_MAX = 15;
    inline constexpr int DEBRIS_ANGLE_VARIATION = 30, DEBRIS_MAX_SPAWN_BATCH = 3;
    inline constexpr float DEBRIS_SPAWN_DISTANCE = 150.0f, DEBRIS_DESPAWN_DISTANCE = 150.0f;
    inline constexpr float DEBRIS_SPAWN_START = 1.5f, DEBRIS_SPAWN_MIN = 0.25f, DEBRIS_SPAWN_RAMP_TIME = 600.0f;
    inline constexpr float SCRAP_MAGNET_SPEED = 150.0f;
    inline constexpr float SCRAP_PICKUP_RADIUS = 2.0f, SCRAP_LIFETIME = 20.0f;
    inline constexpr int SCRAP_MAX_PICKUPS = 150;
    inline constexpr float DEBRIS_PREVIEW_RADIUS = 60.0f;
    // Barricade event prototype. TUNE after playtests.
    inline constexpr float BARRICADE_TRIGGER_TIME = 600.0f;
    inline constexpr float BARRICADE_DURATION = 30.0f, BARRICADE_SCATTER_TIME = 4.0f;
    inline constexpr int BARRICADE_SEGMENTS = 64, BARRICADE_HEALTH = 120;
    inline constexpr float BARRICADE_START_RADIUS = 130.0f, BARRICADE_END_RADIUS = 45.0f;
    inline constexpr std::array<float, 3> BARRICADE_BODY_RADII = {3.75f, 6.25f, 7.5f};
    inline constexpr float BARRICADE_SCATTER_SPEED = 55.0f;
    inline constexpr float BARRICADE_ORBIT_SPEED = 4.0f; // Degrees per simulation second.
    inline constexpr float BARRICADE_ESCAPE_MARGIN = 90.0f, BARRICADE_RESTITUTION = 0.2f;
    inline constexpr int ENEMY_LIMIT = 10'000;
    inline constexpr float ENEMY_SPAWN_RADIUS = 150.0f;
    // Soft low-enemy body spacing; combat hitboxes remain unchanged. TUNE.
    inline constexpr float CROWD_RADIUS_SCALE = 1.5f;
    inline constexpr float CROWD_SLIDE = 0.25f;
    inline constexpr float CROWD_RESPONSE = 12.0f;
    inline constexpr float CROWD_MAX_PUSH_SPEED = 60.0f;
    inline constexpr float CROWD_MAX_STEP_TIME = 0.05f;
    inline constexpr Vector2 PLAYER_SPAWN = {250.0f, 250.0f};
    inline constexpr float PLAYER_RADIUS = 4.0f;
    inline constexpr float PLAYER_TURN_BASE = 4.0f, PLAYER_TURN_SPEED_BONUS = 4.0f;
    inline constexpr float AUG_ATTACK_MULT = 0.9f, AUG_SPEED_MULT = 1.1f;
    inline constexpr float AUG_IFRAME_MULT = 1.1f, AUG_TURN_MULT = 1.1f, AUG_KNOCKBACK = 50.0f;
    inline constexpr int AUG_HEAL = 10;
    inline constexpr float SHIELD_FRONT_HALF_ANGLE = 60.0f, SHIELD_SIDE_HALF_ANGLE = 90.0f;
    inline constexpr int PLAYER_MAX_HEALTH = 100;
    inline constexpr float PLAYER_ATTACK_COOLDOWN = 0.5f;
    inline constexpr float PLAYER_SPEED = 50.0f;
    inline constexpr float PLAYER_ACCELERATION = 400.0f;
    inline constexpr float PLAYER_STUN_TIME = 0.2f;
    inline constexpr float PLAYER_IFRAME_TIME = 0.8f;
    inline constexpr float PLAYER_COLLISION_NUDGE = 20.0f;
    inline constexpr int PLAYER_CONTACT_DAMAGE = 10;
    inline constexpr int PLAYER_DAMAGE_MIN = 7, PLAYER_DAMAGE_MAX = 12;
    inline constexpr float SCATTER_ANGLE = 30.0f;
    inline constexpr float BURST_DELAY = 0.1f;
    inline constexpr float MUZZLE_OFFSET = 3.0f;
    inline constexpr float CANNON_SPEED = 200.0f, CANNON_RADIUS = 0.6f;
    inline constexpr float HEAVY_SPEED = 100.0f, HEAVY_RADIUS = 2.0f;
    inline constexpr int HEAVY_DAMAGE = 40, HEAVY_PIERCE = 3;
    inline constexpr float HEAVY_COOLDOWN = 1.2f;
    inline constexpr float ROCKET_SPEED = 90.0f, ROCKET_RADIUS = 0.7f;
    inline constexpr int ROCKET_DAMAGE = 30;
    inline constexpr float ROCKET_COOLDOWN = 0.9f, ROCKET_SPLASH_RADIUS = 14.0f;
    inline constexpr float LASER_RANGE = 100.0f, LASER_RADIUS = 1.5f;
    inline constexpr float LASER_TICK = 0.1f;
    inline constexpr int LASER_DAMAGE = 4;
    inline constexpr std::array<float, 4> ENGINE_SPEED = {1.0f, 0.9f, 1.1f, 1.4f};
    inline constexpr std::array<float, 4> ENGINE_ACCELERATION = {1.0f, 1.5f, 1.2f, 1.0f};
    inline constexpr float BOOST_DURATION = 0.45f, BOOST_COOLDOWN = 3.0f, BOOST_SPEED = 2.5f;
    inline constexpr std::array<int, 5> SHIELD_CAPACITY = {0, 30, 40, 50, 0};
    inline constexpr float SHIELD_RECHARGE_DELAY = 3.0f, SHIELD_RECHARGE_RATE = 10.0f;
    inline constexpr float SHIELD_RADIUS = 7.5f;
    inline constexpr float SHIELD_FRONT_DOT = 0.5f, SHIELD_SIDE_DOT = 0.0f;
    inline constexpr float INVINCIBILITY_DURATION = 2.0f, INVINCIBILITY_COOLDOWN = 8.0f;
    inline constexpr int LOW_SCORE = 10, MID_SCORE = 50, DEBRIS_SCORE = 5;
    inline constexpr float HULL_SLIGHT_FRACTION = 0.75f, HULL_DAMAGED_FRACTION = 0.5f, HULL_CRITICAL_FRACTION = 0.25f;
}
