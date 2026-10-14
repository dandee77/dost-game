# Library Docs

How to use Raylib, raymath, CMake and the compilers correctly in this project, plus every trap already found in the codebase. Training data mixes Raylib 3.x, 4.x and 5.x APIs; this file records what is true for **Raylib 5.5**.

---

## Authority Order

Native Windows input fixture note (P2): arrow-key PostMessage events need their scan code and extended-key bit. Key-up lParam must also carry bits 30/31; merely using WM_KEYUP with a zero lParam can be interpreted as another press/repeat by GLFW. For Down use scan code 0x50 and bit 24; Enter uses scan code 0x1c. PollInputEvents between press/release frames. This is test-fixture behavior, not an application input workaround.

When information conflicts, trust sources in this order:

1. **The installed header.** After the first configure, Raylib's headers are in `build/_deps/raylib-src/src/raylib.h` and `raymath.h` (when CMake fetched it). Search them before using any function you have not used in this repo: if the signature is not there, the function does not exist in this version.
2. **This file.**
3. **The official cheatsheet and examples** for 5.5: https://www.raylib.com/cheatsheet/cheatsheet.html and https://www.raylib.com/examples.html
4. **Training knowledge**, only when nothing above covers it. Say so in the progress notes.

If this file is wrong, fix it in the same commit and note it in `progress-tracker.md`.

---

## Versions

| Tool | Version | Notes |
|---|---|---|
| Raylib | 5.5 | `RAYLIB_VERSION` in `CMakeLists.txt`; `#define RAYLIB_VERSION "5.5"` in `raylib.h` |
| C++ standard | C++20 | `CMAKE_CXX_STANDARD 20` |
| CMake | 3.11 minimum (3.24+ recommended) | `FetchContent_MakeAvailable` |
| MinGW-w64 GCC | record per machine | `g++ --version` |
| MSVC | Visual Studio 2022 | |
| GLSL | `#version 330` | Desktop OpenGL 3.3 |

Record each team machine's compiler version in `progress-tracker.md`.

---

## Build

### First build

```bash
cmake -G "MinGW Makefiles" -B build -S .      # Windows MinGW
cmake -G "Visual Studio 17 2022" -B build -S . # Windows MSVC
cmake -B build -S .                            # Linux/macOS
cmake --build build -j 8
```

The first configure downloads Raylib 5.5 from GitHub into `build/_deps`. It needs internet once. If a machine has Raylib 5.5 installed system-wide, `find_package(raylib 5.5)` uses that instead.

With the Visual Studio generator, the default Debug executable and copied assets are in `build/Debug/`. Run from that folder. On the current Windows machine, CMake is bundled at `C:/Program Files (x86)/Microsoft Visual Studio/2022/BuildTools/Common7/IDE/CommonExtensions/Microsoft/CMake/CMake/bin/cmake.exe` and is not on PATH.

### Release build for the finals

```bash
cmake -G "MinGW Makefiles" -B build-release -S . -DCMAKE_BUILD_TYPE=Release -DGAME_DEBUG=OFF
cmake --build build-release -j 8
# MSVC: cmake --build build-release --config Release
```

Copy the whole output folder (executable plus `assets/`) to the demo laptop. Test it there, from a fresh copy, at least twice before the finals.

### Debug tools build

```bash
cmake -B build -S . -DGAME_DEBUG=ON
```

Item 04 added to `CMakeLists.txt` (default OFF; `build.bat` opts in for local development):

```cmake
option(GAME_DEBUG "Enable debug keys and overlay" OFF)
if (GAME_DEBUG)
    target_compile_definitions(${PROJECT_NAME} PRIVATE GAME_DEBUG)
endif()
```

### Warnings

Item 01 adds:

```cmake
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W3 /wd4244)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra)
endif()
```

(`/wd4244` already exists: it silences float/int conversion warnings from Raylib-style code.)

### Adding source files

`CMakeLists.txt` uses `file(GLOB_RECURSE SOURCES "src/*.cpp")`. A new `.cpp` file is only compiled after **re-running the configure step** (`cmake -B build -S .`). If the linker says "undefined reference" to a class you just wrote, re-run configure.

### CMake traps

| Trap | Fix |
|---|---|
| MSVC error C4576 for `(Vector2){...}` or `(Rectangle){...}` | Use standard C++ `Vector2{...}` / `Rectangle{...}`. Fixed in the item 01 baseline import |
| MSVC unresolved `WinMain` with `WIN32_EXECUTABLE TRUE` and a standard `main()` | Select `/ENTRY:mainCRTStartup` for MSVC while retaining the windowed executable. Fixed in item 01; see [Microsoft entry-point documentation](https://learn.microsoft.com/cpp/build/reference/entry-entry-point-symbol?view=msvc-170) |
| `if (${PLATFORM} STREQUAL "Web")` errors when `PLATFORM` is undefined (happens when Raylib comes from `find_package` instead of `FetchContent`) | Change to `if (PLATFORM STREQUAL "Web")` (item 01) |
| `WIN32_EXECUTABLE TRUE` hides the console on Windows, so `TraceLog` output is invisible | For debugging, run from a terminal on Linux, or temporarily guard the property with `if (WIN32 AND NOT GAME_DEBUG)` (item 04) |
| Assets not found at runtime | Run the executable from the build folder; paths are relative (`assets/...`) and the post-build step copies `assets/` next to the executable |
| Changed an asset but the old one still loads | The post-build copy only runs when the target rebuilds. Touch a `.cpp` or copy `assets/` manually |
| Linux build fails: "RandR headers not found" | `sudo apt install libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libgl1-mesa-dev` |

---

## Raylib 5.5 Patterns Used in This Project

### Collision performance harness (14 October)

The optional `GAME_COLLISION_TESTS` targets keep benchmarks separate from normal game builds. `CollisionBenchmark` wraps the real `Game` scene inside the unchanged `Application` render pipeline (including all 3840 x 2160 passes). It calls `ClearWindowState(FLAG_VSYNC_HINT)` and `SetTargetFPS(0)` only in the harness. Context7 verified the controls against official Raylib docs; local 5.5 `rcore.c` confirms FPS < 1 disables the CPU frame cap. Do not infer capacity from capped `GetFPS()`.

Preserve `Vector2Distance(...) <= radius` for collision compatibility: squared comparisons can round differently at boundaries. Broad-phase bucket bounds are conservative; narrow-phase acceptance and target order remain unchanged. Regression fixtures must preserve the pre-movement bullet phase and post-movement entity phase. See `collision-performance.md` for commands, scenarios, limitations, and results.

All signatures below were checked against the Raylib 5.5 `raylib.h` and `raymath.h`.

### Window, frame and time

```cpp
float dt = GetFrameTime();          // seconds since last frame; use for all movement and timers
double now = GetTime();             // seconds since InitWindow; used by Cooldown and GameTimer
```

### Camera2D and coordinate conversion

```cpp
BeginMode2D(utils::gameCamera);     // world space
    // ...
EndMode2D();                        // back to screen space

Vector2 world  = GetScreenToWorld2D(GetMousePosition(), utils::gameCamera);
Vector2 screen = GetWorldToScreen2D(dock.getPosition(), utils::gameCamera);
```

`camera.offset` is the screen point the target appears at (the canvas center here); `camera.zoom` 20 means one world unit is 20 canvas px.

### Textures and sprite sheets

```cpp
const Texture2D& sheet = ResourceManager::GetInstance().GetTextureRef("mid_level_enemy");
Rectangle src  = {frameIndex * frameW, 0.0f, frameW, frameH};
Rectangle dest = {pos.x, pos.y, sizeW, sizeH};       // dest x,y is the ORIGIN point position
Vector2 origin = {sizeW / 2.0f, sizeH / 2.0f};       // rotate around the center
DrawTexturePro(sheet, src, dest, origin, rotationDegrees, WHITE);
```

- Rotation in `DrawTexturePro` is in **degrees**.
- Flip horizontally with a negative source width (the `Animation` class does this for `flipX`).
- Render textures are upside down: draw them with a negative source height (as `Application::Run` does).

### Text

```cpp
Font font = ResourceManager::GetInstance().GetFont(Theme::FONT_PRIMARY);
Vector2 size = MeasureTextEx(font, text, Theme::TEXT_BODY, Theme::TEXT_SPACING);
DrawTextEx(font, text, Vector2{x - size.x / 2.0f, y}, Theme::TEXT_BODY, Theme::TEXT_SPACING, Theme::COLOR_TEXT);
DrawTextPro(font, text, position, origin, rotationDeg, fontSize, spacing, tint);   // KillCounter wobble
const char* line = TextFormat("CARGO %d/%d", cargo, capacity);                     // static buffer, use immediately
```

`TextFormat` returns a pointer to a static rotating buffer. Do not store it; use it within the same expression or copy it into a `std::string`.

### Shapes for telegraphs and UI

```cpp
DrawCircleLinesV(center, radius, color);                                   // magnet radius (debug), boss range
DrawRing(center, innerR, outerR, startDeg, endDeg, segments, color);        // charge-up rings, boss telegraph
DrawLineEx(start, end, thickness, color);                                  // charge direction preview
DrawRectangleRounded(rect, roundness, segments, color);                    // panels (KillCounter uses this)
DrawRectangleRoundedLinesEx(rect, roundness, segments, lineThick, color);  // 5.5: thickness variant
DrawRectangleLinesEx(rect, lineThick, color);
```

In Raylib 5.5, `DrawRectangleRoundedLines(rect, roundness, segments, color)` has **no** thickness parameter; use `DrawRectangleRoundedLinesEx` when you need one. Older examples online pass a thickness to `DrawRectangleRoundedLines`; that does not compile here.

### Collision helpers

```cpp
CheckCollisionCircles(c1, r1, c2, r2);
CheckCollisionPointCircle(point, center, radius);
CheckCollisionPointRec(point, rect);          // Button hover
```

The existing code uses `Vector2Distance(a, b) <= radius` (target radius only). Keep that in `CollisionSystem` for the moved code so behavior does not change; use `CheckCollisionCircles` for new pairs where both objects have a real size (player vs boss).

### Color helpers

```cpp
Fade(color, 0.5f);         // same as ColorAlpha in 5.5
ColorAlpha(color, 0.5f);
```

### Input

```cpp
IsKeyPressed(KEY_P); IsKeyDown(KEY_W); IsKeyPressedRepeat(KEY_BACKSPACE);
IsMouseButtonDown(MOUSE_BUTTON_LEFT); IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
GetMousePosition();        // already in canvas coordinates here

int ch = GetCharPressed();  // name entry: call in a loop until it returns 0
while (ch > 0) {
    if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || ch == ' ') { /* append uppercase */ }
    ch = GetCharPressed();
}
```

`Button` uses `MOUSE_LEFT_BUTTON`, the older alias. Use `MOUSE_BUTTON_LEFT` in new code.

### Audio

`GetMasterVolume()` and `SetMasterVolume(float)` are available in the installed Raylib 5.5 header and verified against official Raylib docs through Context7. Master volume applies to all music and sound effects, including active playback. For the debug `mute` command, save the current master volume, set it to `0.0f`, then restore the saved value when unmuting; do not stop/restart each sound or change its individual volume. Keep the saved volume in `DebugTools`; Application routes the console before scene updates so every scene shares the same mute state. Repeated `mute on` must not overwrite the saved volume with zero.

```cpp
// Overlapping instances of one sound (gunfire, kills): aliases share the sample data
Sound base = ResourceManager::GetInstance().GetSound("player_shoot");
std::array<Sound, 10> voices;
for (auto& v : voices) v = LoadSoundAlias(base);
// play: first voice where !IsSoundPlaying(v)
// teardown: for (auto& v : voices) UnloadSoundAlias(v);

SetSoundVolume(sound, 0.6f);
SetSoundPitch(sound, 0.95f + GetRandomValue(0, 10) / 100.0f);   // small variation for repeated SFX

Music m = ResourceManager::GetInstance().GetMusic("boss_music");
PlayMusicStream(m);
UpdateMusicStream(m);    // EVERY frame while it plays, or it stutters and stops
StopMusicStream(m);
SetMusicVolume(m, 0.7f);
```

`LoadSoundAlias` and `UnloadSoundAlias` exist in Raylib 5.0 and later. They replace the current pattern of calling `LoadSound` on the same file ten times per restart.

### Files (leaderboard)

```cpp
if (FileExists("leaderboard.txt")) {
    char* text = LoadFileText("leaderboard.txt");   // must be freed
    if (text != nullptr) {
        std::string content(text);
        UnloadFileText(text);
        // parse lines with std::istringstream
    }
}

std::string out = serialize();
bool ok = SaveFileText("leaderboard.txt", out.data());   // 5.5 takes char*, not const char*
```

`SaveFileText` takes a non-const `char*` in 5.5. Pass `out.data()` from a non-const `std::string` (C++17+ returns `char*`). Do not cast away const from a string literal.

### Randomness

```cpp
SetRandomSeed(seed);            // seeds Raylib's GetRandomValue
int v = GetRandomValue(0, 9);   // both bounds inclusive
```

Gameplay randomness uses `RunRng` (a `std::mt19937` wrapper), not `GetRandomValue`, so visual effects cannot shift the wave sequence. See `architecture.md`, Randomness.

### Shaders

```cpp
Shader s = ResourceManager::GetInstance().GetShader("shader");
int loc = GetShaderLocation(s, "time");
SetShaderValue(s, loc, &timeValue, SHADER_UNIFORM_FLOAT);
BeginShaderMode(s); /* draw */ EndShaderMode();
```

Shaders are `#version 330`. If a teammate's laptop shows a black screen, its OpenGL driver may lack 3.3 support; record it in the machine log.

---

## raymath Functions Used

P1 equipment (14 October): Context7 `/raysan5/raylib` verified `DrawTexturePro` source/destination rectangles, origin and degree rotation against the official API. Sprite source padding matters: drawing a full 32×32 zapper frame into a 3-unit-wide destination shrinks the six visible columns to 0.56 units. Crop the visible columns before scaling so the beam matches its collision width. Use direct, ordered draws for modular ship layers; Animator's unordered map cannot guarantee layer order. Rotate up-facing new projectile art by direction angle +90 degrees. Gameplay timers accumulate `GetFrameTime()` only in update; never advance them inside draw or use wall time for pause-sensitive skills. Swept-circle intersections are local math in Bullet::hitFraction, including stationary overlap and tangency.

Native equipment fixtures reuse the existing test-only field exposure. For calls to private methods, `EquipmentTestAccess` is a friend declared in Player/Game/DebugTools and defined only in the test target using normal class declarations. MSVC decorates method symbols with access, so calling an out-of-line private method through `#define private public` directly produces linker errors. No test accessor implementation ships in SpaceAblaze.

All `RMAPI` in `raymath.h`. Angles in raymath are **radians**; Raylib drawing rotation is **degrees**. Convert with `DEG2RAD` and `RAD2DEG`.

| Function | Use |
|---|---|
| `Vector2Add`, `Vector2Subtract`, `Vector2Scale` | Movement |
| `Vector2Length`, `Vector2Distance`, `Vector2Normalize` | Direction, range checks |
| `Vector2Lerp(v1, v2, amount)` | Swarmer steering |
| `Vector2MoveTowards(v, target, maxDistance)` | Player and satellite acceleration |
| `Vector2Rotate(v, angleRadians)` | Bullet fans, boss rings, spawn angles |
| `Vector2ClampValue(v, min, max)` | Limit speed |
| `Vector2Angle`, `Vector2LineAngle` | Angle helpers (check sign conventions before use) |
| `Clamp`, `Lerp`, `Remap` | Scalars |

`Vector2Normalize` of a zero vector returns zero; the existing code guards with `if (Vector2Length(v) == 0.0f) v = {1, 0};`. Keep that guard when a direction can be zero.

---

## C++ Standard Library in Use

| Header | Use |
|---|---|
| `<string>`, `<vector>`, `<array>`, `<unordered_map>`, `<map>`, `<unordered_set>` | Containers (managers use `unordered_map<string, unique_ptr<T>>`) |
| `<memory>` | `std::unique_ptr`, `std::shared_ptr` (Animator stores `shared_ptr<Animation>`) |
| `<random>` | `std::mt19937` in `RunRng` |
| `<algorithm>`, `<cmath>` | `std::max`, `std::sort`, `expf`, `atan2f` |
| `<sstream>` | Leaderboard parsing |
| `<thread>`, `<mutex>`, `<atomic>`, `<queue>`, `<filesystem>` | Only in `ResourceManager` |

No other libraries. Adding one needs a decision in `progress-tracker.md` with a one-line reason.

---

## Known Pitfalls in This Codebase

Each was found by reading the Space Ablaze source. The build-plan item that fixes it is listed; until then, work around it.

| Pitfall | Effect | Fix / item |
|---|---|---|
| `EnemyManager::update` prints the spawn rate with `std::cout` every frame | Slower frames, flooded console | Remove (05) |
| `Animator::Update()` runs in `Game::draw()` **and** in `Game::update()` during `GAME_OVER` | Game-over animations run at double speed | Remove the call in `update()` (05) |
| `Animator::IsCompleted(name)` dereferences `find()` without checking | Crash or undefined behavior if the animation was already erased (completed non-looping animations are erased in `Update()`) | Add `Animator::has(name)`; check before `IsCompleted` (05) |
| `Animator::Draw()` iterates an `unordered_map` | Draw order between animated objects is random and can change when entries are added | Draw bosses directly or add a layer (17) |
| `Game.cpp` file statics `prevGameTimer`, `gameOverTextStarted` | `prevGameTimer` survives restarts | Move into `Game`, reset in `resetRun()` (05) |
| `LoadSound` of the same file 10 times in `Player::init()` and `Game::onSwitch()` without unloading | Memory grows every restart | Sound aliases (05) |
| `Player::takeDamage` always subtracts 10 | Enemy damage values do nothing | Add an amount parameter (08) |
| Health bar width `1000 * health / 100` | Wrong once max health changes | Use max health (08) |
| Augments chosen by comparing card title strings | Renaming a title silently breaks the augment | `AugmentId` (09) |
| Augment trigger `(int)elapsed % 20 == 0` | Tied to time, replaced by wave clears | (11) |
| `GAME_SCREEN_WIDTH/HEIGHT` defined in `Scene.hpp` and again in `Player.cpp`; `Application.cpp` has its own constants | Three sources for one value | `Config.hpp` (03) |
| `MainMenu` returns `"Settings"` and `"Credits"`, which are not registered | Error log, falls back to the menu | Remove Settings; add `CreditsScene` (22, 25) |
| `Game` holds `Button*` created with `new` | Manual memory management | Values (07) |
| `CollisionSystem.*` and `Pause.*` are empty; `SpatialGrid` is unused | Misleading names | Fill (06, 07); leave `SpatialGrid` unused |
| `Cooldown` uses wall-clock `GetTime()` and `isOnCooldown()` ignores pause | Cooldowns elapse while paused or docked | Accepted; do not rely on `Cooldown` for pause-aware timers |
| `Application` calls `DrawFPS` on the real window | FPS counter appears in recorded videos if debug tools are enabled | Fixed (04): guarded with `GAME_DEBUG`; release with the option OFF |
| `rand()` used for augment offers | Not seeded per run | `RunRng` (09) |
| `MainMenu` calls `exit(0)` after the exit animation | Skips cleanup; acceptable for a game | Leave |
| Enemy IDs (`"enemy_" + counter`) are also Animator keys | A second object with the same ID overwrites the first's animation | Use distinct prefixes per kind (`scrap_`, `boss_`) |
| `EnemyManager` removes far enemies with `removeEnemy`, which plays a destruct animation | Harmless (off screen) | Leave |

---

## Patterns Established During the Sprint

### Item 04: collision overlays and debug build gating (14 October 2026)

Verified `DrawCircleLinesV(Vector2 center, float radius, Color color)` and `DrawLineV` with Context7's official Raylib repository documentation and the locally fetched Raylib 5.5 header. Draw collision circles inside `BeginMode2D`; use the exact radii consumed by collision checks (`getHitbox().width`, `getAsteroidSize()`), not visual sprite bounds. Bullets are point collisions, represented by crosses. Draw diagnostics after `EndMode2D` using `Theme` canvas coordinates. `GAME_DEBUG` guards both input/rendering and the player invincibility flag, including its damage early return; disabling the option removes every debug path. Keep `Player::init()` and `DebugTools::reset()` in both reset paths until item 05 consolidates them.

Add a short section here whenever an item establishes a reusable pattern or discovers a new trap. Format:

```
### Item NN: short title (date)
What was verified, where, and the rule that follows from it.
```

### Item 04: F5 console input (14 October 2026)

Verified `GetCharPressed()` and `IsKeyPressedRepeat()` through Context7's official Raylib repository documentation and the installed 5.5 header. Drain the character queue until zero, including unsupported characters. Commands accept ASCII and normalize to lowercase; Backspace handles both first press and repeat. `IsKeyPressed` does not consume a key for other callers: explicitly capture console opening/open/closing frames before gameplay or menu controls. Escape already cannot exit because Application sets `KEY_NULL`. Use `GameTimer::pause/unpause` only if this console paused the timer; preserve existing GameState. Draw into the virtual canvas before the CRT pass and fit long input/output text with `MeasureTextEx`.

P1 loading race fix: decoded texture progress can become 100% between the first upload drain and the completion check. LoadingScreen now drains once more after observing 100% before returning MainMenu. Every counted successful decode enqueues its image before incrementing progress, so the final drain captures all queued equipment sheets.
