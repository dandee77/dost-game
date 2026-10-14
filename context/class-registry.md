# Class Registry

Living document. It replaces the web project's UI registry: instead of components, it lists every **class**, what it owns, who owns it, its public API and its traps. Read it before creating or changing any class.

Item 01 baseline import (14 October 2026): Debris, Button, GameTimer, MainMenu and Player use standard C++ brace initialization instead of C-style compound literals so MSVC can compile them. Public APIs, ownership and gameplay behavior are unchanged.

Before creating a class:

1. Search this file for the **job** the class would do, not only its name.
2. If a class already does it, use it, extend it with a method, or derive from it.
3. If it is listed under **Planned**, build it at the listed files with the listed API.
4. If it is in neither, add a Planned entry here first, then build it.

After creating or changing a class:

1. Set its **Status**.
2. Update **Public API** to match the header exactly.
3. Add new traps under **Gotchas**.
4. Note the build-plan item in **Changed by**.

### Status values

| Status | Meaning |
|---|---|
| `existing` | From Space Ablaze, unchanged |
| `modified` | From Space Ablaze, changed this sprint |
| `planned` | Not written yet; API here is the contract |
| `built` | New this sprint, done |
| `remove` | To be deleted (files empty or unused) |

### Entry format

```
### ClassName
- Files: src/ClassName.hpp, src/ClassName.cpp
- Status: existing | modified | planned | built | remove
- Kind: abstract base | derived | singleton | scene | entity | value | UI | data
- Inherits: Base (or none)
- Owned by: who creates and destroys it
- Public API: the methods others call
- Uses: classes it depends on
- Used by: classes that depend on it
- Gotchas: traps
- Changed by: build-plan items
```

---

## Inheritance Map

```
Scene (abstract)
├── LoadingScreen                       existing
├── MainMenu                            existing → modified (22)
├── Game                                existing → modified (most items)
├── Cutscene (abstract)                 planned (20)
│   ├── IntroCutscene                   planned (20)
│   └── EndingCutscene                  planned (21)
├── LeaderboardScene                    planned (24)
└── CreditsScene                        planned (25)

Entity (abstract)
├── Player                              existing → modified (08)
├── Debris                            existing → modified (15, reskinned as debris)
├── Enemy (abstract)                    existing → modified (10)
│   ├── LowLevelEnemy                   existing (homing swarmer)
│   ├── MidLevelEnemy                   existing (strafing shooter)
│   ├── HighLevelEnemy                  planned (16, charging tank)
│   └── Boss (abstract)                 planned (17)
│       ├── HoarderBoss                 planned (18)
│       └── CoreBoss                    planned (19)
├── ScrapPickup                         planned (12)
└── Dock                                planned (13)
```

## Singletons

All use the same pattern: `static X& GetInstance()` with a function-local static and a private constructor.

| Singleton | Holds run state? | Must be reset in `Game::resetRun()` |
|---|---|---|
| `ResourceManager` | No (assets) | No |
| `Animator` | Yes (animations keyed by ID) | Yes: `StopAll()` plus removal of run animations |
| `EnemyManager` | Yes | Yes |
| `BulletManager` | Yes | Yes |
| `DebrisManager` | Yes | Yes |
| `DamageIndicatorManager` | Yes | Yes |
| `DamageOverlay` | Yes | Yes |
| `GameOverOverlay` | Yes | Yes |
| `ConfettiManager` | Yes | Yes |
| `ExplosionConfettiManager` | Yes | Yes |
| `ScrapManager` (planned) | Yes | Yes |
| `RunContext` (planned) | Cross-scene data | No (set by menus, read by `Game`) |

---

## Application and Scenes

### Application
- Files: src/Application.hpp, src/Application.cpp
- Status: modified (item 04)
- Kind: value (one instance in `main`)
- Owned by: `main()`
- Public API: `Application()`, `void Run()`, `~Application()`
- Uses: `ResourceManager`, all scenes, shaders `"shader"` and `"barrel_distortion"`, texture `"border"`
- Gotchas:
  - Creates every scene once in `m_sceneFactory` (a `std::map<std::string, std::shared_ptr<Scene>>`). New scenes must be added there.
  - Defines its own `screenWidth = 3840`, `screenHeight = 2160` constants; replace with `Config.hpp` in item 03.
  - Calls `DrawFPS` on the real window (outside the CRT pass) only with `GAME_DEBUG`; coordinates come from `Theme`.
  - Routes the long-lived Game scene's debug console before scene updates and draws it after the scene. While captured, main-menu controls stop but menu music continues. DebugTools stores the session mute preference; Application's public API is unchanged.
  - `SetExitKey(KEY_NULL)`: Esc does not close the window, so Esc is free for pause.
- Changed by: 04; planned: 03, 20, 24, 25

### Scene
- Files: src/Scene.hpp
- Status: existing
- Kind: abstract base
- Public API: `virtual std::string update() = 0`, `virtual void draw() = 0`, `virtual void onSwitch() = 0`, `virtual void onExit() = 0`, virtual destructor
- Gotchas: also `#define`s `GAME_SCREEN_WIDTH 3840` and `GAME_SCREEN_HEIGHT 2160`. Many files get these constants through `Scene.hpp`. Item 03 moves them to `Config.hpp` and makes `Scene.hpp` include `Config.hpp` so existing includes keep working.

### LoadingScreen
- P1: after decoded progress reaches 100%, drains pending GPU uploads again before leaving, preventing final worker textures from missing in the first gameplay scene.
- Files: src/LoadingScreen.hpp, src/LoadingScreen.cpp
- Status: existing
- Kind: scene (`"LoadingScreen"`)
- Behavior: constructor starts `ResourceManager::LoadTextures()`. `update()` calls `ProcessLoadedTextures()` and returns `"MainMenu"` at 100%. Draws "Loading progress: N%" with the default Raylib font.
- Changed by: 20 (returns `"Intro"` instead of `"MainMenu"`)

### MainMenu
- Files: src/MainMenu.hpp, src/MainMenu.cpp
- Status: existing
- Kind: scene (`"MainMenu"`)
- Behavior: animated background (`"main_menu_background"`, 5 x 2 frames) through the Animator under ID `"background"`, four `Button`s (Play, Settings, Credits, Exit), title text "SPACE / ABLAZE", footer "Equity Quest - 2024", home music. Exit plays a full-screen `"exit_animation"` then calls `exit(0)`.
- Gotchas:
  - Returns `"Settings"` and `"Credits"`, which do not exist yet (falls back to MainMenu with an error log).
  - Calls `Animator::Update()` inside `draw()`.
  - `Animator::IsCompleted("exit")` dereferences a missing entry after the Animator erases the completed animation. See `library-docs.md` Known Pitfalls.
  - The title and footer text are Space Ablaze branding; replace in item 22.
- Changed by: 22

### Game
- P4: `resetRun()` now centralizes run-container resets (including ScrapManager) and clears the run-local `harvestedScrap` counter; both entry/restart call it. Running/alive simulation consumes ScrapManager collection results and displays SCRAP in the safe-area HUD. Death/exit/destruction clear pickups. Full player/timer/camera reset consolidation remains item 05.
- P3: owns `BarricadeEvent barricadeEvent`; updates it only during running simulation and resolves wall contact after enemy movement. Private camera/contact helpers restore zoom and route lethal contact to normal game over. Reset event before manager resets, and on exit/death/destruction. Debug console receives the event owner only in an active run.
- P1: private `resolveEquipmentAttacks()`, `damageEquipmentEnemy(const std::string&, int, Vector2, float)`, `destroyEquipmentDebris(const std::string&)`, `detonateRocket(Vector2, int, float)` integrate swept projectiles, beam ticks, splash, score and destruction before legacy snapshots. No public API change. Player draws its own layers and equipment HUD; shield interception precedes legacy enemy-bullet hull collisions.
- Files: src/Game.hpp, src/Game.cpp
- Status: existing → modified in most items
- Kind: scene (`"Game"`), the gameplay orchestrator
- Owns (current): `Player playerEntity`, `KillCounter killCounter`, `GameTimer gameTimer`, `std::vector<Card> augmentCards`, `std::vector<BackgroundLayer> backgroundLayers` (4 parallax layers), `Music gameMusic`, `Button* restartButton`, `Button* mainMenuButton` (raw `new`), `std::array<Sound, 10> scoreSounds`, `DeathInfo deathInfo`, `GameState gameState`
- Owns (target): adds `WaveDirector`, `CollisionSystem`, `HUD`, `Dock`, `UpgradeShop`, `DockShopUI`, `PauseOverlay`, `DebugTools`, run economy (credits, cargo)
- Item 04: owns `DebugTools debugTools` only with `GAME_DEBUG`. Application routes console input before scene updates; Game skips controls and simulation while captured. Draws hitboxes after world sprites and diagnostics after the state UI. Both `onSwitch()` and `restartGame()` reset the tools.
- Item 28 early performance subtask: owns `SpatialGrid enemyCollisionGrid`, `debrisCollisionGrid`, and reusable non-owning `collisionEnemies` / `collisionDebris` vectors. Snapshots use manager iteration order. Bullet snapshots precede movement; debris snapshots are rebuilt after movement/spawning. Both current reset paths clear them; consolidate in item 05. Public API unchanged.
- Public API: `update()`, `draw()`, `onSwitch()`, `onExit()` (Scene overrides). Private: `restartGame()`, `DrawParallaxBackground()`, `DrawLayer()`
- Debug-only API: `bool updateDebugConsole(bool activeGame)`, `void drawDebugConsole() const`. Game owns DebugTools; `debugPausedTimer` remembers whether console capture paused the run timer, without changing GameState. Both reset paths clear it.
- Enums in `Game.hpp`: `GameState : int { GAME_RUNNING, GAME_AUGMENT_SELECTION, GAME_PAUSED, GAME_OVER }` (explicit underlying type permits the debug header's forward declaration; target adds `GAME_DOCKED`, `GAME_VICTORY`), `KillerType { KILLER_ENEMY_BULLET, KILLER_ENEMY_COLLISION, KILLER_DEBRIS }`, struct `DeathInfo`
- Gotchas:
  - File-level statics `prevGameTimer` and `gameOverTextStarted` survive between runs; `prevGameTimer` is never reset. Move them into the class during item 05.
  - `onSwitch()` loads 10 copies of `score_sound.wav` with `LoadSound` every time the scene starts and never unloads them (leak). Use `LoadSoundAlias` (item 05).
  - In `GAME_OVER`, `update()` calls `Animator::Update()` and `draw()` calls it again, so animations run at double speed. Fix in item 05.
  - The augment trigger is `(int)elapsed % 20 == 0`, tied to game time; replaced by wave clears in item 11.
  - The health bar width is `1000 * health / 100`; it breaks once max HP can change (item 08).
- Changed by: 03 to 14, 17, 19, 22, 23, 24, 27

### Cutscene (planned)
- Files: src/Cutscene.hpp, src/Cutscene.cpp
- Status: planned (item 20)
- Kind: abstract base, derives from `Scene`
- Public API:
  ```cpp
  struct CutsceneSlide {
      std::string textureKey;   // ResourceManager key; empty = black background
      std::string text;         // up to 3 lines, '\n' separated
      float duration;           // seconds before auto-advance
  };
  class Cutscene : public Scene {
  public:
      std::string update() override;   // advances, handles skip; returns nextScene() when done
      void draw() override;            // slide image with slow zoom, typewriter text, skip hint
      void onSwitch() override;        // slides = buildSlides(); index = 0; play music
      void onExit() override;
  protected:
      virtual std::vector<CutsceneSlide> buildSlides() const = 0;
      virtual std::string nextScene() const = 0;
      virtual std::string musicKey() const = 0;
  };
  ```
- Behavior: Space, Enter or left click finishes the typewriter, a second press advances. Esc skips the whole cutscene. Text uses `Theme` cutscene type sizes, inside the safe area.

### IntroCutscene (planned)
- Files: src/IntroCutscene.hpp, src/IntroCutscene.cpp
- Status: planned (item 20)
- Kind: derived from `Cutscene`, scene `"Intro"`
- Behavior: the 7 intro slides from `project-overview.md`. `nextScene()` returns `"MainMenu"`. Shown once per launch: `LoadingScreen` returns `"Intro"`; the menu never returns to it.

### EndingCutscene (planned)
- Files: src/EndingCutscene.hpp, src/EndingCutscene.cpp
- Status: planned (item 21)
- Kind: derived from `Cutscene`, scene `"Ending"`
- Behavior: ending slides; then shows run stats from `RunContext::lastResult`; `nextScene()` returns `"Leaderboard"` if the score qualifies, otherwise `"MainMenu"`.

### LeaderboardScene (planned)
- Files: src/LeaderboardScene.hpp, src/LeaderboardScene.cpp
- Status: planned (item 24)
- Kind: scene `"Leaderboard"`
- Behavior: two columns (Story, Endless), top 10 each from `Leaderboard`; highlights the latest entry from `RunContext`; Back button returns `"MainMenu"`.

### CreditsScene (planned)
- Files: src/CreditsScene.hpp, src/CreditsScene.cpp
- Status: planned (item 25)
- Kind: scene `"Credits"`
- Behavior: scrolling text: team, coach, tools (Raylib, compilers, AI tools used), AI disclosure summary, asset licenses (fonts). Content from a `constexpr` array in the `.cpp`, matching `assets/ASSETS.md`.

---

## Entities

### Entity
- Files: src/Entity.hpp
- Status: existing
- Kind: abstract base
- Protected fields: `int health`, `int damage`, `float speed`, `Rectangle rect`, `float rotation`, `Vector2 velocity`, `Vector2 position`, `Vector2 origin`
- Public API: `virtual void update() = 0`, `virtual void draw() = 0`, `getPosition()`, `getSize()` (rect width/height), `getRotation()`, `getVelocity()`, `getHealth()`
- Gotchas: no virtual `getRadius()`; collision radii are read from class-specific methods (`getHitbox().width`, `getDebrisSize()`). Item 10 adds `virtual float getCollisionRadius() const` with a default of `rect.width / 2`.

### Player
- P3: `resolveBarricadeContact(Vector2 correctedPosition, Vector2 normal, Vector2 source)` always corrects position/velocity for living players, but calls normal damage only in PLAYER_DEFAULT. Existing shields, debug invincibility, stun and iframe timers remain authoritative.
- Files: src/Player.hpp, src/Player.cpp
- Status: modified (P1 equipment prototypes, 14 October; PlayerStats refactor remains item 08)
- Kind: entity; inherits Entity; owned by Game as a value.
- Public API: `Player()`, `init()`, `update()`, `draw()`, `drawEquipmentStatus() const`, `getHitbox() const`, `takeDamage(float timeStateEntered, Vector2 entityPosition, float entitySize)`, `getPlayerState() const`, `addScore(int)`, `getScore() const`, `addDamageDealt(int)`, `getTotalDamageDealt() const`, `getRandomDamage() const`, `getMinDamage() const`, `getMaxDamage() const`, `getKnockbackPower() const`.
- Equipment API: `setBuild(PlayerBuild)`, `setWeapon(PlayerWeapon)`, `setEngine(PlayerEngine)`, `setShield(PlayerShield)`, `getWeapon() const`, `getEngine() const`, `getShield() const`, `getShieldCharge() const`, `tryBlockHit(Vector2 source)`, `shieldCovers(Vector2 source) const`, `isLaserActive() const`, `getLaserStart() const`, `getLaserEnd() const`, `consumeLaserTicks()`, `addBlast(Vector2 center)`, `drawAttackHitboxes() const`.
- Augment API (unchanged): `increasePlayerAttackSpeed()`, `increasePlayerHealth()`, `increasePlayerMovementSpeed()`, `increasePlayerIframeDuration()`, `increasePlayerRotationSpeed()`, `increaseTriggerHappyBurst()`, `increaseScatterShot()`, `increasePiercingRounds()`, `increaseInertiaImpact()`.
- Debug-only API: `setDebugInvincible(bool)`, `isDebugInvincible() const`.
- Enums: PlayerState (DEFAULT/STUNNED/IFRAME/DEAD); PlayerEngine (BASE/PULSE/BURST/SUPERCHARGED); PlayerShield (NONE/FRONT/SIDES/ROUND/INVINCIBILITY); PlayerBuild (DEFAULT/CANNON/LASER/ROCKETS/HEAVY/GUNNER). PlayerWeapon is declared before Bullet in Bullet.hpp.
- Owns: equipment selections, shield charge/recharge, boost/guard state, attack/burst/laser timers, ordered layer animation clocks, blast visual values. All cleared by init, called by both current Game reset paths.
- Behavior: WASD movement, mouse-facing attacks, LMB/E fire; Space activates equipped burst/guard abilities. Default is the original ship and original bullets; Gunner is the modular cannon/base/no-shield loadout. All presets clear shields and their timers; shields require explicit separate selection. Typed equipment dispatch; no progression/unlocks. Hull art reflects health. Direct ordered rendering replaces the old accelerating/deaccelerating Animator entries.
- Gotchas: current incoming damage remains 10 until item 08. Directional shields intercept bullets at radius 7.5 and protect contact damage by source direction. All new timers and player stun/iframes use simulation dt. `consumeLaserTicks()` clears pending ticks; Game consumes it once per update. Switching preserves health/augments and in-flight shots, but resets the replaced component's timers; presets disable auto-fire. Shooting sound is ResourceManager-owned, loaded once. `EquipmentTestAccess` is a friend solely for optional native fixtures.
- Changed by: 04, P1; planned: 03, 05, 08, 09, 12, 14.

### PlayerStats (planned)
- Files: inside src/Player.hpp
- Status: planned (item 08)
- Kind: data struct
- Fields: `int maxHealth`, `float damageMultiplier`, `float attackCooldown`, `float moveSpeed`, `float armor` (0 to 0.6 damage reduction), `float magnetRadius`, `int cargoCapacity`, `float iframeDuration`, `float rotationMultiplier`, `int burstCount`, `int scatterCount`, `int piercePower`, `float knockbackPower`
- Rule: base values come from `Balance.hpp`. Augments and gear upgrades modify `PlayerStats` only through `Player` methods, never by poking fields from outside.

### Debris
- Files: src/Debris.hpp/.cpp, src/DebrisKind.hpp
- Status: renamed from Asteroid and extended for the 15 October debris-harvesting request.
- Kind: Entity subclass, owned by DebrisManager as unique_ptr values keyed by unique debris IDs.
- Constructors: Debris(playerPos) chooses a variant; Debris(playerPos, DebrisKind) chooses a specific variant. Ten typed variants share behavior; no random scale.
- API: update(), draw(), getDebrisID(), getDebrisSize() (fixed collision radius from Balance), getKind(), getTextureKey(), getDisplayName(), destruct(bool harvestable = false).
- Draw dimensions come from Theme; collision radius and scrap yield come from Balance. Body remains centered within a 96 x 96 frame. Destruct queues the accepted complete eight-frame sheet; its final visible flecks are replaced by glowing orb pickups.
- IDs use a monotonic counter and are never reused. Collision circles are retained for all silhouettes. No new entity class per art variant.
### ScrapPickup
- Files: src/ScrapPickup.hpp/.cpp
- Status: implemented for debris harvesting (15 October); broader enemy-drop/cargo economy remains item 12.
- Kind: Entity subclass owned by ScrapManager through unique_ptr.
- API: advance(dt, target), update(), draw(), setAttractTarget(), isCollected(), isExpired(), getValue(), addValue(), getElapsed(). Constructor: ScrapPickup(worldPosition, value).
- Each pickup draws the generated scrap_orb texture, including its continuous alpha halo. It starts at a saved final-frame fleck centroid, holds 0.1 s, then homes at 90 units/s. No sprite cutting, scatter simulation or concentric-circle drawing. Swept arrival prevents overshoot; credit is emitted once.
- Orbs expire at 20 simulation seconds. Environmental explosions play without spawning pickups. Rendering changes no state and uses no Animator IDs.
### Dock (planned)
- Files: src/Dock.hpp, src/Dock.cpp
- Status: planned (item 13)
- Kind: entity
- Inherits: `Entity`
- Owned by: `Game` (value member)
- Public API: `Dock()`, `init()` (position = world origin), `update()` (slow rotation, beacon pulse when docking is allowed), `draw()`, `setDockingOpen(bool)`, `isDockingOpen()`, `getDockRadius()`, `contains(Vector2 point)`
- Gotchas: the dock is decorative during waves (no collision). Docking only works during `WAVE_RETURN`.

---

## Enemies

### Enemy
- P3: `canReceiveKnockback() const` is virtual; `getPreviousPosition() const` defaults to current position and is overridden for moving barricade sweeps. `BARRICADE_ENEMY` appended to EnemyType.
- Files: src/Enemy.hpp, src/Enemy.cpp
- Status: existing → modified (item 10)
- Kind: abstract base
- Inherits: `Entity`
- Owned by: `EnemyManager` (map `std::unordered_map<std::string, std::unique_ptr<Enemy>>`)
- Constructor: `Enemy(std::string enemyID, EnemyType type, Vector2 spawnPos, Vector2 playerPos)`
- Public API (current): `getPlayerPositionForEnemy(Vector2)` (a setter), `getEnemyType()`, `getHitbox()`, `getEnemyID()`, `virtual void destruct() = 0`, `takeDamage(int)`, `isDead()`, `applyKnockback(Vector2 direction, float force)`, `canReceiveKnockback()`
- P2: `applySeparation(Vector2 displacement)` updates position and rect/hitbox origins without changing velocity, steering, knockback or combat radius.
- Protected (current): `enemyID`, `enemyType`, `viewDirection`, `playerPosition`, `hitbox`, `speed`, `spriteSize`, `knockbackVelocity`, `knockbackDecay`, `knockbackCooldown` (`ENEMY_KNOCKBACK_COOLDOWN` 0.5 s)
- Enum: `EnemyType { LOW_LEVEL_ENEMY, MID_LEVEL_ENEMY, HIGH_LEVEL_ENEMY, BOSS_LEVEL_ENEMY, BARRICADE_ENEMY }` (high and boss are not used yet)
- Planned additions (item 10):
  ```cpp
  protected:
      int maxHealth = 0;
      int scoreValue = 0;
      int scrapValue = 0;
      int contactDamage = 10;
      std::string displayName;          // for the game-over "Killed by" line
  public:
      int getScoreValue() const;
      int getScrapValue() const;
      int getContactDamage() const;
      int getMaxHealth() const;
      const std::string& getDisplayName() const;
      virtual bool isBoss() const { return false; }
      virtual float getCollisionRadius() const { return hitbox.width; }
      void applyHealthScaling(float multiplier);   // health = maxHealth = round(base * multiplier)
  ```
- Contract for every subclass constructor: set `health`, `maxHealth`, `spriteSize`, `origin`, `speed`, `rect`, `hitbox`, knockback fields, the five new values above; register its looping animation in the Animator **under `enemyID`**; call `Play(enemyID)`.
- Contract for `destruct()`: `Animator::Remove(enemyID)`, then register a **non-looping** destruct animation under the same `enemyID` at the current position and rotation, then `Play`. The Animator deletes it when it completes.
- Contract for `draw()`: update `rect`/`hitbox` position and push position and rotation to the Animator. Do not draw the sprite directly (except bosses, see `Boss`).
- Gotchas: score values are currently hardcoded in `Game.cpp` (low 10, mid 50); item 10 moves them to the enemy via `Balance.hpp`.

### LowLevelEnemy
- Files: src/LowLevelEnemy.hpp, src/LowLevelEnemy.cpp
- Status: existing (reskinned in item 15)
- Kind: derived
- Inherits: `Enemy`
- In-game name: Junk Swarmer
- Debug-spawn support: rotation initializes to zero so drawing while the console pauses simulation is defined before the first update.
- Behavior: homing. Each frame it lerps its direction toward the player (`turnSpeed` 5) and moves at 15 to 30 units/s. Kamikaze on contact. HP 30.
- Sprites: picks one of three variants at random: `low_level_enemy1` (10 frames), `low_level_enemy2` (5), `low_level_enemy3` (5); destruct `*_destruct` (8, 8, 7 frames). All frames 64 x 64 px.
- Gotchas: the constructor initializes `textureName` with one random roll and the animation with a second, separate roll; `textureName` is unused for drawing. Harmless; do not rely on `textureName`.

### BarricadeEnemy
- Files: src/BarricadeEnemy.hpp, src/BarricadeEnemy.cpp
- Status: implemented, P3 user-requested prototype.
- Kind: final subclass of `Enemy`, owned by `EnemyManager`.
- Constructor: `BarricadeEnemy(const std::string& id, Vector2 center, float angle)`.
- Behavior: orbits a fixed center at 4 degrees/s while shrinking, then scatters straight along its release heading, using accumulated simulation time. `update()` delegates to deterministic `advance(float dt)`. Previous position supports relative swept contact.
- Combat: normal enemy HP/damage/removal paths; cannot receive knockback or crowd separation. Never removed by ordinary kamikaze or debris contact. Gameplay values are `Balance::BARRICADE_*`.
  - Drawing: orbital scrap texture registered as a one-frame WORLD animation under its unique enemy ID; destruction removes its Animator entry and queues the same complete destruction sheet and saved-coordinate glow handoff as DEBRIS_CLUMP. Flying enemies retain their top layer.

### BarricadeEvent
- P3 follow-up queries: `getRadius() const`, `getAliveSegments() const`, `hasTriggeredAutomatically() const` provide live diagnostics without exposing mutable event state. Radius includes outward scatter; inactive radius is zero.
- Files: src/BarricadeEvent.hpp, src/BarricadeEvent.cpp
- Status: implemented, P3; value owned by Game, not a singleton or replacement WaveDirector.
- API: `start(Vector2)`, `update(float dt, float runTime, Vector2 playerPosition)`, `constrainPlayer(Player&, Vector2 previousPosition) const`, `finishIfEscaped(Vector2, const Camera2D&)`, `reset()`, `drawStatus() const`, phase/center/elapsed queries.
- Owns only tracked segment IDs, center, simulation elapsed time, phase and once-per-run automatic trigger flag. EnemyManager owns all segment objects. Resolves IDs on every use; no persistent enemy pointers.
- Full-ring spawn or no spawn at capacity. Relative circle sweeps catch boost and moving-wall contacts; bounded neighboring-disk projections resolve seams. Interior bounce points into the arena. Player handles vulnerability and shield damage rules separately.
- Cleanup erases only tracked IDs and their animations without kill rewards. Reset before EnemyManager resets/reuses IDs. Game calls reset on restart, scene entry/exit, death and destruction.

### MidLevelEnemy
- Files: src/MidLevelEnemy.hpp, src/MidLevelEnemy.cpp
- Status: existing (reskinned in item 15)
- Kind: derived
- Inherits: `Enemy`
- In-game name: Rogue Satellite
- P2: excluded from crowd separation/obstacles. Both live and destruction animations use `ANIMATION_FLYING`, drawn after ordinary world animations. Movement/shooting logic is unchanged.
- Behavior: steers toward the player with a slower turn (1.5 to 2.5) and higher speed (25 to 50), producing circling and strafing passes. Fires a bullet along its **view direction** when it is roughly facing the player (`fireRange` 1.85 on the sum-of-directions test), within 100 units, on a 0.5 to 1.25 s cooldown. Bullet speed 120 to 150. HP 50.
- Sprites: `mid_level_enemy` (12 frames), `mid_level_enemy_destruct` (7 frames), 64 x 64 px.

### HighLevelEnemy (planned)
- Files: src/HighLevelEnemy.hpp, src/HighLevelEnemy.cpp
- Status: planned (item 16)
- Kind: derived
- Inherits: `Enemy`, type `HIGH_LEVEL_ENEMY`
- In-game name: Compactor
- Behavior: a state machine inside the class: `APPROACH` (slow homing like the swarmer) → when within charge range: `WINDUP` (stops, flashes toxic tint, aims) → `CHARGE` (dashes in a straight line at high speed) → `RECOVER` (slow, vulnerable) → `APPROACH`. Fires a 3-bullet spread when the charge ends. Numbers in `Balance.hpp`, behavior in `game-design.md`.
- Sprites: `high_level_enemy` (frames per the sprite table in `ui-rules.md`), `high_level_enemy_destruct`.
- Gotchas: the charge must not be stopped by knockback. Ignore knockback while in `CHARGE`.

### Boss (planned)
- Files: src/Boss.hpp, src/Boss.cpp
- Status: planned (item 17)
- Kind: abstract base
- Inherits: `Enemy`, type `BOSS_LEVEL_ENEMY`
- Public API:
  ```cpp
  class Boss : public Enemy {
  public:
      Boss(std::string id, Vector2 spawnPos, Vector2 playerPos);
      bool isBoss() const override { return true; }
      int getPhase() const;                 // 1, 2, 3...
      float getHealthFraction() const;      // for the HUD boss bar
      bool isIntroFinished() const;         // invulnerable during intro
      void update() final;                  // runs intro, phase checks, then updatePhase(dt)
  protected:
      virtual void updatePhase(float dt) = 0;
      virtual void onPhaseChanged(int newPhase) {}
      virtual std::vector<float> phaseThresholds() const = 0;  // e.g. {0.5f} = phase 2 below 50%
      void fireRing(int bulletCount, float speed, float angleOffsetDeg);
      void fireAimed(int bulletCount, float spreadDeg, float speed);
      void spawnAdds(EnemyType type, int count);   // through EnemyManager
      RunRng* rng;                                  // set by WaveDirector at spawn
  };
  ```
- Behavior shared by all bosses: 2 s intro (drifts in, invulnerable, HUD shows name), phase changes at health thresholds, no knockback, contact damage without being removed, large scrap drop on death.
- Gotchas: bosses are large; draw them directly in `draw()` (not through the Animator) so they render above other enemies, or set an Animator layer if item 17 adds one. Record which.

### HoarderBoss (planned)
- Files: src/HoarderBoss.hpp, src/HoarderBoss.cpp
- Status: planned (item 18)
- Kind: derived from `Boss`
- In-game name: The Hoarder (wave 5)
- Behavior: see `game-design.md` Bosses.

### CoreBoss (planned)
- Files: src/CoreBoss.hpp, src/CoreBoss.cpp
- Status: planned (item 19)
- Kind: derived from `Boss`
- In-game name: The Core (wave 10, final)
- Behavior: see `game-design.md` Bosses. Its death in Story mode triggers `GAME_VICTORY`.

---

## Managers

### EnemyManager
- P3: `std::vector<std::string> spawnBarricade(Vector2 center)` creates all event segments using the shared enemy ID counter, or none if capacity is insufficient. Returns IDs to the Game-owned event; no new singleton state. Crowd separation still accepts only LOW_LEVEL_ENEMY.
- Files: src/EnemyManager.hpp, src/EnemyManager.cpp
- Status: existing → modified (items 10, 11)
- Kind: singleton
- Public API (current): `update(Vector2 playerPos, const GameTimer&)`, `draw()`, `getEnemies()` (map reference), `removeEnemy(const std::string& id)` (calls `destruct()` then erases), `reset()`
- Private: `spawnEnemy(Vector2 playerPos, float elapsed)`, `enemyCounter`, `enemySpawnCooldown`. Existing 10,000-enemy limit and 150-unit spawn radius now live in Balance.
- Debug-only API: `int spawnLowEnemies(Vector2 playerPos, int quantity)` evenly distributes new LowLevelEnemy instances around the existing spawn ring, sharing the normal ID counter. Returns the actual count, clamped to remaining capacity. Natural spawns also respect the limit per insertion.
- P2: public `separateEnemies(float dt)` runs after movement/despawning. A reusable `crowdGrid` and non-owning `crowdEnemies` snapshot include only living LOW_LEVEL_ENEMY objects. Compute corrections from immutable positions, then apply gradual speed-limited pushes. `reset()` clears both containers; no observers survive use across frames. Gameplay tuning is in Balance, query budgets in Config.
- Target API (item 11):
  ```cpp
  void update(Vector2 playerPos);                         // move/fire only, no spawning
  std::string spawn(EnemyType type, Vector2 position, float healthMultiplier);
  std::string spawnBoss(std::unique_ptr<Boss> boss);
  int aliveCount() const;                                  // excludes bosses
  bool hasBoss() const;
  Boss* getBoss();                                         // nullptr if none
  void killAllNonBoss();                                   // future clear-wave support (no command currently assigned)
  ```
- Gotchas:
  - The per-frame spawn-rate output was removed during the user-requested item 28 early performance subtask. Public API and spawn behavior are unchanged.
  - Enemies farther than 1000 units are removed **with** their destruct animation.
  - IDs are `"enemy_" + counter`. Bosses use `"boss_<name>"`.

### BulletManager
- Files: src/BulletManager.hpp, src/BulletManager.cpp
- Status: existing
- Kind: singleton
- Public API: `update(Vector2 playerPos)` (moves bullets, removes those over 150 units from the player), `draw(const Texture2D& playerTex, const Texture2D& enemyTex)`, `addBullet(Bullet)`, `getBullets()`, `getBullet(int)`, `removeBullet(int)`, `clear()`, `reset()`
- Gotchas: a `std::vector<Bullet>` with erase-by-index. Callers iterating while removing must decrement the index (existing code does `i--`). Item 17 may add a boss bullet texture; if so, add a third texture parameter rather than a new manager.

### DebrisManager
- Files: src/DebrisManager.hpp/.cpp
- Status: renamed from AsteroidManager, 15 October.
- Kind: run-state singleton; reset() is called by Game::resetRun().
- API: update(playerPos, gameTimer), draw(), reset(), getDebris(), removeDebris(id, bool harvestable = false). Duplicate removal returns false safely.
- Preserves the existing continuous spawn ramp and 150-unit despawn distance; natural spawns choose among ten variants. Player weapon paths pass harvestable=true; environmental collisions and offscreen removal award no scrap.
- Debug-only spawnGallery(playerPos) places all ten types around a stationary 60-unit ring, via spawn debris all.

### ScrapManager
- Files: src/ScrapManager.hpp/.cpp
- Status: implemented for debris harvesting, 15 October.
- Kind: run-state singleton; owns pending Destruction records and vector<unique_ptr<ScrapPickup>>.
- API: spawnDebris(center, angle, kind, drawSize, harvestable), update(dt, playerPosition) returns newly collected value, draw(), reset(), count(), pendingValue(), getPickups(), destructionCount() (read-only inspection).
- Plays all eight whole destruction frames. At 0.7 s it replaces the last visible frame's 14 flecks with glow-texture orbs using Theme::SCRAP_EXIT_PIXELS, scaled/rotated around the same origin. Pending value includes unfinished explosions. Limits active orbs to 150; overflow merges value only after the explosion. New orbs consume only residual dt. Reset clears explosions and pickups.
- Game advances it only while running and alive, after collisions, and adds the result to harvestedScrap. No cargo limit for now (explicit user choice). Pause/console/augment freeze it; death, scene exit, destruction, restart and entry clear it. Deposit/shop/ordinary enemy drops remain planned.
---

## Gameplay Systems (planned)

### WaveDirector
- Files: src/WaveDirector.hpp, src/WaveDirector.cpp
- Status: planned (item 11)
- Kind: class owned by `Game`
- Public API:
  ```cpp
  enum WavePhase { WAVE_LAUNCH, WAVE_ACTIVE, WAVE_BOSS, WAVE_CLEARED, WAVE_RETURN };
  void reset(GameMode mode, unsigned int seed);
  void update(float dt, Vector2 playerPos);   // spawns through EnemyManager
  void startNextWave();                       // called by Game when launching from the dock
  void beginReturnPhase();                    // called by Game after the augment pick
  WavePhase getPhase() const;
  int getWaveNumber() const;                  // 1-based
  bool isBossWave() const;
  bool isFinalWave() const;                   // Story wave 10
  float getBannerTimer() const;
  int getBudgetRemaining() const;             // debug overlay
  RunRng& rng();
  ```
- Uses: `EnemyManager`, `RunRng`, `Balance` wave tables.

### CollisionSystem
- Files: src/CollisionSystem.hpp, src/CollisionSystem.cpp (currently empty)
- Status: remove-empty → planned (item 06)
- Kind: class owned by `Game`
- Public API:
  ```cpp
  struct KillEvent { EnemyType type; Vector2 position; int scoreValue; int scrapValue; bool wasBoss; };
  struct CollisionReport {
      std::vector<KillEvent> kills;
      int debrisDestroyedByPlayer = 0;
      std::vector<Vector2> debrisKillPositions;
      bool playerHit = false;
      bool playerDied = false;
      DeathInfo killer;                 // valid when playerDied
      int scrapCollected = 0;
      bool enteredDock = false;
  };
  CollisionReport run(Player& player, Dock& dock, bool dockingOpen, int freeCargo);
  ```
- Rule: item 06 moves the existing loops out of `Game::update` **without changing behavior**. New collision pairs are added in later items.

### HUD
- Files: src/HUD.hpp, src/HUD.cpp
- Status: planned (item 07)
- Kind: UI class owned by `Game`
- Public API: `update(float dt)`, `draw(const HudData&)`, where `HudData` is a plain struct filled by `Game` each frame: health, max health, cargo, cargo capacity, credits, wave number, wave phase, banner timer, elapsed time, kill count, boss name and health fraction, dock screen position, dock visible flag, tutorial prompt.
- Gotchas: draws only in screen space. Moves the existing health bar, `KillCounter::draw()` and `GameTimer::draw()` calls here.

### Augment (planned)
- Files: src/Augment.hpp, src/Augment.cpp
- Status: planned (item 09)
- Kind: data + free functions (replaces `utils::augmentPool`)
- API:
  ```cpp
  enum AugmentId { AUG_RAPID_FIRE, AUG_TRIGGER_HAPPY, AUG_SCATTER_SHOT, AUG_SPEED_DEMON,
                   AUG_NANO_REPAIR, AUG_PIERCING_ROUNDS, AUG_PHASE_SHIFT, AUG_GYRO_CONTROL,
                   AUG_INERTIA_IMPACT, AUG_COUNT };
  struct AugmentInfo { AugmentId id; const char* title; const char* description; };
  const AugmentInfo& getAugmentInfo(AugmentId id);
  std::array<AugmentId, 3> rollAugmentOffer(RunRng& rng);   // three distinct ids
  void applyAugment(Player& player, AugmentId id);          // the only switch on AugmentId
  ```
- `Card` stores an `AugmentId` (item 09 adds `getAugmentId()`), so `Game` no longer compares titles.

### UpgradeShop and GearUpgrade (planned)
- Files: src/UpgradeShop.hpp, src/UpgradeShop.cpp
- Status: planned (item 14)
- Kind: data + logic owned by `Game`
- API:
  ```cpp
  enum GearId { GEAR_BLASTER, GEAR_FIRE_CONTROL, GEAR_HULL, GEAR_ARMOR,
                GEAR_THRUSTERS, GEAR_TRACTOR, GEAR_CARGO, GEAR_COUNT };
  struct GearUpgrade { GearId id; const char* name; const char* description; int level; int maxLevel; };
  class UpgradeShop {
  public:
      void reset();
      const GearUpgrade& get(GearId id) const;
      int costOfNextLevel(GearId id) const;        // -1 when maxed
      bool canBuy(GearId id, int credits) const;
      int buy(GearId id, Player& player);          // applies effect, returns cost spent
      int repairCost(const Player& player) const;
      void repair(Player& player);
  };
  ```
- Rule: costs and effects live in `Balance.hpp`. The only switch on `GearId` that applies effects is in `buy()`.

### DockShopUI (planned)
- Files: src/DockShopUI.hpp, src/DockShopUI.cpp
- Status: planned (item 14)
- Kind: UI owned by `Game`
- Behavior: drawn in `GAME_DOCKED`. Left: deposit summary ("Scrap deposited +N"), credits. Center: 7 upgrade rows (name, level pips, effect, cost, buy button). Right: Repair button, Launch button. Returns a `DockAction` enum each frame (`DOCK_NONE`, `DOCK_BOUGHT`, `DOCK_REPAIRED`, `DOCK_LAUNCH`).
- Uses: `Button`, `Theme`.

### RunContext (planned)
- Files: src/RunContext.hpp, src/RunContext.cpp
- Status: planned (item 05)
- Kind: singleton
- Fields: `GameMode mode` (`MODE_STORY`, `MODE_ENDLESS`), `unsigned int seed`, `RunResult lastResult` (mode, score, waves cleared, seconds, victory flag, leaderboard rank or -1)

### RunRng (planned)
- Files: src/RunRng.hpp
- Status: planned (item 05)
- Kind: value class (header-only)
- API: `explicit RunRng(unsigned int seed = 0)`, `void reseed(unsigned int)`, `int range(int minInclusive, int maxInclusive)`, `float rangef(float min, float max)`, `float angleRad()`; wraps `std::mt19937`.

### Leaderboard and NameEntry (planned)
- Files: src/Leaderboard.hpp/.cpp, src/NameEntry.hpp/.cpp
- Status: planned (item 24)
- Leaderboard API: `load()`, `save()`, `bool qualifies(GameMode, int score) const`, `int insert(const LeaderboardEntry&)` (returns rank or -1), `const std::vector<LeaderboardEntry>& top(GameMode) const`
- NameEntry: UI widget for the game-over screen; reads `GetCharPressed()`, Backspace, Enter; uppercase letters, digits and space; 3 to 12 characters.

### PauseOverlay (planned)
- Files: src/Pause.hpp, src/Pause.cpp (currently empty; class name `PauseOverlay`)
- Status: planned (item 07)
- Behavior: dim overlay, "PAUSED", Resume and Quit to Menu buttons. Returns an action enum.

### DebugTools
- P3 follow-up: independent `statsVisible` and collision-overlay flags, both cleared by reset. `hitbox` draws only world collision geometry; `stats` draws the panel and reads the current Game-owned BarricadeEvent. Each supports on/off/toggle and autocomplete. Console opacity is 92%, dropdown 95%; stats panel remains independently translucent.
- P3: `spawn barricade event` starts the Game-owned event, with autocomplete/help, living-run guard, duplicate-event and capacity feedback. Console capture freezes the spawned event until closed.
- P2 spawn follow-up: `spawn lowlevel enemy <quantity>` accepts integers 1–10,000, requires a living player, and reports actual count/capacity. Autocomplete fills the command prefix and leaves quantity editable. Enemy creation stays in EnemyManager; the command and batch API compile only with GAME_DEBUG.
- P1: `player` command lists presets and individual weapon/engine/shield choices, with argument autocomplete. Typed metadata dispatch, strict argument validation and live-run guard. Public API unchanged; hitbox view adds swept projectile geometry, beam capsules and shield arcs.
- Files: src/DebugTools.hpp, src/DebugTools.cpp
- Status: built (item 04, F5 console follow-up)
- Kind: value
- Owned by: long-lived `Game` scene; `Application` routes console calls even outside a run
- Public API: `void reset()`, `void update(Player* player, BarricadeEvent* barricade = nullptr)`, `void drawConsole() const`, `bool capturesInput() const`, `void drawWorld(const Player& player) const`, `void drawOverlay(const Player& player, GameState state, const BarricadeEvent& barricade) const`
- Uses: `Player`, read-only enemy/debris/bullet containers, `ResourceManager`, `Theme`, `Config`
- Behavior: compiled only with `GAME_DEBUG`. F5 toggles the translucent terminal; vertical six-row suggestion dropdown with Up/Down or PageUp/PageDown navigation. Tab/Enter fills a selected row; Enter without a selection executes. Ctrl+Up/Down browses history (plain arrows also work with empty input). Editing/reset/execution clears suggestion selection/scroll state. Backspace edits and Escape closes. Metadata lookup dispatches enums for `help`, `hitbox`, `mute`, `invincible`, `credits`, `boss`, `wave`, `clear`, `close`. Toggle arguments are optional `on/off/toggle`. Pending systems report unavailable. A null player rejects gameplay commands outside a run.
- Gotchas: capture includes opening/closing frames. Ship collision radius is `getHitbox().width`, debris radius is `getDebrisSize()`, bullets are points. `drawWorld` uses the gameplay camera; diagnostics and console use canvas space. `reset()` clears run UI state but preserves mute/saved volume; `Player::init()` resets invincibility. Reset both paths until item 05. Input/history/output limits live in Config, layout/opacity in Theme.
- Changed by: 04

---

## Rendering, Assets and Effects

### ResourceManager
- P1: registers 28 modular player textures plus managed `player_shoot` sound. Public API unchanged. Paths/CC0 provenance are in assets/ASSETS.md.
- Files: src/ResourceManager.hpp, src/ResourceManager.cpp
- Status: existing
- Kind: singleton
- Public API: `LoadTextures()` (threaded decode), `ProcessLoadedTextures()` (GPU upload, main thread), `LoadFonts()`, `LoadSounds()`, `LoadMusics()`, `LoadShaders()`, `Unload()`, `GetTextureLoadingProgress()`, `GetTexture(name)` (copy), `GetTextureRef(name)` (reference; returns a static empty texture and logs if missing), `GetFont(name)` (falls back to the default font), `GetSound(name)`, `GetMusic(name)`, `GetShader(name)`
- Registered keys: see the asset table in `ui-rules.md`.
- Rules: every asset is registered by key in the constructor maps (`texturePaths`, `soundPaths`, `musicPaths`, `fontPaths`, `shaderPaths`). Code asks for keys, never paths. Exceptions in the current code: `Game.cpp` and `Player.cpp` call `LoadSound("assets/...")` directly (fixed in item 05).
- Gotchas: fonts load with `LoadFontEx(path, 126, nullptr, 0)`, so glyphs are rasterized at 126 px; very large text is upscaled.

### Animator
- Files: src/Animator.hpp, src/Animator.cpp
- Status: existing
- Kind: singleton
- Public API: `AddAnimation(name, std::shared_ptr<Animation>, AnimationLayer layer = ANIMATION_WORLD)` (replaces any existing entry with that name), `Play(name)` (resets and starts), `Stop(name)`, `Pause(name)`, `StopAll()`, `PauseAll()`, `Remove(name)`, `Update()`, `Draw()`, `IsCompleted(name)`, `SetRotation`, `SetOrigin`, `SetTint`, `SetPosition`
- Behavior: `Update()` advances active animations and **erases** any non-looping animation that completed. `Draw()` traverses WORLD then FLYING, drawing each active animation once. Within each layer, map order remains unspecified. No per-frame sorting or extra animation updates. Mid-level ships and their destruction effects use FLYING.
- Gotchas:
  - `IsCompleted(name)` does not check that `name` exists; calling it after the animation was erased is undefined behavior. Check with a new `has(name)` method first (item 05).
  - Shared by all scenes. Scenes call `StopAll()` in `onExit()`.
  - World-space animations (ships) and screen-space animations (menu background, game-over text) share the same Animator. Game over draws screen-space animations by calling `Draw()` again outside `BeginMode2D` after repositioning; this re-draws everything active. Keep this in mind when adding animations during game over.

### Animation
- Files: src/Animation.hpp, src/Animation.cpp
- Status: existing
- Kind: value
- Constructor: `Animation(const Texture2D& spriteSheet, int frameWidth, int frameHeight, float frameDuration, bool looping, Rectangle dest, bool flipX, Color tint)`
- Behavior: slices the sheet into frames left-to-right, top-to-bottom. `dest` width and height are the **draw size in the current space** (world units for ships, pixels for UI).
- Gotchas: stores a **reference** to the texture. Always pass `ResourceManager::GetTextureRef(...)`, never a temporary copy from `GetTexture(...)`.

### Bullet
- Files: src/Bullet.hpp, src/Bullet.cpp
- Status: modified (P1)
- Kind: value, owned by BulletManager vector.
- Constructor (unchanged): `Bullet(Vector2 position, Vector2 direction, bool isEnemy, int piercePower = 1, float knockbackPower = 0.0f)`.
- Public API: `update()`, `draw(const Texture2D&) const`, `getPosition() const`, `getDirection() const`, `isEnemyBullet() const`, `setBulletSpeed(float)`, `getPiercePower() const`, `reducePiercePower()`, `canPierce() const`, `getKnockbackPower() const`.
- Equipment API: `configure(ProjectileKind, int damage, float radius, float speed)`, `getKind() const`, `getDamage() const`, `getRadius() const`, `getPreviousPosition() const`, `hasHit(const std::string&) const`, `recordHit(const std::string&)`, static `hitFraction(Vector2 from, Vector2 to, Vector2 center, float radius)`.
- Enums: PlayerWeapon (CANNON/LASER/ROCKETS/HEAVY/DEFAULT); ProjectileKind (LEGACY/CANNON/ROCKET/HEAVY).
- Gotchas: constructor defaults to LEGACY for existing enemy callers and regression fixtures. Modular player projectiles configure immutable-at-fire damage, sprite type and radius; the original default uses LEGACY bullets and the existing damage/collision path. update saves previous position before movement. hitFraction returns earliest swept-circle contact in [0,1], or -1 for no hit; use target radius plus projectile radius. Piercing IDs prevent repeated damage across frames. Laser is a Player-owned continuous beam, not a Bullet.
- Planned item 08: incoming enemy/boss damage amounts remain separate; this prototype adds player projectile damage only.

### DamageIndicator / DamageIndicatorManager
- Files: src/DamageIndicator.*, src/DamageIndicatorManager.*
- Status: existing
- Kind: value + singleton
- API: `DamageIndicatorManager::addDamageIndicator(Vector2 worldPos, int damage, int maxDamage)`, `update()`, `draw()` (world space), `reset()`

### DamageOverlay
- Files: src/DamageOverlay.*
- Status: existing
- Kind: singleton
- API: `startDamageAnimation()`, `update()`, `draw()` (red screen-edge gradient), `reset()`

### GameOverOverlay
- Files: src/GameOverOverlay.*
- Status: existing
- Kind: singleton
- API: `startOverlay()`, `update()`, `draw()`, `reset()`, `isActive()`, `isFullyVisible()`, `shouldShowText()`, `getTextYPosition()`

### ConfettiManager / ConfettiParticle
- Files: src/ConfettiManager.*, src/ConfettiParticle.*
- Status: existing
- Kind: singleton + value
- API: `startConfetti()`, `stopConfetti()`, `update()`, `draw()` (screen space, during augment selection), `reset()`

### ExplosionConfettiManager / ExplosionConfettiParticle
- Files: src/ExplosionConfettiManager.*, src/ExplosionConfettiParticle.*
- Status: existing
- Kind: singleton + value
- API: `startExplosion(Vector2 worldPos)`, `stopExplosion()`, `update()`, `draw()` (world space, on player death), `reset()`, `isActive()`
- Reuse: use it for boss deaths too (item 17).

---

## UI Components

### Button
- Files: src/Button.hpp, src/Button.cpp
- Status: existing
- Kind: UI value
- Constructor: `Button(Rectangle rect, std::string text, float size, ButtonType type)`; `ButtonType { BUTTON_LEFT_SIDE, BUTTON_CENTERED }`
- API: `setColor(Color)`, `isHovered()`, `isClicked()` (hover + left press this frame), `draw()`
- Style: text in `secondary_font`; default color `Fade(SKYBLUE, 0.5f)`; hover fills the rect and turns text black.
- Planned (item 14): `setEnabled(bool)` with a muted style, for unaffordable upgrades.

### Card
- Files: src/Card.hpp, src/Card.cpp
- Status: existing → modified (item 09)
- Kind: UI value
- Constructor: `Card(Vector2 position, Vector2 size, const std::string& title, const std::string& description)`
- API: `update()`, `draw()`, `getRect()`, `getTitle()`, `setPosition`, `setSize`, `setTitle`, `setDescription`, `isMouseHovered()`, `isClicked()`, `startIntroAnimation()`, `startExitAnimation()`, `isIntroComplete()`, `isExitComplete()`
- Style: dark panel `{20,20,30}`, animated multicolor border, title in `primary_font`, description in `secondary_font`.
- Planned (item 09): constructor overload taking `AugmentId`, plus `getAugmentId()`.

### KillCounter
- Files: src/KillCounter.*
- Status: existing
- Kind: UI value owned by `Game`
- API: `increment()`, `update()`, `draw()` (top-left "X<count>", red, wobble on increment), `reset()`, `getCount()`

### GameTimer
- Files: src/GameTimer.*
- Status: existing
- Kind: value owned by `Game`
- API: `start()`, `pause()`, `unpause()`, `reset()`, `setStartTime(float)`, `getElapsedTime()`, `getElapsedTimeString()` ("m:ss"), `isRunning()`, `draw(int screenWidth)` (top center)

---

## Utilities

### Cooldown (in Timer.hpp)
- Files: src/Timer.hpp, src/Timer.cpp
- Status: existing
- Kind: value
- API: `Cooldown()`, `Cooldown(float seconds)`, `isOnCooldown()`, `startCooldown()`, `remainingCooldown()`, `getCooldownDuration()`, `remainingCooldownString()`, `updateCooldownDuration(float)`, `pause()`, `unpause()`
- Gotchas: uses wall-clock `GetTime()`. `isOnCooldown()` ignores pausing. Cooldowns keep running while the game is paused or docked, so enemies may fire immediately on resume. Acceptable; do not "fix" without a decision.

### utils (Utils.hpp)
- Files: src/Utils.hpp, src/Utils.cpp
- Status: existing → partly replaced (item 09)
- Contents: `extern Camera2D utils::gameCamera` (keep), `utils::augmentPool` (replaced by `Augment`), `AUGMENTS_POOL_SIZE` define

### SpatialGrid
- Files: src/SpatialGrid.hpp, src/SpatialGrid.cpp
- Status: modified (item 28 early performance subtask, 14 October)
- Kind: value, owned by `Game` (one for enemies, one for debris) and `EnemyManager` (separate crowd snapshot)
- Public API: `NO_HIT`, `clear()`, `reserve(std::size_t)`, `add(Vector2, float radius)`, `build()`, `deactivate(std::size_t)`, `isActive(std::size_t) const`, `firstHit(Vector2) const`, `firstWithin(Vector2, float radius, std::size_t exclude = NO_HIT) const`.
- P2: `Vector2 separation(std::size_t index, float slide = 0.0f) const` returns soft overlap correction, using summed radii, deterministic opposite directions for coincident pairs and optional pair-symmetric lateral steering. Visits at most 24 entries per queried cell; at most 16 cells, otherwise bounded circular sampling. Dense neighborhoods are intentionally approximate. Combat first-hit APIs retain their exact ordering/predicates. No allocations in queries.
- Uses: `Config.hpp` cell size / small-set threshold / bucket sizing, Raymath's original `Vector2Distance` narrow-phase predicate.
- Contract: clear/add/build before querying; returned index is insertion order, not distance order. `firstHit` uses each target's radius; `firstWithin` uses the caller's radius. Deactivation excludes a removed target immediately without invalidating other indices. No owning pointers or singleton state.
- Storage: reusable flat entries and power-of-two hash buckets, linked by indices in ascending insertion order. Per-bucket center bounds reject dense near misses. Tiny sets and enormous/non-finite coordinates use an ordered linear fallback. Large query areas also fall back to scanning.
- Gotchas: add/build snapshots do not follow movement automatically. Never dereference a deactivated observer. Retain deferred entity-phase removals until the existing end-of-phase commit; early deactivation there changes gameplay. `clear()` retains capacity for reuse.
- Changed by: 28 (user explicitly requested this work ahead of the planned date); the previously unused string/position query API had no callers and was replaced.
