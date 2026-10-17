# UI Rules

How everything on screen is drawn: the canvas and safe area, the two coordinate spaces, fonts, colors, sizes, layout, sprites and screens. This file replaces three web files: **ui-rules** (how to compose screens), **ui-tokens** (now the `Theme.hpp` header, defined at the end of this file) and the visual half of **ui-registry** (sprite and asset tables).

Why tokens became a header: in C++ the values must live in code. Writing them in two places (a doc and a header) guarantees drift, so `src/Theme.hpp` is the single source of truth after item 03 creates it. This file explains what each token is for.

---

## Canvas and Window

P5 (17 October): skill effects use existing player/shot art plus simple world-space outlines, arcs and a translucent rift. No asset generation. Selected manual skill/Q prompt and cooldown appear at Theme::SKILL_STATUS_POSITION (220,470), below the scrap readout and inside the CRT safe area. Automatic effects can coexist; F5/autocomplete exposes their state without adding acquisition UI. Clone uses the existing ship sprite tinted sky blue; drone uses a small outlined marker.

15 October unique destruction update: each DebrisKind selects its own 768 x 96 destruction sheet (eight 96px frames) through DebrisInfo::destructTexture. Keep the accepted clump sheet; nine new sheets preserve each variant's shape and break into matching pipe sections, panels, cables, shell plates or struts. Theme::DEBRIS_SCRAP_VISUALS stores each sheet's measured final-fleck coordinates: clump 4 selected exits, pipe 3, wing 10, canister 5, dish 5, coil 4, tank 11, thruster 7, beam 11, hull 15. Small/medium/large orb diameters remain 1.25/1.8/2.5 units. Whole frames play at 0.075 s/frame; at 0.525 s the saved positions become real soft red glow textures, holding 0.05 s before homing. SCRAP stays at (220,390). Red collectible glow remains an explicit user palette override. No runtime sprite slicing.

P3 event UI: sky-blue BARRICADE countdown and the existing camera/orbit behavior. The 15 October follow-up restores the original legacy asteroid sprite and seven-frame breakup. Keys: barricade_asteroid and barricade_asteroid_destruct. The 96px transparent frame has its original centered rock; padded draw sizes are 15/25/30 units for small/medium/large. Each rock receives a random initial angle and stable 5-240 degrees/s spin. Breakup runs at 0.075 s/frame with no collectible particles or scrap reward. Cosmetic death uses the same simulation clock/reset path as debris effects; it does not enter harvesting.

14 October reskin (destruction playback restored in the 15 October correction): muted lavender-gray plates, dented canister, broken panel, bent pipe and wiring replace the debris art. Preserve 96 x 96 transparent frames and the roughly 36-pixel centered body. Destruction now has eight horizontal frames (768 x 96), ending fully transparent, at 0.075 seconds per frame after the 15 October speed tuning. `Theme::FRAMES_DEBRIS_DESTRUCT` applies to normal debris. Original seven-frame sheet and intact sprite under `assets/textures/legacy/` are reused by barricades after the 15 October restoration. User's explicit eight-frame request supersedes the old seven-frame asset constraint.

| Item | Value | Where |
|---|---|---|
| Virtual canvas | 3840 x 2160 | `GAME_SCREEN_WIDTH`, `GAME_SCREEN_HEIGHT` (moving to `Config.hpp`) |
| Initial window | 1280 x 720, resizable, VSync hint | `Application::Application` |
| Target FPS | 60 | `SetTargetFPS(60)` |
| Scaling | Uniform scale to fit the window, letterboxed, bilinear filter on the canvas | `Application::Run` |
| Mouse | Already mapped to canvas coordinates by `SetMouseOffset` / `SetMouseScale` | `Application::Run` |
| Post-processing | CRT shader (curvature, scanlines, vignette, slight color fringe) plus a barrel-distorted border image | `shader.fs`, `barrel_distortion.fs`, texture `border` |

Lay out every screen element in canvas coordinates (3840 x 2160). Never use `GetScreenWidth()` or `GetScreenHeight()` for layout.

### Safe area

The CRT shader scales the image to 92% and curves it, so content near the edges bends and the corners are cut off.

| Zone | Rule |
|---|---|
| Text and buttons | Inside x 200 to 3640, y 150 to 2010 |
| Important HUD (health, timer, boss bar) | Inside x 220 to 3620, y 150 to 2000 |
| Corners (within 300 px of both edges) | Decoration only, never text |
| World-space gameplay | No restriction; the camera keeps the player centered |

The current HUD already respects this: the kill counter sits at (220, 220), the timer at y 150, the health bar ends at x 3640.

---

## Two Coordinate Spaces

P3 follow-up: `hitbox` and `stats` independently toggle world collision geometry and canvas diagnostics. Stats adds event phase, remaining seconds, live segment count, radius, orbital speed and automatic-trigger state; its expanded panel remains within the safe area. Console background opacity is 0.92 and dropdown opacity 0.95. The stats panel keeps its existing separate 0.25 opacity.

P2 console suggestions: draw a separate vertical dropdown immediately below the input. Show six rows at most, a range/count, and a highlighted keyboard selection. Up/Down and PageUp/PageDown keep the selected row visible. All five shield choices fit together. Theme owns row count, dimensions and opacity; the maximum panel bottom remains inside the canvas safe area. Ctrl+Up/Down preserves command-history navigation.

P2 enemy layering: Animator draws WORLD then FLYING; mid-level ships and their destruction effects use FLYING so low-level crowd sprites never cover them. This changes draw order only, preserving their flight and overlap behavior.

| Draw in | When | Units | Examples |
|---|---|---|---|
| **World space** (between `BeginMode2D(utils::gameCamera)` and `EndMode2D()`) | The object exists in the game world and moves with the camera | World units; camera zoom 20 means 1 unit = 20 canvas px | Ships, bullets, scrap, dock, debris, damage numbers, boss telegraph rings |
| **Screen space** (after `EndMode2D()`) | The element is fixed on screen | Canvas px | HUD, cards, shop, menus, pause, game over, dock arrow |

Font sizes follow the space: damage numbers are 4 units tall in world space (80 canvas px on screen); HUD text is 80 px in screen space. A screen-space size used in world space draws 20 times too big.

To place screen UI over a world object, convert with `GetWorldToScreen2D(worldPos, utils::gameCamera)`.

---

## Fonts

| Key | File | Role | Notes |
|---|---|---|---|
| `primary_font` | `assets/fonts/PerfectDOSVGA437.ttf` | Display: titles, numbers, HUD values, card titles, damage numbers | Pixel DOS look |
| `secondary_font` | `assets/fonts/3270-Regular.ttf` | Body: button labels, card descriptions, shop descriptions, cutscene text | Terminal look |

- Both load with `LoadFontEx(path, 126, nullptr, 0)`: glyphs are rasterized at 126 px. Sizes above 126 are upscaled, which suits the pixel style.
- Both font licenses must be confirmed and recorded in `assets/ASSETS.md` before submission. If either cannot be confirmed, replace it with an OFL-licensed pixel font of similar style and keep the same keys.
- Only the default Raylib font is allowed besides these two, and only on the loading screen (it draws before fonts are needed).
- Use `MeasureTextEx` with the same font, size and spacing you draw with when centering.

### Type scale (screen space, canvas px)

| Token | Size | Font | Use | Current example |
|---|---|---|---|---|
| `TEXT_DISPLAY` | 400 | primary | Main menu title | "SPACE / ABLAZE" |
| `TEXT_TITLE` | 200 | primary | Screen titles, wave banner, "PAUSED", "VICTORY" | new |
| `TEXT_BUTTON_LG` | 150 | secondary | Main menu buttons | menu buttons |
| `TEXT_H1` | 120 | primary/secondary | Kill counter, game-over buttons, shop heading | `KillCounter`, Restart |
| `TEXT_CARD_TITLE` | 100 | primary | Augment card titles, boss name | `Card` |
| `TEXT_BODY` | 80 | primary | HUD timer, stats, shop rows | `GameTimer`, game-over stats |
| `TEXT_BODY_SM` | 64 | secondary | Card and upgrade descriptions, cutscene text | `Card` description |
| `TEXT_CAPTION` | 50 | secondary | Hints, footer, "Press Space to skip" | menu footer |
| `TEXT_WORLD_DAMAGE` | 4 (world units) | primary | Damage numbers | `DamageIndicator` |
| `TEXT_WORLD_LABEL` | 5 (world units) | primary | World labels (tutorial, "DOCK") | controls guide |

No other sizes. If a layout needs a new size, add a token first and record why.

Item 04 adds `Theme::DEBUG_TEXT_WORLD_ID = 2` world units for compact debug IDs. Debug text uses `TEXT_CAPTION` (50 canvas pixels). The F5 terminal is `(220, 310, 2000, 720)` with 30-pixel padding and 64-pixel rows, keeping its first text below the cropped corner. Six recent output rows sit above the input and completion hint; overlong lines fit within the panel (input keeps its end visible). Diagnostics occupy `(220, 1060, 1700, 540)` below the console and the invincibility indicator sits at `(220, 1620)`. All tokens live in Theme. Hitboxes use player accent, enemy toxic and debris muted colors; bullets use crosses at their collision points.

---

## Colors

P1 supplied-pack exception (14 October): preserve the user's CC0 pack pixel colors, including green engine/shield effects and gold guard art, for the requested equipment prototypes. This is an explicit asset-integration scope exception to the palette below; do not recolor or replace the supplied files. A final theme reskin remains the separate art track. Runtime PNGs are in `assets/textures/player/`; combined reference sheets and editable files are in `assets/source/player/` with the original license.

P1 sprite layout: hull/engine/effect/weapon layers use 48×48 frames drawn at 12 world units. Shields use 64×64 frames drawn at 16 units, sharing the same center and rotation. Weapon strips have 7 cannon, 12 heavy, 17 rockets, 14 zapper frames; shield strips have 10 front, 6 sides, 12 round and 10 invincibility frames. Engine idle/powering counts: base 3/4, pulse 4/4, burst 7/6, supercharged 4/4. Projectiles are 32×32 frames: cannon 4, heavy 10, rocket 3, zapper 8. Counts derive from sheet width divided by the Theme frame-size tokens; all new sheets are separate assets, with no changes to old sheet dimensions.

The zapper beam crops columns 13–18 of each 32-pixel frame to remove transparent padding, then tiles at 8 world units along the damage capsule. Its visible width matches the 3-unit damage width. Equipment status starts at (2300,350), inside the safe area: weapon/engine, shield capacity or guard state, equipped Space skill cooldown. `hitbox on` outlines beam, directional shield arcs and projectile swept paths/radii. Player-owned sprite timers pause with simulation.

Debug diagnostic text/IDs use 55% opacity, console text 85%, and both panels 25%. World outlines and the invincibility indicator retain normal opacity. The audio status row reports ON or MUTED; use the console's `mute` command to change it.

Semantic colors make the action readable in a 3-second glance and in a trailer.

| Token | Value | Meaning | Use only for |
|---|---|---|---|
| `COLOR_BG` | `BLACK` | Space | Clear color, letterbox |
| `COLOR_TEXT` | `RAYWHITE` | Neutral text | Body text, card text |
| `COLOR_TEXT_MUTED` | `{128,128,128,255}` | Secondary text | Hints, tutorial labels (SA uses this gray) |
| `COLOR_ACCENT` | `SKYBLUE` | The player and the UI | Buttons, player effects, menu title first line, dock beacon |
| `COLOR_DANGER` | `{255,50,50,255}` | Damage and threat | Kill counter (SA), enemy bullets tint, low-health warning, "Killed by" |
| `COLOR_TOXIC` | `{120,255,90,255}` | Contamination | Enemy glow and tint, windup flash, boss attacks telegraph, toxic UI accents |
| `COLOR_SCRAP` | `{255,196,64,255}` | Reward | Scrap pickups, cargo and credit numbers, buy buttons when affordable |
| `COLOR_LIFE` | `{90,200,120,255}` | The World Tree, hope | Ending cutscene, victory screen, heal effects |
| `COLOR_PANEL` | `{20,20,30,255}` | Panels | Card background (SA), shop rows, pause box |
| `COLOR_PANEL_LINE` | `{60,60,80,255}` | Panel borders | Card inner border (SA), dividers |
| `COLOR_OVERLAY` | `Fade(BLACK, 0.7f)` | Dimming | Behind pause, shop, game over; kill counter box (SA) |
| `COLOR_DISABLED` | `Fade(SKYBLUE, 0.2f)` | Unavailable | Unaffordable or maxed upgrade buttons |

Rules:

- **Red only for damage and danger.** Never for decoration or a selected state.
- **Toxic green only for contamination.** The player's shots and UI never use it.
- **Gold only for scrap and credits.**
- Pair color with a second signal (shape, text or icon) for anything the player must act on, so colorblind players can play.
- Confetti and explosion particles keep their multicolor palettes (SA); they are celebration effects, not signals.

---

## Layout Constants (screen space)

Current positions (SA) and planned additions. All move into `Theme.hpp`.

| Element | Rectangle or position | Notes |
|---|---|---|
| Kill counter | top-left at (220, 220), `TEXT_H1`, red on a dark rounded box | (SA) |
| Game timer | top center, y 150, `TEXT_BODY` | (SA) |
| Health bar | x 2640, y 150, 1000 x 150, images `health_bar` and `health` | (SA); width now uses current / max health |
| Cargo | under the health bar: x 2640, y 330, `TEXT_BODY`, gold, "CARGO 34/60" | new |
| Credits | x 2640, y 430, `TEXT_BODY`, gold, "CREDITS 210" | new |
| Wave label | top center under the timer, y 250, `TEXT_BODY`, "WAVE 4" | new |
| Wave banner | centered, y 700, `TEXT_TITLE`, fades in and out over `WAVE_BANNER_TIME` | new |
| Boss bar | x 920, y 1900, 2000 x 60, name above in `TEXT_CARD_TITLE`, phase tick marks | new |
| Dock arrow | on an ellipse 1500 x 800 around the screen center, pointing to the dock; hidden when the dock is on screen | new, return phase only |
| Tutorial prompt | centered, y 1750, `TEXT_BODY`, muted gray | new |
| Augment cards | 1200 x 300, gap 75, stacked vertically at the center | (SA) |
| Game-over buttons | 800 x 120 at (1520, 1600) and (1520, 1780) | (SA) |
| Menu buttons | 1500 x 150 at x 250, y 1200 + 170 × index | (SA) |

### Dock shop layout (S-06)

```
┌──────────────────────────────────────────────────────────────────────────┐
│  BAYANIHAN DOCK                                        CREDITS  1,240    │  title row y 200
│  Scrap deposited +86                                                     │
│                                                                          │
│  ┌──────────────────────────────────────────────┐   ┌──────────────────┐ │
│  │ BLASTER        ■■□□□  +30% damage   140  [BUY]│   │ HULL  72 / 120   │ │  7 rows, 140 px each
│  │ FIRE CONTROL   ■□□□□  -10% cooldown  90  [BUY]│   │ [REPAIR  24]     │ │  starting y 450
│  │ HULL PLATING   □□□□□  +20 max HP     40  [BUY]│   │                  │ │
│  │ ARMOR          ...                            │   │                  │ │
│  │ THRUSTERS      ...                            │   │                  │ │
│  │ TRACTOR BEAM   ...                            │   │ [ LAUNCH WAVE 5 ]│ │  launch = primary
│  │ CARGO HOLD     ...                            │   └──────────────────┘ │
│  └──────────────────────────────────────────────┘                        │
└──────────────────────────────────────────────────────────────────────────┘
 rows panel x 220..2700        side panel x 2800..3620
```

- One primary action on this screen: **Launch**, in `COLOR_ACCENT`.
- Level pips: filled squares in `COLOR_SCRAP`, empty squares in `COLOR_PANEL_LINE`.
- An unaffordable or maxed row uses `COLOR_DISABLED` and its button does nothing; "MAX" replaces the price at level 5.
- Buying plays `button_click` and briefly flashes the row gold.

---

## Sprites and AI-Generated Assets

### Orientation and size rules

15 October low-enemy reskin: three recognizable mutated trash objects, with fronts/claws toward the top and trailing cables toward the bottom. Variant A is a crushed ribbed tin can with torn-lid jaws; B a leaking rectangular battery with two terminals; C a cracked monitor with a green eye and broken bracket claws. Shared dusty mauve/copper metal, dark purple mutation and toxic-green eyes; crisp binary-alpha pixel art. Original 64px frame padding and 15-unit world size are retained, with the animated body bounded to 32px. Idle loops remain 10/5/5 frames at 0.1 s/frame; corresponding object-specific breakups remain 8/8/7 frames at 0.1 s/frame. Death starts with the exact exported idle frame and ends transparent.

- **All ship and enemy sprites face UP** in the source image. The code rotates sprites by `atan2(direction) + 90°`, which assumes the art points toward the top of the image.
- Sprite sheets are **horizontal strips**: frames left to right, all the same size, no padding. The code divides the width by the frame count.
- Transparent PNG. Pixel art, consistent pixel density across all sprites.
- **A reskin keeps the exact pixel size and frame count of the file it replaces.** Then no code changes. If a new frame count is unavoidable, update the matching `Theme::FRAMES_*` constant in the same commit.

### Sprite table

Existing sheets (sizes measured from the current files). "Frame" is width x height of one frame.

| Key | File | Frame | Frames | World size | Reskin as |
|---|---|---|---|---|---|
| `player_acceleration` | player_accelerating.png | 32 x 32 | 4 | 8 | Collector ship, thrusters on |
| `player_deacceleration` | player_deaccelerating.png | 32 x 32 | 3 | 8 | Collector ship, idle |
| `player_bullet` | player_bullet.png | 249 x 144 | 1 | 8 x 5 | Sky-blue bolt |
| `enemy_bullet` | enemy_bullet.png | 233 x 134 | 1 | 8 x 8 | Toxic glob |
| `projectile_impact` | projectile_impact.png | 64 x 64 | 8 | 10 (14 heavy) | Sky-blue contact burst through fading aftermath |
| `low_level_enemy1` | low_level_enemy1.png | 64 x 64 | 10 | 15 | Can biter |
| `low_level_enemy2` | low_level_enemy2.png | 64 x 64 | 5 | 15 | Battery crawler |
| `low_level_enemy3` | low_level_enemy3.png | 64 x 64 | 5 | 15 | Monitor parasite |
| `low_level_enemy1_destruct` | | 64 x 64 | 8 | 15 | Burst into scrap |
| `low_level_enemy2_destruct` | | 64 x 64 | 8 | 15 | |
| `low_level_enemy3_destruct` | | 64 x 64 | 7 | 15 | |
| `mid_level_enemy` | mid_level_enemy.png | 64 x 64 | 12 | 15 | Rogue Satellite (spinning panels) |
| `mid_level_enemy_destruct` | | 64 x 64 | 7 | 15 | |
| `debris` | debris.png | 96 x 96 | 1 | fixed by variant | Scrap clump plus nine variants |
| `debris_destruct` | debris_destruct.png | 96 x 96 | 8 | reference only | Previous breakup sheet; live fragments now use intact art |
| `background1` to `background4` | background1-4.png | 500 x 500 | 1 | tiled parallax | Orbit layers: far stars, Earth haze, debris field, near dust |
| `health_bar`, `health` | healthBar.png, health.png | 128 x 16 | 1 | screen 1000 x 150 | Hull bar frame and fill |
| `wasd_keys` | wasd_keys.png | 67 x 43 | 3 | world 16 x 10 | Keep |
| `e_key` | e_key.png | 19 x 21 | 3 | world 5 x 5 | Keep |
| `game_over_text` | game_over_text.png | 394 x 47 | 10 | screen 1800 x 300 | "SIGNAL LOST" or keep |
| `main_menu_background` | MainMenuBackground.png | 900 x 512 | 5 x 2 grid | full screen | New menu backdrop (Earth and orbit) |
| `exit_animation` | ExitAnimation.png | 1920 x 1080 | 4 x 7 grid | full screen | Keep or replace |
| `border` | border_raw.png | 480 x 320 | 1 | full screen | Keep (CRT bezel) |
| `window` | window.png | 100 x 114 | 1 | | Unused; available for panels |

New sheets (planned). Sizes are recommendations; record the final ones here and in `Theme.hpp`.

| Key | Frame | Frames | World size | Content |
|---|---|---|---|---|
| `high_level_enemy` | 64 x 64 | 6 | 22 | Compactor: boxy crusher with glowing toxic seams |
| `high_level_enemy_destruct` | 64 x 64 | 8 | 22 | |
| `boss_hoarder` | 192 x 192 | 6 | 50 | The Hoarder: sphere of fused junk |
| `boss_hoarder_destruct` | 192 x 192 | 10 | 50 | |
| `boss_core` | 256 x 256 | 8 | 60 | The Core: junk shell around a pulsing green core |
| `boss_core_destruct` | 256 x 256 | 12 | 60 | |
| `boss_bullet` | 32 x 32 | 1 | 6 x 6 | Large toxic orb |
| `scrap_small`, `scrap_medium`, `scrap_large` | 16 x 16 | 1 | 2, 3, 4 | Gold metal bits (values 1, 5, 10) |
| `dock` | 256 x 256 | 1 | 40 | Bayanihan Dock station, top-down |
| `dock_arrow` | 64 x 64 | 1 | screen 120 | Chevron |
| `cutscene_01` to `cutscene_07` | 1920 x 1080 | 1 | full screen | Intro slides |
| `ending_01` to `ending_04` | 1920 x 1080 | 1 | full screen | Ending slides |

### AI asset prompt rules

- Describe the subject and style only. Never name an existing game, studio, film, artist or brand.
- Keep a shared style line and reuse it for every prompt, for example: "top-down 2D pixel art sprite, 64x64, facing up, dark outline, limited palette, toxic green glow accents, transparent background".
- Save the prompt, tool, model and date in `assets/ASSETS.md` for every generated file. Form 03 needs it.
- Clean up AI output by hand: fix frame alignment, remove stray pixels, unify the palette. Note the edits in `ASSETS.md`.

---

## Audio

| Key | Kind | Use | Status |
|---|---|---|---|
| `home_music` | music | Main menu | Exists; confirm provenance or replace |
| `game_music` | music | Waves | Currently a third-party track; **must be replaced** |
| `boss_music` | music | Boss waves | New |
| `dock_music` | music | Dock shop (optional, can reuse `home_music`) | New |
| `cutscene_music` | music | Intro and ending | New |
| `player_damaged`, `player_damaged_2` | sound | Player hit | Exists |
| `button_click` | sound | UI clicks | Exists |
| `exit_sound` | sound | Exit animation | Exists |
| `game_over` | sound | Death | Exists |
| `player_atk_sound.mp3` | sound | Player shot (loaded by path in `Player`) | Register as `player_shoot` in item 05 |
| `bullet_impact` | sound | Player projectile contact | New; original synthesized PCM |
| `score_sound.wav` | sound | Kill (loaded by path in `Game`) | Register as `kill` in item 05 |
| `scrap_pickup` | sound | Scrap collected | New |
| `dock_deposit` | sound | Deposit at the dock | New |
| `boss_roar` | sound | Boss intro | New |
| `charge_windup` | sound | Compactor windup | New |

- Music streams need `UpdateMusicStream` every frame from the active scene. Switching tracks: `StopMusicStream(old)`, `PlayMusicStream(new)`.
- Overlapping SFX use sound aliases (see `library-docs.md`).
- Every music and sound file needs a provenance row.

---

## Feedback ("Juice") Rules

Reuse what exists before adding new effects.

| Event | Feedback | Exists? |
|---|---|---|
| Enemy hit | Damage number, 0.08 s red reaction tint, contact burst and aftermath | Yes |
| Enemy killed | Destruct animation, kill sound, kill counter wobble | Yes |
| Player hit | Red edge overlay, red flashing ship, hit sounds, knockback | Yes |
| Augment pick | Confetti, card animations | Yes |
| Player death | Explosion confetti, overlay slide, game-over text | Yes |
| Scrap collected | Pickup sound, cargo number pulse | New |
| Cargo full | "CARGO FULL" in gold under the cargo number for 1.5 s | New |
| Deposit | Numbers count from cargo into credits over 0.6 s | New |
| Wave start | Banner "WAVE N" | New |
| Boss intro | Name banner, `boss_roar`, background tint shifts toward toxic green | New (the code has a note to tint the background during bosses) |
| Compactor windup | Toxic flash on the sprite | New |
| Boss death | Explosion confetti at the boss, large scrap spray | Reuse |

No camera shake by default; the CRT shader already adds motion. Add shake only if the balance pass finds hits feel weak, and keep it under 1 world unit.

---

## Screen Specifications

Top-to-bottom composition. Screen IDs from `project-overview.md`.

### S-01 Loading (`LoadingScreen`)
Default-font progress text centered at y 1800. Replace with a `TEXT_BODY` progress bar only if time allows (fonts are already loaded before this scene).

### S-02 Intro cutscene (`IntroCutscene`)
Full-screen slide image with a slow 3% zoom over its duration. Bottom text box: `COLOR_OVERLAY` panel x 300 to 3540, y 1550 to 1950, text in `secondary_font` `TEXT_BODY_SM`, typewriter at 40 characters per second. Caption bottom-right "SPACE: NEXT   ESC: SKIP" in `TEXT_CAPTION`, muted.

### S-03 Main menu (`MainMenu`)
Animated background. Title (`TEXT_DISPLAY`): new game title in two lines (first line sky blue, second line toxic green, both at 55% opacity like the SA title). Buttons, left-aligned: Story, Endless, Leaderboard, Credits, Exit. Footer: "DOST Level Up 3.0 - 2026" in `TEXT_CAPTION`. Remove "Equity Quest - 2024" and the Settings button.

### S-04 Gameplay HUD
Health bar, cargo and credits top right. Kill counter top left. Timer and wave label top center. Boss bar bottom center during boss waves. Dock arrow during the return phase. Tutorial prompts during wave 1. "SIGNAL WEAK" warning near the arena edge.

### S-05 Augment pick
Existing card stack and confetti. Header above the cards: "WAVE N CLEARED" in `TEXT_TITLE`.

### S-06 Dock shop
See the layout above. Entering plays the deposit count-up first, then enables the buttons.

### S-07 Pause (`PauseOverlay`)
`COLOR_OVERLAY` over the frozen game. "PAUSED" in `TEXT_TITLE` at y 700. Buttons: Resume (primary), Quit to Menu. P or Esc resumes.

### S-08 Game over
Existing overlay and stats, plus: mode, wave reached, scrap lost (cargo at death). If the score qualifies, a name entry box appears before the buttons (`NameEntry`, `TEXT_H1`, blinking cursor, Enter to save).

### S-09 Ending cutscene (`EndingCutscene`)
Same layout as the intro, `COLOR_LIFE` accents. Final card shows run stats and "ENDLESS MODE: THE JUNK KEEPS COMING".

### S-10 Leaderboard (`LeaderboardScene`)
Title "LEADERBOARD". Two columns, Story (left) and Endless (right): rank, name, score, and time or waves. The latest entry is highlighted in `COLOR_SCRAP`. Back button.

### S-11 Credits (`CreditsScene`)
Scrolling `secondary_font` text: game title, team and roles, coach, built with Raylib, AI tools and what they were used for, asset and font licenses, "Made for DOST Level Up 3.0". Back button.

---

## Do Nots

- Never draw text outside the safe area.
- Never hard-code a color, font size or UI position in a `.cpp`; use `Theme`.
- Never use red, toxic green or gold outside their meanings.
- Never draw HUD inside `BeginMode2D`, or world objects after `EndMode2D`.
- Never use more than one primary action on a screen.
- Never add art that faces a direction other than up.
- Never change a sprite's frame count without updating `Theme.hpp` and the sprite table.

---

## Initial `src/Theme.hpp`

Item 03 creates this file. After that, the header is the source of truth.

```cpp
#pragma once
#include "raylib.h"

namespace Theme {

// ---------- Fonts (ResourceManager keys) ----------
inline constexpr const char* FONT_PRIMARY   = "primary_font";
inline constexpr const char* FONT_SECONDARY = "secondary_font";

// ---------- Type scale (canvas px unless noted) ----------
inline constexpr float TEXT_DISPLAY      = 400.0f;
inline constexpr float TEXT_TITLE        = 200.0f;
inline constexpr float TEXT_BUTTON_LG    = 150.0f;
inline constexpr float TEXT_H1           = 120.0f;
inline constexpr float TEXT_CARD_TITLE   = 100.0f;
inline constexpr float TEXT_BODY         = 80.0f;
inline constexpr float TEXT_BODY_SM      = 64.0f;
inline constexpr float TEXT_CAPTION      = 50.0f;
inline constexpr float TEXT_WORLD_DAMAGE = 4.0f;   // world units
inline constexpr float TEXT_WORLD_LABEL  = 5.0f;   // world units
inline constexpr float TEXT_SPACING      = 1.0f;

// ---------- Colors ----------
inline constexpr Color COLOR_BG         = {0, 0, 0, 255};
inline constexpr Color COLOR_TEXT       = {245, 245, 245, 255};   // RAYWHITE
inline constexpr Color COLOR_TEXT_MUTED = {128, 128, 128, 255};
inline constexpr Color COLOR_ACCENT     = {102, 191, 255, 255};   // SKYBLUE
inline constexpr Color COLOR_DANGER     = {255, 50, 50, 255};
inline constexpr Color COLOR_TOXIC      = {120, 255, 90, 255};
inline constexpr Color COLOR_SCRAP      = {255, 196, 64, 255};
inline constexpr Color COLOR_LIFE       = {90, 200, 120, 255};
inline constexpr Color COLOR_PANEL      = {20, 20, 30, 255};
inline constexpr Color COLOR_PANEL_LINE = {60, 60, 80, 255};
inline constexpr float OVERLAY_ALPHA    = 0.7f;                   // Fade(BLACK, OVERLAY_ALPHA)
inline constexpr float DISABLED_ALPHA   = 0.2f;                   // Fade(COLOR_ACCENT, DISABLED_ALPHA)

// ---------- Safe area ----------
inline constexpr Rectangle SAFE_AREA = {200.0f, 150.0f, 3440.0f, 1860.0f};

// ---------- HUD layout ----------
inline constexpr Vector2   KILL_COUNTER_POS = {220.0f, 220.0f};
inline constexpr float     TIMER_Y          = 150.0f;
inline constexpr float     WAVE_LABEL_Y     = 250.0f;
inline constexpr Rectangle HEALTH_BAR       = {2640.0f, 150.0f, 1000.0f, 150.0f};
inline constexpr Vector2   CARGO_POS        = {2640.0f, 330.0f};
inline constexpr Vector2   CREDITS_POS      = {2640.0f, 430.0f};
inline constexpr float     WAVE_BANNER_Y    = 700.0f;
inline constexpr Rectangle BOSS_BAR         = {920.0f, 1900.0f, 2000.0f, 60.0f};
inline constexpr Vector2   DOCK_ARROW_RADII = {1500.0f, 800.0f};
inline constexpr float     TUTORIAL_Y       = 1750.0f;

// ---------- Cards and buttons (SA values) ----------
inline constexpr float CARD_WIDTH  = 1200.0f;
inline constexpr float CARD_HEIGHT = 300.0f;
inline constexpr float CARD_GAP    = 75.0f;
inline constexpr Rectangle MENU_BUTTON_FIRST = {250.0f, 1200.0f, 1500.0f, 150.0f};
inline constexpr float     MENU_BUTTON_STEP  = 170.0f;

// ---------- Sprite sheet frame counts (horizontal strips) ----------
inline constexpr int FRAMES_PLAYER_ACCEL          = 4;
inline constexpr int FRAMES_PLAYER_IDLE           = 3;
inline constexpr int FRAMES_LOW_ENEMY[3]          = {10, 5, 5};
inline constexpr int FRAMES_LOW_ENEMY_DESTRUCT[3] = {8, 8, 7};
inline constexpr int FRAMES_MID_ENEMY             = 12;
inline constexpr int FRAMES_MID_ENEMY_DESTRUCT    = 7;
inline constexpr int FRAMES_HIGH_ENEMY            = 6;    // planned
inline constexpr int FRAMES_HIGH_ENEMY_DESTRUCT   = 8;    // planned
inline constexpr int FRAMES_DEBRIS_DESTRUCT     = 7;
inline constexpr int FRAMES_BOSS_HOARDER          = 6;    // planned
inline constexpr int FRAMES_BOSS_HOARDER_DESTRUCT = 10;   // planned
inline constexpr int FRAMES_BOSS_CORE             = 8;    // planned
inline constexpr int FRAMES_BOSS_CORE_DESTRUCT    = 12;   // planned
inline constexpr float FRAME_TIME                 = 0.1f; // SA

} // namespace Theme
```

P1 default restoration: Default uses the existing `player_acceleration` (4 frames) / `player_deacceleration` (3 frames) sheets at 32×32 pixels per frame, 8×8 world-unit draw size and 0.1 s per frame. The original `player_bullet` is retained. Gunner names the modular cannon/base-engine/no-shield preset. All presets draw without shield overlays; the separate supplied shield sheets are used only when explicitly equipped. No assets were changed.
