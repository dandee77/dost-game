# AGENTS.md

You are working on a 2D space shooter written in **C++20 with Raylib 5.5**, built on top of the Space Ablaze codebase, for the **DOST Level Up 3.0 Esports Game Dev Challenge** (Philippines). The submission deadline is **25 October 2026**. Every session is part of an 11-day sprint, so scope discipline matters more than cleverness.

Read this file first, then follow the read order below before you write any code.

---

## Read Order

| When | Read |
|---|---|
| Every session | `context/project-overview.md`, `context/progress-tracker.md` (Current Status), the current item in `context/build-plan.md` |
| Before touching any class | `context/class-registry.md` (find the class, its owner, its gotchas) |
| Before writing code | `context/code-standards.md` and the matching template in it |
| Before using a Raylib function you have not used in this repo | `context/library-docs.md` |
| Before drawing anything on screen | `context/ui-rules.md` |
| Before changing any gameplay number | `context/game-design.md` |
| Before changing how systems connect | `context/architecture.md` |

If two files disagree: `project-overview.md` wins on **what** to build, `architecture.md` wins on **how** systems connect, `game-design.md` wins on **numbers**, `code-standards.md` wins on **style**. Record the conflict in `progress-tracker.md` under Open Questions.

---

## Golden Rules

1. **One build-plan item at a time.** Build only what the current item says. No "while I'm here" refactors, no new features, no new libraries.
2. **Check the class registry before creating a class.** If a class already does the job, use it or extend it. Never create a second class that does the same thing.
3. **OOP by inheritance from existing bases.** New enemies derive from `Enemy`, bosses from `Boss`, screens from `Scene`, cutscenes from `Cutscene`, world objects from `Entity`. Declare the base first, then the derived class.
4. **No magic numbers.** Gameplay numbers go in `src/Balance.hpp`, colors, fonts and UI sizes go in `src/Theme.hpp`, engine constants go in `src/Config.hpp`. If the value is not there, add it there first.
5. **The build must pass after every change.** Run the build command below. Zero new warnings.
6. **Every run-state singleton must reset.** If you add state to a singleton, add its `reset()` call to `Game::resetRun()`. A restart that leaks old enemies or scrap is a bug.
7. **IDs are also Animator keys.** Anything drawn through `Animator` needs a unique string ID (`enemy_12`, `boss_hoarder`, `scrap_40`). Reusing an ID overwrites another object's animation.
8. **Frame-rate independence.** Every movement, timer and lerp uses `GetFrameTime()`.
9. **No per-frame logging.** Use `TraceLog()` for events only, never inside an update loop.
10. **Assets are swapped, not re-coded.** A reskinned sprite keeps the same frame size and frame count as the file it replaces (see the sprite table in `ui-rules.md`). Every new asset gets a provenance row in `assets/ASSETS.md`.
11. **Disclose AI use.** After each item, add a row to the AI Usage Log in `progress-tracker.md`. The competition requires this (Form 03) and organizers may ask for logs.
12. **Update the docs in the same commit.** New class: `class-registry.md`. Finished item: `progress-tracker.md`. New pattern or Raylib trap: `library-docs.md`.

Repository AI workflows live in `.agents/skills/`. Codex discovers these skills after a clone or pull; use the relevant skill when its description matches the task.

---

## Commands

```bash
# Configure once (Windows, MinGW)
cmake -G "MinGW Makefiles" -B build -S .
# Configure once (Windows, Visual Studio 2022)
cmake -G "Visual Studio 17 2022" -B build -S .
# Configure once (Linux/macOS)
cmake -B build -S .

# Build (every change)
cmake --build build -j 8

# Run (from the folder that contains the assets/ copy)
cd build && ./SpaceAblaze        # Linux/macOS
cd build && SpaceAblaze.exe      # Windows
```

The executable must run from the build folder because asset paths are relative (`assets/...`). The post-build step copies `assets/` next to the executable.

---

## Workflow for Each Build-Plan Item

1. Read the item in `build-plan.md`. Note its **Classes**, **Done when** and **Test** lines.
2. Look up every class it touches in `class-registry.md`.
3. Make the change, following the matching template in `code-standards.md`.
4. Build. Fix every error and new warning.
5. Run the game and perform the item's **Test** steps. Use the F5 debug console commands (see `architecture.md`) to reach the state quickly.
6. Update `class-registry.md`, `progress-tracker.md` (status, decisions, AI usage) and any other context file the item changed.
7. Commit with a conventional message: `feat(waves): wave director with budgets`.

---

## Never

- Never edit gameplay numbers inline. Use `Balance.hpp`.
- Never use `new`/`delete` in new code. Use values or `std::unique_ptr`.
- Never switch on a string to decide behavior (the old augment code does this; it is being replaced).
- Never switch scenes to show the dock shop, pause or game over. Those are `GameState`s inside `Game`; switching scenes resets the run.
- Never call `Animator::GetInstance().Update()` more than once per frame.
- Never put UI text near the screen edge. The CRT shader curves and crops the edges (safe area in `ui-rules.md`).
- Never add third-party art, music or fonts without a license recorded in `assets/ASSETS.md`.
- Never name a real brand, company, person, game or movie in game content or AI asset prompts.
