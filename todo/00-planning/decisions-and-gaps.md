# Decisions, Missing Details and Implementation Gaps

**24 October reconciliation:** Owner authorized source changes and delegated routine ambiguity resolution. Use the [current context review and confirmation list](../08-review/balance-and-context-review.md), plus the latest game-design section, before older deferrals/formulas below. Battery arithmetic and five sizes are settled; fixed return capacity supersedes level-driven growth; Chaos now increases concurrent boss pursuit. Missing implementation/content stays open even where a design default is resolved.

**21 October 2026. Preparation register, not a feature-completion report.** Read [TODO index](../README.md), [gameplay handoff](../02-gameplay/gameplay.md) and [progress tracker](../../context/progress-tracker.md) first. Existing code evidence comes from the documented prior read-only audit and tracker; this revision does not claim a new runtime audit or that every old finding persists after future pulls.

## 23 October selected field return

Ordinary portals use fixed 500/1000 energy, positive online shield and F inside; Easy/Hard/Impossible have 3/2/1 exits. Boss mode forbids mid-fight retreat and uses one post-kill portal bypassing shield/energy. Exits may be distant, with a roughly one-screen pointer. Portals persist until used/run end, and level-ups never move the threshold. Input defaults and remaining geometry verification are in [return portals](../02-gameplay/return-portals.md). All skills are automatic; no manual fallback is selected.

## 23 October active economy/material review

Owner selected weapon prices 500/1500/4000/10000 (16000 total), T5 at 20–25 Swarm minutes, and shared prices/lower tiers in 5-minute Survival. Attribute/owned-rank prices increase 5x, special acquisitions 10x. Hull repair costs 10 scrap/missing HP with exact proportional partial repair and two previewed buttons. Shield Battery is used on shop purchase, replacing paid recharge service; details are under popup review. Four selected material labels use one wallet and unchanged enemy-tier values. Material/pricing deferrals are reopened for these choices only; actual runtime viability remains unverified.

## 23 October active weapon review

Owner resumed questions and accepted the latest names/tree with T4/T5 branching (1/3/5/7/10). The [weapon tree](../07-upgrade-proposals/weapon-tree.md) and [numeric ledger](../../context/game-design.md#23-october-weapon-stat-draft--accepted-tree-proposed-tuning) replace the earlier six-family graph. Stats/signatures are proposed; numerical adoption, card compatibility, live balance and effect/performance limits remain open. Older no-questions text is superseded only for active weapon review. Unrelated deferrals remain.

## Previous review scope — owner follow-up

[Upgrade proposals](../07-upgrade-proposals/README.md) supply candidate weapon, attribute, Luck and automatic-skill rarity details. Confirmed: mothership cannon tiers, one branch/run, 25% purchased numeric gains, shield cards retained and Legendary reactive Blink. Other details remain open. Boss designs, schedules, final names, layouts and broad economy review are owner-deferred. Send no further questions during preparation; collect upgrade choices in the review checklist.
## 1. How to interpret this file

**Confirmed** means the owner chose the direction. **Delegated** means the owner asked us to select a detail. **Proposed** means a concrete default is written for review and later adoption. **Content needed** means the teammate must obtain or author the actual content before claiming that feature complete. None of these labels means implemented.

The teammate's later instruction may authorize a complete implementation sequence, but each dependency checkpoint still needs a buildable result and verification. This folder is preparation, not permission to start coding now. Do not treat an unchecked production task as a reason to reimplement completed pause, equipment, skills, debris art or collision work.

## 2. Decisions already captured

| ID | Decision | Status | Authoritative brief |
|---|---|---|---|
| D01 | Player remains in the ship; safe orbital colony hub after Start/difficulty | Confirmed | [Gameplay](../02-gameplay/gameplay.md) |
| D02 | Five mode portals: Swarm, Survival, Boss, Chaos, Campaign | Confirmed | Gameplay; each needs a real objective |
| D03 | Normal upgrade cards earned in the field | Confirmed | Gameplay; no paid unlock or forced return for normal leveling |
| D04 | Paid hull repair and random enemy trade currency | Confirmed | [Game design](../../context/game-design.md) |
| D05 | Separate fixed salvage progress for level/return, one random trade wallet | Selected accounting proposal | Gameplay; no cross-run bank or cargo conversion |
| D06 | Skill shop stocks targeted ranks and priced rare skills | Delegated item/price choice | Game design; acquisition/rank rules already detailed |
| D07 | Return usable at half of rising capacity, blocked by broken shield | Confirmed behavior; exact growth and starter shield proposed | Gameplay |
| D08 | H.O.P.E. Colony: Habitat for Orbital Preservation and Endurance | Delegated naming choice | [World and campaign](../01-story/world-and-campaign.md) |
| D09 | Failed remediation affects terrestrial and orbital waste; by 2732 an estimated 1% of humanity remained | Q39 survivor-focused wording; no absolute headcount established | World and campaign |
| D10 | No special tree/seed solution or radiation origin; source isolation enables gradual restoration | Confirmed direction | World and campaign |
| D11 | 2718 breakthrough, 2723 release, 2732 collapse estimate, 2733 cadet deployment | Owner confirmed Q36, 25 October | World and campaign |
| D12 | Earlier engineered waste-eaters mutate after exposure to the separate atmospheric treatment; living organisms occupy scrap shells | Confirmed fictional origin; space support and exact creature design proposed | [Science notes](../01-story/science-notes.md) |
| D13 | Metal Fragments, Circuit Parts, Polymer Pieces, Power Cells; one wallet, enemy-tier values, no crafting gate | Confirmed 23 October; authored source mappings under review | [Scrap types](../03-economy/scrap-types.md) |
| D14 | Alternating story cards and moving footage | Confirmed presentation | [Story/trailer](../01-story/story-context.md) |
| D15 | Intro before menu once per launch; 40-second intro, 24-second ending, 90-second trailer | Proposed pacing/placement | Story/trailer |
| D16 | Neglect and postponed responsibility lead to catastrophe; survivors earn hope through sustained recovery | Confirmed theme; slogan wording drafted | [Theme and slogans](../01-story/narrative-theme.md) |
| D17 | Altered organisms collect indiscriminately and bind retained scrap as armor; inherited traits change across subsequent generations | Confirmed armor direction; detailed biology remains a fictional proposal | [World section 4.1](../01-story/world-and-campaign.md) |

Paid repairs, random trade drops and the shop price list are already specified. They need balance measurements later, not another empty “decide a shop” task.

## 3. What remains missing beyond artwork

These are the areas not fully covered by merely adding a hub, scrap bar or new story. Some have code prototypes; others exist only in the plan. Prioritize resolving P0 data before the relevant future checkpoint. P1 items are necessary for the promised product and presentation, not optional art polish.

| Gap | Priority | Existing evidence / missing contract | Selected next action and owner | Ready when |
|---|---|---|---|---|
| G01 Boss encounter content | P0 before T06 | Old boss names/designs are provisional; no approved complete roster | Owner supplies two campaign guardians and which existing encounters Boss/Chaos reuse; gameplay designer completes template below | Every enabled boss has attack/phase/spawn/death/arena data and a testable objective |
| G02 Mode pressure tables | P0 before T06 | Durations and boss slots are specified; exact ordinary spawn composition, cadence and population budgets are not | Gameplay designer authors each mode/difficulty schedule in game-design.md using existing enemy profiles | Every interval/wave has budget, caps, completion and fallback behavior; no generic-spawner portal masquerades as a mode |
| G03 Equipment access | Written PREP-03 delivered; runtime before T04/T08 | [Beta loadout](../02-gameplay/beta-loadout.md) fixes one cannon/base engine/one persistent shield and defers debug equipment progression | Player owns live shield, SkillSystem owns rank, Game routes one guard/Blink/shield/hull/break sequence; no legacy stack/refill | Written inclusion/ownership contract complete; actual migration/reset/transaction tests remain open |
| G04 Card selection distribution | Written PREP-04/25 delivered; runtime before T03 | [34-card selector](../07-upgrade-proposals/beta-card-selection.md) and [26-node capabilities](../07-upgrade-proposals/card-compatibility.md) define exact grades, prerequisites/weights/gate/draw order and fixed stock | Existing Game/card owners implement distinct locked offers, no pity/promotion, Luck cap and safe invalid-pool restart/menu | Written contract complete; actual catalog/chooser/shop/statistical validation remains open |
| G05 Automatic ability targeting | Written PREP-05 delivered; runtime P0 before T04 | Q33/Q34 confirm independent ability aim and nearest valid single target without boss bias | [19-ability matrix](../02-gameplay/automatic-targeting.md) specifies ranges/selection, stable ID ties, no-target retry, obstacles, cooldown/snapshots and separate group/droid rules | Written contract delivered; manual-to-auto implementation and runtime acceptance remain T04 |
| G06 Mobility automation | P0 implementation | PREP-06/26 written Blink defaults adopted 25 October | Target matrix specifies legal viewport/solid/threat search, no-safe-point behavior, cooldown/protection and no teleport sweep; engine chassis/boost integration remains deferred | Implement/test candidate rejection, failure/no-spend, direct-hit guards and reset without adding a new normal-play skill button |
| G07 Arena/hub geometry | P0 before T05/T06 | Hub behavior is detailed; world dimensions, separation and bounds need actual layouts | Level designer supplies scaled hub and arena diagrams; reuse existing coordinate conventions | Spawn, service radii, gate radii, camera, obstacle clearance and return/resume positions are measurable |
| G08 Scoring and result identity | P0 implementation | PREP-08 specification adopted 25 October | Current game-design weights and results contract replace deposit/old wave/time bonuses | Implement one event ledger and verify all mode/outcome examples; documentation is not runtime delivery |
| G09 Persistence and leaderboard data | P1 implementation | PREP-09 specification adopted 25 October | results-v1.csv, four-mode/difficulty/rules boards, names, bounds, corruption/retry and debug eligibility are specified | Implement/test idempotent saves, result freezing and separate boards without mid-run saves |
| G10 Input and accessibility | P1 | Existing input uses mouse/keyboard; new hub/cards/pause can leak clicks | UI owner documents focus and consumption for each panel; readable labels and distinct shapes supplement color | One action per press; no fire/launch through panels; all required text fits safe area and standard resolution |
| G11 Tutorial sequence | P1 implementation | Q18/PREP-11 adopt in-play tips and the complete copy/trigger/session contract below | Implement through T09 with existing UI ownership and mandatory-panel precedence | First-player review verifies launch, field cards, return blockers, paid repairs and skippable tips without input leaks |
| G12 Story playback lifecycle | P1 | Storyboard exists; current cutscene wiring does not prove playback | Adopt story-context.md's proposed placement/skip routes; programmer validates existing base | Intro, ending, skip, replay per-session rule and frozen results work without hidden simulation |
| G13 Audio behavior | P1 implementation | PREP-13 written contract adopted 25 October; Q32 dark electronic/synth | Audio handoff defines shared tracks, one-owner context/voice routing, buses, serial fades, focus/skip/exit and fallback | Implement/test the transition matrix without stacked music, stale effects, repeated loops or double Master gain |
| G14 High-rank and crowd limits | P0 before scaling release | Rank formulas can keep growing; prior performance baselines do not prove a full new load | Programming owner defines numerical overflow, spawn/effect budgets and visual aggregation without silently capping earned progression | Bounded allocations/queries and retained reward correctness at the declared target load |
| G15 Outcome ordering | P0 implementation | Q19/Q20 confirm same-step boss-clear credit despite player death, followed by run end | Use the game-design outcome contract; no revival/travel; final completion still requires all final objectives resolved | Both event orders, remaining adds, final completion and duplicate callbacks preserve one result and correct boss credit |
| G16 Release and competition readiness | P1 | Eligibility, team-machine validation and submission work remain in tracker | Producer resolves existing eligibility question and confirms actual deliverables; no contact sent by this context task | Approved scope, tested release, disclosures, separate demo/trailer, forms and submission confirmation |

G03-G06 are proposals, not a new implementation instruction. The later team may replace them, but must do so in the authority document before shipping contradictory behavior. A disabled ability or portal is a visible incomplete feature, not evidence that the full requested scope is complete.

## 4. Boss definition template

Create one authored record per final boss before its implementation checkpoint. This template does not choose the owner's boss designs.

| Field group | Required content |
|---|---|
| Identity | Final name, role, material silhouette, source relationship, allowed modes, encounter ID |
| Arena | Bounds, entry and safe spawn, camera framing, obstacles, exit/return rules |
| Stats | Base HP/contact damage, difficulty/level factors applied once, movement speed, collision radius, rewards and material family |
| Attacks | For each attack: windup, readable telegraph, active duration, projectile/contact behavior, recovery, damage, range, target selection and cooldown |
| Phases | HP thresholds, transition duration/invulnerability if any, canceled attacks/projectiles, one-time transition flags |
| Adds | Enemy profiles, cap, cadence, ownership, whether required for completion, source shutdown behavior |
| Fairness | Avoid unavoidable spawn hits; give room to read/dodge; say how safe resume preserves attack state |
| Death | Single resolution, source-emitter stop, remaining-add handling, eligible reward exclusions, cinematic/result transition |
| Tests | Minimum-load clear, strongest supported build, return during every phase, no-loot kill, simultaneous player death, restart and repeated encounter |

Campaign proposes two source sectors. Reusing their bosses in Boss/Chaos avoids implying an additional roster. Their mode-specific outcomes must still differ: Boss ends the encounter, Chaos continues and Campaign advances/ends its source objective.

## 5. Mode schedule template

For every enabled mode and difficulty, specify: encounter seed/rules version; startup delay; spawn ring/allowed region; enemy mix; alive cap; spawn budget and spend rules; escalation interval; wave-clear versus time-window conditions; boss schedule; source-add ownership; cleanup/despawn behavior; pause/hub suspension; retirement/success/defeat criteria.

Default envelopes already selected: Swarm endless without bosses; Survival 300 combat seconds; Boss one encounter; Chaos first boss at 180 combat seconds then at least 180 seconds after the prior boss dies, one alive; Campaign ten waves with bosses at five/ten. These envelopes are not full spawn tables. Do not claim that schedule design is finished until each row can be simulated without the implementer inventing new numbers.

## 6. In-play tutorial - Q18 confirmed, 24 October

Owner selected short, skippable tips while playing instead of a separate practice screen. The following copy/triggers are adopted as delegated beta defaults. Tips teach existing actions; they do not create objectives, rewards, free travel or a new game scene.

| Step | Trigger | Short message | Completion / repetition |
|---|---|---|---|
| H1 Arrival | First hub arrival in a new application session | “Fly to a mode portal. Press F to review its mission.” | Dismiss after portal preview; eligible once per application session |
| H2 Services | First service panel opened | “Repairs and skill upgrades cost Trade Scrap.” | Close with the panel; real prices remain visible |
| F0 Combat | First combat launch | “Aim with the mouse. Hold Shoot to fire, or press E for auto-fire.” | Nonblocking; complete on firing or toggling E, or hide with tips |
| F1 Recovery | First credited pickup | “Trade Scrap buys services. Salvage earns upgrades and charges return portals.” | One short nonblocking prompt; do not pause enemy simulation just for flavor |
| F2 Level | First queued field choice | “Choose an upgrade. Your next level needs more Salvage.” | Existing mandatory card panel owns input; do not stack a tutorial modal |
| F3 Return ready | An ordinary return portal is available with sufficient energy and an online positive shield | “Return portal ready. Press F inside it to visit HOPE.” | Once per application session; HUD carries later readiness; never fire this tip in Boss mode |
| F4 Return blocked | First attempted ordinary portal interaction with broken shield | “Shield offline. This return portal is locked.” | Immediate feedback on every blocked attempt; extended explanation only first time; no false lock on unrestricted clear portals |
| H3 Resume | First successful field-to-hub return | “Repair, upgrade, then resume this expedition.” | Highlight Resume; choosing another mode explains fresh-run reset |

Store seen/dismissed steps and the tips-hidden flag in application-session UI state, outside the individual run; no new save-file key or permanent gameplay state. Restart/death clears pending run-specific hints, while completed tips remain seen for this application session. Fresh application launch enables tips again. Pause Help provides Hide Tips / Show Tips; Show Tips permits unseen tips without replaying completed ones. Safe hub/pause tip panels also offer Skip Tips, which hides optional tips for the session. Combat tips remain passive and require no click or forced acknowledgment.

Show at most one applicable tip. Mandatory panels (cards, shop, confirmation, map, results), pause, console and story take precedence; hide the tip and retain only still-relevant unseen candidates. Coalesce repeated triggers by step ID; drop stale candidates on source/run changes. A required action completing while its tip is hidden still marks that step seen. Tips cannot steal aim, movement, Shoot/E/F or Esc, create their own pause, consume RNG, change cooldowns or alter outcomes. A safe-panel dismissal consumes its input so it cannot also fire, launch or buy. Use the existing safe-area caption style, wrap text clear of HUD/telegraphs and do not attach tutorial narration to combat tips. Required transaction/portal errors and mission controls remain visible after Skip Tips.

Acceptance: first launch teaches hub/fire/pickup/cards/return/services; Skip Tips hides optional prompts while lock/error feedback remains; repeated deaths do not repeat completed tips; focus pause and card selection suppress tips without input leakage; Boss mode never advertises ordinary retreat. PREP-11 copy/trigger contract is adopted; T09 runtime integration and first-player readability review remain open.

## 7. Result contract - adopted 25 October

[Scoring/results specification](../02-gameplay/results-and-leaderboards.md) and the matching game-design numerical ledger now replace this section's older proposal. They define awards, anti-farming, retirement/mutual outcomes, active time, fields, tie order, eligibility, versioned CSV, names, corruption recovery and once-only saves. PREP-08/09 documentation is delivered; PROJECT-06 and scoring integration remain open. No online account, persistent ship progression or mid-run save is introduced.

## 8. Remaining delegated authoring and factual dependencies

On 25 October the owner stopped further questions. Continue authoring from existing choices: title is SCRAPBOUND: Last Hope, biological origin/neglect theme and four-boss/four-level beta are selected; numerical targeting/spawn/compatibility/lifecycle details remain delegated. Preserve unknown human release facts instead of inventing them. Existing repair/shop and authored score tuning need later runtime playtesting, not speculative reapproval. Do not revive the obsolete broad-deferral or no-content-authorization language.

Preparation is ready for an implementation brief only when blocking content and data have an explicit owner, an adopted default or a documented deferral that is visible in the product scope. “Everything is done” cannot mean merely that all missing details have a heading.
