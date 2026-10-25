# TODO — Remaining Work

**Latest25 October DOC-60 review:** [Handoff supplement](00-planning/implementation-handoff.md) closes technical consistency gaps for fault records, return-guard projectile/status handling and P/Esc/focus/stall input. Both remotes were already synchronized before review. Documentation/build checks pass; no additional required gameplay answer found. **32 actual-work tasks remain**; no new code/assets or playable-feature completion is claimed.

**Current —25 October DOC-59: written game context ready for implementation.** Start with [the complete handoff](00-planning/implementation-handoff.md). All six remaining specification areas are supplied, including Q46's optional red-edge warning/shake settings. Eleven written PREP items closed; **32 umbrella tasks remain for actual implementation/production/testing/release/human review**. These are not unanswered design questions. Current changes are context Markdown only; owner is available for needed content, with no further answer required for this handoff. Older delivery counts/owner-away instructions below are historical.

**Latest written delivery — 25 October DOC-58:** [Material source coverage](03-economy/scrap-types.md#3-assignment-rules) completes PREP-20 with explicit debris, basic/ranged/heavy and guardian mappings plus future source/visual acceptance. Current open umbrella count **43**. Metadata/art/runtime implementation remains open; these are not 43 unanswered questions. Context files only, with questions held while owner away. Earlier counts are historical.

**Latest written delivery — 25 October:** PREP-23/24 [numeric attributes and Luck](03-economy/attribute-and-luck-contract.md) is adopted from existing defaults, including exact source/price/payout/snapshot math. Current open umbrella count **44**; source/asset/runtime/economy work remains open. Context/planning only, questions held. Earlier dated counts are historical.

**25 October latest written delivery:** [34-card chooser/rarity/acquisition](07-upgrade-proposals/beta-card-selection.md) and [26-node card capabilities](07-upgrade-proposals/card-compatibility.md) complete PREP-04/25. Current open umbrella count **46**. Actual gameplay code/assets/statistical/readability work remain open. Context/planning only; hold questions while owner away. Earlier counts are historical.

**25 October latest delivery — context only:** PREP-03's [beta loadout/equipment inclusion](02-gameplay/beta-loadout.md) specification is delivered. One normal cannon/base engine/persistent shield, no legacy stacking or station reinitialization. Runtime remains open; current umbrella count is **48**. Owner is away: hold questions and continue Markdown preparation. Earlier counts below are historical snapshots.

**Current instruction — owner away:** Hold questions until they return; continue delegated context authoring. Q45 compact owned-ability HUD is specified for all 19 entries in [UI rules](../context/ui-rules.md#compact-automatic-ability-hud--q45-confirmed-25-october). Actual icon art/metadata/renderer remain open; 49 open umbrella tasks. Earlier question workflows below are historical.

**25 October Q44:** All positive outgoing hits show damage numbers, with explicit critical styling and accurate applied totals. [Popup contract](../context/ui-rules.md#floating-damage-numbers--q44-confirmed-25-october) reuses existing indicator owners and groups rapid hits only by target/tier. Source integration/readability/performance remain open; 49 open umbrella tasks.

**25 October Q43:** Damaged normal enemies show small overhead HP bars; bosses retain named bars and phases. [Written display rules](../context/ui-rules.md#damaged-normal-enemy-health-bars--q43-confirmed-25-october) cover real scaled max HP, visibility, layout/presets and overlap. Actual storage/rendering/readability validation remain open; 49 open umbrella tasks.

**25 October Q42:** All spoken lines receive English captions, including voice over moving footage. [Cue/readability/playback/export contract](01-story/story-context.md#complete-narration-captions--q42-confirmed-25-october) preserves separate main story cards and avoids duplicate overlays. Actual cue/audio assets, renderer and exports remain open; 49 open umbrella tasks.

**25 October Q41:** Shared original AI-generated English narrator sounds natural and human, calm and serious. [Production instructions](09-art/audio-direction.md#narration-and-sound-effects) preserve one profile; teammate handles remaining voice-production details. Actual audio/playback remain open; 49 open umbrella tasks.

**25 October Q40:** Compatible firing-pattern cards remain beside station-only cannon evolution. [26-node qualitative matrix](07-upgrade-proposals/weapon-tree.md#pattern-card-compatibility-by-cannon-node) specifies eligibility and root/secondary/signature boundaries. Numerical combinations/remaining mappings/runtime stay open; 49 open umbrella tasks.

**25 October Q39:** Story states **an estimated 1% of humanity remained by 2732**, derived from the existing roughly 99% loss. World/intro/trailer/science copy agrees; no absolute headcount established. Final copy review/media remain open; 49 open umbrella tasks.

**25 October Q38:** Upgrade offers require one explicit valid card pick; no Skip or deferred combat. [Choice/queue policy](07-upgrade-proposals/automatic-skills-and-rarities.md#4-proposed-field-offer-weighting) preserves locked offers across pause/focus and processes pending choices before resuming. Empty-pool recovery and runtime remain open; 49 open umbrella tasks.

**25 October Q37:** Legendary field cards stay random, with no pity guarantee or miss-streak increase. [Policy](07-upgrade-proposals/automatic-skills-and-rarities.md#4-proposed-field-offer-weighting) is confirmed; numerical gate/grades/acquisition and runtime remain open. Umbrella count stays 49.

**25 October Q35/Q36:** Cards hide until useful to the current build; [eligibility policy](07-upgrade-proposals/attributes-and-luck.md#current-build-card-eligibility--q35-confirmed-25-october) preserves owned ranks and useful new abilities. Exact weapon mapping/rarity remain open. Story dates 2718/2723/2732/2733 are confirmed; final copy review remains open. No runtime/media delivery; umbrella count remains 49.

**25 October current workflow:** Owner clarified: questions only about needed game content, one at a time. Routine technical/numerical and remaining Campaign details stay delegated; no administrative questions. Score/results, creature/audio direction and Blink safety writing are delivered; Cadet identity is specified. Q34 nearest-threat confirmation completes the written [target matrix](02-gameplay/automatic-targeting.md). Current open umbrella count: 49. Runtime/art/audio remain unfinished and unconfirmed human facts stay explicit; earlier counts/workflows below are historical snapshots.

**24 October Q19/Q20:** Simultaneous player/boss death records boss clear and ends the run without revival. [Outcome contract](../context/game-design.md#24-october-simultaneous-boss-clear---q19q20-confirmed) completes PREP-15 design. Current open umbrella count is 56; earlier counts below are dated snapshots. Runtime/scoring/results remain unfinished.

**24 October Q17/Q18:** Basic starter shield and skippable in-play tutorial tips are confirmed. [Tutorial contract](00-planning/decisions-and-gaps.md#6-in-play-tutorial---q18-confirmed-24-october) completes PREP-11 design; actual shield/tutorial integration remains T04/T09 work. There are 57 open umbrella tasks, with overlapping preparation/runtime/release scope.

Current mode contract: [four modes and star-field Campaign](02-gameplay/campaign-stages.md). Survival is removed; beta has four authored levels, three or four visited before final completion. Other unlocked, unfinished levels remain available. Start here for unfinished work beside `assets/`, `build/`, `context/` and `src/`.

**Latest background/wave-clear direction:** Teammate produces backgrounds using the [written art brief](09-art/background-brief.md); no images are created in this context checkpoint. Campaign normal clears offer optional Enter Station or Next Wave/Stage Boss, superseding compulsory base travel. [Checkpoint details](02-gameplay/campaign-stages.md).

**24 October beta handoff:** SCRAPBOUND: Last Hope. Context first for 25 October implementation. [Readiness inventory](08-review/context-readiness-audit.md) tracks gaps; [questionnaire answers](08-review/owner-questionnaire.md) record current choices/delegation. The [four-level beta](02-gameplay/campaign-stages.md) permits visiting either or both middle levels before the final; [layouts](02-gameplay/beta-layouts.md) have numerical defaults. Full wave/difficulty data and runtime remain unfinished.

For the latest owner-requested concepts, see [boss roster and attacks for review](02-gameplay/boss-roster-draft.md). New games always start fresh; no permanent gameplay progression is selected.

Latest: [balance implementation, unfinished context and confirmation list](08-review/balance-and-context-review.md). Owner authorized source changes and delegated routine ambiguity resolution. Earlier context-only statements below are historical.

The maintained [task list and idea register](06-task-list/README.md) is the working entry point for outstanding tasks, new issues, ideas and completion history. Update it whenever work is completed, requirements change or new attention items are discovered; follow its maintenance rules each session.

For the owner's complete numerical review, read [Full game logic and statistics review](08-review/full-game-review.md): starting stats, all weapon/ability upgrades, enemies, economy, progression calculations and prioritized unresolved rules. This is a review snapshot; game-design.md remains the numerical authority.

The owner requested this top-level handoff on **20 October 2026**. These files describe work to implement later; moving or publishing them does not complete their features. This change is documentation only.

## Foldered preparation — 21 October revision

This dated folder structure remains in use. Current implementation authorization and partial deliveries are recorded above and in the tracker; individual task acceptance criteria determine what remains. The current context reconciliation changes documentation only.

```text
todo/
  README.md
  00-planning/
    decisions-and-gaps.md
  01-story/
    world-and-campaign.md
    science-notes.md
    narrative-theme.md
    story-context.md
    story-trailer-text.md
  02-gameplay/
    gameplay.md
  03-economy/
    scrap-types.md
  04-verification/
    preparation-checklist.md
  05-suggested-names/
    README.md
  06-task-list/
    README.md
    tasks.md
    ideas.md
    completed.md
  07-upgrade-proposals/
    README.md
    weapon-tree.md
    attributes-and-luck.md
    automatic-skills-and-rarities.md
  08-review/
    full-game-review.md
```

Read the required context references first, then the planning register, world/science/story, gameplay, scrap taxonomy and preparation checklist. Numbers remain authoritative in context/game-design.md; this folder supplies detailed briefs, not competing tuning sources. Confirmed choices, delegated selections, proposed defaults and content still needed are labeled separately.

## Current implementation context

The adopted [implementation handoff](00-planning/implementation-handoff.md) is the entry point. Written game-content prerequisites are supplied; actual implementation, assets, measured balance/performance and human release evidence remain open.

| File | Current written delivery |
|---|---|
| [Encounters](02-gameplay/beta-encounters.md) | Fifteen Campaign waves, three difficulties, heavy and four complete guardians, legal arenas/spawns/cleanup |
| [Return portals](02-gameplay/return-portals.md) | Exact gates/placement/search/detection/commit/Resume and Boss-clear exception |
| [Weapon composition](07-upgrade-proposals/weapon-composition.md) | All26 adopted profiles, exact cards/crit/snapshots/signature rules |
| [Numerical/load contract](04-verification/numerical-and-load-contract.md) | All19 ability overrides, uncapped progression safety, exact-event constraints and measurable benchmarks |
| [Panel input/settings](02-gameplay/ui-input-and-settings.md) | Complete state/focus/input/readability and optional red-edge warning/shake |
| [Final production script](01-story/final-production-script.md) | Final40/24/90 copy,14 voiced beats and source-checked future cutscene/result pipeline |
| [Cards](07-upgrade-proposals/beta-card-selection.md) / [attributes/Luck](03-economy/attribute-and-luck-contract.md) | Complete grades/eligibility/RNG/acquisition and numeric-source/price/reward contracts |
| [Results](02-gameplay/results-and-leaderboards.md) / [identity](01-story/player-identity.md) | Four-mode score/outcome/local records and player-entered Cadet identity |
| [Art backgrounds](09-art/background-brief.md) / [creatures](09-art/creature-direction.md) / [audio](09-art/audio-direction.md) | Teammate production instructions; no assets produced here |
| [Tasks](06-task-list/tasks.md) | Implementation/release checks remain separately open; no written spec is a delivered feature |

## Gameplay implementation checkpoints

T01-T03 have delivered subparts; all ten checkpoints retain unfinished acceptance criteria. Completed P6 pause/timing work and existing skills/equipment/art are dependencies to preserve, not tasks to rebuild.

- [ ] **T01:** Mode/difficulty data, paired trade/salvage accounting, progression/return formulas and reset contracts.
- [ ] **T02:** Central enemy rewards, deterministic random trade values, pickups and radius magnet.
- [ ] **T03:** Field level-up cards, overflow/queued choices, shared card descriptions; remove timed trigger.
- [ ] **T04:** Persistent shield, automatic combat skills, Shield Detonation and starter-shield contract.
- [ ] **T05:** Start -> difficulty -> safe colony hub, service stations and portal previews.
- [ ] **T06:** Real Swarm, Boss, Chaos and branching beta Campaign objectives; implement the delegated boss roster/content.
- [ ] **T07:** Shield/energy-gated field return portals, encounter suspension/resume, hull repair and separate Shield Battery shop purchases.
- [ ] **T08:** Mothership weapon tree, quarter-strength attributes and eligible skill/special offers after proposal approval; atomic spending and persistent stock.
- [ ] **T09:** HUD, pause/settings, input capture and tutorial integration.
- [ ] **T10:** End-to-end gameplay, reset, balance/performance and documentation verification.

Detailed dependencies, selected prices, unresolved defaults, class owners and acceptance tests are in [gameplay.md](02-gameplay/gameplay.md). Boss availability is a real dependency; a visible portal does not mean its mode is implemented.

## Remaining project work outside or alongside T01–T10

This is a consolidated view of unfinished numbered work from [progress-tracker.md](../context/progress-tracker.md), interpreted using the latest design. Some items are partly implemented; finish their missing portions rather than redo delivered work. Original item details and dependencies remain in [build-plan.md](../context/build-plan.md).

| Original items | Remaining scope / where to find it |
|---|---|
| **01–03** | Eligibility/team-machine validation, asset provenance and remaining Config/Theme/Balance migration |
| **05–06** | Remaining run reset/context/RNG cleanup and collision extraction; reuse completed pause/reset/grid work |
| **07–10** | HUD/pause, player stats/damage, remaining augment refactor and enemy base metadata; overlaps T01–T04/T09 |
| **11–14** | Mode director, paired rewards, hub/return/repair and skill shop; latest T01–T08 supersedes old cargo/credits/gear-ladder requirements |
| **15–16** | Remaining enemy art and heavy enemy implementation; retain accepted low-enemy/debris/projectile art |
| **17–19** | Boss framework, final boss content and victory connections; old boss identities remain provisional |
| **20–21** | Intro/ending implementation and original assets; see [story-context.md](01-story/story-context.md) |
| **22–23** | Menu/difficulty/hub launch and endless mode connection; use current five-mode flow |
| **24–25** | Local leaderboard/name entry and credits, with mode/difficulty/rules separation and disclosures |
| **26–29** | Remaining asset/audio integration, tutorial, human balance/performance testing, feature freeze and release validation |
| **30** | Required separate 3–5 minute gameplay demonstration video |
| **31** | Required 1–2 minute trailer; 90-second treatment in [story-context.md](01-story/story-context.md) |
| **32** | Forms, synopsis, submission materials and submission confirmation |
| **A1–A9** | Remaining style, ship/enemy/boss/dock/background/UI/cutscene/audio deliverables and provenance; completed sub-deliveries remain accepted |

Item **04** and completed P1–P5/P5.1/P6-checkpoint-1 work are intentionally not listed as new work. Their implementation evidence and any partial-item caveats remain in the tracker.

## Current review scope

23 October owner choices: weapon prices 500/1500/4000/10000, 20–25-minute Swarm T5 target, shared prices/lower tiers in Survival, 5x attribute/owned-rank prices, 10x special acquisitions, hull repair at 10 scrap/missing HP with affordable proportional healing, and a Shield Battery shop item replacing paid shield service. Metal Fragments/Circuit Parts/Polymer Pieces/Power Cells share one wallet and unchanged enemy-tier values. Exact battery details/source mappings are under popup review. Pricing/material decisions are now active; unrelated deferrals remain.

On 23 October owner accepted the latest weapon names/tree with T4/T5 branching (1/3/5/7/10), then requested balanced stats. Full proposed profiles/signatures are in game-design.md; numerical adoption, card compatibility and live viability remain open. Weapon questions resumed; attribute/Luck/rarity proposals remain review items. Boss designs, mode schedules, final names, hub/arena layouts and broad economy review are deferred for now. Keep those tasks open; do not ask for those decisions during this preparation.

## Remaining implementation and human review

Game-content defaults are adopted in the current handoff; do not reopen settled Campaign, shield/input, title, voice, card or numerical choices as unanswered questions. Remaining work is actual implementation/production/playtesting and explicit human facts.

- Implement and validate the four modes, fifteen waves, four guardians, nineteen abilities and26 cannon nodes through H00–H14.
- Produce/integrate art/audio/captions and separate truthful gameplay-demo/trailer exports with provenance.
- Measure economy, per-level duration, weapon viability, reset/suspension and numerical/load safety.
- Resolve real release/eligibility/history/forms/hardware evidence; assign final uploader. Do not invent those answers.
- Owner reviews the full audit and team verifies deliverables before a release-complete claim.

## Reference documents stay in context/

`context/` contains the shared product, technical and historical references required by `AGENTS.md`. They mix existing behavior with planned design, so moving them wholesale would break the prescribed read order and hide completed-work evidence.

Read alongside these pending briefs:

- [Project overview](../context/project-overview.md), [progress tracker](../context/progress-tracker.md) and [build plan](../context/build-plan.md).
- [Architecture](../context/architecture.md), [class registry](../context/class-registry.md) and [code standards](../context/code-standards.md).
- [Game design/tuning](../context/game-design.md), [UI rules](../context/ui-rules.md) and [library documentation](../context/library-docs.md).
- [Skill catalog](../context/skills-context.md), [current skill commands](../context/skills-commands.md), [collision performance](../context/collision-performance.md) and [crowd performance](../context/crowd-performance.md).

When work is implemented, update its checkpoint and tracker with verification evidence in the same commit. Keep completed history in the tracker and keep this folder focused on remaining work.
