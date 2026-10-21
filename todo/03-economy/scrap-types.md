# Scrap Types and Recovery Contract

**21 October 2026. Proposed material taxonomy; documentation only.** The owner requested scrap types without specifying categories. This brief chooses six families and defines their first-version purpose. Existing random trade rewards, fixed salvage progress, paid repairs and skill prices remain authoritative in [game design](../../context/game-design.md) and [gameplay](../02-gameplay/gameplay.md).

## 1. One economy, recognizable materials

A pickup has a **material family**, a **trade value**, and a **salvage value**. The family describes what was recovered. Trade value enters the shared wallet used by repairs and the shop. Salvage value independently advances field leveling and Return Home.

The first version does not require collecting particular materials to buy a skill or repair hull. There are no six separate wallets, exchange buttons, material inventory slots, crafting recipes, refinery timers or additional taxes. This keeps normal field upgrades immediate and avoids a player being unable to repair despite owning enough trade scrap.

**Example:** a basic enemy's recovered alloy pickup can contain 3 Trade Scrap and 2 Salvage. An electronic pickup from a mid-tier enemy can contain 4 Trade Scrap and 5 Salvage. The material names do not multiply either reward. Buying a 150-scrap skill rank spends 150 from the one wallet regardless of which families produced it.

## 2. Six proposed families

| ID for later data | Player-facing label | Recognizable source | Colony use in the fiction | Suggested visual distinction |
|---|---|---|---|---|
| ALLOY | Recovered Alloys | Plates, pipes, structural metal | Hull patches, brackets and ordinary repairs | Bent plate silhouette |
| ELECTRONICS | Electronic Components | Boards, sensors, dishes, guidance assemblies | Targeting, control and skill-system repairs | Circuit/connector silhouette |
| POLYMER | Polymer Stock | Insulation, cable jackets, seals, durable housings | Seals, insulated cabling and protective layers | Coiled strip silhouette |
| POWER | Power Modules | Motors, stored-energy units, thruster electronics | Shield servicing and powered equipment | Cell/terminal silhouette |
| COMPOSITE | Structural Composites | Layered panels, wings and reinforced housings | Lightweight ship reinforcement | Layered panel silhouette |
| FILTRATION | Purification Media | Filter canisters and processing assemblies | Life-support filtration after controlled recovery | Filter-grid silhouette |

All six are resource labels, not rarity tiers. Purification Media is not an antidote and Power Modules is not a separately spendable shield charge. The workshop still prices items in Trade Scrap. Existing destruction art and red homing orbs remain accepted; these suggested silhouettes are later optional pickup/UI art, not permission to recolor or regenerate assets now.

## 3. Assignment rules

Use the dominant recoverable material of the authored enemy/debris profile. Material assignment does not need a new random stream. Randomness remains in the existing uniform inclusive enemy **trade amount**. Boss family depends on the final authored body/source design; it never changes its reward tier.

| Existing debris kind | Proposed dominant family | Rationale |
|---|---|---|
| Clump | Recovered Alloys | Mixed compact metal |
| Pipe | Recovered Alloys | Tube and fittings |
| Wing | Structural Composites | Layered structural surface |
| Canister | Purification Media | Recovered filter housing and usable media; proposed narrative identification |
| Dish | Electronic Components | Receiver/control components |
| Coil | Polymer Stock | Recoverable insulation and protective jackets |
| Tank | Recovered Alloys | Reinforced vessel casing |
| Thruster | Power Modules | Recoverable power-control assembly |
| Beam | Recovered Alloys | Structural member |
| Hull | Structural Composites | Reinforced layered plating |

This table classifies a usable fraction, not the whole mass of the object. It does not change any existing per-kind fixed debris reward. If art clearly contradicts a label, revise the profile here before production rather than inventing an extra loot system.

Default enemy mapping until final profiles exist: low/basic -> ALLOY; mid/ranged -> ELECTRONICS; high/heavy -> COMPOSITE. Future elite/boss profiles explicitly declare one family; unclassified prototypes fall back to ALLOY and appear on the content-review list. Final boss/source reward is not automatically FILTRATION. Source completion is independent of its material and of whether it drops anything.

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

Mixed Salvage is a presentation label, not a seventh spendable resource. Reset/quit discards run-local family labels with the same pickup lifecycle as rewards; returning to HOPE preserves uncollected field pickup labels. Separate material counters, persistence and achievements are outside scope.
## 6. Pickup, hub and shop language

The live HUD prioritizes Trade Scrap, Salvage level progress, Return Home and shield state. Do not add six permanent material bars. Existing combined gain feedback such as **“+3 Scrap / +2 Salvage”** remains the main combat message. Family flavor may appear in a tooltip, tutorial example or a quieter summary; it cannot obscure combat.

Onboard sealed collection appraises usable material immediately, which explains the instant trade wallet. The colony later processes material under controlled conditions. No trip to a refinery is needed to turn an earned pickup into money, and no unannounced decontamination fee is deducted.

The skill workshop can describe a purchase as repurposed control circuitry without requiring Electronic Components specifically. The repair berth uses the same wallet at the existing rate of one Trade Scrap per five missing hull points, rounded up for a full quote. Shield recharge follows the existing quoted rule. Rare acquisitions remain Singularity 240, Space Collapse 280, Nuclear Missile 320 and Armageddon 400; material types add no new shop inventory.

## 7. Cases the later implementation must preserve

| Case | Required result |
|---|---|
| A basic alloy enemy rolls 1 instead of 3 | Wallet gains 1 on collection; salvage still gains 2 |
| A mid electronics pickup joins that basic pickup | Mixed label; trade equals both stored rolls; salvage equals 7 |
| Mixed pickup crosses a level threshold | Preserve overflow and queued cards exactly as the ordinary pickup contract |
| Return Home before collection | Pickup and family stay in the suspended expedition; no wallet credit |
| Player spends all trade currency | Earned salvage/level/Return Home charge does not decrease |
| Purification Media is collected | Ordinary trade/salvage only; no free hull heal or instant source cleanse |
| Source boss is erased by a no-loot effect | Source objective still resolves; no material, trade or salvage reward |
| Pickup cap is reached | Merge without erasing either numeric reward; no unlimited object allocation |

## 8. Optional later expansion, not part of this handoff's economy

Recipes, material-specific prices, player trading, warehouses, permanent unlocks and researched purification technology would change the game's economy and scope. They require a separate design revision. The current material system is deliberately descriptive so the already detailed leveling, repair, return and skill-shop rules remain coherent.
