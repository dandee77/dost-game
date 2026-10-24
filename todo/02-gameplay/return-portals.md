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

## Implementation details to finish

These are delegated engineering/tuning work, not unanswered owner policy questions:

- Define viewport-relative detection and placement distances in game-design.md, then Balance.hpp. Convert camera dimensions to world units; never compare world positions with display pixels.
- Validate bounds, obstacles, player clearance and navigable access. Use bounded candidate attempts and a deterministic legal fallback/retry; never accept an unreachable point or loop indefinitely. Validate actual arenas before adopting numeric envelopes.
- Give portal RNG and unique entity/Animator IDs explicit Game-owned reset lifetimes. Generation must not perturb encounter, loot or shop randomness.
- Present locks, prompts and protection within the established safe area using Theme.hpp. Multiple pointers must remain distinguishable without hiding danger.
- Test full-energy Boss retreat rejection, zero-shield boss-clear entry, repeated F, same-frame death, queued cards, pause during protection, manual versus automatic fire, fresh-set creation, and reset from every transition state.

Battery rules are settled separately: `newShield = min(currentShield, normalCapacity) + purchasedCharge`. Replacing a battery removes old excess first; regeneration stops at normal capacity. Batteries never bypass ordinary portal gates.
