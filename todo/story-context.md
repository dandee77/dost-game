# Story and Trailer Context

**20 October 2026 — documentation only.** Existing narrative source: [project-overview.md](../context/project-overview.md), Story section. Gameplay source: [gameplay.md](gameplay.md). This brief develops the owner's request for atmospheric story presentation; it does not generate art/audio, change code or approve final boss content.

## 1. Existing story, retained

The story is already present in the Markdown:

1. Earth has suffered prolonged environmental damage.
2. Humanity has also left orbit crowded with dead satellites, rocket stages and discarded machinery.
3. An experimental orbital cleanup chemical is deployed.
4. The experiment goes wrong. In this fictional setting, contaminated debris becomes hostile.
5. Surviving humans shelter in an orbital settlement, working name **Bayanihan Dock**.
6. Scientists preserve a **Narra seed**, called the **World Tree**, as a symbol of restoring life on Earth.
7. The player is a **Collector**, a pilot reclaiming useful material and clearing a safe route home.
8. Campaign progression leads toward the source of contamination and a final boss.
9. Victory opens a route for a restoration mission. The first new growth represents a beginning.

The original midpoint/final proposals were The Hoarder and The Core. Their identities, designs and attacks remain provisional because the owner plans to develop the bosses. Refer to “midpoint threat” and “contamination source” in production planning until the roster is finalized.

The chemical mutation and World Tree are fictional story elements. Do not present them as established science. Retain the narrow environmental framing in project-overview.md; avoid implying orbital waste alone caused Earth's collapse or that one tree instantly repairs a planet.

## 2. Confirmed presentation: story text, then moving footage

**Owner clarification:** tell the story with a trailer-like rhythm: **story text -> animation/gameplay -> next story text -> next animation/gameplay**, building toward a final reveal. The text introduces an idea; the following moving scene shows it. This replaces the first draft's illustrated-panel-and-caption structure.

```text
Short story card
    -> animated scene or gameplay clip showing that idea
Short story card
    -> next animated scene or gameplay clip
    -> repeat with rising intensity
Final story line
    -> hopeful visual / game-title reveal
```

- **TEXT beats:** one short original sentence on a dark, atmospheric background. Text is the main visual; distant stars or subtle dust may move behind it.
- **FOOTAGE beats:** fade the story card away, then show meaningful motion. Story sentences do not remain over busy combat. Gameplay HUD and accessibility subtitles may remain when needed.
- **Narrative connection:** the clip must answer the preceding text: a line about humanity's new home leads to a colony reveal; a line about reclaiming wreckage leads to actual collection.
- **Actual animation:** ships travel, thrusters burn, machinery moves, enemies attack, debris breaks or the camera reveals a moving environment. A stack of still images with text does not satisfy the intended treatment. Illustrated layers may support scenes, but each footage beat needs visible action.
- **Pacing:** begin quiet and spacious, introduce the catastrophe, reveal the colony, then build momentum with flight and combat. Finish on purpose and hope.
- **Audio:** music bridges the text/footage cuts; sound effects belong to visible actions. Voice-over is optional. The story remains understandable through the required text cards with sound off.
- **Readability:** use brief text and a comfortable hold before cutting. Keep required story sentences out of gameplay shots so viewers can read first, then watch.

This is an original story trailer using the existing premise and the game's own art/action. It does not require a walking character, dialogue system, new 3D engine or imitation of another title's script or footage.

Production language and asset prompts describe composition, materials, lighting and mood directly. Do not name existing games, brands, filmmakers or artists in game content or AI asset prompts. This treatment must have its own narration, visual designs and music.

## 3. Narrative roles

| Element | Function in the story | How the player sees it |
|---|---|---|
| Collector | Working pilot recovering resources and defending a route home | Existing controllable ship; no walking avatar required |
| Mothership | Operational heart of the settlement | Arrival berth and recognizable Return Home landmark |
| Colony | People and a future worth protecting | Habitation lights, connected modules, crop/greenhouse silhouettes and docking structures |
| Repair station | Recovered materials keep ships flying | Visible paid hull/shield service; cost explained as materials and labor |
| Skill shop | Reclaimed components improve mission equipment | Targeted skill upgrades and rare recovered systems |
| Scrap | Waste becomes useful material again | Trade scrap funds maintenance; salvage progress powers field adaptation and return |
| Portals | Routes into different danger zones | Mode selection; exact portal technology remains background fiction |
| World Tree seed | Hope, memory of Earth and a restoration mission | Small greenhouse image in the intro, optional static hub detail, ending seedling |

Do not add named NPCs, quest systems, reputation currencies or colony-building mechanics solely to communicate these roles.

## 4. Intro storyboard: approximately 40 seconds

Five text/footage pairs. Durations include transitions and are editorial targets. The text is mandatory; spoken delivery is optional. Preserve skip/advance controls and the established Start -> difficulty -> hub playable flow.

| Time | Beat | Text or moving scene |
|---|---|---|
| 0-3 s | TEXT | “We scarred our world. Its orbit carried our waste.” |
| 3-8 s | FOOTAGE | Slow orbital reveal: damaged Earth below, discarded panels and rocket stages drifting past. Clear objects moving at different depths |
| 8-11 s | TEXT | “Our attempt to cleanse the sky awakened the wreckage.” |
| 11-16 s | FOOTAGE | Cleanup pulse spreads through debris; fragments fuse and turn; a hostile shape lunges toward the camera |
| 16-19 s | TEXT | “Humanity built a new home among the stars.” |
| 19-24 s | FOOTAGE | Ship approaches the mothership; the camera reveals lit colony modules, docking beacons and moving service traffic |
| 24-27 s | TEXT | “Collector, reclaim what we need to survive.” |
| 27-32 s | FOOTAGE | Gameplay-style ship flight, a short fight, intact destruction animation and scrap absorption; show one readable action chain |
| 32-35 s | TEXT | “One seed. One promise. A way back home.” |
| 35-40 s | FOOTAGE | Greenhouse light reveals the seed; cut to the Collector launching toward Earth, then transition to the existing menu/entry destination |

Suggested palette progression: muted Earth tones -> cold discarded metal -> contamination accent -> warm colony windows -> a restrained living-green seed accent. Use the established game palette where it already defines gameplay meaning.

Use economical 2D animation: moving ships/debris, thrusters, a cleanup pulse, enemy attack and actual collection. Camera pans and light flicker support those actions. Text cards stay inside the CRT-safe region and clear before footage begins.

The in-game intro is a presentation sequence, not a secretly running expedition. It cannot grant scrap, advance mode timers, damage the player, spend currency or change gameplay RNG. In-engine staged animation and captured trailer footage are production options; this brief does not require adding a video-decoding library. Final implementation chooses the supported presentation path.

## 5. The hub carries the story

After Start and difficulty confirmation, the player arrives at the mothership in their ship.

Required visual messages:

- **People live here:** windows, habitation modules and a protected central structure.
- **This is home:** the same landmark appears in the intro, hub and return transition.
- **Resources matter:** repairing and upgrading visibly spend trade scrap; no contradictory free-healing presentation.
- **There is a larger purpose:** a greenhouse/seed motif connects cleanup to eventual restoration.
- **The player chooses the next mission:** named portals communicate danger and objective, not arbitrary menu doors.

Optional short flavor lines, usable without adding an NPC dialogue system:

- Arrival: “Bayanihan Dock — Collector berth.”
- Shop: “Recovered parts. New possibilities.”
- Repair: “Materials required. Review repair cost.”
- Launch: “Recover what you can. Come home.”
- Campaign final approach: “A route to the surface is within reach.”

These are original drafts. Do not display flavor where it hides the price, objective, shield blocker or an important combat warning.

## 6. How the modes fit the world

| Mode | Narrative framing | Story consequence |
|---|---|---|
| Swarm | Ongoing salvage and defensive patrol | Repeatable work; no false claim that the campaign ends |
| Survival | Hold a route during a fixed operational window | Success at the displayed survival deadline |
| Boss | Intercept a major contamination threat | Ends the designated encounter; not automatically the campaign source |
| Chaos | Emergency operation through a heavily contaminated zone | Endless mixed pressure; boss kills are local successes |
| Campaign | Clear successive routes toward the contamination source | Final boss victory enables the restoration ending |

All modes remain accessible according to their actual implemented availability. Campaign completion does not unlock a supposedly unavailable Swarm mode. Do not describe five functioning modes in a trailer if only some are playable.

## 7. Campaign ending

Use the same text-then-moving-scene grammar for a small, hopeful payoff:

1. The final threat falls; the immediate route is safe.
2. Return to a wide view of the colony and the damaged planet below.
3. A restoration shuttle descends carrying the protected seed.
4. A small seedling appears in prepared soil. Fade to a message that recovery has begun.

Original ending card sequence:

1. TEXT: “We could not undo what we left behind.” -> FOOTAGE: the final wreckage settles and the colony comes into view.
2. TEXT: “But we could choose what came next.” -> FOOTAGE: the restoration shuttle leaves the dock and descends.
3. TEXT: “A cleared path. A seed. A beginning.” -> FOOTAGE: a small seedling in prepared soil, then the result transition.

Do not show the whole planet becoming green instantly. The victory is the first successful restoration mission, with continued collection and care still necessary.

Stats/result handling must still follow the gameplay contract: final-boss death resolves once, no currency farming during the ending, and New Run begins with fresh progression.

## 8. Trailer outline: 90 seconds

This fits the existing 1-2 minute trailer target and remains separate from the 3-5 minute gameplay demonstration video. Use six story-card/footage pairs followed by the title. The longer footage sections may contain a few purposeful cuts; each starts after its text card clears.

| Time | Beat | Story text / footage direction |
|---|---|---|
| 0-3 s | TEXT | “What we leave behind does not disappear.” |
| 3-15 s | FOOTAGE | Earth and moving orbital waste; cleanup deployment; contaminated fragments begin moving against their drift |
| 15-18 s | TEXT | “When the wreckage awakened, we built a new home.” |
| 18-30 s | FOOTAGE | Hostile debris closes in, then reveal the inhabited colony and Collector launch. Show the protected settlement before combat |
| 30-33 s | TEXT | “What others discarded can keep us alive.” |
| 33-45 s | FOOTAGE | Real flight, shooting, complete enemy/debris destruction and collection. Follow one pickup into the ship; make the recycling loop readable |
| 45-48 s | TEXT | “Every recovery gives us another chance.” |
| 48-60 s | FOOTAGE | Scrap triggers a field upgrade; show its effect, then eligible Return Home and safe arrival. Do not depict return with a broken shield |
| 60-63 s | TEXT | “Repair. Rebuild. Face what waits beyond the dock.” |
| 63-75 s | FOOTAGE | Paid repair and one skill purchase with visible currency deduction; portal launch; combat pressure and an actually implemented boss threat |
| 75-78 s | TEXT | “Clear a path. Give tomorrow a chance.” |
| 78-86 s | FOOTAGE | Short action climax, then a calmer seed/ship/Earth shot. Tease restoration without revealing the complete Campaign ending |
| 86-90 s | TITLE | Final game title and approved team/competition text; hold for readability and fade toward the opening for looped playback |

Text occupies 18 seconds, footage 68 seconds and the final title 4 seconds. Keep narration optional and use music continuity to connect the alternating beats. Do not turn the text into a continuous voice-over paragraph or leave every sentence as an overlay throughout the footage. Native gameplay labels and accessible speech subtitles are separate from the story cards.

For an early trailer before the full design is implemented, replace unavailable gameplay sections with truthful existing footage and shorten the edit within the required duration. Concept panels may show world/lore, but cannot substitute for proof that a mechanic works.

## 9. Asset and production handoff

Planned materials: reusable atmospheric card background/type treatment; five short intro animation sequences; six trailer footage blocks; ending motion scenes; optional narration; original/properly licensed music and effects. Counts describe edit beats, not a requirement for one new image per beat. Existing planned intro/ending illustration slots can supply layered scenery, but need the moving actions described above. Reuse colony/ship/environment visuals and verified gameplay captures.

For each final asset record source/license, creator/tool, exact prompt if generated, date and edits in assets/ASSETS.md when asset production is authorized. This context session adds no asset files or provenance claims.

Example original visual direction, not an instruction to generate now:

“Wide view of a human orbital settlement above a damaged planet, connected habitation modules with warm window lights, a central salvage mothership and a small collection ship, restrained industrial science-fiction illustration, readable silhouettes, quiet hopeful mood, room for a short lower caption.”

Final format, resolution and typography follow ui-rules.md and the actual capture/export workflow. Story cards remain legible without narration; music never masks essential spoken lines.

### Review checklist

- [ ] Each required story card appears before its related footage and clears for the action.
- [ ] Every footage beat contains visible animated action, not only a stationary illustration.
- [ ] The story is understandable with sound off.
- [ ] Text holds are readable at the actual display size; transitions are included in the 40/90-second totals.
- [ ] Gameplay captures show functioning features and their true outcomes.
- [ ] The in-game presentation cannot change the player's run state or resources.
- [ ] Skip/advance moves cleanly through complete beats and reaches the proper menu/game destination.

## 10. Decisions still open

- Final title and whether working names Bayanihan Dock/World Tree remain.
- Final boss identities, appearances and exact connection to the contamination source.
- Optional narration voice/language; story text cards are required regardless.
- Exact animation/art treatment and approved visual samples; alternating text/footage structure is confirmed.
- Whether the intro plays once per launch or on first Campaign entry; preserve Start -> difficulty -> hub as the playable entry sequence.
- Which completed modes/features can truthfully appear in the recorded trailer.

This brief supplies an original draft ready for review, while the existing story remains the source of the game's premise.
