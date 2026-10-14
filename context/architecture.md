# Architecture

## Current debris harvesting extension (15 October)

`Asteroid`/`AsteroidManager` were renamed to `Debris`/`DebrisManager`, including source files, IDs, texture keys, collision observers, diagnostics, tests, and death labels. `DebrisKind` indexes ten entries; Theme owns fixed draw sizes, Balance owns fixed collision radii and yields. Circular collision search and deferred removal order remain unchanged.

On player destruction, DebrisManager calls Debris::destruct(true), which asks ScrapManager to create eight ScrapPickup entities using rectangles from the destroyed texture. Environmental removal passes false; offscreen despawn creates no burst. BarricadeEnemy::destruct removes its Animator entry and emits the same harvestable clump fragments; timeout/escape cleanup does not call destruct and awards nothing.

ScrapManager owns the complete breakup-to-homing lifecycle. No replacement particles are created at the phase boundary. Game calls update(dt, playerPosition) only when running and alive, after collisions; returned value increments Game::harvestedScrap exactly once on arrival. The user selected accumulation without a cargo cap. Credits, docking, cargo upgrades and ordinary enemy drops are deferred. The separate live-particle cap of 150 preserves earned value by merging overflow.

Game::resetRun now centralizes the shared manager/container resets, including ScrapManager and harvestedScrap, and is called by onSwitch/restartGame. Player, timer, tutorial and camera initialization remain in those callers; full item 05 cleanup remains pending. Scene exit, death and Game destruction also clear pickups. Per-frame collision snapshots are still cleared and rebuilt in their original phases.

Debug: `spawn debris all` places all ten variants around the player at a fixed 60-unit radius with zero translational velocity. It requires a living run, supports autocomplete, and is absent in release builds.

How the game is put together: the runtime loop, scenes, coordinate systems, game states, collisions, singletons and rendering. The first half describes the **current** Space Ablaze code accurately. The second half describes the **target** design this sprint builds toward. When the two differ, the build plan says which item changes what.

---

## Stack

| Layer | Choice | Notes |
|---|---|---|
| Language | C++20 (`CMAKE_CXX_STANDARD 20`) | The README says C++17; CMake says 20. CMake is authoritative |
| Framework | Raylib 5.5 | Fetched by CMake `FetchContent` if not installed |
| Math | `raymath.h` (ships with Raylib) | Vector2 helpers, Clamp, Lerp |
| Build | CMake 3.11+ | `file(GLOB_RECURSE SOURCES "src/*.cpp")`: new `.cpp` files in `src/` are picked up after re-running the configure step |
| Compilers | MinGW-w64 GCC, MSVC 2022, GCC/Clang | Windows is the demo platform |
| Shaders | GLSL 330 fragment shaders | `assets/shaders/shader.fs` (CRT), `barrel_distortion.fs` (border) |
| Persistence | Plain text file next to the executable | Leaderboard only |
| Third-party code | None besides Raylib | Adding a library requires a decision in `progress-tracker.md` |

---

## Folder Structure

The project keeps a **flat `src/` folder**. Moving files into subfolders would break every `#include "X.hpp"` and is not worth it during the sprint.

```
/
├── AGENTS.md, CLAUDE.md         # AI entry point
├── CMakeLists.txt
├── build.bat                    # Windows convenience: build and run
├── context/                     # These docs
├── assets/
│   ├── ASSETS.md                # Provenance for every asset (planned, item 02)
│   ├── fonts/                   # PerfectDOSVGA437.ttf, 3270-Regular.ttf
│   ├── shaders/                 # shader.fs, barrel_distortion.fs
│   ├── sounds/                  # SFX and music
│   └── textures/                # Sprite sheets, backgrounds, UI images
└── src/
    ├── main.cpp                 # Creates Application, calls Run()
    ├── Application.*            # Window, render pipeline, scene loop
    ├── Scene.hpp                # Abstract screen base
    ├── LoadingScreen.*, MainMenu.*, Game.*            # Existing scenes
    ├── Entity.hpp, Player.*, Enemy.*, LowLevelEnemy.*, MidLevelEnemy.*, Debris.*
    ├── EnemyManager.*, DebrisManager.*, BulletManager.*, Bullet.*
    ├── ResourceManager.*, Animator.*, Animation.*
    ├── Timer.* (Cooldown), GameTimer.*, KillCounter.*
    ├── Card.*, Button.*, DamageIndicator*.*, DamageOverlay.*, GameOverOverlay.*
    ├── ConfettiManager.*, ConfettiParticle.*, ExplosionConfetti*.*
    ├── Utils.*                  # gameCamera global, augment pool (being replaced)
    ├── SpatialGrid.*            # Exists, NOT used anywhere
    ├── CollisionSystem.*        # Empty files; filled in item 06
    └── Pause.*                  # Empty files; filled in item 07
```

Planned new files are listed in **Target Architecture** below and in `class-registry.md`.

---

## Runtime Overview

```
main()
 └─ Application()                         constructor
     ├─ InitWindow(1280x720, resizable), InitAudioDevice, SetTargetFPS(60)
     ├─ LoadRenderTexture(3840x2160)      the virtual canvas
     ├─ ResourceManager: LoadShaders, LoadFonts, LoadMusics, LoadSounds (synchronous)
     └─ m_sceneFactory = { "LoadingScreen", "MainMenu", "Game" }  (each scene constructed ONCE)
 └─ Application::Run()                    while (!WindowShouldClose())
     ├─ map mouse to virtual coordinates (SetMouseOffset / SetMouseScale)
     ├─ BeginTextureMode(m_target)
     │    next = scenes[current]->update()       returns the next scene's name
     │    if next != current: current->onExit(); next->onSwitch()
     │    scenes[current]->draw()
     ├─ CRT shader pass into targetFinal
     ├─ border texture + barrel-distortion pass into borderTargetFinal
     └─ BeginDrawing: draw both, letterboxed and scaled to the window; DrawFPS
```

Textures load on worker threads inside `LoadingScreen` (`ResourceManager::LoadTextures` decodes images on threads; `ProcessLoadedTextures` uploads them to the GPU on the main thread every frame until progress reaches 100%).

### Virtual resolution and mouse

- Everything draws into a **3840 x 2160** render texture (`GAME_SCREEN_WIDTH`, `GAME_SCREEN_HEIGHT`), which is then scaled to the window with letterboxing.
- `Application::Run` calls `SetMouseOffset` and `SetMouseScale` every frame, so **`GetMousePosition()` already returns virtual-canvas coordinates**. UI hit tests (`Button`, `Card`) compare against 3840 x 2160 rectangles directly.
- The window starts at 1280 x 720 and is resizable. Do not use `GetScreenWidth()` for layout; use the virtual constants.

### Render pipeline

1. Scene draws into `m_target` (3840 x 2160, cleared to black).
2. `m_target` is drawn through the CRT shader (`shader.fs`: curvature, chromatic offset, scanlines, vignette, `time` uniform) into `targetFinal`.
3. The `border` texture is drawn through the barrel-distortion shader into `borderTargetFinal`.
4. Both are drawn to the window. Render textures are flipped (negative source height) as usual in Raylib.

The CRT curvature crops and bends the outer edges. UI must stay inside the safe area defined in `ui-rules.md`.

---

## Scene System

```cpp
class Scene {
    virtual std::string update() = 0;   // returns the scene name to show next frame
    virtual void draw() = 0;
    virtual void onSwitch() = 0;        // called when this scene becomes active
    virtual void onExit() = 0;          // called when leaving
};
```

Rules that follow from how `Application` works:

- Scenes are created **once** at startup and reused. `onSwitch()` must fully reset the scene; the constructor runs only once.
- Returning an unknown name logs an error and falls back to `"MainMenu"`. `MainMenu` currently returns `"Settings"` and `"Credits"`, which do not exist.
- Scenes cannot pass data to each other through `update()`. The target design adds the `RunContext` singleton for this (selected mode, run seed, last run result).
- **Switching to `"Game"` resets the run** (`Game::onSwitch`). Never use a scene switch for the dock shop, pause or game over; those are `GameState`s inside `Game`.

Scene names (string keys): current `"LoadingScreen"`, `"MainMenu"`, `"Game"`. Planned: `"Intro"`, `"Ending"`, `"Leaderboard"`, `"Credits"`. Register each in `Application::Application()`.

---

## World Scale and Coordinates

There are two coordinate spaces. Mixing them is the most common bug.

| Space | Used inside | Units | Example |
|---|---|---|---|
| **Screen (virtual)** | After `EndMode2D()` in `draw()` | Virtual pixels, 3840 x 2160 | HUD, cards, buttons, overlays |
| **World** | Between `BeginMode2D(utils::gameCamera)` and `EndMode2D()` | World units | Player, enemies, bullets, scrap, dock |

The gameplay camera zoom is **20** (it starts at 150 and eases down to 20 at the start of a run). One world unit is 20 virtual pixels, so the visible area is about **192 x 108 world units** (96 x 54 from the center to the edges).

| Quantity | Current value (world units) | Where |
|---|---|---|
| Player sprite | 8 x 8 (current collision radius 8, from `getHitbox().width`) | `Player::init`, `Game::CheckCollisions` |
| Low and mid enemy sprite | 15 x 15 (hitbox width ~4.3) | Enemy constructors |
| Debris draw size | 15, 25 or 30 | `Debris` (`size * 10`) |
| Bullet draw size | player 8 x 5, enemy 8 x 8 | `Bullet::draw` |
| Player speed | 50 units/s, acceleration 400 | `Player.cpp` defines |
| Player bullet speed | 200 units/s | `Bullet` default |
| Enemy spawn ring | 150 from the player (just off screen) | `EnemyManager::spawnEnemy` |
| Enemy despawn distance | 1000 from the player | `EnemyManager.cpp` |
| Bullet despawn distance | 150 from the player | `BulletManager.hpp` |
| Debris spawn and despawn | 150 from the player | `Debris.cpp`, `DebrisManager.cpp` |
| Damage number font | 4 units | `DamageIndicator` |

Convert between spaces with `GetScreenToWorld2D(screenPos, utils::gameCamera)` and `GetWorldToScreen2D(worldPos, utils::gameCamera)`. The off-screen dock arrow is drawn in screen space from the dock's world position converted with `GetWorldToScreen2D`.

`utils::gameCamera` (in `Utils.cpp`) is a global `Camera2D`. `Player::update` uses it to convert the mouse to a world position for aiming.

---

## Current Game Loop (Space Ablaze)

P1 equipment extension (14 October): Player owns typed weapon/engine/shield selections, fire/skill/shield/animation timers and short-lived blast visuals. Player update produces typed Bullet values or a count of due laser ticks. Game::resolveEquipmentAttacks runs after bullet movement and before the legacy collision snapshots: swept circle tests select projectile contacts in travel order; laser capsules and rocket circles gather targets before removal. Existing score, kill, damage indicator and destruction paths handle results. No progression/unlock system is added. Legacy/enemy bullets retain their existing manager API; enemy bullets can be intercepted by directional shields before hull collision.

The modular player draws directly in a fixed effect/engine/hull/weapon/shield order, avoiding unordered Animator layer ordering. Textures remain ResourceManager-owned. Shots capture damage and pierced target IDs on creation; changing weapons cannot retune shots already in flight. Player::init clears equipment state/effects and both Game reset paths already call it. The player shooting sound now loads once through ResourceManager instead of leaking ten loads per restart.

Debug commands: `player` lists syntax. `player <default|gunner|cannon|laser|rockets|heavy> build` selects presets. `player weapon <cannon|laser|rockets|heavy>`, `player engine <base|pulse|burst|supercharged>`, and `player shield <none|front|sides|round|invincibility>` mix components. Tab completes every argument; invalid/extra arguments are rejected without changes. Commands require a live run and do not revive dead players. All command registration remains under GAME_DEBUG.

P2 console dropdown: at most six suggestions appear vertically under the input, with a visible range/count and highlighted selection. Up/Down scrolls through candidates; PageUp/PageDown skips rows; Tab/Enter fills a selected candidate without executing it. Enter with no selection executes. Ctrl+Up/Down recalls history; empty input also supports plain-arrow history. Selection and scroll reset when editing/executing/resetting. The existing input-capture contract still prevents clicks/keys reaching gameplay on opening/closing frames.

P2 spawn follow-up: `spawn lowlevel enemy <quantity>` parses a whole integer from 1 to Balance::ENEMY_LIMIT (10,000); malformed/trailing tokens, overflow, no active run or a dead player produce feedback without spawning. EnemyManager::spawnLowEnemies returns the number actually added, clamped to remaining capacity. Enemies are real LowLevelEnemy instances evenly spaced around the existing 150-unit ring centered on the player's current position, with normal health, animation IDs, movement, separation and combat. The console keeps simulation paused until closed. The batch method and command are debug-only; the normal ID counter and existing reset paths handle cleanup.

`Game::update()` switches on `GameState`:

| State | What happens |
|---|---|
| `GAME_RUNNING` | Every 20 s of game time, show 3 augment cards. Ease camera zoom. Update player, bullets, damage numbers, confetti, damage overlay. Camera follows the player with velocity lead. Bullet collisions. Debris update. Enemies update and spawn. Entity collisions. Kill counter update |
| `GAME_AUGMENT_SELECTION` | Game timer paused. Cards animate; the clicked card's **title string** decides which `Player::increase*()` runs |
| `GAME_PAUSED` | Toggled with P. Nothing updates; no pause UI is drawn |
| `GAME_OVER` | Explosion confetti, overlay slide-in, game-over text animation, Restart and Main Menu buttons |

Spawning (`EnemyManager::update`) is a **continuous trickle**, not waves: the spawn cooldown shrinks from 1.25 s to 0.025 s over 250 s, 1 to 3 enemies per spawn, and mid-level enemies appear after 150 s with a chance rising toward 40%. Debris follow a similar ramp.

P3 adds a separate Game-owned `BarricadeEvent` alongside that trickle. It requests a complete set of `BarricadeEnemy` instances from EnemyManager, records their IDs and runs once at 2:00 (or via `spawn barricade event` in F5). On running frames: event scheduling/time and camera zoom, player/weapon simulation, normal enemy movement, relative swept barricade contact, distant/offscreen escape cleanup, then ordinary entity collisions. Barricades participate in all player weapon damage paths but skip ordinary enemy contact/debris removal and low-only crowd separation. Player contact correction is independent of vulnerability, so iframes cannot bypass solid segments. The existing augment transition now exits the running branch immediately, freezing event and player simulation on that transition frame too.

Each segment advances its shrink/scatter clock with the same simulation delta as its coordinator. Pause/console/augment paths advance neither. Event expiry removes only tracked IDs and animations; no rewards or destruction effects on despawn. Restart/entry reset the event before manager IDs are reused; scene exit and death clear it and restore camera behavior. This is a scoped event prototype, not the planned WaveDirector or full run-reset refactor.

### Current collision matrix

P2 crowd pass (14 October): after enemy movement/despawning and before entity combat collisions, EnemyManager builds a separate SpatialGrid snapshot containing living low-level enemies only. Each query considers summed soft-body radii with a strict per-cell visit budget. Immutable frame positions avoid sequential update bias; deterministic opposing pair directions resolve exact overlaps and a small lateral component breaks collinear queues. Exponential response and a speed cap turn corrections into gradual pushes. Memory is reused; resets clear the grid and observers. Mid-level enemies do not enter this grid and retain their existing flight. Their live/destruction Animator registrations use FLYING, rendered in a second linear pass above WORLD without sorting or extra Update calls. See `crowd-performance.md` for measured costs. This intentionally changes low-enemy contact positions, superseding the earlier movement-parity promise for this scoped feature; combat search predicates remain unchanged.

All checks retain the inclusive circle-versus-point predicate `Vector2Distance(a, b) <= radius`. Bullets are points. The supplied radius is usually the target's size value (`hitbox.width` for ships, `getDebrisSize()` for debris); debris-versus-debris checks use the **outer/source debris's** radius, not summed radii. At the user's request on 14 October, `Game::update` now uses reusable `SpatialGrid` snapshots for repeated enemy/debris searches. Single-player checks remain linear. `CollisionSystem` extraction remains item 06.

The grid returns the lowest insertion index that passes the original predicate, preserving each manager's first-match iteration order. It is rebuilt before bullet collisions, then the debris index is rebuilt after debris/enemy movement and spawning. Bullet-phase kills deactivate indexed targets immediately, before the next bullet. Entity-phase removals remain deferred, including debris already marked by an enemy/player collision; only debris-pair matches deactivate during pair matching. This distinction preserves multiple enemies hitting the same debris in one frame. Both existing run-reset paths clear the indices and observers. See `collision-performance.md` for parity tests and rendered benchmarks.

| A | B | Result |
|---|---|---|
| Player bullet | Enemy | Random damage 7 to 12, optional knockback, damage number, pierce count decreases; on kill: score (low 10, mid 50), kill counter, sound, enemy removed |
| Player bullet | Debris | Debris removed, score 5 (only if the bullet did not hit an enemy this frame) |
| Enemy bullet | Player | 10 damage if player is in `PLAYER_DEFAULT`; bullet removed |
| Enemy bullet | Debris | Both removed |
| Enemy | Player | 10 damage; **the enemy is removed** (kamikaze) |
| Enemy | Debris | Both removed |
| Player | Debris | 10 damage; debris removed |
| Debris | Debris | Both removed |

`Player::takeDamage` always subtracts 10, stuns for 0.2 s, then gives invincibility frames (0.8 s, flashing red). The health bar assumes a maximum of 100.

---

## Target Architecture

### New and changed classes (summary)

| Class | Kind | Replaces or extends |
|---|---|---|
| `Config.hpp` | constants | Duplicated `#define`s (`GAME_SCREEN_WIDTH` is defined in `Scene.hpp`, `Player.cpp` and `Application.cpp`) |
| `Theme.hpp` | constants | Inline colors and font sizes |
| `Balance.hpp` | constants | Inline gameplay numbers |
| `RunContext` | singleton | Data passed between scenes: mode, seed, last result |
| `RunRng` | value class | Seeded `std::mt19937` for wave composition |
| `WaveDirector` | class owned by `Game` | The time-based spawn ramp in `EnemyManager::update` |
| `CollisionSystem` | class owned by `Game` | Collision loops inside `Game::update` |
| `HUD` | class owned by `Game` | HUD drawing inside `Game::draw` |
| `PlayerStats` | struct inside `Player` | Loose stat fields; adds max HP, armor, magnet, cargo |
| `Augment` | enum + table + `applyAugment()` | `utils::augmentPool` and the string if-chain |
| `GearUpgrade`, `UpgradeShop` | data + logic | New |
| `DockShopUI` | UI class owned by `Game` | New |
| `ScrapPickup`, `ScrapManager` | entity + singleton | New |
| `Dock` | entity owned by `Game` | New |
| `HighLevelEnemy` | `Enemy` subclass | New (the `HIGH_LEVEL_ENEMY` enum value already exists) |
| `Boss`, `HoarderBoss`, `CoreBoss` | `Enemy` subclasses | New (`BOSS_LEVEL_ENEMY` enum value already exists) |
| `Cutscene`, `IntroCutscene`, `EndingCutscene` | `Scene` subclasses | New |
| `Leaderboard`, `LeaderboardScene`, `NameEntry` | data + scene + UI | New |
| `CreditsScene` | `Scene` | New |
| `PauseOverlay` | UI class | Fills the empty `Pause.*` files |
| `DebugTools` | class owned by `Game` | New, debug builds only |

### Game states (target)

`GameState` gains two values. Only `Game` changes `gameState`.

```
                    ┌──────────────────── P / Esc ───────────────────┐
                    v                                                 │
              GAME_PAUSED ─── resume ──> (previous state)             │
                                                                      │
 onSwitch ──> GAME_RUNNING ──(wave cleared)──> GAME_AUGMENT_SELECTION │
                 ^   │                               │ card picked    │
                 │   │                               v                │
                 │   │                    GAME_RUNNING (return phase) ┘
                 │   │                               │ player enters dock radius
                 │   │                               v
                 │   │                          GAME_DOCKED  (shop; launch button)
                 │   │                               │ launch
                 │   └───────────────────────────────┘ next wave
                 │
                 ├──(player HP <= 0)──> GAME_OVER ──> restart (resetRun) / main menu
                 └──(story final boss dead)──> GAME_VICTORY ──(3 s)──> scene "Ending"
```

### Wave phases (owned by `WaveDirector`)

`GAME_RUNNING` covers several wave phases. `Game` asks `WaveDirector` for the phase and reacts.

| Phase | Spawning | Ends when | Then |
|---|---|---|---|
| `WAVE_LAUNCH` | None. Banner "WAVE N" for 2.5 s | Timer ends | `WAVE_ACTIVE` or `WAVE_BOSS` |
| `WAVE_ACTIVE` | Spends the wave's point budget in groups at a fixed interval, respecting the alive cap | Budget spent and all wave enemies dead | `WAVE_CLEARED` |
| `WAVE_BOSS` | Spawns the boss once; the boss may spawn adds | Boss dead | `WAVE_CLEARED` (or victory if it was the final boss in Story) |
| `WAVE_CLEARED` | None | Same frame | `Game` enters `GAME_AUGMENT_SELECTION` |
| `WAVE_RETURN` | None (debris may still drift) | Player is inside the dock radius | `Game` enters `GAME_DOCKED` |

Run start: the player spawns at the dock and the director starts at wave 1, `WAVE_LAUNCH`. The first dock visit happens after wave 1.

### Frame order inside `Game::update` (target, `GAME_RUNNING`)

1. Debug keys (debug builds only)
2. Camera zoom ease
3. `player.update()`
4. `waveDirector.update(dt, player)` — may spawn enemies
5. `EnemyManager::update(playerPos)` — movement and firing only, no spawning
6. `DebrisManager::update(...)`, `BulletManager::update(...)`, `ScrapManager::update(playerPos, magnetRadius)`
7. `CollisionSystem::run(...)` returns a `CollisionReport` (kills, scrap collected, damage taken, player died, killer info)
8. `Game` applies the report: score, kill counter, sounds, game over or boss-dead transitions
9. Wave phase reactions: augment selection on clear, docking check during `WAVE_RETURN`
10. Effects updates (damage numbers, overlays), camera follow, `HUD::update`

### Frame order inside `Game::draw` (target)

```
BeginMode2D(utils::gameCamera)
  parallax background
  dock
  scrap pickups
  debris (debris)
  bullets
  Animator::Update() then Animator::Draw()   // ships, enemies, bosses, explosions (ONE update per frame)
  damage numbers, world-space telegraphs (boss rings), explosion confetti
  debug overlay (hitboxes) when `hitbox on` is enabled
EndMode2D()
HUD (health, cargo, credits, wave, timer, boss bar, dock arrow, tutorial prompts)
State overlays: augment cards | dock shop | pause | game over | victory fade
```

`Animator::Draw()` iterates an `unordered_map`, so the order **between** animated objects is undefined. If a boss must draw above enemies, draw its sprite directly in `Boss::draw()` instead of registering it with the Animator, or add a layer field to the Animator (decision recorded in `progress-tracker.md`).

### Collision matrix (target additions)

| A | B | Result |
|---|---|---|
| Player | Scrap pickup | Added to cargo if there is room; pickup removed |
| Player | Dock (during `WAVE_RETURN` only) | `GAME_DOCKED` |
| Enemy (non-boss) | Player | Player takes the enemy's `contactDamage`; enemy removed (kept from Space Ablaze) |
| Boss | Player | Player takes the boss's `contactDamage` and is knocked back; **the boss is not removed** |
| Player bullet | Boss | Damage; no knockback on bosses |
| Any enemy killed | | `ScrapManager::spawnScrap(position, scrapValue)` |
| Debris killed by the player | | Small scrap drop |

`Player::takeDamage` gains an `amount` parameter. Armor upgrades reduce it; the minimum is 1.

### Run reset protocol

`Game::onSwitch()` and `Game::restartGame()` currently repeat the same reset list. The target design has one function:

```cpp
void Game::resetRun();   // called by onSwitch() and restart
```

It resets, in order: every run singleton (`EnemyManager`, `DebrisManager`, `BulletManager`, `ScrapManager`, `DamageIndicatorManager`, `ConfettiManager`, `ExplosionConfettiManager`, `GameOverOverlay`, `DamageOverlay`), the `Animator` run animations, `player.init()`, `waveDirector.reset(seed, mode)`, `UpgradeShop` levels, credits, cargo, kill counter, game timer, camera. **Any new singleton holding run state must be added here.**

### Dependency rules

| Code | May use | Must not use |
|---|---|---|
| Entities (`Player`, `Enemy` and subclasses, `Debris`, `ScrapPickup`, `Dock`) | `ResourceManager`, `Animator`, `BulletManager` (to fire), `Timer`, `Config`/`Balance`/`Theme`, `utils::gameCamera` | `Game`, scenes, `HUD`, other managers' internals |
| Managers (`EnemyManager`, `ScrapManager`, ...) | Their entity classes, `ResourceManager`, `Animator` | `Game`, `HUD` |
| `WaveDirector` | `EnemyManager` spawn API, `RunRng`, `Balance` | Drawing, sounds, `GameState` |
| `CollisionSystem` | Managers, `Player`, `Dock` | Sounds, UI, `GameState` (it reports; `Game` decides) |
| `HUD`, `DockShopUI`, `PauseOverlay` | Read-only access to `Player`, `WaveDirector`, run data; `Theme` | Mutating gameplay state (the shop calls `UpgradeShop`, which mutates) |
| `Game` | Everything above | Other scenes' internals |
| Scenes | `RunContext`, their own UI | Each other |

### Randomness and fairness

- Wave composition, spawn angles and boss attack choices use `RunRng`, seeded from `RunContext` at run start (fixed seed per mode, in `Balance.hpp`). Two players see the same waves.
- Visual randomness (confetti, damage-number jitter, enemy sprite variant) may keep using Raylib's `GetRandomValue`, because it does not affect fairness.
- The current augment code uses `rand()`; the target uses `RunRng`, so augment offers are also deterministic per seed. Record the decision if the team prefers random offers.

### Persistence

`Leaderboard` reads and writes `leaderboard.txt` next to the executable, one entry per line:

```
mode,name,score,waves,seconds
story,DANDEE,48210,10,812
endless,ANNE,63150,17,1104
```

Names are 3 to 12 characters, A-Z, 0-9 and space only (no commas). The file is created on first save. A missing or malformed line is skipped with a `TraceLog(LOG_WARNING, ...)`. Keep the top 10 per mode.

### Debug tools (debug builds only)

Compiled only with `-DGAME_DEBUG=ON`. The existing `DebugTools` remains owned by the long-lived `Game` scene. `Application::Run()` calls `Game::updateDebugConsole(activeGame)` before scene updates and `drawDebugConsole()` after scene drawing, so the same terminal and audio preference work on the menu and during runs. Gameplay commands receive no player outside the active Game scene.

F5 toggles a translucent console at the top left, inside the CRT safe area. Enter runs the typed command, Tab completes command names and arguments (or their common prefix), Up/Down navigates command history and restores a draft, Backspace edits, and Escape closes. The console shows matching completions and recent results. Commands are looked up in one metadata table and dispatched by enum. Input/history/output are bounded by `Config`.

| Command | Action |
|---|---|
| `help` | Show commands and controls |
| `hitbox [on/off/toggle]` | Collision outlines, IDs and weapon geometry only |
| `stats [on/off/toggle]` | FPS, HP, GameState, entity/bullet counts, audio/invincibility, plus event phase, time remaining, living segments, radius, orbit speed and automatic-trigger state |
| `mute [on/off/toggle]` | All music and effects, in every scene; restore previous volume when unmuting |
| `invincible [on/off/toggle]` | Block player damage and its side effects; does not revive a dead run |
| `spawn lowlevel enemy <quantity>` | Spawn real low enemies; integer 1–10,000, clamped to capacity |
| `spawn barricade event` | Start a durable shrinking ring event around the living player; rejects duplicate active events |
| `credits` | Pending scrap/cargo system (item 12); later add credits and fill cargo |
| `boss` | Pending boss system (item 17); later skip to next boss wave |
| `wave` | Pending wave system (item 11); later advance one wave |
| `clear` | Clear console output |
| `close` | Close the console |

Omitting a toggle argument toggles the current value. Gameplay commands require an active run. Old F1/F2/F3/F4/F6 actions are removed; F5 now controls only the console.

Console focus captures opening, open and closing frames. Main-menu updates are suspended while its music stream continues; loading continues normally. `Game::update()` keeps music streaming but skips gameplay and controls, pausing only a previously running game timer. Closing resumes that timer without changing `GameState`; an existing pause, augment selection or game over stays in place. Existing animation rendering and wall-clock cooldown semantics remain unchanged.

New runs and restarts reset console input/history/output, visibility, hitboxes and the timer-resume flag. `Player::init()` resets invincibility. Master mute and its saved volume persist as a session preference. Consolidate these resets into `Game::resetRun()` in item 05. Wave phase/budget and magnet radius remain unavailable until their systems exist.

The CMake option defaults to OFF. `build.bat` enables it for local development. `-DGAME_DEBUG=OFF` removes console input/rendering, invincibility state, diagnostics and the window FPS counter from the submitted build.

P1 default restoration: the original default draws its existing acceleration/idle sheets directly at the original size and frame duration and fires legacy bullets from the ship center. Gunner retains the previously added modular baseline. Every preset selects SHIELD_NONE, clearing shield charge, recharge delay and active guard/cooldown state. Shields are independent equipment for explicit debug testing and future skill integration. Selecting an individual component while on Default enters the modular equipment system; setting an engine or shield supplies its cannon baseline. Default/new-run/reset cancels pending beam and burst state.
