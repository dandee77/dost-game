# Asset provenance

## Orbital scrap reskin (14 October 2026)

User-requested replacement of the two asteroid textures. Original files are preserved byte-for-byte in `textures/legacy/` and are no longer loaded. New artwork was generated with OpenAI's built-in image tool using the supplied legacy sprites as style/layout references; no third-party asset pack was added. AI-generated output is not claimed as CC0; legacy reference provenance remains pending audit. Prompts and export notes: `source/debris/generation.json`. Human art review pending.

| File | Resource key | Source / author | License | Edits | Date |
|---|---|---|---|---|---|
| `textures/asteroid.png` | `asteroid` | OpenAI image_gen, directed by user/Codex | AI-generated; legacy style reference audit pending | Nearest-neighbor export, binary transparency; 96 x 96 with centered 36 x 31 body | 2026-10-14 |
| `textures/asteroid_destruct.png` | `asteroid_destruct` | OpenAI image_gen, directed by user/Codex | AI-generated; legacy style reference audit pending | Uniformly scaled/repacked from 4 x 2 grid to 768 x 96 strip; eight 96 x 96 frames, final frame transparent | 2026-10-14 |
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
