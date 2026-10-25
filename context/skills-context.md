# Skills & Upgrades Context

**25 October adopted rank data:** [All19 target ability overrides and safety](../todo/04-verification/numerical-and-load-contract.md#ability-rank-defaults-and-continuations) adopts existing base/growth rows where compatible and explicitly replaces timed shield/rings/drone, global magnet and manual Blink behavior. [Cannon composition](../todo/07-upgrade-proposals/weapon-composition.md) keeps primary attributes/signatures separate. These written defaults complete remaining numerical context, not source conversion or performance/balance acceptance. Prototype descriptions below remain historical/current-source evidence.

**25 October written card adoption:** [34-entry catalog/selection](../todo/07-upgrade-proposals/beta-card-selection.md) and [26-node capabilities](../todo/07-upgrade-proposals/card-compatibility.md) now define rarity, acquisition, eligibility and deterministic chooser/stock contracts. Old candidate/unknown-mapping statements below are historical; combined-fire numerical/performance and actual source conversion remain open.

**Q45 HUD target:** [Compact owned-ability icons](ui-rules.md#compact-automatic-ability-hud--q45-confirmed-25-october) show genuine rank/cooldown/active/persistent state for the 19-entry target. Reuse existing SkillSystem data, add accurate read-only shield/droid timing as needed, and remove manual-Q prompts from the beta target. Prototype commands/text below are historical/current-source reference, not this HUD's delivery.

## Current target - 25 October; distinct from the prototype below

[Target matrix](../todo/02-gameplay/automatic-targeting.md) covers 19 automatic/persistent combat abilities under Q33: abilities choose their own enemies while the primary weapon follows mouse aim. No manual Return Home skill; F interacts with world portals. Blink is Legendary incoming-hit rescue; its authored 30-second base/12-second floor, legal 24-candidate search and fixed 2-second protection are specified in game-design.md. Q34 confirms nearest valid enemy without boss bias for single-target attacks, with stable ID ties; group/droid policies remain separate. Existing source still has 18 prototype abilities and manual/debug behavior; commands below describe that actual baseline, not completed conversion.

[Weapon tree](../todo/07-upgrade-proposals/weapon-tree.md) retains mothership-only cannon tiers/one branch per run. [Attributes/Luck](../todo/07-upgrade-proposals/attributes-and-luck.md) uses quarter-strength paid numeric gains and full field-card gains. Luck is Legendary, field-only, rank 10 maximum and scrap-only; Epic Blast Radius brings the final target to 34 cards (19 abilities + 13 original attribute/pattern entries + Luck + Blast Radius). Deflector starts owned at rank 1; paid capacity does not grant full ranks/refill it. Owned automatic skill ranks retain their separate shop rules; precise compatibility/rarity integration remains open.

These current target rules supersede older workshop-Luck/manual-Return/capped-slot text. No code, catalog implementation or debug command changed here. Remaining rarity/compatibility/high-rank work stays open; do not rebuild delivered prototype systems or claim conversion from a document edit.

## 20 October target history - superseded where noted above

The older gameplay draft introduced automatic/persistent conversion, persistent Deflector, radius magnet and Nano Repair -> Shield Detonation. Its 32-card/manual-Return-Home assumptions are superseded by the current 34-card/world-portal target above. Remaining prototype descriptions are evidence of existing behavior, not instructions to restore those retired features.

Owner confirmed normal level upgrades occur in the field and delegated shop inventory/prices. Selected shop: targeted owned ranks plus rare Singularity, Space Collapse, Nuclear Missile and Armageddon acquisition. Use the same rank/effect data and explicit acquisition source: paid Reinforced Hull increases maximum HP without healing; its field card retains max/current HP gain. Paid shield ranks do not refill. Q is proposed for Return Home; no manual combat quick-swap slot is planned.

The descriptions below are the source skill brief/current prototype reference. Where they describe global vacuum, Nano Repair or manual actives, the dated handoff describes the future replacement; skills-commands.md still documents the current executable.

Context file for all player skills in the game. It covers only the skill systems: the augment cards and the active abilities. Other project topics are intentionally left out.

**Game type:** 2D top-down space shooter, swarm-style. The player's ship fights large crowds of enemies, so most skills are built around crowd control, area damage, survivability, and scaling the ship's firepower.

**Sources:** the augment screenshot (existing augments) and `game_skills_design.md` (passives and actives). The former passives are now augments, and overlapping skills were merged, keeping the better-named version (see Section 5).

---

## 1. Skill System Overview

There are two groups of skills:

| Group | Count | How it works | Player involvement |
|---|---|---|---|
| **Augments** | 14 | Cards the player picks. Always on once picked. Permanently change the ship's stats and projectile behavior. | Pick a card |
| **Actives** *(working name, see Section 6)* | 18 | Triggered or deployed effects. Offensive, defensive, or utility. Need timing and positioning. | Timing and positioning matter |

**Total: 32 skills.**

**Design intent**
- **Augments** make the ship stronger all the time (the "build" backbone).
- **Actives** create the big moments: clearing swarms, escaping danger, controlling space.

---

## 2. Augments (14)

Augments are the former existing augments (4 kept) plus the former passive upgrades (10). They run continuously once picked.

### 2.1 Offense Stats

| Augment | Stat | Effect |
|---|---|---|
| **Weapons Payload** | Damage | Scales up the base damage of all standard attacks. |
| **Critical Matrix** | Critical Chance | Raises the chance for attacks to hit weak points, dealing a large damage multiplier. |
| **Overclocked Chambers** | Attack Speed | Shorter cooldown between standard attacks, for a faster, smoother firing animation. |
| **Rapid Fire** | Attack Rate | Raises the total number of bullets fired per second, for heavier suppressive fire. |

### 2.2 Survivability

| Augment | Stat | Effect |
|---|---|---|
| **Reinforced Hull** | Max Health | Raises maximum structural integrity, so the ship survives more hits. |
| **Nano Repair** | Healing | Instantly heals a portion of your HP. |
| **Phase Shift** | Invincibility | Extends invincibility duration after taking damage. |

### 2.3 Mobility

| Augment | Stat | Effect |
|---|---|---|
| **Thruster Overdrive** | Movement Speed | Faster navigation and easier dodging of incoming fire. |
| **Gyro Control** | Rotation Speed | Increases rotation speed for faster turns. |

### 2.4 Projectile Behavior

| Augment | Effect |
|---|---|
| **Armor Piercing (Pierce)** | Projectiles travel through multiple targets instead of stopping at the first. Very efficient against dense swarms. |
| **Inertia Impact** | Bullets briefly knock enemies back. |

### 2.5 Weapon Patterns

| Augment | Direction | Effect |
|---|---|---|
| **Scatter Shot** | Forward spread | Primary weapon fires multiple projectiles in a wide forward-facing spread for better area coverage. |
| **Broadside Cannons (Side Shot)** | Left and right | Lateral turrets fire perpendicular to the ship, covering the flanks. |
| **Tail Gunner (Rear Shot)** | Behind | Rear-facing cannon fires backward automatically, protecting against ambushes and trailing enemies. |

---

## 3. Actives (18)

*"Actives" is a working name. See Section 6 for naming options.*

Actives need strategic timing and positioning. The grouping below is a suggested organization for readability. The source document lists them without categories.

### 3.1 Area Damage / Offensive Burst

| Ability | Description |
|---|---|
| **Nuclear Missile** | Launches a high-yield warhead with a massive blast radius. Instantly obliterates all standard enemies caught in the fallout. |
| **Armageddon** | Calls down a relentless, screen-wide barrage of missiles. Continuous explosive destruction for the duration of the skill. |
| **Radiant Halo** | Emits a localized burst of energy that severely damages all hostiles immediately around the ship. |
| **Space Collapse** | Collapses reality in a designated target zone and banishes everything inside. **Drawback:** enemies are erased from reality, so they drop **zero scrap**. |

### 3.2 Orbiting / Aura Damage

| Ability | Description |
|---|---|
| **Laser Rings** | High-speed spinning laser blades orbit the ship. Very dangerous to enemies that breach the immediate perimeter. |
| **Lightning Ring** | Electrified aura around the ship. Enemies touching the perimeter take shock damage and are temporarily stunned. |

### 3.3 Directed / Chain Damage

| Ability | Description |
|---|---|
| **Plasma Beam** | Sustained, superheated cone of plasma in front of the ship. Melts through heavily armored targets. |
| **Chain Lightning** | High-voltage arc that automatically bounces between multiple grouped enemies, chaining damage across formations. |

### 3.4 Zone Control

| Ability | Description |
|---|---|
| **Singularity (Black Hole)** | Gravitational anomaly that violently pulls nearby enemies into its center, crushing them until they disappear completely. |
| **Realm Breaker** | Slices open a lingering spatial rift. Deals extreme continuous damage to enemies inside and swallows all incoming enemy projectiles, acting as a defensive wall. |
| **Corrosive Trail (Acid Trail)** | Vents toxic exhaust behind the ship. Enemies flying through it take damage over time, move slower, and have reduced combat stats. |

### 3.5 Defense and Crowd Pushback

| Ability | Description |
|---|---|
| **Deflector Shield** | Energy barrier that absorbs a set amount of incoming damage or completely negates a specific number of hits. |
| **Point-Defense Interceptor** | Automated countermeasures that track and shoot down incoming enemy projectiles before they hit. |
| **Repulsor Pulse** | Kinetic shockwave on a recurring timer. Pushes enemies back and creates breathing room when swarmed. |

### 3.6 Mobility and Decoys

| Ability | Description |
|---|---|
| **Blink Drive (Short TP)** | Short-range, instantaneous teleport. For escaping death-traps, dodging boss attacks, or repositioning. |
| **Hologram Clone** | Hard-light duplicate of the ship that draws enemy aggro and mimics the primary weapon's fire. |

### 3.7 Summons and Utility

| Ability | Description |
|---|---|
| **Combat Drone (Robot Pet)** | Autonomous robotic companion that independently targets, chases, and destroys hostiles. |
| **Scrap Magnet** | Electromagnetic field that automatically vacuums up all dropped scrap and resources across the battlefield. |

---

## 4. Quick Reference

### Augments (14)
Weapons Payload, Critical Matrix, Overclocked Chambers, Rapid Fire, Reinforced Hull, Nano Repair, Phase Shift, Thruster Overdrive, Gyro Control, Armor Piercing, Inertia Impact, Scatter Shot, Broadside Cannons, Tail Gunner

### Actives (18)
Laser Rings, Deflector Shield, Lightning Ring, Blink Drive, Nuclear Missile, Space Collapse, Radiant Halo, Repulsor Pulse, Point-Defense Interceptor, Scrap Magnet, Chain Lightning, Hologram Clone, Combat Drone, Plasma Beam, Corrosive Trail, Singularity, Realm Breaker, Armageddon

### Skills With Special Rules or Drawbacks
- **Space Collapse:** enemies killed by it drop no scrap.
- **Singularity:** enemies are crushed until they disappear completely. The source does not say whether they drop scrap.
- **Realm Breaker:** swallows enemy projectiles, so it doubles as defense.
- **Corrosive Trail:** applies three effects: damage over time, slow, and reduced enemy combat stats.
- **Lightning Ring:** applies stun in addition to damage.

---

## 5. Merged Duplicates

These 5 original augments overlapped with other skills. The better-named version was kept.

| Removed | Kept | Reason |
|---|---|---|
| Scatter Shot (old augment) | **Scatter Shot** | Same name and effect; kept version has the fuller description. |
| Piercing Rounds | **Armor Piercing (Pierce)** | Same effect; fits the ship-themed naming. |
| Speed Demon | **Thruster Overdrive** | Same effect (movement speed); fits the ship-themed naming. |
| Rapid Fire (old augment, +10% attack speed) | **Overclocked Chambers** | Same stat (shorter time between shots). Also removes the duplicate "Rapid Fire" name. |
| Trigger Happy | **Rapid Fire** | Both mean more shots per second. |

---

## 6. Naming the Actives (pending decision)

Now that the passives are augments, the second group needs a clear name. Options:

| Name | Fit |
|---|---|
| **Abilities** | Simple and universal. Players understand it immediately. |
| **Modules** | Ship-themed, like installing equipment. Matches the sci-fi setting. |
| **Special Weapons** | Clear, but does not fit non-weapon actives like Scrap Magnet, Blink Drive, or Deflector Shield. |
| **Ship Systems** | Ship-themed and covers weapons, defense, and utility. |
| **Protocols** | Techy and unique. Less obvious to new players. |
| **Skills** | Very clear, but conflicts with this file's use of "skills" for everything. |

---

## 7. Open Questions

1. **Active group name:** pick from Section 6.
2. **Overclocked Chambers vs. Rapid Fire** are still close to each other. One shortens the cooldown between shots, the other raises bullets per second. Consider merging or clearly differentiating them.
3. **No numbers are defined yet:** values, cooldowns, durations, radii, damage, upgrade levels, and how many augments and actives the player can hold at once are all unspecified.
4. **How the player gets each skill** (cards, shop, drops) is not specified. Augments were originally cards, but it is unclear whether actives come from the same cards.
5. **Singularity and scrap:** do enemies it crushes drop scrap, or do they behave like Space Collapse?
6. **Activation:** it is not defined which actives are manual (button press) vs. automatic (timer or auto-trigger). Examples that read as automatic: Repulsor Pulse (recurring timer), Point-Defense Interceptor, Scrap Magnet, Combat Drone.
7. **Balance risk:** Nuclear Missile, Armageddon, and Space Collapse are very strong against swarms. Cooldowns and rarity will matter.

---

## 8. Changelog

| Date | Change |
|---|---|
| 17 Oct 2026 | Initial draft from the augment screenshot and `game_skills_design.md`. |
| 17 Oct 2026 | Removed 5 overlapping augments (Scatter Shot, Piercing Rounds, Speed Demon, Rapid Fire, Trigger Happy), keeping the better-named versions. |
| 17 Oct 2026 | Converted the 10 passives into augments (now 14 total, regrouped by role). Actives name left pending, with options listed. |
