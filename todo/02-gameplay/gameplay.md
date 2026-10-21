# TODO: Colony Hub, Game Modes, Scrap Progression and Return Home

Design handoff updated **20 October 2026**. This replaces the former pause/scrap/difficulty context file. It describes the intended game and remaining work, **not an instruction to start implementing features in this documentation session**. The owner authorized publishing the documentation; their teammate will supply later implementation instructions. Start with [README.md](../README.md) for the full remaining-work index.

No feature below is implemented merely because it is described here. Read [progress-tracker.md](../../context/progress-tracker.md) for implementation status. This session changes documentation only, under `context/` and the owner-requested top-level `todo/`.

## 21 October narrative and material addendum

This handoff now lives in a topic folder. [World and campaign](../01-story/world-and-campaign.md) defines **H.O.P.E. Colony — Habitat for Orbital Preservation and Endurance**, the cadet pilot, failed atmospheric remediation, reused orbital refuges and source-containment campaign. [Science notes](../01-story/science-notes.md) separates primary-source environmental facts from the fictional mutation of engineered waste-eating organisms after atmospheric-treatment exposure. The old special-tree restoration plot and autonomous-machine origin are retired. Hostile creatures are living waste-eaters inside scrap shells; concentrated sources are infested nests and treatment-residue sites. The [narrative theme](../01-story/narrative-theme.md) connects neglect to consequences and recovery to responsibility. These are context changes, not new biological simulation mechanics.

The proposed campaign retains ten waves and boss slots five/ten. Each guardian disables its source emitter on death; existing required adds must still be cleared before the sector completes. Source shutdown does not reroll loot, lower existing HP or require a special drop. The final sector opens a cleanup corridor, not an instantly restored Earth. No-loot effects still resolve objectives; same-step player death takes priority over victory as below. Final boss identities/attacks remain owner content.

[Scrap types](../03-economy/scrap-types.md) proposes six material families over the existing paired trade/salvage economy. Types carry no reward multipliers or crafting gates. A profile assigns the dominant material; a mixed merged pickup displays Mixed Salvage while preserving both totals. Ordinary debris yields, accepted art, random enemy currency ranges, fixed salvage, repair costs and skill prices stay unchanged.

[Decisions and gaps](../00-planning/decisions-and-gaps.md) records remaining specifications beyond art: boss content, spawn tables, equipment access, card distribution, auto-targeting/mobility, geometry, scoring/results, tutorial/audio and performance limits. Their proposed defaults are preparation choices, not delivered features.

## 1. How to use this handoff

Read this file with:

- [project-overview.md](../../context/project-overview.md): product scope, story, competition and screen map.
- [story-context.md](../01-story/story-context.md): revised story cards, animation, ending and trailer treatment.
- [architecture.md](../../context/architecture.md): current ownership, scene lifecycle, simulation and proposed integration boundaries.
- [game-design.md](../../context/game-design.md): authoritative proposed tuning ledger for this revision, plus existing combat numbers.
- [class-registry.md](../../context/class-registry.md): existing classes and planned classes; do not duplicate systems.
- [ui-rules.md](../../context/ui-rules.md): canvas, safe area, art constraints and proposed screen requirements.
- [skills-context.md](../../context/skills-context.md) and [skills-commands.md](../../context/skills-commands.md): skill identities, existing behavior and rank formulas.
- [code-standards.md](../../context/code-standards.md), [library-docs.md](../../context/library-docs.md), [collision-performance.md](../../context/collision-performance.md), and [crowd-performance.md](../../context/crowd-performance.md): implementation and verification constraints.
- [build-plan.md](../../context/build-plan.md): dependency checkpoints for later implementation.

The dated 20 October sections in those files align the old plan with this request. Older sections remain useful for unchanged mechanics and historical implementation evidence. They must not silently restore cargo caps, credits conversion, timed cards, main-menu mode selection, or a separate scene that resets the run when docking.

### 1.1 Decision labels

| Label | Meaning |
|---|---|
| **Confirmed** | Explicitly requested or selected by the owner |
| **Retained target** | Unfinished requirement from the previous specification, still compatible with this request |
| **Proposed default** | A concrete recommendation to remove ambiguity; not a claim of owner approval or tested balance |
| **Delegated design** | Owner asked the author to choose the details; selected for this handoff, still subject to playtesting |
| **Pending content** | Owner/team must still supply final content, especially bosses |
| **Implemented baseline** | Present in the inspected source or recorded with verification in the tracker |

Proposed defaults make this handoff reviewable. The teammate's later implementation brief should adopt or replace them explicitly. The owner has not authorized this documentation session to implement them.

### 1.2 What was removed from the active TODO

The completed P6 checkpoint-1 implementation tasks are removed: pause-aware cooldown/run clocks, running-world animation gating, Esc/P transitions and consuming the pause/resume frame. Existing equipment, debris harvesting, skill effects, repeat-pick ranks, debug console and crowd/collision optimization are reused rather than assigned again as new features.

Their preservation checks remain necessary when new systems are connected. Their historical evidence stays in the progress tracker. The old budget limiter, checkpoint push instructions and generic instructions to an AI are not part of this design handoff.

### 1.3 Audited starting point

Reference: local `13c0090`, branch `feat/pause-scrap-progression`; `git pull --ff-only origin dev` returned “Already up to date” on 20 October.

| Existing component | What is actually there | Remaining connection |
|---|---|---|
| MainMenu | Play goes directly to Game; Settings points at an unavailable scene | Start -> difficulty -> hub; working shared settings panel |
| Game state | Running, augment selection, paused, game over | Hub, docking/shop, expedition and result transitions |
| Pause timing | Simulation clocks and Esc/P freeze/resume foundation | Visible menu, settings, hub-aware resume state |
| Cards | Typed augment/ability cards; repeats upgrade; timed 20-second trigger | Scrap trigger, queued choices, accurate NEW/UPGRADE content |
| Skill catalog | 14 augments and 18 abilities; Q/manual and automatic behavior | Automatic/persistent conversion; replace Nano Repair; Return Home utility |
| Scrap | Debris destruction-to-orb pipeline, harvested counter, minimal ability kill drops | Every reward path, wallet/progress/return accounting, enemy pickup behavior |
| Magnet | Global `collectAll` behavior | Radius attraction for ordinary enemy pickups |
| Shields | Equipment shield prototypes plus skill hit charges | One authoritative normal-play persistent shield contract and return eligibility |
| Modes/dock | Old future design, not a playable hub/mode loop | Actual hub, mode rules, expedition continuity, shop |

This is a focused source/doc audit, not a fresh runtime certification. No game build or gameplay test is claimed by this documentation update.

## 2. Confirmed direction and decision register

| ID | Topic | Decision and status |
|---|---|---|
| C01 | Entry flow | **Confirmed:** open game -> Start Game -> choose difficulty -> enter game at the mothership -> prepare -> choose a mode through a portal |
| C02 | Hub representation | **Confirmed by follow-up:** stay inside the ship and fly around a safe orbital colony hub. No walking pilot/cockpit exit system |
| C03 | Human colony | **Confirmed:** visible settlement, not merely a generic starfield; mothership, occupied colony background, stations and portals |
| C04 | Modes | **Confirmed direction:** Swarm/endless, timed Survival, Boss, Chaos with bosses plus swarms, Campaign ending in a boss |
| C05 | Boss content | **Pending content:** owner will develop bosses. Existing Hoarder/Core designs are reference proposals, not newly approved final content |
| C06 | Level-up location | **Confirmed by follow-up:** normal upgrades happen in the field immediately through scrap progression; returning is not required |
| C07 | Return Home | **Confirmed:** scrap-powered manual ability, usable from 50% charge, capacity grows with player level, blocked while shield is broken |
| C08 | Manual combat skills | **Proposed interpretation:** Return Home is the one manual ability; previous automatic/persistent combat-skill target remains |
| C09 | Scrap numbers | Owner's 100 level requirement and 1,000 return maximum are **example values**; use as proposed initial tuning, not tested final balance |
| C10 | Accounting | **Confirmed:** tradeable scrap is random by enemy, starting at 1-3. **Delegated design:** separate random trade value from fixed salvage progress; one collected pickup carries both |
| C11 | Hub shop | **Delegated design:** targeted next-rank purchases plus rare offers from existing combat skills; inventory and prices selected in section 9 |
| C12 | Hub services | **Confirmed:** base health repair costs scrap. **Delegated design:** paid hull repair, shield recharge and combined service; no free healing fallback |
| C13 | Starter shield | **Proposed default:** start normal runs with level-1 Deflector Shield so Return Home never depends on a lucky first card |
| C14 | Return charge cost | **Proposed default:** successful return drains current charge completely; failure consumes nothing; there is no bonus for waiting until 100% |
| C15 | Expedition continuity | **Proposed default:** return suspends the active expedition in memory; the same portal resumes it without rerolling enemies or rewards |
| C16 | Switching modes | **Proposed default:** one mode per run; switching ends the current run and resets all run progression before another mode launches |
| C17 | Persistence | **Proposed default:** no saved build, wallet, charge, or suspended mission across death, restart, quit, or application exit |
| C18 | Rank purchase versus player level | **Proposed default:** shop raises a selected skill rank only; it does not raise player level, award XP or enlarge the return cap |
| C19 | Rare meaning | **Proposed default:** uncommon acquisition opportunities, not a second stronger version of an existing skill |
| C20 | Healing exception | **Delegated design:** free field Reinforced Hull retains +max/+current HP; paid ranks increase maximum only so the shop cannot bypass repair costs. Remove Nano Repair; no passive combat hull healing |

## 3. Complete player journey

### 3.1 First entry

1. Open the application; loading finishes normally.
2. Reach the main menu. An eventual skippable intro can remain before it, but mode selection is not placed before Start.
3. Select **Start Game**.
4. Select **Easy**, **Hard**, or **Impossible**, then Confirm. First use has no selection and Confirm is disabled. Later visits may highlight the remembered session preference but still require confirmation.
5. Back returns to the main menu without creating a run or advancing RNG.
6. Confirmation creates a fresh run and places the ship at the mothership arrival berth in the orbital hub.
7. Show brief movement, docking and portal guidance. No countdown forces launch; “ready” means the single player has finished preparing.
8. Fly to a portal, inspect its mode summary and confirm Launch. Entering a portal's radius alone never starts a mission.
9. Begin that mode's first encounter. Combat time and spawning start now, not during difficulty selection or hub preparation.

The hub is a local single-player staging area. “Lobby” does not imply matchmaking, other players, network synchronization or ready checks.

### 3.2 In the field

Fight -> collect released scrap -> receive XP, currency and return charge -> complete a level threshold -> choose a card in the field -> resume the same encounter.

At any eligible moment, request Return Home. At the end of that simulation frame, resolve damage/death and pending level choices before a return can commit. A successful return suspends the encounter, moves the player to the hub and opens access to repair/shop services.

### 3.3 At home after return

Arrive -> optionally dock for repair -> optionally buy a targeted skill rank or a rare skill -> undock -> resume the same mode through its active portal.

Do not reset player level, earned skills, wallet, enemy health, boss phase, wave budget, mode time or collectible value on this visit. Do not grant a fresh entry reward. Other mode portals explain that changing mode requires ending the run.

### 3.4 End of run

- Death: record result, clear combat and run resources, show game over. Restart uses the same difficulty and selected mode, but begins a fresh build at the hub with a clear “Launch again” portal.
- Finite objective complete: record victory once, show result, then provide New Run/Menu. A story ending can follow Campaign victory once implemented.
- Endless/Chaos retirement: offer **End Run** from the hub; record retirement, not victory or death.
- Quit to Menu: confirmation warns that the current run and suspended expedition are discarded.
- Changing difficulty requires a new run. There is no mid-run difficulty switch outside debug tools.

Results may visually appear over the colony, but a finished run's wallet/build must not become a reusable bank.

## 4. Orbital colony hub

### 4.1 Environment and readable layout

The player pilots the same Collector ship with the same movement model. Keep camera behavior familiar. The hub is spacious enough for easy navigation but small enough that services are recognizable from the arrival berth.

Required landmarks:

- **Mothership/arrival berth:** central home landmark and the Return Home destination.
- **Human colony backdrop:** lit habitation modules, connecting structures, docking traffic silhouettes or window lights. Background decoration can use existing textures and simple shapes until approved art exists.
- **Repair berth:** clearly labeled service radius and docking progress.
- **Skill shop station:** clearly labeled interaction area, balance and stock panel.
- **Five mode portals:** distinct labels/icons and shape accents; color alone must not communicate mode.
- **Resume marker:** the active mission portal says “Resume” and shows its current objective rather than pretending it is a fresh launch.

Suggested portal arrangement is a broad arc around the station, keeping arrival, repair and shop away from portal confirmation zones. Exact world positions, radii, screen coordinates and visual sizes are future Theme/Balance entries, not inline constants.

The colony must look inhabited without requiring NPC conversations, a walking avatar, new collision-heavy interiors or a simulation of the colony economy.

### 4.2 Safe hub behavior

- No enemy, debris hazard, hostile projectile, boss, barricade or scrap farming spawns in the hub.
- Primary fire, automatic damage skills and manual Return Home are disabled there. Ship movement is allowed outside modal panels.
- Combat cooldown debt, statuses, persistent effects and encounter time freeze; hub time is not a way to recharge offensive skills.
- Do not carry visible hostile projectiles or damaging skill effects into the hub.
- Opening shop or a portal panel captures movement/fire input. Closing it consumes that input.
- E remains auto-fire toggle in combat; use **F** as the proposed nearby-interaction key. A visible Interact button can provide mouse access.
- If multiple interaction zones overlap, select a single nearest service and display its name. Never open two panels from one press.
- Pause/settings may open while free-flying in the hub and resume back to the hub.
- The hub is not another Scene that calls the new-run initialization path.

### 4.3 Repair service

**Health repair is paid, as requested.** Prices use the same spendable trade scrap as the skill shop. The berth offers:

| Service | Selected price | Result after 3 uninterrupted docking seconds |
|---|---|---|
| Repair Hull | `ceil(missingHull / 5)` scrap | Restore hull to current maximum; clear harmful player statuses |
| Affordable Hull Patch | `min(wallet, ceil(missingHull / 5))` scrap, at least 1 | Restore up to 5 HP per paid scrap, clamped to missing hull; clear harmful player statuses |
| Recharge Shield | `ceil(missingShieldPoints / 5)` scrap | Restore shield to current maximum; clear broken/reboot/restoration state |
| Full Service | Hull repair quote + shield recharge quote | Both effects; each component priced once |

Do not floor fractional shield deficits: any positive deficit costs at least 1 scrap. Disable a service with nothing to restore. A full hull needs no repair charge; a full shield needs no recharge charge. The affordable patch appears when full hull repair is unaffordable but the wallet can pay for some healing. Example: 37 missing HP costs 8 for full repair; with 3 scrap, buy a 15-HP patch for 3.

Display exact HP/shield restored, cost and post-service balance before confirmation. Lock that quote and capture input while servicing; no simultaneous shopping. Charge and healing commit together at completion after revalidating funds and deficits. Cancel, leave, pause or quit cannot produce partial free healing: pause freezes service time; cancellation clears the job without a debit or heal; quit cancels it before run teardown. A failed/stale commit returns to the quote without charging.

Repair does not grant scrap, XP, return charge, free cards, shield-break explosions or offensive cooldown resets. A wallet of zero disables paid services, **not** Resume/Undock. The player may resume damaged and earn more, or end the run; there is no free repair, loan, debt or unlimited rescue subsidy. Full service must never be applied automatically on Return Home, portal entry or docking.

There is no combat-field healing zone or physical shortcut to the hub that bypasses Return Home. Automatic objective completion travel is a separate transition.

## 5. Mode contracts

All five requested modes share movement, scrap collection, field leveling, shield rules, Return Home, repair and skill shop. Their encounter director and end condition differ. Difficulty is chosen before the hub; a mode is chosen inside it.

| Mode | Primary objective | Encounter character | Ends when | Return/resume |
|---|---|---|---|---|
| **Swarm** | Survive indefinitely and improve score | Escalating crowds of normal enemies; proposed default has no bosses so Chaos stays distinct | Death or voluntary retirement | Freeze encounter and survival clock; resume same pressure |
| **Survival** | Survive a displayed fixed duration | Increasing pressure over a finite timer | Timer reaches zero while alive, or death | Countdown freezes at home; shopping time cannot win |
| **Boss** | Defeat the designated boss | One focused boss encounter; adds only if part of its design | Boss dead or player dead | Preserve boss HP, phase, adds and attack timing |
| **Chaos** | Survive indefinite mixed pressure | Swarms continue while scheduled bosses appear | Death or retirement; boss death is not victory | Preserve swarm budget, boss and schedule |
| **Campaign** | Complete staged encounters and defeat the final boss | Ordered waves, checkpoints and story progression | Final boss defeated or player dead | Preserve current wave; completed waves stay complete |

### 5.1 Provisional scheduling

- Survival: **300 seconds** combat time as the initial proposed duration. Display “Survive 5:00” before launch. This is a playtest target.
- Campaign: reuse the old **10-wave outline** as a provisional structure, with midpoint boss slot at wave 5 and final boss slot at wave 10. The owner may replace the roster; do not fabricate final boss lore or attacks.
- Swarm: reuse the existing planned Endless normal-wave budget/spawn formulas as initial tuning references; omit its old automatic boss-every-five-waves rule for this mode.
- Chaos: reuse Swarm normal pressure initially; proposed first boss at **180 combat seconds**, minimum **180 combat seconds after the previous boss dies** before the next, maximum **one living boss**. Do not stack missed boss spawns after returning.
- Boss mode: a single designated encounter initially, not an invented boss-rush ladder. Provide a configurable roster entry and honest unavailable state until a playable boss exists.
- Existing barricade event: can remain for Swarm, Survival and Chaos; proposed disabled in Boss and scheduled explicitly in Campaign. It must use expedition time and never trigger in the hub.

These schedules are proposed in the tuning ledger. New boss stats, attacks, animation sheets, phases, loot values and final story names remain pending content. A portal must not claim that a mode works if it only launches the current generic spawner.

### 5.2 Rules at boundaries

- Campaign wave clear does not automatically grant an upgrade card. Only the scrap threshold does.
- Proposed Campaign service checkpoints occur after completed waves. They can automatically offer safe hub transit without a Return Home charge or shield check because the encounter has ended.
- Other modes use the manual return condition while an encounter remains active.
- Objective success/death are resolved once. Proposed tie rule: player death in the same simulation step takes priority over victory.
- After a terminal result, stop scoring and collection. Uncollected loot is not magically converted into currency or XP.
- Uncollected loot at an ordinary wave clear stays collectible until collected or the expedition ends; checkpoint travel freezes it.
- Boss deaths use the selected boss-tier reward range once. Their final encounters remain pending; content tuning can override the explicit tier in Balance, never accidentally inherit low-enemy rewards.
- Separate leaderboard/result identities by mode, difficulty and rules version. The full leaderboard UI is a later feature; record sufficient metadata now.

### 5.3 Fairness and determinism

Use separate RNG streams for encounter schedules, enemy loot, card offers, shop stock and cosmetic scatter. Opening a panel, canceling a portal or rendering effects must not advance encounter/loot RNG.

The determinism promise is the same encounter plan for the same mode/difficulty/seed/rules and equivalent decisions. Adaptive HP based on player level means two players can face different effective HP after different progression choices; do not claim identical entire simulations regardless of inputs.

Combat-time clocks exclude pause, card selection, console, hub and shop. A separate recorded total run duration may include hub service/decision time, while still excluding pause and console, if future leaderboard tie-breaks need it. Label the clocks explicitly.

## 6. One pickup, separate accounting

### 6.1 Trade scrap versus salvage progress

**Owner follow-up:** the exchangeable currency must drop randomly, with 1-3 or more depending on enemy strength. The selected accounting design stores a reward pair on each pickup: `tradeValue = t` and `salvageValue = p`. Trade scrap is money; salvage progress feeds field levels and Return Home. The visual pickup can represent both, without creating two collectible systems.

| Field | Meaning | On pickup | On shop purchase | On return |
|---|---|---|---|---|
| `totalCollected` | Lifetime trade scrap collected in this run; statistics only | +t | Unchanged | Unchanged |
| `wallet` | Spendable trade scrap currency | +t | Subtract confirmed price | Unchanged |
| `levelProgress` | Salvage progress toward field upgrades | +p | Unchanged | Unchanged |
| `returnCharge` | Salvage energy for Return Home | +p, capped | Unchanged | Drain to zero on successful manual return |

There is no allocation menu or conversion fee. Spending money on repair/skills does not undo field progress or discharge Return Home. Random currency luck does not also randomize the level-up/return pace. This separation is the author's chosen implementation interpretation, not an additional owner-specified formula.

There is no capped cargo inventory, deposit conversion, second “credits” currency or banked cross-run currency. `totalCollected` cannot be spent. Wallet and total must not share the same mutable variable.

Scrap is earned on **collection**, not merely on kill, destruction-animation start or magnet activation. Pending destruction value and released world pickups are not spendable yet.

For a collected batch, add its trade sum to total/wallet, resolve level thresholds from its salvage sum and then clamp `oldCharge + salvageSum` against the resulting return maximum. Commit together before opening cards. Merging pickups must sum **both** fields independently, never convert one into the other or reroll trade value. Split debris orbs distribute both totals exactly, even when an individual orb carries zero integer value.

### 6.2 Level progression

- Start player level at 1 and progress at 0.
- Proposed first threshold is **100**, replacing the previous unimplemented base of 30.
- Preserve prior difficulty growth proposals: Easy 5%, Hard 10%, Impossible 15%, compounded per player level.
- `required(L,d) = roundHalfUp(100 * (1 + growth[d])^(L - 1))`.
- At threshold, subtract that threshold, retain all overflow, advance level by one and queue one card choice. If more thresholds are crossed, repeat in order.
- The new level and return maximum take effect when the threshold is crossed. Cards remain mandatory pending choices, so combat/return cannot bypass unchosen rewards.
- Offer three distinct eligible entries, choose one, lock the offer, finish the exit animation and show the next queued choice before combat resumes.
- A purchase does not advance player level. A free field pick does not spend wallet.
- No 20-second card trigger and no extra wave-clear card.
- Pure threshold functions, checked integer arithmetic and bounded processing must prevent overflow or an unbounded frame when debug input supplies very large values.

Example, Easy: collect a batch with 250 salvage and 231 trade scrap from zero at level 1. Costs 100 and 105 are crossed. Result: level 3, progress 45/110, two queued picks, wallet/totalCollected 231 and returnCharge 250. Do not multiply either reward by the number of picks.

### 6.3 Reward eligibility

Centralize reward finalization so every enemy death has one score/kill/drop result regardless of which collision path discovered it:

- Player bullets, cannon, heavy shots, rockets, laser equipment.
- Direct skill damage, damage-over-time, orbiting effects, drones and clone projectiles.
- Enemy/debris collision and legitimate lethal contact paths that currently remove enemies.
- Boss death through its explicit death contract.

Selected initial enemy rewards (uniform inclusive integer currency ranges; all TUNE):

| Enemy reward tier | Trade scrap range | Mean trade value | Fixed salvage progress |
|---|---:|---:|---:|
| Low / basic swarmer | 1-3 | 2 | 2 |
| Mid / ranged enemy | 3-7 | 5 | 5 |
| High / heavy enemy | 8-12 | 10 | 10 |
| Elite, only if later content defines one | 15-25 | 20 | 20 |
| Standard boss | 120-180 | 150 | 100 |
| Final campaign boss | 200-300 | 250 | 200 |

One currency roll per enemy, not one roll per projectile, particle, damage tick or pickup. Assign and store the reward at spawn with a seeded loot RNG isolated from encounter/card/shop/cosmetic RNG; death materializes it only if reward-eligible, collection credits it. Suspended encounters retain the assigned result. Restart/menu visits cannot reroll the same surviving enemy.

Use integer uniform sampling, not modulo-biased random arithmetic. Identical seed and spawn order reproduce loot. Difficulty/player level do not multiply rewards. The elite row is a future reward classification, not permission to add an elite enemy. Boss identity/attacks remain owner content; these explicit rewards are the delegated economy defaults.

Explicit no-reward despawns, resets and scene cleanup stay nonrewarding.

**Space Collapse:** preserve no scrap, no wallet gain, no level progress and no return charge. Its existing score/kill reward remains. Boss erasure rules must follow boss content definitions, not automatically delete a boss.

**Singularity:** normal reward pair. **Barricade segments:** cosmetic breakup and zero in both reward fields. **Ordinary debris:** preserve existing fixed per-kind yields for both trade and salvage and player-destruction restrictions; no new random debris payout.

A final-boss reward still spawns once, but terminal victory does not auto-collect it or delay the ending for farming. Results label collected currency separately from uncollected rewards.

### 6.4 Pickups and magnet

Retain accepted debris visuals: complete per-kind eight-frame animation, saved last-fleck positions, red glow textures and one-time credit on arrival. Do not revert to sliced intact sprites or recolor accepted art as part of this feature.

Ordinary enemy kills create one pickup carrying the whole drop value. It briefly drifts, then waits for collection. Proposed enemy pickups do not expire; preserve value with bounded merge behavior. Existing debris orb timing/homing remains unchanged unless separately authorized.

Touch collection uses a tunable pickup radius. Scrap Magnet retains its level-1 15-second cooldown and 5-second active period, but ordinary pickups are attracted only inside its radius, proposed 60 world units. Outside pickups remain unaffected. After expiry, ordinary attracted pickups settle; the existing debris homing path continues independently.

Pull speed must exceed the actual ship speed including upgrades; proposed floor relationship is `max(basePullSpeed, currentShipTopSpeed * 1.25)`. Growth remains +20% duration, -5% recharge through level 5 with existing positive high-rank continuation, +15% radius through level 5, +10% pull speed per added rank. Card values come from the actual tuning functions.

Use an explicit pickup behavior/type distinction, not a second ScrapManager. Ensure each arrival, direct collection and debug reward feeds the same accounting function.

The proposed ordinary-enemy pickup cap is **500**; preserve the existing **150** debris-orb cap as a separate existing budget. A cap merges incoming value locally into an existing pickup without deleting reward value or moving it directly into the wallet. No all-pairs nearest-neighbor searches each frame; reuse spatial/bounded queries.

## 7. Return Home: the one manual utility

### 7.1 Identity and input

Return Home is a baseline run utility, available from the first expedition. It is not a rare card, purchasable skill or twentieth combat skill. It does not change the combat catalog count.

Proposed input: **Q** and a clickable Return Home HUD control. Q no longer casts the selected manual combat ability once the automatic/persistent conversion is implemented. Space does not remain an unrelated normal-play invincibility-skill key.

### 7.2 Capacity and eligibility

`returnMax(L,m) = 1000 + returnGrowth[m] * (L - 1)`

`returnNeeded = ceil(returnMax * 0.50)`

Proposed per-level growth: Swarm +50, Survival +75, Boss +100, Chaos +125, Campaign +100. These values and the examples are in game-design.md's tuning ledger.

- The requirement is **50% of the current maximum**, not a permanently fixed 500.
- Charge may continue accumulating from 50% to 100%.
- On player level-up, preserve the absolute charge amount; do not preserve percentage or top it up for free.
- If the threshold rises past current charge, readiness disappears and the HUD explains the new amount.
- At the cap, additional scrap still increases wallet, total and level progress; it simply cannot increase return charge further.
- Skill rank purchases do not alter player level or the return maximum.
- Mode is fixed for the run so the player cannot lower the threshold by changing portals.

Example: Swarm level 1 has max 1,000 and needs 500. At level 2 max is 1,050 and needs 525. A stored 510 stays 510, so the ship is no longer ready until it collects 15 more. Half of an odd maximum rounds up; use integer-safe arithmetic.

### 7.3 Eligibility check

All conditions must hold:

1. Player alive, active expedition and ordinary running state.
2. No pause, console, card, shop, portal confirmation or terminal-result input capture.
3. No queued level-up choice.
4. Charge at least the current required amount.
5. Authoritative persistent shield present, online and with positive shield points.
6. No return already pending or committed.

“Shield broken” means zero points or an active broken/reboot state. Hull invulnerability, an equipment shield visual, a temporary protective effect or a queued repair cannot bypass it. A damaged shield with positive points is sufficient; a fully charged shield is not required.

Proposed default for an absent shield is **blocked**, with clear feedback. The recommended starter Deflector avoids this state in normal play; debug/unsupported loadouts must still handle it safely.

### 7.4 Successful and failed requests

- Q/button creates one return request, not an immediate teleport before damage resolution.
- Resolve that frame's normal collision/damage. Death wins. A shield broken by that frame cancels the request.
- Process scrap and thresholds. If cards become pending, open them and cancel the return request; require a fresh Q after choosing.
- Recheck eligibility against the final frame state and updated capacity.
- If valid, commit once: drain charge to zero, suspend expedition, place ship at hub arrival, capture input for the transition.
- If invalid, keep charge and wallet unchanged. Briefly show the reason; do not queue an automatic future return when the shield heals.
- Proposed first version is instant after this validation, with cosmetic transition only. No channeling, invulnerable charge-up, hold-to-cast or cancellation fee is assumed.

A successful return consumes **all current charge**, even at 100%. This simple default should be playtested; it makes the 50%-ready point useful and avoids immediate chained returns. Higher charge currently has no discount or bonus.

Show the most useful blocker: “Shield offline”, “Collect N more scrap”, or “Choose your upgrade first”. Never show “Ready” while another condition prevents use.

### 7.5 Continuity at return

Keep one suspended encounter, not an unlimited stack of saved missions. Preserve enemy identities/HP, boss state, player field position, bullets, pending explosions, pickups, skill snapshots, cooldown debt, spawn schedules and mode time.

Hub movement uses a separate hub position. On Resume restore the saved field position and combat state. Repair changes hull/shield/statuses intentionally; shop ranks change future effects under their normal rank contract. Frozen existing effects retain activation snapshots. No blanket cooldown refill.

Before committing a return, preflight any needed storage. If a transition cannot be completed, leave resources and encounter unchanged. Freezing existing Game-owned world containers is preferable to serializing a save file or duplicating managers.

Projectiles remain at their frozen field positions. Resume consumes its input frame. Do not secretly delete imminent threats or spawn a new boss; any future arrival-protection rule must be separately tuned and documented.

## 8. Persistent shield and combat-skill conversion

### 8.1 Shield ownership

There must be one authoritative normal-play Deflector state: rank, max points, current points, broken flag, reboot remaining and restoration progress. Return eligibility and HUD read the same state used by damage handling.

Equipment prototype shields currently have separate behavior. Keep their debug compatibility as needed, but do not let them become a second hidden shield bar or alternative Return Home gate. Final consolidation belongs to the implementation checkpoint.

**Proposed starter grant:** Deflector rank 1, full 20 points, before first launch. The original ship/weapon appearance remains the baseline apart from the intentional shield presentation. Its first field/shop card is therefore an upgrade, not a duplicate acquisition.

### 8.2 Retained shield target

- Level-1 capacity 20; +5 capacity per added rank.
- While online, regenerate 2 points/second at rank 1, +10% of base per added rank.
- Any hit received with positive shield points is fully absorbed, including the hit that breaks it. Excess damage does not spill into hull.
- At zero, shield goes offline. Rank-1 reboot delay 10 seconds, reduced 1 second per additional rank to a 5-second floor.
- After reboot it returns at 50% of current capacity and fills the remaining half over 3 simulation seconds. During that phase damage still applies; regeneration is capped at capacity.
- Proposed restoration implementation adds the scheduled restoration amount rather than forcing a minimum health percentage each frame. A second break restarts reboot.
- Normal online regeneration does not also double-count the special 3-second restoration phase.
- Pause/card/console/hub freeze combat regeneration except explicit completed repair service.
- Rank increase preserves current absolute points and elapsed reboot debt, clamps new timing safely, and does not revive a broken shield or trigger a free detonation.

### 8.3 Shield Detonation and hull healing

Replace Nano Repair with **Shield Detonation**. Preserve the other 31 catalog keys, yielding **13 augments + 19 combat abilities = 32**. Return Home is outside this count.

Shield Detonation is a separate acquired automatic trigger. On an online-to-broken shield transition, if its internal cooldown is ready, damage nearby enemies once. Retained proposed level-1 values: radius 35, damage 50, internal cooldown 18 seconds; growth +25% damage, +10% radius through rank 5, -10% cooldown using the shared positive high-rank rule.

It cannot prevent the break, resurrect the shield, permit Return Home, or proc from repair/reset/rank purchase. Its normal kills drop scrap through the same reward path.

Remove Nano Repair from cards, shop and public skill catalog; its old command rejects clearly. Hull does not passively regenerate in combat. The documented Reinforced Hull capacity-upgrade exception remains proposed and visible for owner review.

### 8.4 Automatic combat abilities

Do not rebuild existing skill effects. Retain all compatible damage, count, area, duration, companion and status mechanics. Convert activation/targeting and fix connections only.

| Skill/group | Target activation contract |
|---|---|
| Laser Rings | Persistent orbiting blades after acquisition; no duration gaps |
| Deflector Shield | Persistent shield described above |
| Shield Detonation | Shield-break event and its own cooldown |
| Lightning Ring, Radiant Halo, Repulsor Pulse | Automatic around the player when a relevant target is in range |
| Point-Defense Interceptor | Automatic defensive window when hostile projectiles are relevant |
| Scrap Magnet | Automatic collection window when eligible released pickups are in range |
| Nuclear Missile, Space Collapse, Singularity, Armageddon | Automatic bounded dense-group target selection; deterministic ties |
| Chain Lightning | Automatic valid nearby enemy then existing chain logic |
| Plasma Beam, Realm Breaker | Automatic aim toward a valid enemy, not a manual cast slot |
| Blink Drive | Automatic escape from nearby danger; choose a legal destination without bypassing barricade collision rules |
| Hologram Clone, Combat Drone | Automatic existing decoy/companion behavior during combat |
| Corrosive Trail | Automatic trail window while combat movement can place useful pools |

Proposed default: when no valid target/trigger exists, remain ready instead of wasting an activation. Use stable IDs for targeting ties, bounded spatial queries and tuning entries for danger/range decisions. Final targeting numbers require playtest; do not use an O(n²) density calculation every frame.

All abilities owned in the run can coexist under the current prototype ownership model. No new inventory slots, quick-swap screen or manual replacement confirmation.

## 9. Field cards and hub shop

### 9.1 Different purposes

**Field cards:** frequent free random decisions as player level rises. The player stays in the encounter and chooses one of up to three distinct options.

**Hub shop, delegated design:** spend wallet for a deliberate build choice: buy a specific owned skill's next rank, or acquire a rare offered skill. Returning creates access to targeted purchases; it is never required for normal progression. Paid repair/recharge services share this currency at the neighboring berth.

The two systems can upgrade the same skill because their costs and selection methods differ. Both call the same skill/augment acquisition function. A shop must not maintain parallel damage bonuses, separate ranks or its own effect implementation.

### 9.2 Initial shop specification

Two tabs or clearly separated sections:

1. **Upgrade Owned:** list owned eligible skills/augments, current rank, exact next-rank effect and price. Selecting a row opens a purchase preview. Capped augments are labeled Max and disabled.
2. **Rare Offers:** three distinct offers from the four eligible unowned rare abilities below. If fewer than three remain, show fewer. If none remain, say “All rare skills owned.”

Selected rare pool: **Singularity, Space Collapse, Nuclear Missile, Armageddon**. These are existing abilities, not four new classes. They retain the same effects and rank growth when acquired in the field. All other existing augments/abilities are standard for pricing. Owned entries from either category appear in Upgrade Owned.

- Rare skills remain obtainable through field cards at lower weight. Do not make free progression unable to complete a build.
- Stock is generated at expedition start from its own RNG, retained through every dock/panel visit, and not rerolled by leaving/reentering.
- Buying an offer marks that slot sold. It becomes an owned skill available for future targeted upgrades.
- If a field card teaches a skill occupying an unbought rare slot, mark that slot Owned and disable its acquisition; do not replace/reroll it. Its next rank remains purchasable through Upgrade Owned.
- Proposed initial version has **no stock refresh, paid reroll, refunds, selling, consumables, discounts or permanent unlocks**. Later stock expansion can follow playtests.
- Shop access requires docking at the station and opening its panel, not merely having enough currency in combat.
- Return Home itself and the starting shield grant are never rare purchases.

### 9.3 Selected inventory and prices (initial tuning)

See game-design.md for the canonical starting prices:

| Shop item | Price in trade scrap | What the purchase grants |
|---|---:|---|
| Any owned standard augment/ability next rank | `100 + 50*r` | One rank; r is current rank; rank 1 -> 2 costs 150 |
| Any owned rare ability next rank | `200 + 75*r` | One rank; rank 1 -> 2 costs 275 |
| Singularity, unowned rare offer | 240 | Acquire rank 1; crowd control and ordinary rewards |
| Space Collapse, unowned rare offer | 280 | Acquire rank 1; explicitly warns that erased enemies yield neither currency nor progress |
| Nuclear Missile, unowned rare offer | 320 | Acquire rank 1; existing burst effect |
| Armageddon, unowned rare offer | 400 | Acquire rank 1; existing sustained barrage |

No standard skill acquisition is sold: obtain it from field cards, then target its ranks at the shop. Deflector, Scrap Magnet, Combat Drone and every other owned standard ability use the same standard price formula. Capped augments stay capped. Prices are identical across modes/difficulties; no price RNG or price reroll.

The owner delegated inventory/pricing, so these are the selected handoff values rather than unanswered questions. They are not playtest-certified. At the nominal 500 salvage threshold, 250 basic kills produce expected trade income 500, range 250-750, before level-driven increases; this usually funds repair and a meaningful purchase. Actual first return occurs later when leveling raises its requirement. Keep healing inexpensive compared with elective skill upgrades.

Purchase transaction: revalidate run state, item, current rank, eligibility, price and wallet; apply the rank/acquisition exactly once and debit exactly once. Reject stale or repeated click events without charging. If application fails, no currency is lost.

After purchase: wallet falls; totalCollected, player level, level progress and return charge are unchanged. Effects follow normal rank snapshot/cooldown rules. Opening the shop cannot refill drones, revive shields or reset attack cooldowns. To preserve paid hull repair, a **paid Reinforced Hull rank increases maximum HP only**, retaining absolute current HP. Its free field card retains the documented +maximum/+current HP exception. Both use the same rank API with an explicit acquisition-source parameter; the shared card/price preview must explain this intentional difference. Paid shield ranks similarly add capacity without refill.

### 9.4 Shared card and shop descriptions

Generate both presentations from the same live stat functions, not independent hand-typed numbers.

**NEW:** NEW badge, short purpose sentence, AUTO/PERSISTENT/ON SHIELD BREAK tag, rank-1 values and drawback.

**UPGRADE:** current -> next rank and only stats that actually change. Show real rounded damage, count, health, duration, recharge, capacity or force. Do not repeat unchanged descriptions.

- Physical radius/range/length/width/distance stops growing after rank 5.
- Ability counts and other supported numerical growth continue beyond rank 5; cooldown remains positive.
- Passive augments keep their existing cap of 10 where applicable.
- Combat Drone checks: ranks 1..6 -> count 1..6, HP 30/45/60/75/90/105, shot damage 15/19/23/26/30/34.
- Space Collapse checks: radius 32/36.8/41.6/46.4/51.2, then stays 51.2; zone count continues by one per rank. Always show “Enemies killed drop no scrap.”
- Shield Detonation requires owned Deflector; rank purchases cannot skip prerequisites.
- The shop shows a price and Buy state; field cards show no currency price.
- Keep text inside the card/panel at the smallest supported window; prioritize four or five stat lines, with a detail area if necessary.

No successful selection/purchase can activate twice while its exit animation or feedback is still playing.

## 10. Difficulty and enemy scaling

Retain Easy/Hard/Impossible and their 5%/10%/15% progression growth proposals. Initial enemy HP factors are 1.00/1.25/1.50; initial enemy damage multipliers remain 1.0 for all.

Proposed HP computation:

`spawnHP = roundHalfUp(baseHP * modeEncounterHPFactor * difficultyBaseHP * (1 + growth[difficulty])^(playerLevel - 1))`

Apply each factor once, with checked bounds, minimum 1 and a documented maximum effective scaling factor (initial proposal 50x). Mode/wave factors come from the selected schedule; do not apply the old wave multiplier again in EnemyManager after the director already applied it.

Snapshot HP at spawn. Level-up or shopping must not heal or resize existing enemies, rewrite boss phases or recalculate their remaining health. Difficulty does not automatically modify movement, hitboxes, scrap values or loot rarity.

Difficulty preview describes its real effects and selected mode preview describes its real objective. Do not label difficulty choices as game modes in code/UI.

## 11. HUD, menus and input

### 11.1 Field HUD

Required information, ordered for readability:

- Hull and persistent shield, including offline/reboot status.
- **Scrap** wallet at top center; lifetime collected in result/details, not mislabeled as available money.
- Thin player-level progress bar immediately below: `Level L — progress / required`.
- Separate Return Home meter: `charge / maximum`, 50% marker, Q hint and readiness/block reason.
- Mode objective and combat timer: Survival countdown, Campaign wave, Boss name/HP, Swarm/Chaos elapsed time.
- MENU button inside the top-right safe region.

If the original scrap-total display is retained, label it “Collected” beside a clearly separate “Available” wallet. Never let a smooth visual counter determine affordability or readiness.

Use modest pickup feedback: short count-up, at most a 10% pulse and throttled existing sound. Aggregate gains rather than one popup per orb. All gameplay HUD effects freeze with simulation. Return charge and XP must look distinct even though the same pickup fuels them.

### 11.2 Hub UI

Show mode/difficulty, wallet, player level and current objective status. Portal preview lists objective, ending condition, approximate duration if finite, and “Launch” or “Resume.” First launch locks the mode for the run.

Shop rows show ownership/rank, next effect, cost and unavailable reason. Repair shows service progress and current hull/shield. Never show a return-to-home button as useful while already home.

All required text/buttons stay in the existing 3840x2160 CRT-safe canvas; initial window remains 1280x720. Use existing Button/font/hover/click design, Theme tokens and existing render pipeline. The colony may fill the background; text must not sit against cropped edges.

### 11.3 Pause/settings still to build

Visible pause overlay: **Resume**, **Settings**, **Quit to Main Menu**, with confirmation before discarding a run. Show selected mode/difficulty.

- Esc/P/MENU opens pause from field or hub free-flight.
- Resume restores the exact prior state; does not always force GAME_RUNNING.
- Esc/Back in Settings returns to pause, not directly to combat.
- Esc/Cancel in quit confirmation returns to pause.
- Card selection owns its input and does not open another pause layer.
- Shop/portal panels close with Esc to hub; subsequent Esc can pause.
- F5 capture remains highest priority and preserves the underlying state.
- Shared Settings panel works from both main menu and pause. Required master volume only; separate music/SFX sliders only if the existing audio structure supports them.
- Settings are session preferences and survive a run reset. File persistence/fullscreen are deferred; key rebinding/controller settings are out of scope.

## 12. Ownership and lifecycle contract

Use existing Game, Player, SkillSystem, ScrapManager, EnemyManager, Card, Button, DebugTools and planned WaveDirector/Dock/shop boundaries. Do not invent a scene per mode or a second scrap/skill manager.

| Responsibility | Proposed owner/integration |
|---|---|
| Difficulty and selected mode | Typed run configuration, created by menu/hub flow |
| Wallet, collected total, level/progress, pending picks | One Game-owned run-progress value |
| Return charge and eligibility | Game-owned run utility reading authoritative Player/SkillSystem shield state |
| Encounter schedule/objective/result | Planned WaveDirector extended for typed mode policies |
| Pickup/destruction lifecycle | Existing ScrapManager; Game commits collected rewards |
| Skill rank/effect | Existing SkillSystem/Player augment APIs |
| Shop eligibility/price/transaction | Planned UpgradeShop adapted to skill catalog; no old gear-stat duplication |
| UI | Existing Button/Card plus planned PauseOverlay/DockShopUI and HUD |
| Mothership, berth, portals | Existing planned Dock/Entity approach; data-driven interaction zones |

State identifiers are proposed, not existing declarations: HUB, PORTAL_PREVIEW, RUNNING, AUGMENT_SELECTION, PAUSED, DOCKED, RESULT, GAME_OVER. Returning is a validated transition; it need not be another Scene.

### 12.1 Reset versus temporary suspension

| Data | Pause/cards | Return -> hub -> Resume | Fresh run/death/quit |
|---|---|---|---|
| Enemies, boss, projectiles, pickups | Freeze | Preserve suspended world | Clear |
| Field position/camera target | Preserve | Save separately from hub position; restore | Initialize |
| Mode timer/spawn schedule | Freeze | Freeze | Reset |
| Wallet/total/XP/player level | Preserve | Preserve | Reset |
| Return charge | Preserve | Drain on manual return; no refund on Resume | Reset |
| Skill ranks/augments | Preserve | Preserve; shop may upgrade | Reset to starter contract |
| Combat cooldown/effect snapshots | Freeze | Freeze; purchases follow rank rules | Reset |
| Hull/shield/status | Preserve | Preserve except completed repair | Initialize |
| Shop stock and RNG state | Preserve | Preserve | Reseed/regenerate |
| UI pages/transaction flags | State-owned | Clear stale panels/requests | Reset |
| Difficulty preference/volume | Preserve | Preserve | Session preference survives |

Hub and docking transitions must not call `Game::onSwitch()`, `resetRun()` or singleton reset methods. True run teardown must clear every pending reward, return request, card queue, shield-break trigger, shop transaction and suspended encounter observer.

## 13. Remaining work packages

These are future implementation dependencies, not permission to change code now. A teammate can authorize the complete scope once, then implement sequential buildable checkpoints without requiring repeated design prompts.

| ID | Remaining work | Dependencies | Done when |
|---|---|---|---|
| T01 | Typed mode/difficulty, run-progress/return formulas, accounting and reset contracts | Adopt proposed defaults | Pure calculations and resource invariants are verified |
| T02 | Central death/drop finalization, pickup integration, radius magnet | T01 | Every reward path is single-credit and preserves exclusions/art |
| T03 | Field progression/queued picks, shared description data, remove timed trigger | T02 | Real scrap creates correct field choices and overflow |
| T04 | Persistent shield, starter grant, automatic skills, Shield Detonation replacement | T01/T03 | One shield source; 32 combat entries reachable; correct rank/target behavior |
| T05 | Start/difficulty/hub flow, colony presentation, services and portal previews | T01 | Start reaches safe hub; no combat starts before confirmed portal |
| T06 | Director and five real mode objectives with content slots | T05; boss content for Boss/Campaign/Chaos | Each portal has actual specified behavior or honest pending availability |
| T07 | Return request/commit, suspension/resume and repair | T02/T04/T05/T06 | Charge/shield gates and world continuity hold |
| T08 | Targeted skill shop and rare stock | T03/T05/T07 | Same skill effects, atomic spending, no stock/return exploit |
| T09 | Visible pause/settings, final HUD/input/tutorial integration | T03..T08 | All states readable, input captured, new timers freeze |
| T10 | Full integration, reset, balance/performance and documentation evidence | All adopted scope | Complete play loop and verification matrix pass |

Boss content is a real dependency. Framework completion is not Boss/Campaign/Chaos completion. Avoid generating new bosses or silently deleting requested modes to make a checklist green.

No unrelated refactors, dependencies, asset generation, online systems, save-game system, walking avatar or new skill families are implied. Existing content may use placeholders for visuals only; objective and gameplay logic must be real.

## 14. Verification matrix for later implementation

### 14.1 Accounting and formulas

- Verify level requirements for levels 1, 2, 5 and 10 at all three difficulties against game-design.md.
- Verify return maximum/50% threshold for all modes at levels 1, 2, 5, 10; odd maximum rounds up.
- Collect a reward pair through each path: wallet/total gain trade, XP/charge gain salvage once; capped charge does not discard trade/XP.
- Collect salvage 250/trade 231 on Easy at level 1: two picks, level 3, progress 45, wallet 231; test large batches and checked limits.
- Buy rank 2 from rank 1 with exactly 150 wallet: success leaves zero; 149 fails without mutation.
- Purchase changes no player-level requirement, charge or collected statistic.
- Verify inclusive reward endpoints and deterministic seeded samples for every tier. Swapping menu/cosmetic/card activity must not change an enemy's stored roll. Do not require a small random sample to match theoretical frequencies exactly.
- Merging/splitting conserves both trade and salvage independently; no-reward deaths emit neither.
- Hull deficit 37 quotes 8; wallet 3 buys 15 HP for 3. Zero wallet cannot heal. Fully repaired components are not charged.
- Cancellation, pause, repeat clicks and stale service quotes never produce a debit without healing or healing without a debit. Full Service is the sum of its two component quotes.
- Rare acquisition prices and rank-1 upgrade prices (standard 150, rare 275) match the shared preview. Paid Reinforced Hull increases max HP without current-HP healing.
- Shop reentry, resume, reset cleanup, expired cosmetic effects and destroyed barricades award no scrap.

### 14.2 Shield and Return Home

- Below 50% fails; exact threshold succeeds with an online shield.
- Full charge with broken shield fails and retains charge.
- Shield at one positive point permits eligibility; a breaking hit in that frame cancels return and causes no hull spill.
- Reboot returns the shield at 50%; paid shield/full service restores it without detonating; hull-only repair leaves shield state unchanged.
- Level increase can revoke readiness; no charge fraction is preserved for free.
- Death, queued card, pause, F5 and hub reject Q without consuming resources.
- Double click/Q in one frame commits only once; success drains all charge.
- Missing shield fails with an explanation; starter grant prevents this in supported normal runs.
- Repair/level upgrade cannot double-trigger Shield Detonation or erase cooldown debt.

### 14.3 Flow, modes and suspension

- Start -> difficulty -> hub -> preview -> launch; cancel each panel and verify no ghost run/spawn.
- Spend time in hub before launch: zero combat time and no hostile world effects.
- Return during a boss projectile attack, repair, buy a skill, resume: enemy HP/phase, projectile position, spawn debt and loot match saved state.
- Pause/cards/hub do not advance Survival countdown; surviving the entire combat duration wins exactly once.
- Swarm has no unintended old Endless boss wave; Chaos boss death does not end the run.
- Campaign clears waves without free wave cards and wins only at the final required boss.
- End run/change mode resets wallet, level, charge, skills, stock and director; no cross-mode farming.
- Resume consumes input so Launch/Buy/Resume never fires the gun underneath.

### 14.4 Cards, effects and shop

- Every retained/new catalog entry reachable through adopted acquisition rules.
- Verify NEW and UPGRADE text against live gameplay for ranks 1..8 and 12, including frozen size after 5.
- Starter shield is shown owned; capped augments excluded; distinct offers; no empty selection deadlock.
- Every automatic ability chooses a legal target or waits ready; no manual Q replacement prompts.
- Inspect shop stock persistence, prerequisites, sold states, empty stock, insufficient funds and duplicate click handling.
- Existing drone/clone/status/collision behavior and no-scrap Collapse contract remain intact.

### 14.5 Runtime and presentation

- Reuse the existing native harness; Debug/Release checks and relevant sanitizer runs; record actual output.
- Existing pause regression remains a preserved baseline. Extend it for mode time, return/XP HUD, shield reboot, shop and hub state.
- Compare simulation at 30/60/144 FPS; no wall-clock catch-up bursts.
- Stress mass kills and bounded pickup merging; verify full value conservation.
- Run existing collision/crowd benchmarks and the 80-enemy 60 FPS target; report comparable conditions rather than claiming historical FPS is current.
- Inspect native images of difficulty, colony hub, all portal summaries, HUD, shield-offline return, cards, shop, pause and settings.
- New run/restart/quit repeatedly leaves no enemy, bullet, pickup, RNG stock, rank or transaction state behind.
- Keep `--skills-list`, F5 autocomplete and valid existing commands; Release still rejects debug launch arguments as documented.

Suggested future debug additions: `scrap add`, `scrap status`, `progress fill`, `level set`, `return status`, `hub`, `mode status`, and `shop status`. They must route through real owners, mark debug-altered runs ineligible for ranked results, and remain absent from normal controls. Exact command syntax is implementation work, not a claim they exist now.

## 15. Open decisions and balance work

1. Playtest the selected paired reward model: random trade currency, fixed salvage progress, no spending of XP/return charge.
2. Playtest the delegated shop inventory/prices and paid repair. These details have now been chosen; no repeated design permission is needed.
3. Confirm starter Deflector and strict missing-shield block. This makes the broken-shield return rule coherent without relying on random acquisition.
4. Confirm Return Home drains all charge and uses Q; confirm no extra manual combat slot.
5. Playtest 100/1,000 starting values, mode growth, drop income, level growth and shop costs together. The threshold moves while collecting; nominal 500-scrap return is not necessarily attainable at level 1.
6. Supply actual bosses: identity, arena, telegraphs, phases, damage/HP, adds, durations and scrap rewards. Adopt or replace old Hoarder/Core proposals.
7. Confirm Survival duration, Chaos cadence, Campaign structure and checkpoint travel.
8. Evaluate frozen-projectile reentry fairness and targeted shop progression against an injured boss. No hidden boss healing or free invulnerability is specified.
9. Verify source-aware Reinforced Hull text/effects: free field card may grant current HP; paid rank may not bypass repair pricing.
10. Decide submission priorities if all five modes cannot be verified by 25 October. Keep requested scope visible; a cut requires team direction.

The useful first balance measurements are time to first field card, time to first eligible return, wallet at first shop visit, purchases per visit, shield-offline deaths, survival clear rate and boss time-to-kill. Record observed results before calling any proposed numbers balanced.
