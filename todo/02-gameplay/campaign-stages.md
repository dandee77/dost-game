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

## Portal-to-map flow and reference interpretation — owner clarified

Entering/interacting with the Campaign portal in the base opens the star-field stage-selection map instead of immediately launching combat. Preserve the established F portal interaction; merely opening the map starts no fight and spends no resources. The supplied reference establishes connected circular stage nodes and visible route links, translated into a space/star-field presentation. It does not approve its pictured names, terrain, three-star ratings or other game content.

Each clickable circle represents one whole Campaign stage containing its normal waves and final boss, not a single wave. Selecting an available circle chooses that stage for launch. Delegated UI default: show its name, normal-wave count, separate boss and miniboss information with a Launch action; Cancel/Escape returns to the base without changing progression. Consume input so selecting a circle cannot also fire or launch twice.

Owner confirmed predecessor-based unlocking: stage 1 is initially available; clearing a stage's boss encounter and required survivors unlocks its connected successor stages for that run. Locked circles may show a preview but cannot launch. Repeated completion callbacks cannot unlock/award twice. Unlocks and stage completion reset on death/New Game. The precise route graph (single path versus forks) remains authored content; connected nodes do not require a randomly generated map.

Between waves of an unfinished stage, the base departure continues that stage's next encounter. Opening the map must not silently abandon, reset or skip the active stage. After its final encounter clears, the map allows selection of an unlocked successor. Completed nodes show their status; reward-farming replays or mid-stage switching are not authorized by this flow.

## Delegated transition and ownership contract

A normal wave clears when its authored spawn budget is exhausted and all required hostiles are resolved. Boss encounters additionally require the stage boss dead; required adds cannot be silently ignored. Same-step player death wins over clear. Miniboss death alone does not clear an unfinished wave or grant a separate base visit.

Wave completion triggers safe base transit, bypassing ordinary shield/energy gates, with no energy charge or free repair. Stop retired encounter hazards, preserve or credit already-earned pickups exactly once, grant their salvage choices, and resolve mandatory cards before another launch. Cleanup creates no new kill rewards. Base services remain paid; base/pause/card time cannot advance combat or rebuild timers.

Use distinct pending-clear and launch states: record a clear once, retire the encounter once, and start the next wave/boss only on confirmed departure. Never regenerate the cleared wave or increment twice on repeated input. Keep this within Game/run ownership rather than switching scenes or calling resetRun on each base visit. Mid-wave ordinary retreat retains existing gates and resumes the same unfinished encounter; it does not count as a wave clear.

Map status is run-local: locked, available, current and cleared. Show stage identity, wave count, final boss and miniboss presence when known. Use existing UI safe areas and show the separate boss encounter explicitly. Do not display 30 nodes as confirmed content. Predecessor unlocking is selected; exact route graph and individual stage data remain to be defined; no map art or playable map is created by this document.

## Remaining implementation and tuning

Author stage records with normal-wave counts, enemy budgets/composition, miniboss placements, final boss IDs, clear conditions and reward data. Reuse finished bosses where appropriate; do not infer a requirement for 30 unique bosses. Tune enemy pressure and economy for carryover builds without exponential HP inflation. The old 20–25-minute Swarm T5 target is not an automatic per-stage Campaign target.

Acceptance: Survival absent from selectable scope; Swarm/Chaos ordinary rules agree; stage 1 has five normal waves plus a boss; every clear visits base; duplicate transitions cannot award twice; zero shield/energy cannot strand a cleared wave; required survivors block clear; cross-stage state carries; death/new-run clears stage state; minibosses do not create unintended checkpoints.
