# TODO — Remaining Work

Start here for unfinished game work. This folder sits beside `assets/`, `build/`, `context/` and `src/`.

The owner requested this top-level handoff on **20 October 2026**. These files describe work to implement later; moving or publishing them does not complete their features. This change is documentation only.

## Foldered preparation — 21 October revision

Everything here is pending design/content/implementation preparation. No source, tests, assets or builds are changed by this session. The teammate provides the later implementation instruction; these files do not start that work automatically.

```text
todo/
  README.md
  00-planning/
    decisions-and-gaps.md
  01-story/
    world-and-campaign.md
    science-notes.md
    story-context.md
  02-gameplay/
    gameplay.md
  03-economy/
    scrap-types.md
  04-verification/
    preparation-checklist.md
```

Read the required context references first, then the planning register, world/science/story, gameplay, scrap taxonomy and preparation checklist. Numbers remain authoritative in context/game-design.md; this folder supplies detailed briefs, not competing tuning sources. Confirmed choices, delegated selections, proposed defaults and content still needed are labeled separately.

## Pending context files

| File | What remains to be done |
|---|---|
| [Decisions and gaps](00-planning/decisions-and-gaps.md) | Confirmed/proposed choices, missing non-art systems, priorities, boss/schedule templates and tutorial/result proposals |
| [World and campaign](01-story/world-and-campaign.md) | HOPE acronym, 2718-2733 timeline, fictional mechanism, colony functions and source-boss campaign |
| [Science notes](01-story/science-notes.md) | Primary-source environmental framing, fictional boundaries and explanation of retired narrative terms |
| [Scrap types](03-economy/scrap-types.md) | Six proposed material families, existing debris mapping, one-wallet economy and reward conservation |
| [Preparation checklist](04-verification/preparation-checklist.md) | Documentation review, checkpoint content gates and later runtime acceptance scenarios |
| [gameplay.md](02-gameplay/gameplay.md) | Full detailed handoff: colony hub, five modes, field progression, random trade scrap, paid repairs, skill shop, shield/Return Home, UI, lifecycle and verification |
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
- [ ] **T07:** Shield-gated Return Home, encounter suspension/resume and paid hull/shield service.
- [ ] **T08:** Targeted skill-rank shop and priced rare offers; atomic spending and persistent stock.
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
