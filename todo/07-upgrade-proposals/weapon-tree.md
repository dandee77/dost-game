# Mothership Weapon Tree

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

Field attributes strengthening attacks while cannon tiers remain mothership-only is still the proposed interpretation awaiting explicit review. PREP-27 stays open for exact burst/scatter/piercing/beam/flame compatibility; no eligible card may silently waste its effect.

Ideal solo output, crowd coverage and equal prices are starting comparisons. Fixed-seed moving-target/crowd/boss/card-scaling/performance playtests are required before a balance claim. Stat values remain drafts. Boss/schedule/layout/general-economy deferrals remain intact; game-title/boss naming is separate from the now-accepted weapon list.
