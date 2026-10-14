# Class Registry

Living document. It replaces the web project's UI registry: instead of components, it lists every **class**, what it owns, who owns it, its public API and its traps. Read it before creating or changing any class.

Item 01 baseline import (14 October 2026): Asteroid, Button, GameTimer, MainMenu and Player use standard C++ brace initialization instead of C-style compound literals so MSVC can compile them. Public APIs, ownership and gameplay behavior are unchanged.

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
├── Asteroid                            existing → modified (15, reskinned as debris)
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
| `AsteroidManager` | Yes | Yes |
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
- Status: existing
- Kind: value (one instance in `main`)
- Owned by: `main()`
- Public API: `Application()`, `void Run()`, `~Application()`
- Uses: `ResourceManager`, all scenes, shaders `"shader"` and `"barrel_distortion"`, texture `"border"`
- Gotchas:
  - Creates every scene once in `m_sceneFactory` (a `std::map<std::string, std::shared_ptr<Scene>>`). New scenes must be added there.
  - Defines its own `screenWidth = 3840`, `screenHeight = 2160` constants; replace with `Config.hpp` in item 03.
  - Calls `DrawFPS(10, 10)` on the real window every frame (outside the CRT pass). Remove or guard with `GAME_DEBUG` before recording videos.
  - `SetExitKey(KEY_NULL)`: Esc does not close the window, so Esc is free for pause.
- Changed by: 03, 20, 24, 25

### Scene
- Files: src/Scene.hpp
- Status: existing
- Kind: abstract base
- Public API: `virtual std::string update() = 0`, `virtual void draw() = 0`, `virtual void onSwitch() = 0`, `virtual void onExit() = 0`, virtual destructor
- Gotchas: also `#define`s `GAME_SCREEN_WIDTH 3840` and `GAME_SCREEN_HEIGHT 2160`. Many files get these constants through `Scene.hpp`. Item 03 moves them to `Config.hpp` and makes `Scene.hpp` include `Config.hpp` so existing includes keep working.

### LoadingScreen
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
- Files: src/Game.hpp, src/Game.cpp (857 lines)
- Status: existing → modified in most items
- Kind: scene (`"Game"`), the gameplay orchestrator
- Owns (current): `Player playerEntity`, `KillCounter killCounter`, `GameTimer gameTimer`, `std::vector<Card> augmentCards`, `std::vector<BackgroundLayer> backgroundLayers` (4 parallax layers), `Music gameMusic`, `Button* restartButton`, `Button* mainMenuButton` (raw `new`), `std::array<Sound, 10> scoreSounds`, `DeathInfo deathInfo`, `GameState gameState`
- Owns (target): adds `WaveDirector`, `CollisionSystem`, `HUD`, `Dock`, `UpgradeShop`, `DockShopUI`, `PauseOverlay`, `DebugTools`, run economy (credits, cargo)
- Public API: `update()`, `draw()`, `onSwitch()`, `onExit()` (Scene overrides). Private: `restartGame()`, `DrawParallaxBackground()`, `DrawLayer()`
- Enums in `Game.hpp`: `GameState { GAME_RUNNING, GAME_AUGMENT_SELECTION, GAME_PAUSED, GAME_OVER }` (target adds `GAME_DOCKED`, `GAME_VICTORY`), `KillerType { KILLER_ENEMY_BULLET, KILLER_ENEMY_COLLISION, KILLER_ASTEROID }`, struct `DeathInfo`
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
- Gotchas: no virtual `getRadius()`; collision radii are read from class-specific methods (`getHitbox().width`, `getAsteroidSize()`). Item 10 adds `virtual float getCollisionRadius() const` with a default of `rect.width / 2`.

### Player
- Files: src/Player.hpp, src/Player.cpp
- Status: existing → modified (item 08)
- Kind: entity
- Inherits: `Entity`
- Owned by: `Game` (value member `playerEntity`)
- Public API (current): `init()` (resets everything, registers animations), `update()`, `draw()` (empty; the Animator draws the ship), `getHitbox()`, `takeDamage(float timeStateEntered, Vector2 entityPosition, float entitySize)`, `getPlayerState()`, `addScore(int)`, `getScore()`, `addDamageDealt(int)`, `getTotalDamageDealt()`, `getRandomDamage()`, `getMinDamage()`, `getMaxDamage()`, `getKnockbackPower()`, and nine augment methods: `increasePlayerAttackSpeed()`, `increasePlayerHealth()`, `increasePlayerMovementSpeed()`, `increasePlayerIframeDuration()`, `increasePlayerRotationSpeed()`, `increaseTriggerHappyBurst()`, `increaseScatterShot()`, `increasePiercingRounds()`, `increaseInertiaImpact()`
- Enum: `PlayerState { PLAYER_DEFAULT, PLAYER_STUNNED, PLAYER_IFRAME, PLAYER_DEAD }`
- Behavior: 8-direction WASD movement with acceleration; the ship rotates toward the mouse (rotation speed scales with velocity); shooting fires along the **facing** direction, not straight at the cursor. Burst fire (Trigger Happy) and scatter fan (30° steps). Animations `"accelerating"` (4 frames) and `"deaccelerating"` (3 frames) are registered in the Animator under those fixed IDs.
- Gotchas:
  - `takeDamage` always subtracts 10 and ignores its arguments for the amount. Item 08 changes the signature to `takeDamage(int amount, Vector2 sourcePosition, float knockbackScale)`.
  - `increasePlayerHealth()` heals 10 up to a hardcoded 100.
  - Loads 10 copies of `player_atk_sound.mp3` in `init()` on every restart (leak). Use `LoadSoundAlias`.
  - `Player.cpp` redefines `GAME_SCREEN_WIDTH/HEIGHT`.
  - Stats are loose fields (`attackSpeed`, `speed`, `iframeDuration`, `minDamage`, ...). Item 08 groups them into `PlayerStats`.
- Changed by: 03, 05, 08, 09, 12, 14

### PlayerStats (planned)
- Files: inside src/Player.hpp
- Status: planned (item 08)
- Kind: data struct
- Fields: `int maxHealth`, `float damageMultiplier`, `float attackCooldown`, `float moveSpeed`, `float armor` (0 to 0.6 damage reduction), `float magnetRadius`, `int cargoCapacity`, `float iframeDuration`, `float rotationMultiplier`, `int burstCount`, `int scatterCount`, `int piercePower`, `float knockbackPower`
- Rule: base values come from `Balance.hpp`. Augments and gear upgrades modify `PlayerStats` only through `Player` methods, never by poking fields from outside.

### Asteroid
- Files: src/Asteroid.hpp, src/Asteroid.cpp
- Status: existing → reskinned as "debris" (item 15)
- Kind: entity
- Inherits: `Entity`
- Owned by: `AsteroidManager` (`std::unique_ptr` in a map keyed by ID)
- Public API: `Asteroid(Vector2 playerPos)`, `update()`, `draw()` (direct `DrawTexturePro`, not the Animator), `getPlayerPosition(Vector2)` (a setter despite the name), `getAsteroidID()`, `getAsteroidSize()` (collision radius = `size * 2.5`), `destruct()` (plays `"asteroid_destruct"` through the Animator)
- Gotchas: IDs come from a static `asteroidCounter` that never resets. Fine for uniqueness. Spawns 150 units away aimed at the player with ±30° spread.
- Changed by: 12 (drops scrap), 15

### ScrapPickup (planned)
- Files: src/ScrapPickup.hpp, src/ScrapPickup.cpp
- Status: planned (item 12)
- Kind: entity
- Inherits: `Entity`
- Owned by: `ScrapManager`
- Public API: `ScrapPickup(std::string id, Vector2 position, int value)`, `update()` (drift, slow down, lifetime countdown, blink in the last seconds, move toward the player when inside the magnet radius), `draw()` (direct draw, small sprite with gold tint), `getValue()`, `isExpired()`, `setAttractTarget(Vector2 playerPos, float magnetRadius)`
- Gotchas: dropped scrap scatters with a small random burst velocity so a kill drops a visible spray, not one dot.

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
- Files: src/Enemy.hpp, src/Enemy.cpp
- Status: existing → modified (item 10)
- Kind: abstract base
- Inherits: `Entity`
- Owned by: `EnemyManager` (map `std::unordered_map<std::string, std::unique_ptr<Enemy>>`)
- Constructor: `Enemy(std::string enemyID, EnemyType type, Vector2 spawnPos, Vector2 playerPos)`
- Public API (current): `getPlayerPositionForEnemy(Vector2)` (a setter), `getEnemyType()`, `getHitbox()`, `getEnemyID()`, `virtual void destruct() = 0`, `takeDamage(int)`, `isDead()`, `applyKnockback(Vector2 direction, float force)`, `canReceiveKnockback()`
- Protected (current): `enemyID`, `enemyType`, `viewDirection`, `playerPosition`, `hitbox`, `speed`, `spriteSize`, `knockbackVelocity`, `knockbackDecay`, `knockbackCooldown` (`ENEMY_KNOCKBACK_COOLDOWN` 0.5 s)
- Enum: `EnemyType { LOW_LEVEL_ENEMY, MID_LEVEL_ENEMY, HIGH_LEVEL_ENEMY, BOSS_LEVEL_ENEMY }` (the last two are not used yet)
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
- Behavior: homing. Each frame it lerps its direction toward the player (`turnSpeed` 5) and moves at 15 to 30 units/s. Kamikaze on contact. HP 30.
- Sprites: picks one of three variants at random: `low_level_enemy1` (10 frames), `low_level_enemy2` (5), `low_level_enemy3` (5); destruct `*_destruct` (8, 8, 7 frames). All frames 64 x 64 px.
- Gotchas: the constructor initializes `textureName` with one random roll and the animation with a second, separate roll; `textureName` is unused for drawing. Harmless; do not rely on `textureName`.

### MidLevelEnemy
- Files: src/MidLevelEnemy.hpp, src/MidLevelEnemy.cpp
- Status: existing (reskinned in item 15)
- Kind: derived
- Inherits: `Enemy`
- In-game name: Rogue Satellite
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
- Files: src/EnemyManager.hpp, src/EnemyManager.cpp
- Status: existing → modified (items 10, 11)
- Kind: singleton
- Public API (current): `update(Vector2 playerPos, const GameTimer&)`, `draw()`, `getEnemies()` (map reference), `removeEnemy(const std::string& id)` (calls `destruct()` then erases), `reset()`
- Private: `spawnEnemy(Vector2 playerPos, float elapsed)`, `enemyCounter`, `enemySpawnCooldown`, `maxEnemies` (10,000)
- Target API (item 11):
  ```cpp
  void update(Vector2 playerPos);                         // move/fire only, no spawning
  std::string spawn(EnemyType type, Vector2 position, float healthMultiplier);
  std::string spawnBoss(std::unique_ptr<Boss> boss);
  int aliveCount() const;                                  // excludes bosses
  bool hasBoss() const;
  Boss* getBoss();                                         // nullptr if none
  void killAllNonBoss();                                   // debug F2
  ```
- Gotchas:
  - `update()` prints the spawn rate with `std::cout` **every frame**. Remove in item 05.
  - Enemies farther than 1000 units are removed **with** their destruct animation.
  - IDs are `"enemy_" + counter`. Bosses use `"boss_<name>"`.

### BulletManager
- Files: src/BulletManager.hpp, src/BulletManager.cpp
- Status: existing
- Kind: singleton
- Public API: `update(Vector2 playerPos)` (moves bullets, removes those over 150 units from the player), `draw(const Texture2D& playerTex, const Texture2D& enemyTex)`, `addBullet(Bullet)`, `getBullets()`, `getBullet(int)`, `removeBullet(int)`, `clear()`, `reset()`
- Gotchas: a `std::vector<Bullet>` with erase-by-index. Callers iterating while removing must decrement the index (existing code does `i--`). Item 17 may add a boss bullet texture; if so, add a third texture parameter rather than a new manager.

### AsteroidManager
- Files: src/AsteroidManager.hpp, src/AsteroidManager.cpp
- Status: existing (reskinned as debris in item 15)
- Kind: singleton
- Public API: `update(Vector2 playerPos, const GameTimer&)`, `draw()`, `reset()`, `removeAsteroid(const std::string& id)` (plays destruct), `getAsteroids()`
- Behavior: spawn cooldown from 1.5 s down to 0.25 s over 10 minutes, 1 to 3 per spawn; removes asteroids beyond 150 units **without** a destruct animation.
- Changed by: 11 (debris rate follows the wave, not game time), 15

### ScrapManager (planned)
- Files: src/ScrapManager.hpp, src/ScrapManager.cpp
- Status: planned (item 12)
- Kind: singleton
- Public API: `spawnScrap(Vector2 position, int totalValue)` (splits into pickups of value 1, 5 or 10), `update(Vector2 playerPos, float magnetRadius)`, `draw()`, `collect(Vector2 playerPos, float pickupRadius, int freeCargo)` returns the value collected, `reset()`, `count()`
- Gotchas: cap the number of live pickups (`Balance::SCRAP_MAX_PICKUPS`); when exceeded, merge new value into the nearest pickup.

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
      int asteroidsDestroyedByPlayer = 0;
      std::vector<Vector2> asteroidKillPositions;
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

### DebugTools (planned)
- Files: src/DebugTools.hpp, src/DebugTools.cpp
- Status: planned (item 04)
- Behavior: compiled only with `GAME_DEBUG`. Handles F1 to F6 (see `architecture.md`) and draws the overlay.

---

## Rendering, Assets and Effects

### ResourceManager
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
- Public API: `AddAnimation(name, std::shared_ptr<Animation>)` (replaces any existing entry with that name), `Play(name)` (resets and starts), `Stop(name)`, `Pause(name)`, `StopAll()`, `PauseAll()`, `Remove(name)`, `Update()`, `Draw()`, `IsCompleted(name)`, `SetRotation`, `SetOrigin`, `SetTint`, `SetPosition`
- Behavior: `Update()` advances active animations and **erases** any non-looping animation that completed. `Draw()` draws every active animation in map order (undefined).
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
- Status: existing
- Kind: value (stored by value in `BulletManager`)
- Constructor: `Bullet(Vector2 position, Vector2 direction, bool isEnemy, int piercePower = 1, float knockbackPower = 0.0f)`
- Public API: `update()`, `draw(const Texture2D&)`, `getPosition()`, `getDirection()`, `isEnemyBullet()`, `setBulletSpeed(float)`, `getPiercePower()`, `reducePiercePower()`, `canPierce()`, `getKnockbackPower()`
- Planned (item 08): `int damage` field with `setDamage/getDamage` so enemy and boss bullets carry their damage.

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
- Status: existing, **unused**
- Notes: a hash grid that stores positions by string ID. Nothing calls it. Do not wire it in unless the item-28 performance check shows collisions are too slow with 80+ enemies; record the decision first.
