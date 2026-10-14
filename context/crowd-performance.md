# Enemy crowd separation and console dropdown — 14 October 2026

Low-level enemies now push apart gradually and widen into crowds instead of staying in overlapping queues. Mid-level enemies retain their original flight behavior, overlap freely, and render above low-level enemies. Console suggestions now appear in a vertical dropdown with six visible rows, a selection highlight and scrolling; all five shield choices fit at once.

## Measured full-game performance

These are local, uncapped Release measurements on the Ryzen 5 5600GT / Radeon RX590 GME machine. The real Application and Game update/draw paths run in a 1280×720 window with all existing 3840×2160 scene/CRT/border passes retained. Normal game builds still have their existing 60 FPS limiter/VSync. Results are workload measurements, not guaranteed spawn limits.

The enemy mix is 75% low-level (separated) and 25% mid-level (free flight). All enemies are kept in a deliberately crowded visible region; fixture positions/HP and injected bullets are restored outside timed work each frame so counts do not decay. Enemy movement, separation, shooting, collisions, animation, rendering and effects run normally during measured updates. The no-injected-bullets rows still include naturally fired mid-enemy shots. This tests sustained processing cost, not a natural wave playthrough or the appearance of a settled crowd. Dynamic line/pile settling is checked separately.

Benchmarks ran sequentially, with no competing builds or other game instance. Each used 120 warmup frames; enemy-only cases used 1,200 measured frames and the heavy-bullet case used 3,600. Raw per-frame logs and scene captures are under ignored `build-release/crowd-*.csv.frames.csv` and `.csv.png`. Tracked summaries: [render results](../tests/results/crowd-render-2026-10-14.csv).

| Enemies | Injected bullets | Mean FPS | p99 frame time | Frames over 16.67 ms |
|---:|---:|---:|---:|---:|
| 1,000 | 0 | 246.8 | 4.77 ms | 0 / 1,200 |
| 2,000 | 0 | 172.6 | 6.66 ms | 0 / 1,200 |
| 3,000 | 0 | 119.9 | 13.16 ms | 1 / 1,200 |
| 5,000 | 0 | 85.6 | 15.18 ms | 4 / 1,200 |
| 7,500 | 0 | 56.7 | 24.58 ms | 1,054 / 1,200 |
| 2,000 | 8,000 | 103.6 | 10.68 ms | 0 / 3,600 |

5,000 enemies passed the p99 60 FPS budget in this test but had four slower frames; 7,500 regularly exceeded it. The earlier collision report measured a different implementation/session; do not interpret differences as a controlled speedup from adding separation.

## Separation cost and approach

EnemyManager reuses a SpatialGrid and an observer array. It indexes only living low enemies after movement, calculates corrections from that immutable snapshot, then applies bounded movement without changing combat radii, velocity, damage, or spawn rules. No per-frame string copies, neighbor-vector allocations, sorting or all-pairs loops are added. Mid enemies never enter the separation grid.

Each query visits at most 24 entries per cell, with a 16-cell query-area limit and bounded fallback. The shipped low-enemy radius normally spans at most nine cells. Dense same-cell queries begin after the querying enemy in the bucket chain, so every enemy does not repeatedly select the same first group. Neighborhoods exceeding the budget are intentionally approximate: heavily compressed crowds settle over time rather than paying for every possible contact. Exact coincidences get deterministic opposite push directions; a small pair-symmetric side step breaks straight queues without consuming gameplay RNG. An exponential response scales by simulation time; displacement is speed-limited and large frame stalls are capped.

The isolated benchmark calls the real manager pass, restoring positions outside its timer. All objects in these rows are low enemies. It uses 20 warmup passes and 200 measured passes per case. `packed` is a 5-unit lattice; `coincident` places every enemy at one point. Latest complete run: [solver results](../tests/results/crowd-solver-2026-10-14.csv).

| Low enemies | Packed mean / p95 | Coincident mean / p95 |
|---:|---:|---:|
| 1,000 | 0.85 / 1.20 ms | 0.57 / 0.70 ms |
| 2,000 | 1.58 / 2.05 ms | 1.14 / 1.33 ms |
| 5,000 | 4.48 / 6.88 ms | 2.92 / 3.68 ms |
| 10,000 | 9.24 / 10.78 ms | 6.15 / 7.37 ms |

These times cover only separation, not full frames. Budgeted traversal prevents quadratic neighbor scanning, but total game performance still includes rendering, AI, bullets and effects. The prototype soft-body parameters remain TUNE in Balance.hpp.

## Validation and reproduction

Debug/Release builds pass with no new compiler warnings. CTest passes: 713 Debug and 679 Release equipment/console/crowd checks, plus 600,000 exact combat-grid queries and 10,000 ordinary-density crowd comparisons against brute force. Checks cover zero-time updates, speed/stall bounds, symmetric pair pushes, settling at 30/60/144 FPS, collinear chasing, a 500-enemy coincident pile, empty/reset state, unchanged flying position/velocity/steering, and native rendered pixels proving mid sprites cover low sprites. Both run reset paths already call EnemyManager::reset, which now clears the crowd snapshot and observers.

Dropdown checks reach the last of 19 equipment choices, wrap/page short lists, accept selections without execution, clear reset state, and route native Down/Enter events. Native captures `build/console-dropdown.png` and `build-release/crowd-chase.png` were inspected. Test-event debugging exposed missing Windows key-up bits in the fixture; production input handling needed no workaround.

```powershell
cmake --build build --config Debug -j 8
cmake --build build-release --config Release -j 8
ctest --test-dir build -C Debug --output-on-failure
ctest --test-dir build-release -C Release --output-on-failure
# Existing GAME_EQUIPMENT_TESTS and GAME_COLLISION_TESTS options enable the targets.
Push-Location build-release/Release
./CollisionBenchmark.exe 2000 0 spread ../crowd-render-2000.csv 1200
./CollisionBenchmark.exe 2000 8000 combat ../crowd-combat-2000.csv 3600
Pop-Location
```

Release equipment tests also export the isolated solver CSV. Follow the bundled CMake path in library-docs.md if CMake is not on PATH. The low-enemy movement change is intentional, so the earlier byte-for-byte movement-parity claim applies to the earlier collision optimization, not this crowd feature.
