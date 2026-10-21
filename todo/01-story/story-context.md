# Story Cards, Animation and Trailer

**21 October 2026. Preparation only.** Canon: [world and campaign](world-and-campaign.md), governed by [project overview](../../context/project-overview.md). Scientific boundaries: [science notes](science-notes.md). Mechanics: [gameplay](../02-gameplay/gameplay.md). This revision replaces the former seed/tree narrative; it creates no art, audio, video or code.

## 1. Presentation contract

The owner's confirmed format is **short story text -> animation/gameplay -> next story text -> next moving scene**, with rising trailer pacing. Text introduces an idea; the next shot demonstrates it. Narration is optional. Story cards and meaningful moving action are required.

- TEXT: a short original sentence, high contrast, comfortable reading hold inside the CRT-safe area. Subtle background movement is allowed.
- FOOTAGE: story text clears before action begins. Ships move, machinery works, living waste-eaters move inside scrap shells, enemies attack or salvage is collected. Panning over an otherwise static image cannot be the only movement in every shot.
- CONNECTION: an idea about the colony is followed by the inhabited colony; an idea about recovery is followed by actual recovery.
- AUDIO: music bridges cuts; effects follow visible events. Understandable with sound off. Optional narration follows the text rather than introducing essential off-screen facts.
- TIMING: intervals below include fades. Keep most of each three-second text interval fully readable; do not spend it on a slow typewriter reveal.
- ORIGINALITY: use original wording, composition and animation. Production prompts describe subject, materials, mood and motion directly; no real game, movie, brand, person or artist references in game content or prompts.

No walking avatar, dialogue tree, new 3D environment or video-decoding library is required. Use layered 2D scenery, in-engine presentation and verified gameplay capture as appropriate to the later production workflow.

## 2. Story essentials

Earth suffers prolonged climate disruption and waste accumulation. Scientists first engineer living waste-eaters, provisionally called Scavengers, for terrestrial facilities and protected orbital recovery pods. Humanity relies on them while continuing wasteful habits. A separate atmospheric treatment is developed in 2718 and released after five years in 2723. Unexpected exposure changes the creatures' DNA and behavior, making them hostile to humans. Scrap is their shelter and armor, not living metal. Transported organisms and residues spread exposure into orbit.

By 2732, survivor estimates put population loss at roughly 99%, following nine years of attacks and infrastructure collapse. Selected existing orbital stations become defensible refuges. In 2733, the player joins **H.O.P.E. Colony — Habitat for Orbital Preservation and Endurance** as a cadet salvage pilot. Clear routes, recover useful materials and isolate the concentrated sources that keep the wreckage dangerous.

Dates are proposed. Five development years, collapse in less than a decade, cadet role and the source-cleanup campaign are the owner's direction. Orbit remains contaminated; screened stations are locally safer, not a claim that space is clean. No radiation accident, special seed or magical planet-restoration object drives the story.

Theme: dependence on cleanup delayed responsibility until the consequences became unavoidable. Selected tagline: **“We kept throwing it away. Until it came back for us.”** See [narrative theme](narrative-theme.md) for slogans, tone and an optional synopsis passage. The timed script below uses shorter lines that fit its reading windows.

## 3. Intro: 40 seconds, five pairs

Proposed placement: once per application launch, after Loading and before Main Menu. Returning from a run does not replay it. It leads to the normal Start -> difficulty -> ship-based hub flow. No campaign unlock gate or playable simulation runs behind it.

| Time | Beat | Text or moving scene |
|---|---|---|
| 0-3 s | TEXT | “We asked life to clean up after us.” |
| 3-8 s | FOOTAGE | Show a benign waste-eater processing selected refuse, then its protected orbital recovery pod. More waste arrives. Cut to an atmospheric-treatment trial labeled 2718: a separate program begins |
| 8-11 s | TEXT | “Five years later, our treatment changed them.” |
| 11-16 s | FOOTAGE | Show the 2723 atmospheric release, then a waste-eater changing behavior and lunging from a scrap shell. A contaminated transport reaches an orbital pod; its living core moves. No chemical wave crosses vacuum |
| 16-19 s | TEXT | “By 2732, only one in a hundred remained.” |
| 19-24 s | FOOTAGE | Abandoned surface routes give way to evacuation craft and patched orbital stations. Construction arms link reused modules; warm windows reveal people still surviving |
| 24-27 s | TEXT | “H.O.P.E. became our home. You became its cadet.” |
| 27-32 s | FOOTAGE | Mothership reveal; cadet ship launches from its berth, defeats a small threat and collects salvage. Show a recognizable ship and colony landmark |
| 32-35 s | TEXT | “Silence the sources. Give Earth another chance.” |
| 35-40 s | FOOTAGE | An infested source nest releases scrap-covered organisms; cadet approaches. Cut to a survey craft waiting beside HOPE and damaged Earth beyond, then transition to Main Menu |

The five-year interval refers to atmospheric-treatment development, not the invention of the waste-eaters. Those organisms were already deployed. The intro compresses a spreading catastrophe into selected shots; it must not imply every exposed creature transforms identically at the same instant.

Suggested visual progression: damaged industrial Earth -> useful biological processing -> altered organisms in scrap shells -> warm inhabited stations -> purposeful pilot launch. Preserve existing gameplay meanings for danger, player, reward and healing colors.

## 4. Hub storytelling and interface copy

The hub is a safe orbital approach with the player still in the ship. Show inhabited modules, service traffic, life support and a visibly reused mothership. Background ships do not create combat entities or rewards. The settlement feels maintained through work rather than magically protected.

| Moment | Draft text | Required supporting action |
|---|---|---|
| Arrival | “H.O.P.E. Colony — Cadet Operations” | Ship arrives at the recognizable mothership berth |
| Workshop | “Recovered parts. New possibilities.” | Skill offers show their real rank effect and Trade Scrap price |
| Repair berth | “Materials required. Review repair cost.” | Quote, timed service and actual currency deduction |
| Launch | “Recover what you can. Come home.” | Selected mode and objective remain prominent |
| Source shut down | “Source isolated.” | Source emissions stop; remaining required hostiles still need clearing |
| Final corridor | “Recovery teams: the route is open.” | Ending follows a completed encounter, not a random loot drop |

Use ordinary greenhouse or food-production modules as evidence of life support, not a special restoration seed. HOPE's full expansion may appear on an introductory colony card or briefing; small HUD labels use HOPE.

## 5. Mode framing

| Mode | Story role | Limits of its outcome |
|---|---|---|
| Swarm | Continuous salvage patrol | Endless normal threats; no campaign conclusion |
| Survival | Hold a route for a fixed operational window | Success at the displayed combat-time deadline |
| Boss | Intercept one major threat | Local encounter success, not automatically the campaign source |
| Chaos | Emergency containment in a densely contaminated region | Endless swarms and scheduled bosses; one boss kill does not end the mode |
| Campaign | Reach and isolate concentrated source sites | Final source clearance opens a corridor for restoration teams |

Show only implemented playable modes in a recorded gameplay claim. Campaign victory does not unlock Swarm; all enabled modes are available through their hub portals from the start.

## 6. Ending: proposed 24 seconds, three pairs

Trigger after final guardian death, source shutdown and all required hostile resolution, provided the player survives. The result is committed once before presentation. The ending cannot collect leftover loot, grant a second boss reward, heal the ship or advance score/time.

| Time | Beat | Text or moving scene |
|---|---|---|
| 0-3 s | TEXT | “The source fell. The damage remained.” |
| 3-8 s | FOOTAGE | The guardian falls and source dispersal equipment shuts down. The infested nest stops releasing new threats; the route remains littered and Earth is still damaged |
| 8-11 s | TEXT | “For the first time, we could hold the route.” |
| 11-16 s | FOOTAGE | Survey and containment craft leave HOPE, fly through the cleared corridor and approach a prepared surface landing zone |
| 16-19 s | TEXT | “We survived the consequences. Now we must change.” |
| 19-24 s | FOOTAGE | A cleanup crew's remote equipment seals contaminated wreckage; habitat lights come on in a small secured area. End on the damaged planet with the colony above, then show the recorded result |

No whole-planet green flash, universal chemical neutralization or instantaneous climate repair. The achievement is a defensible foothold for continued recovery. A remote cleanup device is cinematic scenery, not a promised playable ground system.

## 7. Trailer: 90 seconds, six pairs and title

The separate gameplay demonstration remains a different deliverable. This trailer fits the planned 1-2 minute slot and alternates brief story cards with longer motion sequences.

| Time | Beat | Text or moving scene |
|---|---|---|
| 0-3 s | TEXT | “We kept the habits. We postponed the consequences.” |
| 3-15 s | FOOTAGE | Living waste-eaters process refuse on Earth and inside orbital pods; incoming waste keeps increasing. Show the separate atmospheric project labeled 2718, then five years of development ending at a 2723 deployment display |
| 15-18 s | TEXT | “2723. The treatment changed more than the sky.” |
| 18-30 s | FOOTAGE | Atmospheric exposure reaches the waste-eaters. Altered creatures move inside scrap armor and attack a service vehicle. Exposed organisms/residues travel with cargo to orbital recovery pods. End on evacuation and abandoned infrastructure |
| 30-33 s | TEXT | “One in a hundred survived. H.O.P.E. gave us a home.” |
| 33-45 s | FOOTAGE | Reused stations connect, habitation lights brighten and a cadet ship leaves the mothership. Move into real flight, shooting and collected salvage |
| 45-48 s | TEXT | “Recover what we need. Return when you can.” |
| 48-60 s | FOOTAGE | Collection crosses a field-level threshold, the player chooses an upgrade and demonstrates it. Show eligible Return Home with positive online shield and sufficient charge |
| 60-63 s | TEXT | “Repair. Rebuild. Cut through the wreckage.” |
| 63-75 s | FOOTAGE | Paid repair and skill purchase visibly spend currency. Portal preview shows objective; launch into a mode that actually works. Preserve readable actions rather than flashing every menu |
| 75-78 s | TEXT | “Silence the sources. Give Earth another chance.” |
| 78-86 s | FOOTAGE | Actual implemented source-boss pressure, pilot evasion and retaliation. End with a hopeful survey-craft/colony/Earth composition; do not spoil the entire ending |
| 86-90 s | TITLE | Approved final game title and approved team/competition text. Four-second readable hold, fading toward the opening for a loop |

Text totals 18 seconds, footage 68 and title four. Transitions are inside these intervals. Voice is optional. Keep story sentences off the busy action; native HUD and accessible speech subtitles can remain when needed.

If a feature is unavailable when recording, use truthful existing footage and revise the edit within the required duration. Lore scenes may illustrate fiction but must not masquerade as proof of functioning mechanics. Do not invent final boss footage before its design and implementation exist.

## 8. Playback and transition contract for later implementation

- Intro completion or Skip Intro reaches Main Menu once. It does not create a run. Start and difficulty confirmation remain explicit player actions.
- Ending completion or Skip Ending reaches the already finalized run result once. It cannot restart combat or duplicate leaderboard submission.
- Proposed controls: Space/Enter/click advances to the next complete beat; Esc skips the whole sequence. Show a small safe-area hint. Consume the triggering input so it cannot activate the destination menu/result button.
- Advance never leaves the previous card over the next footage. A skipped beat stops its presentation effects cleanly. Holding a button does not skip every beat: require a fresh press.
- Intro is marked seen only for this application session. No persistent save or replay-menu feature is required. Ending plays after each valid campaign clear.
- Presentation owns its own clock; gameplay, loot RNG, damage and mode timers are inactive. Pause/focus handling follows the chosen UI lifecycle, without hidden combat progress.
- Use the existing cutscene base and rendering pipeline after checking the class registry. Verify supported animation before committing to a file format; no library adoption is authorized by these notes.

## 9. Production inventory and acceptance

Needed later: reusable story-card treatment; five intro motion blocks; three ending motion blocks; six trailer footage blocks; title card; original music/effects and optional voice. A block may reuse layers or contain several cuts; these counts do not require one new full-screen image per beat.

For every asset produced later, record source/license, creator/tool, prompt when generated, date and edits in assets/ASSETS.md. This preparation session adds no assets or provenance claims.

- [ ] Text precedes footage and clears before related action.
- [ ] Every motion block has a visible action, not only a stationary image.
- [ ] Sound-off viewing communicates catastrophe, refuge, cadet mission and recovery purpose.
- [ ] Text holds are readable at the real display size, within the CRT safe area.
- [ ] Intro/ending/trailer intervals total 40/24/90 seconds, including transitions.
- [ ] Beneficial organisms visibly predate the atmospheric project; living cores explain hostile scrap movement.
- [ ] The theme connects neglect to consequences and recovery to sustained responsibility.
- [ ] Dates, colony name, source mechanics and scientific framing match world-and-campaign.md.
- [ ] Actual gameplay footage shows valid costs, shield/return conditions and available modes.
- [ ] All skip/advance paths consume input and enter their destination once.
- [ ] Final boss names, optional voice, title and asset samples receive team review before production.
