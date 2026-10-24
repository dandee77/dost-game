# Balance implementation and context review — 23 October 2026

**24 October outcome supersession:** Q19/Q20 replace this review's earlier death-before-victory proposal for boss ties: count same-step boss death and end the run without revival. Follow the [current outcome contract](../../context/game-design.md#24-october-simultaneous-boss-clear---q19q20-confirmed). The dated observations below do not override that decision.

Read this update before the [full statistics snapshot](full-game-review.md). That snapshot still contains all 26 weapon profiles, signatures, skill tables and upgrade arithmetic, but its old exponential progression, moving return requirement and spawn pacing are superseded by [game-design.md](../../context/game-design.md#23-october-implemented-population-and-progression-revision).

## Implemented in this pass

- Natural spawning ramps from 0.7/s to 20/s over 35 combat minutes, with gradually increasing living-enemy limits. Integration carries fractional budget across frames, discards blocked whole spawns and bounds stall catch-up. Pause/restart preserve/reset the new state correctly.
- Basic/ranged HP remains 30/50 through five minutes, becomes 45/75 at 25 minutes and caps at 60/100 after 45 minutes. Their damage remains 10. Ranged enemy share caps at 15%. The enclosing barricade moves from minute 2 to minute 10.
- Natural ordinary enemies roll trade currency once at spawn from a dedicated seeded RNG; fixed salvage remains separate. Ordinary weapon kills now pay rewards as eligible skill kills do. Repeated damage after removal cannot double-credit a kill. Legacy weapon damage statistics exclude overkill.
- Enemy pickups retain both values through merging and no longer expire. Debris retains its accepted animation, yield and lifetime. Currency/XP/queued choices/energy are owned together by Game and reset together.
- XP requires 100, 120, 140, ... up to 600 per level. Pickups retain overflow and queue every earned choice. No free card arrives solely because 20 seconds passed. The HUD shows level and salvage progress.
- Repair and battery quote calculations are implemented and unit-tested independently. Shop purchases, hull service and portals are still pending; these helpers do not make those interfaces playable.

## Starting, upgraded and endpoint statistics

| System | Starting | Upgrade/growth | Endpoint or limit |
|---|---|---|---|
| Player hull, current runtime | 100 | Free hull card adds 20 max/current; up to 10 cards | 300 from field cards; proposed eight paid +5 purchases would reach 340, shop pending |
| Primary cannon | 7–12 damage, 0.5 s interval; mean 19 DPS before accuracy | Payload +15% base/card; cooldown x0.9/card; critical +5 percentage points/card | 10 of each: 2.5x damage, 0.17434 s interval, 50% critical, about 204.34 ideal DPS before pattern cards |
| Movement | 50 units/s | x1.1 per speed card | About 129.69 at 10 cards, before equipment modifiers |
| Ordinary damage protection | 0.8 s | x1.1 per applicable card | About 2.075 s at 10 cards; separate from future hub re-entry protection |
| Basic enemy | HP 30, contact 10, speed 15–30 | Slow combat-time HP growth; no damage/speed escalation | HP 60; contact 10 |
| Ranged enemy | HP 50, contact/bullet 10, speed 25–50 | Same bounded HP factor; no damage/speed escalation | HP 100; contact/bullet 10 |
| Ranged fire | Interval 0.5–1.25 s; bullet speed 120–150 | Unchanged | No multiplicative fire-rate growth |
| Barricade | 64 segments, HP 120 each, contact 10 | One event at minute 10; existing shrinking/escape geometry | No loot, no endurance HP scaling |
| Field leveling | Level 1, zero XP | `min(600,100+20*(L-1))`; all overflow retained | Requirement caps at 600; no chosen final build/ability rank |
| Return-energy calculation | 0/1000 | +1 per salvage, capped at 1000 | Requires 500 plus online shield; actual portal system pending |
| Weapons T2–T5, selected design | Starter Cannon | 500 / 1500 / 4000 / 10000 cumulative purchases | 16000 per complete path; T5 draft ideal solo DPS 95–104 including drafted signatures, before cards; see full review |
| Battery design and helper | Normal capacity C, current S | `min(S,C)+f*C`, f=0.2/0.5/1/1.5/2 | Maximum possible total 3C; natural regen only to C; shield integration pending |
| Battery price | 100 / 250 / 500 / 700 / 900 at starting capacity C0 | `ceil(basePrice*C/C0)` | No stacking old excess; buying smaller may lower shield |
| Hull repair quote | 10 scrap per missing HP | Quote Q=ceil(10D); affordable spend B=min(wallet,Q) | Heal D*B/Q, preserving fractions; zero payment heals zero |

The current equipment shield and hit-count Deflector still differ from the selected persistent 20-point starter shield. They have not been silently combined. The full review distinguishes existing equipment values from target shield design. Ability/weapon tables not changed in this pass remain draft or prototype data with their existing labels.

## Economy pacing to validate

Weapon-only T5 costs 16000. Buying repairs and side upgrades delays it; the game must earn more than 16000 gross if T5 is still expected at 20–25 minutes. A starting measurement target is 20% of gross income reserved for side spending:

| Combat interval | Target collected trade/minute | Cumulative gross at interval end | 80% available for weapon path |
|---|---:|---:|---:|
| 0–5 min | 120 | 600 | 480 |
| 5–10 min | 480 | 3000 | 2400 |
| 10–15 min | 900 | 7500 | 6000 |
| 15–20 min | 1200 | 13500 | 10800 |
| 20–25 min | 1400 | 20500 | 16400 |

This model reaches 16000 weapon savings around 24.64 minutes. It is an income target, not fabricated playtest telemetry or a guaranteed payout. At 15% ranged share the mean ordinary reward is 2.45 trade; 1400/min requires about 9.52 collected ordinary kills/s without debris. Actual kill rate, collection, ability mix and spending must be measured. Do not raise enemy HP to absorb excess income; tune spawn flow, purchase usefulness and reward rates together.

## Context contradictions resolved without another approval round

| Ambiguity | Resolution |
|---|---|
| Many files say context-only/no coding | Latest explicit owner authorization governs; those statements describe earlier sessions |
| Full review lists huge level-linked HP | Preserve as historical audit evidence; latest numerical authority replaces it with bounded combat-time HP |
| Easy leveling makes return harder than Hard | Fixed 1000 capacity and 500 charge requirement; no level-driven moving target |
| Battery says three sizes/add/replace/set total in different places | Final five-size rule wins: remove old excess, add purchased charge; preserve missing normal shield |
| Timed cards versus scrap leveling | Runtime now earns choices from salvage; queued picks freeze combat and resolve sequentially |
| Weapon kills versus skill-only salvage | All eligible player weapon/skill kills pay the stored reward; explicit erasure/environment exclusions remain visible |
| Chaos says one living boss versus owner wants growing pursuit | Latest selection wins: all finished bosses, two from 15 minutes, increasing allowance later; concrete initial schedule in game-design |
| “Resume” might mean unpause | In hub design, “Return to Battle” means resume the suspended expedition; ordinary pause resumes the same current state |
| Auto-fire cancels hub re-entry protection immediately | Delegated default: suspend auto-fire during the 2-second re-entry protection; deliberate Shoot fires and ends protection immediately; offensive automatic skills wait too |
| Removed Survival mode | Owner removed it; Swarm and Chaos share core mechanics, Campaign uses star-field stages with base after every wave |
| Repairs based on percent hull or actual deficit | Actual missing HP at 10 scrap/HP; preserve fractional affordable repair |

The delegated re-entry default above is a future integration contract, not implemented protection. Other routine choices use existing safe-area UI, typed IDs, independent RNG, one action per input, same-step death before victory and existing reset ownership. These do not need repeated permission requests.

## Context/work still incomplete

| Area | Missing work | Needs a user decision? |
|---|---|---|
| Unified shield / automatic abilities | One persistent shield source, starter grant, break/reboot, reactive Blink, Shield Detonation, remove manual skill flow | No; direction is already selected. Implement and test |
| Skill math at very high ranks | Unbounded drones/zones/counts, cooldown/tick floors, multiplicative pattern growth, erasure rewards and damage accounting | No; preserve owner-selected uncapped combat-skill/army progression, optimize simulation and cosmetic effects, then measure. Do not call this pass a complete fix of all skill math |
| Weapon tree | 26 nodes, 10 signatures, per-family card compatibility and equal-investment trials | No for routine mapping/tuning; accepted tree remains the basis |
| Hub / portals / shop | Five gates, services, random exits, pointer range/placement, saved world resume and atomic purchases | No; use selected rules and delegated geometry/input defaults |
| Four modes | Actual WaveDirector, objective/outcome logic, shared Swarm/Chaos mechanics, Campaign star-field stages, wave-clear base transitions and boss integration | Roster direction accepted; any scope reduction still needs confirmation |
| Boss content | Final roster, visual identity, source relationship; attacks/phases/telegraphs/stats then require implementation | Owner liked the four concepts and requested phases/bars; exact draft tuning and production remain pending |
| Economy | Full shop integration, rarity/Luck viability, measured T5 timing, repair burden and reward preservation | No; prices/formulas selected, remaining tuning delegated |
| Between-run progression | Implement complete reset coverage across future systems | No; owner confirmed fresh starts with no permanent gameplay unlocks or stats |
| Story / identity | Final title; remaining intro/ending/trailer animation/audio | Title needs confirmation; production and continuity can be organized autonomously |
| UX / audio / results | Complete pause/settings, tutorial, leaderboard, accessibility, mixed sound and polished feedback | No routine approval needed; implementation/testing pending |
| Release | Asset/font licenses, competition eligibility, target machine, forms, demo/trailer, packaging and submission | Human-only evidence/commitments need confirmation; do not invent clearance or submit externally without instruction |

## Confirmation list for the owner

Already settled: fresh starts; five battery sizes and replacement arithmetic; fixed ordinary return threshold; Boss-mode no retreat and unrestricted post-kill portal; repeating boss/base/launch loop; boss phases and visible HP bars. The owner liked the four drafted concepts. No repeat approval question is needed for these decisions.

1. **Final game title:** choose the release title when ready; the working title does not block gameplay work.
2. **Release facts:** actual target PC/minimum hardware, responsibility for eligibility/license evidence, and final submission owner. These require human facts and commitments.
3. **Any proposed scope reduction:** confirm before dropping requested modes or boss content. The current plan retains the requested scope; a cut is not silently authorized.

Boss phase thresholds, attack values, wave budgets, portal geometry, rarity/card compatibility and high-rank numerical/performance handling remains visible draft work or delegated tuning tasks. Prepare and verify them without treating every implementation detail as a permission question. The complete numerical reference is [game design](../../context/game-design.md); the older [full review](full-game-review.md) remains a historical prototype audit, not the current formula authority.

No public push or final balance certification is implied by this review.
