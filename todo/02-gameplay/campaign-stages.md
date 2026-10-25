# Campaign star-field stages — 24 October revision

**25 October complete spawn data:** [Encounter appendix](beta-encounters.md#all-fifteen-campaign-normal-waves) supplies all15 finite quotas/mixes/cadences, exact difficulty factors, guardian/add rules and legal spawn/clear geometry. Later references to unauthored tables are historical. Runtime, actual per-level timing, art and balance acceptance remain open; no new stage or Campaign question is needed.

## Optional station visit after a wave - latest owner revision

Clearing a normal wave opens a safe checkpoint with **Enter Station** and **Next Wave** (or **Stage Boss** after the last normal wave). The owner now wants station visits to be optional. This supersedes the earlier forced base visit after every wave.

Finalize the clear once: resolve required hostiles, stop hazards, preserve/credit earned loot once and resolve mandatory cards. Then show checkpoint choices. Cleanup creates no extra kill rewards. While choosing, freeze combat, shield regeneration and droid rebuilds; start no new wave or countdown. Neither choice heals or resets the build.

**Enter Station:** enter the existing Game-owned hub safely with no energy/shield gate or payment. Repairs, batteries and upgrades still cost scrap. Departure starts the already-pending next encounter exactly once; it does not resume or regenerate the cleared wave.

**Next Wave / Stage Boss:** start that pending encounter directly, skipping the station. Preserve actual hull/shield, wallet, XP, upgrades and cooldown debt. Use the ordinary fresh-encounter entry/warning contract. Do not charge return energy, refill anything or grant the ordinary mid-wave retreat's two-second resume protection just for selecting this action.

After a non-final level's boss and required hostiles clear, the analogous choices are **Enter Station** and **Select Next Level**. The latter opens the existing Game-owned map from the safe checkpoint; Cancel returns to that checkpoint, not a forced station visit. Other unlocked unfinished levels stay available. Final C04 completion still finalizes victory/ending/results; it cannot start another wave. Boss mode retains its separately selected post-kill portal -> station -> next boss loop. Swarm/Chaos remain continuous modes; this change does not invent clear checkpoints or free mid-fight returns for them.

The encounter index advances only on a committed next launch. Repeat clear callbacks, double clicks, Escape, focus loss or reopening the map cannot award twice, start two waves or erase the chosen checkpoint. Normal gated portals still apply to a retreat **before** a wave clears. This document changes design only; no checkpoint UI exists merely because it is described.

## Level terminology and duration - owner clarified

Each selectable map circle is one **Campaign level**, called a **stage** in the technical documents. Its duration covers all of that level's waves and its separate boss. Owner requested around 30 minutes or less **per chosen level**, delegating exact times. The earlier three-stage-route wording described the author's beta graph traversal; it did not mean that the whole map shares one 30-minute allowance.

Selected beta targets by level and difficulty are in [game design](../../context/game-design.md#24-october-campaign-pacing-clarification---per-selected-level): C01 15/20/25 minutes, C02/C03 18/23/28 and C04 20/25/30 for Easy/Hard/Impossible. These are active-combat estimates including the boss, excluding base/cards/pause/presentation. Later levels grow within the beta target; future expansion can author longer levels. Clearing required hostiles determines completion; elapsed time alone never clears or fails a level. Numbers are delegated tuning targets, not verified playtest times.

## Beta content scope - delegated selection, 24 October

The owner confirmed a branching map and delegated choosing a practical beta stage count, with expansion after beta. Use **four authored stages**: opening -> either or both middle levels -> final source. Owner confirmed that unlocked, unfinished levels stay available; a run may visit three or four levels before final completion. Remaining Campaign choices are delegated; do not ask further Campaign questions. This is a content baseline, not implemented gameplay. Keep all four requested modes.

| Stage ID | Working stage label | Normal waves | Separate final boss | Successors |
|---|---|---:|---|---|
| C01 | Outer Approach | 5 | Shellback | C02 and C03 |
| C02 | Relay Graveyard | 3 | Coilmaw | C04 |
| C03 | Freight Ruins | 3 | Brood Hauler | C04 |
| C04 | Source Nest | 4 | Nestheart | Campaign ending/results |

```text
              C02 - Coilmaw
             /            \
C01 - Shellback            C04 - Nestheart
             \            /
              C03 - Brood Hauler
```

Completing one middle level gives 12 normal waves plus three separate bosses, **15 encounters**. Completing both before C04 gives 15 normal waves plus four bosses, **19 encounters**. Four stage records contain 15 authored normal waves and four bosses in total. All four bosses remain available to Boss/Chaos once implemented. No beta miniboss is required. Later expansion can add stages/minibosses through authored data without changing ownership. Stage labels are working content names.

After C01 clears, C02 and C03 both unlock for this run. Previewing or launching either never locks the other. Once the active level clears, any other unlocked, unfinished level is selectable. Canceling a preview spends nothing. Retire the earlier author's exclusive-route lock and Other route chosen label.

C04 requires completion of **either middle stage**, not both: the delegated OR merge. The remaining middle stage stays available until final Campaign completion. An unfinished active stage continues its next encounter; no map visit skips/rewinds it or farms a cleared stage. Ordinary retreat resumes that fight. Death/New Game resets unlocks, current encounter and source flags. Final-level preview states that completion ends the beta Campaign, so optional levels can be finished first.

C04 is the final source. Its boss death stops the source; required surviving hostiles still block completion. For a living player, finalize earned rewards/queued choices exactly once before the final result is frozen. Q19/Q20 count a simultaneous boss kill despite player death, then end the run without revival, automatic loot collection or card choices. If every final objective resolved in that same step, record Campaign completion and play the ending over the frozen result; otherwise record only earned boss/progress credit. On a valid final clear, commit victory once, play the ending, then show that frozen result; no extra map launch or fifth stage is implied.

Remaining content work: exact per-wave enemy budgets, mixes/cadence/caps, pressure/difficulty data, boss tuning, stage geometry and asset production. Counts, routing and beta boss assignments above are selected delegated defaults; tuning/playability are not certified.

## Confirmed mode scope

Four modes remain: **Swarm, Chaos, Boss and Campaign**. Survival is removed from planned menus, gates, objectives, timers, results categories and acceptance criteria. Historical Survival records do not authorize implementing it.

Swarm and Chaos share the same ordinary-enemy spawning, progression, economy, return/base loop and difficulty mechanics. Swarm has no bosses. Chaos adds boss encounters and increasing simultaneous pursuit; its existing timing remains draft tuning. Do not silently add higher ordinary-enemy HP/damage or different shop prices just because Chaos has bosses. Boss mode retains its selected no-retreat, kill/base/next-boss loop.

## Campaign structure selected by the owner

- Present stages as selectable nodes on a **star-field map**, with each stage containing its own wave sequence and a final boss encounter.
- **30 stages was an example**, not a committed count. The delegated beta scope now selects four authored stages as specified above; later expansion remains possible.
- **Stage 1: five normal waves, then one separate boss encounter.** That is six combat encounters, not a boss replacing normal wave five.
- After each normal wave, choose Enter Station or directly launch the next encounter. The next fight always requires a deliberate action.
- Stage 1 flow: map -> wave 1 -> optional station/checkpoint -> wave 2 -> optional station/checkpoint -> wave 3 -> optional station/checkpoint -> wave 4 -> optional station/checkpoint -> wave 5 -> optional station/checkpoint -> stage boss -> station or map selection.
- Every stage ends with a boss. Later expansion may add minibosses; the four-stage beta above requires none. Stage 1's five normal waves do not silently gain minibosses.
- Preserve build, scrap, XP, actual hull/shield and owned effects across waves and stages within the same run. Base visits do not reset progression or grant free healing.
- Death ends the run and resets campaign run progress. New Game starts fresh. No permanent stage unlocks, checkpoint saves or banked builds are added.
- The old single ten-wave campaign with bosses at waves 5/10 is superseded. Existing boss concepts remain reusable; old wave assignments no longer bind them to those positions.

## Portal-to-map flow and reference interpretation — owner clarified

Entering/interacting with the Campaign portal in the base opens the star-field stage-selection map instead of immediately launching combat. Preserve the established F portal interaction; merely opening the map starts no fight and spends no resources. The supplied reference establishes connected circular stage nodes and visible route links, translated into a space/star-field presentation. It does not approve its pictured names, terrain, three-star ratings or other game content.

Each clickable circle represents one whole Campaign stage containing its normal waves and final boss, not a single wave. Selecting an available circle chooses that stage for launch. Delegated UI default: show its name, normal-wave count, separate boss and miniboss information with a Launch action; Cancel/Escape returns to the base without changing progression. Consume input so selecting a circle cannot also fire or launch twice.

Owner confirmed predecessor-based unlocking: stage 1 is initially available; clearing a stage's boss encounter and required survivors unlocks its connected successors for that run. Locked circles may preview but cannot launch. Repeated callbacks cannot unlock/award twice. Unlocks/completion reset on death/New Game. Use the authored graph, persistent unfinished-level availability and OR merge above; no randomly generated map is required.

Between waves, either checkpoint launch or optional station departure continues the pending encounter. Opening the map cannot abandon/reset/skip an unfinished level. After its final encounter clears, choose station or next-level map; map Cancel returns to its originating hub/checkpoint. Completed nodes retain status; no farming replays or mid-level switches are authorized.

## Delegated transition and ownership contract

A normal wave clears when its authored spawn budget is exhausted and all required hostiles are resolved. Boss encounters additionally require the stage boss dead; required adds cannot be silently ignored. Same-step player/boss death retains boss-clear credit but ends the run under Q19/Q20; ordinary-wave fatal ties remain defeat. Miniboss death alone does not clear an unfinished wave or grant a separate base visit.

Wave completion opens the safe optional-station checkpoint above. Only selecting Enter Station transits to base, bypassing shield/energy with no payment/free repair. Earned loot and cards finalize once before another launch. Base services stay paid; checkpoint/base/pause/cards do not advance combat or rebuild timers.

Use distinct pending-clear/checkpoint/launch states: record a clear once, retire once, then commit the next fight through either direct launch or station departure. Never regenerate a cleared wave or increment twice. Keep Game/run ownership, with no Scene switch/resetRun on station visits. Mid-wave retreat keeps ordinary gates and resumes the unfinished encounter without counting as a clear.

Map status is run-local: locked, available, current and cleared. Other unlocked, unfinished nodes remain available after a level clear. Show identity, wave count and separate boss in existing safe areas. Display the four beta nodes, not 30. Graph/counts/boss assignments are specified above; wave data remains to be authored. No map art/runtime is created by this document.

## Remaining implementation and tuning

Author stage records with normal-wave counts, enemy budgets/composition, miniboss placements, final boss IDs, clear conditions and reward data. Reuse finished bosses where appropriate; do not infer a requirement for 30 unique bosses. Tune enemy pressure and economy for carryover builds without exponential HP inflation. The old 20–25-minute Swarm T5 target is not an automatic per-stage Campaign target.

Acceptance: four modes; stage 1 has five normal waves plus boss; every normal clear offers station or direct continuation; both choices work at zero shield/energy; required survivors block clear; duplicate transitions cannot award/start twice; station services remain paid; map Cancel preserves its origin; cross-level state carries and death/New Game resets it. Minibosses do not create extra checkpoints.
