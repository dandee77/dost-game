# Code Standards

Rules for every line of C++ in this repository. They exist so that code written by five people and several AI sessions over 11 days still looks like one codebase. When editing an existing Space Ablaze file, follow these rules for new code and match the file's local style for small edits; do not mass-rename existing code.

---

## Engineering Mindset

- **Read before writing.** Read the class's entry in `class-registry.md` and the current build-plan item before changing anything.
- **Scope is sacred.** Build exactly the current item. No drive-by refactors, no extra features, no new dependencies.
- **Playable after every item.** The game must build and run after each item. If an item is half done at the end of a session, leave it behind a disabled path, not broken.
- **Clean over clever.** A teammate who has not touched C++ in two years must be able to read any file. Prefer an obvious `switch` over template tricks.
- **Inheritance for variants, data for numbers.** A new enemy behavior is a new subclass. A new difficulty is new numbers in `Balance.hpp`, not a new class.
- **Measure, then optimize.** Do not optimize anything the item-28 performance check has not flagged.

---

## Language and Build

- C++20 (`CMAKE_CXX_STANDARD 20`, required). Use modern features only where they make code clearer: `inline constexpr`, structured bindings, `std::array`, range-for. Do not use designated initializers on Raylib structs; write `Rectangle{x, y, w, h}` in field order.
- Raylib structs (`Vector2`, `Rectangle`, `Color`) are initialized with braces: `Vector2{1.0f, 2.0f}`. Avoid the C-style compound literal `(Vector2){...}` in new code; existing code uses it and GCC accepts it, MSVC does not in all cases.
- Floats always have the `f` suffix: `0.5f`, not `0.5`.
- Compile with warnings visible. Item 01 adds `-Wall -Wextra` (GCC/Clang) or `/W3` (MSVC) to `CMakeLists.txt`. A change must not add new warnings. Existing warnings are listed in `progress-tracker.md` and are fixed only when the file is touched for an item.
- No exceptions for control flow. Raylib does not throw; check returned handles (`texture.id == 0`, `font.glyphs == nullptr`) and log.
- No RTTI-based dispatch (`dynamic_cast` chains). Use virtual functions or `getEnemyType()`.

---

## Files and Naming

| Thing | Convention | Example |
|---|---|---|
| Class files | One class per `.hpp`/`.cpp` pair, PascalCase, flat in `src/` | `HighLevelEnemy.hpp`, `HighLevelEnemy.cpp` |
| Header guard | `#pragma once` as the first line | |
| Classes and structs | PascalCase | `WaveDirector`, `PlayerStats` |
| Methods (new code) | camelCase | `spawnScrap()`, `getHealthFraction()` |
| Methods (existing PascalCase classes) | Keep the file's style | `ResourceManager::GetTexture`, `Animator::Play` |
| Singleton accessor | Always `GetInstance()` | `ScrapManager::GetInstance()` |
| Member fields (new classes) | camelCase, no prefix | `bannerTimer` |
| Member fields (existing `m_` classes) | Keep `m_` in `Application`, `MainMenu`, `Button` | `m_buttons` |
| Local variables | camelCase | `playerPos` |
| Constants | `inline constexpr` in a namespace, SCREAMING_SNAKE | `Balance::LOW_HEALTH` |
| Enums | Unscoped with a type prefix, matching existing code | `WAVE_ACTIVE`, `GEAR_ARMOR`, `AUG_SCATTER_SHOT` |
| Asset keys | snake_case strings | `"high_level_enemy_destruct"` |
| Animator IDs | `"<kind>_<number>"` or a fixed name | `"enemy_42"`, `"scrap_7"`, `"boss_core"` |
| Scene names | PascalCase strings | `"Game"`, `"Leaderboard"` |

Existing code uses `#define` constants. Do not add new `#define`s. The only exception is `GAME_DEBUG`, which CMake defines for debug builds.

---

## Constants: Config, Balance, Theme

There are exactly three constants headers. A number belongs in one of them, never inline.

| Header | Contains | Example |
|---|---|---|
| `src/Config.hpp` | Engine and world constants that are not tuning | `GAME_SCREEN_WIDTH`, `CAMERA_ZOOM_PLAY`, `WORLD_DESPAWN_DISTANCE` |
| `src/Balance.hpp` | Every gameplay number: HP, damage, speeds, cooldowns, costs, wave tables, seeds | `Balance::HIGH_CHARGE_SPEED` |
| `src/Theme.hpp` | Colors, font keys, font sizes, layout rectangles, sprite sheet frame counts | `Theme::COLOR_SCRAP`, `Theme::TEXT_BODY` |

```cpp
// src/Balance.hpp (excerpt)
#pragma once
namespace Balance {
    inline constexpr int   LOW_HEALTH          = 30;
    inline constexpr float LOW_SPEED_MIN       = 15.0f;
    inline constexpr float LOW_SPEED_MAX       = 30.0f;
    inline constexpr int   LOW_SCRAP           = 2;
}
```

Values with a source or a reason get a comment. Values still being tuned get `// TUNE` so the balance pass can find them.

---

## Class Layout

Header order:

```cpp
#pragma once

// 1. Raylib and standard headers
#include "raylib.h"
#include <string>
#include <vector>

// 2. Project headers
#include "Enemy.hpp"
#include "Timer.hpp"

// 3. Enums and small structs used in the interface
enum ChargerState { CHARGER_APPROACH = 0, CHARGER_WINDUP, CHARGER_CHARGE, CHARGER_RECOVER };

// 4. Class
class HighLevelEnemy : public Enemy
{
public:
    // constructors, then overrides, then public methods, then getters
private:
    // helpers, then fields
};
```

Source order: includes (own header first), file-local constants in an anonymous namespace, then methods in header order.

- Include only what the file uses. Prefer forward declarations in headers (`class Player;`) when only a reference or pointer is needed.
- Use `override` on every overriding function. Use `final` when a method must not be overridden again (for example `Boss::update`).
- Every class with a virtual function has a `virtual ~Base() = default;` in the base.
- `const` on every getter and every method that does not change state.
- Pass `Vector2`, `Rectangle`, `Color` by value (they are small). Pass `std::string` by `const&`.

---

## OOP Rules

1. **Declare the base first.** The base class (`Enemy`, `Boss`, `Scene`, `Cutscene`, `Entity`) defines the contract with pure virtual functions. Derived classes implement it. Never add a method to a derived class that the base's callers need; add it to the base.
2. **Behavior lives in the class that owns the data.** A boss's attack pattern lives in the boss, not in `Game`. `Game` decides **when** (state machine), entities decide **how**.
3. **Variants are subclasses, numbers are data.** A swarmer that is 10% faster is not a new class.
4. **No downcasting to decide behavior.** If `Game` needs to know something about an enemy, add a virtual query to `Enemy` (`isBoss()`, `getScrapValue()`).
5. **Ownership is explicit.** Managers own entities as `std::unique_ptr` in a map keyed by ID. `Game` owns systems as value members. Nobody else stores owning pointers.
6. **Raw pointers are non-owning observers only**, and only when the owner outlives the observer (`Boss* getBoss()` returned by `EnemyManager`, used within the same frame).
7. **Singletons are for shared services and run-wide containers only.** Do not make gameplay systems (`WaveDirector`, `CollisionSystem`, `HUD`) singletons; they are owned by `Game`.
8. **Every run singleton has `reset()`**, and `Game::resetRun()` calls it.

---

## Frame Logic

- Every movement, timer and interpolation uses `GetFrameTime()` (or a `dt` parameter passed down). Never assume 60 FPS.
- Smooth follow uses the existing exponential pattern: `value += (target - value) * (1.0f - expf(-speed * dt));`
- `update()` changes state; `draw()` only reads state and draws. Existing exceptions: `Animator::Update()` is called inside `Game::draw()` and `MainMenu::draw()`; keep it to **one call per frame**.
- Do not remove items from a container while iterating with a range-for. Collect IDs, then remove after the loop (existing pattern), or iterate by index and decrement on erase.
- Timers that must stop while paused use `GameTimer` or a `float` accumulated with `dt` in `update()`. `Cooldown` keeps running during pauses (see `class-registry.md`).

---

## Randomness

- Anything that changes what the player faces (wave composition, spawn angles, boss attack choices, augment offers) uses `RunRng` from `WaveDirector::rng()`.
- Purely visual randomness (particles, sprite variant, damage-number jitter) may use `GetRandomValue()`.
- Never call `srand()`/`rand()` in new code.

---

## Logging and Errors

- Use `TraceLog(LOG_INFO | LOG_WARNING | LOG_ERROR, "[Class::method] message %d", value);`
- Never log inside per-frame loops. Log events: wave started, boss spawned, upgrade bought, file saved, missing asset.
- No `std::cout` or `std::cerr` in new code. `ResourceManager` uses `std::cerr` for missing files; leave it.
- A missing asset must not crash the game. `ResourceManager::GetTextureRef` already returns an empty texture and logs; keep new loaders equally tolerant.
- File I/O (leaderboard) checks every step and falls back to an empty leaderboard on failure.

---

## Memory and Resources

- No `new`/`delete` in new code. `Game` currently holds two `Button*` created with `new`; item 07 changes them to values.
- Load assets once through `ResourceManager`. Do not call `LoadTexture`/`LoadSound` from gameplay code.
- Overlapping copies of one sound: use `LoadSoundAlias(ResourceManager::GetSound(key))` once in an `init()`, and `UnloadSoundAlias` in the matching teardown. Do not `LoadSound` the same file ten times per restart.
- `Animation` keeps a reference to its texture; pass `GetTextureRef(...)`.
- Music streams need `UpdateMusicStream(music)` every frame while playing, from the active scene's `update()`.

---

## Templates

Copy the structure; rename; keep the order.

### Derived enemy (example: `HighLevelEnemy`)

```cpp
// src/HighLevelEnemy.hpp
#pragma once
#include "raylib.h"
#include <string>
#include "Enemy.hpp"

enum ChargerState { CHARGER_APPROACH = 0, CHARGER_WINDUP, CHARGER_CHARGE, CHARGER_RECOVER };

class HighLevelEnemy : public Enemy
{
public:
    HighLevelEnemy(std::string enemyID, Vector2 spawnPos, Vector2 playerPos);
    void update() override;
    void draw() override;
    void destruct() override;

private:
    void fireSpread();

    ChargerState state = CHARGER_APPROACH;
    float stateTimer = 0.0f;
    Vector2 chargeDirection = {0.0f, 0.0f};
};
```

```cpp
// src/HighLevelEnemy.cpp
#include "HighLevelEnemy.hpp"
#include "Animator.hpp"
#include "Balance.hpp"
#include "BulletManager.hpp"
#include "ResourceManager.hpp"
#include "Theme.hpp"
#include "raymath.h"

HighLevelEnemy::HighLevelEnemy(std::string enemyID, Vector2 spawnPos, Vector2 playerPos)
    : Enemy(enemyID, HIGH_LEVEL_ENEMY, spawnPos, playerPos)
{
    health = Balance::HIGH_HEALTH;
    maxHealth = health;
    scoreValue = Balance::HIGH_SCORE;
    scrapValue = Balance::HIGH_SCRAP;
    contactDamage = Balance::HIGH_CONTACT_DAMAGE;
    displayName = "Compactor";

    spriteSize = Balance::HIGH_SPRITE_SIZE;
    origin = {spriteSize / 2.0f, spriteSize / 2.0f};
    speed = Balance::HIGH_APPROACH_SPEED;
    rect = {position.x, position.y, spriteSize, spriteSize};
    hitbox = {position.x, position.y, spriteSize / 3.0f, spriteSize / 3.0f};

    knockbackVelocity = {0.0f, 0.0f};
    knockbackDecay = 0.9f;
    knockbackCooldown = Cooldown(ENEMY_KNOCKBACK_COOLDOWN);

    const Texture2D& sheet = ResourceManager::GetInstance().GetTextureRef("high_level_enemy");
    Animator::GetInstance().AddAnimation(enemyID, std::make_shared<Animation>(
        sheet, sheet.width / Theme::FRAMES_HIGH_ENEMY, sheet.height,
        0.1f, true, rect, false, WHITE));
    Animator::GetInstance().SetOrigin(enemyID, origin);
    Animator::GetInstance().Play(enemyID);
}

void HighLevelEnemy::update()
{
    const float dt = GetFrameTime();
    stateTimer += dt;

    switch (state) {
    case CHARGER_APPROACH:
        // home toward playerPosition; switch to CHARGER_WINDUP when within Balance::HIGH_CHARGE_RANGE
        break;
    case CHARGER_WINDUP:
        // stand still, flash Theme::COLOR_TOXIC; after Balance::HIGH_WINDUP_TIME lock chargeDirection
        break;
    case CHARGER_CHARGE:
        // move along chargeDirection at Balance::HIGH_CHARGE_SPEED, ignore knockback; then fireSpread()
        break;
    case CHARGER_RECOVER:
        // slow drift; back to CHARGER_APPROACH after Balance::HIGH_RECOVER_TIME
        break;
    }

    rotation = atan2f(viewDirection.y, viewDirection.x) * RAD2DEG + 90.0f;
}

void HighLevelEnemy::draw()
{
    rect = {position.x, position.y, spriteSize, spriteSize};
    hitbox.x = rect.x;
    hitbox.y = rect.y;
    Animator::GetInstance().SetPosition(enemyID, position);
    Animator::GetInstance().SetRotation(enemyID, rotation);
}

void HighLevelEnemy::destruct()
{
    Animator::GetInstance().Remove(enemyID);
    const Texture2D& sheet = ResourceManager::GetInstance().GetTextureRef("high_level_enemy_destruct");
    Animator::GetInstance().AddAnimation(enemyID, std::make_shared<Animation>(
        sheet, sheet.width / Theme::FRAMES_HIGH_ENEMY_DESTRUCT, sheet.height,
        0.1f, false, rect, false, WHITE));
    Animator::GetInstance().SetOrigin(enemyID, origin);
    Animator::GetInstance().SetPosition(enemyID, position);
    Animator::GetInstance().SetRotation(enemyID, rotation);
    Animator::GetInstance().Play(enemyID);
}
```

Register the new type in `EnemyManager::spawn()` (one `case` in the type switch) and in the wave tables in `Balance.hpp`.

### Boss subclass (example: `HoarderBoss`)

```cpp
// src/HoarderBoss.hpp
#pragma once
#include "Boss.hpp"

class HoarderBoss : public Boss
{
public:
    HoarderBoss(Vector2 spawnPos, Vector2 playerPos);
    void draw() override;
    void destruct() override;

protected:
    void updatePhase(float dt) override;
    void onPhaseChanged(int newPhase) override;
    std::vector<float> phaseThresholds() const override { return {Balance::HOARDER_PHASE2_AT}; }

private:
    float ringTimer = 0.0f;
    float spawnTimer = 0.0f;
    float ringOffsetDeg = 0.0f;
};
```

`updatePhase` reads `getPhase()` and runs timers that call the base helpers `fireRing`, `fireAimed` and `spawnAdds`. Movement, intro invulnerability and phase switching are in `Boss::update()`, which subclasses do not override.

### Scene (example: `CreditsScene`)

```cpp
// src/CreditsScene.hpp
#pragma once
#include "Scene.hpp"
#include "Button.hpp"

class CreditsScene : public Scene
{
public:
    CreditsScene();
    std::string update() override;
    void draw() override;
    void onSwitch() override;     // reset scroll position, start music
    void onExit() override;       // stop music, Animator::StopAll() if it used animations

private:
    float scrollY = 0.0f;
    Button backButton;
};
```

Register it in `Application::Application()`:

```cpp
m_sceneFactory = {
    {"LoadingScreen", std::make_shared<LoadingScreen>()},
    {"MainMenu",      std::make_shared<MainMenu>()},
    {"Game",          std::make_shared<Game>()},
    {"Credits",       std::make_shared<CreditsScene>()},
};
```

### Run singleton (example: `ScrapManager`)

```cpp
// src/ScrapManager.hpp
#pragma once
#include "raylib.h"
#include <memory>
#include <string>
#include <unordered_map>
#include "ScrapPickup.hpp"

class ScrapManager
{
public:
    static ScrapManager& GetInstance()
    {
        static ScrapManager instance;
        return instance;
    }

    void spawnScrap(Vector2 position, int totalValue);
    void update(Vector2 playerPos, float magnetRadius);
    void draw();
    int collect(Vector2 playerPos, float pickupRadius, int freeCargo);
    void reset();
    int count() const { return static_cast<int>(pickups.size()); }

private:
    ScrapManager() = default;
    std::unordered_map<std::string, std::unique_ptr<ScrapPickup>> pickups;
    int pickupCounter = 0;
};
```

Then add `ScrapManager::GetInstance().reset();` to `Game::resetRun()`.

### Adding a `GameState`

1. Add the value to the enum in `Game.hpp`.
2. Add a `case` in `Game::update()` and the matching overlay in `Game::draw()`.
3. Decide what pauses: `gameTimer.pause()` on entry, `unpause()` on exit.
4. Add the transition to the state diagram in `architecture.md`.
5. Make sure P/Esc pause cannot be entered from states where it makes no sense (game over, docked).

### Adding an asset

1. Put the file in `assets/textures`, `assets/sounds` or `assets/fonts`.
2. Register the key in the matching map in the `ResourceManager` constructor.
3. If it is a sprite sheet, add its frame count to `Theme.hpp` and the sprite table in `ui-rules.md`.
4. Add a row to `assets/ASSETS.md`: file, key, source (team-made, AI tool and model, or licensed), prompt or author, license, date.
5. Reconfigure is not needed for assets; the post-build step copies `assets/`.

### Adding an augment

1. Add the `AUG_` value before `AUG_COUNT` in `Augment.hpp`.
2. Add its row to the info table in `Augment.cpp` (title, two-line description).
3. Add the `case` in `applyAugment()`, calling a `Player` method.
4. Add the number to `Balance.hpp` and a row to `game-design.md`.

### Adding a gear upgrade

1. Add the `GEAR_` value before `GEAR_COUNT`.
2. Add name, description and max level to the table in `UpgradeShop.cpp`.
3. Add its cost table and per-level effect to `Balance.hpp`.
4. Add the `case` in `UpgradeShop::buy()`.
5. Add a row to `game-design.md`.

---

## Comments

- Explain **why**, not what. A threshold gets its reason; a workaround gets a pointer to `library-docs.md`.
- The existing code uses `//?` for explanations and `// TODO` for open work. Keep `//?` if you like it. Do not add new `TODO` comments; put open work in `progress-tracker.md`.
- Section markers `#pragma region` / `#pragma endregion` are fine in long functions (existing style).

---

## Git

- One branch per build-plan item: `feat/11-wave-director`, `fix/animator-double-update`.
- Conventional commit messages: `feat(scrap): magnet pickup and cargo limit`, `fix(game): reset prevGameTimer on restart`, `docs(context): update class registry`.
- Commit the context-file updates in the same commit as the code.
- Never commit `build/`, executables or `leaderboard.txt` (item 01 updates `.gitignore`).
- Merge to `main` only when the item's Done-when checks pass. `main` must always build.

---

## Pull Request / Self-Review Checklist

- [ ] Matches exactly one build-plan item; nothing extra
- [ ] Builds with no new warnings on the reviewer's compiler
- [ ] No inline gameplay numbers, colors or font sizes
- [ ] New classes registered in `class-registry.md`; changed APIs updated there
- [ ] New run state is reset in `Game::resetRun()`
- [ ] Animator IDs unique; destruct animations non-looping
- [ ] No per-frame logging; no `std::cout`
- [ ] No `new`/`delete`, no `rand()`
- [ ] UI inside the safe area; colors from `Theme`
- [ ] New assets have provenance rows
- [ ] `progress-tracker.md` updated, including the AI Usage Log

## Definition of Done (any build-plan item)

- [ ] The item's **Done when** conditions are met
- [ ] The item's **Test** steps pass in a fresh run and after one restart
- [ ] Builds clean from a fresh configure (`cmake -B build -S .` in a new folder) at least once per day
- [ ] Runs at 60 FPS in the item's heaviest scene (check with the F1 overlay)
- [ ] Context files updated
