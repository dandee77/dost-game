# Skills prototype: commands and behavior

Implemented on `dev` for the 17 October request. Source brief: [skills-context.md](skills-context.md). This is one scoped P5 feature item: 14 augments and 18 abilities, using existing textures and simple Raylib shapes. No generated assets, new dependencies, unlocks, ability drops, inventory, or shop connections.

## Terminal

From the repository, compile and launch with commands:

```powershell
.\build.bat --command "augment weapons-payload" --command "skill equip laser-rings" --command "skill equip blink-drive"
```

Or use an already compiled debug-enabled executable, **from its asset directory** (this workspace uses `build/game`; other configurations may use `build` or `build/Debug`):

```powershell
cd build/game
.\SpaceAblaze.exe --skills-list | Out-Host
.\SpaceAblaze.exe --command "invincible on" --command "skill equip combat-drone" --command "skill equip plasma-beam"
```

`--skills-list` prints all 32 command keys and exits without opening a window. In PowerShell, pipe through `Out-Host` as shown because Windows treats this as a GUI executable. Repeat `--command` to queue commands in order. Assets finish loading, a fresh game starts, and commands run once. Debug commands require `GAME_DEBUG=ON`; a debug-disabled build rejects `--command` with exit code 1. Skills themselves remain compiled into both builds.

## F5 console

Start a game, press F5, enter a command, then close F5 to resume simulation. Tab / Up / Down expose every full key. `skill list` and `augment list` also log the catalogs; the console displays its last six lines, so use autocomplete or the terminal listing for the whole list.

```text
augment weapons-payload
augment nano-repair
skill equip laser-rings
skill equip blink-drive
skill cast nuclear-missile
skill unequip laser-rings
skill status
spawn lowlevel enemy 100
spawn debris all
```

`augment <key>` applies one level. Persistent augments cap at 10 levels; Nano Repair is an immediate consumable heal with no stacking level and reports when hull is full. The existing timed card offer now uses the same typed 14-entry catalog. No new acquisition flow is added.

`skill equip <key>` enables an automatic ability or selects a manual ability for **Q**. Multiple automatic abilities may run together. The most recently equipped manual ability gets Q; every ability can also be activated once with `skill cast <key>` without equipping it. Manual targeted abilities use the mouse position, clamped to 90 world units. Blink travels at most 35 units toward it. Plasma follows ship facing. Q is separate from the existing Space equipment boost/guard.

`skill unequip <key>` cancels that ability's effects but retains cooldown debt. Cooldowns start at activation. Pending console casts execute only after simulation resumes. Pause, console capture, card selection, and game over do not advance skills. Death, scene exit, and restart clear skill state; augments reset on a new run.

## Ability behavior and provisional balance

Numbers live in `Balance.hpp` and are initial tuning, not final balance. Units below are seconds and world units; damage is per tick. Auto abilities repeat while equipped whenever their cooldown reaches zero.

| Key | Activation | Cooldown / duration | Behavior |
|---|---|---|---|
| laser-rings | Auto | 12 / 8 | Three orbiting blades, radius 18, contact radius 4, 12 damage every 0.2 s |
| deflector-shield | Q | 16 / 8 | Absorbs 3 hits; unused hits expire after 8 s; independent of equipment shields |
| lightning-ring | Auto | 14 / 8 | Radius 25 perimeter, width 5, 8 damage every 0.5 s and 0.6 s stun |
| blink-drive | Q | 4 / instant | Teleports toward cursor up to 35 units; 0.25 s protection; can jump over barricade segments |
| nuclear-missile | Q | 30 / 0.7 travel | Radius 55; destroys standard enemies regardless of HP; future boss-type targets take 250 damage |
| space-collapse | Q | 35 / instant | Radius 32 at cursor; erases enemies, **no scrap**, still awards score and kill count |
| radiant-halo | Q | 8 / instant | Radius 32 around ship, 60 damage |
| repulsor-pulse | Auto | 5 / instant | Pushes ordinary enemies within radius 30 outward by 22 units |
| point-defense-interceptor | Auto | 12 / 8 | Removes hostile bullets crossing radius 38, including fast swept crossings; leaves friendly fire alone |
| scrap-magnet | Auto | 15 / 5 | Collects all currently released scrap anywhere every 0.2 s; pending debris explosions still finish first |
| chain-lightning | Q | 7 / instant | Up to 6 distinct nearest targets, 35 damage each, 45-unit jump range, stable tie breaking |
| hologram-clone | Q | 18 / 10 | Stationary clone offset 18; lures enemies within 60 and repeats primary fire |
| combat-drone | Auto | 20 / 15 | Chases nearest enemy within 90 at speed 70; shoots 15-damage bolts every 0.4 s within 35 |
| plasma-beam | Q | 12 / 4 | Facing cone, range 65, half-angle 30 degrees, 12 damage every 0.15 s |
| corrosive-trail | Auto | 14 / 8 | Leaves radius-8 pools lasting 3 s; 6 damage every 0.3 s; refreshes 1 s of half speed and half contact/projectile damage |
| singularity | Q | 22 / 6 | Radius 42 at cursor; pulls at speed 28; 10 damage every 0.2 s; ordinary scrap rewards |
| realm-breaker | Q | 20 / 6 | Rift length 50, half-width 6 at cursor, perpendicular to ship facing; 20 damage every 0.2 s and continuous hostile projectile absorption |
| armageddon | Q | 35 / 6 | Seeded barrage across the visible battlefield; radius 22, 80 damage every 0.3 s |

Formation-controlled barricades take skill damage but ignore displacement, stun, and corrosion so their shared event clock stays correct. Singularity and Repulsor do not move future boss-type targets. Corrosion snapshots reduced damage onto newly fired enemy bullets. Acid pools overlap without multiplying damage.

Direct ability damage uses the existing Game damage/score/destruction path and emits minimal scrap pickups (low 2, mid 5) to make the no-drop distinction testable. Clone/drone projectiles retain the normal weapon reward path; the full enemy-drop economy is still deferred. Scrap Magnet uses the existing uncapped harvested-scrap counter; there is no new cargo or shop connection.

## Augment decisions

Weapons Payload adds 15 percentage points of standard attack damage per level. Critical Matrix adds 5 percentage points of double-damage chance. Both affect default/cannon shots, rockets, heavy shots, and equipment laser pulses. Reinforced Hull adds 20 maximum/current HP; Nano Repair restores 25% of the current maximum. Existing mobility, turning, iframes, scatter, pierce, and knockback modifiers are retained under the new names.

**Overclocked Chambers** multiplies attack cooldown by 0.9. **Rapid Fire** adds a shot per burst (or another pulse for continuous laser equipment). Broadside and Tail Gunner add firing directions; laser equipment uses visible auxiliary bolts for spread/side/rear patterns. Rockets retain their explosions while piercing additional targets. Active ability damage has its own tuning and is not scaled by Weapons Payload.

## Validation

`GAME_EQUIPMENT_TESTS=ON` includes `tests/SkillChecks.cpp` in the existing native harness. It exercises all 32 IDs, real damage/reward application, all weapon patterns, all ability behaviors, command routing, malformed input, caps, pauses, cooldown debt, restart, and 30/144 FPS damage parity. The harness exports `skills-preview.png` next to the built tests using the production draw functions. Build/test results are recorded in `progress-tracker.md`.

Human balance and feel review, polished effects, final naming, and acquisition/inventory/shop integration remain future work by request.
