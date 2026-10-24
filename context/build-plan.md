# Build Plan

The order in which the game is built between **14 October** and the **25 October 2026** submission. Each numbered item is one unit of work: one branch, one pull request, one entry in `progress-tracker.md`. Do not start an item until its dependencies meet the Definition of Done in `code-standards.md`.

## Current checkpoint — DOC-17 Legendary Luck and card tiers

Record Legendary Luck, its selected ten-rank cap and card-only progression; present the 33-card tier roster and distinguish proposed payout/rarity tuning from confirmed rules. Verify documentation and existing build; no source changes in this checkpoint.

## Task-list maintenance for every work item

**23 October owner implementation authorization:** The owner explicitly selected “Implement and update the stats document.” Earlier context-only restrictions below are historical. Current sequence: population-led enemy pacing; T01 progression/economy calculations; T02 consistent paired loot; T03 salvage-driven queued choices. Build and verify each checkpoint. Five-mode hub/shop/weapon/boss content is not silently declared implemented. The owner also reopened general balance and Chaos scheduling; Chaos uses all finished bosses with increasing concurrent pursuit over time.

Read [todo/06-task-list/tasks.md](../todo/06-task-list/tasks.md) before each item. During work, add missing requirements or discovered issues there and optional alternatives to [ideas.md](../todo/06-task-list/ideas.md). After verification, mark the matching task, append dated evidence to [completed.md](../todo/06-task-list/completed.md), and reconcile this plan, the root TODO index and progress tracker in the same change. Follow the [folder maintenance rules](../todo/06-task-list/README.md); partial work stays open. Implementation remains authorized; the current requested checkpoint is context reconciliation, with no source edits.

## 23 October economy checkpoint

Selected weapon prices are 500/1500/4000/10000 (16000 total), Swarm T5 target is 20–25 combat minutes, and Survival retains shared prices/lower-tier outcomes. Attribute/owned-rank prices scale 5x, special acquisitions 10x. Hull repair is 10 scrap per missing HP with proportional affordable repair; Shield Battery replaces paid shield recharge. Four material labels use one wallet and existing enemy-tier values. Five battery sizes, replacement arithmetic and scaled prices are settled in game-design.md; per-variant material coverage still needs content verification. Adopt these contracts for future T02/T07/T08/T10; this documentation does not implement them.

## 23 October weapon-stat checkpoint

Owner accepted names/path with T4/T5 choices (1/3/5/7/10 nodes). Full proposed profiles/signatures and analytical comparisons now exist in game-design.md. PREP-27 remains open for numerical adoption, exact card compatibility and combined effect limits; REVIEW-07 tracks live viability. Paper DPS is not completed T08/T10 gameplay. Implementation authorization does not certify these draft values as balanced.

## 21 October weapon/attribute review checkpoint

Prepare and review the [upgrade proposals](../todo/07-upgrade-proposals/README.md) before changing T03/T04/T08. Confirmed direction includes mothership cannon progression, locked run branches, 25% purchased numeric gains, retained shield cards and Legendary reactive Blink. Details remain candidate designs. Bosses, schedules, names, geometry and broad economy review are owner-deferred; keep tasks open and collect upgrade questions for later. Expand T08 to the weapon/attribute sections alongside eligible skill offers; do not implement the obsolete full-rank numeric-augment shop.

## 21 October context preparation checkpoint

Current work is documentation only. Pending briefs are organized into planning, story, gameplay, economy and verification folders under [todo/](../todo/README.md). Read the [gap register](../todo/00-planning/decisions-and-gaps.md) and [preparation checklist](../todo/04-verification/preparation-checklist.md) before a later implementation instruction. Required shared context files stay here; completed work is not reopened.

HOPE/source-containment canon replaces the old settlement/tree story. The owner's biological follow-up replaces the autonomous-machine premise: existing engineered waste-eaters mutate after the separate atmospheric release, and the theme emphasizes neglect and postponed responsibility. The [world brief](../todo/01-story/world-and-campaign.md) and [revised storyboard](../todo/01-story/story-context.md) govern items 17-21/30-31. [Material families](../todo/03-economy/scrap-types.md) extend T01/T02 metadata and presentation without changing reward amounts or adding crafting. Actual boss content, mode spawn tables and other blocking design data remain pending; folders and detailed briefs do not constitute implemented features.

## 20 October handoff revision (documentation only)

Pending work is collected in [todo/README.md](../todo/README.md), beside assets/build/context. This build plan remains at its required reference path; use the TODO index and latest gameplay brief to interpret superseded older work packages.

The current owner request is to prepare context only. [todo/02-gameplay/gameplay.md](../todo/02-gameplay/gameplay.md) replaces the old pause/scrap/difficulty specification and defines the expanded hub/mode/progression/return/shop design for a teammate's later implementation brief. No code work is authorized by this documentation update.

Completed P6 checkpoint 1 stays complete. The next future checkpoint is **T01: typed mode/difficulty and run-progress/return contracts**, after adopting/revising the clearly marked defaults. Follow TODO section 13 in dependency order; a single implementation brief may authorize the whole sequence while retaining one buildable checkpoint at a time.

Affected older numbered items are reference work packages, with these revisions:

| Older item | Current target replacement |
|---|---|
| 07 HUD/pause | Add return/XP/wallet/shield clarity and source-state-aware hub pause |
| 11 WaveDirector | Five mode objectives; no timer/wave-clear upgrade cards |
| 12 Scrap/cargo | Paired reward: random trade currency and fixed salvage XP/return charge; isolated loot RNG; no cargo cap |
| 13 Dock/return | Safe colony hub; shield/charge-gated return; suspended expedition; paid repair/recharge transactions |
| 14 Dock shop | Delegated owned-skill rank purchases and four priced rare abilities; no seven-line gear ladder |
| 17-19 Bosses | Framework/content dependency; owner to define final roster, older bosses provisional |
| 22 Main-menu modes | Start -> difficulty -> hub portals |
| 23 Endless | Swarm normal-crowd endless; Chaos separately mixes bosses and swarms |
| 24 Leaderboard | Separate mode/difficulty/rules identities; full UI remains later work |
| 27 Tutorial | Hub interaction/portals, field scrap upgrades, shield-blocked Return Home |

The old dated timeline is historical planning, not proof these items are finished. All five modes remain requested; a submission cut needs team direction. Follow the tracker for delivered work and unresolved boss content.

Narrative production reference: [todo/01-story/story-context.md](../todo/01-story/story-context.md) supplies the revised source-containment story and confirmed alternating text-card/animated-footage format: five pairs for a 40-second intro, six pairs plus title for a 90-second trailer. This replaces the earlier seven-panel presentation target for items 20/21/30/31; illustrations may supply scenery but need actual moving actions. No asset generation is authorized, and the separate gameplay demo remains required.

---

## Core Principle

**15 October user-requested P4: debris variants and harvesting.** Implemented ahead of numbered order: rename Asteroid/AsteroidManager to Debris/DebrisManager, ten AI-assisted pixel-art variants with fixed sizes, restored eight-frame destruction followed by red glow texture orbs at saved final-fleck coordinates, uncapped run-local harvested scrap (user confirmed), HUD counter and debug gallery. Follow-up: unique per-kind destruction art/particle layouts and initially a dedicated barricade trash-monster sprite/death with no drops; the latest user correction restores legacy asteroid art and three size tiers with random spin. This is scoped to debris salvage and barricade A5 art; item 12 enemy drops/cargo and item 13 docking remain pending. Existing enemy, wave and shop work is not included.

**Playable at the end of every item.** Every item ends with something you can see and test in the running game. No item leaves the build broken. Refactors (items 03 to 10) must not change how the game plays; new features come after the foundation is safe.

Second principle: **scope down, not quality down.** If the schedule slips, cut from the bottom of the list (Endless polish, Credits scroll effects, extra juice), never from Completeness: a stable, polished 10-wave Story mode beats a buggy feature list. Pre-screening weighs Completeness at 20%.

---

## Timeline

| Date | Phase | Items | Checkpoint |
|---|---|---|---|
| Wed 14 Oct | 0 Foundation | 01, 02 (start), A1 | Everyone builds and runs the game; eligibility question sent |
| Thu 15 Oct | 0 Foundation | 02, 03, 04, 05 | Same gameplay as Space Ablaze, with debug console and clean resets |
| Fri 16 Oct | 1 Core refactor | 06, 07, 08, 09, 10 | Same gameplay; collisions, HUD, stats and augments restructured |
| Sat 17 Oct | 2 Loop | 11, 12 | Waves with banners; enemies drop scrap |
| Sun 18 Oct | 2 Loop | 13, 14 | **Full core loop**: wave, scrap, return, dock shop, next wave |
| Mon 19 Oct | 3 Enemies | 15, 16, 17 | Reskinned enemies, Compactor, boss framework |
| Tue 20 Oct | 3 Enemies, 4 Story | 18, 19, 20 | Both bosses; intro cutscene |
| Wed 21 Oct | 4 Story and modes | 21, 22, 23, 24, 25 | Story start to ending; Endless; leaderboard; credits |
| Thu 22 Oct | 5 Polish | 26, 27, 28, 29 | **Feature freeze at end of day**; release build on the demo laptop |
| Fri 23 Oct | 6 Submission | 30, 31 | Gameplay video and trailer cut |
| Sat 24 Oct | 6 Submission | 32 | **Submit** |
| Sun 25 Oct | Buffer | | Deadline; fix only what blocks submission |

### Team split

| Track | Owner | Items |
|---|---|---|
| Core gameplay | Lead programmer | 01, 03, 05, 06, 11, 12, 13, 23, 28, 29 |
| Enemies and combat | Programmer 2 | 08, 10, 15, 16, 17, 18, 19 |
| UI and meta | Programmer 3 | 04, 07, 09, 14, 20, 21, 22, 24, 25, 27 |
| Art and audio | Artist | 02, A1 to A9, 26 (with Programmer 3) |
| Submission | Producer | 30, 31, 32, `assets/ASSETS.md`, AI Usage Log, forms |

With fewer people, merge tracks; keep the order.

### Dependencies

```
01 ─> 03 ─┬─> 05 ─> 06 ─┬─> 08 ─┬─> 09
          │      │      │       └─────────────────────> 14
          │      │      └─> 10 ─┬─> 11 ─> 12 ─> 13 ─> 14
          │      │              │    └─> 17 ─> 18, 19 ─> 21
          │      │              └─> 16          11 + 17 ─> 23
          │      └─> 22 ─> 24
          ├─> 04, 07, 25
          └─> 20 ─> 21
A1 ─> A2..A9 ─> 15, 26
```

---

## Phase 0: Foundation

### P6 Pause, scrap, difficulty and automatic skills (user request, 19 Oct)
**Specification:** [todo/02-gameplay/gameplay.md](../todo/02-gameplay/gameplay.md), rewritten as the 20 October design handoff. The former implementation/push limiter is historical; this session is context-only.
**Checkpoint 1:** audit and pause-safe timers. Classes: Cooldown, GameTimer, Enemy/MidLevelEnemy, EnemyManager, DebrisManager, KillCounter, Animator, Game.
**Status:** Checkpoint 1 implemented and verified (Debug/Release/ASan/UBSan, native pause/reset/input tests, collision harness, 108.3 FPS in the rendered 80-enemy burst case). Remaining checkpoints are not implemented.
**Done when:** gameplay cooldowns and animations freeze during pause/console/card selection, run time advances from simulation delta, game-over presentation cannot advance the world, and restarts clear timer debt.
**Test:** native PauseChecks (including a real ten-second pause, native Esc/P, no resume shot, stun/recharge parity and run reset), full Debug/Release equipment and spatial suites, sanitizer suite, existing collision harness and rendered 80-enemy benchmark.
**Remaining work:** TODO T01-T10 preserves unfinished progression, scrap, UI and skill requirements and adds the requested colony hub, mode contracts, Return Home and proposed skill shop. Base repair is now specified with the hub; no implementation occurred in this documentation revision.

### P5.1 Repeat-pick ability upgrades (user-requested scope, 18 Oct)
**Status:** Complete. Debug/sanitizer 10,054 native checks, Release 9,969 checks and 610,000 spatial queries passed; level/card previews and packaged startup commands checked. Human balance review pending.
**18 October follow-up:** User removed the five-level ability cap. Physical size freezes at level 5; quantity and other numerical growth continue. Debug/Release/sanitizer builds and expanded native suites pass; live balance review remains pending.
**Classes:** SkillSystem, Game, Card; Balance/Theme tokens; existing SkillChecks native suite.

  - Add repeat-pick levels for all eighteen abilities, preserving cooldown debt and snapshotting active casts. Follow-up: remove the five-level cap; physical size stops at level 5 while counts and other stats continue.
  - Mix typed ability cards into the existing timed picker; keep abilities eligible at every practical level and lock one choice per offer.
- Space Collapse gains count/radius; Combat Drone gains count, real HP and damage; tune all other abilities individually.
- Expose levels/upgrades through cards, Q HUD and F5/startup commands; preserve reset, pause and reward rules.

**Done when:** repeated card/command picks improve actual effects and restart clears progression.
**Test:** Debug/Release native suites, expanded upgrade regressions, level/card render previews and sanitizer checks. No new assets or shop system.

### P5 Skills and augments prototype (user-requested scope, 17 Oct)
**Status:** Complete; Debug/Release builds, 9,414/9,331 native checks, 610,000 spatial queries, catalog/startup command validation and native placeholder preview passed. Human balance/feel review pending.
**Classes:** Augment catalog, SkillSystem (Game-owned), Player, Enemy, EnemyManager, ScrapManager, Card, DebugTools, Application; Balance/Theme/Config tokens.

- Implement all 14 augments and 18 active abilities from `skills-context.md`, with existing art and simple placeholder shapes.
- Expose typed augment/ability commands in F5 with autocomplete and repeatable terminal `--command` launch arguments; provide `--skills-list` without a window.
- Implement only combat/effect support needed by the skills. Acquisition, inventory, drops for acquiring skills, shop and progression connections are deferred explicitly by the user.
- Centralize provisional tuning, support simulation-time cooldowns and statuses, and clear state on restart/exit/death. Space Collapse must award no scrap.

**Done when:** Every skill has observable behavior, can be exercised by command, and passes native effect/reward/reset validation in debug-enabled and debug-disabled builds. No new art generation.
**Test:** `GAME_EQUIPMENT_TESTS=ON`, CTest; native skill gallery; terminal catalog and startup-command launch; validate damage, immunity/crowd control, scrap suppression, interception, all primary weapons, invalid commands, pause, restart and 30/144 FPS timing. See `skills-commands.md`.

This explicit user request overrides numbered ordering and the old nine-augment scope for P5 only. It does not mark unrelated foundation, wave, economy, boss, or submission items complete.

### P3 Shrinking barricade event (user-requested scope, 14 Oct)
**Status:** Complete; Debug/Release builds and native integration checks pass; rendered asteroid ring inspected.
**Classes:** BarricadeEnemy (Enemy subclass), BarricadeEvent (Game-owned coordinator), EnemyManager, Game, Player, DebugTools; Balance/Config/Theme tokens.

- At 2:00, create a durable asteroid-art ring centered on the player's current location while ordinary enemy spawning continues.
- Shrink for 30 seconds. Individual segments take normal weapon damage; surviving segments physically block and bounce the player even during iframes, while damage respects vulnerability.
- Exclude event enemies from crowd separation and ordinary kamikaze/debris collision removal. Destroyed segments open real gaps.
- Scatter survivors outward on timeout; remove them after four seconds. Clear early after distant/offscreen escape. Smoothly widen/restore camera zoom; pause/reset all event state correctly.
- Add `spawn barricade event` to F5 help and autocomplete.
- Follow-up: double the starting radius while reaching the original radius 45 at 30 seconds, retain the original event zoom 13, and use 64 smaller segments with a slow formation orbit. Separate `stats` from `hitbox`, include live event diagnostics and darken console/dropdown backgrounds.

- 15 October correction: restore original asteroid idle/seven-frame breakup, random small/medium/large sizes with matching hitboxes and independent random spin. Retain radius 130 to 45 over 30 seconds, zoom 13, orbit and no-drop deaths. Verify mixed-size containment/gaps and spin at 30/144 FPS.

**Done when:** automatic/manual triggers, combat, containment, escape, scatter, camera and reset checks pass in Debug/Release; native render inspected.
**Test:** swept contact across every seam, boost and iframe checks, all weapon paths, pause/restart, capacity/command validation, timeout and early escape, frame-rate independent zoom. User request overrides numbered item order only for P3.

### P2 Console dropdown and enemy crowd separation (user-requested scope, 14 Oct)
**Status:** Complete; Debug/Release builds, native checks, render inspection and sequential performance measurements passed. See `crowd-performance.md`.
**Classes:** DebugTools, EnemyManager, Enemy, SpatialGrid, Animator, MidLevelEnemy; Theme/Balance/Config tokens.

- Replace horizontal command suggestions with a bounded vertical dropdown, selection, scrolling and keyboard completion.
- Follow-up: `spawn lowlevel enemy <quantity>` creates real low enemies around the player with autocomplete, strict quantity validation, capacity feedback and live-run guards.
- Separate living low-level enemies with soft, time-scaled pushes and bounded spatial queries. Mid-level enemies overlap freely, preserve their flight logic and render above low-level enemies.
- Reuse storage and clear crowd observers on existing run resets. Keep combat hitboxes, damage and spawn rules unchanged.
- Record measured rendered FPS and isolated solver timings at increasing enemy counts.

**Done when:** every suggestion is reachable, line/pile fixtures spread, flying enemies remain unaffected and draw on top, Debug/Release checks pass, and measured performance is documented.
**Test:** native console keys and renders; crowd pair/line/pile, frame-rate, reset and flying-layer checks; SpatialGrid parity; sequential Release rendered benchmarks. This user request overrides numbered item order only for P2.

### P1 Player equipment prototypes (user-requested scope, 14 Oct)
**Status:** Complete on `feat/player-equipment`; Debug/Release builds, native tests and render inspection passed.
**Classes:** Player, Bullet, Game, DebugTools, ResourceManager, LoadingScreen; Balance/Theme/Config tokens.

- Organize the supplied modular ship pack, preserving PNGs, editable sources and CC0 notice.
- Implement cannon, continuous laser, explosive rockets and piercing heavy shots; all four engines, four shields and hull damage art.
- F5 presets (`player default build`, `player gunner build`, `player cannon build`, `player laser build`, `player rockets build`, `player heavy build`) and individual weapon/engine/shield commands. No unlocks, drops, prices or shop integration.
- All presets are shield-free. Shields remain separate equipment selected explicitly with `player shield ...` for testing; future skill integration is deferred.
- Keep gameplay state in Player/Bullet; integrate hit resolution and rewards with the existing Game path. Both current reset paths reset equipment through Player::init.

**Done when:** all variants have working combat/movement/protection, timers stop outside gameplay, switching and restarting leave no stale attacks, both Debug ON and Release OFF build, and `todo` is removed after verified asset relocation.
**Test:** `GAME_EQUIPMENT_TESTS=ON`; run CTest in Debug and Release. Inspect native preset/hull and laser previews; use F5 presets, LMB/E and Space, check hitboxes, pause and restart. This explicit request supersedes normal item order only for P1; items 01–03/05–29 retain their existing status.

### 01 Eligibility, repository and build on every machine
**Owner:** Lead. **Date:** 14 Oct.

- Producer emails the organizers (from the registration contact) asking whether code from Space Ablaze ("Equity Quest - 2024") may be reused under rule 7, with a one-paragraph description. Record the answer in `progress-tracker.md`, Open Question 1. Until answered, build on the code but keep the AI Usage Log and commit history clean so a rewrite path stays possible.
- Register the team through the official link if not done.
- Create the project repository from Space Ablaze (new repo or fork; keep history).
- Add `AGENTS.md`, `CLAUDE.md` and `context/` to the root.
- `.gitignore`: `build/`, `build-*/`, `*.exe`, `leaderboard.txt`, `.vscode/`, `compile_commands.json`. Note: the current `.gitignore` ignores `*.txt`, which would silently ignore new text files such as font license files; replace that line with `leaderboard.txt`.
- `CMakeLists.txt`: add warning flags, fix `if (PLATFORM STREQUAL "Web")` (see `library-docs.md`).
- Every programmer configures, builds and runs on their own machine.

**Done when:** every team machine builds and runs the game; versions recorded in `progress-tracker.md`.
**Test:** play one Space Ablaze run to game over and restart once on each machine.

### 02 Asset purge and provenance file
**Owner:** Artist with Lead. **Date:** 14 to 15 Oct.

- Create `assets/ASSETS.md` with columns: file, key, source (team / AI tool + model / licensed), author or prompt, license, edits, date.
- Add a row for every existing file. Mark each `keep`, `replace` or `unknown`.
- `game_music` (a third-party track) is **replace** without exception. Every `unknown` is **replace**.
- Until replacements exist, keep the old files but list them as `replace`. Nothing marked `replace` may remain at item 29.

**Done when:** every file in `assets/` has a row.
**Test:** `ASSETS.md` row count equals the file count in `assets/` (excluding `desktop.ini`, which should be deleted).

### 03 Config, Theme and Balance headers
**Owner:** Lead. **Date:** 15 Oct. **Depends on:** 01.

- Create `src/Config.hpp` (`GAME_SCREEN_WIDTH`, `GAME_SCREEN_HEIGHT`, camera zooms, despawn distances), `src/Theme.hpp` (from `ui-rules.md`), `src/Balance.hpp` (from `game-design.md`).
- `Scene.hpp` includes `Config.hpp` instead of defining the screen size. Remove the duplicate defines in `Player.cpp` and the constants in `Application.cpp`.
- Replace inline numbers in the files touched for this item only (Player, enemies, managers) with the `Balance` constants that already match (SA values). Behavior must not change.

**Done when:** the game builds and plays exactly as before.
**Test:** one run to wave-equivalent of 3 minutes; compare feel with the original build.

### 04 Debug tools
**Owner:** Programmer 3. **Date:** 15 Oct. **Depends on:** 03.

- `GAME_DEBUG` CMake option; `DebugTools` class owned by `Game`.
- F5 opens/closes a translucent terminal at the top left. Extend the existing `DebugTools`; `Application` routes console input and rendering in every scene.
- Commands: `hitbox`, `mute`, `invincible` with optional `on`, `off`, or `toggle`; `help`, `clear`, `close`. `credits`, `boss`, and `wave` explain their pending systems (items 12, 17, 11).
- Tab completes command names/arguments; Up/Down recalls history. Console focus blocks underlying controls and pauses the running game timer; closing restores the prior state. Mute remains session-wide and restores the previous volume.
- `Application`'s `DrawFPS` only in debug builds. Old F1/F2/F3/F4/F6 actions are removed.

**Done when:** debug build supports the console and existing debug actions; release has no debug console or FPS counter.
**Test:** F5, `hitbox on` in a run with 30+ enemies; test Tab, history, mute, invincibility, pause/augment/game-over focus and restart. Build with `-DGAME_DEBUG=OFF` and confirm F5 does nothing.

### 05 Run reset, RunContext, RunRng and leak fixes
**Owner:** Lead. **Date:** 15 Oct. **Depends on:** 03.

- `Game::resetRun()` replaces the duplicated reset lists in `onSwitch()` and `restartGame()`.
- Move `prevGameTimer` and `gameOverTextStarted` into `Game`.
- Remove the per-frame `std::cout` in `EnemyManager::update`.
- Remove the `Animator::Update()` call from `Game::update()`'s `GAME_OVER` case.
- Add `Animator::has(name)`; guard `IsCompleted` calls.
- Register `player_shoot` and `kill` sounds in `ResourceManager`; replace the repeated `LoadSound` calls with sound aliases.
- Create `RunContext` (mode, seed, last result) and `RunRng`.

**Done when:** restarting 10 times in a row leaves no leftover enemies, bullets or animations, and memory does not grow.
**Test:** debug build, restart 10 times from game over; watch the `hitbox` counts return to zero and the process memory in Task Manager stay flat.

---

## Phase 1: Core Refactor (no gameplay change)

### 06 CollisionSystem extraction
**Owner:** Lead. **Date:** 16 Oct. **Depends on:** 05.

- Move the two collision regions from `Game::update` into `CollisionSystem::run`, returning a `CollisionReport` (see `class-registry.md`). `Game` applies the report (score, sounds, kill counter, game over).
- Behavior identical to before.

**Done when:** `Game::update` has no collision loops; gameplay unchanged.
**Test:** die once from each killer type (enemy bullet, enemy contact, asteroid); confirm the "Killed by" panel is correct each time.

### 07 HUD extraction and pause overlay
**Owner:** Programmer 3. **Date:** 16 Oct. **Depends on:** 03.

- `HUD` class with `HudData`; move the health bar, kill counter and timer drawing out of `Game::draw`.
- `PauseOverlay` in the empty `Pause.*` files; P and Esc toggle pause; Resume and Quit to Menu buttons.
- Game-over buttons become value members (no `new`).
- All HUD positions and colors from `Theme`.

**Done when:** HUD looks the same; pause has a visible menu.
**Test:** pause during a fight, resume, pause again, quit to menu, start a new run.

### 08 PlayerStats and damage amounts
**Owner:** Programmer 2. **Date:** 16 Oct. **Depends on:** 06.

- Group player stats into `PlayerStats` initialized from `Balance`.
- `takeDamage(int amount, Vector2 sourcePosition, float knockbackScale)` applies armor; minimum 1.
- `Bullet` carries `damage`. Mid-level bullets use `Balance::MID_BULLET_DAMAGE`.
- Health bar uses `health / maxHealth`.
- Existing augment methods modify `PlayerStats`.

**Done when:** same feel at base stats; damage numbers in `Balance` actually change damage taken.
**Test:** temporarily set `MID_BULLET_DAMAGE` to 30 in a debug build; one hit takes 30. Revert.

### 09 Augment refactor
**Owner:** Programmer 3. **Date:** 16 Oct. **Depends on:** 08.

- `Augment.hpp/.cpp` with `AugmentId`, info table, `rollAugmentOffer(RunRng&)`, `applyAugment(Player&, AugmentId)`.
- `Card` stores an `AugmentId`. Remove the title if-chain from `Game` and `utils::augmentPool`.
- Fix the Trigger Happy description; Nano Repair heals 25% of max health.

**Done when:** every augment still works; no string comparison decides an augment.
**Test:** pick each of the 9 augments at least once (debug: temporarily force offers) and observe its effect.

### 10 Enemy base extension
**Owner:** Programmer 2. **Date:** 16 Oct. **Depends on:** 06.

- Add to `Enemy`: `maxHealth`, `scoreValue`, `scrapValue`, `contactDamage`, `displayName`, `isBoss()`, `getCollisionRadius()`, `applyHealthScaling()`.
- Low and Mid constructors set them from `Balance`. Remove the hardcoded score switch in `Game`/`CollisionSystem`; use `getScoreValue()` and `getContactDamage()`.
- "Killed by" uses `getDisplayName()`.

**Done when:** scores and contact damage come from the enemy.
**Test:** kill one of each type and check the score increments (10 and 50).

---

## Phase 2: The Core Loop

### 11 WaveDirector
**Owner:** Lead. **Date:** 17 Oct. **Depends on:** 05, 10.

- `WaveDirector` with phases `WAVE_LAUNCH`, `WAVE_ACTIVE`, `WAVE_BOSS` (boss spawn stubbed until 17), `WAVE_CLEARED`, `WAVE_RETURN`.
- Story wave table from `Balance::STORY_WAVES`; budget spending, groups, alive cap, HP multiplier, `RunRng` for type picks and angles.
- `EnemyManager` stops spawning on its own; gains `spawn()`, `aliveCount()`, `killAllNonBoss()`.
- Debris spawning follows the wave's `debris` flag and stops outside `WAVE_ACTIVE`.
- Wave banner and wave label in `HUD`.
- On `WAVE_CLEARED`, `Game` opens the augment cards (replacing the 20-second timer). After the pick, the director enters `WAVE_RETURN`; until item 13 exists, `WAVE_RETURN` immediately starts the next wave.
- Debug: connect the `wave` console command (advance wave). `mute` controls master audio; no clear-wave command is currently assigned.

**Done when:** waves 1 to 4 play in order with banners and augment picks between them; the same seed produces the same waves.
**Test:** play waves 1 to 3 twice with the same seed; enemy counts per wave match (`hitbox` overlay).

### 12 Scrap pickups and cargo
**Owner:** Lead. **Date:** 17 Oct. **Depends on:** 10, 11.

- `ScrapPickup` and `ScrapManager`; kills (and player-destroyed debris) spawn scrap per `scrapValue`.
- Magnet attraction, pickup radius, lifetime and blink.
- Cargo in the run state; `CARGO FULL` handling; cargo lost on death.
- HUD cargo counter; pickup sound (placeholder allowed).
- Debug: `credits` adds credits and fills cargo.

**Done when:** kills spray gold scrap that flies to the ship and fills cargo.
**Test:** collect until cargo is full; confirm further pickups stay on the ground and expire; die and confirm cargo resets.

### 13 Dock, return phase and arena
**Owner:** Lead. **Date:** 18 Oct. **Depends on:** 11, 12.

- `Dock` entity at the origin; player spawns at the dock.
- During `WAVE_RETURN`: dock beacon on, HUD arrow toward the dock when it is off screen, "RETURN TO DOCK" prompt.
- Entering the dock radius during `WAVE_RETURN` sets `GAME_DOCKED`. Until item 14, `GAME_DOCKED` shows a placeholder "DOCKED: PRESS SPACE TO LAUNCH".
- Deposit: cargo becomes credits, score += 2 per scrap.
- Arena soft boundary with warning and pushback.

**Done when:** the full loop runs: wave, scrap, return, deposit, launch, next wave.
**Test:** play waves 1 to 3 through the dock each time; credits equal deposited scrap.

### 14 Dock shop
**Owner:** Programmer 3. **Date:** 18 Oct. **Depends on:** 08, 13.

- `UpgradeShop` (data, costs from `Balance`, `buy()` applies effects to `PlayerStats`), `DockShopUI` per the layout in `ui-rules.md`, repair, Launch.
- `Button::setEnabled()`.
- Upgrade levels reset in `resetRun()`.

**Done when:** all 7 upgrades can be bought to level 5 and their effects are visible.
**Test:** debug `credits` command; buy every upgrade to max; check speed, damage numbers, magnet radius (`hitbox` shows it), cargo capacity and max HP on the HUD.

---

## Phase 3: Enemies and Bosses

### 15 Reskin Low, Mid and debris

**15 October user-requested bullet feedback (complete):** Add a cosmetic charge/core/trail/contact-burst/reaction/sound/aftermath chain to existing player and enemy bullets. Keep weapon cadence, movement, damage, collision order and live projectile art unchanged. Use Bullet/BulletManager ownership, bounded effects, simulation-time cleanup and existing reset paths. Add one original AI-assisted eight-frame impact strip and one original synthesized impact sound with full provenance. Debug/Release builds, native regression checks and native preview must pass. Remaining item 15 enemy art is still pending.

**15 October user-requested low-enemy reskin (complete):** Replace all three low-enemy idle sheets and their matching destruction sheets with concrete mutated-trash creatures: crushed can, leaking battery and cracked monitor. Preserve 64 x 64 frames, idle counts 10/5/5, death counts 8/8/7, existing keys, timing, scale and gameplay. Archive originals, record prompts/provenance, inspect every exported frame and native crowd rendering, then build and run existing integration checks. Mid enemies and remaining item 15 art remain outside this request.
**Owner:** Programmer 2 with Artist. **Date:** 19 Oct. **Depends on:** A3, A5.

**14 Oct user-requested debris-only work:** orbital scrap intact/destruction textures delivered with original 96 x 96 frame size; destruction expanded from seven to eight frames at the user's request. Originals archived under `assets/textures/legacy/`, provenance/prompts recorded. Debug build and 7,513 native checks pass. Human art review and all other item 15/A5 assets remain pending.

- Drop in the new sheets with the same sizes and frame counts (no code change), or update `Theme::FRAMES_*` if counts changed.
- Optional toxic tint pulse on enemies (`Theme::COLOR_TOXIC`).
- Enemy bullet art; debris art.

**Done when:** no Space Ablaze enemy art remains.
**Test:** play wave 3; every sprite is new; destruct animations play fully.

### 16 HighLevelEnemy (Compactor)
**Owner:** Programmer 2. **Date:** 19 Oct. **Depends on:** 10.

- Four-state behavior from `game-design.md`; windup flash telegraph; 3-bullet spread; ignores knockback while charging; extra damage taken while recovering.
- Registered in `EnemyManager::spawn`; appears from Story wave 6.
- Placeholder art (a tinted mid-level sheet) until A3 delivers.

**Done when:** Compactors charge visibly and fairly.
**Test:** debug-spawn 3 Compactors; dodge the charge after seeing the flash; confirm a charge hits for 20.

### 17 Boss framework and boss bar
**Owner:** Programmer 2. **Date:** 19 Oct. **Depends on:** 10, 11.

- `Boss` base: intro invulnerability, phase thresholds, `fireRing`, `fireAimed`, `spawnAdds`, contact damage without removal, no knockback, death explosion and scrap.
- `EnemyManager::spawnBoss`, `getBoss`, `hasBoss`.
- `WaveDirector` spawns bosses on boss waves. HUD boss bar with name and phase ticks. Boss music switch. Background tint during bosses.
- Decide and record how bosses draw above other enemies.
- Debug: `boss` jumps to the next boss wave.

**Done when:** a test boss (Hoarder with only its ring attack) spawns on wave 5, shows a bar and can be killed.
**Test:** `boss`, kill the boss, confirm the wave clears and augment cards appear.

### 18 The Hoarder
**Owner:** Programmer 2. **Date:** 20 Oct. **Depends on:** 17.

- Full two-phase behavior from `game-design.md`.

**Done when:** a player with average upgrades beats it in 60 to 120 s.
**Test:** two teammates attempt it; record time to kill and deaths in `progress-tracker.md` Notes.

### 19 The Core and victory
**Owner:** Programmer 2. **Date:** 20 Oct. **Depends on:** 17.

- Three-phase behavior from `game-design.md`.
- In Story, its death sets `GAME_VICTORY`: stop spawns, explosion, 3 s hold, fill `RunContext::lastResult`, switch to `"Ending"` (until item 21, return to `"MainMenu"`).

**Done when:** The Core can be beaten and Story ends cleanly.
**Test:** `boss` twice to wave 10; win; confirm the transition and that a new run starts clean.

---

## Phase 4: Story, Modes and Meta

### 20 Cutscene base and intro
**Owner:** Programmer 3. **Date:** 20 Oct. **Depends on:** 03; art A8 for final images (placeholders allowed).

- `Cutscene` abstract scene, `IntroCutscene` with the 7 slides from `project-overview.md`.
- `LoadingScreen` returns `"Intro"`; intro returns `"MainMenu"`.
- Typewriter text, slow zoom, skip controls.

**Done when:** the intro plays after loading and can be skipped at any time.
**Test:** watch it fully once; skip it with Esc once; advance with Space through every slide once.

### 21 Ending cutscene
**Owner:** Programmer 3. **Date:** 21 Oct. **Depends on:** 19, 20.

- `EndingCutscene` slides, run stats card, then `"Leaderboard"` or `"MainMenu"`.

**Done when:** winning Story plays the ending.
**Test:** debug win (`boss` to wave 10, `invincible on`); ending plays and returns correctly.

### 22 Main menu with modes
**Owner:** Programmer 3. **Date:** 21 Oct. **Depends on:** 05.

- Buttons: Story, Endless, Leaderboard, Credits, Exit. Remove Settings.
- Story and Endless set `RunContext` mode and seed, then return `"Game"`.
- New title text and footer (see `ui-rules.md` S-03).

**Done when:** both modes start from the menu.
**Test:** start each mode; confirm the wave tables differ (Endless wave 1 budget 14, wave 3 budget 34).

### 23 Endless mode
**Owner:** Lead. **Date:** 21 Oct. **Depends on:** 11, 17.

- `WaveDirector` formulas for Endless; repeating bosses with HP scaling; The Core does not end the run.

**Done when:** Endless runs to wave 15 without errors.
**Test:** debug build, `invincible on` + `wave` to wave 15; watch counts and FPS; then play waves 1 to 5 normally.

### 24 Leaderboard and name entry
**Owner:** Programmer 3. **Date:** 21 Oct. **Depends on:** 22.

- `Leaderboard` load/save (`leaderboard.txt`), `NameEntry` on the game-over screen and after the ending, `LeaderboardScene`.
- Score formula from `game-design.md` (wave clear, no-damage bonus, deposit points, victory bonus).

**Done when:** scores persist across game restarts and rank correctly.
**Test:** enter 3 runs per mode with different scores; quit the game; relaunch; order is correct. Delete the file and relaunch; the game still works.

### 25 Credits scene
**Owner:** Programmer 3. **Date:** 21 Oct. **Depends on:** 03.

- `CreditsScene` with team, tools, AI disclosure and asset licenses matching `assets/ASSETS.md`.

**Done when:** the Credits button opens the scene and Back returns.
**Test:** read it through; check against `ASSETS.md`.

---

## Phase 5: Content and Polish

### 26 Asset and audio integration
**Owner:** Artist with Programmer 3. **Date:** 22 Oct. **Depends on:** A2 to A9.

- All new sprites, backgrounds, UI images, cutscene images, music and SFX in place; every `replace` row in `ASSETS.md` resolved.
- Music per state: menu, waves, boss, dock (optional), cutscenes.

**Done when:** `ASSETS.md` has no `replace` or `unknown` rows.
**Test:** play intro, waves 1 to 5 including the Hoarder, and the dock; listen for missing sounds and look for old art.

### 27 Tutorial prompts
**Owner:** Programmer 3. **Date:** 22 Oct. **Depends on:** 11, 12, 13.

- The 5 wave-1 prompts from `game-design.md`, replacing the WASD/E animation sequence.

**Done when:** a first-time player finishes wave 1 and docks without help.
**Test:** hand the game to someone outside the team; do not speak; note where they hesitate.

### 28 Balance and performance pass
**Owner:** Lead. **Date:** 22 Oct.

**14 Oct user-requested early performance work:** replace the brute-force collision searches after baseline profiling, preserve current hit semantics, and measure rendered capacity. This is a scoped performance subtask; balance runs and slowest-team-laptop validation remain pending. See `collision-performance.md` for reproducible measurements. Item 06 extraction and item 05 reset consolidation are still separate tasks.

- Two full Story runs and two Endless runs by different teammates. Adjust `// TUNE` values only.
- Performance: 80 enemies plus heavy scatter shots at 60 FPS on the slowest team laptop. If not, profile first; only then consider `SpatialGrid`.

**Done when:** a skilled player clears Story in 12 to 16 minutes; an average player reaches wave 5 to 7; 60 FPS holds.
**Test:** record results per run in `progress-tracker.md` Notes.

### 29 Feature freeze and release build
**Owner:** Lead. **Date:** 22 Oct, end of day.

- Release build with `GAME_DEBUG=OFF`, copied to the demo laptop, tested from a fresh copy.
- From here on, only bug fixes go into `main`.

**Done when:** the release build runs Story intro to ending and Endless to wave 10 on the demo laptop.
**Test:** exactly that, without debug tools.

---

## Phase 6: Submission

### 30 Gameplay demo video (3 to 5 min, .mp4)
**Owner:** Producer. **Date:** 23 Oct.

- Capture with OBS at 1920 x 1080, 60 FPS, from the release build.
- Structure: title (5 s), intro cutscene excerpt (20 s), wave 1 with tutorial (40 s), scrap and docking (40 s), dock shop upgrades (30 s), Compactor and waves 6 to 7 (40 s), The Hoarder fight (40 s), The Core excerpt and ending (30 s), Endless and leaderboard (20 s), theme statement (15 s).
- Voice-over or captions explaining mechanics and the climate and circular-economy link.

### 31 Trailer (1 to 2 min, .mp4)
**Owner:** Producer with Artist. **Date:** 23 Oct.

- Loopable: starts and ends on the title card. No dialogue required. Fast cuts, boss moments, the scrap-to-gear loop.

### 32 Forms and submission
**Owner:** Producer. **Date:** 24 Oct.

- Form 01 (roles), Form 02 (signed by all members and the coach), Form 03 (from the AI Usage Log and `ASSETS.md`), Template 01 (synopsis, 500 words max), trailer, gameplay video.
- Upload; save confirmation screenshots in the team drive.

**Done when:** submission confirmed by 24 October.

---

## Art and Audio Track (parallel, starts 14 Oct)

| Item | Content | Needed by | Unblocks |
|---|---|---|---|
| A1 | Style guide: palette (from `ui-rules.md`), shared prompt style line, pixel size rules, 3 test sprites | 15 Oct | A2 to A9 |
| A2 | Collector ship (accelerating 4 frames, idle 3 frames, 32 x 32, facing up), player bullet | 17 Oct | 15 |
| A3 | Junk Swarmer x3, Rogue Satellite, Compactor, each with destruct sheet | 18 Oct | 15, 16 |
| A4 | The Hoarder and The Core, plus destruct sheets and boss bullet | 19 Oct | 18, 19 |
| A5 | Debris and its destruct sheet, scrap pickups (3 sizes), dock, dock arrow | 18 Oct | 13, 15 |
| A6 | Four parallax background tiles (500 x 500), main menu background (5 x 2 frames of 900 x 512) | 20 Oct | 26 |
| A7 | Health bar frame and fill, any UI panel images | 20 Oct | 26 |
| A8 | Intro (7) and ending (4) cutscene images, 1920 x 1080 | 20 Oct | 20, 21 |
| A9 | Music: menu, waves, boss, cutscene; SFX: shoot, kill, scrap pickup, deposit, boss roar, windup, UI click | 21 Oct | 26 |

Every delivered file gets an `ASSETS.md` row the same day.

---

## Finals Backlog (after 25 October, before 26 November)

Not before submission. Order by expected judging impact:

1. Fix everything found in playtests of the submitted build
2. Settings screen (music and SFX volume, fullscreen toggle)
3. Third phase for The Hoarder; a mid-wave elite variant
4. Two or three new augments and one new gear line
5. Filipino voice lines for the dock announcer
6. Screen shake and hit-stop tuning, more particle effects
7. Booth mode: auto-return to the menu after 60 s idle, attract-mode demo loop
8. Spectator readability: larger boss telegraphs, kill feed

---

## Feature Count

| Phase | Items |
|---|---|
| 0 Foundation | 5 |
| 1 Core refactor | 5 |
| 2 Core loop | 4 |
| 3 Enemies and bosses | 5 |
| 4 Story, modes, meta | 6 |
| 5 Polish | 4 |
| 6 Submission | 3 |
| Art and audio | 9 |
