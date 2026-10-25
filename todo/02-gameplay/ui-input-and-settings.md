# Beta panel input, visual comfort and settings

25 October2026. Written PREP-10 contract. Q46 confirms a visual-only critical-hull warning, optional in Settings, with a soft red gradient from the screen sides; owner also requests adjustable screen shake. Exact styling/defaults below are delegated. This is context, not implemented controls/effects. UI rules own presentation; game-design.md adopts the25%/30% warning thresholds as feedback values only.

## One input owner

Route each frame in this order: application focus gate; debug console capture (when enabled); top confirmation/error modal; Settings; Pause; current required card/map/shop/preview/repair/checkpoint/result/story panel; free hub/field flight. A higher owner consumes the event before any lower owner sees it. Focus detection occurs before Game simulation; refocusing never auto-resumes. Panels use logical3840x2160 canvas coordinates and the existing mapped mouse, excluding letterbox bars. Maintain the press origin so dragging into a button does not activate it.

Activation is one LMB release on the same enabled control where its press began, or one fresh Enter/Space on the keyboard-focused enabled control. Tab/Shift+Tab cycle controls in visual order; arrows change selection/list/slider as appropriate. F is only contextual interaction, E only authorized flight auto-fire. Do not make menu Space invoke a combat shield/build ability. Require all transition-triggering keys/buttons released before accepting their next action; keyboard-repeat cannot buy/launch/pick twice. Right mouse has no implicit back/shot behavior in beta. Gamepad/remapping/touch are out of scope unless separately requested.

Esc closes only the top layer, except a mandatory card/clear checkpoint/story where its specified action applies. No action through a dimmed panel. Disabling a button keeps a readable reason and keyboard access to its tooltip; activation makes no transaction. Every commit revalidates authoritative state/cost/eligibility; presentation caches are not trusted. One transaction ID makes retries/double input idempotent.

## Complete state and panel matrix

| Owner / panel | Entry and initial focus | Confirm / Back | Simulation / preserved data |
|---|---|---|---|
| Loading | Application launch; no selectable fight | No skip until resource readiness; close window uses application quit | No run, no input to future scene |
| Intro / Ending | Scene sequence, Skip initially focused only after transition keys release | Enter/Space/LMB advances one beat; Esc/Skip skips whole sequence; destination once | Presentation clock only; focus pause freezes exact beat/voice/cue; ending result immutable |
| Main menu | Intro end/skip or confirmed run exit; Start focus | Start->difficulty; Settings/Credits/Leaderboard route to own panel; Quit confirms | No live run simulation; identity session draft retained |
| Difficulty | Start; current/default difficulty selected | Continue->name; Esc Back->menu | Preview changes no run/RNG/currency |
| Cadet name | After difficulty; text field focus | Validate3..12 normalized characters then Continue->fresh hub; Esc->difficulty keeps draft | Consume character/Enter input before starting run; identity captured once |
| Hub flight | Fresh arrival or successful return; no panel focus | F inside nearest service/gate ring opens panel; Esc pauses | Hub ship moves; suspended field simulation/RNG frozen |
| Mode preview | F gate; objective and Launch focus | Launch same run if permitted, or abandon confirmation for another mode; Esc->hub | No spawn/stock reroll until committed launch |
| Campaign map | Campaign gate or post-level checkpoint; current/first available node | Node selects details; Launch is separate confirmation; Esc->recorded hub/checkpoint origin | Locked/cleared preview only; pending unfinished stage cannot be bypassed |
| Workshop tabs | F workshop; current Weapon tab | Tab buttons select Weapon/Attributes/Owned Skills/Special Offers/Batteries; Esc->hub | One wallet/build; no field time. Changing tab never buys |
| Purchase quote | Buy from any workshop row | Confirm commits once; Cancel/Esc returns same row/scroll | Preview exact before/after/price/locks; stale quote blocked with reason |
| Repair berth | F berth; Full Repair focus if useful | Quote Full or Affordable; Confirm->3-second service; Esc before commit cancels | Field frozen; paid service timeline only; no free component refill |
| Repair active | Accepted quote and reserved transaction | No launch/second purchase; pause/settings/focus allowed; no ordinary Cancel refund | Complete debit+heal atomically at service completion; source state preserved while paused. Confirmed run abandonment rolls back reserved quote without healing |
| Field flight | Valid launch/Resume | WASD/aim/Shoot/E; F inside exit; Esc/P/MENU->Pause | Sole ordinary combat owner; no fire behind any panel |
| Mandatory cards | Earned level after combat event settlement; first valid card focus | Pick one; Esc opens Pause and returns to SAME offer; no Skip | Freeze combat, preserve RNG/panel/queued choices; next offer uses applied build |
| Wave/level checkpoint | Required hostiles resolved, loot/cards finalized once | Enter Station or Next Wave/Stage Boss/Select Next Level; Esc->Pause | Freeze combat; no auto countdown, heal or repeated rewards |
| Boss clear | Valid living clear; visible unrestricted exit | Fly to exit, fresh F->hub; Esc->Pause | Safe arena travel, no next boss until later launch; earned loot finalized once |
| Pause | Esc/P/MENU from authorized free flight; Resume focus | Resume button or fresh Esc/P restores exact source; Settings nested; Quit asks confirmation | Freeze field/hub/repair/story clock as appropriate; no reset/reroll |
| Focus pause | Lose focus from any active state | After return require fresh explicit Resume; Esc cannot secretly resume | Preserve all layers/transaction IDs/offers/scroll/cues; consume refocus click |
| Settings | Menu or Pause; Master slider focus | Preview changes; Back/Esc persists then restores exact origin | No run reset. Failure to save shows message and retains session values |
| Abandon / Quit confirm | Explicit exit/new-mode action; Cancel focus | Confirm terminates/resets only intended run; Cancel/Esc restores origin | No transaction debit/reward/launch on Cancel; no hidden retirement score |
| Retire confirm | Station Swarm/Chaos/Boss; Cancel focus | Confirm one Retired result; Cancel/Esc restores suspended/pending encounter | No uncollected field loot credit or pending boss ordinal advance |
| Results | One frozen terminal record; submission action focus if eligible | Save/Retry idempotent; Restart keeps identity/mode/difficulty but creates fresh run; Menu confirms exit if needed | No live combat/loot/score changes; entered Cadet name cannot be renamed here |
| Leaderboard | Menu/result action; current mode/difficulty board focus | Board selectors, Back/Esc->recorded origin | Local historical data only; no gameplay unlock |
| Credits | Menu action; Back focus | Back/Esc->menu | Clearly marked contributor placeholders; no fabricated names |
| Simulation fault | Unsafe prospective numerical/allocation state; Retry focus | Retry only if safe; End Run confirms unranked diagnostic result | Freeze before affected mutation; no random rerolls or silent truncation |
| Long-stall performance pause | Wall-frame delta>0.25 seconds before combat advance; Continue focus | Fresh explicit Continue; Quit confirms abandonment. Focus loss adds its usual gate | Freeze previous committed state, discard excess wall time; no added survival time, catch-up attack storm or protection refresh |

On focus loss while Settings/confirm/repair/card is open, place one focus gate over that stack; do not create nested repeated Pause layers. Resume removes the focus gate and returns to that exact still-paused panel, rather than launching combat. Repeated focus changes create no repeated save/transaction/voice start. Terminal outcomes discovered in an authorized combat step settle before newly requested nonterminal panels. Lost focus before that step prevents it entirely.

P preserves the existing source pause shortcut for hub/field free flight and ordinary manual Pause. Under Settings/cards/map/confirmation/story/focus/stall gates it does not dismiss a panel, advance story or bypass explicit Resume/Continue. Esc still follows the top-panel matrix rather than acting as a global unpause. MENU is the screen button for the same manual-pause action. Opening/closing manual Pause consumes the trigger; repeated key state cannot both close Pause and fire/launch. Focus/stall Continue requires its explicit focused action, not a held P/Esc from before the interruption.

## Readable layouts and keyboard behavior

All primary panels fit rectangle(300,250,3240,1600) canvas pixels, within text-safe area(200..3640,150..2010). Body/control font48 minimum (16 nominal display pixels at1280x720), line pitch64, control hit height96; titles96 and labels64. Important HUD remains inside220..3620,150..2000. No essential content in cropped corners. Use high contrast backing, text/shape status in addition to color and visible keyboard focus ring. Do not use rapid flashes, forced camera zoom, tiny icon-only prices or hover-only essential text.

Scrollable lists keep header/wallet/footer fixed. Wheel affects only the hovered scroll panel; Up/Down/PageUp/PageDown move its keyboard selection and reveal focused row. Scrolling the boss list never changes primary aim/fire; free-field scrolling only scrolls a deliberately opened paused boss-detail panel. Required living-boss identities remain accessible. Long descriptions wrap or open a detail pane; do not shrink below body size. Test longest26 weapon names, high rank/price/score values, no offers, owned/sold stock, insufficient funds and save errors. Format large presentation numbers compactly with full value in focused details; quotes use exact amounts and never hide a purchase's true cost.

Settings has three audio sliders (Master,Music,SFX/Voice), Graphics selector Low/Medium/High, Low Hull Warning On/Off and Screen Shake Off/Low/Medium/High. Initial settings: gains1,Graphics Medium,Low Hull Warning On,Screen Shake Low. Slider keyboard step0.05 (clamp0..1), Home/End min/max; presets/options change on one fresh directional press and commit on release/confirm. Six rows at y550/680/810/960/1100/1240, labels x500 and controls x1900..3200; Back rowy1670. Theme owns dimensions; no new controls under cropped edge.

## Low-hull red edge warning — Q46

Visual warning only: no critical-health alarm/beep/narration. Enter when living hull/maxHull<=25%; leave only after hull/maxHull>30% (hysteresis prevents flicker). Read authoritative hull/max, not shield health or a rounded display. Shield break alone cannot activate it. On death/quit/fresh run clear it; new capacity causing a lower hull fraction may correctly activate it. Returning to station or pause preserves the low-health condition without damage/heal.

Use a soft stationary red gradient at all four sides, fading fully transparent toward center. Outer18% of canvas width/height supplies each side falloff using smoothstep; combine by maximum rather than additive bright corners. Center64% remains untinted. Theme danger red, opacity from0.08 at25% hull toward0.24 at0; clamp at0.24. Fade in/out over0.2 presentation seconds with no pulsing/flashing. Compose after world drawing and before HUD/panels on the existing logical canvas, then use the selected existing quality/render pipeline; no extra postprocessing pass is required. Health, telegraphs and text remain legible. A dimmed pause background may retain the static tint; never tint Settings/menus/results/cutscene footage. Low graphics uses the same visible gradient without requiring the CRT shader.

Low Hull Warning Off immediately removes this persistent gradient and prevents it from returning until enabled. Actual HP numbers/bars and ordinary discrete hit feedback remain. This setting does not grant immunity, change targeting or hide enemy attack tells. Existing DamageOverlay remains the owner for discrete hit edges; extend its presentation state or the Game HUD path for the persistent warning rather than creating a second damage system. Distinguish the warning from recent-hit red feedback and cap their combined opacity at0.24. No assets are generated by this contract.

## Screen shake

Preference independent of graphics quality: Off amplitude0,Low6,Medium12,High18 canvas pixels. These equal0/2/4/6 displayed pixels at1280x720, and maximum0.9 world units atzoom20. Default Low is delegated, freely changeable. Use nonrotating presentation-camera displacement with a deterministic cosmetic seed, not shake of the whole HUD/window or gameplay camera state.

Shake events: actual hull damage uses multiplier1/duration0.16 seconds; shield break uses0.65/0.12; boss death uses1/0.25. Normal enemy deaths, pickups, every automatic projectile and harmless shield hits do not shake. Overlapping events take maximum remaining envelope, never additive amplitudes beyond preset maximum. Fade envelope linearly to zero; bounded sine/noise displacement does not consume gameplay RNG. Pause/focus freezes current shake; turning Off clears it immediately; fresh run/exit clears state. No shake in hub services, menus, story cards/captions, Settings or results.

Aim/mouse-to-world, pointer detection, collision, camera bounds and target acquisition always use the unshaken logical camera. Apply cosmetic offset only to world rendering; otherwise screen shake could change where a shot aims. HUD/telegraphs attached to world objects move with their world, screen HUD/crosshair remain stable. Check maximum preset at arena edges so the offset cannot expose unrendered borders or clip required attack tells; pad world background rather than altering legal play bounds.

## Preferences and validation

Extend existing version1 settings.cfg with optional `low_hull_warning=true` and `screen_shake=low`. Valid boolean true/false; valid shake off/low/medium/high; invalid/missing values use On/Low. Existing version1 files without new keys load normally. Preserve Master/Music/SFX/graphics fields and their finite/clamp/unknown-version/last-valid-duplicate/atomic-save/failure behavior. Application owns preferences across scenes/resetRun; Game presentation reads them. No gameplay saves or per-run auto-fire persistence is added.

Check every matrix row with mouse and keyboard, held press/release, two rapid activations, Escape, focus loss/refocus, console capture and failed transactions. Inspect at1280x720 with CRT on/off, each graphics/shake level, warning on/off, critical hull entering/exiting hysteresis, zero hull and capacity upgrades. Record screenshots/runtime outcomes later; this written checklist is not a usability test. T09/T10/settings/effect implementation remains open.
