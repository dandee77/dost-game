# Mothership Weapon Tree

**25 October Q35:** Modifier cards require a supported benefit to the current equipped weapon/owned abilities; a future branch is insufficient. [Eligibility contract](attributes-and-luck.md#current-build-card-eligibility--q35-confirmed-25-october) preserves ranks across equipment changes. Exact card-to-node mapping remains PREP-22/27.

**23 October 2026. Accepted names and branching structure; numerical tuning is a draft.** The owner accepted this list/path after requesting choices at both T4 and T5, then asked for balanced stats. This supersedes the earlier six-family proposal. All stats, geometry, signatures and damage accounting are in [game design](../../context/game-design.md#23-october-weapon-stat-draft--accepted-tree-proposed-tuning). No source/assets changed.

## 1. Branches across different tiers

There are **1 / 3 / 5 / 7 / 10 nodes**, 26 total and ten final weapons. Some paths split at T4, some split at T5, and others stay straight.

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

## 2. Roles and refinements

| T3 specialty | Core function | T4 development |
|---|---|---|
| Rotary Cannon | Sustained rapid bullets | Assault Cannon improves output; T5 chooses speed or heavy impact |
| Focus Laser | Narrow tracking beam | Fusion Lance concentrates damage; Arc Projector changes to limited electrical chains |
| Railgun | Powerful penetrating shots | Siege Railgun improves straight-line penetration; Guided Launcher trades penetration/distance bonus for homing explosives |
| Flak Cannon | Short-range explosive pellets | Shrapnel Cannon improves coverage; T5 chooses fragments or a concentrated slug |
| Flamethrower | Short cone with temporary nonstacking burn | Inferno Projector improves direct flame and reach |

T2 identities remain Machine Gun (rapid medium-range bullets), Sniper Cannon (slower penetrating precision) and Shotgun (close pellet fan).

## 3. Final weapons

| T5 | Core identity | Automatic signature |
|---|---|---|
| Tempest | Fast sustained fire | Overdrive: enemy contact builds toward brief faster piercing fire |
| Ironclap | Slower heavy rounds | Hammerfall: periodic empowered round with collateral blast and knockback |
| Starbreaker | Concentrated beam | Core Rupture: sustained contact on one enemy causes a local explosion |
| Thunderweb | Connected crowd damage | Storm Network: enhanced discharge through existing chain links |
| Horizon Piercer | Long firing lanes | Terminal Shock: terminal shockwave damages enemies the projectile did not already hit |
| Sundering Lance | Priority-target precision | Fracture: consecutive hits add damage; gives up inherited penetration |
| Starfall | Guided bombardment | Pursuit Salvo: successful primary hits earn additional guided missiles |
| Shatterstorm | Wide close coverage | Fragment Bloom: secondary fragments cannot repeat damage on their parent's impact victim |
| Breachmaker | Tight heavy slug | Breach Wave: empowered impact adds damage and a blast cone behind the victim |
| Cinderheart | Sustained short flame | Flashover: direct exposure causes a local eruption without chain reactions |

These are primary-weapon effects, separate from automatic ability ownership. Focus Laser does not grant Plasma Beam, Arc Projector does not grant Chain Lightning, and Starfall does not grant Nuclear Missile.

## 4. Purchase and lifecycle

Shared incremental prices and the cumulative path cost are in [game design](../../context/game-design.md#23-october-weapon-stat-draft--accepted-tree-proposed-tuning). Every path crosses the same number of paid edges; no premium is added for choosing a split or a guided/beam weapon.

Show current node, legal children, role/range, exact cost, wallet afterward and sibling-lock warning. Revalidate parent/tier, branch, hub location, funds and transaction state at commit. Debit and equip once together; stale/double clicks cannot skip a tier or spend twice.

Changing cannon never heals hull/shield, charges Return Home, refreshes Blink, changes level or grants a combat ability. Live effects keep firing-time profiles/modifiers. Preserve remaining primary cooldown debt and retire the old loop at the hub; no extra shot/signature on Resume or upgrade. Branch/tier survives same-expedition hub visits. Death, quit or New Run clears all run-local weapon/effect state through existing owners.

## 5. Cards and balance review

**Current eligibility authority:** [Full card/capability contract](card-compatibility.md) completes typed P/AP/BR mapping and all field-card prerequisites, including beam penetration and signature circular blasts. The pattern-only table below remains a matching subset. Exact burst/fan/signature numerical composition remains PREP-27; this eligibility decision does not certify that implementation.

**Q40 confirmed, 25 October:** Keep compatible firing-pattern cards alongside the station's cannon tree. Cards modify the equipped primary; they never acquire/evolve a cannon, switch its branch or grant a similarly named automatic ability. Weapon tiers remain station-only. Apply Q35 usefulness filtering; preserve earned pattern ranks when changing weapons, leaving incompatible ones dormant until compatible again.

### Pattern-card compatibility by cannon node

The following are authored implementation defaults under the owner's delegated mapping work, not separately approved weapon balance. `Yes` means that discrete card supplies its normal earned pattern benefit; `No` hides its next field rank for that equipped weapon. Rapid Fire is the current extra-shot-per-burst card, not Overclocked Chambers' cooldown reduction. Use current catalog IDs; old Trigger Happy/Rapid Fire names in historical prototype tables are not separate new cards.

| Tier | Equipped weapon | Rapid Fire / burst | Scatter Shot | Broadside Cannons | Tail Gunner |
|---|---|---|---|---|---|
| T1 | Starter Cannon | Yes | Yes | Yes | Yes |
| T2 | Machine Gun | Yes | Yes | Yes | Yes |
| T2 | Sniper Cannon | Yes | Yes | Yes | Yes |
| T2 | Shotgun | Yes | Yes | Yes | Yes |
| T3 | Rotary Cannon | Yes | Yes | Yes | Yes |
| T3 | Focus Laser | No | No | No | No |
| T3 | Railgun | Yes | Yes | Yes | Yes |
| T3 | Flak Cannon | Yes | Yes | Yes | Yes |
| T3 | Flamethrower | No | No | No | No |
| T4 | Assault Cannon | Yes | Yes | Yes | Yes |
| T4 | Fusion Lance | No | No | No | No |
| T4 | Arc Projector | No | No | No | No |
| T4 | Siege Railgun | Yes | Yes | Yes | Yes |
| T4 | Guided Launcher | Yes | Yes | Yes | Yes |
| T4 | Shrapnel Cannon | Yes | Yes | Yes | Yes |
| T4 | Inferno Projector | No | No | No | No |
| T5 | Tempest | Yes | Yes | Yes | Yes |
| T5 | Ironclap | Yes | Yes | Yes | Yes |
| T5 | Starbreaker | No | No | No | No |
| T5 | Thunderweb | No | No | No | No |
| T5 | Horizon Piercer | Yes | Yes | Yes | Yes |
| T5 | Sundering Lance | Yes | Yes | Yes | Yes |
| T5 | Starfall | Yes | Yes | Yes | Yes |
| T5 | Shatterstorm | Yes | Yes | Yes | Yes |
| T5 | Breachmaker | Yes | Yes | Yes | Yes |
| T5 | Cinderheart | No | No | No | No |

Projectile patterns operate on the equipped weapon's primary root volleys: Rapid Fire adds earned burst volleys, Scatter adds earned projectiles to each root forward fan, and Broadside/Tail add their earned directional root volleys using that primary profile. Native pellets remain native pellets; do not replace Shotgun with a generic one-bullet cannon. Rotate a copied fan around its own firing axis. Guided missiles acquire within that emission axis's authored forward cone, not the mouse cone of a different side/rear volley. Each root shot retains its own travel/collision/damage; distinct earned projectiles may legitimately hit the same enemy.

Do not recursively apply pattern cards to signature missiles, secondary fragments, explosions, burn, arc links or other descendants. T5 signature counters/intervals remain one shared ledger per equipped cannon and count the existing successful primary trigger group once, never one per pellet, burst member, direction or victim. Pattern growth cannot create parallel signature counters or bypass minimum intervals. Snapshot profile/pattern ranks when firing; weapon/rank changes do not rewrite in-flight effects. A clone may copy the explicitly supported weapon geometry once under its separate ability contract; never apply pattern ranks again to geometry already copied or award primary signature progress from an automatic ability.

Continuous beams, arcs and flame cones do not gain invented bullets, additional beams/cones or chain links from these four cards. Compatible numeric attributes still work under their own rules. Armor Piercing is a separate compatibility mapping; this table does not make missiles penetrate before detonation or grant flame/arc target counts. No new fixed pattern-rank/count cap or silent deletion of earned projectiles is introduced. Exact burst/fan/count formulas, penetration, signature assignment under multi-projectile fire, extreme-load equivalence and measured balance remain PREP-27/PREP-14/T08/T10 work.

Written acceptance: Starter Cannon can offer Scatter; moving Machine Gun -> Focus Laser keeps the earned rank dormant and hides further Scatter offers; the weapon purchase cannot remove that rank or become a free respec. Guided Launcher side volleys keep their own aim cones; Shatterstorm's secondary fragments do not recursively scatter. These defaults specify the compatibility boundary, not completed runtime validation.

Ideal solo output, crowd coverage and equal prices are starting comparisons. Fixed-seed moving-target/crowd/boss/card-scaling/performance playtests are required before a balance claim. Stat values remain drafts. Boss/schedule/layout/general-economy deferrals remain intact; game-title/boss naming is separate from the now-accepted weapon list.
