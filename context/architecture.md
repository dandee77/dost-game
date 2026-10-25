# Architecture

**25 October cross-contract supplement:** Technical End Run freezes one unranked fault result using the existing18-field schema/RunContext boundary; result-save failure keeps the original outcome and retries storage only. Return guards suppress friendly damage/procs while normal projectile contact/termination and effect lifetime advance, preventing delayed-hit banking. Application/Game checks frame delta before stepping: >0.25 seconds opens explicit performance Continue gate and discards the entire interrupted wall interval. Existing manual P/Esc/MENU does not bypass focus/stall/modal input ownership. No additional manager, scene or save format is introduced.

**25 October panel/story target:** [Input/settings matrix](../todo/02-gameplay/ui-input-and-settings.md) defines one input owner, focus gate, full panel preservation and Q46 warning/shake preferences. Application owns persisted presentation preferences; simulation uses unshaken camera. [Source-checked story pipeline](../todo/01-story/final-production-script.md#supported-runtime-pipeline-source-inspection) requires the planned Cutscene base first, then Intro/Ending Scene subclasses with layered PNG/sheets and existing resource/audio ownership. Ending receives immutable RunContext result before world retirement, then shows shared existing GameOverOverlay/result presentation within Ending's results state. Do not return to Game merely to show results: onSwitch currently resets it. Only Restart creates a new run. No runtime video library or additional score owner.

**25 October remaining-context adoption:** [Encounter owner/data](../todo/02-gameplay/beta-encounters.md), [portal transaction/protection](../todo/02-gameplay/return-portals.md#exact-commit-resume-and-reset-order), [root cannon composition](../todo/07-upgrade-proposals/weapon-composition.md) and [numerical/load rules](../todo/04-verification/numerical-and-load-contract.md) govern the target. Keep existing Game/Player/SkillSystem/EnemyManager/BulletManager/ScrapManager plus planned WaveDirector boundaries. One selected enemy variant drives sprite/material, all boss instances have unique IDs/owned effects, and one primary root ledger prevents duplicate signatures. Scalar chronology is authoritative; aggregate only proven equivalent events. Focus/UI freezes combat; long render stalls require explicit Continue rather than banked wall-time. Machine-limit faults pause before mutation with unranked diagnostic outcome, not hidden progression truncation. No runtime migration or benchmark has occurred here.

**Attributes/Luck target:** Existing Player/stat and SkillSystem owners retain distinct field-card/paid sources and derive effects once. EnemyManager's reward assignment adds an isolated seeded Luck comparison stream at spawn, preserving base-loot draw consumption and assigned rewards across suspension/death/collection. [Contract](../todo/03-economy/attribute-and-luck-contract.md) defines exact eligible sources/gate/second roll; reset through current Game/EnemyManager paths. No new wallet, Luck manager, global RNG coupling or shop full-rank shortcut; source integration remains open.

**Card selection target:** Existing Game-owned card engine/typed catalogs implement [beta selection](../todo/07-upgrade-proposals/beta-card-selection.md) with read-only eligibility, fixed canonical order, unbiased bounded draws and independent seeded shop stock. Reject invalid zero-ordinary data before random draws and preserve the choice for safe restart/menu, never force a Legendary. Existing card state locks options/commits once. No additional catalog/RNG manager or string-dispatched behavior; code migration remains T03/T08.

**Beta equipment integration target:** [Loadout contract](../todo/02-gameplay/beta-loadout.md) selects one normal cannon profile/fire loop and one Player-owned live point shield; SkillSystem retains earned Deflector rank, Game resolves guards/Blink/shield/hull/break/death once. Legacy debug engine/build/shield modes remain outside normal menus and cannot add a second absorber. Only genuine new-run initialization grants 20/20 starter points. No second equipment/shield manager; source migration remains T04/T08 work.

**Q45 ability HUD target:** Game's existing HUD pass reads SkillSystem ownership/rank/cooldown/active state and authoritative shield/droid facts. Extend read-only presentation access as needed; the activation-time cooldown denominator belongs to real cast state, never a second UI timer. Existing drawStatus is the migration point for selected-Q prototype text. [Compact icon contract](ui-rules.md#compact-automatic-ability-hud--q45-confirmed-25-october) does not add casting input, RNG, a HUD singleton or run mutations from drawing.

**25 October Q44 damage feedback target:** Game's authoritative hit resolution emits one cosmetic damage fact with stable target ID, saved impact position, actual applied amount and resolved critical tier. Existing DamageIndicatorManager groups only cosmetic same-target/tier output and owns independent popup values/positions; it cannot mutate combat/score/rewards or roll a second critical. Reuse its reset/update/draw integration and isolate cosmetic drift RNG. [Contract](ui-rules.md#floating-damage-numbers--q44-confirmed-25-october) records prototype integer/raw-damage/critical-heuristic limits; event metadata/grouping are planned, not implemented.

**25 October Q43 HP presentation target:** Enemy retains authoritative current/spawn-scaled maximum health; initialize the already-planned Enemy max-health field after final spawn tuning. Existing enemy/world rendering supplies live visibility/bounds to the screen-space overlay; draw one shared bar style under [UI rules](ui-rules.md#damaged-normal-enemy-health-bars--q43-confirmed-25-october), not a new manager or duplicate health state. Boss/normal-add classification determines the appropriate HUD; presentation cannot mutate HP/combat or advance timers. Current source lacks the planned max-health field/getter; no implementation is implied.

**25 October Q42 caption ownership target:** Existing story/cutscene presentation owns authored phrase-cue state alongside its beat/voice timeline; the existing single voice owner supplies the corresponding clip cursor/status. Muting does not stop cue progression, pause/focus freezes both and advance/skip/exit clears both once. Missing audio uses authored presentation timing for readable cues. No live transcription, subtitle singleton or new subtitle-format library. [Contract](../todo/01-story/story-context.md#complete-narration-captions--q42-confirmed-25-october) preserves frozen result ownership and distinguishes written policy from future renderer/audio integration.

**25 October Q38 card lifecycle target:** Existing Game-owned pending-choice/card state retains the locked offer through pause/focus. Only a successful rank/acquisition transaction consumes one queued pick; then exit once and create the next offer against updated state before combat. No skip/defer-to-combat path or new owner/singleton. Consume transition/selection inputs; terminal/reset clears unresolved choices without awarding anything. [Policy](../todo/07-upgrade-proposals/automatic-skills-and-rarities.md#4-proposed-field-offer-weighting) distinguishes target behavior from delivered prototype queue/exit locking; empty-pool recovery and complete UI acceptance remain open.

**25 October Q33/Q34 target ownership:** Existing Game-owned SkillSystem queries enemies/projectiles/pickups through current owners/spatial structures, holds stable target IDs and emits damage/drop/teleport facts. Game remains the sole damage/death/result owner; no separate targeting singleton. Ability aim is independent of mouse primary aim and cannot rotate the player. [Matrix](../todo/02-gameplay/automatic-targeting.md) defines snapshot/refresh/no-target and deterministic droid/Blink rules. Q34 confirms nearest valid single target without boss bias, using attack-origin distance then stable ID; group/droid policies remain separate. Blink's legal-segment test rejects crossing solids but its actual move is not a swept contact/pickup path; failed rescue spends nothing. All clocks freeze with combat. Current manual/debug APIs remain source baseline until T04 implements this target.

**25 October audio routing target:** Q32 selects dark electronic/synth. ResourceManager owns resources; Application's existing audio/scene integration becomes the sole music-context/voice/gain/cursor coordinator, while Game/presentation reports events. Migrate current Game/menu starts/updates rather than adding another AudioManager singleton. One audible music stream and one narration clip, serviced once per application frame; focus/manual pause gates audibility even when terminal results finalize. [Audio matrix](../todo/09-art/audio-direction.md) defines context priority, resume cursors, serial fades, slider/duck/mute behavior, effects cleanup and missing-resource fallback. Current game_music points to an inherited track, not the canonical game_music.mp3 file; planned delivery changes that mapping explicitly. No runtime routing/source change delivered here.

**25 October Q29/Q30 identity ownership:** Existing menu/Application-session UI owns the name draft/last-name prefill; reuse planned NameEntry as a prelaunch widget after difficulty. Confirm copies normalized name into immutable run identity before Game starts; Game/RunContext carries it into the frozen result. Restart retains identity while resetting gameplay. Result submission reads that captured name and does not ask for another alias. Do not add name to settings.cfg or introduce an account/extra scene. [Identity contract](../todo/01-story/player-identity.md) supersedes the earlier post-run naming flow while keeping the 18-column score schema unchanged.

**25 October scoring/result ownership - target:** Game/run owner is the sole scoring ledger and terminal-result finalizer. Reuse planned RunContext for immutable cross-scene lastResult and the planned Leaderboard/NameEntry boundaries for local storage/UI; do not create duplicate managers. All old Player/weapon/skill award paths must report the same typed events, with one death/clear credit. Use entity terminal flags and bounded in-step duplicate suppression rather than an unbounded archive of every ordinary kill; finite Campaign objectives and current Boss ordinal have explicit once-only guards. Pause/station/ending cannot add combat time. [Contract](../todo/02-gameplay/results-and-leaderboards.md) defines fields, 18-column v1 storage, board identities, eligibility, atomic save/retry and corruption handling. These classes/contracts remain planned, not source delivery.

**24 October Q25 Boss retirement:** Reuse Game-owned station confirmation and result finalization for Boss as well as Swarm/Chaos. Snapshot earned score, unique credited boss IDs/count and active time before clearing sequence/run state. Confirm invalidates pending launch/shop actions and creates one terminal Retired result; Cancel preserves the sequence and station origin. No new scene, remote-return path or outcome owner. [Contract](game-design.md#24-october-boss-mode-retirement---q25-confirmed) keeps mutual destruction/quit distinct.

**24 October Q24 sequence ownership:** Boss-mode encounter/run state owns a roster snapshot, current/pending ordinal and credited encounter IDs. Fixed authored order consumes no combat/loot RNG. Validate creation resources before committing the next confirmed station launch; portal/death callbacks finalize credit once but do not launch/increment twice. UI reads the pending name/ordinal; no boss-selection scene. Reset sequence with the run and preserve it during pause/station/cancel. [Sequence contract](game-design.md#24-october-automatic-boss-sequence---q24-confirmed) defines wrap/failure behavior; current boss classes/director remain pending.

**24 October Q19/Q20 outcome ownership:** Resolve valid damage events for one simulation step before deciding terminal results. Same-step player/boss death commits boss-clear credit once, freezes one result and ends the run; no revival, portal travel or next encounter. Keep terminal run state separate from credited boss/objective flags. Final Campaign completion is recorded only if all required final objectives resolved in that step. No new simulation ticks, cleanup kills or automatic loot collection. [Numerical/outcome authority](game-design.md#24-october-simultaneous-boss-clear---q19q20-confirmed) defines edge cases; T06 integration remains pending.

**24 October Q18 tutorial ownership:** Keep seen/dismissed tip IDs and the optional tips-hidden flag in application-session UI state. Game/panels emit existing contextual events and own their inputs; tutorial presentation observes them without mutating combat/RNG. resetRun clears pending run-specific candidates but preserves session seen state; closing the application clears the tutorial session. Mandatory panels suppress optional tips, and stale source/run candidates are discarded. Use existing UI ownership; no tutorial scene or singleton. [Contract](../todo/00-planning/decisions-and-gaps.md#6-in-play-tutorial---q18-confirmed-24-october).

**24 October optional wave checkpoint:** Finalize a Campaign wave once, freeze the cleared encounter and offer station or direct continuation. Game/run ownership retains one pending next encounter; either direct launch or later station departure consumes it once. No scene switch/resetRun, automatic base transit, duplicate index increment or extra reward. Map opened after a non-final level clear remembers checkpoint versus hub origin so Cancel restores the correct state. Checkpoint time freezes combat/shield regeneration/droid rebuilds. Boss-mode base visits and ordinary mid-fight retreat remain separate policies. See [current clear contract](../todo/02-gameplay/campaign-stages.md).

**Background handoff boundary:** The [background brief](../todo/09-art/background-brief.md) assigns art production/integration to the teammate. Preserve current four-layer order/keys/frame formats; add non-repeating level landmarks through existing Game/ResourceManager/render ownership when delivered. No generated assets, new renderer/class or runtime registration is created by the brief.

**24 October beta map ownership:** Use four authored IDs C01-C04: C01 unlocks C02/C03, either middle clear unlocks C04. Keep unlocked/completed IDs and active encounter in Game/run/director ownership; no exclusive route-lock state. Other unlocked, unfinished levels remain selectable after the current level clears. Preview/cancel does not mutate progression. Preserve values across base/pause/cards and clear on death/New Game. Final clear freezes one result before ending playback. See [beta map contract](../todo/02-gameplay/campaign-stages.md).

**24 October focus/audio/graphics settings:** Owner confirmed focus-loss auto-pause with explicit Resume, three shared Master/Music/SFX sliders, Low/Medium/High graphics with **Medium default**, and local audio/graphics persistence. [Questionnaire contracts](../todo/08-review/owner-questionnaire.md) define input/modal preservation, gains and settings.cfg schema/failure handling. Application owns preferences, focus detection and renderer application; Game retains pause source/panel. Preferences survive resetRun/application relaunch; no gameplay state is saved. Graphics alter cosmetics only, preserving simulation and gameplay RNG. Save on committed settings actions, not per frame. Required original English AI narration follows presentation ownership and SFX/Voice routing; skip/pause/exit stops or freezes the correct clip.

**Delegated layout ownership:** [Beta layouts](../todo/02-gameplay/beta-layouts.md) define ship-based hub interaction, separate field/hub positions, finite versus roaming arenas and portal placement/fallback. Numerical geometry belongs to game-design.md/Balance; screen geometry belongs to Theme. The isolated portal stream, pending-placement retry and route data are run-owned state and must freeze/reset with their encounter. No additional world, currency or shield singleton is required.

## 24 October staged Campaign ownership — target

Four modes remain; Swarm/Chaos share ordinary rules and Chaos layers bosses. Campaign uses a Game-owned map and run-local level/encounter/unlock data. C01 starts available; clear callbacks unlock successors once. Opening/canceling maps cannot mutate RNG/currency/progression. Wave clear finalizes rewards/hazards, then offers optional station or direct next encounter. Only selected station travel enters base, without energy/shield gates. Confirmed direct launch or station departure starts the pending fight once. C01 has five normal waves plus boss; progression carries between levels, while death/New Game resets it. No Scene/resetRun per level or permanent unlock save. See [campaign stages](../todo/02-gameplay/campaign-stages.md).

## 24 October Boss-mode encounter lifecycle — target, not implemented

Owner confirmed no mid-fight retreat: the mode policy must suppress ordinary portal generation and reject ordinary return interactions, including at full energy. Only the finalized boss-clear portal permits base travel. Do not implement this restriction solely by hiding a HUD button. Pause/settings do not constitute retreat; quit abandons the run and cannot preserve/retry the encounter as a free base visit.

Game keeps one run through successive boss encounters. The encounter owner finalizes a living player's boss clear once, stops owned spawns/hazards and reveals one base portal. The portal enters the existing base state without calling resetRun. Only a later confirmed launch advances the encounter index and creates a fresh boss arena; progression and wallet persist. Cancel/duplicate portal or launch requests cannot award rewards or advance twice. Existing earned loot is credited once before arena retirement; cleanup gives no additional rewards. Campaign required-add completion remains distinct. See game-design.md for the confirmed boss-clear shield/energy bypass and owner-requested phases/HP bars.

## 24 October implemented balance flow

Game owns RunProgress. EnemyManager assigns stored trade currency from a dedicated loot RNG; Enemy retains separate fixed salvage. Eligible death emits one ScrapReward pickup. ScrapManager and the skill magnet return paired values; Game credits them once. Merging preserves both totals and persistence. Spending currency cannot remove XP/energy.

Queued salvage levels open the existing card state before the next combat update. Accepted input consumes one choice; exit animation creates the next offer or resumes combat. Timer-only cards are removed. Reset/death/exit clear progress with existing manager resets. Repair/battery/return helpers do not create the pending hub or alter live shield behavior.

Natural spawning integrates a piecewise-linear rate over combat delta, retains fractional credit and discards blocked whole spawns. EnemyManager resets credit and loot RNG. Ordinary enemy constructors snapshot bounded combat-time HP without player-level or difficulty multiplication. The current schedule is a prototype endurance schedule, not a five-mode WaveDirector.

## 21 October upgrade integration proposal — not implemented

See [upgrade review](../todo/07-upgrade-proposals/README.md). Keep one authoritative derived-stat path using source records for field card ranks and paid numeric counts. A quarter-strength purchase cannot invoke a full-rank grant and retain its side effects. Cannon branch/tier is run-local equipment state; upgrades are atomic hub transactions and live attacks retain their launch snapshots. Deflector has one live shield state: paid capacity changes its maximum without full-rank/reboot/heal effects. Do not add a second shield manager.

Legendary Blink belongs in the existing damage/skill ownership flow. Intercept a validated direct hit once before shield/hull damage, query bounded legal on-screen destinations, and commit teleport/protection/cooldown together only if safe. Its protected window and cooldown cannot refresh through upgrades, hub entry or repeat collision callbacks. New position is the start of subsequent movement; no sweep/pickup credit along the teleport path.

The proposed Luck source snapshots reward quality at enemy spawn using a separate Luck RNG alongside the existing base loot stream; final values survive suspension and cannot reroll on death/collection. Skill rarity uses the independent card stream and is unaffected by Luck. Owner choices, not proposed tables, determine eventual adopted scope; no new class/singleton or save system is mandated by this context update.

## 21 October preparation alignment

The foldered handoff starts at [todo/README.md](../todo/README.md). Story/source contracts are in [world and campaign](../todo/01-story/world-and-campaign.md); material labels are in [scrap types](../todo/03-economy/scrap-types.md). These are future integration requirements, not new classes implemented in this session.

Keep source-shutdown state inside the existing planned encounter/run ownership. It survives hub suspension, ends future source adds and resolves only after required hostiles; no second quest singleton or loot-dependent victory system. The material label travels with the existing paired reward through spawn, destruction, pickup, merge and collection. Different labels merge to Mixed Salvage while preserving trade/salvage totals; no per-material currency inventory subsystem. Presentation-only intro/ending clocks cannot mutate run state or RNG. Frozen results are owned by the run/result flow, not a cutscene's repeated completion callback.

## 20 October target integration: colony and expeditions (not implemented)

[todo/02-gameplay/gameplay.md](../todo/02-gameplay/gameplay.md) defines the new flow; this section supersedes conflicting older target connections below. The existing P6/P5 implementation notes remain the current-code baseline.

- MainMenu confirms typed difficulty before creating a Game run. Game begins in a safe hub; a portal selects the typed mode. Difficulty and mode are different fields.
- Keep hub, field, dock/shop, card selection, pause and results within the existing Game lifecycle. Calling onSwitch/resetRun for a dock visit would erase the run and is forbidden.
- Game owns one run-progress value: collected trade total, spendable wallet, player level, progress, queued picks and return charge. Each pickup stores tradeValue/salvageValue; collection updates wallet/total by trade and progress/charge by salvage once. Merge both fields independently.
- Retain the existing ScrapManager and accepted debris lifecycle. Add ordinary-enemy pickup behavior and centralized reward finalization rather than another pickup manager. Space Collapse/barricade/despawn exclusions remain explicit.
- Reuse SkillSystem/Player rank APIs for both field choices and paid skill upgrades. Adapt the planned UpgradeShop/DockShopUI to this catalog; do not implement the obsolete parallel gear-stat ladder.
- Extend the planned WaveDirector with mode-specific objective/schedule data. Do not create a Scene per mode, duplicate EnemyManager, or treat an unavailable boss as a completed mode.
- The 23 October field return portal replaces the manual Return Home skill. Game owns portal interaction/energy and queries the same Deflector state used by damage handling; F inside a valid portal requests return, then final-frame shield/energy/death checks gate commit. Use the existing Entity/Dock approach, no new scene or separate shield manager. Seeded portal placement must not advance encounter/loot streams; count/lifetime/replenishment/reset details are in todo/02-gameplay/return-portals.md. Preserve the used portal position for Resume even after retiring its set; Game-owned re-entry protection uses combat time, ends on firing and clears on reset. Duration belongs in Balance; this temporary damage guard is separate from actual shield points. Delegated ordering: pause primary auto-fire and offensive automatic skills during protection; deliberate Shoot fires and ends protection immediately.
- Validate ordinary return after that frame's damage, scrap and level thresholds. Death or a shield break prevents travel; queued cards precede return for living players. Fixed capacity/threshold are 1000/500 at every level. Commit charge consumption and hub transition once; failed requests mutate neither. Boss-clear travel bypasses shield/energy but still requires a living player. Same-step fatal boss damage retains clear credit under Q19/Q20; it cannot cause travel or continuation.
- Suspend one existing field world in memory. Preserve entities, HP, projectile positions, pickups, pending explosions, skill snapshots, clocks and director/RNG state. Keep field and hub player positions separate. No save-file system is required.
- Freeze field updates while at home. Hull repair jobs quote actual missing HP and either full or affordable proportional restoration; preserve fractional HP, freeze/cancel correctly and debit atomically with the quoted healing on completion. No free heal on hub entry. The 23 October Shield Battery is a separate shop item used on purchase, replacing shield/full-service jobs; it uses the same authoritative shield state, no carried inventory or new activation key. Paid hull healing clears harmful statuses; a battery does not clear hull statuses or offensive cooldowns.
- Use the same rank API with an explicit field/shop acquisition source: paid Reinforced Hull changes max HP without healing current HP, while its field card retains the original max/current grant. Cards/shop previews reflect that difference. Other skill rank snapshots remain unchanged.
- Only true new-run/death/quit paths clear the world, run economy, return requests, shop stock, card queues and effects. Session volume/difficulty preference survive. Detailed lifecycle matrix is in TODO section 12.
- Separate encounter, loot, offers, shop and cosmetic RNG streams. Assign enemy trade value once at spawn; retain it across death finalization/suspension and never reroll at collection. Record mode/difficulty/seed/rules and terminal outcome. Combat time excludes hub, pause and modal choice time.

Suggested future states are HUB, PORTAL_PREVIEW, RUNNING, AUGMENT_SELECTION, PAUSED, DOCKED and RESULT/GAME_OVER; these names are design proposals, not declarations already present in Game.hpp. Pause remembers its source state and resumes to that state. No new singleton is required.

## P6 checkpoint 1: pause-safe time (19 October)

`GameTimer::update(dt)` advances run time only in Game's running branch. Cooldown values advance explicitly in their running owners: EnemyManager/DebrisManager spawning, Enemy::advanceCooldowns for knockback, MidLevelEnemy's override for shooting, and KillCounter::update. Enemy::updateWithStatus invokes cooldown advancement before suppressing stunned movement/fire, preserving recharge during stun. No simulation timer reads wall-clock time; Application's CRT time uniform remains cosmetic wall time.

Game advances world Animator entries once per running update, never from draw. Pause, console capture and card selection freeze world animation; card/confetti UI keeps its existing selection update. Game over advances only `game_over_text` through `Animator::Update(name)` and its dedicated presentation effects. Esc and P consume opening/resume frames. The full pause/settings menu is still pending. Reset paths clear spawn/HUD cooldown debt; timers have no new singleton/global clock. Old current-loop descriptions below predate this checkpoint where they mention wall-clock timers or draw-time animation updates.

## P5 repeat-pick extension (18 October)

`Game::createUpgradeOffer` samples eligible typed augment and ability cards using the existing seeded generator. `chooseUpgrade` applies the selected card once and locks the entire offer until its exit animation completes. Capped passive augments are excluded; ability cards remain eligible after level 5, and Nano Repair remains available. `Card` stores separate typed augment/ability IDs, and ability cards show the resulting level. No scene transitions or new singleton are involved.

`SkillSystem::upgrade` owns earned levels; `equip` delegates repeated equipped picks to it. Unequip preserves level/cooldown; each `begin` snapshots `castLevel` so a mid-effect pick cannot refill health/shield charges or retune an existing cast. `abilityTuning` caps physical size growth at level 5 and continues other growth from Balance. Space Collapse stores a zone center per cast level. Pools snapshot their damage/radius. The system owns drone values, each with position, health and a contact clock; it consumes hostile bullets and removes destroyed drones before firing. The existing Game reset/death/exit paths clear all progression and transient values. See `skills-commands.md` for the exact upgrade contract.

## P5 skills extension (17 October)

Game owns `SkillSystem` by value. It owns typed ability states, cooldowns, bounded visual/trail values and seeded barrage randomness. `Player` owns augment levels, modified stats, critical RNG and deflector-hit charges. `Enemy` owns temporary stun/corrosion. No new singleton is introduced. `resetRun()` resets skills and augment-offer RNG; Player::init resets augment stats. Death and scene exit clear skill effects/deflector charges.

During running simulation: Player and BulletManager update, then Game::updateSkills advances effects, removes intercepted hostile bullets, applies enemy status/displacements and returns teleport state. SkillSystem reports typed damage events with an explicit drop flag; Game routes them through existing damage/score/destruction handling. EnemyManager receives an optional short-lived clone position for targeting, then updates enemies through status-aware movement. Blink replaces the pre-teleport swept-contact start so teleporting across a wall is not treated as movement through it. Existing collision snapshots are rebuilt after skill damage/removals.

Augment IDs replace card-title dispatch and utils::augmentPool. The existing timed offer samples three distinct entries from the 14-entry catalog with a reset seeded generator; no new progression path. SkillSystem::command handles skill/augment text at the input boundary; behavior dispatch uses typed IDs. DebugTools binds to the Game-owned system. Application may route repeated terminal `--command` values through the same console only after resources load and a new game starts. Debug commands remain GAME_DEBUG gated. See `skills-commands.md` for commands, provisional behavior and deferred connections.

## Current debris harvesting extension (15 October)

`Asteroid`/`AsteroidManager` were renamed to `Debris`/`DebrisManager`, including source files, IDs, texture keys, collision observers, diagnostics, tests, and death labels. `DebrisKind` indexes ten entries; Theme owns fixed draw sizes, Balance owns fixed collision radii and yields. Circular collision search and deferred removal order remain unchanged.

On player destruction, DebrisManager calls Debris::destruct(true), which queues the variant's own sheet through DebrisInfo::destructTexture in ScrapManager. Environmental removal passes false and plays that sheet without pickups; offscreen despawn creates no effect. BarricadeEnemy uses the original legacy asteroid idle texture via barricade_asteroid. On death it removes its idle Animator entry and calls spawnDestruction with barricade_asteroid_destruct, a cosmetic-only seven-frame breakup that creates no pickups or scrap value. Each destruction stores its own frame count so legacy asteroid and eight-frame debris playback can coexist.

ScrapManager owns pending destruction records and orb entities on one simulation clock. A record owns its texture key and retains DebrisKind for harvest metadata; generic spawnDestruction effects are nonharvestable with zero value. It draws whole 96px frames without cutting intact sprites or updating Animator. At 0.525 s, harvestable records spawn orbs at the variant's own saved final-fleck coordinates (Theme::DEBRIS_SCRAP_VISUALS), rotated/scaled with the explosion. Orb counts follow each exported sheet, while sizes retain the small/medium/large tiers. Only residual dt advances new orbs; after 0.05 s they home. Game advances this system only while running and alive and credits arrival once. Reset clears cosmetic deaths, pending debris explosions and orbs. The 150-orb cap merges overflow value after destruction; there is no cargo cap.

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

Projectile feedback extension (15 October): BulletManager remains the only run-state projectile owner. Adding a bullet creates a bounded muzzle-charge value; each live Bullet directly renders a pulsing core halo and direction trail; collision owners report exact contacts through `spawnImpact`, which creates an eight-frame player burst (or toxic enemy ring), original impact sound and bounded aftermath particles. Enemy owns a short simulation-time reaction tint. Effects update only in the existing running-game BulletManager/EnemyManager updates and clear through their existing reset calls. Damage, cadence, speed, collision order and removal rules are unchanged.

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

Owner-confirmed presentation persistence uses Application-owned settings.cfg under the [questionnaire schema](../todo/08-review/owner-questionnaire.md): three audio gains and graphics preset, Medium default, safe file failure handling and no run state. Scores use the adopted [results-v1.csv contract](../todo/02-gameplay/results-and-leaderboards.md), separate from settings and old leaderboard.txt. PREP-09 specification is delivered; storage is not implemented. The older two-mode example below is retained only as superseded history.

**Historical, do not implement:** the former `leaderboard.txt` example was:

```
mode,name,score,waves,seconds
story,DANDEE,48210,10,812
endless,ANNE,63150,17,1104
```

The current contract keeps compatible 3-12-character display names but replaces the old fields/boards/file format. Do not migrate these Story/Endless scores into current rules or overwrite the legacy file.

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
