# Collision performance — 14 October 2026

The collision searches now use a reusable spatial hash grid. On this machine, **2,000 enemies plus 8,000 injected bullets** is a conservative tested operating point: 97.8 FPS average over 6,000 uncapped combat frames, 12.45 ms at the 99th percentile, and 2 frames above the 16.67 ms budget. **2,500 enemies plus 10,000 bullets** also has substantial headroom on average, but occasional slow frames make it a less conservative choice. These are controlled stress-test results, not a universal gameplay cap.

The existing 80-enemy project target comfortably passes, including a rapid-hit workload. No spawn caps, damage values, hitbox sizes, movement, graphics settings, or gameplay rules were changed.

## Machine and measurement

- Windows 11 Pro 10.0.26200; Ryzen 5 5600GT; Radeon RX590 GME, driver 31.0.12027.9001; approximately 32 GiB RAM.
- MSVC 19.44, C++20, Raylib 5.5, optimized **Release**, `GAME_DEBUG=OFF`.
- Real `Application::Run`, real `Game::update/draw`, 1280 x 720 window, **3840 x 2160 scene/CRT/border render passes retained**, zoom 20. Audio resources remain loaded; master volume is zero during testing.
- Only the benchmark disables VSync and the 60 FPS limiter. Normal builds retain both existing settings. Timings include the real renderer, buffer swap, animation updates, enemy AI, collision handlers, HUD and effects. They are wall-clock frame/throughput measurements, not GPU timer queries.
- 120 warmup frames; normally 600 measured frames. Sustained combat checks use 6,000 frames at 2,000 enemies (about 61 seconds) and 3,600 frames at 2,500 (about 43 seconds).
- Fixture setup is outside the timed region: enemies are placed back at their seeded on-screen positions and given high HP; bullets are restored; automatic manager spawns and augment transitions are held off. Real enemies move and shooters fire during each timed update. No manager or collision code is replaced in the benchmark.
- Enemy mix: 75% low-level, 25% mid-level. The camera-visible workload is deliberately extremely crowded. Bullet positions are held stationary with zero direction to maintain a repeatable load; this is not a natural wave playthrough. Natural shooter bullets add a small varying number beyond the injected count (recorded in the CSV).
- `spread`: visible miss-heavy bullet lane. `combat`: six player-bullet hits per frame, with ordinary damage-number effects. `burst`: approximately 64 player hits per frame. `cluster`: overlapping enemies with nearby misses. No asteroids are injected in these rendered capacity runs; asteroid interaction correctness is covered separately by the differential fixtures.

The stricter question “did every frame stay below 16.67 ms?” is answered by the last column below. Averages alone do not establish a stable 60 FPS limit.

## Measured results

The durable machine-readable log is [tests/results/collision-2026-10-14.csv](../tests/results/collision-2026-10-14.csv). Total base entities are enemies + injected bullets + one player; effects and naturally fired bullets are additional.

| Algorithm / workload | Enemies | Injected bullets | Mean FPS | 99th-percentile frame | Frames over 16.67 ms |
|---|---:|---:|---:|---:|---:|
| Grid, combat | 80 | 320 | 368.9 | 4.49 ms | 0 / 600 |
| Grid, burst | 80 | 320 | 154.5 | 9.98 ms | 0 / 600 |
| Original, spread | 1,000 | 4,000 | 81.8 | 17.00 ms | 8 / 600 |
| Grid, spread | 1,000 | 4,000 | 170.2 | 7.68 ms | 0 / 600 |
| Original, spread | 1,500 | 6,000 | 33.3 | 44.05 ms | 600 / 600 |
| **Grid, sustained combat** | **2,000** | **8,000** | **97.8** | **12.45 ms** | **2 / 6,000** |
| Original, combat | 2,500 | 10,000 | 8.7 | 128.39 ms | 600 / 600 |
| Grid, sustained combat | 2,500 | 10,000 | 83.1 | 14.18 ms | 8 / 3,600 |
| Grid, combat | 3,000 | 12,000 | 70.4 | 16.37 ms | 4 / 600 |
| Grid, spread | 3,500 | 14,000 | 61.6 | 18.80 ms | 192 / 600 |
| Grid, cluster | 1,000 | 4,000 | 155.6 | 8.45 ms | 0 / 600 |
| Grid, burst | 1,000 | 4,000 | 119.2 | 12.87 ms | 2 / 600 |
| Grid, no injected bullets | 5,000 | 0 | 76.1 | 15.31 ms | 1 / 600 |
| Grid, no injected bullets | 7,500 | 0 | 54.6 | 20.62 ms | 595 / 600 |

Practical interpretation:

- **Comfortable heavy-bullet test point: 2,000 enemies + 8,000 bullets**, about 10,001 base entities. 99.97% of measured frames met the budget. The slowest was 17.40 ms, so this is explicitly not a zero-hitch guarantee.
- **Near the tested heavy-bullet limit: 3,000 enemies + 12,000 bullets.** One earlier repeat had a 17.06 ms 99th percentile; the final repeat had 16.37 ms. There is insufficient margin to recommend this as a stable production cap.
- **3,500 enemies + 14,000 bullets exceeds the budget regularly.** An exploratory 5,000 + 20,000 run averaged only 46 FPS. The practical heavy-bullet boundary is around 3,000, depending on layout/effects, rather than the manager's existing 10,000-enemy cap.
- **Enemy-heavy, few-bullet boundary:** 5,000 passes the 99th-percentile budget, while 7,500 averages below 60 FPS. This bounds the limit; it does not establish an exact maximum between those counts.
- **Rapid hits cost real time.** At 80 enemies, increasing targeted player hits from about 6 to 64 per frame raised mean frame time from 2.71 to 6.47 ms. Damage numbers, destruction animations, vector erases, and other effects still matter. Do not translate these counts into a guaranteed limit for arbitrary battles or another computer.

At 1,000 enemies/4,000 bullets, total frame time improved **12.23 → 5.88 ms (2.08x)** and 95th-percentile whole-update time **12.33 → 0.70 ms (17.6x)**. At 2,500/10,000 in combat, mean frame time improved **114.55 → 12.03 ms (9.52x)**. These are observed comparisons, not complexity projections. The original reference also has the per-frame console flush removed, so that cleanup does not inflate the collision comparison. Wall-clock AI cooldowns naturally produce somewhat different shooter-bullet counts at different frame rates; the CSV records those ranges.

The grid is no longer the dominant cost in the large optimized runs: update p95 is roughly 1.65–2.66 ms while complete frames take 10–16 ms. Rendering/animation submission, the existing effects, and GPU work account for most of the remaining frame time; a detailed GPU/renderer profile would be needed to attribute those costs further. No rendering changes were included in this task.

## Behavior preserved and verified

The original reference is `src/Game.cpp` from commit `52e32af84bb80e66eae5c842e7bea75b203a8e5d`.

- 600,000 ordered grid queries match an independent brute-force scan, including empty/small sets, negative coordinates, boundaries, overlapping targets, deactivation, rebuilds, huge radii, and non-finite/out-of-grid-range inputs.
- **480 real `Game::update` frames match the original byte for byte** in recorded health, score, damage dealt, kill count, game/player state, killer identity, surviving enemy IDs/HP, asteroid IDs, and ordered bullet positions/types/pierce counts. Fixtures include immediate kills, piercing across frames, pre-/post-movement asteroid positions, target priority, shared asteroid contacts, asymmetric asteroid radii, and invulnerability state.
- All three lethal sources appear in the comparison: enemy bullet, enemy contact, asteroid.
- The actual Windows Restart button was driven through native mouse events. Health, game state, managers and collision observer lists reset correctly. New-scene entry was also checked.
- Debug ON and Release OFF builds pass without new compiler warnings. The existing Raylib CMake deprecation notice remains.

The implementation keeps `Vector2Distance(...) <= radius` rather than changing boundary rounding with squared comparisons. Targets retain manager iteration order, so overlapping targets still select the same first match and consume random damage in the same order. Bullet queries precede movement, and asteroid snapshots are rebuilt after movement/spawns. Bullet kills deactivate immediately; entity-phase removals remain deferred. Asteroid-pair queries use the source asteroid's radius and exclude previously paired objects, exactly as before.

Storage is reused between frames. Targets live in contiguous arrays; hash buckets contain ordered index chains and conservative bounds. Queries do not allocate, copy ID strings, or sort candidates. Small sets use a direct scan. Bucket bounds were added after the first clustered benchmark exposed unnecessary crowd scans. Extremely large queries and non-finite coordinates fall back to an ordered scan safely.

## Reproduce

The test targets are opt-in and do not add controls, spawning logic, or benchmark instrumentation to the shipping executable. Use a terminal where CMake is available (the local bundled path is recorded in `library-docs.md`). From the repository root:

```powershell
cmake -S . -B build-perf -DGAME_DEBUG=OFF -DGAME_COLLISION_TESTS=ON
cmake --build build-perf --config Release -j 8
ctest --test-dir build-perf -C Release --output-on-failure
Push-Location build-perf/Release
./CollisionRegression.exe ../grid-parity.log
./CollisionBenchmark.exe 80 320 burst ../grid-80.csv
./CollisionBenchmark.exe 2000 8000 combat ../grid-2000.csv 6000
./CollisionBenchmark.exe 3000 12000 combat ../grid-3000.csv
Pop-Location
```

Each benchmark writes summary CSV, per-frame `.csv.frames.csv`, and a warmup scene capture `.csv.png`. The capture shows the scene render texture before CRT compositing; the timed loop still executes the complete post-processing pipeline. On single-configuration generators, use `-DCMAKE_BUILD_TYPE=Release` and run from `build-perf` instead of `build-perf/Release`. Assets must be beside the executable.

To compare the original collision code, retain the grid executable/log, materialize the original source in the ignored build directory, and use the reference switch. It affects only test targets; the actual game always builds the current optimized source.

```powershell
python -c "import pathlib,subprocess; pathlib.Path('build-perf/LegacyGame.cpp').write_bytes(subprocess.check_output(['git','show','52e32af84bb80e66eae5c842e7bea75b203a8e5d:src/Game.cpp']))"
cmake -S . -B build-perf -DGAME_COLLISION_REFERENCE="$PWD/build-perf/LegacyGame.cpp"
cmake --build build-perf --config Release -j 8
Push-Location build-perf/Release
./CollisionRegression.exe ../original-parity.log
./CollisionBenchmark.exe 1000 4000 spread ../original-1000.csv
Pop-Location
python tests/compare_collision_results.py build-perf/original-parity.log build-perf/grid-parity.log
cmake -S . -B build-perf -DGAME_COLLISION_REFERENCE=
cmake --build build-perf --config Release -j 8
```

Run benchmarks sequentially with no builds or other games competing for CPU/GPU. Keep the window open and stationary. A closed window or failed asset load is not a completed measurement. An exploratory run had one 32.52-second stall (`build/grid2-1000.csv`); it was retained and rerun, not silently trimmed from its average. One sustained attempt ended without a result and reported a texture-load failure; the subsequent complete run exited successfully. Neither incomplete nor exploratory results are presented as final capacity measurements. Full per-frame local logs and captures are retained under ignored `build/`; the 14 selected complete-run summaries are tracked in Git.

This work completes the requested collision optimization and local benchmark subtask. Item 28 still requires real Story/Endless balance playtests and validation on the slowest team/demo laptop.
