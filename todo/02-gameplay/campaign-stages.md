# Campaign star-field stages — 24 October revision

## Confirmed mode scope

Four modes remain: **Swarm, Chaos, Boss and Campaign**. Survival is removed from planned menus, gates, objectives, timers, results categories and acceptance criteria. Historical Survival records do not authorize implementing it.

Swarm and Chaos share the same ordinary-enemy spawning, progression, economy, return/base loop and difficulty mechanics. Swarm has no bosses. Chaos adds boss encounters and increasing simultaneous pursuit; its existing timing remains draft tuning. Do not silently add higher ordinary-enemy HP/damage or different shop prices just because Chaos has bosses. Boss mode retains its selected no-retreat, kill/base/next-boss loop.

## Campaign structure selected by the owner

- Present stages as selectable nodes on a **star-field map**, with each stage containing its own wave sequence and a final boss encounter.
- **30 stages was an example**, not a committed count. Determine the final count after stage content and pacing are specified.
- **Stage 1: five normal waves, then one separate boss encounter.** That is six combat encounters, not a boss replacing normal wave five.
- Return to base after every cleared normal wave. The next fight starts only after the player chooses to depart.
- Stage 1 flow: map -> wave 1 -> base -> wave 2 -> base -> wave 3 -> base -> wave 4 -> base -> wave 5 -> base -> stage boss -> base/map.
- Every stage ends with a boss. Some later stages include minibosses along the way; exact placements, counts and identities remain stage-content work. Stage 1's five normal waves do not silently gain minibosses.
- Preserve build, scrap, XP, actual hull/shield and owned effects across waves and stages within the same run. Base visits do not reset progression or grant free healing.
- Death ends the run and resets campaign run progress. New Game starts fresh. No permanent stage unlocks, checkpoint saves or banked builds are added.
- The old single ten-wave campaign with bosses at waves 5/10 is superseded. Existing boss concepts remain reusable; old wave assignments no longer bind them to those positions.

## Delegated transition and ownership contract

A normal wave clears when its authored spawn budget is exhausted and all required hostiles are resolved. Boss encounters additionally require the stage boss dead; required adds cannot be silently ignored. Same-step player death wins over clear. Miniboss death alone does not clear an unfinished wave or grant a separate base visit.

Wave completion triggers safe base transit, bypassing ordinary shield/energy gates, with no energy charge or free repair. Stop retired encounter hazards, preserve or credit already-earned pickups exactly once, grant their salvage choices, and resolve mandatory cards before another launch. Cleanup creates no new kill rewards. Base services remain paid; base/pause/card time cannot advance combat or rebuild timers.

Use distinct pending-clear and launch states: record a clear once, retire the encounter once, and start the next wave/boss only on confirmed departure. Never regenerate the cleared wave or increment twice on repeated input. Keep this within Game/run ownership rather than switching scenes or calling resetRun on each base visit. Mid-wave ordinary retreat retains existing gates and resumes the same unfinished encounter; it does not count as a wave clear.

Map status is run-local: locked, available, current and cleared. Show stage identity, wave count, final boss and miniboss presence when known. Use existing UI safe areas and show the separate boss encounter explicitly. Do not display 30 nodes as confirmed content. Node routing/branching and individual stage data remain to be defined; no map art or playable map is created by this document.

## Remaining implementation and tuning

Author stage records with normal-wave counts, enemy budgets/composition, miniboss placements, final boss IDs, clear conditions and reward data. Reuse finished bosses where appropriate; do not infer a requirement for 30 unique bosses. Tune enemy pressure and economy for carryover builds without exponential HP inflation. The old 20–25-minute Swarm T5 target is not an automatic per-stage Campaign target.

Acceptance: Survival absent from selectable scope; Swarm/Chaos ordinary rules agree; stage 1 has five normal waves plus a boss; every clear visits base; duplicate transitions cannot award twice; zero shield/energy cannot strand a cleared wave; required survivors block clear; cross-stage state carries; death/new-run clears stage state; minibosses do not create unintended checkpoints.
