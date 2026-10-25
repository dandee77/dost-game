# Scrap Types and Recovery Contract

**Updated 25 October 2026. Owner-selected four material types and one wallet; documentation only.** Owner selected Metal Fragments, Circuit Parts, Polymer Pieces and Power Cells, superseding the earlier six-family proposal. All feed one shared scrap wallet; none is required for a particular weapon. Material labels use the existing enemy-tier reward values, with visual/lore differences only. Appearance-matched written profile coverage is specified below; runtime/art acceptance remains open. Existing trade/salvage accounting stays authoritative in [game design](../../context/game-design.md) and [gameplay](../02-gameplay/gameplay.md). Weapon costs are now 500/1500/4000/10000 (total 16000); attributes/owned ranks use the selected 5x scale, special acquisitions 10x, and hull repair costs 10 scrap per missing HP.

**25 October written coverage / PREP-20:** The tables below adopt appearance-matched assignments for all ten existing debris kinds, all three low-enemy variants, ranged/heavy content and the four planned bosses. Existing sprite inspection corrects the former Canister/Thruster assignments to METAL and identifies the dish's visible reflector as METAL. Planned boss assignments are art instructions, not evidence of produced assets. Typed metadata, matching visuals in play and reward integration remain T02/PROJECT-07/T10 work.

**Upgrade-review note:** [Adopted attribute/Luck contract](attribute-and-luck-contract.md) defines the isolated spawn-time trade-quality comparison without changing material families or inclusive reward bounds. Uniform amounts below remain base rolls; salvage/no-drop exclusions remain. New cannon/attribute purchases use their current adopted contracts. Older material/battery review wording is historical; this written source inventory does not certify live economy or visuals.

## 1. One economy, recognizable materials

A pickup has a **material family**, a **trade value**, and a **salvage value**. The family describes what was recovered. Trade value enters the shared wallet used by repairs and the shop. Salvage value independently advances field leveling and Return Home.

The first version does not require collecting particular materials to buy a skill or repair hull. There are no separate material wallets, exchange buttons, material inventory slots, crafting recipes, refinery timers or additional taxes. This keeps normal field upgrades immediate and avoids a player being unable to repair despite owning enough trade scrap.

**Example:** a basic enemy's recovered alloy pickup can contain 3 Trade Scrap and 2 Salvage. An electronic pickup from a mid-tier enemy can contain 4 Trade Scrap and 5 Salvage. The material names do not multiply either reward. Buying a 750-scrap skill rank spends 750 from the one wallet regardless of which families produced it.

### Biological-enemy continuity

The revised enemies are living waste-eaters inside scavenged shells. Their altered intake gathers material indiscriminately; digestible fractions feed the body, while retained fragments are bound into external armor. Recoverable scrap comes from that nonliving shell, carried material and attached equipment. This explains why scrap survives the creature's destruction without implying that every material was digested or converted into tissue. Sealed collection separates it from biological remains; tissue is not a resource or a required harvesting action. Existing red pickup effects are resource feedback, not blood. Material identity is not a mutation cure or free service. The four chosen labels do not change reward amounts; owner selected enemy-tier values with visual/lore distinctions only.

## 2. Four owner-selected material types

| ID for later data | Player-facing label | Recognizable source | Colony use in the fiction | Suggested visual distinction |
|---|---|---|---|---|
| METAL | Metal Fragments | Plates, pipes, structural metal | Hull patches, brackets and repairs | Bent plate silhouette |
| CIRCUIT | Circuit Parts | Boards, sensors, dishes, guidance assemblies | Targeting, control and skill-system repairs | Circuit/connector silhouette |
| POLYMER | Polymer Pieces | Insulation, cable jackets, seals, durable housings | Seals, insulated cabling and protective layers | Coiled strip silhouette |
| POWER | Power Cells | Batteries, stored-energy units, power assemblies | Colony power recovery and powered equipment | Cell/terminal silhouette |

These are material labels, not separate currencies or rarity tiers. Power Cells do not grant shield charge. Owner selected no material-specific value/rarity effects; existing enemy-tier reward ranges remain authoritative. The workshop still prices items in Trade Scrap. Existing destruction art and red homing orbs remain accepted; these suggested silhouettes are later optional pickup/UI art, not permission to recolor or regenerate assets now.

## 3. Assignment rules

Owner-selected assignment rule: use the dominant recoverable material visible in the authored enemy/debris profile. Adopt the following beta mappings. Material assignment does not need a new random stream. Randomness remains in the existing uniform inclusive enemy **trade amount**, followed by the separate eligible Luck comparison. A family never changes its reward tier.

| Existing debris kind / typed source | Adopted dominant family | Visible rationale |
|---|---|---|
| Clump / DEBRIS_CLUMP | METAL — Metal Fragments | Mixed compact metal in assets/textures/debris.png |
| Pipe / DEBRIS_PIPE | METAL — Metal Fragments | Tube and fittings |
| Wing / DEBRIS_WING | METAL — Metal Fragments | Metal wing structure |
| Canister / DEBRIS_CANISTER | METAL — Metal Fragments | Dented cylindrical casing; do not invent a dominant polymer lining |
| Dish / DEBRIS_DISH | METAL — Metal Fragments | Visible reflector and supporting frame; no visible circuit payload required |
| Coil / DEBRIS_COIL | POLYMER — Polymer Pieces | Recoverable cable insulation and protective jackets |
| Tank / DEBRIS_TANK | METAL — Metal Fragments | Reinforced vessel casing |
| Thruster / DEBRIS_THRUSTER | METAL — Metal Fragments | Bell, ribs and frame; not a depicted battery |
| Beam / DEBRIS_BEAM | METAL — Metal Fragments | Structural truss |
| Hull / DEBRIS_HULL | METAL — Metal Fragments | Layered metal plating |

This table classifies a usable fraction, not the whole mass of the object. It does not change any existing per-kind fixed debris reward. If art clearly contradicts a label, revise the profile here before production rather than inventing an extra loot system.

### Enemy and guardian coverage

Enemy mapping follows each visual variant, not health/reward tier. Use the same family for a profile whether it appears naturally, as a Campaign wave enemy or as a reward-eligible boss-owned add. Add score exclusions do not remove its ordinary material/Salvage reward. The basic variants share one reward tier despite their different shells.

| Beta profile / visual key | Family | Evidence or future art instruction |
|---|---|---|
| Tin-can basic / low_level_enemy1 | METAL | Existing crushed can, lid and metal claws |
| Battery basic / low_level_enemy2 | POWER | Existing cell casing and terminals |
| Monitor basic / low_level_enemy3 | CIRCUIT | Existing screen, readout and control housing |
| Ranged / mid_level_enemy | METAL | Existing fighter frame/equipment plates; retain unless replacement is explicitly assigned |
| Heavy / planned armored form | METAL | Teammate keeps layered equipment plates dominant; not a new generated asset here |
| Shellback / planned boss | METAL | Broad overlapping compressed panels |
| Coilmaw / planned boss | POLYMER | Cable jackets and insulated loops remain visually dominant |
| Brood Hauler / planned boss | METAL | Broken cargo shell and release-hatch framing |
| Nestheart / planned boss | CIRCUIT | Teammate shows recovered control assemblies/readouts in damaged recovery infrastructure, with its organism enclosed |

Nestheart uses CIRCUIT in every mode, with the Campaign-final reward tier only where the final encounter contract selects it. Source completion is independent of material and of whether any reward drops. No material is a mutation cure, live tissue, shield battery or instant energy reward. Equal representation of the four families is unnecessary because they have identical economy semantics.

### Metadata ownership and exceptions

Later implementation adds a typed material field to the existing debris/profile/reward records; keep DebrisKind/DEBRIS_INFO and the existing enemy/reward owners, not another material manager. Resolve the family from the selected visual/profile once at spawn, store it beside assigned trade/Salvage and preserve it through death, suspension and collection. Use explicit enums/table fields, not texture-name string switches in update code.

**Prototype mismatch to resolve during T02:** LowLevelEnemy currently selects textureName randomly and independently selects randomEnemyTextureIdx for the actual Animator sprite. Inferring the material from textureName can therefore disagree with what the player sees. Future code must choose one variant identity and derive both its Animator key and material from that identity. This source inspection records a future integration requirement; no constructor or RNG behavior is changed by this document.

Barricade asteroids, cleanup/despawn and Space Collapse victims have no material drop, even if their visible surface resembles metal. Do not fabricate zero-value pickups or a separate material credit. Boss adds use their own ordinary profile, not the guardian's family. An elite has no enabled beta profile here: enabling one later requires an explicit visible family and reward contract first. Disabled/debug or genuinely unknown profiles may use METAL as a diagnostic fallback and must appear in the content-review log; no enabled beta row above relies on that fallback. Keep unrelated legacy art out of the normal profile registry.

### Written coverage and later acceptance

The inventory covers 10/10 DebrisKind values (excluding KIND_COUNT), 3/3 current basic sprites, the existing ranged profile, one planned heavy profile and 4/4 planned guardian identities. Visually checked the existing debris/low/ranged sprites; planned heavy/boss rows are binding production instructions until assets exist. Preserve accepted animation dimensions/frame counts and record any future asset provenance separately. A deliberate future silhouette change must update this table before changing family metadata.

Later acceptance checks each source's actual sprite against its stored family, including many repeated basic spawns to expose the two-selector mismatch. Confirm identical numeric rewards across families, no material RNG draws, same-family and mixed merges, split conservation, no-drop causes and station suspension. Written coverage closes PREP-20 only; it does not close T02, art delivery or runtime acceptance.

## 4. Reward accounting stays unchanged

| Enemy reward tier | Random Trade Scrap | Fixed Salvage |
|---|---:|---:|
| Low/basic | 1-3 | 2 |
| Mid/ranged | 3-7 | 5 |
| High/heavy | 8-12 | 10 |
| Elite, only if authored | 15-25 | 20 |
| Standard boss | 120-180 | 100 |
| Campaign final boss | 200-300 | 200 |

Mirror of game-design.md, not a second tuning authority. Roll the trade amount once at enemy spawn and store it with the fixed salvage amount and material family. Material does not reroll on damage, death, return, pickup, merge or panel opening. No reward multiplier for material, difficulty, rarity, shop purchases or contamination density is introduced.

- Ordinary debris retains its fixed per-kind values and accepted multi-orb destruction sequence.
- Reward-eligible deaths release the assigned value. Collection credits it once; killing alone does not make it spendable.
- Barricades, cleanup, despawn and Space Collapse generate no trade, salvage or material credit. Singularity retains ordinary eligible rewards.
- If a pickup combines sources, preserve both numeric totals. Never average the rewards or discard a family to satisfy a pickup cap.
- Split debris orbs retain the parent's family. Divide totals exactly using the existing value-conserving path; visual orb count is not reward count.
- A family is credited only alongside its collected reward. No separate “material acquired” event can double the wallet.

## 5. Bounded mixed pickups and records

**Selected minimum representation:** a single-source pickup stores its family plus the two authoritative reward totals. On merge, retain the family if both inputs share it; otherwise set the presentation label to **Mixed Salvage**. An already mixed pickup stays mixed when merged again. Add trade and salvage totals independently. A mixed label carries no separate numerical reward and does not require retaining original enemy IDs or an unbounded list of ingredients.

Do not record per-family run statistics or promise a family-by-family inventory in this version: mixed bundles intentionally discard detailed composition while preserving every spendable/progression point. The available metadata is enough for source flavor and pickup feedback. If later material recipes require exact composition, that is a separate economy revision before implementation.

Mixed Salvage is a presentation label, not a fifth spendable resource. Reset/quit discards run-local family labels with the same pickup lifecycle as rewards; returning to HOPE preserves uncollected field pickup labels. Separate material counters, persistence and achievements are outside scope.
## 6. Pickup, hub and shop language

The live HUD prioritizes Trade Scrap, Salvage level progress, Return Home and shield state. Do not add four permanent material bars. Existing combined gain feedback such as **“+3 Scrap / +2 Salvage”** remains the main combat message. Family flavor may appear in a tooltip, tutorial example or a quieter summary; it cannot obscure combat.

Onboard sealed collection appraises usable material immediately, which explains the instant trade wallet. The colony later processes material under controlled conditions. No trip to a refinery is needed to turn an earned pickup into money, and no unannounced decontamination fee is deducted.

The skill workshop can describe a purchase as repurposed control circuitry without requiring Circuit Parts specifically. The repair berth charges 10 Trade Scrap per missing hull HP, with proportional affordable partial repairs. Shield Battery is a separate shop item, consumed on purchase; Power Cell salvage does not restore shield. Special acquisitions use Singularity 2400, Space Collapse 2800, Nuclear Missile 3200 and Armageddon 4000. Material labels do not add recipes or separate balances.

## 7. Cases the later implementation must preserve

| Case | Required result |
|---|---|
| A basic alloy enemy rolls 1 instead of 3 | Wallet gains 1 on collection; salvage still gains 2 |
| A mid electronics pickup joins that basic pickup | Mixed label; trade equals both stored rolls; salvage equals 7 |
| Mixed pickup crosses a level threshold | Preserve overflow and queued cards exactly as the ordinary pickup contract |
| Return Home before collection | Pickup and family stay in the suspended expedition; no wallet credit |
| Player spends all trade currency | Earned salvage/level/Return Home charge does not decrease |
| Power Cells are collected | Ordinary enemy-tier trade/salvage; no free shield recharge, hull heal or source cleanse |
| Source boss is erased by a no-loot effect | Source objective still resolves; no material, trade or salvage reward |
| Pickup cap is reached | Merge without erasing either numeric reward; no unlimited object allocation |

## 8. Optional later expansion, not part of this handoff's economy

Recipes, material-specific prices, player trading, warehouses, permanent unlocks and researched purification technology would change the game's economy and scope. They require a separate design revision. The current material system is deliberately descriptive so the already detailed leveling, repair, return and skill-shop rules remain coherent.
