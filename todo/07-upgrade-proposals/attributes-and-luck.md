# Quarter-Strength Attributes, Shield and Luck

**21 October 2026. Context only.** Owner confirmed purchased attribute gains at **25% of a corresponding field card**, shield retained in cards, and mothership cannon progression. Remaining limits, prices and Luck details are proposals for later review. Numerical authority: pending-review ledger in [game design](../../context/game-design.md).

**23 October pricing update:** Owner selected 5x numeric-attribute and owned-skill-rank prices, and 10x special-skill acquisition prices. Gains are unchanged. Exact current prices are in game-design.md; the earlier low-price draft is superseded. Luck adoption remains open.

## 1. Three different purchases

| Purchase | Effect | Progression source |
|---|---|---|
| Cannon tier/branch | Changes the primary weapon profile | Mothership only; [weapon tree](weapon-tree.md) |
| Attribute increment | Adds a smaller numeric ship improvement | Mothership at quarter strength; field cards grant their full effect |
| Automatic ability acquisition/rank | Adds or strengthens its authored behavior | Field cards and explicitly eligible skill offers; not every ability uses the attribute fraction |

Do not apply the 25% rule blindly to a new ability, an extra drone, a new weapon tier or a discrete extra projectile. The rule concerns purchased numeric attributes. An ability's next rank remains a whole rank unless its specific contract says otherwise.

## 2. Proposed attribute comparison

| Attribute | One full field-card increment | One purchased increment | Notes |
|---|---|---|---|
| Blast Radius — Epic, owner approved | +10% of each compatible effect's base damage radius | +2.5% of base radius | Add once after ability-rank radius; damage per victim unchanged; exact compatibility in game-design.md |
| Weapons Payload | +15 percentage points of base primary damage | +3.75 percentage points | Primary attacks only; automatic ability damage keeps its own tuning |
| Critical Matrix | +5 percentage points critical chance | +1.25 percentage points | Uncapped rating; full 100% blocks add guaranteed critical tiers; remainder rolls the next tier |
| Overclocked Chambers | Attack cooldown multiplied by 0.90 | Attack cooldown multiplied by 0.975 | Quarter of the 10% cooldown reduction; not a claim of exactly 25% of resulting DPS gain |
| Reinforced Hull | +20 max HP and the existing +20 current-HP card grant | +5 max HP; no current-HP grant | Paid capacity is not free repair |
| Thruster Overdrive | Move speed multiplied by 1.10 | Move speed multiplied by 1.025 | Preserve control and frame-rate independence |
| Gyro Control | Turning response multiplied by 1.10 | Turning response multiplied by 1.025 | Use actual prototype meaning of turn responsiveness |
| Phase Shift | Ordinary post-hit protection multiplied by 1.10 | Ordinary post-hit protection multiplied by 1.025 | Does not extend Blink's separate fixed protected window |
| Inertia Impact | +50 knockback magnitude | +12.5 knockback magnitude | Actual supported targets remain bounded by their knockback rules |
| Shield Capacity | Deflector card: +5 capacity plus its full-rank shield effects | +1.25 capacity only | Does not grant a Deflector rank, reboot reduction or regeneration boost |

The shield's starter remains rank 1, capacity 20, pending the existing starter-loadout adoption. Deflector is still an eligible field upgrade. Its card grants a full ability rank under the shield contract; a shop capacity purchase only increases the upper limit. Proposed total capacity:

`maxShield = 20 + 5 * (deflectorCardRank - 1) + 1.25 * paidCapacityPurchases`

Retain fractional capacity internally. Previews display enough precision to show the actual +1.25 gain. If the chosen UI instead uses integers, approve a value-conserving accumulation policy before implementation; never charge for a silently rounded-away gain.

Blast Radius is a separate additive source beyond an ability's own rank-five size progression. It has no fixed rank/purchase cap and uses the normal numeric-attribute price. Offer it only with a currently compatible effect; retain earned ranks through weapon changes. Exclude non-damaging geometry and direct-projectile hitboxes. Full formula, exclusions and snapshot rules are in game-design.md.

## 3. Shared derivation without granting fake ranks

Store card rank and paid purchase count as source records, then derive each live stat once through the shared stat calculation. A quarter-strength purchase does not call the old full-rank grant and then partially undo its side effects. It does not progress the field level, queue a card, generate repair health or reset cooldowns.

For additive stats, add card and paid contributions. For multiplicative stats, apply the defined card multiplier per card rank and the defined paid multiplier per paid count; ordering must not affect the result. Examples before other modifiers:

- Weapons Payload with two cards and four purchases: `baseDamage * (1 + 0.15*2 + 0.0375*4)` = 1.45x base.
- Attack cooldown with one card and one purchase: `baseCooldown * 0.90 * 0.975` = 0.8775x base.
- Move speed with one card and one purchase: `baseSpeed * 1.10 * 1.025` = 1.1275x base.
- Shield rank 3 with four paid capacity purchases: `20 + 5*2 + 1.25*4` = 35 maximum points. Current shield is preserved, not refilled.

“Four purchases equal one card” is exact for additive increments. Compounded percentage modifiers differ slightly; display the actual result rather than promising identical totals.

Owner confirmed 24 October: no fixed numeric-attribute card-rank or paid-purchase cap. Keep source counts separate, quarter-strength paid gains and no-free-repair rules. Weapon tiers still end at T5. Owner selected critical tiers beyond 100% and continued multiplicative fire-rate growth with equivalent-event aggregation. Canonical formulas and acceptance tests are in game-design.md; never sell a zero-effect increment or silently cap ranks.

## 4. Discrete cards and skill ranks

Rapid Fire, Armor Piercing, Scatter Shot, Broadside Cannons and Tail Gunner remain full discrete field-card upgrades. Their purchase tab is disabled/absent in this draft because quarter of a bullet, penetration hit or firing direction is not meaningful. No four-purchase fractional-bullet queue is proposed.

Other owned automatic abilities retain the prior whole-rank skill-upgrade offers, except **Deflector uses the capacity node instead of a full-rank shop offer**. Shield Detonation is its own combat ability and is not removed. Owned Blink has its separate Legendary rank-price proposal in the ledger; its first acquisition remains field-only. Whole skill ranks do not masquerade as quarter-strength attributes.

Shop tabs become **Weapon Tree**, **Attributes**, **Owned Skills** and **Special Offers**. These are proposed panel sections, not four new scenes or four new managers. Existing eligible special offers and paid service stay available; exact availability is shown before spending.

## 5. Local price proposal

Owner-selected 23 October numeric attribute price (5x prior draft): purchase `n + 1` costs `200 + 100*n`, with n the prior paid count. First four prices are 200, 300, 400, 500; the first eight purchases total 4400, and buying may continue. Purchase N costs `100*N + 100`; cumulative cost is `50*N*N + 150*N`. Each attribute tracks its own count. No luck-based discount, random price or service coupon is introduced.

Spending is atomic with the granted increment and requires the hub shop. No standard numeric augment is also sold through the old full-rank purchase row: that would bypass the 25% rule. Failed/stale/duplicate transactions do not charge. If a hard stat limit would make the purchase grant no effect, disable it and do not charge; previews show any clamped final gain. Paid max-HP/capacity gains preserve absolute current health/shield and all break/reboot state.

## 6. Legendary Luck — owner-selected rules

Luck affects trade scrap only. It is acquired and upgraded exclusively through Legendary field cards and has a maximum rank of 10. This is an explicit exception to uncapped ordinary attributes/skills. No workshop acquisition or paid rank is permitted. At rank 10, remove Luck from eligible offers. Luck never improves XP, return energy, card rarity, material family or shop stock.

Proposed payout tuning: rank r grants a 10% * r chance to keep the higher of two independent uniform rolls within the enemy's existing trade range, reaching 100% at rank 10. The amount never exceeds that range. This preserves guaranteed ordinary drops; Luck improves their value, not drop existence. Apply initially to ordinary basic/ranged/heavy enemies, excluding bosses, debris and no-drop deaths. Exact payout strength remains a proposal for review, separate from confirmed acquisition and cap.

Snapshot rank and final reward at enemy spawn using isolated loot/Luck randomness. Later cards, kills, pickup merges or base visits cannot reroll stored rewards. A rank-10 basic enemy roll has mean 22/9 (about 2.444), versus 2 without Luck: about +22.2% trade on average, not +100% scrap and not a guaranteed maximum roll.

Show rank, current effect and next effect in the card/details UI; no permanent HUD meter is required. Weapon and numeric-attribute shop branches remain separate. No Luck purchase is required for progression and no cross-run unlock currency is introduced.
