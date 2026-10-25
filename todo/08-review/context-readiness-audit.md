# Context and release readiness inventory - 24 October 2026

**Current25 October DOC-59:** [Complete implementation handoff](../00-planning/implementation-handoff.md) delivers all six remaining written game-context areas and supersedes the older missing-data/owner-away snapshots below. All game-content defaults needed by the listed implementation slices are supplied; Q46 optional red low-hull edges/configurable shake recorded. Eleven written PREP tasks closed;32 actual implementation/production/runtime-review/release tasks remain. PREP-16 actual human release facts and PREP-30 owner audit approval remain open. Written readiness is not playable-beta/release readiness; no code/assets/media or human playtest delivered.

**Current owner-away workflow, 25 October:** Context/planning Markdown only; hold questions and continue delegated authoring. PREP-03 loadout, PREP-04/25 full card selection/acquisition, PREP-23/24 numeric-source/Luck and PREP-20 material source coverage are written, alongside Q43–45 feedback/HUD. Actual source/art/renderer/statistical/readability/numerical-safety work remains open. Current umbrella count is 43; dated workflows/counts below are historical.

**25 October DOC-44/45 update:** Q35 confirms hiding cards until useful; structural compatibility/new-acquisition/preserved-rank/locked-offer rules are written, with exact per-weapon mapping and rarity still open. Q36 confirms 2718/2723/2732/2733; final narrative copy/media remain open. These partial policy decisions do not close additional umbrella tasks; count remains 49.

**25 October current status:** Latest clarification permits short game-content questions only; administrative questions stop and routine technical/Campaign authoring stays delegated. Score/results, creature/audio direction, [targeting and Blink safety](../02-gameplay/automatic-targeting.md#blink-exact-safe-candidate-contract) complete PREP-08/09/18/13/05/06/26 writing, leaving **49 open umbrella tasks**. Player-entered Cadet identity is specified. Q34 confirms nearest valid single target without boss bias; wave/boss/weapon-compatibility and remaining lifecycle/UI/performance context still need authoring. Runtime UI/scoring/art/audio remain pending. Cutoff hour/hardware/evidence stay unconfirmed; uploader explicitly unassigned. Earlier counts/question workflows below are historical.

**Q22 ownership update:** Implementing teammate makes trailer and gameplay demonstration with AI assistance; owner prepares context. [Production handoff](../01-story/story-context.md) and PROJECT-08/09 record that assignment. No media completed; final upload owner, hardware, cutoff and release/provenance evidence remain missing. Earlier references to all team assignments being unknown are historical.

**Q19/Q20 update:** Same-step player/boss death retains boss-clear credit and ends the run without revival. [Outcome contract](../../context/game-design.md#24-october-simultaneous-boss-clear---q19q20-confirmed) completes PREP-15 documentation, leaving **56 open umbrella tasks**. Runtime, exact scoring and result schema remain open. Older task counts are historical snapshots.

**Q17/Q18 update:** Every fresh run starts with a working basic shield; existing rank-1 Deflector tuning is the delegated default, with no duplicate shield or same-run travel refill. Tutorial direction is confirmed: short skippable tips during play. [Adopted tutorial contract](../00-planning/decisions-and-gaps.md#6-in-play-tutorial---q18-confirmed-24-october) completes PREP-11 documentation, leaving **57 open umbrella tasks**. T04/T09 integration and first-player tests remain open. Earlier counts below are dated snapshots.

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

## 4. Written contracts delivered; actual acceptance remains

The six remaining context areas are supplied by [the implementation handoff](../00-planning/implementation-handoff.md). PREP-01/02/07/10/12/14/19/21/22/27/29 concern written readiness and are delivered. These rows distinguish that from features, assets, measurements and human approval.

| Area | Current written authority | Actual work still needed |
|---|---|---|
| Mode waves/difficulty/bosses | [Encounter appendix](../02-gameplay/beta-encounters.md), all15 waves/3 difficulties/4 guardians | Heavy/boss/director code, telegraphs, real clears/pacing/weapon viability |
| Hub/spawn/portal geometry | [Layouts](../02-gameplay/beta-layouts.md), encounter geometry and [return lifecycle](../02-gameplay/return-portals.md) | Actual legal search/navigation/input/suspension/protection/camera checks |
| Starter/automatic skills/shield | [Loadout](../02-gameplay/beta-loadout.md), [targeting](../02-gameplay/automatic-targeting.md), all19 rank overrides | Single-shield/auto migration, exact events, real rebuild/reboot/Blink cases |
| Cards/rarity/weapon combinations | [Chooser](../07-upgrade-proposals/beta-card-selection.md), [capabilities](../07-upgrade-proposals/card-compatibility.md), [composition](../07-upgrade-proposals/weapon-composition.md) | Actual34 catalog/sampler, all26 handlers/signatures and scalar/aggregate equality |
| Numeric economy/materials/Luck | [Attribute/Luck](../03-economy/attribute-and-luck-contract.md), [source mapping](../03-economy/scrap-types.md) | Actual metadata/transactions, conserving collection/merges and measured income/repair burden |
| Results/identity | [Four-mode record contract](../02-gameplay/results-and-leaderboards.md), [Cadet identity](../01-story/player-identity.md) | Actual score ledger/frozen record/board/save/UI integration and file-failure cases |
| All panels/preferences/accessibility | [Input/settings matrix](../02-gameplay/ui-input-and-settings.md), UI rules and tutorial | Real focus/input/long-text/CRT checks, Q46 warning/shake settings/rendering, actual audio |
| Story copy/playback | [Final production script](../01-story/final-production-script.md), source-checked planned base and14 voiced beats | Teammate assets/voice/cues, inherited cutscene code,40/24 playback and90-second export, human review |
| High ranks/performance | [Numerical/load appendix](../04-verification/numerical-and-load-contract.md) | Exact checked/log/event implementation, frame-time/memory/equivalence benchmarks and disclosed hardware limits |
| Dependencies/reset/RNG | [H00–H14 handoff](../00-planning/implementation-handoff.md),8 domains and lifecycle matrix | Actual reset/suspend/terminal behavior, no duplicate owners/IDs or progression leaks |
| Human release evidence | PREP-16/30 and PROJECT release tasks | Actual eligibility/source history/licenses/forms/hardware, assigned uploader/receipt and owner audit approval |

All new tuning is delegated initial design, not individually approved numbers or measured balance. No remaining human fact is invented and no admin question/contact/submission is triggered by this review. Historical findings below explain why old text is superseded; they do not reopen supplied defaults.

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
