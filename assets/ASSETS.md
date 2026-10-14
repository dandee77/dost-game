# Asset provenance

## Unique debris destruction and barricade monster (15 October 2026)

Built-in OpenAI image_gen created nine shape-specific destruction sheets using the corresponding intact sprites as references, plus one mutated trash creature and its inward-collapse sheet. Image model not exposed; no third-party pack and no CC0 claim. Source prompts: `source/debris/destruction-generation.json` and `source/barricade/generation.json`. Native final-particle measurements: `source/debris/destruction-particles.json` and Theme. Export scripts preserve a shared registration across cells, nearest-neighbor pixel art and binary alpha; each new first frame is the exact intact sprite. Eight 96px frames per sheet, final frame blank. Monster body max 32px within 96px padding; no pickup particles.

| File | Resource key | Source / author | License | Edits | Date |
|---|---|---|---|---|---|
| textures/debris/pipe_destruct.png | debris_pipe_destruct | OpenAI built-in image_gen; user/Codex direction | AI-generated; reference provenance audit pending | Uniform registered pixel export, 768 x 96 RGBA | 2026-10-15 |
| source/debris/destruction/pipe.png | - | OpenAI built-in image_gen | AI-generated; reference provenance audit pending | Unmodified generated source | 2026-10-15 |
| textures/debris/wing_destruct.png | debris_wing_destruct | OpenAI built-in image_gen; user/Codex direction | AI-generated; reference provenance audit pending | Uniform registered pixel export, 768 x 96 RGBA | 2026-10-15 |
| source/debris/destruction/wing.png | - | OpenAI built-in image_gen | AI-generated; reference provenance audit pending | Unmodified generated source | 2026-10-15 |
| textures/debris/canister_destruct.png | debris_canister_destruct | OpenAI built-in image_gen; user/Codex direction | AI-generated; reference provenance audit pending | Uniform registered pixel export, 768 x 96 RGBA | 2026-10-15 |
| source/debris/destruction/canister.png | - | OpenAI built-in image_gen | AI-generated; reference provenance audit pending | Unmodified generated source | 2026-10-15 |
| textures/debris/dish_destruct.png | debris_dish_destruct | OpenAI built-in image_gen; user/Codex direction | AI-generated; reference provenance audit pending | Uniform registered pixel export, 768 x 96 RGBA | 2026-10-15 |
| source/debris/destruction/dish.png | - | OpenAI built-in image_gen | AI-generated; reference provenance audit pending | Unmodified generated source | 2026-10-15 |
| textures/debris/coil_destruct.png | debris_coil_destruct | OpenAI built-in image_gen; user/Codex direction | AI-generated; reference provenance audit pending | Uniform registered pixel export, 768 x 96 RGBA | 2026-10-15 |
| source/debris/destruction/coil.png | - | OpenAI built-in image_gen | AI-generated; reference provenance audit pending | Unmodified generated source | 2026-10-15 |
| textures/debris/tank_destruct.png | debris_tank_destruct | OpenAI built-in image_gen; user/Codex direction | AI-generated; reference provenance audit pending | Uniform registered pixel export, 768 x 96 RGBA | 2026-10-15 |
| source/debris/destruction/tank.png | - | OpenAI built-in image_gen | AI-generated; reference provenance audit pending | Unmodified generated source | 2026-10-15 |
| textures/debris/thruster_destruct.png | debris_thruster_destruct | OpenAI built-in image_gen; user/Codex direction | AI-generated; reference provenance audit pending | Uniform registered pixel export, 768 x 96 RGBA | 2026-10-15 |
| source/debris/destruction/thruster.png | - | OpenAI built-in image_gen | AI-generated; reference provenance audit pending | Unmodified generated source | 2026-10-15 |
| textures/debris/beam_destruct.png | debris_beam_destruct | OpenAI built-in image_gen; user/Codex direction | AI-generated; reference provenance audit pending | Uniform registered pixel export, 768 x 96 RGBA | 2026-10-15 |
| source/debris/destruction/beam.png | - | OpenAI built-in image_gen | AI-generated; reference provenance audit pending | Unmodified generated source | 2026-10-15 |
| textures/debris/hull_destruct.png | debris_hull_destruct | OpenAI built-in image_gen; user/Codex direction | AI-generated; reference provenance audit pending | Uniform registered pixel export, 768 x 96 RGBA | 2026-10-15 |
| source/debris/destruction/hull.png | - | OpenAI built-in image_gen | AI-generated; reference provenance audit pending | Unmodified generated source | 2026-10-15 |
| textures/barricade_enemy.png | barricade_enemy | OpenAI built-in image_gen; user/Codex direction | AI-generated; reference provenance audit pending | 32px body centered in 96px RGBA | 2026-10-15 |
| textures/barricade_enemy_destruct.png | barricade_enemy_destruct | OpenAI built-in image_gen; user/Codex direction | AI-generated; reference provenance audit pending | Eight 96px frames; inward collapse | 2026-10-15 |
| source/barricade/monster-generated.png | - | OpenAI built-in image_gen; user/Codex direction | AI-generated; reference provenance audit pending | Unmodified generated source | 2026-10-15 |
| source/barricade/monster-destruct-generated.png | - | OpenAI built-in image_gen; user/Codex direction | AI-generated; reference provenance audit pending | Unmodified generated source | 2026-10-15 |

## Glowing scrap pickup correction (15 October 2026)

Built-in OpenAI image_gen created a red orb with an actual transparent soft glow halo. Exact prompt, export settings and saved destruction-frame particle coordinates: `source/debris/harvest-handoff.json`. No third-party art pack used. Underlying image model was not exposed by the tool.

| File | Resource key | Source / author | License | Edits | Date |
|---|---|---|---|---|---|
| textures/scrap_orb.png | scrap_orb | OpenAI built-in image_gen, user/Codex direction | AI-generated; no CC0 claim | 96 x 96 RGBA bicubic export preserving continuous alpha | 2026-10-15 |
| source/debris/scrap-orb-generated.png | - | OpenAI built-in image_gen | AI-generated; no CC0 claim | Unmodified generated source | 2026-10-15 |

## Ten debris variants and harvesting (15 October 2026)

The accepted clump is textures/debris.png; textures/debris_destruct.png is now used only by that clump. Nine other variants have dedicated *_destruct.png sheets, and the barricade has separate monster art (see newest provenance entries). Intact debris art, accepted clump destruction, red orb texture and original legacy files are unchanged.

Nine new variants plus the existing clump make ten. Exact prompts and original output paths are recorded in source/debris/variants.json; source images are preserved under source/debris/variants/. Built-in image tool used (underlying image model not exposed); no third-party pack added and no CC0 claim made. Team art review pending.

| File | Resource key | Source / author | License | Edits | Date |
|---|---|---|---|---|---|
| textures/debris/pipe.png | debris_pipe | OpenAI built-in image_gen, user/Codex direction | AI-generated; supplied style reference audit pending | Nearest-neighbor 96 x 96 export, centered body at most 36 x 36, binary alpha | 2026-10-15 |
| source/debris/variants/pipe.png | - | OpenAI built-in image_gen | AI-generated; supplied style reference audit pending | Unmodified generated source | 2026-10-15 |
| textures/debris/wing.png | debris_wing | OpenAI built-in image_gen, user/Codex direction | AI-generated; supplied style reference audit pending | Nearest-neighbor 96 x 96 export, centered body at most 36 x 36, binary alpha | 2026-10-15 |
| source/debris/variants/wing.png | - | OpenAI built-in image_gen | AI-generated; supplied style reference audit pending | Unmodified generated source | 2026-10-15 |
| textures/debris/canister.png | debris_canister | OpenAI built-in image_gen, user/Codex direction | AI-generated; supplied style reference audit pending | Nearest-neighbor 96 x 96 export, centered body at most 36 x 36, binary alpha | 2026-10-15 |
| source/debris/variants/canister.png | - | OpenAI built-in image_gen | AI-generated; supplied style reference audit pending | Unmodified generated source | 2026-10-15 |
| textures/debris/dish.png | debris_dish | OpenAI built-in image_gen, user/Codex direction | AI-generated; supplied style reference audit pending | Nearest-neighbor 96 x 96 export, centered body at most 36 x 36, binary alpha | 2026-10-15 |
| source/debris/variants/dish.png | - | OpenAI built-in image_gen | AI-generated; supplied style reference audit pending | Unmodified generated source | 2026-10-15 |
| textures/debris/coil.png | debris_coil | OpenAI built-in image_gen, user/Codex direction | AI-generated; supplied style reference audit pending | Nearest-neighbor 96 x 96 export, centered body at most 36 x 36, binary alpha | 2026-10-15 |
| source/debris/variants/coil.png | - | OpenAI built-in image_gen | AI-generated; supplied style reference audit pending | Unmodified generated source | 2026-10-15 |
| textures/debris/tank.png | debris_tank | OpenAI built-in image_gen, user/Codex direction | AI-generated; supplied style reference audit pending | Nearest-neighbor 96 x 96 export, centered body at most 36 x 36, binary alpha | 2026-10-15 |
| source/debris/variants/tank.png | - | OpenAI built-in image_gen | AI-generated; supplied style reference audit pending | Unmodified generated source | 2026-10-15 |
| textures/debris/thruster.png | debris_thruster | OpenAI built-in image_gen, user/Codex direction | AI-generated; supplied style reference audit pending | Nearest-neighbor 96 x 96 export, centered body at most 36 x 36, binary alpha | 2026-10-15 |
| source/debris/variants/thruster.png | - | OpenAI built-in image_gen | AI-generated; supplied style reference audit pending | Unmodified generated source | 2026-10-15 |
| textures/debris/beam.png | debris_beam | OpenAI built-in image_gen, user/Codex direction | AI-generated; supplied style reference audit pending | Nearest-neighbor 96 x 96 export, centered body at most 36 x 36, binary alpha | 2026-10-15 |
| source/debris/variants/beam.png | - | OpenAI built-in image_gen | AI-generated; supplied style reference audit pending | Unmodified generated source | 2026-10-15 |
| textures/debris/hull.png | debris_hull | OpenAI built-in image_gen, user/Codex direction | AI-generated; supplied style reference audit pending | Nearest-neighbor 96 x 96 export, centered body at most 36 x 36, binary alpha | 2026-10-15 |
| source/debris/variants/hull.png | - | OpenAI built-in image_gen | AI-generated; supplied style reference audit pending | Unmodified generated source | 2026-10-15 |


## Orbital scrap reskin (14 October 2026)

User-requested replacement of the two asteroid textures. Original files are preserved byte-for-byte in `textures/legacy/` and are no longer loaded. New artwork was generated with OpenAI's built-in image tool using the supplied legacy sprites as style/layout references; no third-party asset pack was added. AI-generated output is not claimed as CC0; legacy reference provenance remains pending audit. Prompts and export notes: `source/debris/generation.json`. Human art review pending.

| File | Resource key | Source / author | License | Edits | Date |
|---|---|---|---|---|---|
| `textures/debris.png` | `debris` | OpenAI image_gen, directed by user/Codex | AI-generated; legacy style reference audit pending | Nearest-neighbor export, binary transparency; 96 x 96 with centered 36 x 31 body | 2026-10-14 |
| `textures/debris_destruct.png` | - (art reference) | OpenAI image_gen, directed by user/Codex | AI-generated; legacy style reference audit pending | Uniformly scaled/repacked from 4 x 2 grid to 768 x 96 strip; eight 96 x 96 frames, final frame transparent | 2026-10-14 |
| `source/debris/scrap-generated.png` | - | OpenAI image_gen | AI-generated; legacy style reference audit pending | Unmodified generated intact source | 2026-10-14 |
| `source/debris/scrap-destruct-generated.png` | - | OpenAI image_gen | AI-generated; legacy style reference audit pending | Unmodified generated destruction source | 2026-10-14 |

## Barricade placeholder reuse (14 October 2026)

Existing repository textures reused at the user's request; no new external assets or image edits. Legacy provenance verification remains item 02.

| File | Resource key | Source / author | License | Edits | Date |
|---|---|---|---|---|---|
| `textures/legacy/asteroid.png` | - (archived) | Existing Space Ablaze repository; original author pending audit | Pending legacy audit | Original 96 x 96 file preserved unchanged | 2026-10-14 |
| `textures/legacy/asteroid_destruct.png` | - (archived) | Existing Space Ablaze repository; original author pending audit | Pending legacy audit | Original seven-frame 672 x 96 file preserved unchanged | 2026-10-14 |

## Player equipment pack (14 October 2026)

User-supplied Void Main Ship 1.0, commissioned from Baldur and distributed by Foozle. CC0, per the original `source/player/readme.txt`, retained verbatim. Files renamed/organized only; image pixels and editable sources preserved with SHA-256 verification. No AI art generated. Existing legacy asset audit remains item 02.

| File | Resource key | Source / author | License | Edits | Date |
|---|---|---|---|---|---|
| `source/player/hull_damaged.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/hull_full_health.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/hull_slight_damage.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/hull_very_damaged.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/hull_damaged.png` | `player_hull_damaged` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/hull_full_health.png` | `player_hull_full_health` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/hull_slight_damage.png` | `player_hull_slight_damage` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/hull_very_damaged.png` | `player_hull_very_damaged` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/engine_base_engine_idle.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/engine_base_engine_powering.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/engine_base_engine_spritesheet.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/engine_big_pulse_engine_idle.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/engine_big_pulse_engine_powering.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/engine_big_pulse_engine_spritesheet.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/engine_burst_engine_idle.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/engine_burst_engine_powering.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/engine_burst_engine_spritesheet.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/engine_supercharged_engine_idle.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/engine_supercharged_engine_powering.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/engine_supercharged_engine_spritesheet.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/engine_base_engine_idle.png` | `player_engine_base_engine_idle` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/engine_base_engine_powering.png` | `player_engine_base_engine_powering` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/engine_base_engine_spritesheet.png` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/engine_big_pulse_engine_idle.png` | `player_engine_big_pulse_engine_idle` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/engine_big_pulse_engine_powering.png` | `player_engine_big_pulse_engine_powering` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/engine_big_pulse_engine_spritesheet.png` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/engine_burst_engine_idle.png` | `player_engine_burst_engine_idle` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/engine_burst_engine_powering.png` | `player_engine_burst_engine_powering` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/engine_burst_engine_spritesheet.png` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/engine_supercharged_engine_idle.png` | `player_engine_supercharged_engine_idle` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/engine_supercharged_engine_powering.png` | `player_engine_supercharged_engine_powering` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/engine_supercharged_engine_spritesheet.png` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/engine_base_engine.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/engine_big_pulse_engine.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/engine_burst_engine.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/engine_supercharged_engine.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/engine_base_engine.png` | `player_engine_base_engine` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/engine_big_pulse_engine.png` | `player_engine_big_pulse_engine` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/engine_burst_engine.png` | `player_engine_burst_engine` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/engine_supercharged_engine.png` | `player_engine_supercharged_engine` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/main_ship_fighter_design.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/shield_front_and_side_shield.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/shield_front_shield.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/shield_invincibility_shield.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/shield_round_shield.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/shield_front_and_side_shield.png` | `player_shield_front_and_side_shield` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/shield_front_shield.png` | `player_shield_front_shield` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/shield_invincibility_shield.png` | `player_shield_invincibility_shield` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/shield_round_shield.png` | `player_shield_round_shield` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/weapon_auto_cannon.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/weapon_big_space_gun.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/weapon_rockets.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/weapon_zapper.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/weapon_auto_cannon.png` | `player_weapon_auto_cannon` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/weapon_big_space_gun.png` | `player_weapon_big_space_gun` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/weapon_rockets.png` | `player_weapon_rockets` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/weapon_zapper.png` | `player_weapon_zapper` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/projectile_auto_cannon_bullet.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/projectile_big_space_gun.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/projectile_rocket.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/projectile_zapper.aseprite` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/projectile_auto_cannon_bullet.png` | `player_projectile_auto_cannon_bullet` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/projectile_big_space_gun.png` | `player_projectile_big_space_gun` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/projectile_rocket.png` | `player_projectile_rocket` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `textures/player/projectile_zapper.png` | `player_projectile_zapper` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
| `source/player/readme.txt` | `-` | User supplied / Baldur, Foozle | CC0 | Renamed only | 2026-10-14 |
