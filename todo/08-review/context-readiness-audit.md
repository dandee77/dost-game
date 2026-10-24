# Context and release readiness inventory - 24 October 2026

**Background/checkpoint update:** Owner requested [instructions for teammate background production](../09-art/background-brief.md), with no generation here. Cleared Campaign waves now offer optional Enter Station or direct continuation; this supersedes earlier compulsory base visits. Choices preserve actual ship/build and finalize rewards once; services stay paid, and ordinary mid-fight/Boss policies remain distinct. Runtime and art delivery remain open.

**Questionnaire update:** [Answer register](owner-questionnaire.md) records persistent unlocked-level availability, delegated Campaign details (no more questions), score-first endless rankings with survival time, focus pause/Resume, three audio sliders, Medium-default graphics and local preference persistence. Credits use placeholders; Payload is primary-only; intro/ending require original English AI narration. Exclusive branch locking is retired: three or four levels may be visited before the ending. Wave/targeting/score-weight/settings/audio production and runtime remain unfinished. Hardware facts remain unknown.

## Purpose and current instruction

The owner wants both detailed context and a playable build ready ASAP, and explicitly prioritizes completing the context first. The original creator will use the context to prompt implementation on **25 October**. This checkpoint gathers unfinished work and records delegated beta choices; it does not treat drafts as implemented gameplay. The owner reports no additional completed work outside this repository. Other team assignments have not been supplied.

The owner clarified the earlier Monday answer: context must be ready **tomorrow, 25 October 2026**, for the teammate's implementation handoff. The repository also states a 25 October competition date, with an earlier internal submission target of 24 October. Exact official cutoff hour remains unconfirmed. Do not assume the corrected handoff target changes the official deadline or guarantees the playable build is complete then.

Current choices: **SCRAPBOUND: Last Hope**; four authored levels C01 -> C02/C03 -> C04, with either or both middle levels available before the final. [Stage contract](../02-gameplay/campaign-stages.md) and [layouts](../02-gameplay/beta-layouts.md) record data/edge cases. Around 30 minutes or less applies per selected level, with exact pacing delegated and difficulty targets in game-design.md. Detailed spawn budgets remain unfinished.

Owner reports that the original creator will prompt implementation. That identifies the implementer; prior publication/competition history and contributor coverage were not supplied, so the existing eligibility evidence task stays open. No new clearance claim is made.

This inventory uses the current authority sections, task registers, detailed briefs and a targeted source inspection. It is not a fresh runtime playtest or an exhaustive line-by-line code audit. Existing build/test/performance records remain dated evidence for their original workloads.

## 1. What is already available

Retain these delivered systems rather than rebuilding them from unchecked historical umbrella items:

- Ship movement, primary combat, low/ranged enemies, debris, existing menus and game-over/restart paths.
- Spatial collision queries, low-enemy separation, debug console and equipment prototypes.
- Fourteen prototype augments and eighteen prototype abilities, including repeat upgrades and cast snapshots. These are not the final automatic 34-card target catalog.
- Accepted low-enemy/debris/projectile artwork, debris destruction and harvesting, and the barricade event.
- Pause-safe combat timing and animation updates; a complete visible pause/settings interface is still pending.
- Population-led ordinary spawning, bounded ordinary HP, separate stored trade/salvage rewards, paired persistent enemy loot and salvage-driven queued level choices.
- Pure XP/repair/battery/return calculations in RunProgress.hpp. Calculations do not provide a playable hub, service berth, shop or portal.

Source inspection confirms that Game currently has RUNNING, AUGMENT_SELECTION, PAUSED and OVER states. The source tree has no implemented WaveDirector, Boss subclass, hub/shop, Campaign map, cutscene, leaderboard or credits system. CollisionSystem and Pause filenames exist as placeholders; filenames alone are not delivery evidence.

## 2. Work-register snapshot

At the start of this review, tasks.md contained **59 unchecked umbrella tasks**:

| Group | Open items | Meaning |
|---|---:|---|
| BAL | 1 | Remaining balance/integration work, including high-rank behavior |
| PREP | 29 | Content, contracts, review and human facts; PREP-28 battery design is checked |
| T01-T10 | 10 | Runtime checkpoints; T01-T03 have delivered subparts |
| PROJECT | 12 | Foundation, presentation, assets, videos, forms, packaging and submission |
| REVIEW | 7 | Consistency, playtesting, reset, performance and release review |

These are not 59 equally sized programming jobs. Several overlap, and some preparation checkboxes still describe choices already settled in newer authority sections. PREP-17 title selection is resolved in this checkpoint, leaving 58 open umbrella tasks once its documentation checks pass. Reconcile remaining acceptance conditions before estimating work or asking the owner again.

## 3. Context readiness standard

A context area is implementation-ready when it states the current target, current runtime baseline, data, owner, state transitions, input handling, failure/edge cases, resets and observable acceptance tests. Every draft must be labeled, and each remaining dependency needs an answer, an authoring owner or an explicit scope decision.

A detailed document is not enough if it leaves the implementer choosing fundamental rules. Equally, historical prototype tables must not be rewritten as if the new target already runs.

| Shared file | Attention needed before the context handoff is called complete |
|---|---|
| project-overview.md | One current four-mode product summary, selected Campaign scope/identity and explicit release facts. This checkpoint corrects its five-mode scope bullet and obsolete Q control; broader historical reconciliation remains. |
| progress-tracker.md | A concise current status and next checkpoint, accurate partial deliveries, current open questions and dated verification limits. Preserve historical logs, but stop sending readers to already-settled reset/boss policy questions. |
| build-plan.md | Replace the completed DOC-20 current checkpoint with the next real checkpoint, align current tasks with T01-T10 and separate the old sprint schedule from a usable remaining-work sequence. |
| architecture.md | Complete four-mode data/state ownership, Campaign/map transitions, world suspension, source/outcome finalization, RNG streams and input precedence. Historical two-mode/cargo diagrams must be clearly separated from current targets. |
| class-registry.md | Reconcile actual APIs/status with source; revise obsolete planned contracts for director, shop, HUD, results and multiple bosses. A single getBoss pointer cannot describe the full concurrent-Chaos target. Preserve inheritance and existing ownership. |
| code-standards.md | Preserve style/templates; align examples/checklists with the current RNG ownership, settings, shop and F5 tooling. Its Definition of Done still refers to an F1 overlay. |
| library-docs.md | Reclassify known pitfalls as current, fixed or historical using source evidence. It still calls SpatialGrid unused and repeats old timed-card/string-dispatch findings. Preserve valid Raylib/build traps. |
| game-design.md | Beta stage counts/graph and layout geometry are now recorded. Still fill wave/difficulty data, automatic targeting, card compatibility, scoring and numerical/performance contracts; reconcile competing boss/portal/phase rules. |
| ui-rules.md | Complete current screen/panel states, map layouts, four-gate hub, settings, errors, previews and input/focus rules. Old five-portal, growing-energy and combined-shield-service descriptions conflict with newer decisions. |
| skills-context.md | Promote the 34-card target and automatic/persistent rules to a clear current section. Retain the 32-entry prototype separately. Workshop-only Luck/manual Return Home are superseded. |
| skills-commands.md | Keep commands truthful to the executable, including current manual Q behavior; update stale timed-picker and reward-deferral descriptions after source checks. Do not advertise future commands. |
| collision-performance.md | Retain measured historical workload/machine evidence. Make clear that it does not certify the final skills/bosses/high-rank build or another PC. |
| crowd-performance.md | Retain its distinct measured workload and hardware. Define which final-load tests must be repeated; do not invent a new performance result from old counts. |

The topic briefs under todo/ must agree too. Prioritize gameplay.md, campaign-stages.md, boss-roster-draft.md, the three upgrade proposals, story/world framing, the decisions register, preparation checklist and task/idea registers. Updating only a top-of-file notice leaves contradictory implementation instructions below it.

## 4. Concrete specifications still needed

| Area / task IDs | Detailed content still missing | Readiness evidence |
|---|---|---|
| Campaign stages - PREP-01/02, T06 | Four authored nodes; three or four may be visited because unfinished alternatives stay available. OR merge and no beta miniboss. Still author wave composition/budget/cadence/caps and difficulty data; account for optional-level builds. | Complete encounter tables; availability, continuation, base visits, final clear and reset tests. |
| Mode pressure/difficulty - PREP-02, T01/T06 | Full Swarm/Chaos ordinary schedule, Boss encounter order/repetition and Campaign wave tables. State exactly how Easy/Hard/Impossible change pressure while preserving selected HP/damage/economy rules. | Every mode/difficulty has deterministic spawn/completion data; Swarm/Chaos ordinary rules agree. No Survival objective remains active. |
| Bosses - PREP-01, T06 | Implementable records for Shellback, Coilmaw, Brood Hauler and Nestheart: source/stage placement, move/attack state machines, three-phase variations, legal targeting, add ownership, hazard cleanup, rewards and multiple-instance identity. Concepts and numerical attack drafts already exist. | One record per enabled boss plus mode-specific death/add rules; overlapping major attacks and named HP bars are testable. Exact tuning remains distinct from measured balance. |
| Starter/equipment - PREP-03/22/27, T04/T08 | Define the normal starter, final use of existing debug presets, authoritative shield source and weapon tree state. Complete every weapon/card mapping and no-effect eligibility rule. Engines remain deferred unless selected. | Every normal-play acquisition has one route; debug-only components do not appear as unavailable promises; equipment shields cannot stack accidentally. |
| Automatic skills - PREP-05/06/25/26, T04 | For all 19 abilities: trigger, targets, range, tie order, aim source, no-target retry, cooldown commit, cast snapshot, persistence, break/rebuild and hub/pause behavior. Exact Blink candidate safety and droid reservations need concrete data. | A complete per-ability targeting/lifecycle matrix with examples and failure cases. No manual combat skill button is introduced in the target. |
| Shield/damage - PREP-03/15, T04 | One damage order covering existing protection, Blink, online shield/full breaking-hit absorption, break event, reboot, ordinary immunity and hull damage. Clarify status ticks and shared-event handling. | Tables cover small/large breaking hits, multiple hits, zero shield, battery replacement, paid capacity, break detonation and same-step death. |
| Field cards/rarity/Luck - PREP-04/24/25, T03 | Full 34-entry typed roster, proposed grades/weights, eligibility/prerequisites, distinct offer generation, ordinary-pool exhaustion, Legendary gate, Luck spawn snapshots and rank-10 exclusion. Existing drafts need one adopted current contract. | Worked offer/reward examples and deterministic RNG/queue behavior, with confirmed versus delegated tuning labeled. |
| Weapon/attribute shop - PREP-22/23/27, T08 | All 26 nodes/edges and ten signatures; exact card compatibility, descendant damage ownership, cooldown preservation, numeric source counts, skill-rank/special stock and transaction previews. Prices/formulas already exist. | One transaction table for buy/deny/cancel/stale quote/repeat input and one compatibility table; no free healing, rank or signature refresh. |
| Hub/arena/portals - PREP-07/29, T05/T07 | Dimensioned hub/arena/portal defaults now drafted; complete encounter spawn placement, boss-clear portal geometry and validate actual reachability/input/protection order. | Layout checks in world units and runtime readability/reachability checks; F/gates/counts already selected. |
| Economy/materials - PREP-20/23/24, BAL-01/T02/T07/T08 | Complete per-variant material assignment, value-preserving merge rules, enemy/debris pickup budgets and no-expiry separation, quote/service edge cases and planned income/spending measurements. | No ambiguous source mapping or duplicated wallet; paid service and rewards conserve values, with expected versus measured results kept separate. |
| Scoring/results/leaderboard - PREP-08/09/15, PROJECT-06 | Four-mode score formula, progress/outcome fields, retirement, anti-farming, tie rules, versioned local schema, name entry, corrupt-file recovery, debug eligibility and one-time finalization. | Worked example per mode/outcome and duplicate-save/ending-skip tests; no retired cargo/deposit bonus. |
| UI/tutorial/settings/audio - PREP-10/11/13, T09 | Layout/state inventory for all S-01-S-14 experiences, map/shop pagination, disabled reasons, input capture, focus-loss policy, tutorial copy/triggers and volume/music/SFX transitions. | One action per press, safe-area/readability cases, sound-off comprehension and no stacked music or hidden combat. |
| Story/identity/presentation - PREP-12/17/18/19, PROJECT-05/07/09 | Title selected. Still supply team identity, final copy/proposed-date review, staged-Campaign alignment, moving-action assets and playback/skip/result handoff. | Shot/asset inventory and timed 40/24/90-second draft continuity; story-only text is not exported media. |
| Lifecycle/RNG/reset - PROJECT-02/03, REVIEW-03 | One state/transition table covering New Game, death, quit, pause, cards, hub, ordinary retreat, wave-clear transit, Boss clear and stage completion; RNG seeds/streams and ownership of every run-local value. | Every system has a reset/suspend/preserve rule; repeated callbacks cannot award or advance twice. |
| High ranks/performance - PREP-14, BAL-01, REVIEW-04 | Safe representation of uncapped attributes/counts, critical tiers, extreme firing rates, fractional damage, signature/proc timing, storage growth, cosmetic budgets and explicit failure reporting. | Equivalence tests compare normal and aggregate paths; target machine/load/frame-time/memory criteria are measurable. Existing benchmarks do not prove this work. |
| Release/human evidence - PREP-16, PROJECT-01/08-12 | Exact deadline; assigned people; target PC; inherited-code history/eligibility evidence; font/audio/reference licenses; final assets; registration, signed forms, synopsis, separate videos, package and upload owner/receipt. | Actual evidence and files, not planned checkmarks. This review sends no external messages or submissions. |

Routine targeting, layout, pricing implementation, score drafting and numerical safety work are already delegated in the latest review. Author concrete proposals and identify tradeoffs; do not repeatedly request generic implementation permission. Product choices and human facts remain legitimate questions.

## 5. Conflicts needing reconciliation

These are findings for REVIEW-01, not fresh gameplay decisions:

| Conflict | Current rule to preserve | Files/sections to reconcile |
|---|---|---|
| Four modes versus five gates/Survival | Swarm, Chaos, Boss, Campaign only | Overview scope, UI target table, TODO index/checkpoints, decisions D02, story mode framing, task T06 |
| F portals versus manual Q Return Home | F inside eligible world portal; no manual teleport skill | Overview controls, skills-context introduction, older tutorial/handoff text |
| Fixed energy versus level-driven maximum | Capacity 1000, ordinary threshold 500 | UI meter text, older gap/idea entries and preparation scenarios |
| Repeating Boss loop versus one-fight victory | No retreat; post-kill unrestricted portal; base then next boss | game-design boss-draft reward paragraph, boss-roster draft body, old mode envelopes |
| New boss phases versus old phase trigger | Latest draft uses 60%/30%; thresholds are tuning | game-design boss-loop section versus its later 50% paragraph and historical boss records |
| Legendary card-only Luck versus workshop-only | Card-only acquisition/upgrades, max rank 10, scrap only | skills-context, IDEA-20, old proposal/review headings |
| 34-card target versus 32-entry prototype | Keep target and actual command catalog separate | skills-context/commands, preparation checklist and review snapshots |
| Unlimited progression versus old caps | No fixed attribute/army/skill cap, with Luck-10/T5/physical-size exceptions | Current offer/stat implementation, old shop/skill examples and proposed contracts |
| Separate batteries versus combined shield service | Paid hull berth and separately purchased battery | UI target table and old repair/handoff references |
| Salvage choices versus timer/wave-clear cards | Current choices are earned from salvage; waves alone grant no free pick | class-registry Game gotchas/WaveDirector plan, skills-commands, library pitfalls, old build-plan packages |
| Current APIs versus legacy planned interfaces | Reuse existing owners, paired rewards and concurrent-boss identities | Registry ScrapPickup/ScrapManager/HUD/CollisionSystem/UpgradeShop/RunContext/director entries |
| Historical restrictions versus current authorization | Context first in this session; implementation remains an eventual authorized goal | Old no-code/no-questions/no-assets restrictions and owner-deferred flags, clearly separated by date |
| Dated test records versus release validation | Preserve dates, machine and workloads; perform final-feature tests later | Performance reports, empty playtest/machine QA tables and release checklist |

Source checks also confirm current direct score-sound loading on Game entry and unchecked Animator completion lookup, already recorded in the older foundation issues. The registry's prevGameTimer/timer-trigger narrative is stale: current Game uses RunProgress queued choices and resetRun clears gameOverTextStarted. These require accurate classification, not blanket repetition of every old bug as current.

## 6. Decisions already settled - do not ask again

- Four modes; Survival removed; Swarm and Chaos share ordinary mechanics, Chaos adds bosses.
- Fresh gameplay progression on New Game; same-expedition hub visits preserve the run.
- Campaign map circles are whole stages; stage 1 is initially available; predecessor clears unlock connected successors within the run.
- Stage 1 has five normal waves and a separate boss; cleared waves offer optional station or direct continuation; carry builds across levels with no free healing.
- Boss mode repeats boss/base/next-boss, forbids retreat and gives one shield/energy-free post-kill portal.
- Ordinary portals use F, fixed 1000/500 energy and online positive shield; counts are 3/2/1 by difficulty.
- Two-second re-entry protection, no hull/shield refill; delegated auto-fire/offensive-skill delay and deliberate-fire cancellation.
- One trade wallet and separate fixed salvage; selected four material labels and no crafting gates.
- Weapon prices 500/1500/4000/10000; one branch per run, 26 nodes and ten finals; paid numeric gains at 25% of field-card gains.
- Paid hull repair at 10 scrap/missing HP, proportional affordable repair and no free hub restoration.
- Five battery sizes with replacement arithmetic and capacity-scaled prices; Power Cells are ordinary salvage.
- Full absorption of the shield-breaking hit; persistent droids with individual 20-combat-second rebuilds and spread fire.
- Uncapped combat skills/armies/numeric attributes, stronger crit tiers above 100% and continuing firing-speed gains; performance remains work.
- Legendary reactive Blink, Legendary card-only Luck capped at 10, Epic Blast Radius; total target roster 34.

## 7. Questions to settle with the owner

### Answered in this session

1. Context first, for the original creator to prompt implementation tomorrow, 25 October; no external completed work reported.
2. Branching Campaign, beta count delegated: four-node graph, counts 5/3/3/4, four bosses. Later Q1 confirmed all unlocked unfinished levels remain available, permitting three or four visits before final completion; no further Campaign questions.
3. Title is the saved Last Hope option: SCRAPBOUND: Last Hope. Layout authoring delegated from current HOPE direction.
4. Original creator will implement; earlier publication history still unverified. Official deadline hour was not supplied.

### Pacing clarification resolved

Owner clarified that selecting any map circle enters one Campaign level, intended to take around 30 minutes or less, with exact duration delegated. Stage and level are technical/player-facing synonyms. Author's proposed graph traversal was not a whole-map time limit. Beta targets now increase from C01 to C04 by difficulty, reaching 30 active combat minutes on final-level Impossible. Clock exclusions and objective-based completion are specified; actual budgets and playtests remain unfinished.

### Following rounds, after those answers

- Credits use owner-approved placeholders. Intro/ending require original English AI narration; production files/provider and release responsibilities remain unfinished.
- Author actual wave budgets from the selected per-level/difficulty targets; do not ask the owner to repeat this pacing choice or choose each tuning number.
- Any new preference the owner supplies that changes the drafted hub/readability/presentation. Geometry and routine implementation details are delegated, so no new generic layout approval is required.
- Actual target PC and who supplies inherited-code history, asset/license evidence, forms, recordings and submission. Do not invent completed work or team commitments.

Only send a small related group at a time. Keep this inventory as the full list so the owner does not need to answer dozens of unrelated questions at once.

## 8. Sequence for finishing context before implementation

1. Campaign extent/map, title, handoff date and per-level pacing are recorded. Author remaining numerical tables; retain missing official release facts as explicit human dependencies.
2. Reconcile current statements across overview, numerical ledger, architecture, UI, skills, registry and TODO, preserving historical evidence in clearly marked sections.
3. Author complete stage/mode/boss data, then automatic targeting, damage/shield order, card/weapon compatibility and shop rules.
4. Complete dimensioned layouts, state/input/RNG/reset matrices, scoring/results, tutorial/audio and story-production inventories.
5. Make build-plan.md identify a concrete next implementation checkpoint; reconcile the 59 open umbrella tasks into implemented subparts, remaining specifications, runtime work and human deliverables.
6. Verify Markdown links/tables/whitespace, formula examples, unique IDs/catalog coverage, graph reachability and cross-document consistency. Mark only verified documentation work complete.
7. Implement one buildable checkpoint at a time, with current acceptance cases. Then perform integrated playtesting, release packaging, recordings/forms and submission verification.

This is a dependency order, not a promise that the full requested product fits a particular number of hours. If the remaining runtime scope cannot be verified before the actual deadline, present concrete scope choices to the owner; do not silently remove modes, stages or bosses.
