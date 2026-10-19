# Context File: Pause Menu, Scrap Economy, Upgrade Progression, Difficulty Modes, Skill-Card Wiring

This file is a **command and specification** for an AI coding assistant. It describes seven changes to the game. Read the whole file before touching code. Where this file conflicts with an older project doc, **this file wins for these seven changes**, and you must update the older doc (see Section 15).

The person who owns this project will re-read this file and change decisions. Every choice I (the file author) had to make is listed in **Section 4 (Decision Register)** with an ID. Follow the stated default unless the owner overrides it in a later message.

---

## 0. Working rules for you (the AI)

1. **Credits are limited.** Do not re-read files you have already read. Do not narrate every step. Read, plan briefly, build, test, report.
2. **Do not stop to ask questions.** If something is ambiguous, use the default in Section 4, and list what you assumed in your final report. Only stop if a requirement is physically impossible in the codebase.
3. **Preserve behavior except for explicit changes below.** Existing tests, the debug console, `--command` / `--skills-list` and benchmark targets must keep working. Update tests for intentional new contracts. The final catalog stays at 32 entries: preserve the 31 retained keys, remove Nano Repair and add `shield-detonation`; old Nano Repair commands must reject without granting healing.
4. **No new dependencies. No generated assets.** Use existing textures, existing sounds and plain Raylib shapes (circles, rectangles, lines, polygons, text) as placeholders.
5. **Every tunable number goes in `Balance.hpp`** and is marked `TUNE`, following the project's existing convention. No magic numbers inside scene or UI code.
6. **Match existing code style.** Read `code-standards.md`, `architecture.md`, `class-registry.md` and `ui-rules.md` first and follow them. If a new class is added, register it in `class-registry.md`.
7. **Build and test both Debug and Release.** No new compiler warnings. Record results in `progress-tracker.md`.
8. **Do not write placeholder logic that fakes a result.** Placeholders are allowed for *visuals and audio only*. Gameplay effects must be real.

### 0.1 Budget limiter and pushed checkpoints (owner request, 19 October 2026)

- Work on one small, independently buildable checkpoint at a time, following Section 5. Estimate its implementation, tests, documentation and Git work before starting. Do not start a checkpoint that cannot reasonably finish within the available budget.
- Reserve at least **25% of the available session token budget (and at least 8,000 tokens when a numeric budget is exposed)** for verification, repairs, documentation, commit and push. Enter checkpoint mode when that reserve is reached, a low-budget warning appears, or there is uncertainty about finishing the next checkpoint. If less than this reserve is initially available, do not start code changes.
- Account credits are not necessarily visible to the assistant. Never invent a remaining credit balance or promise a hard billing cutoff. When no numeric budget is exposed, commit and push after each verified checkpoint instead of waiting for a warning. Keep tool output focused and avoid repeated broad file reads.
- In checkpoint mode, stop adding features. Finish the current coherent change, run the relevant checks, and update `progress-tracker.md` with what is implemented, exact verification results, incomplete requirements, decisions, and the precise next step. Include the AI Usage Log. Do not describe the whole specification as complete when only one checkpoint is done.
- Commit only task-owned files with a conventional message, then push the working feature branch to `origin` (set upstream on the first push). The owner authorizes these checkpoint commits and pushes. Never force-push, discard other contributors' work, or commit generated binaries, build outputs or secrets. Broken/incomplete experiments must not be pushed as working code; use an explicitly documented WIP branch only if preserving them is necessary.
- Before work, inspect the current branch, working tree and remote tracking state. Before pushing, fetch and check for remote divergence. A rejected push is not a successful checkpoint: preserve local commits, resolve routine conflicts while budget permits, and otherwise report the blocker and branch/commit for recovery. Do not silently overwrite remote work.
- Verify the remote branch points to the checkpoint commit and that no task-owned changes remain uncommitted. Report the branch, commit, test status and next step, then **stop for now** when the limiter triggered. On resumption, read the recorded handoff and synchronize that same branch first. Regular pushes reduce lost work and divergence; they cannot guarantee zero merge conflicts or survive an abrupt service cutoff.

---

## 1. Project snapshot (for orientation)

| Item | Value |
|---|---|
| Game | 2D top-down space shooter with roguelike upgrades, swarm-style crowds |
| Engine | C++20, Raylib 5.5, CMake |
| Origin | Built on Space Ablaze (C++/Raylib). Scene classes include `LoadingScreen`, `MainMenu`, `Game` |
| Game states in `Game` | `GAME_RUNNING`, `GAME_AUGMENT_SELECTION`, `GAME_PAUSED` (exists, **no UI yet**), `GAME_OVER`, `GAME_DOCKED` (planned, **not part of this task**) |
| Rendering | 1280x720 window, 3840x2160 scene/CRT/border render passes, zoom 20. HUD must respect the CRT border/safe area. Read how the existing HUD handles this |
| Units | "World units". Existing skill numbers (radius 18, range 65, etc.) are in world units |
| Performance targets | 60 FPS with 80 enemies on screen (project requirement). Collision grid and crowd separation are already optimized: **do not regress them** |
| Deadline | Submission 25 October 2026. Keep scope tight, finish all seven items, polish second |
| Skill system baseline and target | Baseline: 14 augments + 18 abilities and timed cards. Target: 13 augments + 19 abilities = 32 entries, offered by the scrap-progress picker. Check `progress-tracker.md` for implemented checkpoints; this specification describes intended behavior |
| Existing scrap | Minimal scrap pickups already exist: low enemy 2, mid enemy 5, and an "uncapped harvested-scrap counter". The full enemy-drop economy was deferred. **This task builds it** |

---

## 2. Mandatory first step: read and audit (before writing code)

### 2.1 Files to read, in this order
1. `project-overview.md` (controls, screens S-01 to S-11, scope)
2. `architecture.md` and `class-registry.md` (where code lives, how scenes and states work)
3. `code-standards.md` and `ui-rules.md` (style and UI rules)
4. `game-design.md` and `Balance.hpp` (numbers; `Balance::ABILITY_GROWTH` and associated constants)
5. `skills-context.md` and `skills-commands.md` (all 32 skills and their exact behavior)
6. `library-docs.md` (Raylib usage notes, local CMake path)
7. `collision-performance.md` and `crowd-performance.md` (performance baselines and test commands)
8. `progress-tracker.md` (to log results and decisions)
9. Source: `Game` scene (update/draw/state machine/HUD/augment picker/restart), `MainMenu` scene (button style and layout), `EnemyManager`, the enemy destruction path, the scrap pickup code that already exists, the skill manager, the debug console, `Application::Run`, audio code, `tests/SkillChecks.cpp`.

### 2.2 Things you must verify in the code and record in your report
- **Esc and the Raylib exit key.** Raylib closes the window on Esc by default unless `SetExitKey(KEY_NULL)` was called. Confirm what the project does now. After this change Esc must open the pause menu, not close the app.
- **Existing pause.** P and Esc already set `GAME_PAUSED` with no UI. Find that code and extend it; do not create a second pause mechanism.
- **Timers during pause (critical).** `collision-performance.md` says enemy AI cooldowns are **wall-clock** based. If any timer (enemy shooting, spawns, animations, skill cooldowns, scrap lifetime, invulnerability, UI animation) uses wall-clock time such as `GetTime()` instead of accumulated simulation time, it will keep running during pause and enemies will fire instantly on resume. Find every such timer. Fix it with a pause-aware simulation clock or a pause-duration offset **without changing any gameplay number**. This is a must-fix.
- **Where enemies die.** Find the single place where an enemy is destroyed (bullets, rockets, skills, drones, clone, asteroid hits, contact kills). All drops must come from one central function so no path is missed and none double-drops.
- **Existing augment picker trigger.** Find what currently opens `GAME_AUGMENT_SELECTION` (a timer). Section 10 replaces that trigger.
- **How Scrap Magnet is implemented today.** Current behavior is "collects all released scrap anywhere every 0.2 s". Section 7 changes it.
- **The Space Ablaze main menu style** (button look, font, hover/press feedback, sounds, layout). The pause menu must reuse it (Section 6).
- **Existing difficulty or settings code**, if any. `Settings` is linked from the current main menu but does not exist.

---

## 3. Shared definitions (use these words consistently in code and docs)

| Term | Meaning |
|---|---|
| **Run** | One play session from start until death, restart or quit. A new run resets everything below |
| **Scrap pickup** | A world object dropped by a destroyed enemy that the player collects |
| **Scrap total** | Lifetime scrap collected **this run**. Only ever increases during a run. Shown on the HUD (Section 8). This is the existing "harvested-scrap counter", reused |
| **Upgrade progress** | Scrap collected toward the *current* level. Resets to the overflow remainder when a level completes. Shown as a bar (Section 10) |
| **Player level (L)** | Starts at **1** each run. Increases by 1 every time the progress bar fills and an upgrade is taken. Drives both the scrap requirement and enemy toughness |
| **Scrap required for level L** | `required(L)` from Section 10 |
| **Difficulty** | `Easy`, `Hard`, `Impossible`. Chosen before a run starts (Section 11) |
| **Card** | One option in the upgrade picker. May be an augment or an ability |
| **New card** | The player does not have this skill yet |
| **Upgrade card** | The player already has this skill and picking it grants the next level |

---

## 4. Decision Register (recheck these)

Each decision has a default. The owner may override any of them.

| ID | Topic | Default chosen | Why / alternative |
|---|---|---|---|
| D-01 | Meaning of "menu" in item 1 | A small clickable **MENU** button on the HUD (top-right) **and** the Esc key (P also keeps working) | "press the menu or click esc" was ambiguous. Alternative: Esc/P only |
| D-02 | "Quit Game" behavior | Shows a confirmation, then **returns to the main menu** and discards the run | Matches planned screen S-07 ("Resume, quit to menu"). Alternative: close the application entirely |
| D-03 | Settings scope | Minimal panel: **volume sliders** (master; music and SFX only if the audio code already separates them) and a Back button. Optional if trivial: fullscreen toggle | `project-overview.md` lists Settings as out of scope; this task brings back a **minimal** version only. No key rebinding |
| D-04 | Main-menu Settings button | The dead Settings button on the main menu is wired to the **same** Settings panel | Alternative: remove the button as the old doc said |
| D-05 | Scrap Magnet behavior | Changed from "collect everything everywhere" to **radius-based attraction** (Section 7.4) | Needed for "when the player gets near it, it is drawn to them". Alternative: keep global vacuum |
| D-06 | Scrap lifetime | Scrap **does not expire**. A cap with value-preserving merge protects performance | Alternative: expire after about 30 s with a fade |
| D-07 | Scrap value per enemy | Keep existing: **low 2, mid 5**. Does **not** scale with difficulty or level | Harder modes level slower because requirements grow and enemies are tougher |
| D-08 | Timed picker | The old timed trigger is **removed**. Cards now appear only when the progress bar fills (kept behind a debug command for testing) | The owner said upgrades come when the bar fills |
| D-09 | Growth formula | **Compounded**: `required(L) = round(BASE * (1+g)^(L-1))` | Alternative: additive `BASE * (1 + g*(L-1))` |
| D-10 | Base scrap for level 1 | `BASE = 30` for all difficulties | Tunable. Difficulty changes growth, not the starting cost |
| D-11 | Growth rates | Easy **5%**, Hard **10%**, Impossible **15%** | Item 5 mentioned "10 or 20%", item 6 gave 5/10/15. **Item 6 (more specific) wins**. Change in `Balance.hpp` if 20% was intended |
| D-12 | Enemy toughness | Enemy **max HP** multiplier = `HP_BASE[difficulty] * (1+g)^(L-1)` using the same g as D-11. `HP_BASE`: Easy **1.00**, Hard **1.25**, Impossible **1.50** | Easy 1.00 keeps current game balance and keeps existing tests valid. Alternative: no baseline difference |
| D-13 | Enemy damage | A `DAMAGE_BASE[difficulty]` hook exists but defaults to **1.0 for all** (no change yet) | Lets the owner tune later without new code |
| D-14 | Difficulty select default | Nothing preselected the first time. Confirm is disabled until one is chosen. Remember the last choice for the rest of the session | Item 6 says choose and confirm |
| D-15 | Default difficulty when bypassing the menu (debug `--command` launches, tests) | **Easy** | Easy at level 1 equals current balance |
| D-16 | Pause availability | Pause menu opens only in `GAME_RUNNING`. Ignored during card selection, game over, loading, cutscenes, and while the F5 console has input capture | Keeps states simple |
| D-17 | Manual skill activation and quick-swap | **Removed.** There is no player-activated Q slot. All timed skills autocast when their cooldown is ready; persistent skills remain active. The old manual-ability replacement warning is removed. | Keeps the control scheme focused on movement, aiming and survival |
| D-18 | Leaderboard | Not built. The run record stores the difficulty so the future leaderboard can use it | Leaderboard is a separate planned feature |

---

## 5. Recommended implementation order (dependencies matter)

Implement in this order even though the owner listed them differently. Report back using the owner's numbering (Items 1 to 7).

1. Audit (Section 2) and the pause-safe clock fix.
2. Data layer: `Difficulty` enum, difficulty config in `Balance.hpp`, `requiredScrap(L, difficulty)`, enemy HP multiplier function, `RunProgress` state (scrap total, progress, level).
3. **Item 2**: scrap drops, pickups, magnet rework.
4. **Item 3**: HUD scrap total.
5. **Item 5**: progress bar and level-up trigger (replaces the timer).
6. **Item 6**: difficulty select screen, difficulty-scaled requirement and enemy HP.
7. **Item 4**: card description generator.
8. **Item 7**: skill and card audit, weights, placeholders.
9. **Item 1**: pause menu and settings (placed late because it must also freeze the new systems, but see Section 6; it can be built earlier if easier).
10. Debug commands, tests, docs, final report.

---

# 6. ITEM 1: Pause menu

## 6.1 Goal
While playing, Esc, P or clicking the HUD **MENU** button opens a pause menu with **Resume**, **Settings**, **Quit Game**. The game is fully frozen while it is open. It uses the **same visual design as the starting menu's options** (the Space Ablaze main menu buttons).

## 6.2 Behavior
| Situation | Input | Result |
|---|---|---|
| `GAME_RUNNING` | Esc, P or click MENU | Enter `GAME_PAUSED`, show pause menu |
| Pause menu (main page) | Esc, P or click Resume | Resume (see 6.5) |
| Pause menu (main page) | Click Settings | Show Settings page |
| Settings page | Esc or click Back | Return to the pause menu main page (do **not** resume) |
| Pause menu (main page) | Click Quit Game | Show a confirm box: "Quit to main menu? Progress in this run will be lost." with **Quit** and **Cancel** |
| Confirm box | Esc or Cancel | Close the confirm box, stay in pause menu |
| Confirm box | Quit | Reset run state (like scene exit) and go to the main menu |
| `GAME_AUGMENT_SELECTION`, `GAME_OVER`, loading, F5 console capturing input | Esc | Does **not** open the pause menu (D-16). Check how the console uses Esc and do not conflict |

Optional keyboard navigation (Up/Down/Enter) only if the main menu already supports it, so the two stay consistent.

## 6.3 Visual design
- Reuse the main menu's button drawing code, font, colors, hover and press feedback and click sound. **Extract shared drawing into a reusable helper** if the main menu draws buttons inline. Do not copy and paste a second look.
- Dim the frozen gameplay frame behind a semi-transparent dark overlay. Draw a centered panel or just centered buttons, whichever the main menu style suggests.
- Title text "PAUSED". Vertical button order: Resume, Settings, Quit Game.
- Show a small line with the current difficulty (for example "Difficulty: Hard") once difficulty exists.
- The world stays drawn underneath (still frame). HUD may stay visible but dimmed by the overlay.
- Render through the same pipeline the main menu uses so the CRT look is consistent. Respect the CRT border safe area.
- Mouse cursor: use the normal menu cursor while paused; restore the gameplay crosshair on resume if the game uses a custom one.

## 6.4 Settings page (D-03)
- Master volume slider (0 to 100%). Music and SFX sliders only if the audio code already has separate categories.
- Back button.
- Optional if trivial and safe: fullscreen toggle.
- Values live in one `Settings` struct shared by the main menu and the pause menu (D-04). Apply immediately. Persisting to a small file next to the executable is optional; if added, it must fail safely when the file is missing or unwritable.
- No key rebinding. No controller options.

## 6.5 Freeze and resume rules (must be correct)
- While paused **nothing advances**: enemies, bullets, debris, scrap pickups, skills and cooldowns, animations tied to simulation, spawn timers, invulnerability timers, the progress bar fill animation, HUD flash effects, the new scrap pulse effects. This ties to the clock fix in Section 2.2.
- Skills already follow "pause, console capture, card selection and game over do not advance skills". Keep it and add the new systems.
- Pending console casts execute only after simulation resumes (existing rule, keep).
- On resume, **consume the click/press** that triggered Resume so the ship does not fire a shot or select something under the cursor on that same frame. Also ignore a held fire button until it is released and pressed again, or at least do not fire on the resume frame.
- Auto-fire toggle (E), equipped skills, skill cooldown debt, shield state and health all stay exactly as they were.
- Audio: pause or lower gameplay music and silence gameplay SFX while paused if the audio system supports it; menu click sounds still play.
- Restart and quit must clear: pause menu state (page returns to main), skill state, pickups, run progress.
- Window losing focus: auto-pause is **not required**.

## 6.6 Acceptance criteria
- Esc, P and the MENU button open the pause menu in `GAME_RUNNING`; Esc/P/Resume closes it.
- The window does **not** close when pressing Esc.
- A 10 second pause with enemies on screen changes nothing: positions, HP, cooldowns, scrap and bullets are identical at resume (add a test that snapshots and compares).
- No enemy burst-fires on resume (wall-clock bug check).
- Quit Game confirmation works and the next run starts clean.
- Settings volume change is audible/effective and the main menu Settings button opens the same panel (D-04).
- The pause menu does not open during card selection or game over.

---

# 7. ITEM 2: Scrap drops and Scrap Magnet pull

## 7.1 Goal
Defeated enemies drop scrap pickups. The player collects them by flying over them. When the **Scrap Magnet** ability is active, scrap near the player is pulled toward the ship and collected.

## 7.2 Drop rules
- All drops are created in the **one central enemy-destruction path** found in the audit. This covers bullets, rockets, heavy shots, equipment lasers, skill damage, clone and drone fire, asteroid kills and any contact kills. Verify each path with a test. No path may drop twice, and none may be missed.
- Amount: existing values, **low enemy = 2, mid enemy = 5** (D-07). Use a `Balance.hpp` entry per enemy tier so the future tank tier can be added. If the code already has a different per-enemy value, keep that and note it.
- One pickup per kill carrying the full value (not N tiny pickups) for performance. Visual size may scale slightly with value.
- Spawn at the enemy's death position with a small random offset and a short outward drift that slows to a stop (about 0.3 s, TUNE). Use a **separate cosmetic RNG** for scatter. It must **not** consume the gameplay RNG, otherwise the fixed-seed wave guarantee and the existing parity tests break.
- **Exceptions that must be preserved:**
  - **Space Collapse**: enemies erased drop **no scrap**, give **no upgrade progress** (still award score and kill count as documented).
  - **Singularity**: ordinary scrap rewards (already documented).
  - Debris keeps its existing behavior including "pending debris explosions still finish first".
- Scrap is dropped even if the enemy was killed by an ability, as long as that ability is not Space Collapse.

## 7.3 Collection
- Base collection: the pickup is collected when it overlaps the ship's pickup radius (`PICKUP_RADIUS`, TUNE, a little larger than the ship's visual so it feels fair).
- On collection: add the value to **Scrap total** and **Upgrade progress** (Section 10), play a throttled collect sound using an **existing** sound (at most one sound per short window, TUNE, so a crowd of pickups does not spam), and trigger the subtle HUD pulse (Section 8).
- Pickups are frozen while paused, in card selection and on game over.
- Use the existing spatial grid or a similar structure for pickup queries. **No all-pairs checks.** Pre-allocate and reuse storage; no per-frame allocations.

## 7.4 Scrap Magnet rework (D-05)
Current spec: "collects all currently released scrap anywhere every 0.2 s". New spec:

- Scrap Magnet stays an **automatic** ability: **cooldown 15 s, duration 5 s** at level 1 (existing numbers).
- While it is active, every pickup within the **attraction radius** of the ship accelerates toward the ship and is collected on contact.
- Attraction radius level 1: `MAGNET_RADIUS` TUNE (suggested **60 world units**, comparable to other skill ranges such as Hologram lure 60 and Combat Drone range 90; confirm it looks right against the screen scale).
- Pull motion: start slow, accelerate (ease-in). Maximum pull speed must be **greater than the ship's top speed including Thruster Overdrive**, so the player cannot outrun it (for example `max(MAGNET_BASE_SPEED, playerMaxSpeed * 1.25)`; choose and document).
- Pickups outside the radius are not affected. When the magnet effect ends, pickups stop being pulled and keep their last tiny drift to rest.
- Visual placeholder: a faint thin ring of the attraction radius around the ship while active (low alpha, not distracting), plus the pickups visibly sliding toward the ship. Raylib shapes only.
- Level growth (replaces "collection frequency multiplier +0.10"): per additional level **+20% duration, -5% cooldown, +15% attraction radius (stops growing after level 5, per the existing rule), +10% pull speed**. Put in `Balance::ABILITY_GROWTH`.
- Existing rules to keep: unequip cancels effects but keeps cooldown debt, level snapshot per activation, restart clears state.
- Update `skills-commands.md`, `skills-context.md` (Scrap Magnet description), the `skill status` output and the card text accordingly. Update the Scrap Magnet checks in `tests/SkillChecks.cpp`, which currently test the global vacuum.

## 7.5 Performance and caps (D-06)
- Pickups do not expire. Add `MAX_ACTIVE_SCRAP` (TUNE, suggested 400 to 600).
- When the cap is reached, **merge** instead of deleting: combine the **oldest or farthest** pickup into the nearest pickup, **adding its value**, so total scrap value is always preserved. Never silently destroy value. Add a test asserting total value in = total value out under mass kills.
- Stress case to verify: kill about 1,000 enemies at once (for example via Armageddon or `spawn` plus Nuclear Missile) and confirm frame time stays within budget and the cap/merge behaves.

## 7.6 Acceptance criteria
- Killing enemies by every method (except Space Collapse) produces pickups with the correct value; Space Collapse produces none and gives no progress.
- Flying over a pickup collects it; with Scrap Magnet active, pickups within the radius fly to the ship; outside the radius they do not.
- The magnet visibly cannot be outrun.
- Total scrap value is conserved when the cap merges pickups.
- Fixed-seed determinism is unchanged (cosmetic RNG is separate). Existing collision parity tests still pass without edits to their expectations (if a fixture needed to change, explain exactly why).

---

# 8. ITEM 3: Scrap accumulation at the top of the HUD

## 8.1 Goal
Show the **Scrap total** at the top of the screen. It must be noticeable but **not flashy or distracting**.

## 8.2 Layout
- Top **center**, inside the CRT-safe area. Small gold scrap icon (simple Raylib shape such as a diamond or hexagon, or an existing texture) followed by the number.
- The upgrade progress bar (Section 10.4) sits directly beneath it as a thin bar, so the two read as one compact group.
- Do not overlap existing HUD elements (health, active-skill status, MENU button). Read the current HUD and place around it. The MENU button goes top-right.
- Use thousands separators for readability (for example 1,250).
- Palette: gold for scrap, consistent with the project's palette (toxic-green enemies, gold scrap, sky-blue player). Contrast must be readable on the busy background (thin dark outline or soft shadow under the text).

## 8.3 Motion and feedback (keep it tiny)
- The displayed number **counts up smoothly** (a short ease, about 0.2 s) rather than jumping.
- On gain, a very small scale pulse of the icon/number: at most **10% scale**, about **0.15 s**, TUNE.
- An optional small, low-alpha "+N" that aggregates gains over about 0.8 s then fades. **Aggregate, never one popup per pickup.** If it feels busy, leave it out.
- No particles, no screen shake, no glow, no sound beyond the throttled pickup sound.
- All of these timers use the pause-safe simulation clock (they freeze in pause).

## 8.4 Acceptance criteria
- Number is readable at a glance, updates correctly, never lags far behind the true value, and shows the exact true value once settled.
- With 50+ pickups collected rapidly the HUD still looks calm.
- Resets to 0 on restart and new run.

---

# 9. ITEM 4: Fix upgrade card descriptions

## 9.1 Problem
Card text must clearly separate **first-time acquisition** from **upgrading** a skill the player already has.

## 9.2 Rules
**NEW card (skill not owned):**
- A "NEW" badge.
- One short plain-language sentence saying what the skill does (about 12 words or fewer).
- Its **level-1 stats**: activation mode (AUTO or PERSISTENT), cooldown or regeneration timing, duration when applicable, and the key effect numbers (damage, radius, count, range, and so on).
- Any drawback (for example Space Collapse).

**UPGRADE card (skill owned):**
- An "UPGRADE" badge and `Level n -> n+1`.
- **Only the stats that change**, shown as old -> new where useful, for example `Damage 12 -> 15`, `+1 blade (3 -> 4)`, `Cooldown 12.0 s -> 11.4 s`.
- Do **not** repeat the unchanged base description or unchanged stats.
- Only list stats that actually change at that level transition. After level 5, radius, range, distance, length and width **no longer grow**, so they must **not** appear on the card for levels above 5. Counts, damage, health, duration, force and frequency keep growing and are listed. Cooldown uses the additive reduction through level 5 and positive diminishing returns after that, so show the **real computed** old -> new value.

**Persistent augments:** same split. New: what it does and the per-pick amount. Upgrade: `Level n -> n+1 (max 10)` and what this pick adds, plus the running total where it helps (for example "Damage +15% (total +45%)"). Capped augments are not offered.

## 9.3 Single source of truth (mandatory)
Card text must be **generated from the same data and growth functions the gameplay uses** (`Balance.hpp`, `Balance::ABILITY_GROWTH`), never from hand-typed numbers. If a balance number changes, the card changes automatically. Add one function that, given (skill, current level), returns the structured card content (badge, title, sentence, list of stat lines). Put a test on it (Section 14).

## 9.4 Reference data for the generator
These are the **current** values from `skills-commands.md`. Read the live values from code; this table is only for checking your output. "Per level" means additional level, additive relative to level 1, and "(<=L5)" means the stat stops growing after level 5.

| Ability | Mode | Level-1 stats (NEW card) | Per additional level (UPGRADE card) |
|---|---|---|---|
| Laser Rings | PERSISTENT | 3 blades, orbit radius 18, 12 damage per 0.2 s while active | +1 blade; +8% orbit radius (<=L5); +25% damage |
| Deflector Shield | PERSISTENT | 20 shield points orbit the player; fully negates the hit that breaks it; regenerates at 2 points/s; 10 s reactivation delay at level 1 | +5 max shield; +10% regeneration rate; -1 s reactivation delay to a 5 s floor |
| Lightning Ring | AUTO | Radius 25, 8 damage per 0.5 s, 0.6 s stun, 8 s, 14 s cooldown | +10% radius (<=L5); +25% damage; +10% duration |
| Blink Drive | AUTO | Automatically blinks away from the nearest threat, up to 35 distance, 0.25 s protection, 4 s cooldown | +15% distance (<=L5); -10% cooldown |
| Nuclear Missile | AUTO | Automatically targets the densest enemy group; blast radius 55, destroys standard enemies, 250 damage to bosses, 30 s cooldown | +15% radius (<=L5); +30% boss damage; -5% cooldown |
| Space Collapse | AUTO | Automatically targets the densest enemy group; zone radius 32, erases enemies, **no scrap and no upgrade progress**, 35 s cooldown | +1 zone; +15% radius (<=L5) |
| Radiant Halo | AUTO | Automatically fires around the ship; radius 32, 60 damage, 8 s cooldown | +15% radius (<=L5); +30% damage; -5% cooldown |
| Repulsor Pulse | AUTO | Radius 30, push 22, every 5 s | +10% radius (<=L5); +15% push distance; -5% cooldown |
| Point-Defense Interceptor | AUTO | Destroys hostile bullets within radius 38, 8 s, 12 s cooldown | +10% radius (<=L5); +15% duration |
| Scrap Magnet | AUTO | Pulls scrap within radius (Section 7.4), 5 s, 15 s cooldown | +20% duration; -5% cooldown; +15% radius (<=L5); +10% pull speed |
| Chain Lightning | AUTO | Automatically chains to up to 6 nearby targets, 35 damage each, 45 jump range, 7 s cooldown | +1 target; +10% jump range (<=L5); +25% damage |
| Hologram Clone | AUTO | Automatically deploys a decoy for 10 s, lures enemies within 60, copies primary fire, 18 s cooldown | +15% duration; +0.15 firing frequency multiplier; inherits primary weapon damage |
| Combat Drone | AUTO | 1 drone, 30 HP, 15 damage per bolt every 0.4 s, 15 s, 20 s cooldown | +1 drone; +15 HP per drone; +25% shot damage |
| Plasma Beam | AUTO | Automatically aims a cone with range 65 and half-angle 30 degrees, 12 damage per 0.15 s, 4 s duration, 12 s cooldown | +10% range (<=L5); +25% damage; +10% duration |
| Corrosive Trail | AUTO | Pools radius 8 for 3 s, 6 damage per 0.3 s, slows to half speed, 8 s, 14 s cooldown | +15% pool radius (<=L5); +25% damage; +10% emitter duration |
| Singularity | AUTO | Automatically targets the densest group; radius 42, pull speed 28, 10 damage per 0.2 s, 6 s duration, 22 s cooldown | +10% radius (<=L5); +25% damage; +10% duration; +15% pull speed |
| Realm Breaker | AUTO | Automatically aims a rift of length 50 and half-width 6, 20 damage per 0.2 s, absorbs hostile projectiles, 6 s duration, 20 s cooldown | +15% length/width (<=L5); +25% damage; +10% duration |
| Armageddon | AUTO | Automatically selects the densest area for a 6 s barrage, radius 22, 80 damage every 0.3 s, 35 s cooldown | +1 blast per volley; +10% radius (<=L5); +20% damage |
| Shield Detonation | AUTO | When Deflector Shield is destroyed, detonates around the player for 50 damage in radius 35; 18 s internal cooldown | +25% damage; +10% radius (<=L5); -10% internal cooldown |

Special exact cases (use the code's rounding, "round to nearest integer"):
- **Combat Drone** levels 1 to 5: drones 1/2/3/4/5, HP 30/45/60/75/90, shot damage 15/19/23/26/30. Level 6: 6 drones, 105 HP, 34 damage; afterwards +1 drone, +15 HP, +25% of base shot damage per level.
- **Space Collapse** levels 1 to 5: zones 1/2/3/4/5, radii 32/36.8/41.6/46.4/51.2. Level 6 and up: radius stays 51.2 and one more zone per level.

### Skill activation and shield rules

- Manual player activation is removed from normal gameplay. Every timed ability is **AUTO**: it selects a valid target or direction and fires when its cooldown is ready. There is no Q slot, no Q replacement, and no requirement to press a skill key.
- Persistent abilities are always present after acquisition. Orbiting blades and the shield stay centered on the player and update continuously; they do not wait for a cast cooldown. Their level changes apply immediately after an upgrade.
- `Deflector Shield` is a persistent, orbiting shield with a level-1 capacity of 20 shield points. Any incoming hit is fully negated when the shield has any remaining capacity: excess damage is discarded, the player's HP is unchanged, and the hit that breaks the shield never spills through. Shield damage does not create extra scrap, progress or experience.
- While active, the shield regenerates continuously at 2 shield points per second at level 1; the rate increases by 10% per level. After the shield is destroyed, it remains offline for 10 seconds at level 1, reduced by 1 second per level to a minimum of 5 seconds; it then returns at 50% capacity and refills to maximum over 3 seconds. The shield's regeneration and reactivation timers use the pause-safe simulation clock.
- Player HP does not passively regenerate. HP can be restored only at base: the player must enter the base/docking zone after the current encounter is clear, remain there for 3 seconds (`BASE_HEAL_DOCK_TIME`, TUNE), and avoid taking damage or leaving the zone; then HP restores to maximum. `Reinforced Hull` still raises maximum and current HP when selected.
- `Shield Detonation` is a separate AUTO ability, not part of Deflector Shield. If owned and its internal cooldown is ready when the shield breaks, it detonates around the player (35 world-unit radius, 50 damage at level 1). The detonation cannot prevent or change the shield's damage-negation rule; it only damages nearby enemies. If its cooldown is unavailable, the shield still breaks normally and the incoming hit is still fully negated.

Augment facts (read the rest from code): Weapons Payload **+15 percentage points** standard damage per level; Critical Matrix **+5 percentage points** double-damage chance; Reinforced Hull **+20 max and current HP**; Overclocked Chambers **attack cooldown x0.9**; Rapid Fire **+1 shot per burst** (or another pulse for continuous laser equipment). Phase Shift, Thruster Overdrive, Gyro Control, Armor Piercing, Inertia Impact, Scatter Shot, Broadside Cannons and Tail Gunner: take the real per-pick numbers from code and present them the same way. `Nano Repair` is removed from the card pool and replaced by the separate `Shield Detonation` AUTO ability.

## 9.5 Presentation rules
- Order of lines: badge, name, one-sentence description (NEW only), then stat lines. Mode tag AUTO or PERSISTENT beside the name; Shield Detonation additionally states its shield-break trigger.
- Maximum about four to five stat lines. Text must **fit the card**: wrap or shorten, never overflow or clip. Test at the smallest supported window size.
- Do not show a Q-replacement warning: normal gameplay has no manual abilities or Q slot. A debug-only `skill cast` hook may remain for automated tests, but it must not create a player-facing activation mode.
- Space Collapse always shows its drawback line: "Enemies killed drop no scrap".
- Keep the existing exit animation and the rule that a successful pick locks all cards.
- The active-skill indicator and `skill status` must show the same level the card promised.

## 9.6 Acceptance criteria
- A first pick of any of the 32 entries shows its what-it-does sentence and level-1 stats.
- Each repeat pick shows only the changed stats and the correct `n -> n+1`, including levels above 5 (frozen stats hidden) and the Combat Drone / Space Collapse special tables.
- Card numbers match the live gameplay numbers after the pick (test: read the card, apply the pick, read the live stat).

---

# 10. ITEM 5: Scrap progress bar triggers upgrades

## 10.1 Goal
Upgrade cards no longer come on a timer. Collecting scrap fills a **progress bar**. When it is full the player gets an upgrade pick. The requirement grows each level.

## 10.2 Formula (D-09, D-10, D-11)
```
required(L, difficulty) = round( BASE * (1 + g[difficulty]) ^ (L - 1) )
BASE = 30            (BALANCE: SCRAP_BASE_REQUIREMENT, TUNE)
g    = Easy 0.05, Hard 0.10, Impossible 0.15   (BALANCE: SCRAP_GROWTH[difficulty], TUNE)
round = round half up (std::round)
```
Use `double` for the power and clamp the result to a safe integer range. Expected values at BASE 30 (use these as test expectations):

| L | Easy (5%) | Hard (10%) | Impossible (15%) |
|---:|---:|---:|---:|
| 1 | 30 | 30 | 30 |
| 2 | 32 | 33 | 35 |
| 3 | 33 | 36 | 40 |
| 4 | 35 | 40 | 46 |
| 5 | 36 | 44 | 52 |
| 6 | 38 | 48 | 60 |
| 7 | 40 | 53 | 69 |
| 8 | 42 | 58 | 80 |
| 9 | 44 | 64 | 92 |
| 10 | 47 | 71 | 106 |

(Reference: a low enemy gives 2 scrap, a mid enemy 5. At level 1 that is roughly 15 low enemies per upgrade. The owner will tune BASE after playing.)

## 10.3 Flow
1. Each collected pickup adds its value to **Upgrade progress** and to **Scrap total**.
2. When progress >= `required(L)`: subtract `required(L)`, keep the **overflow** (never discard scrap), increment **Player level**, open `GAME_AUGMENT_SELECTION` with three cards.
3. If the overflow is still >= the next requirement (a big pickup or magnet burst), queue another pick. Show picks **one at a time**; after the player chooses, immediately check the queue.
4. The simulation is frozen during card selection (existing rule), so no scrap is collected during it. The magnet and pickups resume afterwards.
5. The first pick of a run comes when the first bar fills (the player starts with no skills).
6. Space Collapse kills add **nothing** to progress.
7. The old timed trigger is removed (D-08). Keep a debug command to force a pick (Section 13).

## 10.4 Bar visuals
- Thin horizontal bar under the Scrap total (Section 8.2). Fill color gold or a distinct accent that still reads on the dark background.
- The fill **eases** toward the true value (short ease, about 0.2 s) rather than snapping.
- Small label: current level, for example `Lv 3`, and optionally `progress/required` in small text. Keep text tiny.
- At the moment of filling, a brief subtle highlight (a quick brightness pulse) before the card screen opens. No flashing, no screen flash.
- Must freeze in pause (pause-safe clock).

## 10.5 Acceptance criteria
- Required scrap per level matches the table for all three difficulties.
- Overflow carries over exactly; no scrap is lost or duplicated; queued picks open one by one.
- Progress and level reset on restart and new run.
- The bar never shows more than 100% or below 0%.
- No upgrade card appears from any timer.

---

# 11. ITEM 6: Difficulty modes (Easy, Hard, Impossible)

## 11.1 Goal
After the player presses the main menu's start/play option, they choose a **difficulty**, confirm it, then the run starts. Difficulty changes how fast the scrap requirement grows and how tough enemies are.

## 11.2 Flow and screen
- Read the current `MainMenu` to see which buttons start a run (the owner says "start or play"; the project plan also lists Story and Endless). **Insert the difficulty step after whichever button starts a run**, for every start path that currently exists.
- New screen (scene or sub-state of `MainMenu`, whichever fits the architecture) in the **same visual style** as the main menu.
- Three selectable options: **Easy**, **Hard**, **Impossible**. Selecting highlights it and shows a short description (for example "Scrap requirement grows 5% per level. Enemies are standard." / "10% per level. Tougher enemies." / "15% per level. Much tougher enemies."). Compute the numbers from `Balance.hpp`, do not hardcode.
- **Confirm/Start** button, **disabled until a difficulty is chosen** (D-14). **Back** returns to the main menu.
- The choice is stored in the run state and never changes mid-run. Restart keeps the same difficulty. Quit to menu and starting again asks again.
- Display the current difficulty name in the pause menu and game over screen. Store it in the run record (D-18).

## 11.3 What difficulty changes (D-11, D-12, D-13)
**1. Scrap requirement growth** (Section 10.2): Easy 5%, Hard 10%, Impossible 15% per level.

**2. Enemy toughness (max HP)**, applied **when an enemy spawns**:
```
hpMultiplier(L, difficulty) = HP_BASE[difficulty] * (1 + g[difficulty]) ^ (L - 1)
HP_BASE = Easy 1.00, Hard 1.25, Impossible 1.50     (BALANCE, TUNE)
```
- `L` is the Player level at spawn time. Enemies already alive keep their HP.
- Apply to every enemy tier and the future boss HP hook (bosses are not built yet; do not invent them).
- Apply the multiplier to max HP and current HP together and round to a sensible integer, minimum 1. Clamp the multiplier to a safe upper bound (for example 50x) purely to avoid overflow, and document the clamp.
- **Enemy damage hook:** `DAMAGE_BASE[difficulty]`, default 1.0 for all three (D-13). Wire it into enemy contact and bullet damage so the owner can tune it later, but do not change any damage number now.
- Do **not** change enemy speed, spawn counts, hitboxes, scrap values or any other existing value.

**Effect on skills:** "destroys regardless of HP" (Nuclear Missile on standard enemies) and "erases" (Space Collapse) must still work at any HP. Fixed-damage skills get relatively weaker on higher difficulties and higher levels, which is intended.

## 11.4 Compatibility
- Easy at level 1 gives multiplier 1.0 and growth 0, so **existing tests and benchmarks behave exactly as before**. Tests and `--command` launches default to Easy (D-15).
- Fixture enemies in benchmarks are given high HP; make sure the scaling does not run on top of fixtures in a way that changes them (apply at the spawn function, not in fixture setup).

## 11.5 Acceptance criteria
- The difficulty screen appears after pressing start/play, cannot be skipped, and Confirm stays disabled until a choice is made.
- Each difficulty uses its own growth rate for the scrap requirement and for enemy HP (verify with the numbers in Section 10.2 and a few computed HP values).
- Enemies spawned later in a run are tougher than earlier ones on the same difficulty; enemies spawned at the same level are tougher on Hard than Easy, and on Impossible than Hard.
- Restart keeps difficulty; quit and re-enter asks again.

---

# 12. ITEM 7: Connect skills to the upgrade cards

## 12.1 Status check first
`skills-commands.md` says the existing picker already offers all 32 entries and repeat picks already upgrade abilities. So this item is mostly **verify, fix gaps, and finish placeholder visuals**, not rebuild. Do the audit below and fix whatever fails.

## 12.2 Audit checklist (record the result for each of the 32 in your report)
For every augment and every ability confirm all of these:
1. It can appear as a card through the new progress-bar trigger (not only through the old timer or debug commands).
2. Picking it applies the **real gameplay effect** (not just a stat flag).
3. AUTO abilities start running by themselves when their cooldown is ready; persistent abilities remain active and orbit the player. No ability requires manual activation.
4. A repeat pick grants the next level and the live numbers match the card text (Section 9).
5. It has a **placeholder visual** so the player can see it working: use Raylib shapes (rings, beams, circles, lines, translucent fills) and existing textures. Examples: orbiting blades as small rotating rectangles, shield as a translucent circle, magnet ring as a faint circle, drones as small ships using an existing texture tinted. No new asset files.
6. It does not crash when paused, resumed, restarted, or quit to menu mid-effect.
7. It behaves at 30 and 144 FPS the same (existing parity rule).

If a skill fails an item, fix it. If a fix would change a documented balance number, do not change the number; report it instead.

## 12.3 Card pool selection ("use the skills you think are useful in this situation")
The owner wants **you** to use judgment about which skills suit this new scrap-driven loop. Apply these rules:

- All 32 final entries stay reachable: Nano Repair is explicitly replaced by Shield Detonation. Do not remove any other skill.
- You may add **weights** (TUNE in `Balance.hpp`) so the pool favors skills that make sense in a scrap-and-survive loop, and documents why. Suggested thinking, adjust if you disagree and explain:
  - **Scrap Magnet** becomes valuable because leveling is now scrap-driven. It should appear reasonably often early on.
  - **Space Collapse** is anti-synergistic (no scrap, no progress). Keep it available but not heavily weighted; its card already warns about the drawback.
  - Crowd clearers (Radiant Halo, Lightning Ring, Laser Rings, Chain Lightning, Repulsor Pulse) and survivability (Deflector Shield, Shield Detonation, Reinforced Hull) are good early picks for a swarm game.
  - Very strong skills (Nuclear Missile, Armageddon) can have lower weight.
- Keep the existing pool rules: up to three **distinct** cards, capped persistent augments excluded, AUTO/persistent abilities eligible beyond level 5. Offer Shield Detonation only after Deflector Shield is owned, and keep offering repeat picks to upgrade it. Use the seeded or cosmetic RNG consistently with how the picker already chooses (do not consume gameplay RNG in a way that changes wave determinism; check how the picker does it now and follow it).
- Report which skills you boosted or reduced and why, in two or three lines.

## 12.4 Acceptance criteria
- Every one of the 32 entries can be obtained through normal play via the progress bar, works, shows a visual, and upgrades correctly.
- `--skills-list` still prints all 32 keys; console commands still work.

---

# 13. Debug and console additions (debug builds only, `GAME_DEBUG=ON`)

Add to the F5 console (with autocomplete) and to `--command` where appropriate. Debug-disabled builds must continue to reject `--command` with exit code 1 as today.

```text
scrap add <n>            # add n scrap as if collected (affects total and progress)
scrap spawn <n>          # drop n pickups near the cursor/ship to test the magnet
scrap status             # print total, progress, required, level, active pickup count
level set <n>            # set player level (updates requirement and future enemy HP)
progress fill            # fill the bar and trigger the card pick
difficulty <easy|hard|impossible>   # set difficulty for the current run
```
- `difficulty` and `level set` only affect future spawns and the next requirement; they must not rewrite existing enemies.
- Keep the existing commands (`augment`, `skill equip/upgrade/unequip/status/list`, `spawn`, `invincible`) working and in autocomplete. If the legacy `skill cast` command remains for harness compatibility, it is debug-only and does not restore manual activation in normal play.

---

# 14. Tests (extend the existing native harness; run Debug and Release)

Use the existing `GAME_EQUIPMENT_TESTS` target (`tests/SkillChecks.cpp`) and add a new file such as `tests/ProgressionChecks.cpp` registered the same way if it keeps things clean. Also run the collision and crowd tests unchanged.

Required checks:
1. **Requirement table:** `required(L, difficulty)` equals Section 10.2 for L 1 to 10 on all three difficulties.
2. **Enemy HP multiplier:** correct for each difficulty at several levels; Easy at L1 equals 1.0.
3. **Drops:** every kill path produces the right pickup (low 2, mid 5), exactly once; Space Collapse produces none and no progress; Singularity produces normal rewards.
4. **Cosmetic RNG isolation:** fixed-seed gameplay results are identical with and without drops enabled.
5. **Collection:** touch collection, magnet radius inside/outside, pull speed exceeds ship speed, state after magnet expiry.
6. **Value conservation:** total value is preserved through the cap/merge under mass kills.
7. **Progress:** overflow carry, queued multiple level-ups, no progress during selection or pause, reset on restart.
8. **Timer trigger removed:** no card opens by time.
9. **Pause:** a 10 s pause leaves all state byte-identical (enemies, bullets, pickups, skills, cooldowns, bar, HUD timers); no enemy fires on resume; resume click is consumed; Esc does not close the window; menu navigation via native input events (follow the style of the earlier restart-button test); settings volume applies.
10. **Card text:** for all 32 entries, NEW and UPGRADE content for levels 1 to 8 and 12; frozen stats absent after level 5; Combat Drone and Space Collapse special tables; no Q-replacement warning; text fits the card box.
11. **Difficulty screen:** Confirm disabled until selection; selection persists on restart; quit and re-enter asks again.
12. **Skills:** all 32 reachable through the new flow; Scrap Magnet checks rewritten for the radius behavior; existing skill checks still pass; 30/144 FPS damage parity still holds.
13. **Performance:** run the 80-enemy case and the existing benchmark commands from `collision-performance.md` and `crowd-performance.md` and confirm no regression. Add one mass-kill stress check (Section 7.5).

Native screenshots to inspect and keep with the other test captures: pause menu, settings page, difficulty screen, HUD with scrap and bar, a NEW card and an UPGRADE card for the same skill.

Record all build/test results and benchmark numbers in `progress-tracker.md`.

---

# 15. Documents to update (keep them truthful)

- `project-overview.md`: controls table (MENU button, Esc/P behavior), screens table (S-07 now has UI; a difficulty-select screen added; Settings now a minimal panel), scope lists (Settings moved from out of scope to a minimal version), core loop note that scrap now drives upgrade progress in this build and the cargo/dock/credits loop is still deferred.
- `game-design.md` and `Balance.hpp` comments: scrap base requirement, growth per difficulty, HP baselines, damage hook, pickup radius, magnet values, caps, card weights.
- `skills-commands.md`: new Scrap Magnet behavior, new card text rules, new console commands, removed timed trigger.
- `skills-context.md`: Scrap Magnet description; changelog row dated 19 Oct 2026.
- `class-registry.md`: any new classes (for example pause menu, difficulty select, scrap pickup manager, run progress, card text generator).
- `ui-rules.md`: pause menu, difficulty screen, HUD scrap and bar rules.
- `progress-tracker.md`: task log, test and benchmark results, assumptions, any open questions.

---

# 16. Guardrails

- **Determinism:** gameplay RNG stays untouched; cosmetic randomness uses its own stream. Wave composition for a given seed must not change.
- **Frame-rate independence:** all new movement, easing and timers scale with simulation delta time (tested at 30/60/144 FPS).
- **Performance:** no per-frame heap allocations in pickup update, HUD or card code. Reuse storage. No O(n^2) pickup/enemy loops.
- **Order of update inside a frame** must remain consistent with the existing manager update order; document where pickups update relative to enemies and skills.
- **Reset completeness:** restart and quit must reset enemies, bullets, pickups, scrap total, progress, level, skills, augments, queued picks, pause menu page, HUD effect timers.
- **Input:** while any menu or card screen is open, game input (shoot, move, skill activation) must not leak through.
- **Debug-only code** stays behind `GAME_DEBUG`.

---

# 17. Out of scope for this task (do not build)

Cargo limit, dock, dock shop, credits, deposit, waves and bosses, cutscenes, leaderboard, key rebinding, controller support, save games, online features, new art/music/sfx files, manual skill activation or a Q quick-swap system, new enemy types. Only wire the hooks described here (difficulty stored in the run record, HP hook for future bosses).

---

# 18. Final report format (keep it short)

1. Per Item 1 to 7: done / partial / not done, with one or two lines each.
2. List of decisions you used from Section 4, and any you changed and why.
3. Audit findings: Esc exit key, wall-clock timers found and fixed, central kill path location, Scrap Magnet old vs new.
4. The 32-skill audit table (reachable, effect real, visual, upgrades OK).
5. Card pool weights you chose and why.
6. Files changed or added.
7. Build and test results (Debug and Release), benchmark comparison, screenshots produced.
8. Known issues and anything the owner should tune first (BASE, growth, HP_BASE, magnet radius, pickup radius).

---

# 19. Final self-check before you report

- [ ] Esc/P/MENU open the pause menu; Resume, Settings, Quit Game work; styled like the main menu; nothing advances while paused; no resume click leak.
- [ ] Wall-clock timers audited and fixed; no burst fire after pause.
- [ ] Enemies drop scrap from every kill path except Space Collapse; magnet radius pull works and cannot be outrun; value conserved at the cap.
- [ ] Scrap total at top center, calm and readable; bar beneath it.
- [ ] Card text: NEW shows what it does and level-1 stats; UPGRADE shows only added stats; generated from live data; frozen stats hidden after level 5.
- [ ] Progress bar triggers picks; overflow carries; queued picks one at a time; no timer picks.
- [ ] Difficulty screen with disabled Confirm until chosen; 5/10/15% requirement growth; enemy HP scaling with baselines; Easy L1 identical to old balance.
- [ ] All 32 skills reachable, working, visible with placeholders, upgrading correctly.
- [ ] Debug commands added; `--skills-list` and `--command` still work.
- [ ] Debug and Release builds clean; all tests pass; no performance regression; docs updated.
