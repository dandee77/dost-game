# Game Design

## 21 October material and campaign alignment (proposed; not implemented)

[Scrap types](../todo/03-economy/scrap-types.md) classifies recoveries into **six** families: Recovered Alloys, Electronic Components, Polymer Stock, Power Modules, Structural Composites and Purification Media. A family is fixed by content profile, not a random price multiplier. Existing trade ranges, fixed salvage, debris yields and prices below are unchanged. Single-family merged pickups retain the label; different families display Mixed Salvage with conserved trade/salvage totals. There are no per-family wallets, recipes, conversion rates or statistics in the selected minimum scope.

The ten-wave Campaign proposal now represents two source sectors, with guardians at five and ten. Guardian death stops that source's future emissions/adds; remaining required hostiles still block completion. No global HP reduction, reward reroll or purification-item requirement is introduced. Source shutdown flags persist through hub visits and reset with a fresh run. Same-step player death takes priority over victory. See [world and campaign](../todo/01-story/world-and-campaign.md).

Remaining numerical design gaps are explicit in [decisions and gaps](../todo/00-planning/decisions-and-gaps.md): complete spawn budgets, boss stats/attacks, auto-target ranges, arena dimensions, scoring weights and high-rank/performance limits. Existing prototype values are not automatically approved answers for those new systems. Adopt the proposed card distribution/targeting policy there before adding corresponding numeric tables here.

## 20 October proposed tuning ledger (not implemented or playtested)

The new product contract is [todo/02-gameplay/gameplay.md](../todo/02-gameplay/gameplay.md). The owner confirmed the hub/field progression/return direction, then required **paid base health repair** and **random trade scrap by enemy**, delegating shop inventory/prices to the author. The economy values below are selected design defaults, not playtested balance. The owner's 100/1,000 progression examples remain provisional. This ledger supersedes older cargo/credits, free-repair, one-value reward, wave-card and P6 base-30 targets.

### Progression and Return Home

| Quantity | Proposed value/formula |
|---|---|
| Starting player level/progress | 1 / 0 |
| First field-upgrade requirement | 100 scrap |
| Difficulty growth g | Easy 0.05; Hard 0.10; Impossible 0.15 |
| Requirement at player level L | round half up of `100 * (1 + g)^(L - 1)` |
| Return maximum | `1000 + modeGrowth * (L - 1)` |
| Return availability | `ceil(maximum / 2)` and online shield with positive points |
| Return growth per player level | Swarm 50; Survival 75; Boss 100; Chaos 125; Campaign 100 |
| Charge per collected salvage point | 1, capped at current maximum; independent of random trade value |
| Successful manual return | Drain current charge to zero; no wallet/XP cost |
| Level-up capacity adjustment | Preserve absolute charge; recalculate maximum/threshold |
| Low/mid salvage progress | Fixed 2 / 5; currency rolls listed separately below |
| Owned standard rank r -> r+1 price | `100 + 50*r`; rank 1 -> 2 costs 150 |
| Owned rare rank r -> r+1 price | `200 + 75*r`; rank 1 -> 2 costs 275 |
| Rare acquisition prices | Singularity 240; Space Collapse 280; Nuclear Missile 320; Armageddon 400 |
| Rare stock | Three distinct unowned entries from those four, fixed for the run; fewer if insufficient eligible entries |
| Hull repair | `ceil(missingHP / 5)` trade scrap; restores quoted hull after 3 uninterrupted service seconds |
| Affordable hull patch | Spend up to wallet/needed repair cost; 5 HP per paid scrap, clamped; minimum price 1 |
| Shield recharge | `ceil(missingShield / 5)` trade scrap; restores shield/reboot after 3 service seconds |
| Full service | Sum of hull + shield quotes, same 3 seconds; no charge for already-full components |

Each pickup stores `tradeValue` and `salvageValue`. Wallet and totalCollected increase by trade value; levelProgress and returnCharge increase by salvage value. Currency luck affects buying power without changing progression pace. Spending never subtracts XP/charge or lifetime trade collected. No cargo cap, credits conversion or deposit multiplier.

### Selected enemy currency ranges

All ranges are uniform inclusive integers; one stored roll per enemy from a separate seeded loot RNG. Values do not multiply with difficulty or player level.

| Tier | Trade minimum | Trade maximum | Expected trade | Fixed salvage |
|---|---:|---:|---:|---:|
| Low/basic | 1 | 3 | 2 | 2 |
| Mid/ranged | 3 | 7 | 5 | 5 |
| High/heavy | 8 | 12 | 10 | 10 |
| Elite, only if future content exists | 15 | 25 | 20 | 20 |
| Standard boss | 120 | 180 | 150 | 100 |
| Campaign final boss | 200 | 300 | 250 | 200 |

Assign once at spawn, store across suspension, materialize only on reward-eligible death, credit only on collection. No currency reroll at kill/collection/merge. Summing/splitting preserves both fields. Existing ordinary debris keeps fixed per-kind yields for both fields. Barricades, cleanup/despawn and Space Collapse yield zero for both; Singularity follows normal rules. These reward tiers do not authorize new enemy/boss content.

Paid hull service clears harmful player statuses only on completion of actual healing; shield-only service does not. Debit and service effects commit atomically after the 3-second duration, never on panel opening. Cancel means no cost and no healing. Pause freezes service. Zero wallet permits launch/resume but no free repair. Example: missing 37 HP costs 8; wallet 3 buys 15 HP for 3. Fractional positive shield deficits round up to at least 1 scrap.

The shop sells all eligible owned standard ranks, owned rare ranks and the four rare acquisitions above. No standard first acquisition, weapon shop, consumable, reroll or permanent unlock is added. Paid Reinforced Hull grants max HP only; the field card retains its max/current-HP increase. Paid shield capacity never refills current points. Pass acquisition source through the same rank API and display the real resulting effect.

### Level and return examples

| Player level | Easy requirement | Hard requirement | Impossible requirement |
|---|---:|---:|---:|
| 1 | 100 | 100 | 100 |
| 2 | 105 | 110 | 115 |
| 5 | 122 | 146 | 175 |
| 10 | 155 | 236 | 352 |

Return cells below show **maximum / minimum usable charge**:

| Level | Swarm | Survival | Boss | Chaos | Campaign |
|---|---|---|---|---|---|
| 1 | 1000 / 500 | 1000 / 500 | 1000 / 500 | 1000 / 500 | 1000 / 500 |
| 2 | 1050 / 525 | 1075 / 538 | 1100 / 550 | 1125 / 563 | 1100 / 550 |
| 5 | 1200 / 600 | 1300 / 650 | 1400 / 700 | 1500 / 750 | 1400 / 700 |
| 10 | 1450 / 725 | 1675 / 838 | 1900 / 950 | 2125 / 1063 | 1900 / 950 |

The return target moves as levels rise. At 2 salvage per basic enemy, the initial 500 threshold requires 250 collected kills before growth. Those kills yield expected trade 500, possible 250-750. Measure actual first-return time, repair burden and purchases per visit; do not promise these values are balanced.

### Retained shield target and new utility gate

Deflector: rank-1 maximum 20, +5 per rank; online regeneration 2 points/s, +10% of base per rank. A hit against positive points is entirely absorbed even if it breaks the shield. Offline delay 10 s, minus 1 s/rank to a 5 s floor; restart at 50%, then restore the remaining half over 3 simulation seconds. No concurrent normal regeneration during that special restoration phase. Zero/offline shield blocks return; positive online shield permits it.

Proposed starter Deflector rank 1 guarantees the utility has a normal-play shield. Rank increases preserve current points and elapsed cooldown debt; no free revival. Paid shield recharge/full service restores shield and clears reboot; hull-only repair does not. Hull has no passive field regeneration; Reinforced Hull's max/current-HP exception applies to free field cards only.

Replace Nano Repair with Shield Detonation: 50 damage, radius 35, 18 s internal cooldown; +25% damage/rank, +10% radius/rank through rank 5, -10% cooldown with positive high-rank continuation. Trigger once on actual break, not repair/reset/upgrade. Combat catalog remains 32; Return Home is separate.

### Modes, pickups and scaling

| Quantity | Proposed initial tuning |
|---|---|
| Survival duration | 300 combat seconds |
| Campaign outline | 10 waves; boss content slots at 5 and 10; final boss ends campaign |
| Chaos boss schedule | First at 180 combat seconds, subsequent at least 180 seconds after previous boss death, one living boss maximum |
| Swarm | Endless normal-wave schedule; no bosses by default |
| Boss mode | One designated boss encounter; roster/yield/content pending owner |
| Enemy HP difficulty baseline | Easy 1.00, Hard 1.25, Impossible 1.50 |
| Spawn HP | base HP * encounter factor * difficulty baseline * `(1+g)^(L-1)`, round half up, min 1 |
| Effective HP scaling safety bound | Proposed 50x total; apply each factor once |
| Enemy damage baseline multiplier | 1.0 for all difficulties |
| Ordinary enemy pickup cap | 500, no expiry, value-preserving local merging |
| Existing debris orb budget | Preserve 150 and accepted visual/homing behavior |
| Magnet | 60-unit base radius, existing 15 s cooldown / 5 s duration; pull faster than upgraded ship |
| Magnet speed relation | `max(basePullSpeed, currentShipTopSpeed * 1.25)` |

Enemy HP is snapshotted at spawn, not recalculated on player level-up. Shield/skill rank and player level are separate concepts. All numbers become Balance entries marked TUNE during implementation; none are changed in src by this documentation session. Preserve existing ability growth formulas in skills-commands.md except the explicitly revised shield, activation, magnet and Nano Repair replacement contracts.

The single source for gameplay rules and numbers. Code reads numbers from `src/Balance.hpp`; this file explains them. When a number changes, change both in the same commit. Values marked **TUNE** are first guesses for the item-28 balance pass.

Values marked **(SA)** are the current Space Ablaze values, kept so the game still feels like Space Ablaze.

---

## Design Pillars

**18 October P5 repeat-pick extension:** Ability cards join the existing 20-second picker with no gameplay level cap. First pick learns; repeats upgrade. This user request supersedes the earlier acquisition deferral only for the existing picker. All per-ability growth and drone health/contact numbers are documented in `skills-commands.md` under Repeat-pick ability upgrades and centralized in `Balance.hpp`. Physical size reaches its maximum at level 5; count and other stat growth continue. Recharge follows the original additive rule through level 5, then positive diminishing returns. Casts retain their activation stats. Space Collapse gains one erasure zone per level without scrap, and Combat Drone gains one drone per level with real health and stronger shots. No wave/shop system is added.

**17 October P5 skills override:** The user's supplied `skills-context.md` supersedes the old nine-augment names below for this prototype. There are now 14 typed augments and 18 abilities. Provisional numbers, activation rules, and resolved assumptions are documented in `skills-commands.md`; executable values live in `Balance.hpp`. Rapid Fire adds burst shots; Overclocked Chambers reduces cooldown. Nano Repair heals 25% of current max hull; Reinforced Hull increases max/current hull. Singularity yields scrap; Space Collapse does not. No acquisition/shop work is included.

1. **Readable chaos.** Many enemies, but the player always sees what hurts: toxic green is danger, gold is reward, sky blue is you.
2. **Every kill feeds the loop.** Junk becomes scrap, scrap becomes gear, gear clears more junk.
3. **Fair competition.** The same seed gives every player the same waves; score rewards skill, not luck.
4. **A judge sees everything in 5 minutes.** Wave 1 teaches, the first dock visit happens within 2 minutes, a boss is reachable through Endless or by skilled play.

---

## Player

### P3 barricade event (14 October, user request)

Once per run at 120 seconds of active gameplay, 64 durable event enemies surround the player's current position. The center stays fixed. Existing augment selection at 2:00 pauses play; the event starts when play resumes. Ordinary enemy spawning and combat continue. `spawn barricade event` starts the same event immediately for testing; an active event cannot stack. At the population cap, creation waits until all 64 slots are available.

Prototype TUNE values in Balance: 120 HP per segment; radius shrinks continuously from 130 to 45 world units over 30 simulation seconds; random small/medium/large segment collision radii 3.75/6.25/7.5 with matching padded draw sizes 15/25/30. The shrink rate is (130 - 45) / 30 = 2.833 units/s, reaching the original compact radius exactly at timeout. The whole ring orbits its fixed center at 4 degrees/s; each asteroid receives a random initial rotation and its own constant visual spin of 5-240 degrees/s at spawn. Destroyed gaps orbit with the formation. With the player's existing radius 4, intact neighboring segments block passage, and destroyed sections create real openings. With 64 segments compressed to radius 45, a single missing segment can be too narrow for the ship; the required gap depends on neighboring sizes; clearing five adjacent segments guarantees a traversable late-event gap even between the largest rocks. Contact deals the existing 10 damage only when vulnerable, respects shields/debug invincibility, and physically blocks during stun/iframes too. Bounce restitution is 0.2. Segments ignore knockback and crowd separation; other enemies may overlap them freely. Each destroyed segment uses the existing debris reward (5 score) and normal kill count.

At 30 seconds, survivors release containment and stop orbiting and scatter along their release headings at 55 units/s for four seconds, then despawn without rewards. Early escape requires distance greater than the current ring radius plus 90 units AND the entire ring outside the camera viewport. Killing every segment also ends the event. Smooth zoom targets the original 13 during containment and the normal 20 after escape/scatter/death; exponential response is 2.5/s. All event clocks and zoom freeze during pause, console capture and augment selection. Restart clears the event and rearms its automatic trigger. No equipment access/progression conditions are introduced.

### P2 low-enemy crowd motion (14 October, user request)

Living low-level enemies softly separate after their normal chase movement. Body radius is 1.5 times the combat hitbox radius (about 6.43 units), with response 12/s, maximum push speed 60 units/s, and a 0.05 s maximum correction step after a stall. A pair-symmetric side-step coefficient of 0.25 lets collinear queues widen rather than remain a single-file train. All values are prototype TUNE constants in Balance. This does not alter combat hitboxes or apply damage. Extremely crowded groups may remain compressed while settling; this is soft separation, not rigid-body physics.

Mid-level enemies retain their original flight/steering and can overlap all enemies. They are neither pushed nor treated as separation obstacles, and their sprites/destruction draw above low enemies. No new access conditions or progression mechanics are added.

Debug crowd spawning: `spawn lowlevel enemy <quantity>` accepts 1–10,000 and adds up to the remaining capacity of the existing 10,000-enemy limit. Enemies appear evenly around the existing 150-unit spawn ring and use ordinary low-enemy stats/combat. These unchanged values are now `Balance::ENEMY_LIMIT` and `Balance::ENEMY_SPAWN_RADIUS`; normal spawns also enforce the cap on each insertion.

### P1 equipment prototypes (14 October, user request)

These are debug-selectable prototypes, with no acquisition conditions or progression integration. New runs use the original ship, original bullet and base movement with no shield. `player default build` restores this original loadout; `player gunner build` selects the newly added modular cannon/base-engine/no-shield loadout. Every build preset is shield-free; shields are selected separately with `player shield ...` for testing, with future skill integration deferred. All values are in `Balance.hpp` and are TUNE. Switching equipment preserves health, score and earned augments; presets turn auto-fire off. Projectiles already in flight keep their original weapon, damage and piercing count. Beam/burst state and relevant cooldowns reset when replacing their equipment. Explicit shield selection refills the selected shield; presets clear shield charge and active guard/recharge timers.

15 October feedback pass is cosmetic only: projectile spawn shows a brief charge ring, the existing projectile art remains the moving core with a pulsing halo and trail, contact produces a short burst/SFX, targets tint briefly, and bounded particles provide aftermath. It does not add firing latency or change any table value below.

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

**15 October debris prototype (explicit user request):** shootable floating junk is `Debris`, and harvested fragments are `ScrapPickup`. Harvested scrap accumulates without a cargo limit for now, as confirmed by the user; it is run-local and lost on death/restart. This prototype does not provide credits, deposits, upgrades, or normal-enemy drops. The planned cargo/dock rules below remain future work.

Each debris kind has a unique eight-frame destruction at 0.075 s/frame. Frame eight is blank; at 0.525 s its own saved final-fleck positions become glow pickups. Visual counts: clump 4, pipe 3, wing 10, canister 5, dish 5, coil 4, tank 11, thruster 7, beam 11, hull 15. Small clump/pipe/canister/coil use 1.25-unit orbs, medium dish/thruster 1.8, large wing/tank/beam/hull 2.5. Total variant scrap yields are unchanged and divided exactly among that variant's particles. Orbs hold 0.05 s, then home at 150 units/s; pickup radius 2, lifetime 20 s, cap 150 with overflow merging. Only player-destroyed ordinary debris is harvestable. Barricade asteroids play the original seven-frame breakup without collectible particles or scrap reward. Pause/console/augment freeze the entire lifecycle; environmental breakup and despawn award nothing.

Fixed variant values (TUNE; never randomized):

| Variant | Collision radius | Padded draw size | Harvest value |
|---|---:|---:|---:|
| Scrap clump | 3.75 | 20 | 3 |
| Broken pipe | 3 | 20 | 2 |
| Satellite wing | 8 | 48 | 8 |
| Dented canister | 3.3 | 20 | 2 |
| Antenna dish | 5.7 | 34 | 5 |
| Cable coil | 3 | 18 | 2 |
| Pressure tank | 6.8 | 38 | 6 |
| Thruster bell | 5 | 30 | 4 |
| Broken truss | 6 | 38 | 3 |
| Hull panel | 6 | 36 | 5 |

All source frames are 96 x 96 with at most a 36-pixel body, so visible width/height includes transparent padding. Existing circular collision predicates are retained. Debris movement uses speed 5-15 units/s and rotation 5-240 degrees/s; continuous spawns retain the 1.5-to-0.25 s ramp over 600 s, 1-3 objects per batch, 150-unit spawn/despawn distance. Variant selection replaces random scale. Debug gallery radius: 60 units.

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

**Historical plan, superseded:** the seven gear lines and credit prices below are not the current shop specification. Use the 20 October ledger above and TODO section 9 for skill purchases and paid hull/shield services.

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
