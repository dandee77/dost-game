# Game Design

The single source for gameplay rules and numbers. Code reads numbers from `src/Balance.hpp`; this file explains them. When a number changes, change both in the same commit. Values marked **TUNE** are first guesses for the item-28 balance pass.

Values marked **(SA)** are the current Space Ablaze values, kept so the game still feels like Space Ablaze.

---

## Design Pillars

1. **Readable chaos.** Many enemies, but the player always sees what hurts: toxic green is danger, gold is reward, sky blue is you.
2. **Every kill feeds the loop.** Junk becomes scrap, scrap becomes gear, gear clears more junk.
3. **Fair competition.** The same seed gives every player the same waves; score rewards skill, not luck.
4. **A judge sees everything in 5 minutes.** Wave 1 teaches, the first dock visit happens within 2 minutes, a boss is reachable through Endless or by skilled play.

---

## Player

### P1 equipment prototypes (14 October, user request)

These are debug-selectable prototypes, with no acquisition conditions or progression integration. New runs use the original ship, original bullet and base movement with no shield. `player default build` restores this original loadout; `player gunner build` selects the newly added modular cannon/base-engine/no-shield loadout. Every build preset is shield-free; shields are selected separately with `player shield ...` for testing, with future skill integration deferred. All values are in `Balance.hpp` and are TUNE. Switching equipment preserves health, score and earned augments; presets turn auto-fire off. Projectiles already in flight keep their original weapon, damage and piercing count. Beam/burst state and relevant cooldowns reset when replacing their equipment. Explicit shield selection refills the selected shield; presets clear shield charge and active guard/recharge timers.

| Weapon | Behavior | Values |
|---|---|---|
| Cannon | Animated shot; swept circular hitbox; consumed on first hit unless piercing augmented | 7–12 damage, 0.5 s cooldown, speed 200, radius 0.6 |
| Laser (Zapper art) | Continuous piercing capsule from the muzzle along ship facing; damages all intersecting enemies and destroys debris | Range 100, radius 1.5; immediate first tick, then 4 damage every 0.1 s; long frames accumulate all due ticks |
| Rockets | Swept collision; detonates once at first contact; full damage to each overlapping enemy, destroys overlapping debris | 30 damage, 0.9 s cooldown, speed 90, radius 0.7; splash radius 14 |
| Heavy | Slow energy shot; hits each target at most once, nearest first | 40 damage, 1.2 s cooldown, speed 100, radius 2; pierces 3 targets |

LMB and E use the existing fire/auto-fire controls. Rapid Fire scales every weapon cooldown, including laser ticks. Scatter and Trigger Happy apply to projectile weapons; continuous laser already hits every target in its beam and does not fire burst/scatter projectiles. Piercing adds targets to cannon/heavy; rockets always detonate once. Inertia Impact applies to all weapons. Damage dealt records actual HP removed (overkill excluded) for equipment attacks. Existing enemy/debris kill scores and effects are retained.

| Engine | Speed multiplier | Acceleration multiplier | Skill |
|---|---|---|---|
| Base | 1.0 | 1.0 | None |
| Pulse | 0.9 | 1.5 | Strong acceleration |
| Burst | 1.1 | 1.2 | Space: speed ×2.5 for 0.45 s, 3 s cooldown |
| Supercharged | 1.4 | 1.0 | Higher sustained speed |

| Shield | Protection | Capacity / timing |
|---|---|---|
| Front | Facing ±60 degrees | 30 capacity |
| Sides | Facing ±90 degrees | 40 capacity |
| Round | All directions | 50 capacity |
| Invincibility | Space activates all-direction protection | 2 s active, 8 s cooldown from activation |

Each ordinary block costs 10 capacity; a shield with less than 10 cannot block. It regenerates 10/s after 3 s without a block. Bullet interception uses radius 7.5; contact protection uses the same directional coverage at the hull. Invincibility is a timed equipment skill, distinct from the existing permanent debug `invincible` toggle. Space activates both equipped skills when a custom build combines burst engine and invincibility shield. All equipment, animation, attack, stun and iframe timers advance only during gameplay; console/pause/augment selection stop them.

Hull art selects full, slight, damaged and very damaged at >75%, ≤75%, ≤50%, ≤25% health. The original player collision radius remains 4 world units. Equipment lives in Player/Bullet values and resets on both restart and new scene entry; no new singleton.

| Stat | Base | Source |
|---|---|---|
| Max health | 100 | (SA) |
| Damage per bullet | 7 to 12, random | (SA) |
| Attack cooldown | 0.5 s | (SA) |
| Move speed | 50 units/s | (SA) |
| Acceleration | 400 units/s² | (SA) |
| Stun after hit | 0.2 s | (SA) |
| Invincibility after stun | 0.8 s | (SA) |
| Bullet speed | 200 units/s | (SA) |
| Armor (damage reduction) | 0% | new |
| Magnet radius | 12 units | new, TUNE |
| Pickup radius | 4 units | new |
| Cargo capacity | 60 scrap | new, TUNE |

Damage taken = `max(1, round(incoming × (1 − armor)))`. Contact with a non-boss enemy also destroys that enemy (SA).

---

## Enemies

Display names are working names. All three keep their Space Ablaze movement; only the art changes for Low and Mid.

| | Low: Junk Swarmer | Mid: Rogue Satellite | High: Compactor | Debris |
|---|---|---|---|---|
| Class | `LowLevelEnemy` | `MidLevelEnemy` | `HighLevelEnemy` (new) | `Asteroid` |
| Behavior | Homes on the player (SA) | Circles and strafes, shoots when facing the player (SA) | Approach, wind up, charge, recover; 3-bullet spread after a charge | Drifts across, aimed loosely at the player (SA) |
| Health | 30 (SA) | 50 (SA) | 160 TUNE | 1 hit (SA) |
| Speed | 15 to 30 (SA) | 25 to 50 (SA) | Approach 12, charge 110 TUNE | 5 to 15 (SA) |
| Contact damage | 10 | 10 | 20 TUNE | 10 |
| Bullet damage | | 10 | 10 | |
| Bullet speed | | 120 to 150 (SA) | 110 | |
| Fire cooldown | | 0.5 to 1.25 s (SA) | After each charge | |
| Score | 10 (SA) | 50 (SA) | 120 | 5 (SA) |
| Scrap dropped | 2 | 5 | 12 | 1 |
| Wave budget cost | 1 | 3 | 6 | not budgeted |
| Sprite size (world units) | 15 (SA) | 15 (SA) | 22 | 15 / 25 / 30 (SA) |

### Compactor behavior (HighLevelEnemy)

| State | Behavior | Exit |
|---|---|---|
| Approach | Homes like the swarmer at 12 units/s | Player within 60 units |
| Windup | Stops, faces the player, flashes toxic green, 0.6 s | Timer; locks the charge direction |
| Charge | Straight line at 110 units/s for 0.45 s; ignores knockback | Timer; fires a 3-bullet spread (20° apart) toward the player |
| Recover | Drifts at 20% speed for 1.0 s; takes 25% extra damage | Timer, back to Approach |

The windup flash is the telegraph that makes the charge fair. It must be visible on the trailer.

---

## Bosses

Both bosses derive from `Boss`. Shared rules: 2 s intro (drifts in from off screen, invulnerable, HUD shows the name), no knockback, contact damage without being destroyed, bullets deal 15 damage, death triggers the explosion effect and a large scrap drop, the HUD boss bar shows health and phase markers.

### The Hoarder (Story wave 5)

A mass of fused junk that keeps pulling in debris.

| | Value |
|---|---|
| Health | 1800 TUNE |
| Size | 50 units |
| Movement | Drifts toward the player at 8 units/s, never closer than 30 units |
| Contact damage | 25 |
| Score | 2000 |
| Scrap | 120 |

| Phase | Health | Attacks |
|---|---|---|
| 1 | 100% to 50% | Ring of 16 bullets every 3.0 s (speed 70). Spawns 4 Junk Swarmers every 9 s |
| 2 | Below 50% | Ring every 2.0 s, each ring offset by 11.25° from the last. Spawns 2 Rogue Satellites every 12 s. Speed 12 |

### The Core (Story wave 10, final)

The largest piece of junk, holding the heart of the failed chemical.

| | Value |
|---|---|
| Health | 3200 TUNE |
| Size | 60 units |
| Movement | Slowly moves toward a point 40 units from the player at 10 units/s |
| Contact damage | 30 |
| Score | 5000 |

| Phase | Health | Attacks |
|---|---|---|
| 1 | 100% to 60% | Aimed triple shot every 1.6 s (15° spread, speed 90). Spiral burst every 7 s: 4 arms, one volley every 0.15 s for 3 s, rotating 12° per volley, speed 65 |
| 2 | 60% to 25% | Spiral every 5 s. Spawns 2 Compactors every 15 s |
| 3 | Below 25% | Enrage: spiral has 6 arms, aimed shots every 1.0 s, all bullet speeds ×1.2 |

In Story mode, The Core's death triggers `GAME_VICTORY`, then the ending cutscene. In Endless it is just a boss.

---

## Waves

### Spawning rules

- `WaveDirector` spends the wave's **budget** by picking an enemy type by weight. If the picked type costs more than the remaining budget, it spawns a Low instead.
- Every `spawnInterval` seconds it spawns a group of `groupMin` to `groupMax` enemies at random angles on a ring 150 units from the player (SA distance), as long as the number alive is below `aliveCap`.
- The wave is cleared when the budget is spent and no wave enemies are alive. Debris does not count.
- Enemy health is multiplied by the wave's `hpMul`.
- Boss waves spawn only the boss; the boss spawns its own adds.

### Story waves

| Wave | Kind | Budget | Weights Low / Mid / High | Interval | Group | Alive cap | HP mult | Debris |
|---|---|---|---|---|---|---|---|---|
| 1 | Normal (tutorial) | 14 | 100 / 0 / 0 | 1.2 s | 2 to 3 | 20 | 1.00 | Off |
| 2 | Normal | 22 | 100 / 0 / 0 | 1.0 s | 2 to 4 | 25 | 1.00 | On |
| 3 | Normal | 32 | 75 / 25 / 0 | 0.9 s | 2 to 4 | 30 | 1.05 | On |
| 4 | Normal | 42 | 65 / 35 / 0 | 0.8 s | 3 to 5 | 35 | 1.10 | On |
| 5 | **Boss: The Hoarder** | | | | | | 1.00 | Off |
| 6 | Normal | 56 | 55 / 30 / 15 | 0.8 s | 3 to 5 | 40 | 1.15 | On |
| 7 | Normal | 68 | 50 / 32 / 18 | 0.7 s | 3 to 6 | 45 | 1.20 | On |
| 8 | Normal | 82 | 45 / 33 / 22 | 0.7 s | 3 to 6 | 50 | 1.25 | On |
| 9 | Normal | 98 | 40 / 35 / 25 | 0.6 s | 4 to 6 | 55 | 1.30 | On |
| 10 | **Boss: The Core** (final) | | | | | | 1.00 | Off |

Expected Story length: about 12 to 16 minutes including dock visits. All values TUNE.

### Endless waves

Endless uses formulas instead of a table, with `w` = wave number starting at 1:

| Quantity | Formula |
|---|---|
| Budget | `14 + 10 × (w − 1)` |
| Weights | Wave 1-2: 100/0/0; then interpolate linearly from 75/25/0 at wave 3 to 35/35/30 at wave 12; constant after |
| Spawn interval | `max(0.35, 1.2 − 0.06 × (w − 1))` s |
| Group | `2 + w / 4` to `4 + w / 3` (integer division), capped at 10 |
| Alive cap | `min(90, 20 + 5 × w)` |
| HP multiplier | `1 + 0.08 × (w − 1)` |
| Bosses | Every 5th wave: The Hoarder on waves 5, 15, 25...; The Core on waves 10, 20, 30... |
| Boss HP multiplier | `1 + 0.35 × bossIndex`, where `bossIndex = w / 5 − 1` |

### Arena

- The dock sits at the world origin. The player spawns there.
- Soft boundary: 400 units from the dock. Beyond 360 units, the HUD shows "SIGNAL WEAK, RETURN TO ORBIT"; beyond 400, a force pushes the ship back.
- Keeps return trips short (under 10 seconds at base speed).

---

## Scrap and Economy

| Rule | Value |
|---|---|
| Drops | Enemy's scrap value, split into pickups of 10, 5 and 1 |
| Pickup lifetime | 20 s; blinks during the last 4 s |
| Magnet | Pickups inside the magnet radius fly to the ship |
| Cargo | Collected scrap goes to cargo; at capacity, pickups are not collected and the HUD shows "CARGO FULL" |
| Death | Cargo is lost |
| Deposit | Docking converts all cargo to credits, 1 scrap = 1 credit |
| Live pickup cap | 150; beyond it, new value merges into the nearest pickup |

Estimated Story income: about 900 to 1,100 credits by wave 10 (TUNE). That buys roughly 12 to 15 upgrade levels out of 35, so choices matter.

---

## Gear Upgrades (Dock Shop)

Bought with credits at the dock. Effects persist for the run. Max level 5 each.

| Gear | ID | Effect per level | Cost table |
|---|---|---|---|
| Blaster | `GEAR_BLASTER` | Damage ×(1 + 0.15 × level) | Premium |
| Fire Control | `GEAR_FIRE_CONTROL` | Attack cooldown ×0.9 per level | Premium |
| Hull Plating | `GEAR_HULL` | +20 max health per level (also heals 20) | Standard |
| Armor | `GEAR_ARMOR` | Damage taken −8% per level (40% at level 5) | Standard |
| Thrusters | `GEAR_THRUSTERS` | Move speed ×(1 + 0.08 × level) | Standard |
| Tractor Beam | `GEAR_TRACTOR` | Magnet radius ×(1 + 0.3 × level) | Standard |
| Cargo Hold | `GEAR_CARGO` | +30 cargo capacity per level | Standard |

| Cost table | L1 | L2 | L3 | L4 | L5 |
|---|---|---|---|---|---|
| Standard | 40 | 75 | 120 | 180 | 260 |
| Premium | 50 | 90 | 140 | 200 | 280 |

**Hull repair:** 1 credit per 2 missing health, rounded up, full repair only.

---

## Augments (after each wave)

Free. Pick 1 of 3 distinct cards, offered with `RunRng`. These are the 9 Space Ablaze augments with their current effects.

| ID | Title | Effect (SA) | Description fix |
|---|---|---|---|
| `AUG_RAPID_FIRE` | Rapid Fire | Attack cooldown ×0.9 | |
| `AUG_TRIGGER_HAPPY` | Trigger Happy | +1 shot per burst | Current text says "Boosts fire rate"; change to "Fires an extra shot\nin each burst" |
| `AUG_SCATTER_SHOT` | Scatter Shot | +1 bullet in the fan (30° apart) | |
| `AUG_SPEED_DEMON` | Speed Demon | Move speed ×1.1 | |
| `AUG_NANO_REPAIR` | Nano Repair | Heal 10, capped at 100 (SA) | Change to heal 25% of max health, since max health can now exceed 100 |
| `AUG_PIERCING_ROUNDS` | Piercing Rounds | +1 pierce | |
| `AUG_PHASE_SHIFT` | Phase Shift | Invincibility duration ×1.1 | |
| `AUG_GYRO_CONTROL` | Gyro Control | Turn speed ×1.1 | |
| `AUG_INERTIA_IMPACT` | Inertia Impact | +50 knockback | |

---

## Scoring

| Event | Points |
|---|---|
| Enemy kill | Enemy's score value |
| Debris destroyed | 5 |
| Scrap deposited at the dock | 2 per scrap |
| Wave cleared | 100 × wave number |
| Wave cleared without taking damage | +250 |
| Boss killed | Boss score value |
| Story victory | + `max(0, 6000 − 5 × seconds)` (rewards speed) |

Leaderboard order: Story by score, then lower time. Endless by score, then more waves.

---

## Tutorial (wave 1 only)

Prompts appear one at a time at the bottom center, each until its condition is met or 6 s pass:

1. "WASD TO MOVE" (until the player moves)
2. "AIM WITH THE MOUSE, HOLD LEFT CLICK TO SHOOT" (until 3 shots)
3. "PRESS E TO TOGGLE AUTO-FIRE" (6 s)
4. "COLLECT THE GOLD SCRAP" (when the first scrap drops, until one is collected)
5. "WAVE CLEAR: FOLLOW THE ARROW BACK TO THE DOCK" (return phase)

These replace the current WASD/E key animations (keep the key images if they fit).

---

## Fixed Seeds

| Mode | Seed |
|---|---|
| Story | 20261126 |
| Endless | 20261127 |

Changing a seed changes every wave; do it only before submission and record it.

---

## Initial `src/Balance.hpp`

Item 03 creates this file. After that, the header is the source of truth and this section is only a reference.

```cpp
#pragma once
#include <array>

namespace Balance {

// ---------- Player (SA = Space Ablaze value) ----------
inline constexpr int   PLAYER_MAX_HEALTH        = 100;    // SA
inline constexpr int   PLAYER_DAMAGE_MIN        = 7;      // SA
inline constexpr int   PLAYER_DAMAGE_MAX        = 12;     // SA
inline constexpr float PLAYER_ATTACK_COOLDOWN   = 0.5f;   // SA
inline constexpr float PLAYER_SPEED             = 50.0f;  // SA
inline constexpr float PLAYER_ACCELERATION      = 400.0f; // SA
inline constexpr float PLAYER_STUN_TIME         = 0.2f;   // SA
inline constexpr float PLAYER_IFRAME_TIME       = 0.8f;   // SA
inline constexpr float PLAYER_COLLISION_NUDGE   = 20.0f;  // SA
inline constexpr float PLAYER_BULLET_SPEED      = 200.0f; // SA
inline constexpr float PLAYER_MAGNET_RADIUS     = 12.0f;  // TUNE
inline constexpr float PLAYER_PICKUP_RADIUS     = 4.0f;
inline constexpr int   PLAYER_CARGO_CAPACITY    = 60;     // TUNE

// ---------- Enemies ----------
inline constexpr float ENEMY_SPRITE_SIZE = 15.0f;                                   // SA, low and mid
inline constexpr float LOW_SPEED_MIN = 15.0f, LOW_SPEED_MAX = 30.0f, LOW_TURN_SPEED = 5.0f;          // SA
inline constexpr float MID_SPEED_MIN = 25.0f, MID_SPEED_MAX = 50.0f;                                  // SA
inline constexpr float MID_TURN_MIN = 1.5f, MID_TURN_MAX = 2.5f;                                      // SA
inline constexpr float MID_FIRE_COOLDOWN_MIN = 0.5f, MID_FIRE_COOLDOWN_MAX = 1.25f;                   // SA
inline constexpr float MID_BULLET_SPEED_MIN = 120.0f, MID_BULLET_SPEED_MAX = 150.0f;                  // SA
inline constexpr float MID_FIRE_RANGE = 100.0f, MID_FACING_THRESHOLD = 1.85f;                         // SA
inline constexpr int   LOW_HEALTH = 30, LOW_CONTACT_DAMAGE = 10, LOW_SCORE = 10, LOW_SCRAP = 2, LOW_COST = 1;
inline constexpr int   MID_HEALTH = 50, MID_CONTACT_DAMAGE = 10, MID_SCORE = 50, MID_SCRAP = 5, MID_COST = 3;
inline constexpr int   MID_BULLET_DAMAGE = 10;
inline constexpr int   HIGH_HEALTH = 160, HIGH_CONTACT_DAMAGE = 20, HIGH_SCORE = 120, HIGH_SCRAP = 12, HIGH_COST = 6; // TUNE
inline constexpr int   HIGH_BULLET_DAMAGE = 10;
inline constexpr float HIGH_SPRITE_SIZE = 22.0f;
inline constexpr float HIGH_APPROACH_SPEED = 12.0f, HIGH_CHARGE_SPEED = 110.0f, HIGH_CHARGE_RANGE = 60.0f; // TUNE
inline constexpr float HIGH_WINDUP_TIME = 0.6f, HIGH_CHARGE_TIME = 0.45f, HIGH_RECOVER_TIME = 1.0f;       // TUNE
inline constexpr float HIGH_SPREAD_DEG = 20.0f, HIGH_BULLET_SPEED = 110.0f, HIGH_RECOVER_DAMAGE_TAKEN = 1.25f;
inline constexpr int   DEBRIS_SCORE = 5, DEBRIS_SCRAP = 1, DEBRIS_CONTACT_DAMAGE = 10;

// ---------- Bosses ----------
inline constexpr float BOSS_INTRO_TIME = 2.0f;
inline constexpr int   BOSS_BULLET_DAMAGE = 15;
inline constexpr int   HOARDER_HEALTH = 1800, HOARDER_CONTACT_DAMAGE = 25, HOARDER_SCORE = 2000, HOARDER_SCRAP = 120; // TUNE
inline constexpr float HOARDER_SIZE = 50.0f, HOARDER_SPEED = 8.0f, HOARDER_SPEED_P2 = 12.0f, HOARDER_MIN_DISTANCE = 30.0f;
inline constexpr float HOARDER_PHASE2_AT = 0.5f;
inline constexpr int   HOARDER_RING_BULLETS = 16;
inline constexpr float HOARDER_RING_INTERVAL = 3.0f, HOARDER_RING_INTERVAL_P2 = 2.0f, HOARDER_RING_SPEED = 70.0f;
inline constexpr float HOARDER_ADDS_INTERVAL = 9.0f, HOARDER_ADDS_INTERVAL_P2 = 12.0f;
inline constexpr int   CORE_HEALTH = 3200, CORE_CONTACT_DAMAGE = 30, CORE_SCORE = 5000;                     // TUNE
inline constexpr float CORE_SIZE = 60.0f, CORE_SPEED = 10.0f, CORE_HOVER_DISTANCE = 40.0f;
inline constexpr float CORE_PHASE2_AT = 0.6f, CORE_PHASE3_AT = 0.25f;
inline constexpr float CORE_AIMED_INTERVAL = 1.6f, CORE_AIMED_INTERVAL_P3 = 1.0f, CORE_AIMED_SPREAD_DEG = 15.0f, CORE_AIMED_SPEED = 90.0f;
inline constexpr float CORE_SPIRAL_INTERVAL = 7.0f, CORE_SPIRAL_INTERVAL_P2 = 5.0f, CORE_SPIRAL_DURATION = 3.0f;
inline constexpr float CORE_SPIRAL_VOLLEY_TIME = 0.15f, CORE_SPIRAL_STEP_DEG = 12.0f, CORE_SPIRAL_SPEED = 65.0f;
inline constexpr int   CORE_SPIRAL_ARMS = 4, CORE_SPIRAL_ARMS_P3 = 6;
inline constexpr float CORE_ADDS_INTERVAL = 15.0f, CORE_P3_SPEED_MULT = 1.2f;

// ---------- Waves ----------
enum BossKind { BOSS_NONE = 0, BOSS_HOARDER, BOSS_CORE };

struct WaveDef {
    int budget;
    int weightLow, weightMid, weightHigh;
    float spawnInterval;
    int groupMin, groupMax;
    int aliveCap;
    float hpMultiplier;
    bool debris;
    BossKind boss;
};

inline constexpr std::array<WaveDef, 10> STORY_WAVES = {{
    {14, 100,  0,  0, 1.2f, 2, 3, 20, 1.00f, false, BOSS_NONE},
    {22, 100,  0,  0, 1.0f, 2, 4, 25, 1.00f, true,  BOSS_NONE},
    {32,  75, 25,  0, 0.9f, 2, 4, 30, 1.05f, true,  BOSS_NONE},
    {42,  65, 35,  0, 0.8f, 3, 5, 35, 1.10f, true,  BOSS_NONE},
    { 0,   0,  0,  0, 0.0f, 0, 0,  0, 1.00f, false, BOSS_HOARDER},
    {56,  55, 30, 15, 0.8f, 3, 5, 40, 1.15f, true,  BOSS_NONE},
    {68,  50, 32, 18, 0.7f, 3, 6, 45, 1.20f, true,  BOSS_NONE},
    {82,  45, 33, 22, 0.7f, 3, 6, 50, 1.25f, true,  BOSS_NONE},
    {98,  40, 35, 25, 0.6f, 4, 6, 55, 1.30f, true,  BOSS_NONE},
    { 0,   0,  0,  0, 0.0f, 0, 0,  0, 1.00f, false, BOSS_CORE},
}};

inline constexpr float WAVE_BANNER_TIME   = 2.5f;
inline constexpr float SPAWN_RING_RADIUS  = 150.0f;  // SA
inline constexpr float ENDLESS_BOSS_HP_STEP = 0.35f;
inline constexpr unsigned int STORY_SEED   = 20261126u;
inline constexpr unsigned int ENDLESS_SEED = 20261127u;

// ---------- Arena and dock ----------
inline constexpr float ARENA_WARNING_RADIUS = 360.0f;
inline constexpr float ARENA_RADIUS         = 400.0f;
inline constexpr float ARENA_PUSHBACK       = 120.0f;
inline constexpr float DOCK_RADIUS          = 18.0f;

// ---------- Scrap and economy ----------
inline constexpr float SCRAP_LIFETIME       = 20.0f;
inline constexpr float SCRAP_BLINK_TIME     = 4.0f;
inline constexpr float SCRAP_MAGNET_SPEED   = 90.0f;
inline constexpr int   SCRAP_MAX_PICKUPS    = 150;
inline constexpr int   SCRAP_TO_CREDITS     = 1;
inline constexpr int   REPAIR_HP_PER_CREDIT = 2;

// ---------- Gear ----------
inline constexpr int GEAR_MAX_LEVEL = 5;
inline constexpr std::array<int, 5> COST_STANDARD = {40, 75, 120, 180, 260};   // TUNE
inline constexpr std::array<int, 5> COST_PREMIUM  = {50, 90, 140, 200, 280};   // TUNE
inline constexpr float GEAR_BLASTER_DAMAGE_PER_LEVEL = 0.15f;
inline constexpr float GEAR_FIRE_COOLDOWN_MULT       = 0.9f;
inline constexpr int   GEAR_HULL_HEALTH_PER_LEVEL    = 20;
inline constexpr float GEAR_ARMOR_PER_LEVEL          = 0.08f;
inline constexpr float GEAR_THRUSTER_PER_LEVEL       = 0.08f;
inline constexpr float GEAR_TRACTOR_PER_LEVEL        = 0.3f;
inline constexpr int   GEAR_CARGO_PER_LEVEL          = 30;

// ---------- Augments (SA values) ----------
inline constexpr float AUG_RAPID_FIRE_MULT   = 0.9f;
inline constexpr float AUG_SPEED_MULT        = 1.1f;
inline constexpr float AUG_NANO_REPAIR_FRACTION = 0.25f;
inline constexpr float AUG_IFRAME_MULT       = 1.1f;
inline constexpr float AUG_GYRO_MULT         = 1.1f;
inline constexpr float AUG_KNOCKBACK_ADD     = 50.0f;

// ---------- Scoring ----------
inline constexpr int SCORE_PER_SCRAP_DEPOSITED = 2;
inline constexpr int SCORE_WAVE_CLEAR_PER_WAVE = 100;
inline constexpr int SCORE_NO_DAMAGE_WAVE      = 250;
inline constexpr int SCORE_VICTORY_BASE        = 6000;
inline constexpr int SCORE_VICTORY_PER_SECOND  = 5;

} // namespace Balance
```
