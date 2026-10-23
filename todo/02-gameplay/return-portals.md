# Field Return Portals

**23 October 2026. Owner-selected replacement for manual Return Home; design only.** No source/assets changed. This supersedes the planned Q Return Home ability and follows the same shield/energy gates. All skills are automatic; F is a world interaction. Primary movement, aiming and firing retain their ordinary controls.

## Selected behavior

- Begin generating return portals at random legal combat-map positions once the energy meter reaches at least half its current maximum. The threshold rises with player level under the existing energy contract.
- Spawn **three portals on Easy, two on Hard, and one on Impossible**, independent of mode. This changes exit availability by difficulty while leaving the five mode objectives distinct.
- Exit positions may be far away. No guaranteed nearby exit or global pointer is selected.
- Show a directional pointer only within a detection range of roughly one visible gameplay screen. Exact camera-relative interpretation/world distance remains numerical work in game-design.md/Balance during implementation; do not hard-code display pixels into world queries.
- Fly inside a portal and press F to request return. Touching its ring alone does not teleport.
- At commit, require the player alive, shield present/online/positive, energy at least the current half-full threshold, and no pending mandatory card/input-capture/result state.
- Keep spawned portals present until used or the run ends. A broken shield leaves them visible but locked, labeled Shield Offline until recovery. If a level-up raises the half-capacity threshold above current charge, keep the same portals visible but locked and show the missing energy; unlock them when charge recovers. Do not reroll locations on threshold flicker.
- Energy consumption retains the prior draft: drain all current return energy on successful use, no wallet/XP cost. This drain amount has not been newly changed by the portal request.
- Successful return suspends the existing expedition and combat clocks in Game, opens the same hub/shop/repair loop, and preserves build, enemies, boss HP/phases, pickups and rewards for Resume.
- Resume places the ship at the used portal's saved position with **2 seconds of damage protection**, ending immediately when the player fires. This does not refill hull or shield. The protection is a temporary re-entry effect, not a manual skill or extra shield capacity. Its timer follows combat time and cannot be refreshed by opening panels.
- A successful return retires that entire portal set. Resume the same expedition with depleted return energy. Once charge next reaches half capacity, generate a fresh random set at the same difficulty count; merely recovering an existing locked set does not generate another one.
- Failed use preserves charge/wallet/world state and shows the actual blocker. A shield broken or player killed in the request frame prevents travel. Input is consumed so F cannot open another panel on arrival.

## Ownership and fairness contracts for later implementation

Use the existing Game run ownership, shield state, paired salvage/return energy and planned Entity/Dock approach. Do not create a scene switch, a second shield/currency manager or a manual backup teleport. Portal creation must not reroll encounters, loot or shop stock; proposed dedicated seeded portal randomness needs a bounded ownership/reset contract.

Locations must obey authored arena bounds/obstacles and cannot be inside solid barricades or overlap the player's ship on creation. Far travel is allowed, but that does not authorize an unreachable portal inside geometry. Portal entities/activation state survive same-expedition suspension; reset/quit clears them.

Campaign completed-wave checkpoint travel remains a distinct previously proposed transition, pending review; these field gates apply to return during a live encounter. Boss-specific layouts remain owner content, not invented here.

## Open decisions before T07

- Spawn placement envelopes, validation fallback and exact detection range; the concurrent count is selected by difficulty.
- Resume input handling must prevent one F press creating repeated transitions. Exact protection presentation and attack-input handling (including auto-fire) remain implementation-contract work.
- Numeric spawn/detection constants and any new input messages go through Balance/Theme; actual build/runtime checks remain pending.

The pending battery-size/application/overcharge choices are independent of portal access. Return still requires positive online shield; a purchased battery does not bypass the field-to-hub gate.
