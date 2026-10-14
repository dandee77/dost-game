# Progress Tracker

Update this file after every completed build-plan item. Anyone reading it (teammate or AI) should immediately know what is done, what is in progress, what is next, which decisions were made, and which questions are still open.

---

## Current Status

**Phase:** 0 (Foundation)
**Last completed:** Item 04 debug tools (14 October 2026, branch `feat/04-debug-tools`); Debug ON and Release OFF builds and in-game smoke checks passed
**In progress:** Item 01 (eligibility, other team machine builds, and full gameplay/restart checks pending)
**Next:** Item 01 (eligibility question, repository, build on every machine) and item 02 (asset provenance)
**Blocked:** Open Question 1 (may Space Ablaze code be reused under rule 7?) must be answered before the team depends on the old code for the final submission
**Deadline:** 25 October 2026 (target submission 24 October)

---

## How to Update

After finishing an item:

1. Tick it below with the date and commit or PR: `- [x] 05 Run reset ... (2026-10-15, #7)`.
2. Update **Current Status**.
3. Add decisions to **Decisions Made During Build** (date, decision, reason, files changed).
4. Add a row to the **AI Usage Log** for any AI tool used in the item.
5. Add surprises, workarounds and playtest results to **Notes** or **Playtest Log**.
6. If the item changed a class, confirm `class-registry.md` matches the headers.

---

## Team Machines and Versions

Fill in during item 01.

| Machine | Owner | OS | Compiler and version | CMake | Builds? | 60 FPS at 80 enemies? |
|---|---|---|---|---|---|---|
| Local development machine | dandee77 | Windows 11 | MSVC 19.44.35229.0 (VS 2022) | 3.31.6-msvc6 | Yes, Debug | Not tested |
| Demo laptop (finals) | | | | | | |

| Dependency | Version | Notes |
|---|---|---|
| Raylib | 5.5 | Fetched by CMake |
| C++ | 20 | |
| CMake | | Minimum 3.11 |

---

## Progress

### Phase 0: Foundation
- [ ] 01 Eligibility, repository and build on every machine
- [ ] 02 Asset purge and provenance file
- [ ] 03 Config, Theme and Balance headers
- [x] 04 Debug tools (2026-10-14, `feat/04-debug-tools`)
- [ ] 05 Run reset, RunContext, RunRng and leak fixes

### Phase 1: Core Refactor
- [ ] 06 CollisionSystem extraction
- [ ] 07 HUD extraction and pause overlay
- [ ] 08 PlayerStats and damage amounts
- [ ] 09 Augment refactor
- [ ] 10 Enemy base extension

### Phase 2: Core Loop
- [ ] 11 WaveDirector
- [ ] 12 Scrap pickups and cargo
- [ ] 13 Dock, return phase and arena
- [ ] 14 Dock shop

### Phase 3: Enemies and Bosses
- [ ] 15 Reskin Low, Mid and debris
- [ ] 16 HighLevelEnemy (Compactor)
- [ ] 17 Boss framework and boss bar
- [ ] 18 The Hoarder
- [ ] 19 The Core and victory

### Phase 4: Story, Modes and Meta
- [ ] 20 Cutscene base and intro
- [ ] 21 Ending cutscene
- [ ] 22 Main menu with modes
- [ ] 23 Endless mode
- [ ] 24 Leaderboard and name entry
- [ ] 25 Credits scene

### Phase 5: Polish
- [ ] 26 Asset and audio integration
- [ ] 27 Tutorial prompts
- [ ] 28 Balance and performance pass
- [ ] 29 Feature freeze and release build

### Phase 6: Submission
- [ ] 30 Gameplay demo video
- [ ] 31 Trailer
- [ ] 32 Forms and submission

### Art and Audio
- [ ] A1 Style guide
- [ ] A2 Collector ship and player bullet
- [ ] A3 Enemies (Swarmer x3, Satellite, Compactor) with destruct sheets
- [ ] A4 Bosses and boss bullet
- [ ] A5 Debris, scrap, dock, dock arrow
- [ ] A6 Parallax backgrounds and menu background
- [ ] A7 HUD images
- [ ] A8 Cutscene images
- [ ] A9 Music and SFX

---

## Decisions Made During Planning (14 October 2026)

| # | Decision | Reason |
|---|---|---|
| D1 | Build on the Space Ablaze C++20 / Raylib 5.5 codebase | Saves days of work on movement, shooting, effects and menus. Conditional on Open Question 1 |
| D2 | Keep the flat `src/` folder | Subfolders would break every include for no gameplay gain during the sprint |
| D3 | Dock shop, pause, game over and victory are `GameState`s inside `Game`, not scenes | `Game::onSwitch()` resets the run; a scene switch would wipe the run |
| D4 | Waves with budgets replace the time-based spawn ramp; fixed seeds per mode via `RunRng` | Esports fairness and readable pacing |
| D5 | Keep the 9 augments (free pick after each wave) and add a gear shop (paid with credits) | Roguelike randomness plus a deliberate recycling economy |
| D6 | Story: 10 waves, The Hoarder at wave 5, The Core at wave 10. Endless available from the start | Fits the 11-day schedule; judges can reach bosses quickly |
| D7 | Carried scrap is lost on death; deposit converts 1 scrap to 1 credit | Risk and reward; keeps the return-to-dock trip meaningful |
| D8 | Visual tokens live in `src/Theme.hpp`, gameplay numbers in `src/Balance.hpp`, engine constants in `src/Config.hpp` | One source of truth in code; docs explain, headers decide |
| D9 | Web context files adapted: `ui-registry.md` became `class-registry.md`; `ui-tokens.md` merged into `ui-rules.md` plus `Theme.hpp`; `game-design.md` added for numbers | C++ games reuse classes, not components; tokens must live in code |
| D10 | Add a new `HighLevelEnemy` (Compactor) | Only Low and Mid enemies exist in Space Ablaze; the `HIGH_LEVEL_ENEMY` enum value is unused |
| D11 | Do not wire in `SpatialGrid` unless item 28 shows a performance need | It is unused today and collisions are cheap at expected counts |
| D12 | Claim Climate Change (primary) and Circular Economy (secondary); keep pitch claims narrow and cited | Science-department judges; the rules allow several themes |
| D13 | Local plain-text leaderboard | No networking in scope |
| D14 | Settings screen out of scope; remove the menu button | Time |
| D15 | Debug keys only with `-DGAME_DEBUG=ON` | Fast testing and clean video capture without shipping cheats |
| D16 | All ship sprites face up; reskins keep the old frame size and count | Matches the rotation code; art swaps need no code |

## Decisions Made During Build

| Date | # | Decision | Reason | Files changed |
|---|---|---|---|---|
| 2026-10-14 | D17 | Import Space Ablaze main at `72361209c6afac24a2a0400a605124b38ca46420`, preserving all 113 upstream commits | User selected the existing game as the starting point; keep `origin` pointing to dost-game and `space-ablaze` pointing to the reference repository | Source, assets, README, build files |
| 2026-10-14 | D18 | Make only the compatibility changes needed for the local MSVC baseline build | Replace 10 C-style compound literals with C++ brace initialization; select the CRT entry point for the existing `main()` in a windowed MSVC executable; enable compiler warnings and fix the optional PLATFORM condition | CMakeLists.txt, Asteroid.cpp, Button.cpp, GameTimer.cpp, MainMenu.cpp, Player.cpp |
| 2026-10-14 | D19 | Implement item 04 ahead of item 03 at the user's explicit request, seeding only the required Theme tokens | Keep the requested debug scope small; Config/Balance migration and the rest of item 03 remain pending. Existing collision behavior is unchanged | Theme.hpp, DebugTools.*, Game.*, Player.*, Application.cpp |
| 2026-10-14 | D20 | Default GAME_DEBUG to OFF; enable it in the Windows development launcher | Local `build` provides F1/F5 while release builds can omit every debug path. F2/F3/F4/F6 show unavailable explanations until their planned systems exist | CMakeLists.txt, build.bat, DebugTools.* |

---

## Open Questions

| # | Question | Owner | Needed by | Answer |
|---|---|---|---|---|
| Q1 | The Space Ablaze main menu says "Equity Quest - 2024". Was it entered in a competition or published? If yes, rule 7 forbids its code ("code from previously published or submitted games in any other competition"). Ask the organizers in writing before relying on it. If the answer is no, the team may need to rewrite on a fresh codebase, using Space Ablaze only as a design reference | Producer | 16 Oct | |
| Q2 | Student or Professional category? (Changes prizes, forms and coach rules) | Producer | 14 Oct | |
| Q3 | Game title | Team | 20 Oct (menu, trailer) | |
| Q4 | Licenses of `PerfectDOSVGA437.ttf` and `3270-Regular.ttf` | Artist | 22 Oct | |
| Q5 | Provenance of `home_music.mp3` and every SFX in `assets/sounds` | Artist | 22 Oct | |
| Q6 | Were all Space Ablaze contributors on this team? Rule 7 allows reusing personal code only if team members wrote all of it | Lead | 15 Oct | |
| Q7 | Augment offers deterministic per seed (current plan) or random? | Team | 16 Oct (item 09) | |
| Q8 | How bosses draw above other enemies: direct draw or Animator layer | Programmer 2 | 19 Oct (item 17) | |
| Q9 | Demo laptop specs and OS for the finals | Lead | 22 Oct | |
| Q10 | Final names: Bayanihan Dock, World Tree (Narra), Junk Swarmer, Rogue Satellite, Compactor, The Hoarder, The Core | Team | 20 Oct | |

---

## Known Issues and Existing Warnings

Record compiler warnings present after item 01 here, so new warnings are easy to spot.

| File | Warning | Status |
|---|---|---|
| Raylib 5.5 CMakeLists.txt | CMake deprecation warning for compatibility with CMake older than 3.10 | Existing dependency warning; no game compiler warnings in the MSVC build |

Known bugs from the code review are in `library-docs.md`, Known Pitfalls.

---

## AI Usage Log

Required for Form 03 (Asset and AI Usage Disclosure). Organizers may request prompts, development logs or version-control records. Add a row per item, per tool.

| Date | Item | Tool and model | Used for | Extent (Minimal / Moderate / Heavy) | Human review |
|---|---|---|---|---|---|
| 2026-10-14 | Planning | Claude (Anthropic) | Context files, code review of Space Ablaze, build plan | Moderate | Team review pending |
| 2026-10-14 | 01 (repository setup only) | Codex (OpenAI) | Initialize Git, prepare README, and upload the existing project documents to dandee77/dost-game | Minimal | Team review pending |
| 2026-10-14 | 01 (baseline import and local build) | Codex (OpenAI) | Import Space Ablaze with history, resolve README, fix ignore patterns and MSVC build compatibility, verify build and launch, update documentation | Moderate | Team review pending |
| 2026-10-14 | 01 (local build launcher) | Codex (OpenAI) | Repair build.bat, install a local build command in the existing user PATH, and verify compilation and game launch | Minimal | Team review pending |
| 2026-10-14 | 04 | Codex (OpenAI, GPT-6) | Implement debug overlay and invincibility, build gating and launcher, verify Raylib docs with Context7, compile Debug/Release and exercise actual key events in a temporary native integration harness; update context files | Moderate | Team review pending |

Asset generation is logged per file in `assets/ASSETS.md`.

---

## Playtest Log

| Date | Build / commit | Tester | Mode | Result (wave reached, time, deaths) | Notes |
|---|---|---|---|---|---|
| | | | | | |

---

## Machine QA Log

| Date | Machine | Build | Checks (launch, intro, Story to wave 5, Endless to wave 10, leaderboard save) | Result |
|---|---|---|---|---|
| | | | | |

---

## Notes

- 14 Oct, item 04 follow-up QA: the native harness drove the real bullet-collision/game-over path, enabled F5 on game over, then clicked the actual Restart button. F1 was reset; reopening it showed `GAME_RUNNING`, HP 100, invincibility OFF and cleared enemies/bullets. Both full application executables also launched responsively and closed normally (exit 0). Release object inspection confirmed no `DrawFPS` reference in `Application` and no debug indicator text in the executable.
- 14 Oct, item 04: MSVC Debug with `GAME_DEBUG=ON` and a fresh Release configure with `GAME_DEBUG=OFF` both built without compiler warnings (only the existing Raylib CMake deprecation notice). Temporary integration harness under ignored `build/` used actual Raylib rendering and Windows key events: F1 on/off with 35 real enemies, player/enemy bullet counts, F2/F3/F4/F6 explanations, F1 while paused, new-run overlay reset, F5 on/off, no health loss/stun/knockback while invincible, normal damage afterward, and `Player::init()` resetting invincibility. Disabled-build harness confirmed F1-F6 do not show debug UI. Screenshots and logs remain in `build/` for local review. This is a functional smoke test, not the item 28 sustained FPS benchmark; manual full gameplay/restart QA remains part of item 01.
- 14 Oct, item 04: `Game::resetRun()` does not exist yet. Debug state is reset in both current paths (`onSwitch()` and `restartGame()`); consolidate in item 05. The F1 radius revealed an inaccurate architecture note: player collision uses width 8, not 4; corrected the note without changing gameplay. F5 leaves existing collision removal behavior intact.

- 14 Oct: `build.bat` now discovers CMake from PATH or Visual Studio, configures and builds Debug, stops on failure, refreshes assets, and launches from the executable directory. `C:/Users/dande/.local/bin/build.cmd` forwards to this checkout, enabling plain `build` in PowerShell without changing execution policy or PATH. Verified the command compiled and launched a responsive game; the wrapper is machine-local and not tracked in Git.
- 14 Oct: Imported the source and assets from Space Ablaze after the initial documentation upload. Local Debug build passed using Visual Studio's bundled CMake (not on PATH). Executable and copied assets are in `build/Debug/`; run from that directory. Launch smoke check stayed responsive for 8 seconds and closed normally; a game-over/restart playtest and other team machines remain unverified. Existing assets are retained for the item 02 provenance audit.
- 14 Oct: Initialized the repository on `main` with origin `https://github.com/dandee77/dost-game.git`. This workspace currently contains project instructions and context documents only; no game source, assets, or CMake project are present, so a build cannot yet be verified. Item 01 remains incomplete.
- 14 Oct: Code review findings: `CollisionSystem.*` and `Pause.*` are empty files; `SpatialGrid` is unused; collisions are brute-force loops in `Game::update`. Only Low and Mid enemies exist. `MainMenu` links to `Settings` and `Credits` scenes that do not exist. The game builds cleanly on Linux with Raylib 5.5 (checked 14 Oct).
- 14 Oct: The `.gitignore` contains `*.txt`, which silently ignores any new text file, including font license files (`OFL.txt`) needed for asset provenance. Replace it with `leaderboard.txt` in item 01.
