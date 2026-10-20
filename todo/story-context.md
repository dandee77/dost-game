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

## 2. Intended presentation

Interpretation of the owner's reference: **an atmospheric illustrated introduction with restrained narration, followed by playable scenes that carry the story through place and action**. This is a proposed treatment, not a claim that the owner selected one precise reference trailer.

- Tell the history through a small sequence of original illustrations with slow pans, layered movement and short captions.
- Move from damaged Earth to abandoned orbit, then reveal the warm lights of a lived-in colony.
- Present the player as a working pilot whose recovered scrap supports survival.
- Let the hub establish what the player protects before asking them to enter a dangerous portal.
- Use a calm narrator or short written captions. Narration is optional; all important meaning remains readable without sound.
- Transition to actual gameplay quickly in the trailer: collecting, field choices, returning, paying for repairs and improving a build.
- End on hope and responsibility, with the recovery of Earth still ahead.

Avoid lengthy dialogue trees, character lip-sync, walking cutscenes, a second art pipeline or cinematics that require a 3D engine. Original illustrated panels and existing 2D gameplay suit the current project scope.

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

Seven original panels, consistent palette and framing. Timing is an editorial target. Captions can double as the narration script. Keep existing skip/advance affordances; final startup placement follows the product flow rather than forcing a second intro after difficulty selection.

| Time | Image/composition | Original narration/caption |
|---|---|---|
| 0-6 s | Earth from orbit; clouded atmosphere and quiet dark city outlines | “We left more than footprints behind. We left a world struggling to breathe.” |
| 6-12 s | Broken panels, spent stages and discarded machinery circling the planet | “Above it, the things we discarded kept circling.” |
| 12-18 s | Cleanup deployment; a faint chemical bloom threads between objects | “We sent a cleansing agent to reclaim the sky.” |
| 18-24 s | Fused debris moves against its orbit; hostile silhouettes appear | “Instead, the wreckage began to move.” |
| 24-30 s | Pull back to the mothership and glowing habitation modules | “Those who remained built a home among the stars.” |
| 30-35 s | A protected seed inside a small lit greenhouse | “And kept one promise alive: someday, we would return.” |
| 35-40 s | Collector ship leaves its berth toward the debris field | “Collector, bring back what we need. Help us find the way home.” |

Suggested palette progression: muted Earth tones -> cold discarded metal -> contamination accent -> warm colony windows -> a restrained living-green seed accent. Use the established game palette where it already defines gameplay meaning.

Animation can be limited to parallax layers, light flicker, gentle ship translation and crossfades. All text stays inside the CRT-safe region. Short title cards do not obscure gameplay or require reading a paragraph during a fight.

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

Use the existing planned ending sequence as a small, hopeful payoff:

1. The final threat falls; the immediate route is safe.
2. Return to a wide view of the colony and the damaged planet below.
3. A restoration shuttle descends carrying the protected seed.
4. A small seedling appears in prepared soil. Fade to a message that recovery has begun.

Original ending narration draft:

> “We could not undo what we had left behind. But we could choose what came next. A cleared path. A seed in the soil. A beginning.”

Do not show the whole planet becoming green instantly. The victory is the first successful restoration mission, with continued collection and care still necessary.

Stats/result handling must still follow the gameplay contract: final-boss death resolves once, no currency farming during the ending, and New Run begins with fresh progression.

## 8. Trailer outline: 90 seconds

This fits the project's existing 1-2 minute trailer target. It is separate from the required 3-5 minute gameplay demonstration video. Use original story panels plus captured real gameplay; do not imply scripted concept footage is already playable.

| Time | Picture/edit | Audio/text purpose |
|---|---|---|
| 0-8 s | Damaged Earth and abandoned orbital machinery | Quiet opening; “What we leave behind does not disappear.” |
| 8-16 s | Cleanup attempt; hostile debris wakes | Rising sound; “Our last attempt to clear the sky changed it.” |
| 16-26 s | Mothership and inhabited colony reveal, then pilot ship | “Now, this is home.” Show human survival clearly |
| 26-38 s | Real flight, shooting, destruction and collection | Establish readable core action; caption “Recover” |
| 38-48 s | Actual scrap-triggered field card, then upgraded effect | Caption “Adapt in the field”; show one complete readable choice |
| 48-59 s | Return meter ready -> return -> colony arrival | Caption “Make it home”; do not demonstrate returning with broken shield |
| 59-69 s | Paid repair quote/confirmation and one real skill purchase | Show wallet deduction and resulting change; caption “Rebuild” |
| 69-80 s | Portal/mode cuts, then an implemented boss threat | Escalate action; no invented final boss design or unavailable feature claim |
| 80-86 s | Seed motif and the ship facing the planet | “Clear a path. Give tomorrow a chance.” |
| 86-90 s | Working title placeholder, team/competition card as finalized | Clean ending; compose to loop into the orbital opening |

Gameplay should remain visible long enough to understand cause and effect. Avoid filling the trailer with text, cutscene panels or unreadable rapid UI cuts.

For an early trailer before the full design is implemented, replace unavailable gameplay sections with truthful existing footage and shorten the edit within the required duration. Concept panels may show world/lore, but cannot substitute for proof that a mechanic works.

## 9. Asset and production handoff

Planned materials: seven intro illustrations, four ending illustrations, existing colony/gameplay footage, optional narration, original/properly licensed music and transition sounds. Reuse visual elements across intro and trailer rather than demanding separate cinematic assets.

For each final asset record source/license, creator/tool, exact prompt if generated, date and edits in assets/ASSETS.md when asset production is authorized. This context session adds no asset files or provenance claims.

Example original visual direction, not an instruction to generate now:

“Wide view of a human orbital settlement above a damaged planet, connected habitation modules with warm window lights, a central salvage mothership and a small collection ship, restrained industrial science-fiction illustration, readable silhouettes, quiet hopeful mood, room for a short lower caption.”

Final format, resolution and typography follow ui-rules.md and the actual capture/export workflow. Captions remain legible without narration; music never masks essential spoken lines.

## 10. Decisions still open

- Final title and whether working names Bayanihan Dock/World Tree remain.
- Final boss identities, appearances and exact connection to the contamination source.
- Narration voice/language and whether the intro uses voice or captions only.
- Exact illustration treatment and approved visual samples.
- Whether the intro plays once per launch or on first Campaign entry; preserve Start -> difficulty -> hub as the playable entry sequence.
- Which completed modes/features can truthfully appear in the recorded trailer.

This brief supplies an original draft ready for review, while the existing story remains the source of the game's premise.
