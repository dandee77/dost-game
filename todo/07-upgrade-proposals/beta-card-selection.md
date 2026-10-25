# Beta card catalog, rarity and acquisition - 25 October 2026

Adopted written beta defaults under existing design delegation; not separately recorded owner approval of each number or completed runtime implementation. Preserve Q35 useful cards, Q37 no pity, Q38 mandatory choice, Q40 compatible patterns and the selected Luck/Blink/Blast Radius exceptions. [Capabilities](card-compatibility.md), [target matrix](../02-gameplay/automatic-targeting.md) and [numeric authority](../../context/game-design.md#25-october-beta-card-catalog-and-selection) govern effects.

## Complete 34-entry grade assignment

| Grade | Count | Entries |
|---|---|---|
| Common | 6 | Scrap Magnet; Repulsor Pulse; Weapons Payload; Overclocked Chambers; Reinforced Hull; Thruster Overdrive |
| Uncommon | 9 | Deflector Shield; Radiant Halo; Corrosive Trail; Point-Defense Interceptor; Critical Matrix; Rapid Fire; Phase Shift; Gyro Control; Inertia Impact |
| Rare | 9 | Laser Rings; Lightning Ring; Chain Lightning; Combat Drone; Shield Detonation; Armor Piercing; Scatter Shot; Broadside Cannons; Tail Gunner |
| Epic | 6 | Plasma Beam; Hologram Clone; Realm Breaker; Nuclear Missile; Singularity; Blast Radius |
| Legendary | 4 | Space Collapse; Armageddon; Blink Drive; Luck |

Rarity changes offer frequency, not a random damage multiplier. All combat abilities can coexist; no active-slot/army/rank ceiling is introduced. Luck alone ends at rank 10; weapons end at T5. Starter Deflector is already rank 1. No Nano Repair, Return Home or historical alias becomes a duplicate field card.

## Eligibility, snapshots and distinctness

Filter typed entries before sampling: implemented capability, current weapon/owned abilities, prerequisite, genuine next benefit and explicit cap. Use the complete 26-node mapping. An unowned ability is a useful acquisition; another offered-but-unselected card/future purchase cannot qualify a modifier. Temporary full HP/shield, no targets and cooldown debt do not invalidate structural benefits. Preserve dormant owned ranks on incompatible cannon upgrades. Exclude Luck at rank 10.

All options use one unchanged build snapshot. Remove each offered typed identity from that panel's remaining pools; no duplicates, but a future panel may repeat an eligible card. Lock options through pause/focus/reopen/settings. Successful pick applies once, consumes one pending choice and generates the next queued panel from the updated build. Unselected Nuclear Missile does not qualify Blast Radius in the same panel; selecting it can qualify Radius on the next panel. Invalid/stale/duplicate commits never grant, charge, consume or reroll.

## Exact sampler and exhaustion

Three slot attempts in order. Each draws an independent Legendary gate, including when no Legendary is eligible. Gate succeeds for a uniform integer 0..9999 below 50: probability 0.005. Success with a remaining Legendary chooses uniformly from that pool and removes it. Otherwise choose a remaining ordinary tier by the weights below, then uniformly within that tier. Failed gate cannot choose Legendary.

| Ordinary tier | Integer weight | Nominal slot share with all tiers available |
|---|---|---|
| Common | 4500 | 45% |
| Uncommon | 3000 | 30% |
| Rare | 1800 | 18% |
| Epic | 650 | 6.5% |

Renormalize only over nonempty ordinary tiers. Full ordinary sum is 9950; multiplying by ordinary-gate probability 0.995 gives the exact nominal shares. Entry count never multiplies a tier's weight. A successful gate with an empty Legendary pool falls back to ordinary selection. If ordinary entries become exhausted during a panel, a failed/fallback gate omits that slot without tier/entry draws. Never promote, retry the gate, replace a card or regenerate the panel.

Pre-draw invariant: require at least one eligible ordinary entry. Valid normal beta data has at least four uncapped, always-supported Common attributes (Payload, Overclock, Hull, Thruster) on every equipped cannon, plus ordinary abilities, so normally all three distinct slots fill. An initial zero-ordinary pool is invalid/unsupported data, not universal Legendary access. Preserve the queued pick and show an upgrade-data diagnostic with confirmed Restart/Return to Menu. No combat Resume, consumption, compensation or RNG retry; ordinary abandonment remains available, preventing an inescapable empty modal. All locked options becoming invalid through debug/stale mutation uses the same recovery. Shipping normal data must never reach this diagnostic.

With one ordinary entry initially available, the panel cannot be empty: every successful Legendary selection adds an option, or the first ordinary selection adds that ordinary entry before exhaustion. Fewer-than-three handling remains for reduced synthetic/debug pools. Q38 requires explicit selection even for a one-card panel; normal pause restores the same panel.

## Deterministic stream and bounded draws

Use the existing Game-owned card engine, isolated from encounter/base-loot/Luck/shop/cosmetic streams. No random draw on hover, rendering, pause, focus, reopen, failed commit or failed zero-ordinary precheck. No wall-clock seeding/global UI random helper.

Target seed contract: initialize existing mt19937 through seed_seq containing low/high 32-bit words of recorded run seed and domain 0x43415244 (CARD). Shop uses a separate engine/domain 0x53484F50 (SHOP). Fixed engine-domain values belong in Config during implementation. Rules/catalog version identifies weights/order; changing those needs the appropriate rules revision. This complete stream contract is not already implemented.

For integer bound n > 0, compute a 64-bit limit = floor(2^32/n)*n. Read 32-bit engine output u until u < limit, then select u modulo n. This avoids modulo bias and host-library distribution differences. Bound 1 still consumes one output; never use bound 0. Gate bound is 10000. Ordinary-tier bound is sum of available weights, with cumulative Common/Uncommon/Rare/Epic order; entry bound is that pool's size. Rejected engine words consume engine state but are not extra slot attempts or pity.

Canonical order: the 19-row automatic-targeting matrix, then source augment-catalog order excluding Nano Repair, then Luck and Blast Radius. Use an explicit ordered typed-ID table, not display-name behavior or unordered-container order. Successful Legendary selection consumes gate plus entry selection; ordinary selection consumes gate plus tier plus entry. Empty omitted slots consume their gate only. Uniform selection with one candidate still consumes its bounded draw. Filtering/sorting and commit cannot advance the card stream.

## No pity and odds meaning

No miss counter, escalating odds, boss/time milestone, minimum-per-run Legendary or end-of-run compensation. Luck affects scrap only. Three independent gates yield 1 - 0.995^3 = 0.014925125, about 1.49% chance of any Legendary while one is available for each success. Entire runs may have none; consecutive successes remain possible.

With four Legendary entries eligible and three distinct attempts, Blink inclusion is exactly 3*0.005/4 = 0.00375 (0.375%) per panel: given k successes, its inclusion chance is k/4. With capped Luck removed and the other three available, it becomes 0.5% per panel. The slot gate remains 0.5%; the smaller conditional entry pool is not pity or a Luck rarity bonus.

## Acquisition and fixed stock

| Family | First acquisition | Owned improvement |
|---|---|---|
| Deflector | Fresh rank-1 starter | Full field ranks; shop capacity-only numeric increments, no full paid rank |
| Ordinary combat abilities | Field | Field ranks or selected owned ordinary-rank price |
| Singularity, Space Collapse, Nuclear Missile, Armageddon | Field or stocked special offer | Field ranks or selected premium owned-rank price |
| Blink | Legendary field first acquisition only | Field rank or 3000+750*r paid whole rank, r current rank; no guaranteed first stock |
| Eight ordinary numeric attributes | Full field increments | Quarter-strength numeric shop increments, separate counters |
| Rapid Fire, Armor Piercing, Scatter, Broadside, Tail | Compatible field only | Further field ranks, no fractional-projectile shop route |
| Blast Radius | Compatible Epic field card | Full field or quarter-strength numeric shop increment |
| Luck | Legendary field cards, maximum 10 | No paid acquisition/rank, rarity/XP/energy/material effect |

At true run creation choose three distinct unowned entries from the selected four-special pool with the separate shop stream; fewer if insufficient. Persist those slots. Purchase marks Sold; field acquisition of its unbought entry marks Owned. Never replace/refresh/reroll stock on panel/station visits. Owned ranks remain in their own tab. Selected special prices remain 2400/2800/3200/4000; ordinary owned rank 500+250*r; premium rank 1000+375*r. Explicit shop access means field rarity is not universal scarcity. Station services never roll free field cards/ranks.

## Later runtime acceptance

Cover all 34 unique IDs and 6/9/9/6/4 grades; all 26 profile prerequisites; starter/NEW/RANK distinction; Luck 9 -> 10 across queued panels; Nuclear/Radius same-panel independence; stable seed/draw order; gate boundary 49/50; tier cumulative boundaries; empty Legendary fallback; reduced ordinary exhaustion; pre-draw invalid-pool diagnostic and safe abandonment; stale/double commits; locked focus/settings; fixed stock and field-acquired-stock handling. Deterministic branch cases precede statistical checks. Actual T03/T04/T08/T10 code, cue/art/UI and statistical/visual acceptance remain open.
