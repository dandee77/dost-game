# Scoring, results and local leaderboards - 25 October 2026

Status: adopted implementation specification, authored under the owner's delegation. No scoring/result/leaderboard runtime is delivered by this document. Gameplay numbers belong to the matching current section of [game design](../../context/game-design.md#25-october-scoring-defaults---beta-r1). Ownership belongs to [architecture](../../context/architecture.md). This replaces older deposit scoring, two-mode CSV and death-first boss-tie proposals.

## Confirmed direction and authored defaults

Owner confirms score-first Swarm/Chaos rankings with survival time, station retirement in Swarm/Chaos/Boss, boss-clear credit on simultaneous player/boss death followed by run end, four modes, fresh gameplay runs and local preferences/history without permanent gameplay benefits. Latest 25 October clarification permits short needed game-content questions only; technical authoring remains delegated. Values, schema and error behavior below are author-selected defaults; human deadline, hardware, registration/provenance evidence and submission assignment are not invented. Q29/Q30 revise naming to player-entered prelaunch Cadet identity, as detailed below.

Score is earned through credited combat and finite Campaign objectives, never wallet size or spending. Current source has 10-point low enemies, 50-point ranged enemies and 5-point debris, an int score on Player, and several legacy award paths. Preserve those verified baseline facts while replacing all award paths with one typed run-owned scoring ledger during implementation. Planned Leaderboard/RunContext boundaries are not existing implementations. Do not leave an old Player/skill branch awarding the same death twice.

## Score events and anti-farming

The numerical table in game-design.md is authoritative. Entity death carries a unique entity ID, encounter ID, spawn origin and one terminal cause. One credited death emits at most one score event; erasure skills may suppress material drops without suppressing a valid enemy/boss kill score. Environmental cleanup, scripted retirement/despawn and reset are not kills. Barricade segments, scenery and boss-owned adds receive no kill points. Boss adds retain their ordinary material/Salvage rewards where the loot contract permits them; this scoring exclusion does not silently remove those rewards.

Ordinary director-spawned enemies pay ordinary points, including legitimate endless reinforcements. Boss-owned repeatedly spawned adds pay zero points to prevent indefinitely farming a single boss for score. A legitimate repeated Boss-mode encounter pays the normal boss award once because it has a new encounter/entity ID. Use terminal entity flags, current encounter finalization and bounded in-step duplicate checks; do not retain every ordinary kill ID forever merely to enforce once-only credit. Damage dealt, overkill, critical tiers, shots fired, dodging, active time, scrap collection, purchasing, shield breaks, repairs, portal use and entering the station add no points.

Campaign normal-wave, level and final-completion awards use separate `(run, level, wave/objective kind)` keys. A level award is additional to its boss-kill award; final completion is additional to the C04 level award. No completed-level replay/farming is available. A canceled map, duplicate clear callback or station visit cannot award again. Optional unlocked middle levels legitimately add their encounter/objective points, so three-level and four-level completions may produce different scores on the same ruleset; display completed levels so that difference is visible.

No time multiplier, difficulty multiplier, currency conversion, damage bonus or retirement bonus. Separate difficulty boards instead. Boss mode has no cycle-completion bonus; Nestheart -> Shellback does not create a new run. Campaign receives its ordinary completion award if all final objectives resolve in the same boss/player-fatal step, as allowed by Q19/Q20; no extra mutual-destruction award is added.

## Worked score examples

| Mode / outcome | Credited events | Score |
|---|---|---:|
| Swarm, Retired | 100 low enemies, 10 ranged, 4 debris | 1520 |
| Chaos, Defeated | Same events plus 2 boss kills | 5520 |
| Boss, Retired | 5 boss clears; boss adds add no points | 10000 |
| Boss, Mutual Destruction | 3 credited boss kills including fatal tie | 6000 |
| Campaign, complete via one middle level | 1000 low, 100 ranged, 20 debris; 12 normal waves, 3 bosses, 3 levels, one final completion | 32100 |
| Campaign, complete via both middle levels | Same ordinary kills; 15 normal waves, 4 bosses, 4 levels, one final completion | 35850 |
| Campaign, fatal final boss tie with required adds left | Boss award only for this encounter; no final level/completion award | 2000 added to already earned total |

These are arithmetic examples, not expected player income, spawn counts, encounter duration or measured balance. Time saved with each result is actual active combat time, not a score component.

## Terminal result and event order

Game/run owner aggregates valid events from one simulation step, then selects one terminal outcome. The score ledger consumes validated death/clear events before the result freezes. Existing Player/Enemy/Skill/Director owners report facts; they do not each own separate result saves.

| Condition | Outcome token | Credited progress / presentation |
|---|---|---|
| Living player completes every final Campaign objective | `victory` | Campaign completion true; normal ending then frozen result |
| Player and boss die in same step | `mutual` | Count each valid boss death once; end run without revival/portal; Campaign completion true only if all final objectives also resolved |
| Fatal player damage without a same-step boss death | `defeat` | Keep already earned score/progress; no ordinary-wave fatal-tie clear |
| Living player confirms station retirement in Swarm/Chaos/Boss | `retired` | Earned score/time; Boss includes credited boss count; no pending encounter credit |
| Player confirms abandon/exit from an unfinished run | `abandoned` | No competitive submission; optional recent-result record only |
| Player confirms End Run from an unresolved simulation-capacity/numerical fault | `fault` | Last fully committed score/progress/time, unranked diagnostic result; no invented victory, retirement bonus, loot or new objective credit |

After terminal decision: stop simulation/scoring/collection, freeze an immutable result, clear pending travel/shop/launch/card requests, then perform ending/results flow. Do not force a posthumous card choice. New effects and later-step damage cannot extend a terminal run to obtain a boss kill. Remaining hostile cleanup gives nothing. A dying ship cannot enter the station even if its boss clear counts. Victory/mutual/retirement confirmation cannot be reclassified by later callbacks.

The `fault` outcome completes the [numerical-failure contract](../04-verification/numerical-and-load-contract.md#representation-and-failure-semantics). Retry does not finalize a result; only confirmed End Run does. Preserve the last fully committed state, never partially completed faulting transactions or unprocessed simulation time. An already committed ordinary terminal result cannot later become fault because a cosmetic/save/presentation operation fails. Optional cosmetic allocation failure reduces cosmetic output within the adopted budget; it is not a gameplay-simulation fault. A result-file write failure remains Saved/Retry UI on the SAME result, not a second fault outcome.

Snapshot rules identity and seed at fresh-run creation. A result contains unique run ID, mode/difficulty, outcome, Campaign-complete flag, score/validity, active time, uniquely credited boss count, normal-wave count, completed-level count, lifetime trade collected, final level, ranked eligibility and debug flags. Wallet is not lifetime trade. Active time accumulates only running combat delta and converts to floored milliseconds once at finalization; station, pause, card, console capture, wave-clear choice, map, intro/ending and menu time are excluded. Never round each frame separately.

Use checked uint64 score/time/counters; serialize base-10 integers without float conversion. If arithmetic cannot represent earned totals, flag numeric failure and make that result unranked instead of wrapping or displaying a fake maximum score as competitive. Preserve the last representable diagnostic value and visible reason. This is representational failure handling, not a gameplay rank or army-count cap.

## Boards and tie order

Board key is `(rules, mode, difficulty)` with modes `swarm|chaos|boss|campaign` and difficulties `easy|hard|impossible`. Current rules identity is `beta-2026-10-25-r1`; changing scoring, roster, combat rules or difficulty tables requires a different identity. Never combine old two-mode entries or different rules on current competitive boards. Seeds are recorded for replay/diagnosis but are not an extra filter in this beta; no network validation is claimed.

Swarm/Chaos/Boss: score descending, active milliseconds descending, then earlier accepted record wins. Campaign: score descending, Campaign-complete true first, completed levels descending, boss clears descending, active milliseconds ascending, then earlier accepted record wins. Score always remains primary; no sorting by wallet or converting all outcomes to victory. Display survival time in `mm:ss` or `hh:mm:ss`, with exact stored milliseconds used only to break ties. Boss rows also show boss clears; Campaign rows show completion/progress. Keep 10 entries per board. Display the latest run's frozen result even when it does not enter the top 10.

`victory`, `defeat`, `mutual` and `retired` may qualify if otherwise eligible. `abandoned`, `fault`, numeric failure, debug-mutated runs, partial-content rosters and unsupported rules never qualify. Compiling a debug build or opening the console alone does not taint a run. Commands that mutate gameplay (spawn, kill, grant, equip, upgrade, heal, invincibility, seek, seed replacement) irreversibly taint the current run. Stats, hitboxes, ordinary settings and mute do not. Turning a cheat off cannot restore eligibility. New Game resets run-local taint; sound/graphics changes preserve eligibility.

## Name entry and one-time submission

**Q29/Q30 latest identity revision:** Enter the name before the run, after difficulty and before hub entry, under the [identity contract](../01-story/player-identity.md). Input accepts 3-12 ASCII characters after trim, uppercase conversion and collapsing repeated spaces; allowed characters are A-Z, 0-9 and single internal spaces. Require a valid name; unsupported/empty/too-short input cannot Continue. There is no automatic PILOT fallback or post-run alias entry in normal play. The name is local identity, not an account; Cadet is a separate rendered title. CSV name excludes commas, quotes and newlines.

Only the current frozen result may submit, using its already-captured pilot name. Show Submit Result with name/score/progress, not another Enter Name field. A nonqualifying top-10 run may still save to recent records. Confirm creates one canonical row keyed by run ID; repeated callbacks, ending skip, result re-entry and Retry cannot create another row or change name/statistics. Escape/Skip submission may keep it pending, but must confirm leaving without save before losing it on New Game/exit. A write failure retains the immutable in-memory result and supports Retry. No post-run alias/rename or automatic resubmission on scene transitions.

## File format, limits and recovery

Use `results-v1.csv` beside the executable, separate from settings.cfg and the legacy leaderboard.txt. UTF-8 without BOM on write, LF or CRLF accepted on read, exact header `SCRAPBOUND_RESULTS,1`, then rows in these 18 columns (there is no second column-name row):

```text
run_id,rules,mode,difficulty,seed,outcome,campaign_complete,score,score_valid,active_ms,bosses,waves,levels,trade_collected,final_level,ranked,debug_flags,name
```

Example data row:

```text
0123456789abcdef0123456789abcdef,beta-2026-10-25-r1,boss,hard,42,retired,0,10000,1,1800000,5,0,0,500,none,1,0,PILOT
```

Generate a distinct 128-bit run ID independently of gameplay RNG and verify it against loaded IDs; the seed itself is not a run ID. Format as 32 lowercase hex characters. Rules IDs are bounded to 64 ASCII letters/digits/dot/underscore/hyphen. Seed/score/time/counters/flags are checked unsigned decimal; booleans are 0/1. final_level is `none|C01|C02|C03|C04`; Campaign uses its actual last active level. Require exact field count, legal enums, valid name and no trailing junk. A structurally valid record with unknown rules is retained as non-current history, never ranked as current. Schema mismatch disables writes to that file; do not guess field meanings.

Legal outcome enum is exactly `victory|mutual|defeat|retired|abandoned|fault`. A fault row always has ranked=0, campaign_complete=0; score_valid stays1 if the last committed score is representable and becomes0 only on actual score arithmetic failure. Other numeric/allocation faults need not falsely invalidate a valid earned score. Keep the existing18 columns/version1; no free-text error column. Current in-memory results may show a bounded diagnostic reason; loaded fault history shows Simulation Fault, without inventing the original cause. Recent history may save it through the same explicit submission/atomic-write path; it never enters a top10 board.

Valid diagnostic example (not a competitive record):

```text
fedcba9876543210fedcba9876543210,beta-2026-10-25-r1,swarm,hard,42,fault,0,1520,1,90000,0,0,0,120,none,0,0,PILOT
```

Maximum read size 1 MiB, line length 1024 bytes and 4096 data rows. Reject oversized/unknown-format files non-destructively with one visible load error; do not auto-overwrite them with an empty board. Missing file means an empty first-run history. Skip malformed individual rows within a recognized bounded v1 file and report one aggregate warning, not one per frame. Validate ranked=true against flags/outcome/score validity; never trust that bit by itself. First valid duplicate run ID wins; identical or conflicting later duplicates are skipped and counted in the warning. Do not execute or render unchecked arbitrary text from a damaged row.

Maintain the newest 100 accepted results plus top 10 for each loaded board, deduplicated by run ID and written in stable acceptance order. No full-history browsing screen is required. If the union would exceed the bounded format, refuse the save with a clear storage-limit error and preserve file/in-memory result; never prune a current top-10 board silently. Legacy leaderboard.txt remains untouched; there is no fabricated migration of Story/Endless scores to the new rules.

For save: construct the validated deduplicated image in memory, write a sibling temporary file completely, verify stream/close success, then atomically replace the destination using the platform's supported replacement operation. Do not delete the only good destination before replacement. On any failure, preserve the old file and frozen in-memory result; show Saved/Retry status accurately. If loading skipped corrupt rows, first make a uniquely named exact-byte backup and verify that backup succeeds before replacing the recognized v1 file. Keep unsupported/oversized files untouched and writes disabled rather than repairing by guesswork. Use event-only diagnostics. No cloud, login, database or new serialization library.

## Acceptance checklist for the later implementation

1. Verify all seven arithmetic examples and every award source, including no-loot skills, boss adds, debris and cleanup.
2. Collect one kill through each legacy weapon/skill path; the ledger credits once and matches HUD/final result.
3. Verify retirement after zero/one/four/five Boss clears, Cancel and repeated saves; pending boss count stays excluded.
4. Resolve simultaneous death/boss kill in both event orders, with/without final adds and with several Chaos bosses; freeze one correct result.
5. Compare active time across pause, cards, ordinary return, station, checkpoint choice and ending; graphics/frame-rate changes do not add waiting time.
6. Verify all board keys, outcome labels, score-first ties and top-10 retention; unsupported rules never mix with the current rules.
7. Test missing, valid, duplicate, malformed, truncated, oversized and unknown-schema files, write denial, replacement failure and retry. Old data and current result survive failed writes.
8. Check prelaunch name validation/capture, no post-run re-entry/rename, leaving without submission, click-through prevention, ending skip, repeat result entry and taint that remains after disabling cheats.
9. Repeat New Game/restart/quit: only current run-local ledger/pending result clears; settings and successfully saved records remain. Clean release packaging still needs a real target-machine test.
10. Technical Retry preserves the run without finalizing; confirmed End Run emits one fault row with18 fields and no ranking. Allocation fault preserves a valid prior score; actual score overflow sets score_valid=0. Cosmetic failure and save failure never reclassify an existing victory/defeat/mutual/retired result.

Specification delivery completes PREP-08/09 only. PROJECT-06, runtime scoring integration, package validation and all listed acceptance tests remain unfinished until actually implemented and run.
