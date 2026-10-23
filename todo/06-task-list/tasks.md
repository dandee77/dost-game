# Open Work and Attention List

**Last reviewed: 23 October 2026.** Initial inventory comes from the current preparation documents and recorded implementation status. It is not a fresh source-code or runtime audit. Update this file as work is discovered or verified; see [maintenance rules](README.md). Implementation is deferred until the teammate authorizes it.

## Start here

**Latest Boss-mode acceptance:** each kill reveals one base portal; entering base preserves the run; next launch creates the next boss once. Add phase thresholds and named HP bars to PREP-01/T06/T09 acceptance. Portal shield/energy bypass remains pending. Retire the one-boss-victory and proposed half-energy-start assumptions; do not mark mode implementation complete from this contract update.

- [x] **DOC-12 — Fresh-run rule and boss proposal delivered.** Owner confirmed always-reset gameplay. Four boss concepts, canonical attack/stat proposals and overlap/fairness rules are documented for review. 283 local links resolve; whitespace and existing build pass. PREP-01/T06 stay open for approval and implementation.

**24 October follow-up:** Between-run progression is settled: always start fresh, no permanent gameplay unlocks/stat bonuses. Boss drafting is delegated to us; PREP-01 now reviews [the concrete roster/attack proposal](../02-gameplay/boss-roster-draft.md) instead of waiting for owner-authored concepts. Review approval and T06 implementation remain open.

**24 October verified subcheckpoint:** Natural spawning/ordinary HP/barricade pacing, paired eligible loot and salvage-driven choices are implemented. Build and three CTests pass; pure math passes ASan/UBSan. BAL-01 remains open for high-rank skills, weapon/shield integration and human pacing trials. T01–T03 remain partial: typed modes/return integration, final pickup budgets and rarity rules are pending.

- [x] **DOC-11 — Balance/context review delivered.** [Report](../08-review/balance-and-context-review.md) separates implemented and pending work, resolves historical authority/input/formula contradictions and lists necessary owner confirmations.

**Latest owner instruction:** Implementation and full balance review are now authorized. Earlier context-only/general-balance/schedule deferrals below are historical. Current checkpoint sequence is pacing, T01 accounting, T02 paired rewards, T03 queued field choices. Boss content still needs definition; Chaos now requires all finished bosses and increasing concurrency with elapsed combat time.

- [ ] **BAL-01 — Population-led balance pass.** Replace abrupt spawning/exponential HP targets, unify weapon/skill rewards, connect salvage leveling, verify rounding/overflow/reset and publish current versus pending stats. Pure calculations and regression checks do not certify human balance or complete the missing hub/boss/weapon features.

The current work is context preparation. Resolve the design prerequisites below before their affected implementation checkpoint. Keep the requested five-mode scope visible; any submission reduction needs team direction. Release dates and original competition requirements remain in the [overview](../../context/project-overview.md) and [main tracker](../../context/progress-tracker.md).

## Current owner review focus — 23 October economy, batteries and return portals

Selected prices, materials, repair and the five-size battery design are recorded in game-design.md. PREP-28 is adopted; PREP-29 portal placement/input details remain open. Implementation is pending; no source/assets changed.

Read [upgrade proposals](../07-upgrade-proposals/README.md). Confirmed: one weapon branch/run, mothership-only cannon tiers, 25% paid numeric gains, retained shield cards, automatic combat and Legendary reactive Blink. Owner resumed questions and accepted the latest weapon names/tree with T4/T5 branching (1/3/5/7/10 nodes). Full profiles/signatures are drafted in game-design.md; numbers, exact card compatibility and runtime balance remain open. Luck, other rarity grades/weights and Blink tuning remain proposals.

**Owner-deferred:** PREP-01 bosses, PREP-02 schedules, PREP-07 layouts, PREP-17 and the final-name portion of PREP-18, REVIEW-02 broad balance review beyond the owner's reopened pricing/material choices. Keep these incomplete dependencies; do not erase them, claim completion or request those decisions now.

## Preparation and decisions

- [ ] **PREP-30 — Owner review — Owner: owner/gameplay designer.** Review the [complete game logic/statistics audit](../08-review/full-game-review.md), especially R01–R20: authoritative shield, moving return threshold, XP/enemy HP growth, card compatibility, high-rank skill budgets and economy pacing. Owner requested the full picture before choosing improvements. Report delivery does not approve all draft stats or implement changes.

Reference for PREP-01 through PREP-16: [detailed gap register](../00-planning/decisions-and-gaps.md), including the boss/schedule templates and proposed tutorial/result behavior.

- [ ] **PREP-01 — P0 — Owner-deferred — Owner: owner/gameplay designer.** Finalize campaign guardians and the encounters reused by Boss/Chaos. Done when every enabled boss has identity, arena, attacks, phases, telegraphs, adds, stats and death/source-resolution rules. Corresponds to G01; needed by T06.
- [ ] **PREP-02 — P0 — Owner-deferred — Owner: gameplay designer.** Author mode/difficulty spawn tables. Done when each wave or time interval specifies enemy profiles, cadence, budget, population cap, escalation and completion; envelopes alone are insufficient. G02; needed by T06.
- [ ] **PREP-03 — P0 — Owner: gameplay designer.** Finalize starter/equipment integration using the confirmed mothership branch direction; family content is tracked in PREP-22. Done when existing debug equipment has a clear inclusion/defer decision and equipment shields cannot accidentally stack with Deflector. G03.
- [ ] **PREP-04 — P0 — Owner: gameplay designer.** Review the new five-grade candidate weights and independent Legendary gate; keep eligibility/fallback approval open. Done when exact weights, distinct offers, rarity, prerequisites, capped entries and exhausted-pool handling are documented. G04; needed by T03.
- [ ] **PREP-05 — P0 — Owner: gameplay designer.** Complete the automatic-skill targeting matrix. Done when each relevant ability has exact trigger/range, valid targets, tie handling, no-target behavior and cooldown commitment. G05; needed by T04.
- [ ] **PREP-06 — P0 — Owner: gameplay/level designer.** Finalize Blink and other mobility automation. Legendary reactive rescue is confirmed; exact numerical/safety review is PREP-26. Done when triggers and legal destinations respect obstacles, barricades and arena bounds. G06; needed by T04.
- [ ] **PREP-07 — P0 — Owner-deferred — Owner: level designer.** Draw measurable hub and arena layouts. Done when entry/resume points, service/gate radii, separation, bounds, camera and safe flight paths are specified. G07; needed by T05/T06.
- [ ] **PREP-08 — P0 — Owner: gameplay designer.** Publish the new scoring formula. Done when combat/objective awards, retirement, tie ordering and anti-farming rules cover all five modes without the retired deposit bonus. G08.
- [ ] **PREP-09 — P1 — Owner: UI/programming owner.** Define local result/leaderboard data. Done when schema, mode/difficulty/rules identity, names, invalid files, duplicate prevention and debug eligibility are explicit. G09; depends on PREP-08.
- [ ] **PREP-10 — P1 — Owner: UI designer.** Complete input/focus and readability requirements. Done when every panel has entry/exit/input consumption rules, visible blockers and readable safe-area layouts. G10.
- [ ] **PREP-11 — P1 — Owner: UI/gameplay designer.** Adopt or revise the tutorial proposal. Done when final copy, triggers, dismissal, repetition and session-state rules are specified without stacking conflicting modals. G11.
- [ ] **PREP-12 — P1 — Owner: presentation programmer.** Review story playback contracts against the supported cutscene pipeline. Done when intro/ending placement, advance/skip, destination and result ownership are ready for implementation. G12.
- [ ] **PREP-13 — P1 — Owner: audio/UI owner.** Define music/SFX/volume routing. Done when field, hub, boss, pause and exit transitions cannot stack music or leave effects running. G13.
- [ ] **PREP-14 — P0 — Owner: programming owner.** Define high-rank numerical and effect budgets. Done when overflow, spawn/effect limits, reward conservation and performance targets are measurable without silently discarding earned progression. G14.
- [ ] **PREP-15 — P0 — Owner: gameplay designer.** Adopt consistent outcome precedence. Done when Survival/Boss/Campaign specify same-step death versus success and source/reward finalization agrees. Existing proposal: player death takes priority. G15.
- [ ] **PREP-16 — P0 — Owner: producer/team.** Confirm submission scope and resolve the existing eligibility question. Done when the team's recorded decision addresses the inherited-code requirement and deliverable owners are assigned. G16 and tracker Open Question 1; no external message is authorized by this checklist.
- [ ] **PREP-17 — P1 — Owner-deferred — Owner: team.** Choose a final game title. Done when selection is recorded in the overview/tracker and title-card references agree. Suggestions are in [suggested names](../05-suggested-names/README.md); SCRAPBOUND is a recommendation, not a selected title.
- [ ] **PREP-18 — P1 — Owner: story/art owner.** Review final Scavenger name, body plan, biological binding layer and protected orbital core. Done when existing monster silhouettes have a consistent written biological explanation and later production references agree. See [world section 4.1](../01-story/world-and-campaign.md).
- [ ] **PREP-19 — P1 — Owner: story/producer.** Review proposed dates, exact trailer wording, tagline and optional narration. Done when the final narrative copy agrees with the two separate inventions, mutation/generational adaptation and gradual-restoration ending. See [story](../01-story/story-context.md), [text trailer](../01-story/story-trailer-text.md) and [theme](../01-story/narrative-theme.md).
- [ ] **PREP-20 — P1 — Owner: gameplay/story owner.** Owner selected four labels, one wallet, unchanged enemy-tier values and appearance-matched assignment. Verify authored per-variant/debris mapping coverage; keep open for that content review. See [scrap types](../03-economy/scrap-types.md).
- [ ] **PREP-21 — P1 — Owner: teammate implementing the game.** Assemble the later implementation instruction from adopted briefs. Done when dependencies, unresolved content, validation and scope are explicit, using one buildable checkpoint at a time. This list does not authorize starting code now.

- [ ] **PREP-22 — P1 — Owner: owner/gameplay designer.** Names/graph adopted 23 October, with T4/T5 branching and ten finals. Keep open for explicit field-card-versus-cannon acquisition/compatibility review. Done when tree and field-card behavior form a complete adopted contract. Reference: [weapon tree](../07-upgrade-proposals/weapon-tree.md); branch locking is confirmed.
- [ ] **PREP-23 — P1 — Owner: owner/gameplay designer.** Review numeric attribute/shield shop details. Done when the confirmed 25% gain has approved supported attributes, discrete exclusions, source accounting, limits and local draft prices. Reference: [attributes](../07-upgrade-proposals/attributes-and-luck.md).
- [ ] **PREP-24 — P1 — Owner: owner/gameplay designer.** Review Luck source/effect. Done when shop-only versus Legendary card and exact reward/limits/snapshot rules are adopted. Reference: attributes/Luck proposal; no new drop system implemented.
- [ ] **PREP-25 — P1 — Owner: owner/gameplay designer.** Review the automatic roster, persistence categories and grades. Done when entries and acquisition exceptions are adopted; Blink grade/automation already confirmed. Reference: [skills/rarities](../07-upgrade-proposals/automatic-skills-and-rarities.md); weights are PREP-04.
- [ ] **PREP-26 — P1 — Owner: owner/gameplay designer.** Review Blink rescue details. Done when cooldown/floor, protection, candidate safety, no-safe-spot outcome and no-free-refresh rules are approved. Owner intent is confirmed; current numbers are proposals.
- [ ] **PREP-27 — P0 before weapons — Owner: gameplay designer.** Full T1-T5 profile/signature draft delivered 23 October with bounds and analytical DPS comparisons. Keep open for numerical adoption, exact family/card mappings and combined effect/performance limits. Done when these contracts are adopted and validation prerequisites are explicit. Deferred bosses/schedules/layouts stay deferred.
- [x] **PREP-28 — Design adopted 23 October — Owner: gameplay designer.** Tiny/Small/Medium/Large/XL supply 20%/50%/100%/150%/200% of normal capacity, added to min(current shield, normal capacity). Starting prices 100/250/500/700/900 scale proportionally with capacity. Repeat paid purchases, normal-only regeneration, exact replacement previews and atomic payment are documented in game-design.md. Implementation/playtesting remain T07/T10.
- [ ] **PREP-29 — P0 before T07 — Owner: gameplay/level designer.** Finish field return portal data. Selected: random spawn at half energy, Easy/Hard/Impossible counts 3/2/1 across modes, F inside, shield/energy gates, distant exits allowed, one-screen pointer detection, persist until used/run end, visible lock when shield breaks or charge falls below a raised threshold, fresh set after successful return/recharge, and Resume at the used portal with 2 seconds of protection ending on firing. Done when legal placement/fallback, exact detection and Resume protection/input ordering (including auto-fire) are adopted. See [portal brief](../02-gameplay/return-portals.md).

## Gameplay implementation checkpoints

All remain pending in the current tracker. The authoritative acceptance cases and dependencies are in [gameplay sections 13-14](../02-gameplay/gameplay.md). Tick both this list and the root [TODO index](../README.md) only when the checkpoint passes its actual completion criteria.

- [ ] **T01 — P0 — Owner: gameplay programmer.** Add typed mode/difficulty and run-progress/return contracts. Done when accounting, formulas, ownership and resets satisfy the brief.
- [ ] **T02 — P1 — Owner: gameplay programmer.** Centralize enemy rewards, stored random trade/fixed salvage, pickup merging and magnet behavior. Done when eligible paths credit once, both totals are conserved and exclusions/accepted art remain correct. Depends on T01 and the material decision.
- [ ] **T03 — P1 — Owner: gameplay/UI programmer.** Replace timed upgrade triggers with field salvage levels and queued choices. Done when overflow, locked offers, prerequisites and shared descriptions work. Depends on T01/T02 and PREP-04.
- [ ] **T04 — P1 — Owner: gameplay programmer.** Complete automatic/persistent skills, starter shield and Shield Detonation contracts. Done when activation, targeting, cooldowns, break behavior and rank effects pass the brief. Depends on PREP-03/PREP-05/PREP-06.
- [ ] **T05 — P1 — Owner: gameplay/UI programmer.** Implement Start -> difficulty -> safe ship-based hub, stations and portal previews. Done when real flow and input ownership work with measurable geometry. Depends on T01 and PREP-07/PREP-10.
- [ ] **T06 — P1 — Owner: gameplay programmer.** Implement five real mode objectives and campaign source encounters. Done when each enabled portal has its promised schedule/outcome and actual boss content. Depends on T05 and PREP-01/PREP-02/PREP-15.
- [ ] **T07 — P1 — Owner: gameplay/UI programmer.** Implement gated field return portals (F interaction), suspended encounter/resume and paid hull repair; batteries are separate shop purchases. Done when charge/shield gates, preserved world state and atomic repair/cancel behavior pass. Depends on the shield/hub contracts.
- [ ] **T08 — P1 — Owner: gameplay/UI programmer.** Implement the approved mothership weapon tree, quarter-strength numeric attributes, Luck if adopted, eligible whole skill ranks and fixed special stock. Done when rank effects, prices, ownership, stock persistence and atomic transactions pass without free-heal exploits. Depends on T03/T05/T07.
- [ ] **T09 — P1 — Owner: UI programmer.** Integrate HUD, pause/settings, input capture and tutorial. Done when required status and errors are readable and no input leaks into another state. Depends on adopted UI/tutorial/audio requirements.
- [ ] **T10 — P1 — Owner: team.** Verify full gameplay and reset/balance/performance behavior. Done when the later runtime acceptance checklist passes and measured limitations are recorded. Depends on the implemented promised scope; document actual deferred work.

## Project work alongside the gameplay checkpoints

Reference: [remaining numbered/art work](../README.md), [build plan](../../context/build-plan.md) and [progress tracker](../../context/progress-tracker.md). Some umbrella items are partial; preserve their delivered subparts.

- [ ] **PROJECT-01 — P0 — Owner: producer/programmers.** Complete remaining machine/eligibility/provenance foundation checks. Done when original items 01-03 have the missing evidence; retain the existing local build/debug baseline.
- [ ] **PROJECT-02 — P1 — Owner: programmer.** Finish remaining run-context/RNG/reset and collision-owner integration. Done when original items 05-06 are reconciled with the new lifecycle and existing grid/pause work remains verified.
- [ ] **PROJECT-03 — P1 — Owner: programmer.** Finish remaining HUD/player-stat/augment/enemy-metadata integration. Done when the unfinished portions of items 07-10 are addressed through their existing owners without duplicate systems.
- [ ] **PROJECT-04 — P1 — Owner: gameplay/art.** Complete missing enemy content, including the heavy enemy where retained. Done when behavior, stats, accepted art integration and provenance meet the selected scope; no duplicate rebuild of completed low/debris content.
- [ ] **PROJECT-05 — P1 — Owner: presentation programmer/art.** Implement and produce intro/ending. Done when the adopted card/motion sequences and skip routes work with original assets and finalized run results.
- [ ] **PROJECT-06 — P1 — Owner: UI programmer.** Complete local leaderboard/name-entry and credits. Done when actual result records, separate rankings, tools/licenses and AI disclosure are integrated.
- [ ] **PROJECT-07 — P1 — Owner: art/audio.** Finish missing ship/enemy/boss/hub/background/UI/cutscene/audio deliveries. Done when each unfinished A1-A9 sub-delivery has approval, correct format, integration and provenance. Keep completed supplied/generated assets.
- [ ] **PROJECT-08 — P1 — Owner: producer/art.** Produce the separate gameplay demonstration video. Done when the required 3-5 minute export shows functioning features and accurately explains play.
- [ ] **PROJECT-09 — P1 — Owner: producer/art.** Produce the story/game trailer. Done when the required 1-2 minute export has readable original copy, appropriate moving scenes and truthful gameplay claims; saved text alone does not complete this task.
- [ ] **PROJECT-10 — P1 — Owner: producer/team.** Complete synopsis, forms, provenance and AI disclosures. Done when required materials agree with the actual build, team roles and asset sources.
- [ ] **PROJECT-11 — P1 — Owner: programmer/tester.** Freeze, package and validate the release on the intended machine. Done when clean-clone build/package, asset paths, smoke/restart checks and measured capacity pass the agreed release criteria.
- [ ] **PROJECT-12 — P1 — Owner: producer.** Submit and record confirmation. Done when actual required deliverables are submitted and the team records receipt/status; a planned upload is not completion.

## Verification and maintenance attention

- [ ] **REVIEW-07 — P1 — Owner: gameplay designer/testers.** Validate weapon-choice viability after implementation. Done when equal-investment fixed-seed lone-target/crowd/moving-target trials with at least three pilots record actual DPS, time-to-kill, incoming damage and completion, meeting the weapon ledger's acceptance gates. No enabled encounter may require a particular family. Arithmetic alone is insufficient. Depends on PREP-27 and implemented T08; execute as part of T10.

- [ ] **REVIEW-01 — P1 — Owner: context author/team.** Reconcile historical requirements before implementation. Done when affected work uses the current five-mode, field-leveling, paid-service, biological-source design and records conflicts instead of restoring retired cargo/credits/tree/machine-origin rules. Historical logs remain intact.
- [ ] **REVIEW-02 — P1 — Owner-deferred — Owner: tester/gameplay designer.** Playtest the selected economy and pacing. Done when time to first card/return, wallet at hub, repair burden, purchases, shield-related deaths and mode/boss outcomes are measured and tuning changes recorded in the authoritative ledger.
- [ ] **REVIEW-03 — P1 — Owner: tester/programmer.** Validate full reset and suspension across the final feature set. Done when restart/quit/death clears all run state and hub Resume preserves exactly the intended state, including source flags, pickups and timers.
- [ ] **REVIEW-04 — P1 — Owner: tester/programmer.** Validate load, long runs and high ranks. Done when approved frame-time/memory budgets hold and numeric/effect limits preserve rewards and usable play.
- [ ] **REVIEW-05 — P1 — Owner: producer/tester.** Review narrative/science/accessibility consistency. Done when scripts and final footage distinguish fiction, show the biological armor chain, remain readable with sound off and depict actual supported mechanics.
- [ ] **REVIEW-06 — P1 — Owner: each task author.** Before the implementation handoff, review every open item with the team. Done when each prerequisite has an adopted answer, assigned owner or explicit scope deferral; keep ongoing maintenance separate from claiming product completion.

## Verified preparation deliveries

These checked tasks concern documentation only. Evidence and historical implementation baselines are in [completed.md](completed.md).

- [x] **DOC-01 — P1 — Owner: context author.** Organize pending briefs by topic and link shared references.
- [x] **DOC-02 — P1 — Owner: context author.** Document biological waste-eater origin, scrap armor, responsibility theme and source-containment campaign.
- [x] **DOC-03 — P1 — Owner: context author.** Save the text-only trailer and the timed production brief as distinct documents.
- [x] **DOC-04 — P1 — Owner: context author.** Create the suggested-game-names folder with options and meanings; final selection remains PREP-17.
- [x] **DOC-05 — P1 — Owner: context author.** Create this task-list folder, populate attention/idea/history registers and connect its maintenance rules to the required session context.

- [x] **DOC-06 — P1 — Owner: context author.** Write the upgrade review package and record confirmations, deferrals and later review questions. This completes draft documentation, not PREP-22 through PREP-27 approval or implementation.

- [x] **DOC-07 — P1 — Owner: context author.** Configure and verify initial context publication to both authorized repositories on docs/context-preparation; record the initial matching remote hashes and future refresh/push procedure in repository-sync.md. Subsequent publications still require verification.

- [x] **DOC-08 — P1 — Owner: repository maintainer.** Publish the complete current feature baseline to dev in both authorized repositories at the owner's request. Both remote dev hashes verified at dc39d78; Debug build and configured CTest passed. See repository-sync.md and completed.md. Pending gameplay proposals remain unimplemented.

- [x] **DOC-09 — P1 — Owner: context author.** Record accepted weapon tree and full stat/signature draft, analytical comparisons and runtime acceptance limits. Numerical adoption/compatibility/implementation remain PREP-27/REVIEW-07.
