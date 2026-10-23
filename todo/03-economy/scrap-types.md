# Scrap Types and Recovery Contract

**23 October 2026. Owner-selected four material types and one wallet; documentation only.** Owner selected Metal Fragments, Circuit Parts, Polymer Pieces and Power Cells, superseding the earlier six-family proposal. All feed one shared scrap wallet; none is required for a particular weapon. Material labels use the existing enemy-tier reward values, with visual/lore differences only. Owner selected appearance-matched assignments; authored profile coverage remains to verify. Existing trade/salvage accounting stays authoritative in [game design](../../context/game-design.md) and [gameplay](../02-gameplay/gameplay.md). Weapon costs are now 500/1500/4000/10000 (total 16000); attributes/owned ranks use the selected 5x scale, special acquisitions 10x, and hull repair costs 10 scrap per missing HP.

**Upgrade-review note:** [Luck and attributes](../07-upgrade-proposals/attributes-and-luck.md) propose a spawn-time trade-quality comparison without changing material families or inclusive reward bounds. Uniform amounts below remain base rolls; salvage/no-drop exclusions remain. New cannon/attribute purchases use the review contracts. Owner reopened material identity and weapon-price review on 23 October. Broader encounter/balance decisions remain deferred; material values are confirmed unchanged, while Shield Battery details and source mapping are under review.

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

Owner-selected assignment rule: use the dominant recoverable material visible in the authored enemy/debris profile. The table below proposes exact mappings for later profile/art verification. Material assignment does not need a new random stream. Randomness remains in the existing uniform inclusive enemy **trade amount**. Boss family depends on the final authored body/source design; it never changes its reward tier.

| Existing debris kind | Proposed dominant family | Rationale |
|---|---|---|
| Clump | Metal Fragments | Mixed compact metal |
| Pipe | Metal Fragments | Tube and fittings |
| Wing | Metal Fragments | Recoverable metal structure in the wing |
| Canister | Polymer Pieces | Recoverable seals and durable housing; proposed identification |
| Dish | Circuit Parts | Receiver/control components |
| Coil | Polymer Pieces | Recoverable insulation and protective jackets |
| Tank | Metal Fragments | Reinforced vessel casing |
| Thruster | Power Cells | Recoverable power-control assembly |
| Beam | Metal Fragments | Structural member |
| Hull | Metal Fragments | Recoverable metal within layered plating |

This table classifies a usable fraction, not the whole mass of the object. It does not change any existing per-kind fixed debris reward. If art clearly contradicts a label, revise the profile here before production rather than inventing an extra loot system.

Enemy mapping follows each visual variant, not health/reward tier: crushed-can shells -> METAL, battery shells -> POWER, cracked-monitor shells -> CIRCUIT. Other enemies declare their visible dominant recoverable material in their profile. Final assignments should follow the actual salvageable shell/equipment; a heavy power-bearing design may instead use POWER. Future elite/boss profiles explicitly declare a family. Unclassified prototypes fall back to METAL and appear on the content-review list. Final boss/source reward is not automatically POWER. Source completion is independent of its material and of whether it drops anything.

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
