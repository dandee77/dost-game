# Return Portals

**Reconciled 24 October 2026.** Selected design and delegated integration defaults; portal/hub runtime remains pending. Numerical authority is [game design](../../context/game-design.md). F is an interaction, not an active skill.

## Access rules

| Rule | Swarm, Chaos, Campaign ordinary return | Boss mode |
|---|---|---|
| Creation | First readiness at 500 energy out of fixed 1000 | Only after valid boss death |
| Count | Easy 3 / Hard 2 / Impossible 1 | One boss-clear portal on every difficulty |
| Use | Alive, F inside, positive online shield, energy at least 500 | Alive, F inside; bypass shield and energy |
| Cost | Drain all current return energy; no wallet/XP debit | No energy or wallet/XP debit |
| Mid-fight retreat | Allowed through an eligible portal | Forbidden, including at full shield/energy |
| Next launch | Resume suspended world at used portal position | Start next boss once; preserve build and wallet |

Neither type heals the ship or resets upgrades. Pause remains available; quitting abandons the run. Player death prevents portal travel. Under Q19/Q20, a same-step boss death still earns boss-clear credit before the run ends; it does not permit revival, station entry or the next encounter.

## Ordinary portal lifecycle

- Randomize legal combat-map locations. Far exits are allowed; a direction pointer appears within roughly one visible gameplay screen. Do not promise a nearby exit or global pointer.
- Keep the set until used or the run ends. Broken shield shows **Shield Offline**; insufficient charge shows the deficit to 500. Level-ups never change capacity or threshold. Recovery unlocks the same locations.
- At commit, resolve damage, pickup accounting and mandatory queued choices first. Require valid gameplay state and no captured/modal input. Failed requests change no resources or world state.
- Successful use retires the entire set and saves the used location. Suspend encounter state, RNG and combat clocks within Game; do not switch scenes or regenerate enemies, loot or shop stock.
- **Return to Battle** means resume that expedition, not unpause. Place the player at the saved location with two combat seconds of damage protection. It restores no hull/shield. Opening panels cannot refresh protection.
- Delegated default: primary auto-fire and offensive automatic skills wait through protection. Deliberate Shoot fires immediately and ends protection. Consume F once so arrival cannot trigger another interaction.
- After resuming, reaching 500 charge creates a fresh set. Locked/unlocked flicker never rerolls an existing set.

## Campaign wave-clear travel

A cleared Campaign wave offers optional Enter Station or direct Next Wave/Stage Boss after rewards/cards finalize once. Only selected station entry travels to base, with no shield/energy gate or payment/healing. Either direct launch or later station departure starts the pending encounter once. Checkpoint time freezes combat; no auto travel/countdown. Ordinary mid-wave retreat still uses gates and resumes the unfinished wave. See [campaign stages](campaign-stages.md).

## Boss-clear lifecycle

Suppress ordinary portal creation and interaction throughout Boss mode. On a valid boss kill, create exactly one base portal. It works at zero shield and zero energy. Resolve owned encounter hazards/adds using the boss cleanup contract, without additional cleanup drops; preserve or credit earned loot exactly once before retiring the arena.

The base visit preserves the run. No boss spawns while shopping. A confirmed launch advances the encounter once and creates the next boss. Repeated input cannot duplicate rewards, portals or encounters. Campaign source clears retain their separate required-survivor rules; Boss-mode cleanup does not override them.

## Adopted placement, detection and protection appendix — 25 October

These complete written PREP-29; actual T07/T10 integration and map tests remain open. Numerical authority adopts this appendix through game-design.md. Existing geometry stays radius12 interaction,70–140 from player, minimum center separation36,32 random candidates per missing member, then eight headings at radii70/105/140, retry1 combat second. Difficulties require3/2/1 ordinary exits, not merely that many attempts. Boss mode suppresses this entire ordinary generator regardless of energy.

Game owns one isolated mt19937 portal stream, seeded from low/high run-seed words plus domain0x504F5254 (PORT), using the same unbiased bounded-draw method as the card contract. Each candidate draws angle integer0..999999 then radial integer0..999999. Let u=radial/1000000; angle=2*pi*angleDraw/1000000; radius=sqrt(70^2+u*(140^2-70^2)), uniform by annular area. Generate from the player's position when filling the missing slot. Preview, lock changes and drawing consume no RNG; failed random candidates consume their own draws only. Fallback consumes none: radius-major70/105/140, headings0/45/90/135/180/225/270/315 degrees. Use full precision internally and stable slot order0..count-1. IDs include run/set/slot serials; no duplicate Animator key across retired/recreated sets.

Legal candidate: full interaction disk within finite bounds; no disk overlap with static solids or active barricade bodies (2-unit clearance); center>=36 from current player and every accepted exit. Dynamic enemies/projectiles do not count as permanent placement blockers; moving hazards cannot make placement loop forever. Validate a ship-clear path from player to the interaction disk through the current traversable component, including barricade membership. In an open finite circle/empty roaming area, direct swept-circle visibility is sufficient. Otherwise use a deterministic4-world-unit navigation grid centered on player,112x112 cells, eight-neighbor flood search, no corner cutting; edge sweeps use actual ship radius+0.5 clearance, and start/goal connectors must also be clear. Max12544 visited cells/search; lack of a witness rejects the candidate, not permission to accept it. This is conservative and may retry a physically valid location; it never promises to solve arbitrary mazes. Beta finite arenas deliberately have no solid maze.

Retain valid partial members while searching missing ones, at most one bounded full missing-slot pass per retry. Reuse one legal navigation flood/component map for that pass instead of rebuilding it for every candidate; invalidate it when solids/barricade geometry change. A living player may use any real valid member even before the full set exists. Pending slots show Exit placement pending; never draw fake pointers or reduce the required set size. Retry on the combat clock from the current player location. No energy cost until successful interaction. Failed placement, broken shield and sub500 charge preserve the same set serial, members and readiness record. The set retires only on successful use, encounter clear/retirement or run reset; encounter replacement is not a mid-wave reroll.

Existing barricade creation must preserve all current portal members in the player's traversable component. If its selected enclosing geometry would separate them, postpone the event and recheck after1 combat second until the set retires or the existing geometry can satisfy membership; do not move exits, delete them, close a wall through a portal or grant a teleport. Destroyed segments update navigation legality. A blocked portal remains rendered with Obstructed reason and cannot commit while its interaction disk overlaps a live solid. No permanent barrier may be added after Resume that intersects its saved arrival disk.

Pointer detection: squared center distance<=`(3840/actualCameraZoom)^2`; at zoom20 exactly192 world units, at zoom13 approximately295.384615. Reject nonfinite/nonpositive camera zoom for projection with an explicit renderer diagnostic; do not silently use window pixels. Detection does not imply interaction. On-screen exit gets ring/text; off-screen detected exit gets a marker intersecting the important-HUD safe rectangle x220..3620,y150..2000. Same-angle markers stack in stable slot order with48 canvas-pixel spacing inward and show ordinal/distance; at most three ordinary markers. Beyond detection range no ordinary exit marker. Ship and portal positions use the logical, unshaken camera for decisions. Boss-clear exit has a distinct Exit to HOPE marker with global direction within its finite arena, so a surviving player can always find it.

## Exact commit, Resume and reset order

| Stage | Required operation |
|---|---|
| Before return request | Run the authorized combat step, settle damage/death, rewards/progression and objective events. Death or terminal completion wins over a travel request |
| Mandatory choice | If that step earns cards, keep the request uncommitted; resolve the cards and require a fresh F afterward. No auto-travel on last card pick |
| Validate | Living/running state, no captured input, fresh F, correct portal type and inside radius12; ordinary additionally online positive shield and energy>=500; recheck solid overlap |
| Commit | Drain ALL ordinary current energy, retire its entire set, capture used location/encounter identity and suspend field once; Boss-clear/checkpoint entry has no energy debit. No wallet/XP debit or heal |
| Hub | Keep field entities, projectiles, loot, cooldowns, RNG and clocks frozen. Fly hub ship separately; services operate on the same build |
| Resume confirmation | Consume the confirmation input; restore field position and camera target, retaining encounter state. Guard remaining=2 combat seconds, assigned once per successful return, never on opening/closing panels |
| Protected field update | World/enemy timers/motion run normally; ship can move and collect ordinary earned pickups. Reject incoming damage before Blink/shield/Detonation. Suppress all outgoing primary/automatic/companion/persistent-zone damage and offensive signature/contact charge until guard ends |
| Deliberate Shoot | A fresh post-UI LMB press cancels guard before firing through the normal cooldown. Preserve toggle/debt; E may toggle but never cancels guard or fires through it by itself |
| Natural expiry | At guard expiry allow normal outgoing behavior from then onward; no catch-up damage, banked missed shots, extra cast or refreshed cooldown. Incoming future hits follow ordinary ordering |

Previously held LMB/F/Enter must be released after UI dismissal before it can become a fresh deliberate action. Resume's click cannot be that shot. Defensive interception/droid movement may continue during protection, but cannot damage enemies; destroyed droid rebuilds still advance only on real combat time. Existing committed hostile attacks are not reset: player protection supplies the safe entry. Pause/focus/card time freezes remaining protection; leaving and reentering pause does not renew it. A direct next-wave/Boss launch uses fresh encounter arrival rules, without ordinary return protection. In-flight player projectiles keep their trajectories/lifetimes; protected intervals suppress their collision damage and do not store missed contacts for a later hit.

When an arena retires on a genuine clear, clear its ordinary set/pending placements/used-location token. Never reuse an old portal to skip the next fight. Fresh run resets stream seed, serials, retry debt, protection, saved field location and return tokens through Game::resetRun. Same-expedition station visits reset none of the suspended encounter state. Exit/restart during a pending transaction follows the confirmation/input contract without partially draining charge.

## Implementation validation

The written defaults above are adopted, not unanswered owner questions. These remain actual engineering acceptance:

- Implement the adopted bounds/detection/search in Balance/Config and measure actual layouts; compare world coordinates consistently.
- Validate all candidates/fallbacks, partial sets, barricade postponement and saved-position clearance; no paper search proves runtime reachability.
- Implement isolated portal RNG/IDs/reset and confirm generation changes no encounter/loot/shop draws.
- Present locks, prompts and protection within the established safe area using Theme.hpp. Multiple pointers must remain distinguishable without hiding danger.
- Test full-energy Boss retreat rejection, zero-shield boss-clear entry, repeated F, same-frame death, queued cards, pause during protection, manual versus automatic fire, fresh-set creation, and reset from every transition state.

Battery rules are settled separately: `newShield = min(currentShield, normalCapacity) + purchasedCharge`. Replacing a battery removes old excess first; regeneration stops at normal capacity. Batteries never bypass ordinary portal gates.
