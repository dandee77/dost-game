# TODO — Remaining Work

Current mode contract: [four modes and star-field Campaign](02-gameplay/campaign-stages.md). Survival is removed; stage count remains undecided. Start here for unfinished game work. This folder sits beside `assets/`, `build/`, `context/` and `src/`.

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

## Pending context files

| File | What remains to be done |
|---|---|
| [Field return portals](02-gameplay/return-portals.md) | Selected random portal/F interaction replacing manual teleport; shield/half-energy gates, limited-range pointer; count/placement/replenishment still open |
| [Weapon/attribute/rarity review](07-upgrade-proposals/README.md) | Five-tier weapon proposal, 25% shop attributes, Luck, complete automatic roster and Legendary Blink; details awaiting confirmation |
| [Maintained task list](06-task-list/tasks.md) | Prioritized open work, decisions and verified preparation checkboxes; update when work changes |
| [Ideas and attention](06-task-list/ideas.md) | Suggestions and alternatives with explicit review status; not automatically active scope |
| [Completion history](06-task-list/completed.md) | Dated results and evidence, with clear separation from pending implementation |
| [Suggested game names](05-suggested-names/README.md) | Title options, meanings and recommended tagline pairing; final title undecided |
| [Decisions and gaps](00-planning/decisions-and-gaps.md) | Confirmed/proposed choices, missing non-art systems, priorities, boss/schedule templates and tutorial/result proposals |
| [World and campaign](01-story/world-and-campaign.md) | HOPE acronym, 2718-2733 timeline, biological waste-eater origin, colony functions and source-boss campaign |
| [Science notes](01-story/science-notes.md) | Primary-source environmental framing, fictional boundaries and explanation of retired narrative terms |
| [Narrative theme](01-story/narrative-theme.md) | Neglect, postponed responsibility, consequences, hopeful recovery and original slogan options |
| [Scrap types](03-economy/scrap-types.md) | Four selected material labels, one wallet and enemy-tier values; authored source mappings and later integration remain |
| [Preparation checklist](04-verification/preparation-checklist.md) | Documentation review, checkpoint content gates and later runtime acceptance scenarios |
| [gameplay.md](02-gameplay/gameplay.md) | Full detailed handoff: colony hub, five modes, field progression, random trade scrap, paid repairs, skill shop, shield/Return Home, UI, lifecycle and verification |
| [Text-only story trailer](01-story/story-trailer-text.md) | Standalone storytelling script from the chat; untimed literary draft for later production |
| [story-context.md](01-story/story-context.md) | Alternating story text and animated/gameplay footage: 40-second intro, ending and 90-second trailer; final boss content/art/optional voice still pending |

The handoffs now live in topic folders. `gameplay.md` was formerly `context/todo.md`; `story-context.md` was formerly `context/story-context.md`. They have been moved, not copied. The original pause/scrap/difficulty specification is replaced by the gameplay handoff.

## Gameplay implementation checkpoints

All remain pending. Completed P6 pause/timing work and existing skills/equipment/art are dependencies to preserve, not tasks to rebuild.

- [ ] **T01:** Mode/difficulty data, paired trade/salvage accounting, progression/return formulas and reset contracts.
- [ ] **T02:** Central enemy rewards, deterministic random trade values, pickups and radius magnet.
- [ ] **T03:** Field level-up cards, overflow/queued choices, shared card descriptions; remove timed trigger.
- [ ] **T04:** Persistent shield, automatic combat skills, Shield Detonation and starter-shield contract.
- [ ] **T05:** Start -> difficulty -> safe colony hub, service stations and portal previews.
- [ ] **T06:** Real Swarm, Survival, Boss, Chaos and Campaign objectives; owner-supplied boss content.
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

## Decisions and content still needed

See [the detailed gap register](00-planning/decisions-and-gaps.md) for all remaining non-art specifications and proposed defaults. The HOPE name and source-cleanup story now replace the former settlement/tree premise.

- [ ] Owner's final boss roster, attacks, phases, telegraphs, art and encounter definitions.
- [ ] Review proposed starter shield, Return Home input/consumption and suspended-world resume rules.
- [ ] Playtest chosen currency ranges, repair costs, skill prices, level/return growth and mode schedules.
- [ ] Final title, narrative visual treatment, optional voice and original production assets; story cards are required.
- [ ] Submission prioritization if the full requested scope cannot be verified by the deadline.

Paid repair, random enemy trade drops and delegated shop inventory/prices have already been resolved in the handoff. Do not turn them back into unanswered permission questions.

## Reference documents stay in context/

`context/` contains the shared product, technical and historical references required by `AGENTS.md`. They mix existing behavior with planned design, so moving them wholesale would break the prescribed read order and hide completed-work evidence.

Read alongside these pending briefs:

- [Project overview](../context/project-overview.md), [progress tracker](../context/progress-tracker.md) and [build plan](../context/build-plan.md).
- [Architecture](../context/architecture.md), [class registry](../context/class-registry.md) and [code standards](../context/code-standards.md).
- [Game design/tuning](../context/game-design.md), [UI rules](../context/ui-rules.md) and [library documentation](../context/library-docs.md).
- [Skill catalog](../context/skills-context.md), [current skill commands](../context/skills-commands.md), [collision performance](../context/collision-performance.md) and [crowd performance](../context/crowd-performance.md).

When work is implemented, update its checkpoint and tracker with verification evidence in the same commit. Keep completed history in the tracker and keep this folder focused on remaining work.
