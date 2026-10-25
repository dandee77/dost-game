# Adopted beta encounters and spawn data

25 October 2026. Delegated initial tuning, adopted as the numerical appendix linked from game-design.md. This completes written PREP-01/02/07 data, not implemented enemies/director, measured pacing or rendered assets. All four modes and guardians remain required. Existing [roster](boss-roster-draft.md), [level graph](campaign-stages.md) and [layouts](beta-layouts.md) supply identity and routing; this file resolves their missing encounter data and superseded phase/schedule text.

## Ownership, clocks and common geometry

Game owns one run and WaveDirector owns encounter scheduling. EnemyManager owns normal enemies and Boss-derived guardians; existing BulletManager/SkillSystem handle their appropriate effects through typed ownership. Use encounter ID plus monotonically increasing instance ID, including repeated Chaos bosses; a static boss-name Animator key is unsafe. No scene switch/resetRun for waves, station visits or next Boss encounter.

Use combat delta only. Freeze spawning, attack phases, travel, per-victim debts, RNG, phase timers and emitters during cards, checkpoint, station, pause, console and story. Resume preserves their exact state. A fresh encounter resets its own scheduling credit/local clock, not lifetime combat time, player build, cooldown debt or reward streams. No passive shield/droid recovery at a checkpoint.

Boss/Campaign arena: center (0,0), radius 220, legal entity-center radius = 220 minus that entity's collision radius. Player arrives at center, radius-24 arrival exclusion. Fresh finite encounters contain no decorative solid obstacles or BarricadeEvent; boundary projection removes outward velocity without damage. Swarm/Chaos roam and schedule the existing barricade once at 600 lifetime combat seconds. No repeated barricade timer or implied fifth mode.

Normal finite spawns choose a heading uniformly around the current player at radius 150, projecting to arena radius minus enemy radius minus 2 if needed. Reject a point less than 36 from the player, overlapping a solid/hostile or a portal's full interaction disk. Try 32 random headings, then 16 equally spaced stable headings (0 degrees first, counterclockwise) at radii 150, 100, 60, in that order. All candidates obey the same legality checks. On failure retain the unspawned quota, discard accumulated whole cadence credit and retry after 1 combat second; never substitute an illegal spawn or auto-clear the wave. Transient enemy overlap uses circles plus a 2-unit margin; do not require permanent global connectivity through moving enemies.

Fresh boss placement uses 32 uniform candidates 100–140 from the player, followed by 16 stable headings at radii 100/120/140; whole body must fit, with 24 clearance from player and no overlap with live solids/portals/boss bodies. If all fail, show Arrival pending and retry after 1 combat second without consuming encounter/roster selection twice. In Chaos relocate relative to the current player only before successful placement. Two combat seconds of visible arrival warning: boss moves/damages/attacks neither, takes no damage, and cannot overlap player arrival. End warning before enabling its body collision damage. Do not add another immunity period on ordinary retreat Resume.

## Normal profiles and difficulty

| Profile | Base HP | Contact | Speed | Collision radius | Behavior / reward family |
|---|---:|---:|---|---:|---|
| Basic | 30 | 10 | Existing 15–30 spawn roll | Existing sprite hitbox | Existing homing/contact; equal-choice can/battery/monitor visuals with METAL/POWER/CIRCUIT |
| Ranged | 50 | 10 | Existing 25–50 spawn roll | Existing sprite hitbox | Existing strafing shooter/bullet damage 10; METAL |
| Heavy | 80 | 10 | 10 roam, 40 charge | 5 | New planned HighLevelEnemy, METAL; rules below |

Normal HP snapshots the existing lifetime curve `roundHalfUp(baseHP * clamp(1+(combatSeconds-300)*0.025/60,1,2))`; no difficulty/player-level/stage multiplier. Existing ordinary trade/Salvage/score and Luck eligibility apply. Basic and ranged movement/fire variation remains existing behavior, not a new boss attack rule.

Heavy moves toward the player. When within 70, ready and not charging: wind up 1.2 seconds with a visible lane, track aim for 0.8 then lock for 0.4; charge at 40 for 0.8 seconds, recover stationary for 1 second, earliest next windup 6 seconds after the prior start. One 10-damage contact event per charge, subject to player guards; ordinary noncharging contact uses the existing player hit guard. World boundary ends charge into recovery; no wall penetration or damage on projection. Ignore knockback during charge only; no homing turn after aim locks. Telegraphed charges never spawn under the player. Body/reward handling stays the normal heavy tier, not a miniboss.

| Difficulty | Endless rate factor | Endless population factor | Finite quota factor C01 | Finite C02/C03 | Finite C04 | Finite normal alive cap |
|---|---:|---:|---:|---:|---:|---:|
| Easy | 0.8 | 0.75 | 0.75 | 18/23 | 0.8 | 90 |
| Hard | 1 | 1 | 1 | 1 | 1 | 120 |
| Impossible | 1.2 | 1.15 | 1.25 | 28/23 | 1.2 | 150 |

Adopt these delegated pressure differences without HP/damage/reward/shop/XP multipliers. Finite quotas round half up per wave, minimum 1; cadence and mix are the same across difficulties. Population values floor after scaling; bosses are separate from the normal cap, their adds are not. Count all living normal enemies, including barricade segments and owned adds. Boss encounters in finite arenas allow at most 24 living normal adds globally, still respecting each emitter's own cap.

## Shared Swarm/Chaos ordinary schedule

Interpolate rate and cap linearly at the following lifetime combat-time knots, applying difficulty factors afterward. Cap at the final knot thereafter. Integrate the piecewise-linear rate over the actual combat interval; carry only the fractional remainder. At most 32 normal insertions per update; discard blocked whole opportunities, with no backlog burst. Crossing knots must integrate both sides, not sample the final rate for the entire delta.

| Minute | Hard potential spawns/s | Hard normal cap | Ranged share | Heavy share |
|---|---:|---:|---:|---:|
| 0 | 0.7 | 120 | 0% | 0% |
| 3 | 1.18 | 168 | 0% | 0% |
| 5 | 1.5 | 200 | 1.363636% | 0% |
| 10 | 4 | 400 | 4.772727% | 0% |
| 15 | 8 | 650 | 8.181818% | 1.666667% |
| 20 | 12 | 900 | 11.590909% | 3.333333% |
| 25 | 16 | 1200 | 15% | 5% |
| 35 | 20 | 1500 | 15% | 5% |
| 45 onward | 20 | 1500 | 15% | 5% |

Exact shares, rather than rounded display entries: ranged `0.15*clamp((t-180)/1320,0,1)`; heavy `0.05*clamp((t-600)/900,0,1)`; basic is the remainder. One uniform bounded draw 0..999999 per successful natural insertion, compare against floor(1000000*heavy), then cumulative floor(1000000*(heavy+ranged)); otherwise basic. Draw profile/visual/position from the isolated spawn stream, reward from its independent streams. Do not consume profile/reward draws for capacity-rejected opportunities. No startup wave, finite clear or time-limit victory in either endless mode.

Swarm has no guardian. Chaos adds one opportunity at 300 seconds, then 480, 660, 840, 1020… (`300+180*k`). Alive allowance `1+floor(t/900)`; an opportunity at allowance skips with no debt. Use a seeded shuffled bag containing all four guardians, prefer an absent living type while preserving deterministic bag order; if needed select the first absent type in bag, remove/refill only after a successful spawn. Once all four types live, allow repeated instances. A placement-pending opportunity retains its selected identity and blocks additional opportunities until resolved or skipped at the next opportunity; at that boundary cancel the pending placement then evaluate current allowance once. No backlog, difficulty HP inflation or player-visible promise of unlimited physical simulation. See the numerical/load contract before claiming supported concurrency.

## All fifteen Campaign normal waves

The Hard quota is a finite enemy count, not a timed success condition. Apply the difficulty factor once to obtain total quota N. Mix uses deterministic cumulative allocation: ranged count=floor(N*ranged%), heavy=floor(N*heavy%), basic=remainder. Schedule profile slots by largest cumulative deficit against those totals; ties basic/ranged/heavy. This distributes sparse heavy/ranged entries instead of releasing all late. Do not reroll percentages per kill or convert unused quota into currency.

| Wave | Hard quota | Potential spawns/s | Ranged | Heavy | Boss after this wave? |
|---|---:|---:|---:|---:|---|
| C01-W1 | 120 | 0.5 | 0% | 0% | No |
| C01-W2 | 180 | 0.75 | 5% | 0% | No |
| C01-W3 | 240 | 1 | 8% | 0% | No |
| C01-W4 | 300 | 1.25 | 10% | 2% | No |
| C01-W5 | 360 | 1.5 | 12% | 3% | Separate Shellback encounter |
| C02-W1 | 480 | 1.1 | 18% | 4% | No |
| C02-W2 | 600 | 1.4 | 22% | 5% | No |
| C02-W3 | 720 | 1.7 | 25% | 6% | Separate Coilmaw encounter |
| C03-W1 | 480 | 1.1 | 8% | 8% | No |
| C03-W2 | 600 | 1.4 | 10% | 10% | No |
| C03-W3 | 720 | 1.7 | 12% | 12% | Separate Brood Hauler encounter |
| C04-W1 | 660 | 1.8 | 18% | 8% | No |
| C04-W2 | 780 | 2.2 | 20% | 10% | No |
| C04-W3 | 900 | 2.6 | 22% | 12% | No |
| C04-W4 | 1020 | 3 | 24% | 14% | Separate Nestheart encounter |

Fresh wave: zero spawn credit, first insertion after its normal cadence interval; no prepopulated wave or extra wave-reward burst. Every actual insertion decrements unspawned quota by 1. At capacity/failure discard whole cadence opportunities but retain unspawned quota, never bank a giant release. Max 32 insertions/update. Clear requires quota zero AND no required living wave enemy; no timer, cleanup or return counts as a kill. Source boss encounters have no independent endless/normal-wave spawner.

Hard quota totals C01=1200, C02=1800, C03=1800, C04=3360. Ideal quota/rate emission spans are 1200, approximately 1288.46, 1288.46 and 1407.37 seconds, before cap blocking and final survivors/boss. They are analytical pacing estimates, not extra minimum waits: sufficiently quick kills still wait for future scheduled enemies because cadence is real, while wave completion itself has no artificial hold. These initial tables target the selected per-level durations; actual balance must measure expected incoming builds. Do not increase boss HP to fill a timing target. Later tuning changes this appendix and Balance together.

## Boss state, phases and attack selection

Adopt existing base stats and attacks in game-design.md: Shellback 1200 HP/contact12/speed12/radius10; Coilmaw1600/10/18/8; Hauler2000/10/10/12; Nestheart2800/15/8/14. Boss mode uses base HP each encounter. Campaign/Chaos apply the existing lifetime HP factor once, capped 1.5x at minute30; no difficulty/loop ordinal damage or HP factor. Material assignments remain METAL/POLYMER/METAL/CIRCUIT. Standard boss trade120..180/Salvage100; Campaign final200..300/200.

Phases: P1 `HP>0.6*max`, P2 `0.3*max<HP<=0.6*max`, P3 `0<HP<=0.3*max`. Crossing several boundaries updates once to the final phase, preserving the current attack snapshot. Apply P2 variations from the existing attack table on future casts; P3 also multiplies repeat intervals by0.9. No HP refill, damage multiplier, invulnerable phase transition or mid-tell angle/count change. The old 50% variant trigger is superseded. Arrival immunity alone lasts2 seconds.

Each boss cycles its listed attack order, starting at the first attack after arrival. Choose the next ready attack in that cyclic order; if none ready, move/idle. Repeat debt runs from attack START, with no missed-cast queue. Windup/active/recovery are nonoverlapping states; no second attack in recovery. Snapshot aim, pattern, phase and damage when windup starts; tracking windows explicitly allowed below. Only Ram/Sweep/Pulse reserve the global major budget (maximum2); use FIFO request time then instance ID, discard stale requests on death/state change. A waiting attack never creates an invisible hazard. Minor attacks may run concurrently but cannot erase a major safe route.

| Boss / ordered attacks | Exact geometry and targeting supplement | Active / recovery / repeat |
|---|---|---|
| Shellback 1 Ram | Windup1.2: track nearest player position for0.8, lock last0.4. Lane width = boss diameter20 + player diameter; charge straight65 units/s, boundary stops into recovery; one contact event per target/ram | 0.7 /1.5 /6 seconds |
| Shellback 2 Scrap Fan | Windup1; lock aim at start;5 evenly spaced bullets across -40..40 degrees, P2/P3 use7 at same endpoints; radius0.8, speed70, damage8 | Instant /1.2 /8 |
| Coilmaw 1 Arc Volley | Windup1.1; lock aim at start;3 bullets at -18/0/18 degrees, radius0.8, speed90, damage8 | Instant /1 /4 |
| Coilmaw 2 Sweep | Windup1.5 shows initial ray and direction; start at aim-30, sweep+60 degrees at30 deg/s, range100/full width4. P1 always positive; P2/P3 alternate direction by committed cast ordinal | 2 /2 /10 |
| Hauler 1 Release | Windup1.5;4 basic adds, P2/P3 use5; maximum12 living owned adds. Spawn on radius24 from boss at stable evenly spaced headings with legal-point checks and at least24 clearance from player | Instant /1.5 /10 |
| Hauler 2 Residue | Windup1.2 shows3 circles; candidate centers at player's snapshotted location plus radius24 at aim-relative0/120/240 degrees; radius8, centers>=20 apart, avoid initial player overlap; deterministic heading rotations if invalid | Pools4 seconds /1.5 /9 |
| Nestheart 1 Split Volley | Windup1.2; lock aim at start;7 bullets at -60/-40/-20/0/20/40/60 degrees, radius0.8, speed75, damage8 | Instant /1.5 /7 |
| Nestheart 2 Source Pulse | Windup1.8 marks annulus/opening; ring radius15..90 at40 units/s, full width4, opening80 degrees centered toward player snapshot. P1 uses that heading; P2/P3 alternate snapshot heading and heading+180 by cast ordinal | 1.875 /2 /12 |
| Nestheart 3 Release | Windup1.5;3 basic adds, same radius24/clearance legality as Hauler, maximum9 living owned adds in all phases | Instant /1.5 /12 |

Sweep damage8 with0.75-second per-player debt; pools damage6 share1-second per-player debt per emitting boss across all its pools; pulse damage10 once per pulse/player, gap is safe. Bullets travel at most180 units, hit once then disappear, stop at solids/arena edge. Swept collision tests prevent low-FPS tunneling. Existing player guards still reject damage before shield/hull; no same-frame stacked bypass. Boss collision never removes the boss. Distinct boss instances retain independent debts; ordinary player hit guards remain authoritative.

Residue selection: rotate the three-center pattern by22.5 degrees through16 stable candidates; require all three circles fit arena/solids and player clearance. If no full pattern is legal, use the largest legal subset, stable circle order, or show no attack and enter recovery if none. Do not spawn a pool at the player's feet or save rejected pools for later. Pools persist during recovery/other attacks until their own expiry. Release attempts only free local/global slots; rejected adds are skipped without debt, but consumed attack time remains. Each add receives its own normal profile/variant/reward snapshot and owning encounter/boss ID.

Movement: nominal standoff60 for Shellback/Hauler and80 for Coilmaw/Nestheart. Actual desired standoff=min(nominal, half of the smaller current world-viewport dimension minus boss radius minus8), minimum player radius+boss radius+4. Advance/retreat to that distance and strafe clockwise inside ±5. This keeps a close attack position visible even when vertical viewport space is smaller than the nominal range. Recompute from the unshaken logical camera; window resizing alone does not change world framing. If a viewport is too small to fit the full body plus margin, reject the camera configuration with a diagnostic rather than negative standoff/hidden damage.

Attack start additionally requires the boss body intersects the viewport and all gameplay-relevant telegraph geometry crossing the player region is rendered for its complete windup. Off-screen arrivals/pursuers keep their direction marker and approach; they cannot launch an unseen sweep/ram/pulse or aimed volley. Once committed, do not reset a visible attack merely because the player moves offscreen; preserve readable world geometry/pointer and normal timing. During Ram/Release/Residue windup and recovery hold position; fan/volley windup hold position; sweep/pulse windup/active/recovery hold position. Ram alone translates during its active state. Use finite-arena constraints and do not teleport through solids. Roaming Chaos bosses follow normal locomotion when not in an attack; nearby boss markers use the existing HUD policy.

Fairness validator before major windup: prospective lane/beam/pulse plus existing reserved major geometry must leave a16-unit-wide route from player to a nonhazard point in the current playable component. Sample16 headings at distances16/32/48 and use swept player-circle clearance against solids/committed hazard geometry for their actual active windows. If no witness route exists, delay that request0.25 combat seconds; after2 seconds of waiting drop that request and retry normal selection without a damage event. Minor pool placement must not close that witness corridor. This is a conservative authored rejection rule, not a mathematical guarantee of human dodgeability; live overlapping/close-range tests remain required.

## Death, source and completion matrix

Death resolves once by immutable instance ID. Commit eligible boss score/source flag/reward assignment even on same-step player death; actual collection and run continuation still require a living player. Stop that emitter immediately, cancel its projectiles/pools/reservations; do not cancel unrelated Chaos instances. Source shutdown is run-local, not a global enemy stat debuff.

| Mode | Surviving owned adds after guardian death | Required clear / next step |
|---|---|---|
| Swarm | No guardians | Endless until defeat or station retirement |
| Chaos | Stay normal enemies with stopped parent emitter | No encounter-wide cleanup/victory; other bosses/ordinary schedule continue |
| Boss | Remove without kill score/loot; already earned pickups preserved | Reveal one unrestricted exit, stop combat clocks at safe clear; next deliberate station launch selects next fixed-cycle guardian |
| Campaign | Remain required hostiles, ordinary rewards on eligible kills | Clear only when guardian dead AND all required adds dead; then stage checkpoint, or final ending/result |

Boss clear portal: place at dead boss position if its full12-unit interaction disk fits legal space; otherwise project inward to arena radius-12, then validate solids. Empty finite arena has no solid obstacles, so projection supplies a legal point. Player must fly inside and press F; no forced travel. Earned arena pickups finalize once on station entry/clear checkpoint under existing reward rules. Do not grant loot from removed adds or unspawned wave quota. Simultaneous player/boss death ends run with boss credit, no collection/portal/revival. Final Campaign completion additionally requires every required hostile resolved in that same simulation step.

## Implementation acceptance

Verify every wave/difficulty count, retained quota under population/placement blocking, exactly one normal spawner, same Swarm/Chaos seeded ordinary draws absent boss effects, all phases/boundary crossings, every attack windup/active/recovery, legal fallback, per-instance IDs and attack reservation cleanup. Exercise all26 weapon nodes against all4 guardians, both Campaign branches, Boss cycle wrap, Chaos repeated types, no-loot kills, same-step deaths, optional station/direct continue, and pause/retreat in each attack state. No missing heavy/guardian implementation may be replaced with a basic enemy while claiming a complete beta.

Record actual level durations/build/economy, boss target uptime, clear rates and frame times at30/60/144 render FPS. The quota tables, safe-route witness and nominal DPS calculations are written defaults, not completed playtesting or supported-hardware certification.
