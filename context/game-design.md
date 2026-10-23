# Game Design

## 23 October field-return portal contract — design only

Owner selected random return portals in the combat map, generated once energy reaches at least 50% of the current maximum: **Easy 3 / Hard 2 / Impossible 1**, across all modes. F inside a portal requests travel; shield must remain online/positive and energy at least the current threshold at commit. Portals may be far away. A pointer detects them at roughly one visible screen, with exact detection/placement constants pending. Portals persist until used or run end; a broken shield leaves them visible/locked. A higher level can raise the energy threshold: existing portals remain visible, display missing energy and unlock once charge recovers without moving. Successful return retires the full set; the next half-charge readiness after Resume generates fresh random positions. See [return portals](../todo/02-gameplay/return-portals.md). This replaces planned manual Q Return Home, without changing existing energy-growth or full-charge-consumption defaults. No source/assets changed.

Selected re-entry: Resume returns the ship to the used portal's saved position with **2 combat seconds of damage protection**, ending immediately when the player fires. It restores no hull or shield and does not increase shield capacity. Protection/attack ordering, including auto-fire, must be explicit before implementation.

## 23 October economy decisions — design only

Owner selected higher weapon costs and a typical Swarm T5 target of **20–25 combat minutes**. Shared prices remain in 5-minute Survival, which normally finishes with a lower-tier build. These are pacing targets, not measured runtime results. Enemy-tier trade ranges and fixed salvage/XP/Return Home rewards do not increase implicitly.

| Selected economy rule | Value |
|---|---|
| T2 / T3 / T4 / T5 weapon purchase | 500 / 1500 / 4000 / 10000; cumulative 500 / 2000 / 6000 / 16000 |
| Numeric attributes and owned skill ranks | 5x their prior quoted prices; gains/ranks do not increase |
| Special skill first acquisition | 10x prior prices: Singularity 2400, Space Collapse 2800, Nuclear Missile 3200, Armageddon 4000 |
| Hull repair full quote Q | `ceil(missingHP * 10)` scrap; zero deficit means no charge |
| Affordable repair | B = min(wallet, Q); restore `missingHP * B / Q` for positive Q and B, exactly proportional to payment; fractional HP retained |
| Repair UI | Full Repair and Repair What I Can Afford, exact restored HP, debit and remaining wallet shown before purchase |
| Shield Battery | Five sizes: Tiny/Small/Medium/Large/XL supply 20%/50%/100%/150%/200% of upgraded normal capacity. Remove old overcharge, then add purchased charge: `newShield = min(currentShield, normalCapacity) + batteryCharge`. Starting prices 100/250/500/700/900 scale proportionally with normal capacity. Repeat paid purchases allowed; regeneration stops at normal capacity |
| Materials | Metal Fragments, Circuit Parts, Polymer Pieces, Power Cells; one wallet; enemy-tier values, visual/lore differences only |

Repair scales with actual missing HP rather than a flat visit fee or percentage-of-max surcharge. A full quote of 1000 and payment of 500 restores half the quoted missing hull. The same policy applies to any quoted deficit. Hull repair remains a 3-second atomic service; a battery purchase is a separate shop transaction. Power Cells are salvage, not Shield Batteries and not free shield restoration.

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

The weapon-only target requires average net saving of 16000/1500 to 16000/1200 = **10.67–13.33 scrap/s**; actual gross income must also pay repairs, skills and attributes. These are required budget rates, not a spawn schedule or proven earnings. At the base basic-enemy mean of 2, the weapon path represents 8000 basic-kill equivalents before other spending. Measure real mixed-enemy income and pickup collection before tuning. Older low repair/shop prices and the six-material proposal below are superseded; unrelated boss/layout/encounter decisions remain deferred.

## 21 October upgrade review ledger — revised by decisions above, no code changes

Read [upgrade review](../todo/07-upgrade-proposals/README.md). Confirmed: mothership-only cannon tiers, one branch per run, 25% purchased numeric attribute gains, shield cards retained, automatic combat skills, and Legendary incoming-hit Blink. Other values in this section are proposed for later confirmation, not tested balance. This section supersedes older full-rank numeric-augment shop and no-weapon-shop targets where they conflict. Current executable values remain in the prototype sections below.

Owner originally deferred boss designs, mode schedules, final names, hub/arena layout and general economy review. The 23 October request reopens material identity and shop/repair pricing only; unrelated deferrals remain. New upgrade costs below are local draft quotes to review later; existing reward ranges and fixed salvage remain; selected repair/shop prices are revised above.

### 23 October weapon stat draft — accepted tree, proposed tuning

The owner accepted the latest weapon names/tree and requested stats that support choosing any path. This replaces the earlier six-family graph and its T2/sniper draft. The tree is **1 / 3 / 5 / 7 / 10 nodes**, 26 total: branches occur at T3, T4 and T5, with straight paths where appropriate. Names refer to weapons; the game's final title and boss names remain deferred. Source code/assets are unchanged.

All values below are **TUNE, analytical starting values**. They are not implemented or certified balanced. The authoritative graph and qualitative identities are in [weapon-tree.md](../todo/07-upgrade-proposals/weapon-tree.md).

#### Reading the profiles

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

### Numeric attribute proposal numbers

| Attribute | Field-card increment | Purchased increment |
|---|---|---|
| Weapons Payload | +15 percentage points base-primary damage | +3.75 percentage points |
| Critical Matrix | +5 percentage points critical chance | +1.25 percentage points, probability capped at 100% |
| Overclocked Chambers | Cooldown multiplier 0.90 | Cooldown multiplier 0.975 |
| Reinforced Hull | +20 max/current HP | +5 max HP only, no healing |
| Thruster Overdrive | Move-speed multiplier 1.10 | Move-speed multiplier 1.025 |
| Gyro Control | Turn-response multiplier 1.10 | Turn-response multiplier 1.025 |
| Phase Shift | Ordinary hit-protection multiplier 1.10 | Ordinary hit-protection multiplier 1.025; no Blink extension |
| Inertia Impact | +50 knockback magnitude | +12.5 knockback magnitude |
| Shield Capacity | Deflector full rank adds +5 max plus its rank effects | +1.25 max only, no full rank/recharge/reboot benefit |

Each purchase's gain is 25% of the listed card increment; compounded modifiers need not make four purchases exactly equal one card. Keep actual derived previews. Preserve fractional shield values. Capacity formula: `20 + 5*(deflectorCardRank - 1) + 1.25*paidCapacityPurchases`. Current HP/shield and cooldown debt are preserved on paid capacity increases.

Proposed eight paid purchases per numeric attribute per run, owner-selected price `200 + 100*n` (5x prior draft) where n is its prior paid count: 200/300/400/500/600/700/800/900, total 4400. Persistent augment card ranks retain their existing cap 10; paid counts are independently capped and add their specified benefit. Deflector card rank remains an ability rank. Discrete Rapid Fire/Armor Piercing/Scatter/Broadside/Tail Gunner cards are field-only in the draft; no fractional projectiles or duplicate full-rank shop route.

Owner-selected 5x owned-rank pricing: ordinary combat abilities use `500 + 250*r`; the existing four special abilities use `1000 + 375*r`; Deflector is excluded from whole-rank rows. Proposed owned Blink pricing is scaled to `3000 + 750*r`, first upgrade 3750; its inclusion/acquisition contract stays under review and first acquisition remains field-only. Owner-selected 10x special acquisition prices: Singularity 2400, Space Collapse 2800, Nuclear Missile 3200 and Armageddon 4000; stock rules are unchanged.

### Luck proposal numbers

| Quantity | Proposed value |
|---|---|
| Source | Workshop-only Support node, not a field card in the initial recommendation |
| Rank | 0-5 |
| Quality-check chance | `0.10 * rank`, capped at 0.50 |
| Success | Keep higher of independent base/comparison uniform trade rolls inside the existing tier range |
| Eligible reward tiers | Low/basic, mid/ranged, high/heavy only; not bosses/debris/excluded causes |
| Prices, if Luck adopted | Proposed 5x support-price alignment: `400 + 200*n`; 400/600/800/1000/1200, total 4000; Luck itself and this support-node interpretation remain under review |
| Basic mean at Luck 0 / 5 | 2 / 20/9, approximately 2.222 at rank 5 |

Assign final reward and Luck snapshot at spawn using isolated base-loot and Luck RNG state. Currency spending, later Luck purchase, kill cause, pickup merging or collection cannot reroll existing assigned values. Salvage, Return Home, score, card rarity and material family are unchanged by Luck. Existing uniform enemy range tables below describe the base roll; Luck intentionally biases the final eligible distribution while preserving the same inclusive bounds.

### Blink and rarity proposal numbers

| Quantity | Proposed value |
|---|---|
| Blink grade | Legendary, confirmed |
| Cooldown at rank r | `max(12, 30 * 0.95^(r-1))` combat seconds; snapshot on successful activation |
| Blink protected window | 2 seconds, fixed; no Phase Shift multiplication |
| Travel maximum | Existing 35 at rank 1, +15% base/rank through rank 5, capped 56 |
| Destination search | At most 24 candidates: eight stable headings at one-third/two-thirds/full travel; legal visible-screen and arena checks |
| If no safe destination | No teleport/protection/cooldown consumption; resolve ordinary hit |
| Field rarity nominal weights | Common 45, Uncommon 30, Rare 18, Epic 6.5, Legendary 0.5 percent |
| Legendary gate | Independent 0.005 per offered slot; no ordinary-tier exhaustion promotion |
| Three-slot Legendary gate probability | `1 - 0.995^3` = 0.014925125, approximately 1.49% |
| Proposed drone persistence | Persistent until destroyed; per-missing-slot respawn uses existing 20 combat seconds |

The [skill/rarity roster](../todo/07-upgrade-proposals/automatic-skills-and-rarities.md) assigns all 19 combat abilities and 13 augments. Blink's direct-hit interception precedes shield/hull damage; already-negated hits and non-spatial status ticks do not trigger it. Ordinary card selection renormalizes only the non-Legendary tier weights over eligible entries. Luck does not alter these weights.

## 21 October material and campaign alignment (proposed; not implemented)

[Scrap types](../todo/03-economy/scrap-types.md) now uses the owner's **four** selected labels: Metal Fragments, Circuit Parts, Polymer Pieces and Power Cells, superseding the six-family draft. All feed one shared wallet, with enemy-tier reward values and visual/lore differences only. Existing trade ranges, fixed salvage and debris yields are unchanged. Weapon/upgrade/repair prices are revised by the 23 October decisions; older 20/21 October prices are superseded. Single-family merged pickups retain the label; different families display Mixed Salvage with conserved trade/salvage totals. There are no per-family wallets, recipes, conversion rates or statistics in the selected minimum scope.

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
| Successful field-return portal use | Drain current charge to zero; no wallet/XP cost |
| Level-up capacity adjustment | Preserve absolute charge; recalculate maximum/threshold |
| Low/mid salvage progress | Fixed 2 / 5; currency rolls listed separately below |
| Owned standard rank r -> r+1 price | `500 + 250*r`; rank 1 -> 2 costs 750 |
| Owned rare rank r -> r+1 price | `1000 + 375*r`; rank 1 -> 2 costs 1375 |
| Rare acquisition prices | Singularity 2400; Space Collapse 2800; Nuclear Missile 3200; Armageddon 4000 |
| Rare stock | Three distinct unowned entries from those four, fixed for the run; fewer if insufficient eligible entries |
| Hull repair | `ceil(missingHP * 10)` Trade Scrap; restores quoted hull after 3 uninterrupted service seconds |
| Repair What I Can Afford | For positive deficit/full quote Q, spend B = min(wallet, Q), restore `missingHP * B / Q`; preserve fractional HP; zero wallet buys no healing |
| Shield Battery | Separate shop purchase; remove old overcharge and add supplied charge using the five-size contract above; no paid recharge berth service |
| Service separation | Hull repair at the berth; Shield Battery purchased separately at the shop; no automatic combined debit |

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

Paid hull service clears harmful player statuses only on completion of actual healing. Debit and hull healing commit atomically after 3 seconds; cancel means no cost/healing and pause freezes the job. Zero wallet permits launch/resume but no free repair. At 10 scrap per missing HP, missing 37 quotes 370; wallet 185 buys 18.5 HP, exactly half the deficit for half the quote. Preserve fractional HP so a small paid repair is not rounded away. Buying a Shield Battery is a distinct shop transaction; it does not heal hull or grant a Deflector rank.

**Older shop target, superseded for numeric augment grants and cannon access by the 21 October upgrade review:** the shop sells all eligible owned standard ranks, owned rare ranks and the four rare acquisitions above. No standard first acquisition, weapon shop, consumable, reroll or permanent unlock is added. Paid Reinforced Hull grants max HP only; the field card retains its max/current-HP increase. Paid shield capacity never refills current points. Pass acquisition source through the same rank API and display the real resulting effect.

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

Proposed starter Deflector rank 1 guarantees the utility has a normal-play shield. Rank increases preserve current points and elapsed cooldown debt; no free revival. Shield Batteries use the selected five-size shop contract above; normal field return requires an online positive shield. Hull-only repair does not restore shield or change its reboot. Hull has no passive field regeneration; Reinforced Hull's max/current-HP exception applies to free field cards only.

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
