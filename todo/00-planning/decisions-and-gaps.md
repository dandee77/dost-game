# Decisions, Missing Details and Implementation Gaps

**21 October 2026. Preparation register, not a feature-completion report.** Read [TODO index](../README.md), [gameplay handoff](../02-gameplay/gameplay.md) and [progress tracker](../../context/progress-tracker.md) first. Existing code evidence comes from the documented prior read-only audit and tracker; this revision does not claim a new runtime audit or that every old finding persists after future pulls.

## Current review scope — owner follow-up

[Upgrade proposals](../07-upgrade-proposals/README.md) supply candidate weapon, attribute, Luck and automatic-skill rarity details. Confirmed: mothership cannon tiers, one branch/run, 25% purchased numeric gains, shield cards retained and Legendary reactive Blink. Other details remain open. Boss designs, schedules, final names, layouts and broad economy review are owner-deferred. Send no further questions during preparation; collect upgrade choices in the review checklist.
## 1. How to interpret this file

**Confirmed** means the owner chose the direction. **Delegated** means the owner asked us to select a detail. **Proposed** means a concrete default is written for review and later adoption. **Content needed** means the teammate must obtain or author the actual content before claiming that feature complete. None of these labels means implemented.

The teammate's later instruction may authorize a complete implementation sequence, but each dependency checkpoint still needs a buildable result and verification. This folder is preparation, not permission to start coding now. Do not treat an unchecked production task as a reason to reimplement completed pause, equipment, skills, debris art or collision work.

## 2. Decisions already captured

| ID | Decision | Status | Authoritative brief |
|---|---|---|---|
| D01 | Player remains in the ship; safe orbital colony hub after Start/difficulty | Confirmed | [Gameplay](../02-gameplay/gameplay.md) |
| D02 | Five mode portals: Swarm, Survival, Boss, Chaos, Campaign | Confirmed | Gameplay; each needs a real objective |
| D03 | Normal upgrade cards earned in the field | Confirmed | Gameplay; no paid unlock or forced return for normal leveling |
| D04 | Paid hull repair and random enemy trade currency | Confirmed | [Game design](../../context/game-design.md) |
| D05 | Separate fixed salvage progress for level/return, one random trade wallet | Selected accounting proposal | Gameplay; no cross-run bank or cargo conversion |
| D06 | Skill shop stocks targeted ranks and priced rare skills | Delegated item/price choice | Game design; acquisition/rank rules already detailed |
| D07 | Return usable at half of rising capacity, blocked by broken shield | Confirmed behavior; exact growth and starter shield proposed | Gameplay |
| D08 | H.O.P.E. Colony: Habitat for Orbital Preservation and Endurance | Delegated naming choice | [World and campaign](../01-story/world-and-campaign.md) |
| D09 | Failed remediation affects terrestrial and orbital waste; near extinction in under a decade | Confirmed premise | World and campaign |
| D10 | No special tree/seed solution or radiation origin; source isolation enables gradual restoration | Confirmed direction | World and campaign |
| D11 | 2718 breakthrough, 2723 release, 2732 collapse estimate, 2733 cadet deployment | Proposed exact dates | World and campaign |
| D12 | Earlier engineered waste-eaters mutate after exposure to the separate atmospheric treatment; living organisms occupy scrap shells | Confirmed fictional origin; space support and exact creature design proposed | [Science notes](../01-story/science-notes.md) |
| D13 | Six material families, single currency, no crafting gate | Proposed taxonomy and minimum scope | [Scrap types](../03-economy/scrap-types.md) |
| D14 | Alternating story cards and moving footage | Confirmed presentation | [Story/trailer](../01-story/story-context.md) |
| D15 | Intro before menu once per launch; 40-second intro, 24-second ending, 90-second trailer | Proposed pacing/placement | Story/trailer |
| D16 | Neglect and postponed responsibility lead to catastrophe; survivors earn hope through sustained recovery | Confirmed theme; slogan wording drafted | [Theme and slogans](../01-story/narrative-theme.md) |
| D17 | Altered organisms collect indiscriminately and bind retained scrap as armor; inherited traits change across subsequent generations | Confirmed armor direction; detailed biology remains a fictional proposal | [World section 4.1](../01-story/world-and-campaign.md) |

Paid repairs, random trade drops and the shop price list are already specified. They need balance measurements later, not another empty “decide a shop” task.

## 3. What remains missing beyond artwork

These are the areas not fully covered by merely adding a hub, scrap bar or new story. Some have code prototypes; others exist only in the plan. Prioritize resolving P0 data before the relevant future checkpoint. P1 items are necessary for the promised product and presentation, not optional art polish.

| Gap | Priority | Existing evidence / missing contract | Selected next action and owner | Ready when |
|---|---|---|---|---|
| G01 Boss encounter content | P0 before T06 | Old boss names/designs are provisional; no approved complete roster | Owner supplies two campaign guardians and which existing encounters Boss/Chaos reuse; gameplay designer completes template below | Every enabled boss has attack/phase/spawn/death/arena data and a testable objective |
| G02 Mode pressure tables | P0 before T06 | Durations and boss slots are specified; exact ordinary spawn composition, cadence and population budgets are not | Gameplay designer authors each mode/difficulty schedule in game-design.md using existing enemy profiles | Every interval/wave has budget, caps, completion and fallback behavior; no generic-spawner portal masquerades as a mode |
| G03 Equipment access | P0 before loadout UI | Weapons/engines/shields exist as debug prototypes; normal acquisition is not settled | Normal cannon start with confirmed mothership branching; proposed five-tier families in PREP-22; equipment/shield integration still needs adopted data | A non-debug new run has a defined loadout; no inaccessible menu promises; equipment shield and Deflector cannot stack accidentally |
| G04 Card selection distribution | P0 before T03 | Field thresholds, repeats and overflow are specified; exact eligibility/rarity weighting is not | Review the five-grade candidate table and independent Legendary gate; confirm eligibility, caps and fallback before T03 | Catalog matrix states starter/owned/rare eligibility, duplicate handling, exhausted pool and deterministic stream |
| G05 Automatic ability targeting | P0 before T04 | Most abilities exist, but manual-to-auto conversion needs per-ability targets and triggers | Expand the per-ability trigger table in gameplay section 8.4 with exact ranges/selection; nearest-target abilities use stable ID ties, area/danger abilities keep their own policies | Range, aim source, no-target retry, obstacles, cooldown commit and snapshot behavior specified for all relevant skills |
| G06 Mobility automation | P0 before T04 | Blink/boost behavior cannot safely be inferred from generic auto-cast | Legendary incoming-hit Blink is confirmed; adopt exact safe-screen rescue/cooldown/protection details from the new brief before T04 | No teleport into an obstacle or off the playable area; prompt accurately states trigger |
| G07 Arena/hub geometry | P0 before T05/T06 | Hub behavior is detailed; world dimensions, separation and bounds need actual layouts | Level designer supplies scaled hub and arena diagrams; reuse existing coordinate conventions | Spawn, service radii, gate radii, camera, obstacle clearance and return/resume positions are measurable |
| G08 Scoring and result identity | P0 before leaderboard | Old cargo-deposit/Story-Endless formula conflicts with the new economy/five modes | Proposed minimum removes deposit bonus and scores combat/objectives only; gameplay designer publishes exact weights before ranked UI | Every result has explicit mode/difficulty/rules, deterministic tie order and no repair/shop/return farming |
| G09 Persistence and leaderboard data | P1 | Local leaderboard flow and result serialization need complete schema | UI/programming owner designs local-only versioned entries; no mid-run save | Name limits, invalid-file handling, duplicate submission prevention, debug eligibility and separate boards verified |
| G10 Input and accessibility | P1 | Existing input uses mouse/keyboard; new hub/cards/pause can leak clicks | UI owner documents focus and consumption for each panel; readable labels and distinct shapes supplement color | One action per press; no fire/launch through panels; all required text fits safe area and standard resolution |
| G11 Tutorial sequence | P1 | Planned tutorial has no complete trigger/copy/once-state list | Use the sequence below; UI owner decides exact placement and dismissal | New player understands launch, field cards, return blockers and paid repairs without external explanation |
| G12 Story playback lifecycle | P1 | Storyboard exists; current cutscene wiring does not prove playback | Adopt story-context.md's proposed placement/skip routes; programmer validates existing base | Intro, ending, skip, replay per-session rule and frozen results work without hidden simulation |
| G13 Audio behavior | P1 | Assets/mute prototype do not define all hub/mode/pause transitions | Audio/UI owner defines buses, mute/volume, fades and interruption priorities | No stacked music, repeated dock loops or sound after exit; sliders affect all intended sources |
| G14 High-rank and crowd limits | P0 before scaling release | Rank formulas can keep growing; prior performance baselines do not prove a full new load | Programming owner defines numerical overflow, spawn/effect budgets and visual aggregation without silently capping earned progression | Bounded allocations/queries and retained reward correctness at the declared target load |
| G15 Outcome ordering | P0 before T06 | Existing gameplay brief proposes death before same-step victory | Adopt that default consistently across Survival, Boss and Campaign; world shutdown must not revive the player | Same-step fatal hit/final kill is defeat; source flags/reward finalization occur once without a victory scene |
| G16 Release and competition readiness | P1 | Eligibility, team-machine validation and submission work remain in tracker | Producer resolves existing eligibility question and confirms actual deliverables; no contact sent by this context task | Approved scope, tested release, disclosures, separate demo/trailer, forms and submission confirmation |

G03-G06 are proposals, not a new implementation instruction. The later team may replace them, but must do so in the authority document before shipping contradictory behavior. A disabled ability or portal is a visible incomplete feature, not evidence that the full requested scope is complete.

## 4. Boss definition template

Create one authored record per final boss before its implementation checkpoint. This template does not choose the owner's boss designs.

| Field group | Required content |
|---|---|
| Identity | Final name, role, material silhouette, source relationship, allowed modes, encounter ID |
| Arena | Bounds, entry and safe spawn, camera framing, obstacles, exit/return rules |
| Stats | Base HP/contact damage, difficulty/level factors applied once, movement speed, collision radius, rewards and material family |
| Attacks | For each attack: windup, readable telegraph, active duration, projectile/contact behavior, recovery, damage, range, target selection and cooldown |
| Phases | HP thresholds, transition duration/invulnerability if any, canceled attacks/projectiles, one-time transition flags |
| Adds | Enemy profiles, cap, cadence, ownership, whether required for completion, source shutdown behavior |
| Fairness | Avoid unavoidable spawn hits; give room to read/dodge; say how safe resume preserves attack state |
| Death | Single resolution, source-emitter stop, remaining-add handling, eligible reward exclusions, cinematic/result transition |
| Tests | Minimum-load clear, strongest supported build, return during every phase, no-loot kill, simultaneous player death, restart and repeated encounter |

Campaign proposes two source sectors. Reusing their bosses in Boss/Chaos avoids implying an additional roster. Their mode-specific outcomes must still differ: Boss ends the encounter, Chaos continues and Campaign advances/ends its source objective.

## 5. Mode schedule template

For every enabled mode and difficulty, specify: encounter seed/rules version; startup delay; spawn ring/allowed region; enemy mix; alive cap; spawn budget and spend rules; escalation interval; wave-clear versus time-window conditions; boss schedule; source-add ownership; cleanup/despawn behavior; pause/hub suspension; retirement/success/defeat criteria.

Default envelopes already selected: Swarm endless without bosses; Survival 300 combat seconds; Boss one encounter; Chaos first boss at 180 combat seconds then at least 180 seconds after the prior boss dies, one alive; Campaign ten waves with bosses at five/ten. These envelopes are not full spawn tables. Do not claim that schedule design is finished until each row can be simulated without the implementer inventing new numbers.

## 6. Tutorial copy and trigger proposal

| Step | Trigger | Short message | Completion / repetition |
|---|---|---|---|
| H1 Arrival | First hub arrival in a new application session | “Fly to a route gate. Press F to review its mission.” | Dismiss after portal preview; show again only if explicitly replayed later |
| H2 Services | First service panel opened | “Repairs and skill upgrades cost Trade Scrap.” | Close with the panel; real prices remain visible |
| F1 Recovery | First credited pickup | “Trade Scrap buys services. Salvage earns field upgrades and charges Return Home.” | One short nonblocking prompt; do not pause enemy simulation just for flavor |
| F2 Level | First queued field choice | “Choose an upgrade. Your next level needs more Salvage.” | Existing mandatory card panel owns input; do not stack a tutorial modal |
| F3 Return ready | Threshold met while shield online | “Return Home is ready. Press Q to visit HOPE.” | Once per application session; HUD carries later readiness |
| F4 Return blocked | First attempted return with broken shield | “Shield offline. Return Home unavailable.” | Immediate feedback on every blocked attempt; extended explanation only first time |
| H3 Resume | First successful field-to-hub return | “Repair, upgrade, then resume this expedition.” | Highlight Resume; choosing another mode explains fresh-run reset |

Store tutorial visibility outside the individual run only for the current application session; no save-file requirement. Restart clears run markers but does not spam every introductory prompt. A player can ignore nonblocking tips. Required transaction/return errors must always display even after tutorial tips are exhausted.

## 7. Result record proposal

Before leaderboard integration, define: schema/rules version, unique run/result ID, mode, difficulty, seed identity, outcome (victory/defeat/retired), score, combat elapsed time, completed waves, boss kills, total trade collected, final level and debug/ranked eligibility. Wallet is not lifetime collected. Hub time does not increase combat time. Paused or cinematic time must not affect survival duration or speed comparisons.

Recommended ordering: score descending, then completed objective progress descending, then combat clear time ascending for victorious finite modes; endless ties use completed waves then combat duration descending; final exact ties preserve insertion order. This is a proposal pending G08's published score formula. Do not mix rules versions or modes on the same competitive board.

Only one finalized result may be submitted once. Ending skip, repeated result-menu entry or saving twice cannot duplicate it. No leaderboard design may require persistent ship upgrades, online accounts or networking.

## 8. Remaining decisions to discuss with the owner — later

The current upgrade checklist takes priority. The broad review below is deferred for bosses, schedules, final names, layouts and general economy; do not send those questions now. Later review: review the proposed chronology, final Scavenger name/body plan and protected orbital core; approve/revise the six scrap families; supply the boss concepts; choose the final game title. The biological origin and neglect theme are now owner-selected; do not reopen the retired autonomous-machine premise. The team can author spawn schedules, targeting matrices, geometry, score values and technical limits from the templates before coding. Existing paid repair and shop prices need a later playtest, not speculative reapproval now.

Preparation is ready for an implementation brief only when blocking content and data have an explicit owner, an adopted default or a documented deferral that is visible in the product scope. “Everything is done” cannot mean merely that all missing details have a heading.
