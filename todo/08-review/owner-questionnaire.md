# Owner questionnaire - 24 October 2026

Ask one question at a time. Skip settled decisions. Owner explicitly delegated the remaining Campaign details and requested no more Campaign questions. Preserve that delegation; only new owner instructions change it.

| Question | Answer / status | Consequence |
|---|---|---|
| Q1: Other unlocked, unfinished Campaign levels remain available? | **Yes - owner confirmed** | Remove the author's exclusive branch lock. After a level clear, other unlocked, unfinished nodes remain selectable. |
| Q2: Must both middle branches be cleared before the final level? | **Delegated; no more Campaign questions** | Author default: either middle level unlocks the final. The other middle level stays available until final Campaign completion. |
| Q3: Swarm/Chaos leaderboard priority? | **Score, also add survival time - owner confirmed** | Rank by score; show active combat survival time alongside each entry. Exact point weights remain design work. |
| Q4: Pause when game loses focus? | **Yes; require Resume on return - owner confirmed** | Focus regain never resumes combat automatically. Preserve originating state and pending modal/transaction data. |
| Q5: Audio controls? | **Master, Music and Sound Effects - owner confirmed** | Three shared sliders in main-menu and pause Settings; resetRun does not clear preferences. |
| Q6: Target computer? | **Hardware not supplied; owner requested graphics levels instead** | Add Low/Medium/High graphics presets. Hardware/performance validation remains open; presets do not prove minimum specifications. |
| Q7: Default graphics preset? | **Medium - owner confirmed** | Default first launch to Medium; Low/High remain available in Settings. |
| Q8: Remember audio/graphics after closing? | **Yes, save locally - owner confirmed** | Persist presentation settings only; no gameplay progression/save game. |
| Q9: Team/member Credits names? | **Leave placeholders - owner confirmed** | Clearly mark unfilled entries; never invent contributors. |
| Q10: Weapons Payload scope? | **Primary weapon only - owner confirmed** | Automatic abilities retain their own damage/rank upgrades; no inherited Payload boost. |
| Q11: Spoken beta intro/ending narration? | **Include - owner confirmed** | Narration is now required alongside readable story text. |
| Q12: Narration source? | **Original AI-generated narrator - owner confirmed** | Original voice direction, provenance and AI disclosure; no production audio is delivered by this decision. |
| Q13: Narration language? | **English - owner confirmed** | Use English scripts/voice; no bilingual/localization scope is implied. |
| Q14: Same narrator in trailer? | **Yes, same narrator - owner confirmed** | Intro, ending and trailer share one original English AI narrator/voice profile. |
| Q15: Primary weapon auto-fire on a fresh run? | **Start OFF - owner confirmed** | Hold Shoot/LMB or press E to enable auto-fire; mouse aiming stays available. |
| Q16: Submit Swarm/Chaos score after voluntary station retirement? | **Yes - owner confirmed** | Record score and active survival time with Retired outcome; normal ranked eligibility and duplicate prevention still apply. |

## Primary-fire default and retirement

Every fresh run/restart starts primary auto-fire OFF. Holding LMB/Shoot fires while aiming; E toggles auto-fire. This preference is run-local, not part of saved audio/graphics settings. Pause, focus pause, cards and same-expedition station visits preserve the chosen toggle, while suppressing actual combat fire. Ordinary re-entry protection temporarily delays automatic shots without changing that toggle; deliberate Shoot ends protection under the existing rule. Toggling E or buying upgrades cannot refresh firing cooldowns. Existing Player source initializes autoShoot=false and already uses LMB/E; full hub/protection integration remains pending.

Swarm/Chaos station UI provides **Retire Run**, with score/time preview and an explicit confirmation; Cancel preserves the suspended expedition. Confirming freezes one final result with **Retired**, actual earned score and active-combat survival time. Station/pause/card time never increases survival. Permit name entry/leaderboard submission subject to the same debug/rules/difficulty eligibility as normal results. Score remains the primary ranking; show time alongside it. No defeat/victory relabeling, retirement bonus, new boss-clear credit or credit for uncollected suspended loot.

Finalization stops scoring/damage/collection and clears the run only after preserving the result record. Cleanup yields no rewards; repeated callbacks/save/return-to-results cannot submit twice. The player must reach the station through an already valid return policy; this does not introduce free field retirement travel. Quit/abandon remains a separate confirmed action and cannot masquerade as a station retirement to keep a suspended run. Exact point weights/result implementation remain PREP-08/09 and PROJECT-06 work.

## Additional owner steering - backgrounds and wave clears

Owner assigns background production to the implementing teammate. Provide written scene/style/format instructions only; generate or edit no background images here. [Background brief](../09-art/background-brief.md) specifies shared tiles, menu/hub/map/level identities, examples, export compatibility and delivery checks. Its completion is not asset delivery.

Owner changed cleared-wave station visits from compulsory to optional. Campaign clear offers Enter Station or Next Wave/Stage Boss. Cleared-wave station entry bypasses shield/energy with no payment/healing; services stay paid. Preserve rewards/build and pending encounter once. [Checkpoint contract](../02-gameplay/campaign-stages.md) defines map/cancel/final-clear cases; ordinary mid-fight/Boss rules stay distinct. This steering was separate from Q14, subsequently answered Yes for the same narrator.

## Delegated Campaign correction

Four beta levels remain authored: C01 unlocks C02/C03; completion of either unlocks C04. Completing C02 does not block C03, and vice versa. A player may complete three levels via one middle branch or four by completing both before C04. A level already in progress must finish or be abandoned under the existing fresh-run policy before switching; ordinary retreat resumes it. Cleared levels are not replayed for additional rewards. Final C04 clear ends the beta Campaign using the existing ending/result contract.

The shortest authored traversal has 12 normal waves plus three bosses (15 encounters). Visiting both middle levels has 15 normal waves plus four bosses (19 encounters). Optional progression may strengthen the player; encounter tuning must account for both incoming builds without inventing a permanent unlock or a repeat-farming loop. Final-level preview explains that its completion ends the Campaign, allowing the player to finish the other optional level first.

## Focus-loss behavior

Focus loss blocks simulation and gameplay input before another combat step. Running field/hub free flight enters pause with the exact source state retained. Existing pause/selection/shop/map/preview/repair/quit panels preserve their data under a focus-pause gate; do not dismiss or reroll them. Show an explicit Resume action after focus returns, then restore the originating state/panel. Repeated focus events cannot stack pause layers, commit a transaction, advance a timer or refresh protection.

The click used to refocus cannot also fire, choose a card, buy, launch or resume. Resume requires a new deliberate press after focus is restored. Opening/closing frames consume their input. Loading and noninteractive menu rendering may continue; no hidden gameplay may advance. Presentation clocks freeze while focus-paused. Existing mandatory cards remain mandatory after Resume.

## Audio routing

Master affects both music and sound effects; category sliders multiply their corresponding gain. Use master once in the output chain: effective music gain is Master x Music; effective effect gain is Master x SFX. Keep independent slider values; setting Master to zero or using debug mute does not erase category preferences. UI clicks follow SFX, music streams follow Music, and one-shot gameplay audio cannot bypass Master.

All three controls share preferences across menu/pause/hub and survive restart/death/new run. Owner confirmed local persistence across application launches; use the settings-file contract below. Sliders apply live without resetting a run or restarting the current track. Paused gameplay cannot emit new combat sounds; existing short sounds may finish, and UI sounds remain available at configured gain. Narration follows the SFX/Voice gain; no fourth slider is required.

## Graphics scope

Low/Medium/High control cosmetic presentation and shader passes. Combat enemy counts, attack events, skill armies, hitboxes, timers, loot, targeting and RNG streams remain identical. Cosmetic reductions cannot discard earned damage, companions or rewards. Keep logical canvas, camera framing, mouse mapping, hit telegraphs, boss bars and required UI unchanged. No new rendering library is required.

Default to **Medium** on first launch or invalid/missing preference, then load the saved choice. Preset presentation is authored in UI/architecture references; actual performance must be measured. Settings do not change ranked eligibility/rules unless gameplay changes.

## Local preferences contract

Use a small versioned settings.cfg beside the executable, resolved through the existing application asset-directory convention. Store Master, Music, SFX/Voice and graphics preset only. Application loads once and owns preferences across scenes. Future implementation puts filename/defaults in Config, slider geometry in Theme and reuses existing resource/audio ownership.

```text
version=1
master=1.0
music=1.0
sfx=1.0
graphics=medium
```

These are author-selected defaults: full category gains and Medium quality. Gains must be finite and clamped to 0..1; unknown graphics values use Medium. Missing fields use their defaults. Ignore unknown keys; last valid duplicate wins. Missing/malformed/unreadable files cannot prevent launch. Unknown schema version uses defaults without silently rewriting that file during load. Log problems once as events.

Preview slider changes live. Persist on slider release, confirmed preset change or Settings close; never write every frame while dragging. Write a temporary sibling then atomically replace the completed file. If permissions/disk errors prevent saving, keep working session values, show a short Settings error and keep the game usable. Do not clear user preferences on resetRun or write run state, seed, scrap, levels, unlocks or leaderboard records into this file.

Verify close/reopen retention, missing/malformed files, nonfinite/out-of-range gains, unknown schema/preset, failed writes, mute restoration, graphics changes at a safe render boundary and exact originating pause/panel restoration. Saving preferences does not authorize mid-run save games.

## Narration contract

The beta intro, ending and trailer require the **same original AI-generated English narrator**, owner confirmed. Preserve readable story cards and meaningful motion. Provider/voice profile/files remain production work; no audio/license review/disclosure completion is claimed. Record actual tool/model, prompt, source/output paths, edits and provenance in assets/ASSETS.md and the AI Usage Log during production.

Use one consistent original voice direction, without imitating a named real person or referencing brands/games/movies in generation prompts. Spoken lines follow the approved card text and add no essential facts unavailable to a sound-off viewer. Read HOPE as the word Hope. Narration may finish over its associated motion beat after the story card clears; stop it before an unrelated beat. Measure actual clip duration rather than speeding the voice to fit a guessed interval.

Keep the existing 40-second intro and 24-second ending as production targets, adjusting wording/beat allocation within those totals as needed. Skip/advance stops the active voice once, prevents overlap and consumes transition input. Pause/focus loss freezes presentation/voice; explicit Resume continues it. No old voice may continue over destination menus/results. Intro/ending audio cannot mutate run state or duplicate results.

Voice follows Master x SFX/Voice. Music follows Master x Music, with author-selected 0.35 duck during audible narration and normal gain afterward. Ducking never overwrites sliders. Mix validation/clip production remain PROJECT-05/07/09 work. Trailer voice is confirmed: reuse the same saved original voice profile and pronunciation/delivery direction as intro/ending. Avoid per-scene random voice selection; inspect all clips together for consistency. The 90-second trailer target includes narration; voice must fit associated text/footage beats without adding uncaptioned essential facts or extending the export automatically.

## Still to ask or author

Continue non-Campaign questions only when an answer is needed. Hardware facts, recording/submission ownership and official cutoff remain missing. Team credit placeholders are owner-approved. Author delegated spawn/targeting/compatibility/scoring details instead of asking for every tuning value. No external contact/submission is authorized by this questionnaire.
