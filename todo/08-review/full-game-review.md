# Full game logic and statistics review

**Later revision:** Read [balance implementation and context review](balance-and-context-review.md) first. Its implemented population/HP/loot/XP changes supersede the corresponding snapshot figures below; unchanged weapon/ability tables retain their original draft/code labels. The new review also lists unfinished context and the small set of decisions needing owner confirmation.

**23 October 2026. Review snapshot prepared for the owner.** This document consolidates the game design and inspected prototype source. It does not implement new features or certify balance. Later accepted decisions belong in the authority documents, not only here.

**Status key:** **Selected** = owner-approved design; **Draft** = proposed tuning or integration; **Code** = inspected current implementation; **Open** = no final rule/data. Historical retired systems are identified explicitly. “Final weapon” means T5; there is no finite final player build while ability ranks remain uncapped.

## Review map

1. [Core logic needing attention](#1-core-logic-needing-attention)
2. [Run flow and modes](#2-run-flow-and-modes)
3. [Starting player and shields](#3-starting-player-and-shields)
4. [All 26 weapon nodes and signatures](#4-all-26-weapon-nodes-and-signatures)
5. [Attributes, cards and high-build endpoints](#5-attributes-cards-and-high-build-endpoints)
6. [All abilities and rank calculations](#6-all-abilities-and-rank-calculations)
7. [Enemies, damage and encounter scaling](#7-enemies-damage-and-encounter-scaling)
8. [XP, levels and return energy](#8-xp-levels-and-return-energy)
9. [Economy, shop, repair and batteries](#9-economy-shop-repair-and-batteries)
10. [Drops, debris, collection and Luck](#10-drops-debris-collection-and-luck)
11. [Rarity and acquisition](#11-rarity-and-acquisition)
12. [Interactions, damage, scoring and reset rules](#12-interactions-damage-scoring-and-reset-rules)
13. [Complete unresolved data checklist](#13-complete-unresolved-data-checklist)
14. [Source references and verification limits](#14-source-references-and-verification-limits)
15. [Historical wave tables for comparison only](#15-historical-wave-tables-for-comparison-only)

## 1. Core logic needing attention

These are review findings and proposed priorities, not silently adopted balance changes.

| ID | Priority | Finding and consequence | Suggested review/fix |
|---|---|---|---|
| R01 | Critical | Current code starts without a shield; target return requires positive online shield. Equipment shields, hit-count Deflector and proposed point-based Deflector are separate systems. | Adopt one authoritative normal-play shield and starter grant before connecting return, batteries or shield cards. |
| R02 | Critical | New economy, five modes, weapon tree, hub/field portals and batteries are design, not implemented runtime behavior. Current cards arrive every 20 seconds. | Implement the adopted contracts in T01–T10 dependency order; do not assume writing numbers made them playable. |
| R03 | Critical | Player-level XP growth also drives enemy HP exponentially. At 16,000 salvage, basic HP is about 270/595/1,120 across Easy/Hard/Impossible before encounter factors. | Tune HP curves against actual build DPS and target kill times. Review whether all level, encounter and difficulty multipliers should compound. |
| R04 | High | Return threshold rises while energy is being collected. Easy levels faster and can require MORE kills for first return. | Decouple return-cap growth from fast leveling, or adopt a different controlled growth policy. Current rule remains pending tuning. |
| R05 | Critical | Boss mode may have one boss and no sufficient pre-kill salvage. A 500+ energy requirement may make its return portal inaccessible throughout the fight. | Specify energy availability for each encounter; do not promise a reachable return loop without that content. |
| R06 | High | 16,000 weapon cost requires 10.67–13.33 NET scrap/s for T5 at 20–25 minutes. Repairs, attributes, skills and batteries increase gross income needed. | Author reward/spawn schedules and measure pickup collection. Equal prices alone do not meet the pacing target. |
| R07 | Critical | Burst/scatter/pierce/side/rear cards have no complete mapping to 26 different projectile, beam, chain, cone and explosive weapons. | Approve a compatibility matrix; no offered card should silently give no benefit or multiply damage unintentionally. |
| R08 | High | T5 paper solo DPS 95–104 excludes misses, range, crowd coverage and cards. With capped scalar cards/shop increments, ordinary primary components can gain about 15.73x expected DPS before discrete patterns. | Compare whole builds, crowd clear, survivability and encounter access, not only unmodified solo DPS. |
| R09 | Critical | Uncapped ability ranks increase damage, duration and quantities. Drone count × drone damage grows roughly quadratically; cooldowns can approach zero. | Adopt effect/target/count budgets and numerical rules that preserve earned outcomes; playtest high ranks. |
| R10 | High | Proposed shield absorbs an entire hit even if only 1 point remains. Regeneration can therefore prevent arbitrarily large hull hits; hit cadence and break rules determine its value. | Explicitly choose full-hit absorption versus overflow-to-hull and whether online shield regeneration has a hit delay. |
| R11 | High | Current skill duration may exceed cooldown at high ranks, and cooldown starts on activation. Persistent conversion changes uptime and renewal rules. | Specify per-skill overlap/refresh behavior; avoid free replacement, duplicated companions or damage loss. |
| R12 | High | Nuclear Missile instantly kills ordinary enemies in the prototype; Space Collapse erases with zero drops. Those behaviors bypass HP scaling and can respectively dominate or starve economy. | Review exemptions, boss treatment, reward tradeoffs and limits before balancing primary weapon routes. |
| R13 | High | Three of four special acquisitions are fixed shop stock; special ranks and field rarity are separate. A desired special may never be stocked that run. | Decide whether fixed randomness fits “play what you want”; show eligible stock clearly. |
| R14 | High | Return-to-field protection ends on firing, but primary auto-fire and autonomous ability attacks have unresolved ordering. | Define the 2-second protection interaction; owner has not answered the auto-fire question. |
| R15 | Critical | Bosses, mode spawn tables, arena geometry and new scoring are incomplete. Old boss/wave/credit tables still exist as historical text. | Supply final content and mark/archive superseded sections; do not treat old tables as adopted current rules. |
| R16 | High | Prototype common enemy spawning reaches a theoretical mean 80 spawns/s near 245 seconds, subject to frame/update/population limits. | Replace with mode/difficulty schedules and measured population/CPU budgets. |
| R17 | High | Currency is random, but salvage/XP/energy is fixed. Some current kill paths only have minimal drops, and reward exclusions differ. | Route every legitimate death through one reward decision, preserving both values and cause. |
| R18 | Medium | Starter shield is proposed at 20, while examples used 100/500. The battery price reference must use actual starting normal capacity. | Select starter stats explicitly; examples are not automatic stat changes. |
| R19 | Medium | Paid max-hull/shield upgrades preserve current points; free Hull cards grant health. Re-entry protection, shield reboot and purchases must not accidentally refill anything. | Enforce source-aware gains, atomic payments, stable cooldowns and exact previews. |
| R20 | Medium | Names/controls in some older paragraphs still mention manual Q, paid shield service, cargo, credits and wave cards. | Reconcile current-facing documentation before implementation; retain historical evidence as historical. |

## 2. Run flow and modes

**Selected direction:** Start Game -> difficulty -> safe ship-based colony hub -> choose a mode portal -> launch. Field scrap grants levels/cards. Return portals take the ship to the hub for purchases/repairs. **Return to field** means leaving the hub to continue the same suspended fight; it is different from unpausing.

| Mode | Objective | Completion | Timing and content status |
|---|---|---|---|
| Swarm | Endless normal enemy crowds | Death or voluntary retirement | No bosses; T5 purchase target 20–25 combat minutes selected; exact spawn schedule open |
| Survival | Stay alive | 300 combat seconds or death | Five minutes; shared prices and lower-tier end build selected |
| Boss | Defeat one designated boss and required adds | Required encounter defeated or death | Actual boss and access to return energy open |
| Chaos | Endless crowds plus bosses | Death or retirement | Draft first boss at 180 seconds, next at least 180 after previous death; one living boss maximum |
| Campaign | Clear the source sectors | Final required encounter defeated or death | Draft 10 waves with source guardians at 5 and 10; identities/attacks pending |

Hub, pause, console and mandatory cards freeze combat clocks. Hub travel preserves enemies, boss HP/phases, pickup values, build and source shutdown state. Switching modes/new run resets the expedition under the proposed continuity contract. No persistent wallet/build progression across death/restart/application exit is selected. Same-frame player death taking priority over victory is a proposed outcome rule, not a tested current mode behavior.

Return portals: Easy 3, Hard 2, Impossible 1 across all modes; random legal positions, allowed to be far away. Nearby pointer begins around one visible screen; exact world-space measurement open. Press F while inside, alive, shield online/positive, energy at least half current capacity, with no mandatory modal pending. Failed travel spends nothing. Successful travel retains the draft drain-all-current-energy rule. Retire the whole set; generate new locations after returning to field and reaching half energy again. Merely dropping below threshold from a level-up keeps the same visible locked portals, displaying missing energy. Broken shield displays Shield Offline.

Return to field uses the used portal's saved position and 2 seconds damage protection ending on player firing, with no healing. Auto-fire and automatic skill interactions remain open. Campaign cleared-wave checkpoint travel is an older separate proposal still needing reconciliation.

## 3. Starting player and shields

| Stat | Current code | Target/review status |
|---|---|---|
| Hull/max hull | 100 / 100 | Retained starting value |
| Normal shield | None in default and all build presets | Draft starter Deflector rank 1, capacity 20; 100/500 in chat were examples |
| Primary | Legacy default cannon, random 7–12 damage | Selected Starter Cannon tree root; numerical profile retains 7–12 |
| Mean hit / crit | 9.5 / 0% starting crit; critical multiplier 2 | Retained draft |
| Primary interval | 0.5 seconds | 2 attacks/s, ideal 19 DPS |
| Burst / projectiles / penetration | 1 / 1 / 1 | Exact new-family card mappings open |
| Projectile speed / radius | Cannon 200 / 0.6 world units | Target T1 range 100 |
| Speed / acceleration | 50 / 400 world units per second / per second squared | Retained baseline |
| Turning response | 4 at rest to 8 while at top speed, before Gyro multiplier | Exponential aim smoothing |
| Hit stun / ordinary protection | 0.2 / 0.8 seconds | Current stages; do not confuse with Blink/re-entry windows |
| Collision radius / nudge scale | 4 / 20 | Current constants |
| Contact damage value | 10 | Current constant; not primary-shot damage |
| Spawn position | (250,250) | Current code; future hub location open |
| Player level / progress | No new salvage-level system | Draft level 1 / progress 0 |
| Wallet / return energy | Existing harvested counter only | Target fresh run starts empty |
| Return cap / minimum | Not implemented | Draft 1000 / 500 at level 1 |

### Normal-play shield draft

For Deflector rank r and paid capacity purchases p:

- Normal capacity C = 20 + 5(r−1) + 1.25p.
- Online regeneration = 2 × [1 + 0.10(r−1)] points/s.
- Proposed break delay = max(5, 10−(r−1)) seconds.
- After delay, restart at 50% of C; restore remaining half over 3 combat seconds, without concurrent normal regeneration.
- A positive shield absorbs the entire hit even if damage exceeds remaining charge. Break blocks portal use. Exact online hit-delay and post-block invulnerability need an explicit rule.
- Paid capacity upgrades preserve current charge and reboot state. Batteries never raise C. Regeneration cannot refill overcharge.

| Example | Rank 1, p=0 | Rank 5, p=0 | Rank 10, p=0 | Rank 10, p=8 |
|---|---|---|---|---|
| C | 20 | 40 | 65 | 75 |
| Regen/s | 2 | 2.8 | 3.8 | 3.8 |
| Break delay | 10 s | 6 s | 5 s | 5 s |
| 50% restart | 10 | 20 | 32.5 | 37.5 |
| Maximum fresh XL charge total | 60 | 120 | 195 | 225 |

Rank 10 is a comparison milestone, not the final Deflector rank. Ability ranks remain uncapped.

### Existing equipment prototypes: integration unresolved

| Prototype | Current values |
|---|---|
| Cannon | Random 7–12, interval 0.5, speed 200, radius 0.6 |
| Heavy | Damage 40, interval 1.2, speed 100, radius 2, penetration 3 |
| Rockets | Damage 30, interval 0.9, speed 90, radius 0.7, blast radius 14 |
| Laser | Damage 4 per 0.1-second tick, range 100, half-width/radius 1.5 |
| Base engine | Speed ×1, acceleration ×1 |
| Pulse engine | Speed ×0.9, acceleration ×1.5 |
| Burst engine | Speed ×1.1, acceleration ×1.2; manual boost ×2.5 for 0.45 s, cooldown 3 s |
| Supercharged engine | Speed ×1.4, acceleration ×1 |
| Front / front+side / round shield | Capacity 30 / 40 / 50; directional coverage 120° / 180° / 360° |
| Equipment shield recharge | 3 s delay, 10 points/s |
| Invincibility equipment | 2 s active, 8 s cooldown, manual Space |

These are debug-selectable current equipment, not extra normal-play upgrade branches already approved. Their manual Space actions conflict with the all-automatic target unless retired/adapted. Do not add their shield capacity to Deflector by accident.

## 4. All 26 weapon nodes and signatures

**Graph selected; numerical profiles/signatures are draft tuning.** Prices are selected. All signatures are automatic.

```text
T1 Starter Cannon
  T2 Machine Gun
    T3 Rotary Cannon
      T4 Assault Cannon
        T5 Tempest
        T5 Ironclap
    T3 Focus Laser
      T4 Fusion Lance
        T5 Starbreaker
      T4 Arc Projector
        T5 Thunderweb
  T2 Sniper Cannon
    T3 Railgun
      T4 Siege Railgun
        T5 Horizon Piercer
        T5 Sundering Lance
      T4 Guided Launcher
        T5 Starfall
  T2 Shotgun
    T3 Flak Cannon
      T4 Shrapnel Cannon
        T5 Shatterstorm
        T5 Breachmaker
    T3 Flamethrower
      T4 Inferno Projector
        T5 Cinderheart
```

Buy only an immediate child of the current node. Choosing a child locks its siblings for that run, including T4/T5 splits. Upgrades remain mothership-only; a fresh run starts with Starter Cannon. No branch swapping, refund, persistent unlock or manual signature key is added.

### Full profiles and damage rules

Damage is HP, range/radius/distance are world units, speed is world units/s, cadence is triggers or ticks/s, and time is active combat seconds. Solo DPS is a long-run, zero-armor, stationary single-target calculation before cards, crits, abilities or difficulty; every applicable pellet hits, burn is established, sniper distance is at its maximum bonus, and signatures are earned at their fastest legal cadence. Opening delay, dodging, travel time, target switching, overkill and misses reduce actual output.

T1 preserves the existing random inclusive 7–12 damage, with mean 9.5. Primary fire has no ammunition/reload resource or movement slowdown in this draft. Range is travel length; beam/arc/cone attacks require valid visible targets. Homing cannot acquire off-screen targets. Existing obstacle/barricade blocking applies; enemy penetration is not wall penetration.

| Quantity | Draft value / rule |
|---|---|
| Purchase cost to reach T2 / T3 / T4 / T5 | Owner-selected 500 / 1500 / 4000 / 10000 Trade Scrap; cumulative 500 / 2000 / 6000 / 16000 |
| Ownership | One path/run; only immediate children, no respec/refund; new run resets |
| Primary damage modifiers | Apply Payload once to every primary-owned damage component; automatic abilities retain their own tuning |
| Critical handling | Existing 2x multiplier; one roll per emitted shot/volley/pulse/tick, shared by its damage descendants, never rolled recursively |
| Sniper family distance bonus | `1 + 0.25 * clamp((travelDistance - 12) / 18, 0, 1)`: 1x through 12, 1.125x at 21, 1.25x from 30 |
| Distance eligibility | Sniper Cannon, Railgun, Siege Railgun, Horizon Piercer and Sundering Lance direct shots only; not their secondary damage or Guided Launcher/Starfall |
| Enemy penetration falloff | First enemy 100%, each later enemy 60% of that contact's distance-adjusted shot damage; one hit per projectile/enemy |
| Same-tier price fairness | Identical purchase price across choices; no rarity or material gate added |
| Signature scaling | Payload/critical snapshot once; signature minimum intervals remain fixed combat seconds under attack-speed/burst/pellet modifiers |
| Fractional damage | Preserve fractional HP/damage internally in the future implementation; rounded UI must not discard repeated fractional ticks |

| Tier | Weapon | Base damage | Attacks/s | Range | Speed | Target limit | Ideal solo DPS |
|---|---|---|---|---|---|---|---|
| T1 | Starter Cannon | 7–12 | 2 | 100 | 200 | 1 | 19 |
| T2 | Machine Gun | 4 | 8 | 90 | 280 | 1 | 32 |
| T2 | Sniper Cannon | 28 | 1 | 120 | 480 | 3 | 35 |
| T2 | Shotgun | 6 × 6 pellets | 1 | 40 | 240 | See pellet rule | 36 |
| T3 | Rotary Cannon | 5 | 10 | 95 | 300 | 1 | 50 |
| T3 | Focus Laser | 5 / tick | 10 | 70 | Instant | 1 | 50 |
| T3 | Railgun | 40 | 1 | 135 | 600 | 4 | 50 |
| T3 | Flak Cannon | 8 × 6 pellets | 1 | 42 | 260 | See pellet rule | 48 |
| T3 | Flamethrower | 3 / tick + 20 burn/s | 10 | 30 | Cone | See flame rule | 50 |
| T4 | Assault Cannon | 6 | 12 | 100 | 320 | 1 | 72 |
| T4 | Fusion Lance | 7 / tick | 10 | 80 | Instant | 1 | 70 |
| T4 | Arc Projector | 14 / pulse | 5 | 60 | Instant | 3 | 70 |
| T4 | Siege Railgun | 56 | 1 | 145 | 700 | 5 | 70 |
| T4 | Guided Launcher | 56 | 1.25 | 120 | 160 | See explosive rule | 70 |
| T4 | Shrapnel Cannon | 9 × 8 pellets | 1 | 45 | 280 | See pellet rule | 72 |
| T4 | Inferno Projector | 5 / tick + 20 burn/s | 10 | 35 | Cone | See flame rule | 70 |
| T5 | Tempest | 7 | 12 | 105 | 340 | 1; 2 in Overdrive | 98 |
| T5 | Ironclap | 22 | 4 | 95 | 280 | 1 + splash | 96 |
| T5 | Starbreaker | 8 / tick | 10 | 90 | Instant | 1 + signature splash | 95 |
| T5 | Thunderweb | 14 / pulse | 5 | 65 | Instant | 3 | 95 |
| T5 | Horizon Piercer | 76 | 1 | 155 | 800 | 6 | 95 |
| T5 | Sundering Lance | 72 | 1 | 145 | 800 | 1 | 100 |
| T5 | Starfall | 64 | 1.25 | 130 | 180 | See explosive rule | 95 |
| T5 | Shatterstorm | 13 × 8 pellets | 1 | 48 | 300 | See pellet rule | 104 |
| T5 | Breachmaker | 60 | 1.5 | 60 | 320 | 1 + signature cone | 96 |
| T5 | Cinderheart | 6 / tick + 20 burn/s | 10 | 40 | Cone | See flame rule | 95 |

#### Pattern, geometry and damage accounting

- Bullet radii: Starter/Machine Gun/Rotary/Assault/Tempest 0.6; Ironclap 0.9; sniper/rail shots 0.7; pellet 0.45; guided missile 0.8; Breachmaker slug 1.0. Beam half-width: Focus 1.0, Fusion 1.25, Starbreaker 1.5. Beam stops after its allowed enemy count; both beam and projectile traversal stop at blocking world geometry.
- Shotgun T2: six evenly spaced pellets over a 30-degree full fan. Flak T3: six over 32 degrees. Shrapnel T4/Shatterstorm T5: eight over 32 degrees. Shotgun pellets hit one enemy; explosive Flak/Shrapnel/Shatterstorm pellets detonate on contact or range end, radius 3. An impacted enemy takes exactly the listed damage once; up to two other nearby enemies take 50% each. A range-end burst deals listed damage to its nearest enemy and 50% to up to two others. Damage is not both direct plus full blast on the same victim.
- Flame T3/T4/T5: full cone angle 40/45/50 degrees, range as in profiles, 10 direct ticks/s. The nearest enemy inside the aim cone receives full direct/burn damage; up to three additional enemies receive 35%. Burn is 20 damage/s on the primary, ticks every 0.25 s and expires 1.5 s after last flame contact. Additional enemies receive 7 burn damage/s. Burn refreshes, never stacks with itself; a new primary can upgrade an existing weaker burn, while weaker refreshes cannot downgrade a stronger unexpired burn. Secondary-only exposure refreshes a stronger burn only to its existing expiry; after expiry the current 35% burn applies. No ground fire. Flame exposure counters advance only on actual direct contact, not lingering burn.
- Arc T4/T5: acquire the nearest visible enemy in a 50-degree full forward cone. Chain to at most two further distinct visible enemies, each within 12 of its preceding link and at 50% damage, not compounded. Targets cannot repeat; no damage multiplication when only one enemy exists. Walls block acquisition and links. Stable ID breaks distance ties.
- Guided Launcher/Starfall: acquire the nearest visible enemy within 80 in a 90-degree full forward cone; turn at most 240 degrees/s. Keep a valid visible lock or reacquire under the same policy; without a legal target continue straight, never hold the primary firing loop waiting for a lock. Impact or travel limit detonates radius 10/12, up to four distinct enemies: primary 100%, others 50%. Direct plus splash is a single damage event per victim. These weapons do not inherit rail distance/penetration.
- Rotary has no damage ramp penalty before T5; all weapons retain their listed baseline immediately. Ordinary fire stops during hub/pause. Existing cooldown debt is preserved when upgrading; no extra shot or signature refresh is granted.
- Nearest-first with stable-ID ties selects damage-limited area targets. Hard visual budgets must not silently delete already-earned damage or rewards. Card-added target counts remain separate, bounded compatibility work under PREP-27/PREP-14.

#### T5 signatures

Counters below count only primary trigger groups that actually contact an enemy: one group for a pellet volley, burst or emitted primary pulse, never one per pellet, victim, chain or secondary effect. World-object hits do not earn signature charge. Counters cannot bank additional activations while a minimum interval is closed. All signature-generated damage is unable to generate another signature. A no-target trigger never spends a ready signature. Pauses/hub suspend counters and timers; upgrades cannot precharge or reset them.

| T5 | Automatic signature | Trigger / bound | Extra damage and coverage |
|---|---|---|---|
| Tempest | Overdrive | 4 s of primary enemy contact earns 2 s at 18 shots/s, then repeat. Contact time has a 0.2 s grace; after 0.5 s without contact, unfinished charge resets. No charge during Overdrive | Normal 12 shots/s, 7 damage; Overdrive rounds hit up to 2 enemies with the penetration falloff. Overdrive duration advances in combat even if shots miss; ideal cycle is 6 s |
| Ironclap | Hammerfall | Every eighth successful shot, minimum 2 s between activations | That shot adds 16 to its primary victim; radius-8 splash deals 16 to at most 3 other enemies, excludes the primary; push up to 3 units subject to enemy resistance, never stun-lock a boss |
| Starbreaker | Core Rupture | 2 s actual beam contact on the same enemy, minimum 2 s between activations. A miss gap over 0.2 s or target switch resets exposure | 30 damage to primary, 15 each to at most 3 others within radius 8 |
| Thunderweb | Storm Network | 2 s of actual primary arc contact, minimum 2 s between activations; miss gap over 0.2 s resets charge | One enhanced pulse adds 50 to its primary and 25 each to its existing two links; no extra links or recursive arcs |
| Horizon Piercer | Terminal Shock | Every third successful shot, minimum 3 s between activations | Empowered projectile stores last enemy contact; on termination, radius-8 shock deals 24 to at most 4 enemies not already hit by that projectile. No solo DPS bonus; ordinary 76 x 1.25 = 95 |
| Sundering Lance | Fracture | Every third consecutive successful shot on the same target, minimum 3 s between activations. A miss, target change or 2 s without contact resets the sequence | Add 30 damage to that target, no permanent vulnerability/debuff. Direct shots hit one enemy, trading away Siege Railgun's penetration |
| Starfall | Pursuit Salvo | Every fifth successful primary missile, minimum 4 s between activations | Launch 3 additional missiles, 20 damage each, using normal guidance and radius-6 blast with the normal four-target/50% secondary rule. Distribute among legal targets before reusing one; all may hit a lone target |
| Shatterstorm | Fragment Bloom | Every fourth successful volley, minimum 4 s between activations | Each impacted parent pellet emits 2 child fragments, 3 damage each, ±15 degrees from its incoming direction, speed 300, travel 10, radius 0.3; no blast/splitting, and each pair excludes its parent's impact victim. At most 16 children per empowered volley; no solo bonus against the impacted lone target |
| Breachmaker | Breach Wave | Every third successful slug, minimum 2 s between activations | Add 12 damage to its impact victim; behind it, a 45-degree full cone of length 15 deals 24 to at most 4 others, excludes primary |
| Cinderheart | Flashover | 2 s of direct flame contact on one enemy, minimum 2 s globally between activations. Miss gap over 0.2 s resets that enemy's exposure | 30 to triggering enemy and 15 each to at most 3 others within radius 8. Choose greatest exposure then stable ID if simultaneous; eruptions/burn cannot trigger eruptions |

Earned signature effects commit only if their triggering primary hit occurs; a victim killed by that hit still produces its committed area effect at the stored impact position. Target-death cannot charge another target or duplicate the effect. Missing initial targets means no free signature charge from firing into empty space. Signature counters/timers are run-local; full reset clears them.

#### Analytical balance evidence and playtest gates

| T5 | Ideal long-run solo calculation | DPS |
|---|---|---|
| Tempest | `7 * (12*4 + 18*2) / 6` | 98 |
| Ironclap | `22*4 + 16/2` | 96 |
| Starbreaker | `8*10 + 30/2` | 95 |
| Thunderweb | `14*5 + 50/2` | 95 |
| Horizon Piercer | `76*1.25` | 95 |
| Sundering Lance | `72*1.25 + 30/3` | 100 |
| Starfall | `64*1.25 + 3*20/4` | 95 |
| Shatterstorm | `13*8` | 104 |
| Breachmaker | `60*1.5 + 12/2` | 96 |
| Cinderheart | `6*10 + 20 + 30/2` | 95 |

The ideal solo spread is 104/95 = 1.0947, under 10%. This is a paper comparison, not measured combat throughput. Burn can continue briefly after disengaging; shotgun pellet loss and sniper near-range damage must be reported rather than replaced by these ceilings.

Future checks before any balance claim:
1. Compare each tier against equal HP targets and equal upgrade investment. Include 30-HP basic and 50-HP ranged prototype targets, plus synthetic durable 1000-HP targets (test fixtures, not approved boss stats), dispersed enemies, packed crowds and moving targets. Check all firing directions and obstacle lanes at the real camera zoom.
2. Run each T5 in a fixed-seed lone durable-target encounter and a mixed crowd encounter with at least three pilots. Record time-to-kill, actual landed DPS, incoming damage, clear rate and target uptime. Aim for median lone-target completion times within 15% of the roster median at intended fighting distances; a failed target leads to tuning, not declaring a path balanced from nominal DPS.
3. Repeat with equal offensive card/shop budgets and with each supported pattern card. Do not publish a card/weapon pairing that silently wastes the card; exact burst/scatter/beam/cone mappings remain PREP-27, not implicitly approved here. Check high-rank attack-speed/crit and signature recursion.
4. Every enabled encounter must remain completable by every path at the expected tier without requiring a rare compensating ability. Close-range routes require practical attack windows; no hard weapon-family immunity is proposed. This is an encounter acceptance requirement, not new boss authorship.
5. Record time/wallet to each tier and affordable repair burden in real modes. Equal prices do not establish that T5 is reachable in 300-second Survival; economy/schedules remain deferred.
6. Verify no damage/reward loss under the combined multi-target/effect load, at both 30 and 144 FPS, plus hub suspension and new-run reset. Do not claim implementation readiness until compatibility, performance limits and runtime checks are resolved.

## 5. Attributes, cards and high-build endpoints

The 25%-strength numeric shop rule is selected. Exact list, eight-purchase limits and family compatibility remain draft. Ordinary persistent augment cards currently cap at 10; ability ranks do not.

| Attribute | One full field-card increment | One purchased increment | Notes |
|---|---|---|---|
| Weapons Payload | +15 percentage points of base primary damage | +3.75 percentage points | Primary attacks only; automatic ability damage keeps its own tuning |
| Critical Matrix | +5 percentage points critical chance | +1.25 percentage points | Clamp probability at 100%; show percentage points, not ambiguous percent |
| Overclocked Chambers | Attack cooldown multiplied by 0.90 | Attack cooldown multiplied by 0.975 | Quarter of the 10% cooldown reduction; not a claim of exactly 25% of resulting DPS gain |
| Reinforced Hull | +20 max HP and the existing +20 current-HP card grant | +5 max HP; no current-HP grant | Paid capacity is not free repair |
| Thruster Overdrive | Move speed multiplied by 1.10 | Move speed multiplied by 1.025 | Preserve control and frame-rate independence |
| Gyro Control | Turning response multiplied by 1.10 | Turning response multiplied by 1.025 | Use actual prototype meaning of turn responsiveness |
| Phase Shift | Ordinary post-hit protection multiplied by 1.10 | Ordinary post-hit protection multiplied by 1.025 | Does not extend Blink's separate fixed protected window |
| Inertia Impact | +50 knockback magnitude | +12.5 knockback magnitude | Actual supported targets remain bounded by their knockback rules |
| Shield Capacity | Deflector card: +5 capacity plus its full-rank shield effects | +1.25 capacity only | Does not grant a Deflector rank, reboot reduction or regeneration boost |

For card count c and paid count p, before other modifiers:

| Stat | Formula |
|---|---|
| Primary damage factor | 1 + 0.15c + 0.0375p |
| Critical chance | min(1, 0.05c + 0.0125p) |
| Expected crit damage factor | 1 + criticalChance, for 2x crits |
| Attack interval factor | 0.90^c × 0.975^p |
| Max hull | 100 + 20c + 5p |
| Speed | 50 × 1.10^c × 1.025^p |
| Turn response multiplier | 1.10^c × 1.025^p |
| Ordinary iframe duration | 0.8 × 1.10^c × 1.025^p |
| Knockback magnitude | 50c + 12.5p |
| Shield capacity | 20 + 5(r−1) + 1.25p; r is Deflector rank, not player level |

Each attribute has its own c/p. A full Hull card grants +20 current HP too; a paid Hull increment grants no heal. Shield rank/paid capacity preserve current points. Four shop purchases exactly equal one card only for additive gains: 0.975^4 is not 0.90, and 1.025^4 is not 1.10.

### Defined milestone instead of an invented “final player”

| Scalar stat | Start | 10 matching cards | 10 cards + 8 paid increments |
|---|---|---|---|
| Primary damage factor | 1x | 2.5x | 2.8x |
| Critical chance | 0% | 50% | 60% |
| Expected damage incl. crit | 1x | 3.75x | 4.48x |
| Attack interval factor | 1x | 0.349x | 0.285x |
| Starter attacks/s, no burst | 2 | 5.736 | 7.024 |
| Ideal starter expected DPS, scalar only | 19 | 204.343 | 298.93 |
| Max hull | 100 | 300 | 340 |
| Speed | 50 | 129.687 | 158.011 |
| Ordinary iframe duration | 0.8 s | 2.075 s | 2.528 s |
| Turn multiplier | 1x | 2.594x | 3.16x |
| Knockback | 0 | 500 | 600 |

These are separate capped attribute endpoints, not a promise all can be acquired in one run. Nine attributes × eight shop increments costs 39,600; adding a T5 path costs 55,600 before skills, repairs or batteries. Ranks in automatic skills have no finite final endpoint. Enemy HP also changes with player level, not these card counts.

**Do not multiply every T5 DPS by 15.73 blindly:** only ordinarily cadence-scaled components follow that scalar estimate. Fixed signature intervals, exposure requirements, burn rules and target limits must be calculated separately.

### Discrete field cards

| Card | Current effect per pick | At 10 picks, before family-specific compatibility |
|---|---|---|
| Rapid Fire | +1 burst shot | 11 shots per burst |
| Scatter Shot | +1 projectile in fan | 11 projectiles per directional shot |
| Armor Piercing | +1 penetration count | Base count +10 |
| Broadside Cannons | +one shot-pattern on each side | 10 per side |
| Tail Gunner | +one rear shot-pattern | 10 rear patterns |

Current shot directions = 1 + 2×BroadsideRank + TailRank. With all three pattern cards at 10, a single burst shot can emit 31×11 = 341 projectiles; 11 shots makes 3,751 projectiles per burst before any new-family effects. This is why compatibility and effect budgets are critical.

Current ballistic burst cycle = weaponCooldown + (burstCount−1)×0.1 s. Burst is not simply an 11x attack-rate multiplier. Current laser prototype has separate pulse/auxiliary-bolt logic. No quarter-bullet shop purchase is selected. Nano Repair currently heals 25% max HP but is targeted for removal/replacement by Shield Detonation.

## 6. All abilities and rank calculations

Target roster: 19 abilities + 13 augments = 32 entries. Current prototype: 18 abilities + 14 augments = 32. Difference: Nano Repair removed; Shield Detonation added. All target skills automatic; no Q skill slot. Primary shooting stays player-controlled/auto-fire.

| Ability | Proposed rarity | Automatic behavior and duration category |
|---|---|---|
| Scrap Magnet | Common | Starts its timed local collection window when eligible released pickups are in range; respects radius and existing exclusions |
| Repulsor Pulse | Common | Periodic instantaneous push when nearby enemies make a pulse useful; otherwise stays ready |
| Deflector Shield | Uncommon | Persistent shield; starter grant and field ranks. Shop buys capacity only; broken shield blocks Return Home |
| Radiant Halo | Uncommon | Instant burst centered on the ship when enemies are within its authored radius |
| Corrosive Trail | Uncommon | Timed emission window while useful combat movement occurs; individual pools expire under existing duration rules |
| Point-Defense Interceptor | Uncommon | Timed defensive window triggered by relevant hostile projectiles; does not delete friendly fire |
| Laser Rings | Rare | Persistent orbiting blades once acquired; no duration gap. Existing rank/count/radius rules apply, subject to authored load budgets |
| Lightning Ring | Rare | Temporary ring around the ship, then recharge; damages/stuns nearby enemies during the window |
| Chain Lightning | Rare | Selects a valid nearby target automatically and chains through distinct targets; instantaneous event |
| Combat Drone | Rare | Proposed persistent companions until destroyed; each missing slot returns after its combat respawn delay. No free revival on hub/shop opening |
| Shield Detonation | Rare | Instant shield-break event when its own cooldown is ready; does not restore the shield |
| Plasma Beam | Epic | Timed forward/cone damage; automatically aims toward a valid enemy while preserving the authored cast snapshot |
| Hologram Clone | Epic | Temporary decoy/firing copy, then recharge; primary weapon inherited at clone creation, not free future weapon replacement |
| Realm Breaker | Epic | Temporary targeted rift with automatic valid-target placement and projectile defense |
| Nuclear Missile | Epic | Automatically selects a valid threat/group, launches its existing delayed attack and resolves its blast once; not the primary Guided Missile tree node |
| Singularity | Epic | Temporary automatically placed pull/damage zone; ordinary eligible rewards remain |
| Space Collapse | Legendary | Automatic bounded group targeting; enemies erased by it yield no trade or salvage. Source objectives still resolve |
| Armageddon | Legendary | Timed automatic barrage with bounded effects; no manual target/cast button |
| Blink Drive | **Legendary — owner confirmed** | Reactive interception of a direct incoming hit, legal on-screen relocation and short protected breathing window; full contract below |

### Current rank-one numerical baseline

The next table is inspected prototype data. Q labels describe current code only. Shield, Blink, Magnet, persistent Rings and persistent Drones have target overrides below. Damage is per tick/event, not DPS.

| Key | Activation | Cooldown / duration | Behavior |
|---|---|---|---|
| laser-rings | Auto | 12 / 8 | Three orbiting blades, radius 18, contact radius 4, 12 damage every 0.2 s |
| deflector-shield | Q | 16 / 8 | Absorbs 3 hits; unused hits expire after 8 s; independent of equipment shields |
| lightning-ring | Auto | 14 / 8 | Radius 25 perimeter, width 5, 8 damage every 0.5 s and 0.6 s stun |
| blink-drive | Q | 4 / instant | Teleports toward cursor up to 35 units; 0.25 s protection; can jump over barricade segments |
| nuclear-missile | Q | 30 / 0.7 travel | Radius 55; destroys standard enemies regardless of HP; future boss-type targets take 250 damage |
| space-collapse | Q | 35 / instant | Radius 32 at cursor; erases enemies, **no scrap**, still awards score and kill count |
| radiant-halo | Q | 8 / instant | Radius 32 around ship, 60 damage |
| repulsor-pulse | Auto | 5 / instant | Pushes ordinary enemies within radius 30 outward by 22 units |
| point-defense-interceptor | Auto | 12 / 8 | Removes hostile bullets crossing radius 38, including fast swept crossings; leaves friendly fire alone |
| scrap-magnet | Auto | 15 / 5 | Collects all currently released scrap anywhere every 0.2 s; pending debris explosions still finish first |
| chain-lightning | Q | 7 / instant | Up to 6 distinct nearest targets, 35 damage each, 45-unit jump range, stable tie breaking |
| hologram-clone | Q | 18 / 10 | Stationary clone offset 18; lures enemies within 60 and repeats primary fire |
| combat-drone | Auto | 20 / 15 | Chases nearest enemy within 90 at speed 70; shoots 15-damage bolts every 0.4 s within 35 |
| plasma-beam | Q | 12 / 4 | Facing cone, range 65, half-angle 30 degrees, 12 damage every 0.15 s |
| corrosive-trail | Auto | 14 / 8 | Leaves radius-8 pools lasting 3 s; 6 damage every 0.3 s; refreshes 1 s of half speed and half contact/projectile damage |
| singularity | Q | 22 / 6 | Radius 42 at cursor; pulls at speed 28; 10 damage every 0.2 s; ordinary scrap rewards |
| realm-breaker | Q | 20 / 6 | Rift length 50, half-width 6 at cursor, perpendicular to ship facing; 20 damage every 0.2 s and continuous hostile projectile absorption |
| armageddon | Q | 35 / 6 | Seeded barrage across the visible battlefield; radius 22, 80 damage every 0.3 s |

### Every rank-growth rule

| Ability | Improvement per additional level |
|---|---|
| Laser Rings | +1 blade; +8% orbit radius, +25% damage, +10% duration |
| Deflector Shield | +1 absorbed hit; +15% duration |
| Lightning Ring | +10% ring radius, +25% damage, +10% duration |
| Blink Drive | +15% distance; -10% cooldown |
| Nuclear Missile | +15% blast radius, +30% boss damage; -5% cooldown; same travel time |
| Space Collapse | +1 collapse zone, +15% radius; always no scrap |
| Radiant Halo | +15% radius, +30% damage; -5% cooldown |
| Repulsor Pulse | +10% radius, +15% push distance; -5% cooldown |
| Point-Defense Interceptor | +10% radius, +15% duration |
| Scrap Magnet | +20% duration; -5% cooldown; collection frequency multiplier +0.10 |
| Chain Lightning | +1 distinct target, +10% jump range, +25% damage |
| Hologram Clone | +15% duration; firing frequency multiplier +0.15; inherits primary weapon damage |
| Combat Drone | +1 drone, +15 HP per drone, +25% shot damage |
| Plasma Beam | +10% cone range, +25% damage, +10% duration |
| Corrosive Trail | +15% pool radius, +25% damage, +10% emitter duration |
| Singularity | +10% radius, +25% damage, +10% duration, +15% pull speed |
| Realm Breaker | +15% length/width, +25% damage, +10% duration |
| Armageddon | +1 blast per volley, +10% radius, +20% damage |

Let e = rank−1, z = min(e,4). For base B and growth fractions from the table:
- Radius/range = baseRadius × (1 + radiusGrowth×z).
- Damage = round-half-up(baseDamage × (1 + damageGrowth×e)), with the current int-range saturation.
- Duration = baseDuration × (1 + durationGrowth×e).
- Tick interval = baseInterval / (1 + frequencyGrowth×e).
- Cooldown factor through rank 5 = 1 − rechargeReduction×e.
- Above rank 5 = (1−4×rechargeReduction) / [1+rechargeReduction×(e−4)].
- Base cooldown is multiplied by that factor. It remains positive for finite rank but approaches zero at unbounded ranks.
- Counts continue: Rings blades = r+2; Chain target count = r+5; Collapse zones = r; Drones = r; drone HP = 30+15(r−1); Armageddon blasts per volley = r.
- Push/pull strength grows +15% of base per additional rank where specified. Radius freezes at rank 5, not damage/count/duration.
- Casts snapshot rank; picking an upgrade does not refresh an active effect or erase cooldown debt.

### Rank 5 and 10 numerical snapshots

These are computed from current Balance.hpp growth, not adopted overrides. Column order is **damage / radius-or-range / cooldown seconds / duration seconds**. Zero damage means a non-damage mechanic, not a useless ability. Nuclear's damage column applies to boss-type targets; ordinary-target erasure and Collapse behavior are separate.

| Ability | R5: damage / radius / cooldown / duration | R10: damage / radius / cooldown / duration |
|---|---|---|
| Laser Rings | 24 / 23.76 / 12 / 11.2 | 39 / 23.76 / 12 / 15.2 |
| Deflector Shield | 0 / 8 / 16 / 12.8 | 0 / 8 / 16 / 18.8 |
| Lightning Ring | 16 / 35 / 14 / 11.2 | 26 / 35 / 14 / 15.2 |
| Blink Drive | 0 / 56 / 2.4 / 0.2 | 0 / 56 / 1.6 / 0.2 |
| Nuclear Missile | 550 / 88 / 24 / 0.7 | 925 / 88 / 19.2 / 0.7 |
| Space Collapse | 300 / 51.2 / 35 / 0.2 | 300 / 51.2 / 35 / 0.2 |
| Radiant Halo | 132 / 51.2 / 6.4 / 0.2 | 222 / 51.2 / 5.12 / 0.2 |
| Repulsor Pulse | 0 / 42 / 4 / 0.2 | 0 / 42 / 3.2 / 0.2 |
| Point-Defense Interceptor | 0 / 53.2 / 12 / 12.8 | 0 / 53.2 / 12 / 18.8 |
| Scrap Magnet | 0 / 0 / 12 / 9 | 0 / 0 / 9.6 / 14 |
| Chain Lightning | 70 / 63 / 7 / 0.2 | 114 / 63 / 7 / 0.2 |
| Hologram Clone | 0 / 60 / 18 / 16 | 0 / 60 / 18 / 23.5 |
| Combat Drone | 30 / 90 / 20 / 15 | 49 / 90 / 20 / 15 |
| Plasma Beam | 24 / 91 / 12 / 5.6 | 39 / 91 / 12 / 7.6 |
| Corrosive Trail | 12 / 12.8 / 14 / 11.2 | 20 / 12.8 / 14 / 15.2 |
| Singularity | 20 / 58.8 / 22 / 8.4 | 33 / 58.8 / 22 / 11.4 |
| Realm Breaker | 40 / 38.4 / 20 / 8.4 | 65 / 38.4 / 20 / 11.4 |
| Armageddon | 144 / 30.8 / 35 / 6 | 224 / 30.8 / 35 / 6 |


### Target overrides and additional values

| Skill | Target change/numbers | Status |
|---|---|---|
| Deflector | Point-based capacity/regen/reboot in section 3, replaces temporary hit-count skill | Draft numerical contract |
| Blink | Legendary reactive direct-hit rescue; cooldown max(12,30×0.95^(r−1)); 2 s protection; distance 35×[1+0.15×min(r−1,4)] | Legendary/reactive selected; exact numbers draft |
| Blink milestones | Cooldown R1 30, R5 24.435, R10 18.907 s; max travel R5+ 56 | Derived draft |
| Blink no safe point | No teleport, no protection, no cooldown spent; ordinary hit resolves | Proposed contract |
| Laser Rings | Persistent blades rather than an 8-second active window | Proposed persistence |
| Combat Drone | Persistent until destroyed; individual slot returns after 20 combat seconds; existing damage/count/HP growth | Proposed persistence |
| Scrap Magnet | Local radius 60, 15 s cooldown, 5 s duration; pull speed max(basePullSpeed,1.25×shipSpeed) | Draft; replaces global collection |
| Shield Detonation | Break-triggered 50 damage, radius 35, cooldown 18; +25% damage/rank, +10% radius/rank through R5, −10% cooldown with positive continuation | Draft new skill replacing Nano Repair |
| Shield Detonation R5 / R10 | Damage 100 / 163; radius 49 / 49; cooldown 10.8 / 7.2 s if common continuation adopted | Derived draft, not implemented |

Other constants: stun 0.6 s; corrosion status 1 s with speed/damage ×0.5; Repulsor base push 22; Singularity pull 28/s; blade contact radius 4 and orbit speed 6 rad/s; ring width 5; clone offset 18; drone speed 70, firing range 35, standoff 15, radius 3, spawn spacing 10, contact damage at most every 0.5 s; plasma half-angle 30°; trail pool life 3 s; rift half-length 25 and half-width 6; Armageddon chooses across 85% of view extent. Barricades ignore displacement/stun/corrosion. Overlapping acid pools do not multiply their damage.

Examples: prototype drone R1 delivers up to 15/0.4 = 37.5 DPS while firing; R5 five drones ×30/0.4 = 375 DPS; R10 ten ×49/0.4 = 1,225 DPS before misses/target access/uptime. This outscales a bare T5 primary and needs whole-build review. Laser Rings' 12/0.2 = 60 DPS is per blade-contact opportunity, not guaranteed target DPS. Plasma is 12/0.15 = 80 active DPS at R1, not long-run DPS across cooldowns.

## 7. Enemies, damage and encounter scaling

### Ordinary enemies and hazards

| Type | HP | Contact damage | Projectile damage | Movement/fire | Status |
|---|---|---|---|---|---|
| Low/basic | 30 | 10 | None | Speed 15–30; turning 5; sprite 15, hitbox parameter 15/3.5 ≈4.286 | Code |
| Mid/ranged | 50 | 10 | 10 | Speed 25–50, turning 1.5–2.5, fire interval 0.5–1.25 s, projectile speed 120–150, range 100 | Code |
| Heavy/Compactor | 160 | 20 | 10 | Approach 12, windup 0.6 s at range 60, charge 110 for 0.45 s, recovery 1 s; recovery takes ×1.25 damage; three-shot spread 20°, bullets110 | Historical draft only; no class found |
| Barricade segment | 120 | 10 | None | 64-segment ring; details below | Code |
| Ordinary debris | One-hit destruction behavior | 10 collision damage | None | Speed 5–15, rotation 5–240°/s | Prototype; final enemy/debris interaction review pending |
| Elite | Not authored | Not authored | Not authored | Reward tier exists, content does not | Open |
| Boss | Not authored final content | Not authored final content | Not authored final content | Old proposals below are reference only | Open |

Current enemy contact damage is shared through Enemy::getContactDamage: 10 ordinarily, 5 under corrosion. Mid bullets snapshot that damage when fired. Sprite variants of basic enemies are visual variants, not separate HP/damage profiles. Enemy HP/damage must eventually move into the adopted Balance profile, since several old numbers remain inline.

### Spawn HP formula (draft)

HP = max(1, round-half-up(baseHP × min(50, encounterFactor × difficultyBaseline × (1+g)^(L−1)))).

Difficulty baseline Easy/Hard/Impossible = 1 / 1.25 / 1.50; g = 0.05 / 0.10 / 0.15. Enemy damage multiplier is 1 for every difficulty in this draft. Spawn snapshots HP; leveling does not heal or inflate existing enemies. The 50x total bound is proposed, not playtested.

| Collected salvage | Difficulty | Player level | Low HP | Mid HP | Draft heavy HP |
|---|---|---|---|---|---|
| 500 | Easy | 5 | 36 | 61 | 194 |
| 2000 | Easy | 15 | 59 | 99 | 317 |
| 6000 | Easy | 29 | 118 | 196 | 627 |
| 16000 | Easy | 46 | 270 | 449 | 1438 |
| 500 | Hard | 5 | 55 | 92 | 293 |
| 2000 | Hard | 12 | 107 | 178 | 571 |
| 6000 | Hard | 21 | 252 | 420 | 1345 |
| 16000 | Hard | 30 | 595 | 991 | 3173 |
| 500 | Impossible | 5 | 79 | 131 | 420 |
| 2000 | Impossible | 10 | 158 | 264 | 844 |
| 6000 | Impossible | 17 | 421 | 702 | 2246 |
| 16000 | Impossible | 24 | 1120 | 1867 | 5974 |


Assumptions: all listed salvage has been collected, requirements rounded half-up per level, encounterFactor=1. At expected ordinary trade≈salvage, 16,000 salvage is comparable to gross weapon-path income; actual wallet timing differs with random drops, bosses, spending and collection. These are calculations, not measured run results.

At those 16,000-salvage basic HP values, a bare 95-DPS T5 needs about 2.84 / 6.26 / 11.79 seconds of ideal damage to kill one basic enemy. Crowd weapons, cards and abilities change that dramatically; paper T5 DPS cannot alone support swarm scaling.

### Current spawner, not final mode schedules

Current interval = max(0.025, 1.25 − 0.005×combatSeconds); random group of 1–3, mean 2. Nominal mean spawn rate = 2/interval, limited by actual frame/update handling and the 10,000-enemy cap. At 0 s: 1.6/s; 120 s: 3.077/s; 240 s: 40/s; at 245 s and later: theoretical 80/s. Spawn ring radius 150; enemies beyond 1,000 distance despawn.

Mid introduction starts at **150 seconds in code**, despite stale comments saying five minutes. Mid chance = 40×[1−exp(−(t−150)/180)] percent after that time, approaching 40%. It is about 22.62% at t=300. There is no inspected five-mode WaveDirector implementation.

### Barricade encounter

At 120 combat seconds, once/run, 64 segments of 120 HP surround a fixed center. Ring radius 130 ->45 over30 s (2.833/s), rotates4°/s. Segment radii3.75/6.25/7.5; player radius4. Destroyed gaps stay in the rotating formation. Five adjacent destroyed segments guarantee a late-ring traversable gap even beside largest segments; five segments represent600 HP before damage modifiers. Survivors scatter55/s for4 s, then despawn. Contact10, score5 on destruction, zero scrap. No stacking event; at population limit wait for64 slots. Crowd/enemy pressure continues. Return/Blink legal-region rules must prevent unintended wall bypass.

### Boss reference numbers: NOT approved final bosses

| Old reference | HP | Contact / bullet damage | Speed / size | Main attack reference |
|---|---|---|---|---|
| Wave-5 reference (“Hoarder” in historical docs) | 1800 | 25 / 15 | 8 then12 /50 | 16-bullet ring every3 s then2 s below50%; speed70; Low adds4/9 s, then Mid adds2/12 s |
| Wave-10 reference (“Core” in historical docs) | 3200 | 30 /15 | 10 /60 | Aimed triple every1.6 s; spiral4 arms, tick0.15 s for3 s every7 s; below60% spiral every5 s and Heavy adds2/15 s; below25% six arms, aimed1 s, bullet speed×1.2 |

Shared old intro2 s invulnerable; knockback immune. Final identities/phases/stats are owner content. Old fixed boss rewards/scores and old Story victory flow must not override current source-objective/mode contracts. Current selected reward bands are in section10.

## 8. XP, levels and return energy

**Draft numeric curve; field progression selected.** Each pickup carries fixed salvage and random money. Spending money never removes XP or energy.

Required salvage at level L = round-half-up[100×(1+g)^(L−1)]. Start L1, progress0. Subtract each completed requirement and carry remainder; queue every earned card choice, one at a time. Take one of three distinct eligible cards. No timed/wave-clear cards in the target.

| Player level | Easy requirement | Hard requirement | Impossible requirement |
|---|---:|---:|---:|
| 1 | 100 | 100 | 100 |
| 2 | 105 | 110 | 115 |
| 5 | 122 | 146 | 175 |
| 10 | 155 | 236 | 352 |

Cumulative salvage to reach level L is the sum of individually rounded requirements for levels1 through L−1. Do not simply round one closed-form sum when exact integer progression matters.

Return maximum = 1000 + modeGrowth×(L−1); minimum = ceil(maximum/2). Mode growth: Swarm50, Survival75, Boss100, Chaos125, Campaign100. Every collected salvage point also adds one energy up to the cap. Level-up preserves absolute energy and changes the cap/threshold. Successful return drains current energy to0; this cost remains the retained draft.

| Level | Swarm | Survival | Boss | Chaos | Campaign |
|---|---|---|---|---|---|
| 1 | 1000 / 500 | 1000 / 500 | 1000 / 500 | 1000 / 500 | 1000 / 500 |
| 2 | 1050 / 525 | 1075 / 538 | 1100 / 550 | 1125 / 563 | 1100 / 550 |
| 5 | 1200 / 600 | 1300 / 650 | 1400 / 700 | 1500 / 750 | 1400 / 700 |
| 10 | 1450 / 725 | 1675 / 838 | 1900 / 950 | 2125 / 1063 | 1900 / 950 |

### Actual first-return kill calculation

Assume only basic enemies, each worth2 collected salvage, all level-ups processed immediately, no debris, no spending effect and a healthy online shield. The threshold is recalculated after leveling. Counts below are mathematical equivalents; Boss mode is not assumed to contain that many basic enemies.

| Mode | Easy: kills / level / energy needed | Hard | Impossible |
|---|---|---|---|
| Swarm | 313 / L6 / 625 | 300 / L5 / 600 | 300 / L5 / 600 |
| Survival | 363 / L7 / 725 | 344 / L6 / 688 | 325 / L5 / 650 |
| Boss | 400 / L7 / 800 | 375 / L6 / 750 | 375 / L6 / 750 |
| Chaos | 469 / L8 / 938 | 438 / L7 / 875 | 407 / L6 / 813 |
| Campaign | 400 / L7 / 800 | 375 / L6 / 750 | 375 / L6 / 750 |


This exposes the difficulty inversion and proves “250 kills” is only the initial-threshold estimate. Later return cycles depend on level, residual XP and energy lost at the prior return. There is no fixed seconds-to-return without a kill/collection schedule.

## 9. Economy, shop, repair and batteries

### Weapon progression

| Purchase | Increment | Cumulative |
|---|---|---|
| T2 | 500 | 500 |
| T3 | 1500 | 2000 |
| T4 | 4000 | 6000 |
| T5 | 10000 | 16000 |

Same price on every branch; only immediate children; one branch/run; no respec/refund. Tier purchases grant no healing, XP, energy, extra skills or cooldown refresh. All ten finals cost16,000.

For T5 in20–25 combat minutes: weapon-only net saving rate16000/(1200–1500) =13.33–10.67 scrap/s, or800–640/min. At basic mean2, 8,000 kills' expected money before any other spending. At the same net rate, five-minute Survival yields3,200–4,000 scrap, enough for T3 total2,000 but short of T4 total6,000. This is an illustrative consistent-rate comparison, not a promised Survival earnings curve.

### Attribute and ability prices

| Purchase | Formula | Examples / total |
|---|---|---|
| Numeric attribute purchase with n prior paid purchases | 200+100n | 200/300/400/500/600/700/800/900; eight total4400 |
| Standard owned skill, current rank r | 500+250r | R1->2:750; R5->6:1750; R10->11:3000 |
| Special owned skill, current rank r | 1000+375r | 1375 /2875 /4750 at r1/5/10 |
| Owned Blink rank (proposal) | 3000+750r | 3750 /6750 /10500 at r1/5/10 |
| Proposed Luck, n prior purchases | 400+200n | 400/600/800/1000/1200; total4000 |
| Singularity acquisition | 2400 | Only if stocked/unowned |
| Space Collapse acquisition | 2800 | Only if stocked/unowned |
| Nuclear Missile acquisition | 3200 | Only if stocked/unowned |
| Armageddon acquisition | 4000 | Only if stocked/unowned |

Whole skill ranks do not use quarter-strength gains. Deflector has capacity purchases instead of full-rank shop purchases. Three distinct unowned special entries from the four are stocked for the run; no free reroll on reopening or returning. Blink first acquisition is proposed field-only. Shop does not grant ordinary first skills under this draft.

From owned rank1 to R: standard cost500(R−1)+125R(R−1); special1000(R−1)+187.5R(R−1); Blink3000(R−1)+375R(R−1). To R10:15,750 /25,875 /60,750 respectively, excluding acquisition. Rank is unbounded, so no finite total max-out cost exists.

### Hull repairs

Selected10 scrap per missing HP. Let D=maxHP−currentHP, Q=ceil(10D). Full repair spendsQ and restoresD. Affordable repair spendsB=min(wallet,Q), restoresD×B/Q for positiveD,Q,B. Fractional HP preserved. Example37 missing ->370 full quote; wallet185 buys18.5 HP. Empty wallet buys no healing.

Service takes3 seconds; pause freezes it; cancellation before completion spends/heals nothing. Revalidate deficit/funds at commit and do not use a stale quote. Actual successful hull repair clears harmful player statuses under the retained service draft. Battery purchase is a separate transaction. Paid max hull gives capacity only.

### Final battery contract

Selected battery contract: let C be current normal shield capacity including upgrades, S current shield, and f the purchased size fraction. On a successful shop purchase set `newShield = min(S, C) + f*C`. This removes the previous battery's excess above C, preserves any damage below C, and adds exactly the purchased charge. Do not refill to C first and do not set the total to f*C. There is no stacking: the largest purchase yields at most 3*C. Normal regeneration only restores up to C; damage above C consumes the excess permanently until another paid purchase. Purchases may repeat without depletion or per-visit limits, and replacing with a smaller size can lower shield. Capacity upgrades preserve current shield points; they do not retroactively refill a battery. Battery charge uses C at purchase, never the overcharged shield total.

| Battery | Charge supplied | Starting price (scrap) |
|---|---|---|
| Tiny | 20% of C | 100 |
| Small | 50% of C | 250 |
| Medium | 100% of C | 500 |
| Large | 150% of C | 700 |
| XL | 200% of C | 900 |

Let C0 be the ship's normal starting shield capacity before run upgrades, fixed for that run. Price is `ceil(startingPrice * C / C0)` scrap; quote from the same current capacity used for charge. A 50% capacity increase raises prices to 150/375/750/1050/1350. Preview normal capacity, current shield -> resulting shield, replacement loss if any, exact price and wallet afterward. An unaffordable purchase changes neither shield nor wallet; a successful purchase commits both together. Preserve fractional shield points. Battery use does not heal hull, increase normal capacity, grant a shield rank or create a carried activation item.

At C=100: S=80 + Tiny -> 100; S=80 + XL -> 280; S=280 + Tiny -> 120; S=100 + XL -> 300; buying XL again at S=300 stays 300. The owner's earlier 20-point Small example now maps to Tiny in the adopted five-size list. The resolved 80 + 200 -> 280 example supersedes the earlier 80 -> 200 interpretation. These are selected initial tuning and arithmetic contracts, not playtested balance.

Price C0 means actual initial normal shield capacity before run upgrades, NOT a 100/500 example. Under proposed C0=20:
- Rank1 C20 prices100/250/500/700/900; charges4/10/20/30/40.
- Rank5 C40 prices200/500/1000/1400/1800; charges8/20/40/60/80.
- Rank10 plus8 paid increments C75 prices375/938/1875/2625/3375; charges15/37.5/75/112.5/150.
- Full normal shield20 plus XL40 yields60. At current16, XL yields56.
- Buying XL at an already full60 replaces excess40 with40 and stays60; it does not reach100.

The UI must make replacing with a smaller battery visibly reduce total shield before spending. An identical full battery has zero net benefit; whether to disable that optional purchase is a UI policy still worth reviewing, not a change to the selected ability to repurchase.

At proposed starting capacity20, listed battery charge costs 25/25/25/23.333/22.5 scrap per supplied point for Tiny through XL, before rounding and discarded excess. Capacity-proportional pricing keeps these ratios roughly constant as capacity grows. Hull repair costs10 scrap/HP; shield points also regenerate and can absorb an entire breaking hit, so the two point types are not equivalent. Battery price/value still needs live review despite the selected prices.

## 10. Drops, debris, collection and Luck

| Tier | Trade minimum | Trade maximum | Expected trade | Fixed salvage |
|---|---:|---:|---:|---:|
| Low/basic | 1 | 3 | 2 | 2 |
| Mid/ranged | 3 | 7 | 5 | 5 |
| High/heavy | 8 | 12 | 10 | 10 |
| Elite, only if future content exists | 15 | 25 | 20 | 20 |
| Standard boss | 120 | 180 | 150 | 100 |
| Campaign final boss | 200 | 300 | 250 | 200 |

Currency ranges are inclusive uniform rolls stored once on spawn, isolated loot RNG. Fixed salvage feeds both XP and return energy; expected money happens to equal salvage for ordinary tiers, not bosses. Difficulty/level do not multiply rewards in the selected draft. Eligible death materializes the stored reward; collection credits it once. No enemy-specific materials are needed to buy a weapon.

Four appearance-matched labels: Metal Fragments, Circuit Parts, Polymer Pieces, Power Cells. All feed one wallet; no crafting wallet, conversion or rarity multiplier. Mixed merges conserve both trade and salvage values.

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

Debris values remain fixed for both fields in the target. Barricades, cleanup/despawn and Space Collapse give zero trade/salvage. Singularity gives ordinary eligible rewards. Environmental breakup gives no free harvest. Current minimal skill-kill drops are not the full target enemy economy.

Ordinary enemy pickups: draft cap500, no expiry, local value-preserving merging. Debris orbs retain their separate150 visual budget,20 s lifetime,0.05 s hold,150/s home speed,pickup radius2 and exact yield conservation. Debris destruction has8 frames×0.075 s; final flecks turn to pickups at0.525 s. Variant particle counts4/3/10/5/5/4/11/7/11/15 must not multiply their scrap yield. At cap, merge value rather than deleting it.

### Luck (unapproved)

Workshop ranks0–5; each rank gives a10% chance (maximum50%) to keep the higher of two independent tier trade rolls. Only ordinary low/mid/high; not XP, energy, card rarity, boss/debris/excluded rewards. Snapshot at enemy spawn so purchases cannot reroll suspended enemies.

For uniform integer range of n values starting at a, ordinary mean=a+(n−1)/2; mean of max of two=a+(n−1)(4n+1)/(6n). Luck mean = ordinaryMean + probability×(maxMean−ordinaryMean). For1–3 at rank5:2 +0.5×(22/9−2)=20/9≈2.222. The increase is2/9 per basic enemy; recovering4,000 solely from this expected increment requires18,000 newly affected basic enemies. That makes the current price/reward proposal questionable at20–25-minute progression.

## 11. Rarity and acquisition

| Proposed rarity | Cards |
|---|---|
| Common | Weapons Payload, Overclocked Chambers, Reinforced Hull, Thruster Overdrive |
| Uncommon | Critical Matrix, Rapid Fire, Phase Shift, Gyro Control, Inertia Impact |
| Rare | Armor Piercing, Scatter Shot, Broadside Cannons, Tail Gunner |

Proposed per-slot weights Common45%, Uncommon30%, Rare18%, Epic6.5%, Legendary0.5%. Independent Legendary gate0.005; if failed, sample eligible ordinary tiers with45/30/18/6.5 weights renormalized. Never promote a failed gate into Legendary because ordinary entries are exhausted. Three distinct choices; locked offer, no free reroll. Fewer choices if pool truly exhausted.

Probability at least one Legendary gate in three slots =1−0.995³=1.4925125%, provided slots/eligible candidates exist. This is not Blink probability: other Legendary entries compete. Luck does not affect card rarity. Capped augment entries leave the pool; unbounded abilities remain eligible. Exact no-target trigger/target tie/fallback details still need the ability matrix.

## 12. Interactions, damage, scoring and reset rules

- Damage, money and salvage must not double-count shared direct/splash hits, multiple overlap zones or repeated death checks.
- Fractional weapon/repair/shield values are required by the target; current Enemy and Player HP/damage code uses integers. This is an implementation gap, not proof fractional target values already work.
- Primary Payload/crit modifiers apply once to primary descendants. Automatic ability damage uses its own tuning. Clone inherited-primary and autonomous skill interactions require explicit snapshots.
- One roll per proposed shot/volley/pulse/tick avoids recursive crits. Current prototype crit is rolled in scaleAttackDamage; new-family integration must enforce the selected grouping.
- Shield state, Blink rescue, re-entry protection, post-hit invulnerability and death need one documented priority order. Blink before shield/hull is the proposal; already-negated damage should not consume it.
- Recheck death, shield, energy and mandatory cards after collisions before portal commit. A portal interaction cannot undo a same-frame death.
- Pause/card/hub freeze simulation timers, movement, attacks, statuses, boss schedules, drop lifetimes and shields. Input causing a transition must not also shoot/buy/interact in the destination.
- Same-expedition hub return preserves all run state and spawn/loot RNG. New run resets all manager state, charge, wallet, skills, cards, effects, portals, source flags, boss state and timers.
- No scene switch to show the hub/shop/pause/results inside a run. This prevents accidental expedition resets.
- Formation barricades are solids to the player; other enemies can overlap them in current code. Teleport/portal placement must respect legal geometry and avoid unintended sealed-region escapes.
- No file save of an unfinished run is currently selected. Leaderboards need independent mode/difficulty/rules identities and debug-run exclusion.

### Scoring and run endings

Current prototype basic/mid/debris score values are10/50/5. The previous planned deposit bonus, wave-clear bonus and Story speed bonus belong to the retired cargo/Story system. **No adopted replacement five-mode score formula exists.** Therefore there is no honest final score calculation to publish yet. Needed: combat/objective points, boss/source completion, retirement treatment, time tie-breaks, duplicate prevention, and anti-farming of adds.

Current source has an old timed picker; target field levels replace it. New Survival deadline, Boss required-add completion, Chaos boss cadence and Campaign source shutdown need same-frame precedence and victory transitions. “Resume” in the hub means return to the suspended field, whereas “Resume” in pause means unpause; different button wording would make this clearer.

## 13. Complete unresolved data checklist

| Area | Still needs adoption/content |
|---|---|
| Starter | Explicit normal shield grant/capacity and integration with equipment; confirm no hidden starting skills |
| Weapons | All draft damage/range/geometry values; precise card-to-family matrix; turn/homing/obstacle edge cases; live balance |
| Attributes | Exact eligible list/eight-paid caps and clamping; stat-source integration; high-speed/iframe balance |
| Abilities | Rarity weights, persistence decisions, trigger/target/range/tie rules, active overlap policy, high-rank budgets |
| Shield | One authoritative owner; complete hit absorption versus overflow policy; online regen hit delay; break/restoration interactions |
| Blink | Exact cooldown/protection/destination safety dimensions; all unresolved PREP-26 numerical rules |
| Return portals | Measured detection/spawn distances, geometry fallback, auto-fire/automatic-attack protection ordering, campaign checkpoint reconciliation |
| Economy | Actual spawn/collection income versus expense schedule; special stock accessibility; Luck adoption or removal |
| Difficulty | XP and HP curves, encounter multipliers and cap; solve early-return inversion |
| Enemies | Final heavy/elite profiles if retained; real mode population and spawn tables; common damage paths |
| Bosses | Final identities, HP, attacks, telegraphs, phases, adds, movement, rewards and source/objective linkage |
| Modes | Authored wave/time budgets, Boss return-energy access, Survival outcome precedence, Chaos timing, campaign content |
| World | Arena/hub geometry, camera-relative measurements, legal spawn and return locations |
| Results | New score formula, leaderboard schema/order, debug exclusion, victory/death/retirement transitions |
| UX | Distinct return-to-field versus unpause labels; exact shop/repair/battery previews; tutorial and settings |
| Verification | Representative whole-build and crowd tests, hardware performance, 30/144 FPS parity and reset checks |

Boss, layout and schedule content was previously owner-deferred. This report exposes the gaps for review; it does not invent final boss designs or silently cancel those deferrals.

## 14. Source references and verification limits

Numerical design: [game-design.md](../../context/game-design.md). Flow: [gameplay brief](../02-gameplay/gameplay.md). [Weapon tree](../07-upgrade-proposals/weapon-tree.md), [attributes](../07-upgrade-proposals/attributes-and-luck.md), [skills/rarities](../07-upgrade-proposals/automatic-skills-and-rarities.md), [return portals](../02-gameplay/return-portals.md), [open tasks](../06-task-list/tasks.md).

Inspected source: [Balance.hpp](../../src/Balance.hpp), [Player.cpp](../../src/Player.cpp), [Enemy.cpp](../../src/Enemy.cpp), [LowLevelEnemy.cpp](../../src/LowLevelEnemy.cpp), [MidLevelEnemy.cpp](../../src/MidLevelEnemy.cpp), [EnemyManager.cpp](../../src/EnemyManager.cpp), [SkillSystem.cpp](../../src/SkillSystem.cpp), [Game.cpp](../../src/Game.cpp). [Skills command reference](../../context/skills-commands.md) documents existing prototype mechanics.

This is source/document inspection plus arithmetic, not a full gameplay bug reproduction or playtest. “Code” means present in the inspected code paths, not exhaustive proof of every runtime interaction. Cosmetic-only values (font sizes, animation tint, audio levels) are outside this gameplay-stat review. Every currently documented combat/progression/economy category is covered; nonexistent enemy/boss/score data is explicitly open. Existing builds and targeted arithmetic/document checks can establish consistency, not balance.


## 15. Historical wave tables for comparison only

These are superseded Story/Endless proposals, not adopted schedules for the five requested modes. They are reproduced so their old numbers are visible during review, not to revive their boss roster or timing. Low/Mid/Heavy budget costs were 1/3/6; group spawns came from a radius-150 ring, with unaffordable selections falling back to Low. Normal waves ended after the budget and required enemies were exhausted. Old warning/arena radii were360/400 with pushback120; these are not confirmed new hub/portal geometry.

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

Retired score proposal: low/mid/heavy kill 10/50/120; debris5; deposit2 per scrap; wave-clear100×wave; no-damage wave250; old boss scores2000/5000; Story victory max(0,6000−5×seconds). Deposit bonuses are incompatible with the selected no-deposit economy. None of this supplies an adopted new five-mode score formula.
