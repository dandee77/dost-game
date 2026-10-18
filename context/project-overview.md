# Project Overview

Read this file first in every session. It defines what the game is, why it exists, how it plays, which screens exist, and what is in and out of scope for the submission. For technical questions, `architecture.md` wins. For numbers, `game-design.md` wins.

---

## About the Project

A 2D top-down space shooter with roguelike upgrades, built for the **DOST Level Up 3.0 Esports Game Dev Challenge** (Department of Science and Technology, Philippines). The finals are the Game Demonstration and Judging Day on 26 to 27 November 2026 at GMall of GenSan, General Santos City, during National Science and Technology Week.

The game is built on top of **Space Ablaze**, a C++/Raylib shooter previously made by a team member. Space Ablaze already has the ship, shooting, two enemy types, debris, augment cards, a CRT shader and menus. This project changes its theme and adds the scrap economy, the dock, bosses, cutscenes and an endless mode.

| Item | Value |
|---|---|
| Working title | TBD. Refer to it as "the game" until the team decides; record the title in `progress-tracker.md` |
| Engine | C++20, Raylib 5.5, CMake |
| Platform | Windows PC (primary, used at the finals), Linux and macOS builds also work |
| Category | Student or Professional (record in `progress-tracker.md`) |
| Themes claimed | Climate Change (primary), Circular Economy (secondary) |
| Gameplay type | Player-versus-Environment with leaderboards |
| Submission deadline | 25 October 2026 |
| Finals | 26 to 27 November 2026 |

### Team

Fill in names. Maximum five members (plus one coach in the Student category).

| Role | Name | Focus |
|---|---|---|
| Lead / Gameplay programmer | | Core loop, waves, scrap, dock |
| Programmer | | Enemies, bosses, collisions |
| Programmer | | UI, dock shop, cutscenes, leaderboard |
| Art and audio | | AI-assisted sprites, music, SFX, `assets/ASSETS.md` |
| Producer | | Forms 01 to 03, synopsis, trailer, gameplay video |
| Coach (student category) | | Mentorship only |

---

## The Pitch

Climate change is usually discussed as something happening on the ground and in the lower atmosphere. The game points at a less visible source: the junk humanity leaves in orbit.

The pitch must stay scientifically honest because the judges are from a science department. Keep the claim narrow:

- Satellites burning up on reentry release aluminum oxide particles that can linger in the upper atmosphere for decades and may deplete ozone ([AGU, Geophysical Research Letters, 2024](https://agupubs.onlinelibrary.wiley.com/doi/10.1029/2024GL109280)).
- Studies are modeling how reentry aluminum oxide accumulates in the stratosphere and affects upper-atmosphere temperatures ([NOAA repository](https://repository.library.noaa.gov/view/noaa/71517)).
- Rocket launch soot (black carbon) warms the upper atmosphere far more efficiently than soot from ground sources.

Do **not** claim that space junk is a major driver of global warming. Say it is an emerging, under-studied contributor, and that orbit is part of the environment we are responsible for.

**Circular Economy angle:** every enemy is junk. Destroying it yields scrap, scrap is recycled at the dock into better gear, and better gear clears more junk. The core loop is a recycling loop.

---

## Story

All names below are working names. The team may rename them; record changes in `progress-tracker.md`.

**Intro cutscene (skippable, about 40 seconds):**

1. Earth is dying. Smog over the cities, the seas rising.
2. Above it, an orbit choked with dead satellites, rocket stages and debris.
3. As a last resort, humanity detonates an experimental cleansing chemical in orbit to dissolve the junk.
4. It goes wrong. The chemical fuses with the debris and the radiation around it. The junk mutates and turns hostile.
5. The surface becomes uninhabitable. The last humans live on **Bayanihan Dock**, a giant orbital station.
6. Scientists find a seed that can still regrow life on Earth: the **World Tree** (a Narra seed). It can only be planted once the orbit is clean.
7. You are a **Collector**, one of the dock's garbage-collection pilots. Clear the orbit. Bring back the scrap. Find the source.

**Midpoint (wave 5):** The Hoarder, a giant mass of fused junk, guards the inner orbit.

**Final boss (wave 10):** The Core, the biggest piece of junk, which absorbed the heart of the failed chemical. Destroying it stops the contamination.

**Ending cutscene:** The orbit clears. A shuttle carries the World Tree seed down. The seed takes root and green spreads across the planet. Endless mode unlocks with the message that the junk keeps coming and someone has to keep collecting.

---

## Game Modes

| Mode | Goal | Ends when | Leaderboard ranks by |
|---|---|---|---|
| **Story** | Clear 10 waves; defeat The Hoarder (wave 5) and The Core (wave 10) | The Core is destroyed (victory) or the player dies | Score, then clear time |
| **Endless** | Survive as many waves as possible | The player dies | Score, then waves cleared |

Both modes use a fixed seed for wave composition so every player faces the same waves (fair competition, Esports Potential criterion). Endless is available from the start so judges can play it without finishing Story.

---

## Core Loop

```
Launch from the dock
  -> Wave starts: contaminated junk spawns around the player
  -> Shoot enemies; they explode and drop scrap
  -> Fly over scrap to collect it (cargo hold has a limit)
  -> Wave cleared: pick 1 of 3 augment cards (free, random)
  -> "Return to dock" phase: an arrow points home, no enemies spawn
  -> Dock: scrap is deposited and converted to credits
  -> Dock shop: spend credits on gear upgrades, repair the hull
  -> Launch -> next wave (harder; boss every 5 waves)
```

**Risk and reward:** scrap you are carrying is lost if you die. Scrap only becomes credits at the dock.

---

## Controls

| Input | Action |
|---|---|
| W A S D | Move (8 directions) |
| Mouse | Aim (the ship turns toward the cursor) |
| Left mouse button | Shoot |
| E | Toggle auto-fire |
| P or Esc | Pause |
| Mouse click | Menus, augment cards, shop |
| Space / Enter / click | Skip cutscene slide |
| F5 | Debug console with autocomplete, debug builds only (see `architecture.md`) |

---

## Screens

Screen IDs are used in `build-plan.md`, `ui-rules.md` and `class-registry.md`.

| ID | Screen | Implemented as | Purpose |
|---|---|---|---|
| S-01 | Loading | `LoadingScreen` scene (exists) | Load textures with a progress readout |
| S-02 | Intro cutscene | `IntroCutscene` scene (planned) | Story slides, skippable; shown once per launch before the menu |
| S-03 | Main menu | `MainMenu` scene (exists, modified) | Story, Endless, Leaderboard, Credits, Exit |
| S-04 | Gameplay HUD | `Game` scene, `GAME_RUNNING` | Health, cargo, credits, wave, timer, boss bar, dock arrow |
| S-05 | Augment pick | `Game`, `GAME_AUGMENT_SELECTION` (exists) | Choose 1 of 3 cards after each wave |
| S-06 | Dock shop | `Game`, `GAME_DOCKED` (planned) | Deposit scrap, buy gear, repair, launch |
| S-07 | Pause | `Game`, `GAME_PAUSED` (exists, no UI yet) | Resume, quit to menu |
| S-08 | Game over | `Game`, `GAME_OVER` (exists, modified) | Stats, name entry if on the leaderboard, restart, menu |
| S-09 | Ending cutscene | `EndingCutscene` scene (planned) | Story victory |
| S-10 | Leaderboard | `LeaderboardScene` (planned) | Top 10 per mode |
| S-11 | Credits | `CreditsScene` (planned) | Team, tools, AI disclosure, asset licenses |

`Settings` is linked from the current menu but does not exist. Remove the button (out of scope).

---

## Features In Scope (submission, 25 October)

- Story mode with 10 waves, 2 bosses, intro and ending cutscenes
- Endless mode with scaling waves and repeating bosses
- Three enemy tiers with Space Ablaze behaviors (homing swarmer, strafing shooter, new charging tank) reskinned as contaminated junk
- Debris hazards (the current debris, reskinned)
- Scrap drops, magnet pickup, cargo limit, deposit at the dock
- Dock shop with 7 gear upgrades (5 levels each) and a hull repair
- Fourteen augments and eighteen abilities from `skills-context.md` (P5). The 18 October user-requested extension adds abilities to the existing timed cards, with five repeat-pick levels and individual scaling. Shop/drop/inventory wiring remains deferred; timed cards remain until waves are implemented.
- Local leaderboard per mode with name entry
- In-game tutorial prompts for the first wave
- Credits screen with AI and asset disclosure
- All art and audio original (team-made or AI-generated) with provenance recorded
- Debug console and overlay for testing and recording the videos

## Features Out of Scope

- Online leaderboards or networking
- Multiplayer (the rules allow PVE with leaderboards)
- Settings screen (volume, key rebinding)
- Controller support
- Save games mid-run
- Mobile or web builds
- Localization (English in game; Filipino words used as names and flavor only)

## After Submission (before the 26 November finals)

Only after the 25 October submission: polish pass, extra augment and upgrade options, a third boss phase, better VFX, settings screen, Filipino voice lines, balance from playtests. Track these under "Finals Backlog" in `build-plan.md`.

---

## Submission Requirements (from the official mechanics)

| Requirement | Owner | Notes |
|---|---|---|
| Registration via the official link, before submitting | Producer | Must happen first |
| Form 01: Team roles | Producer | Names, roles |
| Form 02: Waiver and Declaration of Originality | All members sign | Declares code and assets are original or licensed |
| Form 03: Asset and AI Usage Disclosure | Producer, from `progress-tracker.md` AI Usage Log and `assets/ASSETS.md` | Required: the game uses AI-generated assets |
| Template 01: Title and synopsis, max 500 words | Producer | Include mechanics and the theme link |
| Game trailer, 1 to 2 min, .mp4 | Producer, art | Plays on loop at events |
| Gameplay demo video, 3 to 5 min, .mp4 | Producer | Voice-over or captions explaining the game |
| Playable build on the demo laptop for the finals | Lead | Test on the actual machine |

Pre-screening is judged on the submitted materials, mainly the videos. The criteria are Completeness, Theme Relevance, Originality, Gameplay, and Aesthetics and Creativity, 20% each.

### Code originality rule (important)

Rule 7 says the source code must not contain code from games previously published or submitted to **any other competition**. Personal code may be reused only if it was never part of a previously published or submitted game, and must be declared. The Space Ablaze main menu shows "Equity Quest - 2024". If Space Ablaze was entered in a competition, reusing its code is a disqualification risk. This is Open Question 1 in `progress-tracker.md` and must be resolved before significant work is built on the old code.

---

## How Judging Maps to Features

| Criterion (final judging) | Weight | What delivers it |
|---|---|---|
| Gameplay | 20% | Responsive controls (existing), wave pacing, upgrade choices, two bosses |
| Esports Potential | 20% | Fixed-seed waves, clear score formula, leaderboards, bosses as spectator moments |
| Graphics and Art | 10% | Consistent AI-assisted pixel art, contamination palette, CRT shader |
| Music and Sound | 10% | Distinct music for menu, waves and bosses; impact SFX |
| Creativity and Innovation | 20% | Scrap economy loop, orbital-junk theme, Filipino setting |
| Game Feedback (audience vote) | 20% | Trailer and live demo appeal |

---

## Target Players

- **The judge.** Plays for 3 to 5 minutes at a booth. Must understand the goal within 20 seconds and see a boss or upgrade within 5 minutes. Endless mode and the tutorial prompts serve this player.
- **The audience voter.** Watches a trailer on loop. Needs readable action and clear contrast: toxic-green enemies, gold scrap, sky-blue player.
- **The competitive player.** Replays Endless to climb the leaderboard. Needs deterministic waves and a score formula that rewards skill.

---

## Success Criteria for Submission

1. The game builds from a clean clone on a Windows laptop and runs at 60 FPS with 80 enemies on screen.
2. A new player can finish wave 1 without instructions outside the game.
3. Story mode can be completed from intro to ending cutscene without crashes.
4. Endless mode reaches wave 15 without crashes or runaway memory.
5. Restarting a run resets every enemy, bullet, scrap pickup, upgrade and timer.
6. Every art, music, sound and font file has a provenance row in `assets/ASSETS.md`.
7. Forms 01 to 03, the synopsis, the trailer and the gameplay video are submitted by 24 October, leaving 25 October as a buffer.
