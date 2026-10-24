# Audio direction and routing - 25 October 2026

Written implementation/production handoff, not generated audio or completed playback. Q32 selects **dark electronic / synth** music. Q31 selects calm, serious delivery from the same original English AI narrator across intro/ending/trailer. Q5/Q8 retain Master/Music/SFX sliders and local settings. [Voice contract](../08-review/owner-questionnaire.md#narration-contract), [storyboard](../01-story/story-context.md) and [identity](../01-story/player-identity.md) remain authoritative for copy/voice/name behavior.

## Music production direction

Use restrained dark pads, low synthetic pulses, textured electronic percussion and clear original motifs. The danger comes from tension/rhythm, not constant maximum loudness. Leave space for shooting, damage warnings and the calm narrator. Do not request a real artist/game/film imitation or use commercial track references in prompts. New actual music must have source/tool/prompt/license records in assets/ASSETS.md and the AI usage log.

Minimum runtime set is three shared music assets. Different levels/bosses do not each require a new track, adaptive stems or beat-synchronized combat.

| Delivery | Target resource / runtime file | Direction / uses |
|---|---|---|
| MUS01 | Existing home_music / assets/sounds/home_music.mp3 replacement if needed | Quiet restrained synth, spacious pads, low pulse, a small hopeful motif; menu, name/difficulty panels, inhabited HOPE, map, credits and subdued story bed |
| MUS02 | Existing game_music key; planned canonical assets/sounds/game_music.mp3 | Dark driving synth/percussion, clear rhythm and room for warnings; Swarm, ordinary Chaos and normal Campaign waves |
| MUS03 | Planned boss_music / assets/sounds/boss_music.mp3 | Heavier pulse, tense bass and controlled sharper percussion; all active boss fights, including any living Chaos boss |

Source check: home_music currently maps to home_music.mp3; game_music currently maps to a different inherited MP3, even though a game_music.mp3 file is present. Do not claim that the canonical MUS02 path is already active. When a final replacement is delivered/provenance-checked, update the existing game_music mapping to its canonical path; do not register a competing gameplay key. These source facts do not prove acceptable provenance or selected final sound. Boss music is a new planned asset/key, not registered/produced here. Preserve working prototypes until replacements are supplied and checked. Supply clean loopable runtime MP3 matching the existing loader, plus a lossless editing master when produced. Avoid clipped peaks, leading silence and abrupt loop seams; inspect encoded playback, not only the editing master. A roughly one-minute-or-longer loop is a production preference, not a combat timer.

Intro uses MUS01 as an ominous restrained bed; ending brings its hopeful motif forward without claiming Earth is instantly restored. The trailer may edit MUS01/02/03 into an escalating arrangement with a quiet final resolve; it does not require a separate fourth composition. Final trailer music is mixed into its export and is not a second in-game stream. The gameplay demonstration captures real game audio; editing may balance it but cannot fabricate demonstrated mechanics.

## Narration and sound effects

Keep one saved original English voice profile, calm and serious, with measured diction and restrained emotional weight. Address the player as Cadet/Pilot/you; runtime text alone substitutes the entered name. Record separate clips by storyboard beat so skip/advance can stop the correct clip. Never play two narration clips at once. Deliver dry intelligible voice rather than baking a loud music mix into every clip. Teammate measures the actual speech against the existing 40/24/90-second production targets; adjust line allocation, not rushed playback or automatic sequence extension.

Music follows the Music bus. Narration and all one-shot/UI/world effects follow SFX; no fourth slider. Source-authored sound direction:

| Event family | Direction / playback condition |
|---|---|
| Primary weapon / abilities | Short electronic/mechanical impacts; fire only on actual committed attacks, not every held-input frame |
| Scavenger motion/attacks | Scrap clanks/strained mechanisms with restrained organic texture; supports hidden-body art rather than a human talking monster |
| Shield hit/break/reboot | Distinct impact, clear break and subtle recovery; only actual events, not shop preview/reset/each zero-shield frame |
| Pickups/cards/purchases | Distinct soft confirmation cues; collection/success only, never declined/stale transactions |
| Portal ready/locked/travel | Short readiness/lock/commit cues; ready transition once, lock on an attempted interaction, travel only after committed checks |
| UI | Hover on entry/change and click on accepted action; held hover/click cannot replay each frame |
| Boss tells / player danger | Readable priority cues paired with mandatory visible tells; sound is never the only warning |
| Death/retirement/final clear | Once-only outcome cue after finalization; not repeated by result/save/ending re-entry |

Retain accepted working SFX until actual delivery/provenance review. Existing named files are not automatic license clearance. Use existing bounded sound-pool approach; coalesce simultaneous cosmetic feedback without dropping actual damage, kills, pickups or score. Reserve priority for danger/major tells and UI; avoid unbounded per-enemy looping emitters. No positional-audio engine or new audio library is required. World effects never continue as if the suspended field were still running at the station.

## Ownership, bus gains and update rules

ResourceManager owns loaded samples/streams and unloads them at application shutdown. Application's existing scene/audio integration owns the requested music context, effective gains, current playback cursor and suspended-context cursor. Game/presentation owners report context/events; they must not also start independent copies of the same track. This is a target migration of current Game/menu-owned playback, not an existing AudioManager class or permission to create another singleton.

At most one audible background music stream and one narration clip. The narrator is classified as SFX/Voice even if its implementation uses a pausable streaming resource. Service each active stream once per application frame, including menus and console capture, through a single owner; do not update/play it again from Game or a modal. Paused streams retain their cursor without advancing playback. Audio presentation uses UI/application elapsed time for fades, not the frozen combat clock.

Effective music gain is Master x Music x transition fade x narration duck; SFX/voice is Master x SFX x source envelope. Apply Master once, not both globally and again inside every local category gain. The existing narration duck is 0.35 while voice is audible, with normal music gain restored when it ends/skips; it does not overwrite sliders or stack for repeated clips. Debug mute overrides final output without erasing saved gains. Changing graphics never alters audio timing or gameplay RNG.

For a different music context, fade the old track to silence over an author-default 0.35 UI seconds, stop it, then start/fade the new context over 0.35 UI seconds. No overlapping crossfade is required; this keeps the one-music invariant simple. A new higher-priority request replaces the pending destination without starting a stale intermediate track. Same-context requests do not restart the track. Stop immediately on application shutdown; no fade requires the process to stay alive. Envelope constants belong in Config during implementation.

## State/transition matrix

| State / transition | Music | Voice / world effects |
|---|---|---|
| Main menu, difficulty/name panels | MUS01; changing panels does not restart | UI effects only; prelaunch input cannot fire a world sound |
| Hub, services, shop, hub map | MUS01; no restart while staying in safe context | UI/service cues; field emitters stop and their tails are discarded |
| Ordinary combat | MUS02 | Actual committed world events |
| Boss mode / Campaign boss / any living Chaos boss | MUS03 | Owned tells/attacks; multiple bosses still use one background track |
| Last Chaos boss dies, ordinary fighting continues | Transition MUS03 -> MUS02 after finalized boss-count update | No extra clear/reward merely for audio transition |
| Field card selection | Keep the current music | Suppress new world events; card/UI cues remain; combat time stays frozen |
| Safe Campaign cleared-wave choice / level-map checkpoint | Pause current music cursor; no automatic hub track | UI only; clear cues once; next choice resumes/selects the proper context |
| Ordinary field return -> station | Save field/boss music cursor, then MUS01 | Stop world sounds; no new simulated attacks/droid rebuild sounds |
| Resume same suspended encounter | Restore saved context/cursor, then fade in | Do not replay abandoned world sound tails; preserve all combat cooldowns |
| Manual pause | Pause current music/voice cursor | Stop/discard world one-shots; allow pause UI cues; Resume restores origin |
| Focus loss | Pause all music/voice; suppress other audio | No queued world/UI bursts on refocus; explicit Resume required |
| Debug console capture | Current music continues unless actual focus/manual pause | Combat is frozen; no new world SFX; console/UI and mute follow normal buses |
| Intro / ending | MUS01 bed, ducked during voice | One owned narration clip plus scene cues; pause/skip freezes/stops correct clip |
| Defeat / mutual destruction / retirement / ordinary results | Fade music to silence; results do not start a combat loop | Outcome cue once; stop world/old voice before results; no autosave cue on failed save |
| Valid final Campaign completion -> ending | Finalize result, then MUS01 story bed | Same narrator; no posthumous gameplay sound/loot/advance |
| Credits / return to main menu | MUS01 | Stop any old presentation voice; normal UI cues |
| Quit / application exit | Stop every owned stream; clear pending fades/requests | Stop active sounds, discard queues, then unload through ResourceManager |

Audibility priority is application exit, focus/manual pause, then terminal/required presentation, committed hub/field context and optional cosmetic cues. Terminal result bookkeeping still completes while audio is focus-paused, but cannot make an unfocused application speak/play again. A paused source remains paused when another context is selected; only explicit Resume releases that gate. Focus return never auto-resumes or plays buffered sounds. Ending skip stops voice and ducking before destination UI receives fresh input. Scene exit cannot leave an old owner's stream alive.

## Missing content and later acceptance

If a new boss track is not delivered, use the field track as an explicitly temporary audio fallback; it does not replace missing boss gameplay/content. Missing home/field/voice resources produce an event warning and silence/readable story text, rather than throwing from an unchecked missing key or repeatedly trying every frame. Such fallback is not evidence that required narration/music production is complete. Never substitute an unlicensed/random external recording.

1. Test each matrix row, repeated same-context events, rapid boss-clear/return/launch and pause during an in-flight fade; at most one music/voice instance remains.
2. Verify all three sliders, zero gains, ducking, debug mute/unmute and persisted settings without resetting music/cooldowns or double-applying Master.
3. Freeze voice/music on focus loss; refocus needs explicit Resume. Skip/exit leaves no stale clip, ducking, effects or delayed restart.
4. Confirm audio silence/Low graphics still leave every required tell, blocker and story fact visible.
5. Verify encoded loop boundaries, level consistency and voice intelligibility at the actual game window/workload. Actual files, licenses/tool logs and exports must exist before production completion is marked.

This completes PREP-13 written routing/production specification. Audio delivery/integration and real playback testing remain PROJECT-07/T09/T10 and media-production work.
