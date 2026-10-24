# Background art handoff - SCRAPBOUND: Last Hope

**24 October 2026. Instructions only.** Owner explicitly assigns background production to the teammate who will implement the game. This checkpoint creates no images, animations, textures, prompts submitted to an image service or runtime changes. The teammate may create original art or use an approved generation workflow later and must record provenance at delivery.

Read [UI rules](../../context/ui-rules.md), [hub/arena layouts](../02-gameplay/beta-layouts.md), [storyboard](../01-story/story-context.md) and [world canon](../01-story/world-and-campaign.md) before production. Keep the existing accepted player/enemy/debris art. Use original subject descriptions; no real brands, companies, people, games, movies or named-artist references in game content or prompts.

## Shared direction

- Original 2D space pixel art with crisp shapes, restrained texture and the existing dark space/mauve-metal palette. The playfield reads clearly behind the current small ship, red scrap orbs, hostile shots and skill effects.
- Deep near-black/navy space, muted indigo/purple haze and desaturated gray metal. HOPE has soft warm-white inhabited windows and restrained player-blue service lighting. Contaminated sites have muted organic seams and sparse subdued green; bright threat green remains reserved for actual combat tells.
- Preserve the biological story: engineered waste-eaters live inside bound scrap shells. Scenery may show infested recovery equipment and fibrous binding, not a different autonomous-machine or magical-tree premise.
- Keep the central fighting region low contrast. Most large recognizable wrecks sit at the margins or in distant layers. No painted ships, enemies, bullets, pickups, interactable portals, health bars, route nodes, labels or text in backdrop art.
- Decorative wreckage is visibly distant/non-solid. Never paint a wall across a navigable route unless the implementation also authors actual geometry. Background changes do not alter collision or difficulty.
- Preserve the logical 3840 x 2160 canvas and existing CRT-safe text zones. Inspect at the real 1280 x 720 window, with CRT on and off. A striking still image is insufficient if projectiles disappear against it.

## Production inventory and formats

The minimum reusable set is **11 PNG files**: four shared tiles, one menu sheet, one hub landmark plate, one map plate and four level landmark overlays. Story shots can reuse these layers before requesting extra scenery. The new-asset dimensions below are authoring defaults; existing replacements must keep the verified dimensions/frame layout.

| Delivery ID | Asset / intended key | Format and size | Content / integration |
|---|---|---|---|
| BG01 | background1 | Existing replacement: 500 x 500 PNG, one frame | Sparse distant stars and opaque dark base; seamless on both axes |
| BG02 | background3 | Existing replacement: 500 x 500 RGBA PNG, one frame | Transparent, subdued gas/haze; seamless on both axes |
| BG03 | background4 | Existing replacement: 500 x 500 RGBA PNG, one frame | Faint distant fragmented silhouettes; seamless; no dense foreground rocks |
| BG04 | background2 | Existing replacement: 500 x 500 RGBA PNG, one frame | Very sparse fine dust/near specks; seamless; low contrast |
| BG05 | main_menu_background | Existing replacement: 4500 x 1024 PNG; 5 columns x 2 rows; ten 900 x 512 frames | Earth/HOPE orbital composition, quiet left/lower region for buttons, gentle loop |
| BG06 | Proposed bg_hub_landmark | New 1024 x 1024 RGBA PNG; non-repeating | Reused inhabited colony modules/trusses framing the mothership/service area; clean approach lanes |
| BG07 | Proposed bg_campaign_map | New 1920 x 1080 PNG; one frame | Quiet navigation-space plate; no baked nodes, lines, names, ratings or locks |
| BG08 | Proposed bg_c01_landmark | New 1024 x 1024 RGBA PNG; non-repeating | Outer Approach: sparse salvage-route structures and distant Earth-side orbital context |
| BG09 | Proposed bg_c02_landmark | New 1024 x 1024 RGBA PNG; non-repeating | Relay Graveyard: broken receiver dishes, cable loops, dead relay frames |
| BG10 | Proposed bg_c03_landmark | New 1024 x 1024 RGBA PNG; non-repeating | Freight Ruins: damaged cargo shells, broken loading trusses, distant freight debris |
| BG11 | Proposed bg_c04_landmark | New 1024 x 1024 RGBA PNG; non-repeating | Source Nest: a large infested recovery site with scrap-bound biological structures at the margins |

Resource keys marked Proposed do not exist yet. The teammate registers delivered assets through ResourceManager during integration. Preserve original replaced files in the existing archive workflow and record final paths/keys. Do not rename working textures or assume writing this table loads them.

Existing source dimensions were checked from PNG headers: four 500 x 500 tiles and MainMenuBackground.png at 4500 x 1024. MainMenu slices five columns/two rows and advances at 0.1 seconds per frame. Preserve ten frames and a smooth one-second loop for a direct swap; no frame-count/cadence redesign is requested.

## Existing parallax order - preserve on a direct swap

Game currently draws **background1 -> background3 -> background4 -> background2**, with factors **0.2 / 0.4 / 0.7 / 1.0**. Numbered filenames are not depth order. Use the four shared tiles for all modes and add the level's non-repeating landmark layer under combat entities. This provides location identity without producing sixteen independent tile sets.

Only the far base needs opaque pixels. Near layers preserve transparency instead of covering the previous layer with opaque black. Validate edge wrapping in a 3 x 3 tile preview: no seams, bright cross pattern, duplicate planets or repeating station silhouettes. Keep Earth, the mothership and major source structures out of seamless tiles; show them through a non-repeating composition.

## Scene direction

**Main menu:** a damaged Earth and a recognizable inhabited orbital refuge. Place the strongest silhouette toward the upper/right side, with dark visual breathing room where title/buttons render. Window lights/dust can animate gently; no camera jump, strobing glow or reset seam. Title and team text are drawn by UI, never embedded in the sheet.

**HOPE hub:** warm, maintained life amid reused infrastructure. Habitat pods, patched solar arrays, life-support conduits and a few lit windows communicate that people live here. Keep the actual arrival, four mode gates, workshop and repair approaches clear according to the layout. Coordinate the decorative colony plate with the separately planned Dock/mothership sprite so the same ship is not painted twice. The player remains in the ship; do not add a walking interior or new room-navigation system.

**Campaign map:** a calm star field/navigation display with minimal detail. The four circles, route lines, status shapes and previews are runtime UI. Leave their positions unobstructed. The map must remain usable if a future content expansion adds nodes; do not bake the beta graph into the art.

**Outer Approach:** open space with scattered distant structural fragments. It introduces salvage operations while keeping a new player's first fights readable. Use the least visual clutter of the four locations.

**Relay Graveyard:** cold, quiet communications wreckage. Curved dishes and loose cable silhouettes give identity without resembling active homing projectiles or outlining false collision walls. Relays remain dim; bright flashes belong to real attacks.

**Freight Ruins:** larger rectangular cargo-shell fragments and broken handling frames. Keep clear gaps and faded depth cues. Painted cargo is not harvestable debris; actual destructible debris still uses the accepted existing entity/art lifecycle.

**Source Nest:** damaged recovery infrastructure partly enclosed by bound plates, dark organic joins and restrained contamination. Communicate a localized biological source rather than an entire planet healed/destroyed on screen. Central space stays open for Nestheart's ring-gap tells and enemy silhouettes.

**Swarm/Chaos:** reuse the shared space stack and selected neutral distant salvage dressing. Chaos intensity comes from real enemies/bosses. Do not make its backdrop brighter/busier as a substitute for gameplay pressure.

**Boss mode:** reuse the matching boss-associated location overlay: Shellback/Outer Approach, Coilmaw/Relay, Brood Hauler/Freight and Nestheart/Source. No independent boss backdrop set is required for beta. Boss bars, arrival warnings and attack telegraphs stay in foreground code.

**Intro/ending:** reuse Earth, colony and source layers with original animated actions from the storyboard. Benign cleanup precedes mutation; colony windows communicate habitation; the ending shows the beginning of sustained recovery, not instant planetary restoration. Additional narrative scenery is produced only when its shot requires it, with original English AI narration handled separately.

## Prompt starting points for the teammate

These are written briefs only; no generation is performed here. Adapt dimensions/composition to the delivery row and preserve the shared palette.

- Shared tile: "Original seamless 2D pixel-art deep-space layer, sparse tiny distant stars, near-black navy base, restrained desaturated indigo haze, very low contrast, crisp small-scale texture, no planets or large objects, no text, no ships, no interface, seamless horizontally and vertically."
- Hub landmark: "Original top-down 2D pixel-art orbital refuge made from reused habitat modules, patched trusses and life-support equipment, warm-white inhabited windows, restrained cool-blue service lighting, dark mauve-gray metal, broad clear flight approaches, transparent outer background, no characters, no text, no interface or portals."
- Source landmark: "Original top-down 2D pixel-art distant infested orbital recovery structure, living waste-eater tissue concealed in bound scrap shells, muted purple organic joins and desaturated metal, sparse subdued contamination, dark open central fighting space, detail concentrated at margins, transparent outer background, no combat effects, no enemies, no text or interface."

For the menu, storyboard each of ten cells before producing a sheet; independent random images do not make a registered loop. For other level overlays, substitute the scene's actual structures instead of adding arbitrary visual noise.

## Delivery checklist

- Original/source files, final PNGs, intended key/path, dimensions/frame count and preview available.
- A 3 x 3 seam check for each tile; ten-frame contact sheet and loop preview for the menu.
- Native screenshots at real camera zoom with enemies, scrap, bullets, boss tells and safe-area UI visible; inspect both busy combat and a quiet scene.
- Validate transparency, edge cropping and consistent pixel scale; no blurred resize, watermark, baked UI or unwanted real-world references.
- Low/Medium/High keep the same location identity and required readability. Cosmetic dust/lights may reduce on lower quality; collision/targets/RNG never change.
- Every new/replaced final asset gets assets/ASSETS.md provenance, creator/tool/model when known, source/license or AI disclosure, date, prompt and edits. No row is claimed complete until the file exists and is inspected.
- Confirm performance using actual integrated layers. The number of supplied images does not certify load times, GPU memory or FPS.

Art delivery and runtime integration remain PROJECT-07/A6/T05/T09/T10 work. This brief completes instructions only.
