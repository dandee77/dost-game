# Numeric attributes and Luck beta contract - 25 October 2026

Adopt existing proposed values as written beta starting defaults under current delegation; not a claim of live balance or separately recorded per-number owner approval. Preserve selected quarter-strength purchases, uncapped ordinary ranks, field-only rank-10 Luck and no free paid healing. [Game design](../../context/game-design.md#25-october-adopted-attributes-and-luck) owns numbers; [attribute table](../07-upgrade-proposals/attributes-and-luck.md#2-proposed-attribute-comparison) lists each grant and [card capabilities](../07-upgrade-proposals/card-compatibility.md) determines eligibility.

## Sources, shop inventory and ranks

There are eight ordinary numeric field attributes: Payload, Critical Matrix, Overclock, Reinforced Hull, Thruster Overdrive, Gyro Control, Phase Shift and Inertia Impact. Blast Radius is a ninth numeric field attribute. The shop exposes their supported quarter-strength increments plus Shield Capacity: ten numeric purchase rows when all are compatible. Deflector remains a combat-ability field rank, not an eleventh numeric card. Luck is a separate Legendary capped field card, never a paid row. Five discrete burst/penetration/fan/side/rear cards stay field-only; no fractional projectile purchases or four-purchase conversion queue.

Store full field-card counts and each paid-node purchase count separately, starting at zero. Deflector alone begins owned at rank 1. A paid numeric increment neither calls the full field-card rank handler nor grants skill ranks/XP/return energy. A numeric row does not require first finding its field card: require a supported current stat/effect and genuine gain. Blast Radius requires present compatible damage geometry; Shield Capacity requires the one real starter shield. Ordinary owned skill ranks and weapon equipment remain separate transactions.

First numeric purchase costs 200; purchase n+1 costs 200+100*n with n that row's prior paid count. Purchase N costs 100*N+100; cumulative cost is 50*N*N+150*N. Counts/prices are independent per node, so two Payload purchases do not raise the first Hull price. No per-visit/run numeric purchase limit, price RNG, discount or Luck coupon. Reject stale/duplicate/ineligible/no-effect/unrepresentable transactions without payment; preserve the exact prior state and explain the failure. Real numeric/overflow handling remains PREP-14 implementation work, not a secretly advertised MAX rank.

## Derive and preview the actual benefit

Use one shared stat derivation for field, shop, HUD and damage, with explicit source counts. Additive card/paid contributions add; multiplicative sources multiply in their prescribed counts. Primary modifiers apply once to primary-owned components, not again to an automatic ability/clone/secondary descendant. Do not use a paid count as a full-rank ability count. Every preview shows current -> actual next value and exact price/wallet afterward.

Adopt the existing field/paid table: Payload +15/+3.75 percentage points base primary damage; critical +5/+1.25 percentage points rating; Overclock cooldown factors 0.90/0.975; Hull +20 max/current versus +5 max only; Thruster/Gyro/ordinary hit-protection factors 1.10/1.025; Inertia +50/+12.5 magnitude; Blast Radius +10%/+2.5% of each compatible base radius. Shield field rank increases capacity by 5 plus its separately authored full-rank effects; paid capacity adds 1.25 maximum only. Critical overflow uses the selected additive tiers, not a 100% cap. Blink and return protection retain fixed two-second guards, unaffected by Phase Shift.

Preserve fractional values internally. A field Hull card on a living 30/100 ship yields 50/120; a paid Hull increment instead yields 30/105. A dead/terminal ship cannot choose a pending card to revive. Paid capacity on a 20/20 shield yields 20/21.25; a Deflector rank card instead raises maximum to 25 without refilling current points or clearing reboot. Rank 3 with four capacity purchases has maximum 35. Only true fresh-run initialization gives the full starter; only the explicitly selected battery/repair/free Hull field grant changes current resources.

Worked source math: two Payload cards and four paid increments -> 1+0.15*2+0.0375*4 = 1.45x primary damage. One Overclock card and one purchase -> 0.90*0.975 = 0.8775x cooldown. One Thruster card and purchase -> 1.10*1.025 = 1.1275x speed. Four purchases exactly equal one full card for additive gains; compounded percentage effects need not be identical. Preserve shot/cast snapshot/debt when deriving later values; a shop click cannot fire, heal droids or reset cooldowns.

## Luck payout and snapshot algorithm

Luck rank r in 0..10 gives comparison probability q=0.10*r. It affects reward-eligible ordinary basic/ranged/heavy enemies, including reward-enabled ordinary boss adds. Exclude bosses/final bosses, debris, barricades, cleanup/despawn, no-drop flags and any unauthored elite profile. Material family, score, fixed Salvage, return charge, shop stock and card rarity remain unchanged. Luck improves value within the existing inclusive trade range, not the chance for a normal reward to exist.

At enemy spawn, after its base reward tier/range is known:

1. Draw base trade U once from the existing base-loot stream and range [L,H]. Preserve that stream's consumption regardless of Luck.
2. Snapshot the current Luck rank. Rank zero uses U and makes no Luck draw. A fixed-value/noneligible source also makes no Luck draw.
3. For eligible rank 1..10, draw one uniform gate 0..9 from the isolated Luck stream; comparison succeeds when gate < r. Rank 10 still consumes this gate for a fixed algorithm.
4. On success draw independent V uniformly in [L,H] from the Luck stream and store max(U,V); on failure store U without a second roll. Never draw V from base-loot/encounter/card RNG.
5. Store final trade, fixed Salvage and family with the entity before damage/death. Death materializes them only if the kill remains reward-eligible; collecting/merging/spending/returning cannot reroll them.

Use the same unbiased bounded-integer convention as the card contract, with a separate existing-owner Luck engine seeded from recorded run seed and domain 0x4C55434B (LUCK); the domain belongs in Config when implemented. Base-loot draw U remains in its existing independent domain. Rank changes affect only later enemy spawns, never an existing enemy or already released pickup. A later Space Collapse/no-drop death still suppresses both stored reward fields; Luck cannot bypass that exclusion. Boss-owned ordinary adds retain whatever normal reward eligibility the encounter assigned; a boss label does not automatically make them a boss reward tier.

## Payout expectations and examples

For N=H-L+1 and max of two independent uniform draws, P(max=k) = ((k-L+1)^2-(k-L)^2)/N^2. Expected value is baseline mean plus q*(N*N-1)/(6*N). Inclusive endpoints never change. This formula is explanatory evidence, not a runtime substitute for the specified seeded draws.

| Ordinary range | Rank-0 mean | Rank-10 mean | Relative trade gain |
|---|---|---|---|
| Basic 1..3 | 2 | 22/9 = 2.444444... | About 22.22% |
| Ranged 3..7 | 5 | 5.8 | 16% |
| Heavy 8..12 | 10 | 10.8 | 8% |

Basic rank-10 final probabilities are 1/9, 3/9 and 5/9 for 1,2,3; rank 10 never guarantees the maximum. Examples: U=1,V=3,successful comparison -> 3; U=3,V=1 -> 3; failed rank-5 gate with U=1 -> 1; an enemy spawned at rank zero retains U after a later Luck card. Ordinary rank-10 basic still has fixed Salvage 2, not 2.444 or double XP. Power Cells remain a material label, not extra energy/shield charge.

## UI, reset and later runtime acceptance

Show Luck's rank and current comparison percentage in card/paused details; at rank 10 remove future offers, with no paid row or ability-cooldown icon. Numeric previews show card and paid sources separately and resulting precise increments, including capacity fractions. Missing purchases/partial repair cannot create free points. New Run clears all run counts/ranks and reseeds streams; same-run hub/level/pause transitions preserve them and assigned rewards.

Verify ten supported numeric shop rows, five discrete exclusions, independent price counts, quarter-gain/source math, Hull/current-shield preservation, no-field-rank shop grant, genuine effect checks, capped Luck filtering, gate endpoints, bounds, source eligibility, spawn snapshots, no-drop suppression and value-conserving pickup merging. Compare enumerated payout expectations with runtime deterministic/statistical checks later. Written values/formulas are adopted; actual Player/SkillSystem/loot/shop integration, numerical safety and measured economy remain open.
