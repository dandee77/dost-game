#pragma once
#include <array>
#include "raylib.h"
#include "DebrisKind.hpp"

// Player equipment prototypes. TUNE in playtests before adding progression.
namespace Balance {
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
    inline constexpr float BARRICADE_TRIGGER_TIME = 120.0f;
    inline constexpr float BARRICADE_DURATION = 30.0f, BARRICADE_SCATTER_TIME = 4.0f;
    inline constexpr int BARRICADE_SEGMENTS = 64, BARRICADE_HEALTH = 120;
    inline constexpr float BARRICADE_START_RADIUS = 130.0f, BARRICADE_END_RADIUS = 45.0f;
    inline constexpr float BARRICADE_BODY_RADIUS = 3.5f, BARRICADE_SCATTER_SPEED = 55.0f;
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
