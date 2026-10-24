# Player identity - 25 October 2026

Q29 confirms the address **Cadet [Name]**; Q30 confirms the player enters that name. This document authors the remaining UI/lifecycle defaults. No name-entry UI, voice or gameplay code is implemented here.

## Character and presentation

The player is a new cadet salvage pilot at HOPE. The rank/title is Cadet; the entered name identifies the pilot, not the ship or an online account. Do not invent a fixed protagonist name, gender, face, biography, dialogue tree or separate walking character. The player remains in the ship under existing scope.

Store the normalized name alone; render **Cadet {name}** in the hub welcome, relevant mission briefing and results header. Leaderboard name columns use just the name to keep rows readable. The title is not part of name-length validation or the persisted name field. Duplicate names across different players/runs are allowed; run IDs distinguish records.

Preproduced intro/ending/trailer narration addresses the character as Cadet/Pilot/you. It does not synthesize every entered name or require online voice generation. Runtime text can substitute the name without baking it into background art, story footage or the narrator audio. The shared original English narrator remains unchanged. Sound-off viewing stays understandable. Do not send player-entered names to generation services as part of this beta flow.

## Name entry and fresh-run creation

Current normal flow becomes **Start Game -> difficulty -> name entry -> safe hub**. This adds a panel to existing menu/input ownership, not a new Scene or account system. Reuse the planned NameEntry widget. First application session starts with an empty field. Require a valid entry to Continue; Back returns to difficulty selection with the typed draft intact. Do not initialize/advance a run, allocate rewards, spawn enemies or consume gameplay RNG until Continue commits the chosen setup once.

Use existing beta name rules: trim, uppercase, collapse repeated spaces, then 3-12 ASCII characters made of A-Z, 0-9 and single internal spaces. The label Cadet is separate. Empty/too-short/unsupported input gets a short readable error and no launch. No first-run automatic PILOT fallback or forced second name entry after the game. A literal player-chosen PILOT remains a valid name; debug/test fixtures may use it.

Enter/click Continue consumes the transition input so it cannot also fire, activate a portal or choose a card. Focus loss follows existing focus/input rules; regaining focus cannot auto-confirm. Escape/Back edits no gameplay state. Keep the panel in the CRT-safe area with the existing font/button/field style; Theme owns eventual geometry. Show allowed characters/length in the panel, not storage/implementation details.

## Session, restart and saving

Copy the chosen normalized name into immutable run identity when starting the fresh run. Changing settings, entering station, pausing, choosing cards, moving between levels and changing weapon tiers preserve it. There is no mid-run rename UI. Death/restart creates fresh gameplay progression but retains the chosen identity; restarting should not force name entry again. Starting a different New Game from the menu offers the name panel prefilled with the last chosen name, editable before Continue.

Remember that prefill only in application-session UI memory. Do not add name/game state to the existing audio/graphics settings file or imply a saved run. Saved results retain their captured name, but loading old results does not automatically choose someone else's identity at launch.

The frozen final result carries the run's name. Eligible results use **Submit Result**, showing the already-entered name and score/progress; no retyping or separate alias. Confirm saves that immutable result once. Back/Skip submission means leave it unsaved, with confirmation before losing the pending result on New Game/exit. Save failure retains the result and supports Retry with the same run ID/name. No result-name edit after death or after successful submission. This supersedes the earlier post-run Enter Name/Skip-to-PILOT default in the result contract; the 18-column file format and all score/ranking rules are unchanged.

## Later acceptance

- Start with a valid name: difficulty and name commit once, hub says Cadet {name}, and auto-fire remains OFF.
- Reject empty/invalid/too-short input; normalize spaces/case; verify minimum/maximum allowed names without clipping the title.
- Back, focus return and repeated Enter/click do not launch or create a second run accidentally.
- Pause/cards/station/level changes keep the name; death/restart resets gameplay but preserves identity.
- Menu New Game allows editing the session-prefilled name; application relaunch begins an empty name field with audio/graphics still saved.
- Results/leaderboards save the captured name without re-entry; Retry/ending skip cannot duplicate or rename a result.
- Intro/ending/trailer voice works unchanged for all names; no dynamic narration, baked player-name art or network dependency.

This is a written identity/input contract. T05/T09/PROJECT-06 must implement and actually test it before claiming delivery.
