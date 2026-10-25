# Beta field-card compatibility - 25 October 2026

**25 October composition adopted:** [Numerical cannon contract](weapon-composition.md) now completes burst/fan/bank/AP/signature composition. [Rank/load contract](../04-verification/numerical-and-load-contract.md) specifies all19 ability target overrides. Earlier remaining-PREP-27 wording below describes the pre-adoption checkpoint; actual handlers/tests/balance still remain T04/T08/T10.

Authored under delegated technical/content work while the owner is away. Q35 hides cards until useful, Q40 retains compatible pattern cards, Q37 excludes Legendary pity and Q38 requires a valid pick. This is the eligibility/data contract, not completed weapon behavior or balanced numerical composition. [Game design](../../context/game-design.md#25-october-card-capability-mapping) owns gameplay rules/numbers; exact burst/fan/signature-load tuning remains PREP-27.

## Capability mapping for all 26 cannon nodes

P enables the four primary projectile-pattern cards Rapid Fire, Scatter Shot, Broadside Cannons and Tail Gunner. AP enables Armor Piercing. BR means the equipped primary has an eligible circular damaging blast, including a real built-in signature; it does not make projectile collision radii larger. These are typed profile capabilities, not runtime switches on weapon names. A true capability requires its corresponding working runtime handler; missing promised handlers are implementation failures, not evidence the feature is delivered.

| Tier | Weapon | P | AP | BR | Geometry note |
|---|---|---|---|---|---|
| T1 | Starter Cannon | Yes | Yes | No | Direct bullet |
| T2 | Machine Gun | Yes | Yes | No | Direct bullet |
| T2 | Sniper Cannon | Yes | Yes | No | Direct penetrating shot |
| T2 | Shotgun | Yes | Yes | No | Nonexplosive pellet fan |
| T3 | Rotary Cannon | Yes | Yes | No | Direct bullet |
| T3 | Focus Laser | No | Yes | No | Finite piercing beam |
| T3 | Railgun | Yes | Yes | No | Direct penetrating shot |
| T3 | Flak Cannon | Yes | No | Yes | Contact/range-end explosive pellets |
| T3 | Flamethrower | No | No | No | Flame cone/burn, not a circular blast |
| T4 | Assault Cannon | Yes | Yes | No | Direct bullet |
| T4 | Fusion Lance | No | Yes | No | Finite piercing beam |
| T4 | Arc Projector | No | No | No | Authored chain links, not penetration |
| T4 | Siege Railgun | Yes | Yes | No | Direct penetrating shot |
| T4 | Guided Launcher | Yes | No | Yes | Missile detonates once |
| T4 | Shrapnel Cannon | Yes | No | Yes | Explosive pellets |
| T4 | Inferno Projector | No | No | No | Flame cone/burn |
| T5 | Tempest | Yes | Yes | No | Normal/Overdrive penetrating bullets |
| T5 | Ironclap | Yes | Yes | Yes | Direct shot and Hammerfall circular splash |
| T5 | Starbreaker | No | Yes | Yes | Beam and Core Rupture circular blast |
| T5 | Thunderweb | No | No | No | Enhanced existing chain links |
| T5 | Horizon Piercer | Yes | Yes | Yes | Penetrating shot and terminal circular shock |
| T5 | Sundering Lance | Yes | Yes | No | Native one-target precision; earned penetration remains a separate card benefit |
| T5 | Starfall | Yes | No | Yes | Explosive guided missiles |
| T5 | Shatterstorm | Yes | No | Yes | Explosive pellets; fragments do not inherit pattern recursion |
| T5 | Breachmaker | Yes | Yes | No | Slug plus directional cone, not a circular blast |
| T5 | Cinderheart | No | No | Yes | Flame cone plus Flashover circular eruption |

AP adds one allowed enemy contact per earned Armor Piercing rank to the native direct-projectile/beam allowance, never an obstacle/wall penetration. Each victim is hit at most once by that projectile/resolved beam tick; later contacts use the existing 60% direct-penetration falloff rather than recursively applying it. It does not add arc links, flame victims, explosive splash victims, signature targets or child-fragment penetration. A missile/explosive pellet still detonates once. Sundering Lance keeps its native one-contact base instead of inheriting Siege Railgun's base; paid/earned cards are not a free branch respec. Signature counters/secondary exclusions still apply; full multi-effect numerical validation remains PREP-27/T08/T10.

## Exact field-card eligibility families

Target arithmetic: current source has 14 augments plus 18 abilities. Remove Nano Repair from normal field eligibility, retain the other 13 augments, add Shield Detonation as the nineteenth ability, then add Luck and Blast Radius: 34 cards. Deprecated/debug aliases are not duplicate normal entries. Return Home is a world interaction. Reuse typed ability/augment ownership, not another string-dispatched catalog.

| Card / family | Eligible current-build condition | Scope |
|---|---|---|
| Weapons Payload, Critical Matrix, Overclocked Chambers, Inertia Impact | A supported normal primary profile is equipped; all 26 target profiles support these attributes | Primary-owned damage/crit/cadence/direct impact only; not a second automatic-ability multiplier |
| Rapid Fire, Scatter Shot, Broadside Cannons, Tail Gunner | Current profile P = Yes | Native primary projectile patterns; no new cannon node or recursive signature/child copies |
| Armor Piercing | Current profile AP = Yes | Direct primary traversal only |
| Reinforced Hull, Thruster Overdrive, Phase Shift, Gyro Control | Supported ship stat has a genuine next increment | Full HP, no nearby enemy or current protection does not make the structural increment useless |
| Blast Radius | Current primary BR = Yes OR at least one owned compatible damaging circular ability effect exists | Apply only to each explicitly eligible radius, once |
| Luck | Current rank below 10 | Legendary field acquisition/ranks only; no weapon prerequisite and no shop |
| Deflector Shield | Already-owned starter has a genuine next full-rank upgrade | Never require a card to obtain the starting shield; paid shop capacity is separate |
| Shield Detonation | Own Deflector and the ability handler supports its genuine break event | Starter satisfies prerequisite; does not require the shield to be currently broken/online |
| All other 17 combat abilities | A supported acquisition or next rank adds its defined capability | Unowned acquisition itself is useful; no limited active-slot inventory or weapon-family lock |

Primary offensive attributes do not grant their bonuses again to automatic abilities. Hologram Clone copies the selected native weapon tier/geometry at creation under its ability contract; it does not become a second player receiving field/paid primary ranks, primary signature charge or recursive pattern copies. Any explicitly supported cloned geometry must be snapshotted once, not derived again when the original weapon changes. Actual clone damage/cadence remains ability-rank tuning; native beam/arc/flame compatibility needs real T04 implementation.

Inertia Impact augments the supported direct primary impact, subject to the existing target's resistance/charge immunity. Repeated burn/splash/child events do not reapply that same primary knockback bonus. Intrinsic authored signature push remains its own effect. No card invents a new stun, boss vulnerability or material reward.

## Blast Radius effect tags

Eligible owned automatic effects: Radiant Halo damage circle, Corrosive Trail damage pools, Lightning Ring's damaging circular area, Shield Detonation blast, Nuclear Missile blast, Singularity damage zone and Armageddon blasts. Only the named damaging component grows: Singularity pull/acquisition and Lightning Ring's unrelated trigger/timing do not inherit the bonus. Keep radius snapshots and unchanged per-victim damage/target limits.

Not eligible: Scrap Magnet pickup radius, Repulsor push, Deflector capacity, Interceptor defensive radius, Laser Rings orbit/blade size, Chain Lightning reach, drone range, Plasma Beam cone/length, clone native projectile hitbox, Realm Breaker's currently excluded compound rift, Space Collapse erasure and Blink travel. A future explicit compound-effect mapping can revise its typed tags; do not silently infer them from a name or icon. A clone of an explosive primary is still governed by its separately supported native geometry, not a reason to double-apply player attributes.

## Filtering and lifecycle

Build the current eligible set before sampling: enabled/implemented catalog entry, structural prerequisite/capability, next rank/cap and a genuine supported effect. Never filter based on a temporarily empty field, cooldown debt, full HP or a temporarily offline shield. A future cannon choice or unowned ability cannot make a modifier useful now. Keep earned ranks across incompatible weapon upgrades, mark their current effect dormant and restore it when applicable; do not refund/reset/respec or offer further useless ranks.

Owned-ability rank updates preserve committed casts/debt. Existing offers stay locked across pause/focus/reopen; normal UI prevents weapon changes while a choice is unresolved. New offers recompute eligibility after a successful pick. Debug/stale mutation invalidates the transaction without charging/granting/rerolling; follow the chooser's diagnostic recovery contract. Shops reuse these facts for truthful previews and no-effect blocking without regenerating fixed stock.

Worked eligibility cases: Starter Cannon has no BR, so Blast Radius is hidden until an eligible area ability is learned. Flak immediately qualifies BR but excludes AP. Focus Laser qualifies AP and numeric primary buffs, but not the four pattern cards. Starbreaker qualifies BR through its real signature even before the next signature trigger. Breachmaker's cone alone does not qualify BR. Full-health hull and full starter shield still have useful capacity ranks. Rank-10 Luck is excluded independently of all weapon bits.

Written mapping only. Exact primary burst/fan/signature formulas and extreme-load correctness remain PREP-27/PREP-14; actual chooser/catalog/weapon/ability code and acceptance tests remain T03/T04/T08/T10.
