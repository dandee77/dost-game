# Beta loadout and single-shield integration - 25 October 2026

Authored under the owner's existing fresh-run, starter-shield, station-only cannon and technical-design delegation. This completes the written equipment-inclusion decision for PREP-03; it does not implement Player/SkillSystem integration. Numerical authority is [game design](../../context/game-design.md#25-october-beta-loadout-and-shield-inclusion).

## Fresh run

| Component | Normal beta starting state | Same-run station/Resume |
|---|---|---|
| Hull | 100/100 HP, using existing PLAYER_MAX_HEALTH | Preserve actual HP; only explicit paid repair/free field-card grant changes it |
| Primary | T1 Starter Cannon, one active primary profile/fire loop | Preserve node/branch and remaining fire debt; station purchases only immediate children |
| Engine | Existing base engine/motion, modified only by earned movement attributes | Preserve derived movement and actual state; no engine acquisition/tree or manual boost |
| Shield | Deflector owned at rank 1, 20/20 points, online, zero overcharge/reboot/break debt | Preserve actual points/offline/reboot state; no station refill or second shield |
| Other abilities | Unowned; no drone army, Blink, active zone or pending cast | Preserve genuine learned ranks/casts/slots/debt under suspension rules |
| Field progression | Level 1, zero progress/pending choices/return charge, zero wallet/collected total | Preserve all values; service spending changes wallet only |
| Controls | Primary auto-fire OFF; hold Shoot/LMB or toggle E; mouse primary aim | Preserve toggle, suppress firing in inactive states; F remains world interaction |
| Temporary guards | No debug invulnerability, manual shield guard or leftover Blink/return protection | Preserve only a legitimate still-active guard under its actual lifecycle |

Validated Cadet identity, selected mode/difficulty and presentation settings follow their separate session/launch contracts. A restart may retain identity/mode selection while resetting all gameplay. Preview/cancel, entering the hub or changing a graphics preset is never a fresh-run initialization. Initial field entry uses only the separately specified safe spawn/protection rules; loadout initialization grants no hidden extra ability.

## Prototype equipment inclusion/defer decisions

| Existing source feature | Normal beta decision | Debug/source treatment |
|---|---|---|
| PlayerWeapon prototype cannon/default paths | One T1 profile, later the accepted 26-node tree | Preserve old code for migration/debug; never run legacy and equipment firing loops simultaneously |
| Prototype laser/rocket/heavy builds | No separate free build-picker or second equipment progression | Their useful drawing/projectile code may support accepted tree profiles; prototype names/stats do not bypass tiers/prices |
| ENGINE_BASE | Included as normal starting engine | Existing art/motion baseline |
| ENGINE_PULSE/BURST/SUPERCHARGED | Deferred as gameplay equipment/chassis upgrades | Existing assets/debug commands can remain; no station rows/unreachable purchase promise |
| SHIELD_FRONT/SIDES/ROUND point shields | Excluded as additional normal shields | Their angular coverage/capacities cannot stack with Deflector |
| SHIELD_INVINCIBILITY / Space guard | Excluded as a normal manual shield skill | No normal Space guard/recharge purchase; Blink/ordinary hit protection retain their own selected rules |
| Player deflector-hit counter and timed Deflector cast | Replaced in normal play by the single persistent point shield | No additional three-hit layer or periodic free refill from legacy begin() |
| Nano Repair target entry | Replaced by selected Shield Detonation | No separate Nano Repair field ability or extra passive hull regeneration |
| Existing ship/engine/weapon/shield sprites | Reuse compatible layers as presentation | Preserve accepted frame sizes/counts; visuals do not create a second damage absorber |

No assets/code are deleted by this document. A mutating debug equipment/invulnerability command marks that run unranked under the result contract even if its effects are later reversed; normal read-only inspection does not invent a new build. This eligibility flag still needs actual implementation. Production menus never expose debug loadouts as legitimate equipment choices.

## One authoritative shield

Player owns the one live shield's current/capacity/overcharge/online/reboot state; SkillSystem owns the Deflector earned rank and other ability state. Game owns ordered damage/death/result orchestration. Adapt existing Player fields or their replacement inside that existing owner; no second ShieldManager or copied UI shield. Deflector is persistent, not a duration-based cast that refills a hit counter. HUD, paid batteries, capacity purchases, return gates and Shield Detonation all read this same shield.

1. Reject already-negated incoming events using existing valid guards; no shield debit or break event.
2. For eligible direct hits, permit ready learned Blink to validate its real rescue. Successful rescue consumes that event before shield/hull debit; failure spends nothing.
3. If the real shield is online with positive points, absorb the whole hit. Subtract points to zero as needed; the breaking hit has no hull overflow. Emit one genuine online-positive -> broken transition.
4. A hit not absorbed by that shield/another valid selected guard follows ordinary hull damage and post-hit protection. Shield art/old equipment counters cannot intercept it a second time.
5. Game routes the genuine shield-break fact to learned/ready Shield Detonation exactly once. A reset, capacity purchase, rank update, battery replacement or already-zero frame cannot synthesize that transition.

Use the existing documented damage-event ordering for same-step boss/player death; presentation or shield integration cannot revive the ship or discard a credited simultaneous boss clear. Special non-direct damage follows its authored damage policy, not a newly invented Blink escape path.

Deflector field ranks/paid capacity share `20 + 5*(rank-1) + 1.25*paidCapacityCount` maximum points, with their already-authored distinct effects. Preserve current points and break/reboot debt on ordinary rank/capacity changes. Battery purchases use the selected additive replacement formula and may add overcharge; normal regeneration stops at normal capacity. Start capacity C0 is 20 for price scaling. Hull repair is not shield repair. Same-run transitions cannot reset any of these values.

## Initialization and reset boundary

Only the genuine new-run path clears run managers/progression/weapon selection/skills, initializes Player, grants rank-1 Deflector and sets its initial points once. Use Game::resetRun and current manager resets; do not grant the starter in draw(), panel open, field entry, station entry or every SkillSystem::update. Reset legacy equipment shield charges, deflector-hit counters, invincibility debt, pending damage/break facts and old effects so none survive alongside the new state. A debug transition cannot accidentally authorize leaderboard eligibility.

Same-run wave/level changes and station launch preserve the loadout, except the explicit accepted transaction or encounter cleanup. A failed/canceled purchase changes nothing. Exact weapon/card/stat combination and whole damage-pipeline performance remain their separate implementation prerequisites; PREP-03 delivery is the inclusion/ownership decision above.

## Later runtime acceptance

- New run in every mode/difficulty: one T1 firing loop, base engine, 100/100 hull, one 20/20 shield, no other acquired abilities, auto-fire off and zero wallet/progression.
- Shield 1 point versus a large direct hit: points reach zero, hull unchanged, one break event. Next eligible unabsorbed hit follows hull rules, not an old equipment layer.
- Station/Resume/rank/capacity purchase: no free refill or reboot; one correctly priced battery/repair transaction changes only its intended values.
- Debug front/round/Space shields cannot enter ordinary play or make a second absorber; mutating equipment cheats make results unranked.
- Restart after damaged/overcharged/offline shield, manual prototype guard, droids, Blink and queued effects: no leaked state. Real normal gameplay still needs code/tests; this document is not that validation.
