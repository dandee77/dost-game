# Quarter-Strength Attributes, Shield and Luck

**21 October 2026. Context only.** Owner confirmed purchased attribute gains at **25% of a corresponding field card**, shield retained in cards, and mothership cannon progression. Remaining limits, prices and Luck details are proposals for later review. Numerical authority: pending-review ledger in [game design](../../context/game-design.md).

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
| Weapons Payload | +15 percentage points of base primary damage | +3.75 percentage points | Primary attacks only; automatic ability damage keeps its own tuning |
| Critical Matrix | +5 percentage points critical chance | +1.25 percentage points | Clamp probability at 100%; show percentage points, not ambiguous percent |
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

## 3. Shared derivation without granting fake ranks

Store card rank and paid purchase count as source records, then derive each live stat once through the shared stat calculation. A quarter-strength purchase does not call the old full-rank grant and then partially undo its side effects. It does not progress the field level, queue a card, generate repair health or reset cooldowns.

For additive stats, add card and paid contributions. For multiplicative stats, apply the defined card multiplier per card rank and the defined paid multiplier per paid count; ordering must not affect the result. Examples before other modifiers:

- Weapons Payload with two cards and four purchases: `baseDamage * (1 + 0.15*2 + 0.0375*4)` = 1.45x base.
- Attack cooldown with one card and one purchase: `baseCooldown * 0.90 * 0.975` = 0.8775x base.
- Move speed with one card and one purchase: `baseSpeed * 1.10 * 1.025` = 1.1275x base.
- Shield rank 3 with four paid capacity purchases: `20 + 5*2 + 1.25*4` = 35 maximum points. Current shield is preserved, not refilled.

“Four purchases equal one card” is exact for additive increments. Compounded percentage modifiers differ slightly; display the actual result rather than promising identical totals.

Proposed per-run purchase limit: eight paid increments per listed attribute. Existing persistent augment cards keep their rank-10 cap; paid counts are separately bounded and may add their specified smaller benefit beyond that card cap. Deflector card ranks keep their existing ability progression. Reassess these draft bounds during the deferred economy/balance review; do not silently treat them as tested limits.

## 4. Discrete cards and skill ranks

Rapid Fire, Armor Piercing, Scatter Shot, Broadside Cannons and Tail Gunner remain full discrete field-card upgrades. Their purchase tab is disabled/absent in this draft because quarter of a bullet, penetration hit or firing direction is not meaningful. No four-purchase fractional-bullet queue is proposed.

Other owned automatic abilities retain the prior whole-rank skill-upgrade offers, except **Deflector uses the capacity node instead of a full-rank shop offer**. Shield Detonation is its own combat ability and is not removed. Owned Blink has its separate Legendary rank-price proposal in the ledger; its first acquisition remains field-only. Whole skill ranks do not masquerade as quarter-strength attributes.

Shop tabs become **Weapon Tree**, **Attributes**, **Owned Skills** and **Special Offers**. These are proposed panel sections, not four new scenes or four new managers. Existing eligible special offers and paid service stay available; exact availability is shown before spending.

## 5. Local price proposal

Numeric attribute purchase number `n + 1` costs `40 + 20*n`, with `n` the prior paid count for that attribute. First four prices are 40, 60, 80, 100; eight purchases total 880. Each attribute tracks its own count. No luck-based discount, random price or service coupon is introduced.

Spending is atomic with the granted increment and requires the hub shop. No standard numeric augment is also sold through the old full-rank purchase row: that would bypass the 25% rule. Failed/stale/duplicate transactions do not charge. If a hard stat limit would make the purchase grant no effect, disable it and do not charge; previews show any clamped final gain. Paid max-HP/capacity gains preserve absolute current health/shield and all break/reboot state.

## 6. Luck recommendation

**Proposed initial direction:** Luck is workshop-only. Keep it off the permanent combat HUD, but show its current rank, exact effect and next price in workshop details. A deliberately hidden effect with unexplained prices would be difficult for the player to assess. No Luck field card is added in this draft; a Legendary Luck card remains a later alternative for owner review.

Luck improves the **quality of the existing trade-value roll**, not the chance that a normally eligible enemy drops anything. Eligible enemies already yield their stored reward on an allowed death. No chests, rare equipment drops or new material drop table is introduced.

Proposed ranks: 0-5. Each rank gives a 10% chance to use the higher of two independent uniform trade rolls, capped at 50%. The result stays inside the existing tier's inclusive range. Salvage XP, Return Home charge, score, material family, card rarity and skill stock are unaffected. Ordinary debris, bosses, excluded death causes and hypothetical future elite content do not receive the bonus in this initial proposal.

For later reward assignment, the ordinary loot RNG still assigns one base amount at enemy spawn. A separate Luck RNG supplies its check and comparison amount. Both the final stored amount and Luck snapshot are assigned at spawn, never on death/collection. A later Luck purchase cannot improve existing suspended enemies or reroll world pickups. Reopening the shop or returning cannot farm a second roll. Luck cannot override Space Collapse/barricade/despawn no-drop rules.

Example: a basic enemy's base roll is 1; a successful Luck comparison rolls 3, so its stored trade amount is 3 and fixed salvage remains 2. If the comparison fails, keep 1. If both rolls are 1, keep 1. Without Luck, the existing uniform base distribution remains intact; with Luck, the final distribution intentionally favors higher values.

Proposed Luck price: `80 + 40*n` for the next rank with `n` prior Luck purchases; prices 80/120/160/200/240, total 800 for rank 5. This is a support-node proposal, not a normal quarter-strength combat attribute, and cannot recursively improve its own price or offer rarity. At rank 5, expected basic-enemy trade rises from 2 to 20/9 (about 2.222), not beyond its 1-3 range.

The workshop tree has independent Weapon, Attributes and Support/Luck branches. No mandatory Luck purchase blocks a cannon, shield or repair. No cross-run unlock currency, permanent research grind or extra material inventory is added.
