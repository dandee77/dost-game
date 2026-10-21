# Mothership Weapon Tree

**21 October 2026. Confirmed acquisition direction plus proposed branch content.** Read the [review index](README.md). All new stats/prices below are mirrored from the pending-review ledger in [game design](../../context/game-design.md). No weapon, asset or class is implemented by this document.

## 1. Five tiers without an expanding content explosion

The owner's spoken tier counts were ambiguous. Proposed interpretation: **1 / 3 / 6 / 6 / 6 nodes** across T1-T5. That is 22 nodes including the free starter, but six end-family behaviors. T4 and T5 improve an existing specialization instead of introducing another doubling of choices. Exact family names remain descriptive placeholders; final-name work is deferred.

```text
T1 Simple Cannon
  T2 Machine Gun
    T3 Rotary Cannon -> T4 Rotary Cannon II -> T5 Rotary Cannon III
    T3 Focus Laser   -> T4 Focus Laser II   -> T5 Focus Laser III
  T2 Sniper
    T3 Rail Lance    -> T4 Rail Lance II    -> T5 Rail Lance III
    T3 Guided Missile -> T4 Guided Missile II -> T5 Guided Missile III
  T2 Shotgun
    T3 Flak Burst    -> T4 Flak Burst II    -> T5 Flak Burst III
    T3 Flamethrower  -> T4 Flamethrower II  -> T5 Flamethrower III
```

**Confirmed branch lock:** buy one T2 child of the starter and, later, one T3 child of that branch. Other siblings become unavailable for the rest of the run. T4/T5 follow the chosen specialization. No swapping owned weapons, refund, respec, branch merge or persistent unlock is proposed. A fresh run returns to the starter.

All cannon tier purchases happen at the mothership. A new run starts with the normal cannon before any purchase. The owner did not ask to change the selected ship's appearance or create a playable character-selection roster.

## 2. Branch identities and initial comparison

| Tier-two path | Intended role | Benefit | Cost/tradeoff |
|---|---|---|---|
| Machine Gun | Sustained mid-range pressure | Small individual bullets, rapid attack cadence, reliable crowd damage | Lower per-bullet damage; limited reach relative to Sniper |
| Sniper | Long-range aligned targets | Fast projectile, high per-hit damage, built-in penetration and distance-based damage bonus | Slow firing; weak recovery when surrounded; requires firing lanes |
| Shotgun | Close-range interception | Several pellets in a forward fan; strong when multiple pellets connect | Short travel range; dispersed pellets lose effective damage at distance |

Proposed baseline before augment modifiers:

| Profile | Damage | Trigger rate | Range / projectile speed | Built-in pattern |
|---|---|---|---|---|
| T1 Simple Cannon | Preserve existing 7-12 damage | 2 shots/s | Proposed finite range 100 / preserve speed 200 | One ordinary shot |
| T2 Machine Gun | 4 per bullet | 8 shots/s | 90 / 240 | One small shot per trigger |
| T2 Sniper | 24 base per target | 1 shot/s | 180 / 480 | Up to three distinct target hits; distance bonus below |
| T2 Shotgun | 6 per pellet | 1 volley/s | 60 / 180 | Six pellets over a proposed 40-degree fan |

All ranges/speeds are world units and world units/s. “Small bullets” refers to presentation/collision profile; final radius/art sizing must be authored before code. Finite range is projectile travel length, not a claim that everything currently despawns this way. Current prototype root values remain the implementation baseline.

Nominal single-target damage/s before other effects is 19 average for T1, 32 for Machine Gun, 24-42 for Sniper depending on range, and at most 36 for Shotgun when every pellet hits. These are comparison examples, not encounter balance certification. Penetration and splash change total crowd damage.

## 3. Six proposed specializations

| Parent | T3 family | Behavior and identity | T4 refinement | T5 refinement |
|---|---|---|---|---|
| Machine Gun | Rotary Cannon | Sustained rapid physical fire; strongest when a firing lane stays open | Improve stable sustained output | Final sustained-output package; no new input or branch |
| Machine Gun | Focus Laser | Sustained narrow mid-range beam; rewards keeping aim on a target | Improve authored beam output/uptime | Final beam refinement; not unlimited screen-wide reach |
| Sniper | Rail Lance | Very fast straight shot with deeper penetration; retains distance bonus | Improve penetration/long-range profile | Final precision profile with bounded hits and no repeat hit on one enemy |
| Sniper | Guided Missile | Slower cadence guided explosive projectile; emphasizes distant priority targets | Improve authored guidance/splash profile | Final missile refinement with bounded blast/effect load |
| Shotgun | Flak Burst | Close-range pellet volley with a bounded airburst at its designed endpoint | Improve close-area coverage | Final close-interception profile; no distant sniper damage |
| Shotgun | Flamethrower | Short cone/stream of damaging exhaust; little long-range capability | Improve short-range stream profile | Final short-range area profile; no permanent arena-covering trail |

Guided Missile replaces the sniper bullet model: it **does not inherit the Rail Lance distance multiplier or built-in penetration**. Flak/rocket splash and Flamethrower/laser damage need their own per-target timing rules. These families are alternatives, not an instruction to combine every strength in one weapon.

Flamethrower is placed under Shotgun to preserve the short-range identity even though the owner also mentioned it near Machine Gun. That placement is a proposal for later review. The primary Focus Laser and automatic Plasma Beam are different systems; a purchased cannon must not silently grant the Plasma Beam ability.

T3-T5 exact damage, attack rate, range, projectile/effect counts and area caps remain **UPG-REVIEW-08**, to author after family approval. Do not mark the weapon specification implementation-ready before those tables exist. Reuse prototype Cannon/Rockets/Laser/Heavy behavior where suitable after consulting the class registry; ownership/reuse does not prove all six families are already implemented.

## 4. Distance damage and penetration

Proposed Sniper/Rail Lance formula before ordinary primary-attack augments:

`damage(distance) = baseDamage * [1 + 0.75 * clamp((distance - 80) / 80, 0, 1)]`

Distance is the projectile's accumulated travel from its firing point at that target contact, not the player's current distance after moving. Hits through 80 units get 1x, at 120 units 1.375x and from 160 onward 1.75x, up to the projectile's finite range. A T2 24-damage shot therefore deals 24, 33 and 42 in those examples before other modifiers/rounding.

Each target is hit once by a given projectile. T2 has three total target hits, not three extra hits after the first. Existing Armor Piercing cards can add supported target hits; their interaction must remain explicit. No indefinite hit loop, extra damage just for being off-screen or unlimited multiplier beyond the range is permitted. Partial/blocked trajectories use actual travel; target movement does not rewind it.

## 5. Purchase, application and lifecycle

| Tier reached | Proposed incremental cost | Cumulative path cost |
|---|---:|---:|
| T1 | Free starter | 0 |
| T2 | 150 Trade Scrap | 150 |
| T3 | 300 Trade Scrap | 450 |
| T4 | 600 Trade Scrap | 1050 |
| T5 | 1000 Trade Scrap | 2050 |

No level gate, special-material recipe or boss unlock is added in this proposal. The tree edge and wallet are the prerequisites. Each transaction grants only its immediate child; purchasing multiple consecutive tiers requires separate deliberate confirmations and exact quoted costs.

Show the current node, next choices, role/range, exact price, wallet afterward and branch-lock warning. Revalidate parent/tier, branch, location, funds and transaction state at commit. Debit and equip once together. A stale/double click cannot skip a tier or spend twice.

Changing cannon never heals hull/shield, charges Return Home, refreshes Blink or changes level/ability ownership. Live projectiles/effects keep their firing profile and modifiers. Retire the old primary firing loop at the safe hub without duplicating a beam/burst on Resume. Preserve the remaining primary cooldown; the new profile applies on the next legal attack, with no free bonus shot.

Weapon branch/tier survives hub visits, pause and same-expedition Resume. Death, quit or New Run resets it. Return Home does not reroll or reset branch choices.

## 6. Field cards versus cannon tiers

Proposed interpretation to confirm: field cards still improve ship attributes and primary-attack modifiers, including damage, speed, pellets and penetration. They never change the selected cannon model or buy a tier. This preserves field progression while cannon evolution requires a mothership visit.

Keep the existing compatible augment effects. Pattern cards on a beam/stream require an authored auxiliary-shot mapping rather than copying full beam damage into every direction. Extra pellets, directions, burst counts and penetration stay discrete card effects; quarter-strength purchases do not create fractional bullets. Guided explosives must detonate once and count each affected target under their damage contract. Final family/augment compatibility is part of UPG-REVIEW-02/08.
