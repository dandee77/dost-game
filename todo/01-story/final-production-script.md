# Beta production copy and cutscene pipeline

25 October2026. Adopted written beta copy under the owner's request to complete context. PREP-19 wording and PREP-12 implementation-facing playback design are complete here; owner review, actual voice/art/exports/playback remain separate. Use [storyboard](story-context.md) for shot detail, [background](../09-art/background-brief.md)/[creature](../09-art/creature-direction.md) briefs for teammate production and [audio](../09-art/audio-direction.md) for shared natural, calm/serious English AI voice. No assets/audio/video are generated in this task.

## Final intro —40 seconds

Each8-second beat starts with its large card for3 seconds, then clears the card for5 seconds of motion. Voice spans the associated whole beat, within its8-second window. Read years as twenty-seven eighteen, twenty-seven twenty-three, twenty-seven thirty-two and twenty-seven thirty-three. HOPE is pronounced like the ordinary word hope, not four separately spoken letters. Cadet names are text only. Use complete phrase captions over motion and card deduplication rules; final cue offsets are derived from actual voice recordings, not assumed equal to these planning windows.

| ID / window | Large story card | Final spoken line | Motion instruction |
|---|---|---|---|
| I01 /0–8 | We asked life to clean up after us. | We asked life to clean up after us. Scavengers consumed our waste. | Useful organisms process selected refuse, waste keeps arriving; protected orbital pod establishes life support. Cut to separate atmospheric program labeled2718 |
| I02 /8–16 | Five years later, our treatment changed them. | Five years later, our treatment changed them. It was meant for the sky. | Show release labeled2723; exposed organism binds plates/cables to itself and attacks. Contaminated cargo reaches orbital equipment; no cloud crosses vacuum |
| I03 /16–24 | By 2732, an estimated 1% of humanity remained. | By 2732, an estimated one in a hundred people remained. Survivors gathered in orbit. | Abandoned surface, evacuation and patched warm-window stations; diverse small scrap-shell descendants imply adaptation across years |
| I04 /24–32 | H.O.P.E. became our home. You became its cadet. | H.O.P.E. became our home. You became its cadet. In 2733, your mission begins. | Inhabited mothership, recognizable player ship leaves berth, fights a small threat and collects salvage |
| I05 /32–40 | Silence the sources. Give Earth another chance. | Silence the sources. Give Earth another chance. Open a route for recovery teams. | Nest emits hostiles, cadet approaches; survey craft waits by HOPE, damaged Earth below. Transition to Main Menu |

Preserve the exact wording/qualifiers. No absolute population is invented, and HOPE is one refuge. Intro shows life engineered before the separate atmospheric program, an unintended effect, subsequent generations, collapse and the 2733 cadet role. The harmful mechanism remains fictional, not a real environmental/scientific claim.

## Final ending —24 seconds

Same3-second card/5-second motion pairing, three8-second beats. Trigger only after committed final Campaign objectives. Generic survivor language works even if the player's same-step final sacrifice ended the run; do not show that specific ship returning alive or claim revival.

| ID / window | Large story card | Final spoken line | Motion instruction |
|---|---|---|---|
| E01 /0–8 | The source fell. The damage remained. | The source fell. The damage remained. The creatures no longer controlled this route. | Guardian falls, dispersal equipment stops, nest no longer releases threats; damaged landscape/wreckage remain |
| E02 /8–16 | For the first time, we could hold the route. | For the first time, we could hold the route. Recovery teams could begin their work. | Survey and containment craft leave HOPE through the cleared corridor toward a prepared landing zone |
| E03 /16–24 | We survived the consequences. Now we must change. | We survived the consequences. Now we must change. A future is something we maintain. | Remote cleanup equipment seals contaminated wreckage, a small secured habitat lights up, damaged Earth/colony composition; then frozen result |

No universal cure, magic seed/tree, instant green planet or boss death making every Scavenger disappear. No new ground-play or cleanup-device mechanic is promised. Completion is a foothold for continued recovery; responsibility and cooperation support the hopeful ending.

## Final trailer —90 seconds

Six15-second beats, each3-second card then12-second motion, except final beat has8-second motion before the4-second title hold. Exact spans are0–15,15–30,30–45,45–60,60–75,75–86, then86–90 title. Use actual playable footage for mechanics and separate cinematic layers for lore. Do not present a mocked panel as a functioning mechanic. Same saved original voice profile as intro/ending; music dark electronic/synth. No gameplay-demo substitute: the separate demonstration must show the real build.

| ID / window | Card at window start | Final spoken line | Motion / production emphasis |
|---|---|---|---|
| T01 /0–15 | We kept the habits. We postponed the consequences. | We kept the habits. We postponed the consequences. Scavengers consumed our waste, on Earth and in protected stations. We kept making more. | Existing useful organisms, growing waste, separate sky program2718 through deployment2723 |
| T02 /15–30 | 2723. The treatment changed more than the sky. | In 2723, the treatment changed more than the sky. The Scavengers changed. What they could digest fed them. What remained became their shells. | Mutation, binding nonliving plates/cables, later adapted descendants; contaminated cargo carries organisms/residues to orbital pods, then evacuation |
| T03 /30–45 | An estimated 1% remained. H.O.P.E. became our refuge. | By 2732, an estimated one in a hundred people remained. The survivors built refuges in orbit. Now, in 2733, you are a cadet of H.O.P.E. | Reused inhabited stations, mothership, actual ship flight/shooting/collected salvage |
| T04 /45–60 | Recover what we need. Return when you can. | Recover what we need. Return when you can. Choose upgrades from recovered salvage, and reach an exit while your shield and return charge allow it. | Actual threshold/card choice/effect, then valid ordinary return with positive online shield and>=500 energy |
| T05 /60–75 | Repair. Rebuild. Cut through the wreckage. | Repair. Rebuild. Cut through the wreckage. Spend recovered scrap on repairs and stronger equipment, then choose your next mission from H.O.P.E. | Actual paid repair/purchase and mission preview/launch, with readable before/after wallet; do not advertise free recovery |
| T06 /75–86 | Silence the sources. Give Earth another chance. | Silence the sources. Give Earth another chance. Open the route for those who will begin the cleanup. | Actual source-boss tell/evasion/retaliation; hopeful survey-craft/colony/Earth image, no full ending spoiler |
| Title /86–90 | SCRAPBOUND: Last Hope | No additional speech | Hold title readable4 seconds; approved team text only, otherwise omit rather than invent credits/competition endorsement |

The untimed literary version in story-trailer-text.md is retained as a synopsis/reference, not an additional narration track or permission to overrun90 seconds. The table above is the final timed production script. Keep the selected thematic tagline for promotional material without squeezing another paragraph onto the title hold.

## Supported runtime pipeline —source inspection

Current source has Scene, Application, LoadingScreen, MainMenu and Game. Scene supplies update/draw/onSwitch/onExit. Application registers only LoadingScreen/MainMenu/Game; LoadingScreen currently returns MainMenu after final texture upload. Cutscene/IntroCutscene/EndingCutscene exist only as planned registry entries, with NO source files. There is no supported runtime video-player/MP4-decoder pipeline to reuse. Earlier instructions to use an existing cutscene base are corrected: implement the planned base first, do not assume it is compiled.

Use the existing Raylib draw/texture/Animation/audio ownership and logical render canvas. Teammate supplies PNG layers or horizontal sprite sheets with documented geometry; animate transforms/layer movement using normalized beat time and existing sprite animation. A camera pan alone may establish a shot, but required gathering/launch/shutdown actions need moving layers/frames. No new video library or runtime web/video dependency. Trailer is edited/exported externally by the teammate, separate from the executable's layered cutscenes.

Future Cutscene derives Scene and owns sequence/beat ID, elapsed presentation time, layer animation state, current voice/cue and completion guard. IntroCutscene/EndingCutscene derive Cutscene; one set of inherited logic, no duplicated audio/timer implementations. Replace the old registry typewriter/7-slide sketch with5 intro pairs and3 ending pairs. Register Intro/Ending in Application only after resources/scene entries exist. Unique sequence-specific Animator keys cannot collide with world entries; update presentation animations once/frame and do not call world Animator Update a second time. Use ResourceManager texture references and actual missing-resource status, not temporary Texture2D references.

## Destinations, result ownership and controls

| Transition | Required target behavior |
|---|---|
| Loading complete | Finalize all pending GPU uploads on main thread, then Intro if not seen this application session; no run created |
| Intro finish/Skip | Mark session intro seen; stop voice/cues/owned effects once; MainMenu. Never replay on restart/Menu return |
| Valid final Campaign clear | Game settles objectives/earned rewards and terminal ordering, freezes one immutable RunResult in planned RunContext, then retires live world and enters Ending |
| Ending finish/Skip | Reveal that SAME frozen result panel inside the Ending scene's presentation state, with no return to Game merely to show results |
| Ending result actions | Reuse existing GameOverOverlay/result UI boundary extended for immutable record/actions; save/Retry idempotent. Menu->MainMenu, Restart->fresh Game entry with captured identity/mode/difficulty |
| Nonfinal/other-mode run end | Existing Game-owned result state; no ending scene or source-victory cinematic |
| Invalid/missing frozen result | Diagnostic with Menu action; no invented score, replayed reward or automatic fresh-run launch |

This avoids Game::onSwitch resetting a run just to show a result. Cutscene never owns another score ledger or references destroyed enemies. GameOverOverlay/result presentation reads frozen data only; one scene draws/handles it at a time. Actual leaderboard submission uses the same local record ID regardless of cinematic skip/re-entry. Retain results until a deliberate fresh-run/Menu action; final presentation cannot award, heal, collect or advance active time.

Automatic timeline uses presentation delta; combat remains inactive. Enter/Space/LMB fresh activation advances exactly one beat to the next pair boundary, stopping current voice/caption and discarding the rest of that beat; Esc/Skip skips whole sequence to its destination once. There is no typewriter-first-click state. Held input, double-click from previous scene and a Skip click cannot activate Menu/Restart/Save. Focus loss creates explicit Resume gate, freezes clock/cues/layers/voice; focus regain alone resumes nothing. Window close abandons presentation normally without a second result/score submission.

Caption complete spoken wording with phrase-level cues tied to actual clip offsets. Suppress duplicate compact text only while a matching full card itself displays that exact line; once speech carries into footage, show compact captions. Always show captions, including mute/missing voice. Voice absence uses planned beat clock/cards/cues and a diagnostic; it is a fallback, not delivered narration. Missing image uses readable card/subdued backdrop and a diagnostic, not crash. No audio busy-wait or duration-dependent game simulation. If recorded voice cannot fit, re-record/edit within the stated beat budget; changing duration requires updating this contract, not silently desynchronizing cues.

## Production handoff and acceptance

Teammate delivers layer/sheet assets with file/key/geometry/provenance, 14 voice clips (5 intro+3 ending+6 trailer; title is silent), and phrase-cue sheets per clip with exact start/end, plus the separate 90-second trailer/export and gameplay demonstration. Multiple phrases may share one beat clip. Record actual tools/voice profile/prompts/licenses/edits in assets/ASSETS.md and Form03 log when produced; writing these instructions does not populate provenance.

Validate40/24/90 total spans, all14 voiced beats and silent title, two inventions and2718/2723/2732/2733 chronology, survivor estimate qualifier, hidden organism/scrap-shell continuity and gradual recovery. Exercise every advance/Skip/natural end, focus/mute/missing-resource path, final same-step death, frozen-result save failure/retry and Restart/Menu. Confirm world/RNG/active combat time never advances behind story or results. Actual recording/readability/timing and executable paths remain PROJECT-05/07/08/09/T09/T10 work.
