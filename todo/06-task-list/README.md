# Task List and Idea Register

**Last reviewed: 21 October 2026.** This folder is the working checklist for preparation, remaining implementation, issues needing attention and ideas. Current authorization is context-only preparation. Listed implementation tasks are for the teammate's later instruction.

| File | Purpose |
|---|---|
| [tasks.md](tasks.md) | Open work, priorities, dependencies and completion conditions |
| [ideas.md](ideas.md) | Suggestions, questions and alternatives requiring review before adoption |
| [completed.md](completed.md) | Dated completion records and links to evidence |

## Update this folder whenever work changes

1. **At the start of a task:** read tasks.md and the current status in [progress tracker](../../context/progress-tracker.md). Select an existing ID before creating a duplicate. Check the linked specification and dependencies.
2. **While working:** add newly discovered missing details, bugs, contradictions or dependencies to tasks.md. Give each a stable ID, priority, next action and a concrete completion condition. Put optional alternatives in ideas.md.
3. **When the task is verified:** mark its checkbox complete in tasks.md and append a dated entry in completed.md with the result and evidence. Also update the relevant specification, the main tracker, and the T01-T10 index when affected. Make these documentation updates in the same change as the completed work.
4. **When only part is finished:** keep the original task open and state what remains. Record the delivered subtask under its own ID if useful. Writing a design is not completing its implementation.
5. **When a choice is made:** record the decision in the authority document and progress tracker, resolve the corresponding idea, and create or revise the actionable task. A suggested idea is not automatically approved scope.
6. **When an issue returns:** reopen its original checkbox and append the reason/date to the history. Preserve the earlier completion evidence; do not erase it or reuse its ID.
7. **Before ending the session:** reconcile these files with actual changes, include newly discovered work and record verification limits. Keep open and completed lists consistent.

This is a maintained Markdown workflow, not a background watcher. The person or AI doing the work must update it during each work session. No new code, automation or dependency is needed to maintain it.

## Status and priority conventions

- `[ ]` means incomplete, including work waiting for content or a decision. `[x]` means the stated completion condition was verified.
- **P0:** prerequisite or blocker for the next affected checkpoint or release decision.
- **P1:** required for the requested complete product or its deliverables.
- **P2:** optional improvement; discuss before adding it to active scope.
- **Waiting:** describe the exact missing input, responsible role and next step. Do not mark a task blocked merely because nobody has started it.
- Owners name roles until the team assigns people. Dates record actual review/completion, not guessed delivery promises.

New task format: `- [ ] ID — P0/P1/P2 — Owner: role. Action. Done when: observable result. Reference: linked brief. Dependencies: IDs, if any.` Completed history records the same ID. Keep stable IDs even if priorities or file ordering change.

## Authority and existing work

[Project overview](../../context/project-overview.md) defines scope, [architecture](../../context/architecture.md) defines connections, [game design](../../context/game-design.md) defines numbers and [code standards](../../context/code-standards.md) defines coding style. This task list points to those authorities; it does not introduce competing numbers or specifications.

[Decisions and gaps](../00-planning/decisions-and-gaps.md) supplies detailed design templates. [Gameplay](../02-gameplay/gameplay.md) supplies implementation contracts and tests. [Build plan](../../context/build-plan.md) and the main tracker preserve older item IDs, completed work and submission dependencies.

Previously delivered equipment, skills, debug tools, pause timing, debris harvesting/art and collision work are baselines to retain. Their incomplete integrations remain tasks; do not rebuild their delivered parts simply because they appear in an older unchecked umbrella item.
