# Project Overview

**Latest Boss-mode direction:** defeating each boss reveals a base portal; launching from the base starts the next boss encounter in the same run, preserving the build and wallet. Boss mode no longer ends after one kill. Owner requested boss phases and visible named HP bars. Boss-clear portals bypass shield/energy requirements; no starting-energy exception is adopted.

**24 October owner decision:** every new game starts fresh; no permanent gameplay unlocks, banked scrap or stat progression. Settings/history may persist without combat benefits. Same-expedition hub visits preserve the run. Owner delegated [boss concept/attack drafting](../todo/02-gameplay/boss-roster-draft.md) for review; the proposed roster is not yet approved or implemented.

Read this file first in every session. It defines what the game is, why it exists, how it plays, which screens exist, and what is in and out of scope for the submission. For technical questions, `architecture.md` wins. For numbers, `game-design.md` wins.

The owner requires the [task-list folder](../todo/06-task-list/README.md) to be maintained every session: read its open tasks before work, add newly discovered attention items/ideas, and update checkboxes plus completion evidence whenever something is verified complete. This supplements the main tracker and does not change the current context-only authorization.

## 23 October field-return portal revision

**Latest implementation direction:** Owner authorized C++ balance fixes plus updated statistics. Early combat should be calm, later pressure should come primarily from enemy numbers, and HP growth should remain modest. Chaos rotates through all finished bosses and allows progressively more concurrent pursuers as combat time grows. Earlier context-only/general-balance deferrals are superseded for this work; missing boss content remains open.

Owner replaced the planned manual teleport skill with random combat-map return portals. Portals appear once energy reaches 50%; travel requires positive online shield and at least half of current energy capacity, with F pressed inside the portal. Difficulty sets concurrent count across every mode: Easy 3, Hard 2, Impossible 1. They can be far away; a pointer appears within roughly one visible screen. Portals remain until used/run end and stay visible but locked while shield is broken or energy is short after a level-up. A successful return retires the set; the next half-charge readiness generates fresh random locations. All skills are automatic. Exact placement ranges and fallback remain open in [return portals](../todo/02-gameplay/return-portals.md); no source changes are authorized here.

Resume returns the ship to the used portal position with two seconds of damage protection, ending on firing and restoring no hull/shield. Exact attack-input handling remains a later contract detail.

Owner also selected appearance-matched scrap types. Five Shield Batteries—Tiny/Small/Medium/Large/XL—supply 20%/50%/100%/150%/200% of upgraded normal shield capacity. Each purchase removes old overcharge before adding its charge; damage below normal capacity is preserved first. Repeat paid purchases are allowed. Natural regeneration only fills to normal capacity. Starting prices 100/250/500/700/900 scale proportionally with normal-capacity upgrades. Full formula, examples and shop previews are in game-design.md. Power Cell salvage is not a battery.

## 23 October selected economy and materials

Owner selected weapon costs **500/1500/4000/10000** (16000 total), targeting T5 at 20–25 Swarm combat minutes; 5-minute Survival keeps the shared prices and ends with lower tiers. Attribute/owned-rank prices increase 5x and special acquisitions 10x. Hull repair costs 10 scrap per missing HP and offers proportional affordable repair with exact previews. A Shield Battery shop item, used on purchase, replaces paid shield-recharge/full-service jobs; its details remain under popup review. Four selected salvage labels—Metal Fragments, Circuit Parts, Polymer Pieces and Power Cells—feed one wallet at existing enemy-tier values, with no material gates or free shield restoration. This reopens price/material review only; source and assets remain unchanged. See [game design](game-design.md).

## 23 October accepted weapon tree and draft stats

Owner accepted the latest weapon names/path, with choices at T4 and T5: **1/3/5/7/10 nodes**, 26 total and ten finals. The [weapon tree](../todo/07-upgrade-proposals/weapon-tree.md) supersedes the earlier six-family graph. [Game design](game-design.md#23-october-weapon-stat-draft--accepted-tree-proposed-tuning) contains the requested full profile/signature draft. Numbers, exact card compatibility, actual viability and performance remain unverified. No source/assets changed. Weapon questions have resumed; boss/schedule/layout/general-economy and final game-title decisions remain deferred.

## 21 October weapon and upgrade follow-up — historical proposal

Confirmed owner direction: simple-cannon start, cannon tiers bought only at the mothership, one weapon branch per run, and purchased numeric attributes at **25% of the matching card gain**. Shield remains in field cards and can also receive paid capacity increments. All combat abilities are automatic; Return Home remains the manually activated utility. Blink is Legendary and reacts to an impending direct hit by preventing its damage and relocating the ship to a safer visible-screen position.

The [upgrade proposal folder](../todo/07-upgrade-proposals/README.md) originally presented a five-tier, six-specialization tree (superseded above), attribute/skill purchase separation, Luck recommendation and full automatic roster/rarity tables for later confirmation. Exact family placement, new prices/stat profiles, rarity weights and Blink cooldown/protection details are drafts; older full-rank numeric-augment/no-weapon-shop descriptions are superseded. The 25% rule concerns numeric attributes, not fractional skill acquisitions. Field attack-stat cards remain under the explicitly labeled interpretation awaiting review; they do not grant cannon tiers.

Boss designs, mode schedules, final names, hub/arena layouts and general economy review are deferred by the owner. Keep their tasks open and marked deferred. No new mode/boss/layout decisions or source changes are authorized by this follow-up.

## 20-21 October product revision: design only

The owner's current design handoff is [todo/02-gameplay/gameplay.md](../todo/02-gameplay/gameplay.md). No code was changed for this revision; the tracker distinguishes implemented behavior from targets. This revision and the current story/screen sections below supersede the original cargo/deposit/two-mode/tree design.

**Confirmed flow:** Open game -> Start Game -> select difficulty -> spawn in the mothership's safe orbital hub -> prepare -> fly to a mode portal -> confirm launch. The player stays in the ship. The visible colony must communicate that humanity lives in space. This is a single-player hub, not multiplayer matchmaking.

Requested modes are **Swarm** (endless normal crowds), **Survival** (fixed-duration survival), **Boss** (focused boss encounter), **Chaos** (bosses and swarms together), and **Campaign** (staged progression ending with a boss). The no-boss Swarm distinction, durations and schedules are proposed defaults in the handoff. Older Story/Endless references in historical planning map to Campaign/Swarm; they are not the complete new mode list. The owner will supply final boss identities and attacks; previous boss names are not approved content.

**Confirmed field progression:** collected scrap fills level progress and presents normal upgrade cards in the field. Docking is not required. Scrap also powers field-return portal eligibility at 50% of a maximum that grows with player level; a broken shield blocks use. Portals replace the planned manual Return Home skill.

**Economy follow-up:** the owner requires paid base health repair and random tradeable scrap by enemy (basic enemies 1-3), and delegated inventory/pricing. Selected design: each pickup carries random trade currency and fixed salvage progress for leveling/Return Home. No cargo cap, credit conversion or deposit. The shop sells targeted owned-skill ranks and rare Singularity/Space Collapse/Nuclear Missile/Armageddon acquisitions; a paid hull-repair berth and a separately purchased Shield Battery share that currency. Exact ranges, costs and transaction rules are in game-design.md and TODO. These are selected initial tuning, not claims of tested balance.

**Target hub loop:** return -> repair berth/skill shop -> resume the same expedition. Hub visits preserve the build and suspend the encounter in the existing Game scene. Switching modes begins a fresh run. No walking character, networking, cross-run progression or save system is added.

Minimal shared volume settings, difficulty UI, hub/portal UI and visible pause UI are in the target scope. The original blanket Settings exclusion, seven gear lines, credits and cargo loop are superseded. Existing completed skills, art, equipment and pause timing remain the implementation baseline.

Current target controls: F = nearby hub/field-return-portal interaction, E retains auto-fire; all skills are automatic/persistent and there is no manual teleport skill. Proposed starter Deflector prevents a missing shield from making return unreachable. These are defaults to adopt or revise in the teammate's implementation brief.

New target screen additions: S-12 Difficulty (menu panel), S-13 Colony Hub (Game state), S-14 Portal Preview (hub panel). S-05 becomes field level-up, S-06 becomes the skill shop, S-07 gains settings/quit confirmation. Mode selection moves from S-03 into S-13/S-14. The screen table below lists target responsibilities; the tracker reports actual completion.

Success for this expanded scope requires a real objective for every enabled portal, correct return/shield/resource behavior, field upgrades, shop transactions and complete run resets. Adding portals alone does not complete five modes. Any submission scope reduction needs team direction.

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

Humanity survives in reused orbital stations after an experimental atmospheric treatment mutates engineered waste-eating organisms already deployed on Earth and in orbital cleanup systems. As a cadet salvage pilot, clear routes, recover useful material and isolate the concentrated sources that keep the wreckage dangerous.

**Climate framing:** research has detected spacecraft-reentry metals in stratospheric particles and modeled possible ozone/radiative effects. It does not establish a percentage of present global warming caused by orbital debris. Keep this as one environmental concern within a wider crisis. [NOAA paper repository](https://repository.library.noaa.gov/view/noaa/58476), [NOAA modeling summary](https://www.csl.noaa.gov/news/2025/427_0428.html). Detailed sources and fictional boundaries: [science notes](../todo/01-story/science-notes.md).

**Circular economy:** recovered material supports ship maintenance and repurposed skill systems. The game abstracts salvage into trade currency and progression; shooting waste is a combat fiction, not a claim that it is efficient real-world recycling.

---

## Story

**21 October canon supersedes the previous seed/tree narrative.** Full detail: [world and campaign](../todo/01-story/world-and-campaign.md). The settlement is **H.O.P.E. Colony — Habitat for Orbital Preservation and Endurance**. Its mothership is the operational heart of a refuge assembled from existing stations. The player is a cadet salvage pilot and remains inside the ship.

Proposed chronology: scientists develop a remediation medium in **2718**, release it into the atmosphere after five years in **2723**, and survivor estimates record approximately **99% population loss by 2732**. The player begins service in **2733**. The owner's required five-year development and under-decade collapse are preserved.

Before 2718, scientists had already engineered waste-eating creatures, provisionally called Scavengers, for ground facilities and protected orbital cleanup systems. The later atmospheric treatment unexpectedly changes their DNA and disrupts feeding, growth and defensive behavior. They become hostile and collect material indiscriminately. Digestible fractions feed them; retained metal and other fragments are fastened by a biological binding layer into external armor around their living cores. Over later generations, useful inherited gathering/binding traits become more common among surviving lineages. The chemical starts the fictional mutation crisis; evolution then occurs across generations, while metal itself stays nonliving. Exposed organisms, contaminated cargo and residue on serviced hardware carry the disaster into orbit. Protected cores and repurposed propulsion support the fictional space creatures; an atmospheric cloud does not cross vacuum. This biological mechanism supersedes the earlier autonomous-machine proposal and remains science fiction.

The campaign targets infested nests and concentrated residue sites that keep spreading exposure and hostile organisms. Proposed ten-wave outline retains boss slots at five and ten, now two source sectors; identities and attacks remain owner content. Defeating a source guardian stops that site's future emissions/adds. Remaining required hostiles must still be cleared. No random loot or purification item is needed to complete the objective.

**Narrative theme:** humanity used cleanup inventions to postpone changing wasteful habits. The catastrophe is the accumulated consequence of neglect and overreliance on fixes after the damage. The survivors now choose sustained responsibility. Draft tagline: **“We kept throwing it away. Until it came back for us.”** See [theme and slogans](../todo/01-story/narrative-theme.md).

The ending opens a corridor for survey, containment and cleanup teams. Earth remains damaged and climate recovery takes time. No special tree, seed quest or instant cure remains. Other modes are repeatable operations and are not locked behind Campaign completion.

Presentation remains **short story card -> moving animation/gameplay -> next card -> next scene**. [Story and trailer](../todo/01-story/story-context.md) specifies a proposed 40-second intro before the menu once per application launch, 24-second ending and 90-second trailer. All sequences have explicit skip/input/result rules. Final title, boss content, art and optional voice remain pending.

---
## Game Modes

| Mode | Goal | Ends when |
|---|---|---|
| Swarm | Endless normal-enemy salvage patrol; no bosses by default | Death or voluntary hub retirement |
| Survival | Survive 300 combat seconds | Deadline reached alive, or death |
| Boss | Defeat one authored boss encounter and required adds | Encounter complete, or death |
| Chaos | Endless swarms with scheduled bosses | Death or retirement; boss death does not end the run |
| Campaign | Ten-wave proposed route with source bosses at five and ten | Final source encounter complete, or death |

Exact encounter tables and boss content remain to be authored. Same mode/difficulty/seed/rules and equivalent decisions reproduce the plan; player-level scaling means different decisions can change effective enemy HP. Separate mode/difficulty/rules leaderboard identities are required. See [decisions and gaps](../todo/00-planning/decisions-and-gaps.md) for scoring and schedule work still missing.

---

## Core Loop

Open game -> optional intro -> Start Game -> difficulty -> HOPE hub in the ship -> preview/choose a portal -> launch.

During the expedition, defeat threats and collect scrap. The random trade amount enters one wallet; fixed salvage independently advances field levels and Return Home. Choose normal upgrade cards in the field. At sufficient charge with an online positive shield, Return Home suspends the encounter. Pay for repairs or skill upgrades, then Resume that same expedition. Selecting another mode starts a fresh run after the existing-run confirmation. No cargo deposit or credits conversion remains.

Four owner-selected material labels add recognizable salvage flavor: Metal Fragments, Circuit Parts, Polymer Pieces and Power Cells. They share one wallet and enemy-tier reward ranges; there are no material-specific crafting gates. See [scrap types](../todo/03-economy/scrap-types.md).

Current delivered behavior remains in the progress tracker; writing this loop does not implement it. P6 checkpoint 1's pause-safe timing and existing combat/skills/equipment/debris remain the baseline.

---
## Controls

| Input | Action |
|---|---|
| W A S D | Move (8 directions) |
| Mouse | Aim (the ship turns toward the cursor) |
| Left mouse button | Shoot |
| E | Toggle auto-fire |
| Q | Return Home when shield and charge permit (target) |
| F | Nearby hub interaction (target) |
| P or Esc | Pause |
| Mouse click | Menus, augment cards, shop |
| Space / Enter / click | Advance one presentation beat; Esc skips the sequence (proposed) |
| F5 | Debug console with autocomplete, debug builds only (see `architecture.md`) |

---

## Screens

These are target screen responsibilities; existing classes are not proof that every listed flow works. See class-registry.md and progress-tracker.md for current delivery.

| ID | Screen | Target responsibility |
|---|---|---|
| S-01 | Loading | Load existing assets and enter optional intro/menu |
| S-02 | Intro | Skippable story cards and animation, once per application launch |
| S-03 | Main menu | Start Game, Leaderboard, Credits, settings access and Exit |
| S-04 | Gameplay HUD | Hull, shield, wallet, salvage level, Return Home, mode objective and boss status |
| S-05 | Field upgrade | Mandatory queued level-up choices; no timed/wave-clear trigger |
| S-06 | Skill shop | Owned-skill ranks and eligible rare acquisitions; shared trade wallet |
| S-07 | Pause | Resume, volume/settings and quit confirmation; respects originating hub/field state |
| S-08 | Results | Victory/defeat/retirement, final stats, eligible name entry, restart/menu |
| S-09 | Ending | Source containment and beginning of restoration; then finalized results |
| S-10 | Leaderboard | Local rankings separated by mode/difficulty/rules |
| S-11 | Credits | Team, tools, AI disclosure and licenses |
| S-12 | Difficulty | Explicit selection before first hub arrival |
| S-13 | Colony hub | Safe ship flight, paid repair berth, workshop, portals and same-expedition Resume |
| S-14 | Portal preview | Mode objective and launch/reset confirmation |

Hub, shop, repairs, pause and cards remain Game states/panels, not scene switches that reset the expedition. Screen IDs name user experiences, not a requirement to create a class per row.

---

## Features In Scope

- Five requested mode objectives, with honest availability until their content exists.
- Ship-based HOPE hub, portals, field upgrades, shield-gated Return Home and same-expedition suspension/resume.
- Random trade/fixed salvage rewards, material flavor, paid hull/shield service and targeted skill shop.
- Existing accepted ship/enemy/debris/equipment/skill/art/performance work retained as the baseline.
- Proposed automatic combat skills, starter Deflector and Shield Detonation replacement described in the gameplay handoff.
- Intro/ending, local leaderboard, credits, tutorial and minimal shared volume controls.
- Original/licensed production assets and required disclosures, trailer, separate demo and submission materials.

All are target scope, not a declaration of completion. Full boss content, spawn tables, score rules, loadout integration, targeting, UI/audio and release verification remain visible in the gap register. A smaller submission scope requires team direction.

## Features Out of Scope

- Networking, multiplayer, online accounts or online leaderboards.
- Walking avatars, playable ground combat or colony-building simulation.
- Persistent ship progression, cross-run banking or mid-run save games.
- Material-specific crafting, inventory management or player trading.
- Controller support, mobile/web builds, key-rebinding UI and localization for this preparation scope.

Minimal volume controls are in scope; the previous blanket Settings exclusion is retired.
## After Submission (before the 26 November finals)

Only after the 25 October submission: polish pass, extra augment and upgrade options, a third boss phase, better VFX, expanded settings, Filipino voice lines, balance from playtests. Track these under "Finals Backlog" in `build-plan.md`.

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
| Creativity and Innovation | 20% | Scrap economy loop, orbital-junk theme, survivor-colony setting |
| Game Feedback (audience vote) | 20% | Trailer and live demo appeal |

---

## Target Players

- **The judge.** Plays for 3 to 5 minutes at a booth. Must understand the goal within 20 seconds and see a boss or upgrade within 5 minutes. The hub, clear portal objectives and tutorial prompts serve this player.
- **The audience voter.** Watches a trailer on loop. Needs readable action and clear contrast: toxic-green enemies, gold scrap, sky-blue player.
- **The competitive player.** Replays supported modes to climb separate leaderboards. Needs deterministic waves and a score formula that rewards skill.

---

## Success Criteria for Submission

1. The game builds from a clean clone on a Windows laptop and runs at 60 FPS with 80 enemies on screen.
2. A new player can finish wave 1 without instructions outside the game.
3. Campaign can be completed from hub launch through source clearance, ending and results without crashes.
4. Swarm and Chaos sustain their approved target load without crashes or runaway memory; finite modes resolve their objectives correctly.
5. Restarting a run resets every enemy, bullet, scrap pickup, upgrade and timer.
6. Every art, music, sound and font file has a provenance row in `assets/ASSETS.md`.
7. Forms 01 to 03, the synopsis, the trailer and the gameplay video are submitted by 24 October, leaving 25 October as a buffer.
