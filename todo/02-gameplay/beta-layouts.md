# Beta hub, arenas and map layout

**24 October 2026. Delegated layout draft for SCRAPBOUND: Last Hope.** Owner requested drafting from the existing inhabited HOPE space setting. These are authoring defaults, not rendered assets or playtest results. Geometry authority: [game design](../../context/game-design.md#24-october-delegated-beta-layout-geometry). Presentation authority: [UI rules](../../context/ui-rules.md).

## Ship-based HOPE hub

Use the current ship controls and camera. The mothership, patched habitation modules, warm windows, maintained trusses, decorative service craft and Earth establish human habitation. Decorative traffic has no collision/reward/combat ownership. No walking character, dialogue system or multiplayer lobby.

```text
                         NORTH (-Y)
            SWARM     CHAOS     BOSS     CAMPAIGN
            (-90,-80) (-30,-100) (30,-100) (90,-80)

        WORKSHOP          MOTHERSHIP          REPAIR
         (-60,0)             (0,0)             (60,0)

                         ARRIVAL (0,40)
```

Mothership/modules are non-solid scenery for beta; do not imply an invisible maze. The camera follows the ship using existing smoothing/zoom. The whole hub need not fit in one screen; safe-area navigation labels identify services/gates while flying. Shape/text distinguish destinations in addition to color.

Service/gate rings are interaction triggers, not solid barriers. F inside opens their panel; crossing alone never launches or spends. Select nearest center then stable zone ID if future geometry overlaps. Consume the opening input and require a new press after closing. Stop ship movement while a panel owns input.

Workshop views: Weapon, Attributes, Owned Skills, Special Offers and Batteries, all using one wallet. Repair berth: Full Repair and Repair What I Can Afford, exact previews and timed job. No combined shield/full-service option. Base departure remains separate from shopping and reads authoritative encounter state.

Each gate previews objective, difficulty, ending and Launch. Campaign opens the level map first. Suspended fights offer Return to Battle; cleared Campaign waves first offer Enter Station or direct Next Wave/Stage Boss, so visiting this hub is optional. After level clear, next-level map may open from the safe checkpoint or station; Cancel restores that origin. Choosing another mode requires abandon/fresh-run confirmation. Preview/Cancel cannot clear a suspended fight or regenerate stock.

Store hub and field positions separately. Field return enters the arrival berth without healing; Return to Battle restores the used portal position. A cleared encounter instead begins its next authored arena only on confirmed departure. Base transit never calls resetRun.

## Hub and combat bounds

Use the numerical circular hub boundary: warn in its outer band, project movement inside the legal ship-center radius and remove only outward velocity. Boundaries deal no damage or skill charge. Keep labels inside CRT-safe canvas coordinates.

Swarm/Chaos retain roaming player-centered spawning and share ordinary rules. Boss/Campaign use an open circular arena with a visible, non-damaging edge. Each fresh finite encounter begins at its center with a clear arrival region. No new obstacle labyrinth or collision-shape redesign is required; stage backdrops supply identity.

Boss arrival keeps its existing two-second safety/tell. Spawn bosses legally, outside player/portal overlap. The director owns Boss/Campaign spawning; the ordinary endless spawner cannot also run independently. Every encounter record must specify BarricadeEvent eligibility before scheduling it; its automatic timer cannot advance at base or after clear.

Boundaries constrain actual movement and Blink, including the current barricade region. Fast movement cannot tunnel through an edge; teleport paths cannot collect loot or apply swept contact. Preserve damage handling separately from position correction.

## Ordinary return-portal placement

Use an isolated seeded portal stream and the current legal arena. Random candidates use the configured angle/distance envelope. Validate the entire interaction ring against finite bounds, solids, player/portal separation and current barricade membership. Distant exits are allowed, but unreachable exits are not.

After bounded random attempts, try configured radii/headings in stable order. If no legal point exists, retain readiness/energy, display **Exit placement pending**, and retry after the configured combat interval. Never loop indefinitely, silently reduce the exit-count policy or grant free teleportation. Preserve any valid members while filling missing members; only actual exits get pointers.

An unused set does not reroll with shield/energy changes. Successful use retires it and saves the used position. Boss mode has no ordinary set; its post-kill exit bypasses shield/energy. Cleared Campaign waves use an optional station/continue checkpoint; only chosen station travel bypasses ordinary eligibility.

Detect ordinary exits within one current world viewport width. Visible exits show F/lock rings; off-screen exits inside detection range get safe-area markers. Beyond that range there is no global ordinary-exit arrow. Hub navigation and nearby-boss markers have separate policies.

## Campaign map panel

Use the four-node [beta graph](campaign-stages.md): C01 left, C02 above center, C03 below center, C04 right. Lines connect whole levels, not waves. Details show wave count, separate boss, progress and Launch/Continue/disabled reason. Launching one middle level never locks the other.

Distinguish locked/available/current/cleared using labels/shapes; no exclusive-route-lock state or three-star ratings. C04 accepts either middle predecessor. Other unlocked, unfinished levels remain selectable after the current level clears. Cancel preserves RNG/currency/encounter state; map visits cannot skip an unfinished level.

## Required validation

- Inspect separation/navigation at actual camera zoom; arrival never automatically opens a panel.
- Exercise F/held F, clicks, Escape, pause and console capture from every panel.
- Check fast ship movement, arena edges, legal Blink and barricade membership.
- Check portal placement at arena edges, failure/retry, partial sets, unique IDs and saved-position resume.
- Verify field entities/skills/clocks/RNG freeze while hub ship flight remains usable.
- Exercise both routes, unchosen previews, OR merge, unfinished-stage continuation and final-result transition.
- Inspect at 1280x720 with the complete CRT pass; document geometry does not prove readability.

Asset creation, wave budgets, runtime integration, human readability and release performance remain separate work. PREP-07 stays open until the complete arena/spawn data is specified and reviewed.
