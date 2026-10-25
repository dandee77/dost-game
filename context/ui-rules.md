# UI Rules

## Compact automatic-ability HUD — Q45 confirmed, 25 October

Show one compact icon for each owned automatic/persistent ability, including the rank-1 starter Deflector. Use the 19-entry target catalog, not the 18-entry manual prototype or all 34 field cards. Numeric/pattern attributes, Luck, weapon tiers and world portals are not ability cooldown icons. Filter owned entries in stable target-catalog order; acquisition may insert a new entry, but cooldown changes never reorder icons. No locked/unowned placeholders or earned rank/army cap.

Icons are read-only combat information: no casting, manual selection, intercepted Shoot/mouse aim or Q/Space skill prompts. Full names, exact rank/effect and detailed timers belong in paused build details using the same owner snapshot. Each icon has a rank badge; abbreviate large display values while retaining exact values in details, never clamp actual ranks.

| State | Combat presentation | Meaning / source |
|---|---|---|
| Cooldown debt > 0 | Dimming/radial mask and remaining seconds rounded upward | Real combat-time debt; mask denominator is cooldown captured at activation, not new-rank tuning |
| Timed effect active | Steady active border plus any actual cooldown debt | Active and cooldown can coexist; no display-induced reset |
| Debt zero, timed effect inactive | RDY | Waiting for its valid target/trigger, not a promise of a current hittable enemy |
| Active window open after debt reaches zero | ACT | No duplicate overlapping cast merely because cooldown is zero |
| Persistent Laser Rings | ON plus rank | No invented cooldown/despawn |
| Deflector | ON/OFF; real reboot debt when applicable | One authoritative shield; main shield HUD owns points/overcharge |
| Combat Drone | Living/earned slots and rebuilding indicator | No universal army cooldown; paused details show individual destroyed-slot timers |
| Blink protection active | Active border plus actual Blink cooldown | Guard and cooldown separate; failed safe-point searches spend neither |
| Return protection/combat suspension | Preserve state and dim action status | No hidden ticking, free activation or cooldown refund |

Display-only ceil must not mutate a positive float debt into zero. Missing/invalid timing metadata shows a neutral unknown marker, never invented RDY. Drawing reads snapshots only: no targeting, RNG, lock refresh, cast, shield refill or droid rebuild.

Authored logical-canvas defaults, to be added to Theme: origin (220,1500), ten columns, cell pitch 128, icon 96 square centered in the cell, rank/state labels with existing readable caption styling. All 19 fit two rows within x 220..1500 and y 1500..1756, above the named boss-bar region near y 1900 and away from upper resource HUD. Keep complete tile/text bounds inside the safe area; compose tips/captions/panels around required HUD. Apply the canvas transform once, not world-camera scaling. All presets preserve information; optional glow may be reduced.

Teammate art instructions: consistent original pictograms, square transparent 96x96 PNGs if new raster icons are produced; register actual files/provenance later. No images generated here. Missing art uses these unique glyphs on simple tiles; fallback is not final artwork.

| Ability | Fallback glyph | Pictogram direction |
|---|---|---|
| Scrap Magnet | SM | Magnet drawing scrap |
| Repulsor Pulse | RP | Outward circular pulse |
| Deflector Shield | DS | Closed shield |
| Radiant Halo | RH | Bright corona |
| Corrosive Trail | CT | Droplet and trail |
| Point-Defense Interceptor | PI | Shot stopped at boundary |
| Laser Rings | LR | Orbiting blade |
| Lightning Ring | LT | Ring and bolt |
| Chain Lightning | CL | Linked lightning nodes |
| Combat Drone | CD | Small companion craft |
| Shield Detonation | SD | Broken shield and burst |
| Plasma Beam | PB | Focused beam |
| Hologram Clone | HC | Paired ship silhouettes |
| Realm Breaker | RB | Split rift |
| Nuclear Missile | NM | Generic warhead and burst |
| Singularity | SG | Inward spiral |
| Space Collapse | SC | Folding tiles |
| Armageddon | AR | Cluster of impacts |
| Blink Drive | BD | Offset ship and motion gap |

Pause/cards/console/focus and station visits preserve actual timers/ranks. Show icons only over their displayed combat arena, not hub/map/story/results. New Run clears old ownership/timers, then shows the real starter state. Resume/new encounter cannot reset debt through UI. Reuse SkillSystem level/cooldown/isActive/drawStatus and Game's HUD pass; accurate shield/droid read-only data still needs integration. No independent HUD timers/singleton. Source still draws selected-Q prototype text, not this 19-icon target.

Later acceptance: starter-only/all-19/stable-order HUD; 0.01 s debt displays 1 without becoming ready; ready/no-target and active/debt-zero distinctions; rank purchase preserves mask denominator/debt; persistent shield/rings and independent rebuilds; pause/focus/return/reset; no click-to-cast/input theft; art fallback; all presets/window scales. Inspect real crowded layout/readability later. Written specification only; no icon art, snapshot API, renderer or playtest delivered.

## Floating damage numbers — Q44 confirmed, 25 October

Show floating numbers for all positive resolved player-owned damage to hostile enemies/bosses and existing HP-based combat obstacles: primary shots, supported secondary/signature damage, automatic abilities, droids/clone and damage-over-time ticks. Ordinary hits remain visible, not only critical hits or bosses. Misses, blocked/immune zero-damage events, cleanup/despawn and objects without a numerical damage model produce no invented damage number. Player incoming damage retains its existing hull/shield/HUD feedback; this contract covers outgoing combat numbers.

Use actual damage applied to that target, after its damage rules and limited to the health removed, not raw attack power or overkill. A 12-damage hit removing a target's final 5 HP contributes 5. A lethal hit still creates its number at the saved impact position; the popup owns its position/value and must not dereference a removed enemy. Game's authoritative resolved-hit path emits the cosmetic fact once; duplicate callbacks cannot award a second amount. The display never deals damage, grants loot/score, changes critical rolls or advances signature counters.

Critical styling uses the attack's resolved critical tier, including the existing tiers above 100% rating. Ordinary amounts use the existing light text color; critical amounts use the existing accent color plus a textual CRIT marker so color is not the only cue. Tier one may show `24 CRIT`; higher tiers show a compact explicit tier, e.g. `36 CRIT2`. Amount is the already-resolved damage, not multiplied again for display. Never infer a critical from damage equaling a maximum roll; a strong normal hit is still normal. Abilities without an authored critical rule retain ordinary styling.

At ordinary rates, show each resolved hit promptly. Rapid hits may accumulate into the same visible number only for the same stable target ID and same critical tier within a short fixed cosmetic bucket. The first hit displays immediately; later matching hits update its exact stored sum. Never merge different enemies or merge normal damage into a critical label. The bucket uses `[firstHit, firstHit + window)`: a hit exactly at the end starts a new bucket. Its boundary is not extended by every hit. Keep full precision internally and round only the final displayed text; positive sub-unit damage must not become a false zero. Use an explicit `<0.1` display below that precision. Actual hit/critical/proc/reward calculations remain separate from cosmetic grouping.

| Planned Theme token / existing UI rule | Authored default | Purpose |
|---|---|---|
| DAMAGE_NUMBER_BUCKET | 0.1 combat seconds | Same-target/same-tier aggregation window, first hit visible immediately |
| DAMAGE_NUMBER_LIFETIME | 1.5 combat seconds | Preserve the prototype lifetime; starts at first hit and is not refreshed by bucket additions |
| TEXT_WORLD_DAMAGE | Existing UI-rule size 4 world units | Use world-space font size once; source still has the literal until Theme migration |
| Normal / critical color | Existing COLOR_TEXT / COLOR_ACCENT | Textual critical tier also distinguishes outcomes |

Draw through existing DamageIndicatorManager world-space rendering, above impact sprites but clear of mandatory telegraphs, overhead HP bars, HUD and captions. Use saved impact anchors, readable offsets and deterministic/isolated cosmetic drift; cosmetic motion cannot consume encounter/loot/card/critical RNG. Theme owns lifetime/window/font/motion/style constants when implemented. All presets retain ordinary and critical feedback; reduce decoration or coalesce same-target/same-tier cosmetic output under load rather than hide normal hits. Exact extreme-load rendering budgets remain PREP-14/T10, not a claim that arbitrarily many separate texts fit every machine.

Only running combat advances bucket age, drift/fade and lifetime with frame time. Pause/cards/console/hub freeze these clocks; do not show a suspended field's numbers over hub/map/story/results. New run/reset and retiring an arena clear its cosmetic buckets/indicators; reset cannot preserve stale IDs or delayed totals. No popup may change terminal results or continue allocating from an abandoned encounter.

Current baseline is partial: DamageIndicatorManager/Indicator already exist, Game calls their reset/update/draw and several hit paths add integer values. Equipment damage uses actual HP removed, while the legacy bullet popup passes raw damage; the constructor styles by `damage >= maxDamage`, not explicit critical metadata. Bucket grouping, fractional values and consistent authoritative-hit coverage are future work. Extend these existing owners rather than adding another popup manager. Written acceptance: ordinary and critical single hits, 12 into 5 HP -> 5, same-target tier-zero 3+4 -> 7, different target/tier separation, lethal cleanup, small fractional totals, pause/reset, all presets and dense continuous-fire readability. No source fix or runtime visual test is delivered here.

## Damaged normal-enemy health bars — Q43 confirmed, 25 October

Show a small overhead health bar for every visible living normal enemy with `0 < currentHP < maxHP`. Include basic/ranged/heavy enemies and normal boss-owned adds; spawning at full HP shows no bar. Successful damage reveals the bar as soon as the enemy remains alive below maximum. No timeout: keep it while damaged, hide immediately on full healing, death/despawn or leaving view, and restore it on re-entry if still damaged. Damage rejected by immunity or dealing zero cannot reveal a full-health enemy's bar. Pause freezes underlying HP and retains the same visible bars; a new run cannot inherit bars/HP snapshots. Only the displayed combat arena supplies these bars; do not draw a suspended field's bars over hub/map/story/result panels.

Use each entity's actual spawn-scaled maximum HP, captured after its final spawn tuning, rather than its untuned archetype base or highest recently observed health. If a future mechanic explicitly changes maximum HP, update the authoritative maximum and derive the display from that same state. Presentation cannot heal, recalculate difficulty/HP, change targeting or create an enemy shield/armor statistic. Current source has inherited current health; Enemy's maximum-health/getter is a planned addition, not an API already delivered here.

Bars show a simple current/max fill ratio, clamped for drawing only; no name, numeric HP text, boss phase marker, hit-timer fade or decorative animation. Keep the named boss HUD with actual numbers/phases; bosses do not also get this ordinary overhead bar. Player/drone bars keep their separate rules. Debris, barricade formation segments, pickups, scenery and friendly colony traffic do not acquire normal-enemy bars from this decision.

Project the top-center of the rendered enemy bounds once into screen space and draw a horizontal bar above it, without sprite rotation or double camera scaling. Keep it anchored to that entity; no off-screen arrows or clamping an off-screen enemy's bar to the screen edge. Clip to the combat viewport and respect HUD/panel masks. Do not obscure mandatory telegraphs, captions or interaction errors. Do not add remote enemy detection or a target-selection system just to draw health.

Authored presentation defaults, to be added to Theme during implementation:

| Planned Theme token | Logical canvas pixels / value | Purpose |
|---|---|---|
| NORMAL_ENEMY_HP_WIDTH | 100 | Fixed readable screen-space width |
| NORMAL_ENEMY_HP_HEIGHT | 12 | Total bar height including border |
| NORMAL_ENEMY_HP_GAP | 12 | Gap above projected sprite top |
| NORMAL_ENEMY_HP_BORDER | 2 | Border inset; fill uses remaining interior |
| Track / fill / border | Existing COLOR_PANEL / COLOR_DANGER / COLOR_TEXT_MUTED | Distinguish remaining HP without extra palette/assets |

Use the current logical-canvas transform at each window size; these are not world-unit dimensions. Every Low/Medium/High preset retains these required bars with the same health information, not a particle budget or an optional enemy-count cap. In overlaps, draw farther enemies first and nearer enemies last, with stable entity ID ties; preserve each bar's true anchor rather than merging unrelated health. Use viewport/spatial culling and simple primitives; no per-frame texture/font allocation or logging. Crowded readability/performance still needs runtime validation.

Later acceptance: full enemy hidden; nonlethal hit shows correct fraction; lethal first hit never leaves a detached bar; paused damage/HP cannot advance; off-screen/re-entry preserves real fraction; healing to full hides; different spawn-scaled HP yields correct denominator; boss adds obey normal rules while bosses retain named bars; restart clears old entities; all presets/window scales retain the information. Example: a spawned 50-HP enemy at 25 HP shows half fill; a scaled 100-HP enemy at 25 shows quarter fill. Written target only; no renderer or HP storage code is implemented here.

**25 October Q42 narration captions:** Show English captions for all speech, including narration over moving scenes and muted playback. A matching story card serves as its caption while visible; otherwise one compact block, at most two wrapped lines, inside the existing CRT-safe area with readable body font/high-contrast backing. Keep clear of action/HUD/Skip hint; split cues rather than shrink text. Pause/focus freezes the cue, Resume restores it, and skip/advance/exit clears it with its voice clip. [Full contract](../todo/01-story/story-context.md#complete-narration-captions--q42-confirmed-25-october) supplies timing/fallback/export rules. Written UI target only; no renderer/export delivered.

**25 October Q38 mandatory cards:** Nonempty upgrade panels require an explicit valid card pick; no Skip, timer auto-pick, cash replacement or dismiss-to-combat. One remaining option still requires confirmation. Show pending-choice count; freeze combat behind the panel. Pause/focus Resume restores that same offer. Consume selection and transition inputs so they cannot activate another card, shoot or enter a portal. Allow existing confirmed abandonment; no banked picks. [Queue/input contract](../todo/07-upgrade-proposals/automatic-skills-and-rarities.md#4-proposed-field-offer-weighting) applies; exact empty-pool recovery and runtime validation remain open.

**25 October player-entered Cadet name:** After difficulty, show a name field in the existing menu flow, then Continue/Back. Normalize to the existing 3-12-character A-Z/0-9/space format; require a valid name and display Cadet separately. Consume confirmation input and preserve the draft on Back. Hub/briefings/results use Cadet {name}; leaderboard name uses the captured name alone. Results offer Submit Result/leave-unsaved confirmation, without another name entry or alias edit. Safe-area/font/button constants stay in Theme. See [identity contract](../todo/01-story/player-identity.md).

**25 October result/leaderboard contract:** Use [current rules](../todo/02-gameplay/results-and-leaderboards.md): immutable results, visible outcome/eligibility, score and active time, Boss clears/Campaign progress, safe name entry and Saved/Retry state. Name/confirm/skip/back consume input once; ending skip cannot submit twice. Four-mode/difficulty board filters show current-rules top 10, latest run highlight and no mixed-rule comparison. Keep within established safe area and readable row style; paginate rather than shrink text. A failed save preserves the frozen result; unsupported/corrupt-file status must not imply a successful save. No online account/login or extra scene beyond existing planned boundaries.

**24 October Q25 Boss station retirement:** Boss station also shows Retire Run. Preview score, bosses cleared and active time, then Confirm/Cancel. Distinguish completed bosses from the upcoming automatic encounter; confirmation cannot count/start that pending boss. Results show Retired with the same earned fields and one eligible save, not Victory/Defeated. No station retirement controls appear during combat or after mutual destruction. Swarm/Chaos retirement remains unchanged.

**24 October automatic Boss sequence UI:** Station/launch preview shows upcoming boss name, encounter ordinal and cycle from authoritative run state. Use Launch/Cancel; no boss picker, next/random buttons or auto-launch timer. Cancel leaves the same upcoming boss. Repeating to Shellback after Nestheart is visibly the next encounter, not a new run or victory. An unavailable encounter gives a clear launch error without advancing or charging. Mutual destruction still ends the run without station/next-boss controls.

**24 October mutual destruction result:** Q19/Q20 count a same-step boss kill even if the player dies, then end the run. Show **Mutual Destruction - Boss Cleared**, credited boss count, score/time and actual objective completion. Do not show Resume/Enter Station/Next Boss for the destroyed ship. If all final objectives resolved in that step, show Campaign completion and permit its frozen-result ending; otherwise do not imply final victory. Ordinary deaths remain Defeated. Results and ending never grant another reward or revive the player.

**24 October Q18 tutorial:** Use short, skippable in-play tips, not a practice screen. Follow the [adopted copy/trigger/input contract](../todo/00-planning/decisions-and-gaps.md#6-in-play-tutorial---q18-confirmed-24-october). One passive tip within the safe area, clear of HUD and telegraphs; no combat pause/input capture. Mandatory panels suppress tips. Skip Tips is available in safe hub/pause panels; pause Help exposes Hide/Show Tips. Dismissal consumes its own input. Required blockers/errors remain visible even when optional tips are hidden. No new hotkey, combat voice or scene is required.

**Primary-fire/retirement UI:** Fresh-run help shows Hold Shoot / E: Auto-fire (OFF initially). Preserve the selected toggle across same-run panels/station visits; UI input never leaks into firing. Swarm/Chaos station UI has Retire Run, score/time preview and Confirm/Cancel. Results label voluntary station completion **Retired**, display both score and active survival time, and permit eligible name entry once. Do not label it Defeated/Victory or give retirement bonuses.

**Trailer voice consistency:** Owner confirmed the same original English AI narrator for intro/ending/trailer. Use one voice profile, consistent pronunciation and measured clip timing; retain readable story cards and existing export duration targets. Production follows the [voice contract](../todo/08-review/owner-questionnaire.md).

**24 October background production/checkpoint UI:** [Written background brief](../todo/09-art/background-brief.md) is for the teammate to produce; no images are generated in this checkpoint. After a Campaign normal clear and earned cards, show **Enter Station** and **Next Wave** (or **Stage Boss**), with current hull/shield/wallet and paid-service reminder. No auto travel/countdown. These station entries show no shield/energy lock. After non-final level clear, show station or next-level map; map Cancel returns to its originating checkpoint/hub. Consume each action once; focus pause preserves pending choice. Final victory and Boss-mode portal rules remain separate.

**Campaign duration copy:** Call each map circle a Level in player-facing copy; Stage remains a technical synonym. Node previews show estimated active combat time for the selected level and difficulty, including its boss, using game-design.md. Do not show a whole-route estimate as that level's duration or render a countdown implying automatic clear/defeat. Base, shopping, cards and pause do not consume the estimate; faster clears remain valid.

**24 October beta Campaign map:** Display C01 -> C02/C03 -> C04. C01 unlocks both middle levels; either middle clear unlocks C04, and other unlocked, unfinished levels remain available. Three or four levels may be completed before the ending. Remove the exclusive-route-lock label. Previews show counts (5/3/3/4), separate boss and per-level duration; cancel is harmless. Use the [beta stage contract](../todo/02-gameplay/campaign-stages.md).

**24 October confirmed Settings/result controls:** Focus loss pauses; focus regain requires explicit Resume. Preserve underlying panels/transactions/offers and consume the refocus click. Settings shares three Master/Music/SFX-Voice sliders and Low/Medium/High quality, **Medium default**, across menu/pause. Audio/graphics save locally across launches; preview live and show save failures without blocking play. Swarm/Chaos show score and survival time; score determines rank. Credits use marked placeholders until names are supplied. Intro/ending now require original AI English narration alongside readable text. See [owner questionnaire](../todo/08-review/owner-questionnaire.md).

### Beta graphics preset presentation

| Preset | CRT/barrel passes | Cosmetic particle/flash/trail draw budget | Gameplay/UI |
|---|---|---|---|
| Low | Bypass effect passes; show the scene directly | One quarter of existing full-quality cosmetic budget | Same logical canvas, camera, input, telegraphs, sprites, boss bars and required UI |
| Medium - default | Enabled | Half of existing full-quality cosmetic budget | Same gameplay and required UI |
| High | Enabled | Existing full-quality cosmetic budget | Same gameplay and required UI |

Ratios are delegated beta rendering defaults and belong in Config during implementation. They apply to presentation-only feedback, not damaging pools, projectile collisions, drones, enemies or attack events. Never reduce actual earned counts or rewards. Preserve the existing logical canvas and mouse transforms; no internal-resolution scaling is required for this beta policy. Decorative suppression uses isolated cosmetic state and cannot advance loot/card/encounter RNG differently. Apply changes between frames, with existing renderer ownership and cleanup; changing quality cannot restart a run. Profile all presets before claiming supported hardware or FPS.

## Campaign star-field map and four-mode selection — target

Show Swarm, Chaos, Boss and Campaign; remove Survival. Entering the base Campaign portal opens a map panel before combat. Circular stage nodes connected by route lines represent whole stages, not individual waves. Stage 1 starts available; clearing a predecessor unlocks connected successors for the current run. A selected available node shows details and a Launch action; Cancel returns to base. The image reference does not add a three-star rating system. The four-node beta map uses run-local locked/available/current/cleared states plus route-unavailable reasons, readable identity, normal-wave count and a separate final boss. Beta has no required miniboss; later expansion may add them. Base departure says Next Wave or Stage Boss as appropriate. Clear transit grants no free repair. Keep map/panels in the established safe area and existing Game lifecycle; no map art/runtime is delivered by this context change.

## Current boss and portal HUD contract — target, not implemented

Show a named HP bar whenever a boss appears, with current/max HP and phase markers. Multiple Chaos bosses need individually identifiable compact bars and a safe-area overflow view; never combine their health into one misleading total. Phase thresholds and attack tuning come from game-design.md. Unique encounter IDs distinguish repeated boss types.

Ordinary portals show F, Shield Offline or the deficit to fixed 500 energy as appropriate. Boss mode shows no retreat prompt during a fight; its post-kill portal never displays a shield/energy lock. Consume the interaction once. Label hub re-entry **Return to Battle**, distinct from pause **Resume**; Boss-mode departure starts the next encounter. Show the two-second re-entry protection clearly, with auto-fire/offensive automatic skills waiting until it expires and deliberate Shoot ending it.

Battery previews show current shield -> resulting shield, charge supplied, old excess replaced, normal regeneration cap, price and wallet afterward. A smaller battery may reduce total shield; show that result before purchase. Repair previews retain exact proportional healing and never promise free replenishment.

## 23 October repair/shop feedback

Show Full Repair and Repair What I Can Afford at the berth with the quoted deficit, exact restored HP, cost and wallet afterward. Partial payment restores the same fraction of missing HP; retain fractional values instead of displaying a paid zero gain. Shield Battery is a separate shop purchase used immediately, distinct from Power Cell salvage. Disable purchase when nothing can be restored, and commit debit/effect together after validation. This is a design contract; no screen is implemented by this documentation.

## 21 October upgrade review UI — proposed, not implemented

The [upgrade review](../todo/07-upgrade-proposals/README.md) adds a mothership weapon tree and quarter-strength numeric attributes. Show current parent/branch/tier, exact next effect/price, remaining wallet and the run-long branch lock before purchase. Five tiers refer to equipment progression, not the rarity color of a skill card. Disable sibling branches with a readable reason; do not advertise an unavailable weapon profile as finished.

Attribute previews show full-card versus purchased gain and preserve fractional capacity/+percentage-point meaning. Deflector remains a field card; shop capacity does not display a full ability-rank gain. Discrete shot/direction/piercing cards do not offer fractional purchases. Luck is proposed visible in workshop details, absent from the permanent combat HUD; describe trade quality within existing ranges, not a new item-drop table.

Blink's card is Legendary and automatic. Its status shows readiness/cooldown and a separate short protected window; no manual Blink button. Failure to find a safe destination cannot display a successful rescue. Other rarity assignments and weights remain review proposals. Reuse established UI/theme ownership; no new asset, color constant or rendered interface is created by this context update.

## 21 October narrative and material presentation

Use **H.O.P.E. Colony** on arrival/story cards and **HOPE** where space is limited. Full expansion: **Habitat for Orbital Preservation and Endurance**. The player stays in the ship; show reused inhabited station modules, safe service approaches and Earth beyond. No special-tree/seed quest art or radiation-origin imagery is required. Source shutdown and survey/containment craft replace the old ending motif. The latest creature origin is biological: an altered waste-eater moves inside a shell formed by binding indiscriminately collected fragments around its body. Retain the accepted canister/appliance/metal-cluster silhouettes; the bulk of each visible enemy can be nonliving external armor concealing the organism. A later story close-up can show fibrous joins and gathering behavior without requiring a sprite redesign or new armor mechanic. Future narrative shots establish benign organisms before exposure, then altered movement and protected orbital cores. Preserve accepted enemy/debris art in this context-only session; organic seams or core reveals are later art-direction proposals, not replacement assets required now. Detailed motion beats and playback rules: [story context](../todo/01-story/story-context.md).

The four owner-selected [scrap labels](../todo/03-economy/scrap-types.md)—Metal Fragments, Circuit Parts, Polymer Pieces and Power Cells—share the same trade/salvage accounting. Do not add four HUD meters, material-specific prices or compulsory new pickup art. Mixed bundles use Mixed Salvage. Preserve accepted destruction frames and red glow pickups; future icons distinguish shape as well as color. The main combat readout remains Trade Scrap, Salvage progress, shield and Return Home readiness. Source-isolation notices must not hide required surviving-hostile counts.

## 20 October target screens (design only)

See [todo/02-gameplay/gameplay.md](../todo/02-gameplay/gameplay.md) sections 3-5 and 9-11 for behavior. These targets supersede conflicting old screen descriptions below; they do not describe newly shipped UI.

| Surface | Target |
|---|---|
| S-03 Main menu | Start Game -> difficulty; retain shared minimal Settings access; modes chosen in hub |
| S-12 Difficulty | Easy/Hard/Impossible, effects summary, explicit Confirm and Back |
| S-13 Colony hub | Same pilot ship, safe navigation, visible inhabited colony, mothership, repair berth, shop and five labeled portals |
| S-14 Portal preview | Objective, mode/difficulty, ending condition, Launch/Resume; crossing radius alone never launches |
| S-04 Field HUD | Wallet and level progress at top center; distinct portal-energy meter/50% tick/nearby F/block reason; hull/shield, objective/timer, MENU |
| S-05 Field cards | NEW/UPGRADE, real changing stats, automatic/persistent tags; triggered by scrap, not wave clear or elapsed time |
| S-06 Skill shop | Upgrade Owned and Rare Offers, shared card-stat preview, rank, price, Buy/disabled reason, sold and empty-stock states |
| S-07 Pause | Resume/Settings/Quit to Main Menu with confirmation; resumes to original hub/field state |
| Repair | Hull, affordable hull patch, shield or combined service; exact restoration/cost/post-purchase balance before confirmation; visible 3-second progress; no free repair |

Mode portals are Swarm, Survival, Boss, Chaos and Campaign. Use names/shapes as well as color. The colony background should show human habitation without walking characters or an NPC-dialogue system. Use existing textures and shapes until assets are supplied; this session creates no assets.

Normal field upgrades remain free. Shop inventory/prices are selected under the owner's delegation; paid repairs use the same wallet. Label currency “Trade Scrap” and progression “Salvage”; show separate aggregated gain feedback, e.g. “+3 Scrap / +2 Salvage”, with clear tutorial copy explaining both. Lifetime collected means trade earned, not available wallet. Return Home cannot say Ready while shield is offline. Meter maximum visibly increases with player level.

Repair UI disables unaffordable/full components, offers an affordable hull patch when appropriate, and always allows Undock/Resume. Paid Reinforced Hull previews say “Maximum HP only; repair sold separately”; field-card previews retain the actual max/current HP effect. If a fixed rare offer is later learned through a field card, label it Owned and disable acquisition rather than rerolling or double-selling it.

Intro/trailer treatment is in [todo/01-story/story-context.md](../todo/01-story/story-context.md): a short story-text card clears, then its animated scene/gameplay clip plays; repeat with trailer pacing. Use the same safe area/type constraints. Required story sentences belong on their own beats, not continuously over combat. Footage needs moving action; narration is optional. No new art is generated in this documentation session.

Preserve existing 3840x2160 canvas, 1280x720 initial window, CRT-safe regions, mapped mouse input, Button style and Theme tokens. No UI text at the cropped screen edge. Keep accepted red debris glow and complete destruction art. Selected field return portals replace the planned Q Return Home ability. F interacts inside a return portal or at hub services, with frame input consumed at transitions; E retains auto-fire. Portal pointer appears only within the selected detection radius (roughly one visible screen); broken-shield portals remain visible with Shield Offline. Do not present a manual skill slot.

How everything on screen is drawn: the canvas and safe area, the two coordinate spaces, fonts, colors, sizes, layout, sprites and screens. This file replaces three web files: **ui-rules** (how to compose screens), **ui-tokens** (now the `Theme.hpp` header, defined at the end of this file) and the visual half of **ui-registry** (sprite and asset tables).

Why tokens became a header: in C++ the values must live in code. Writing them in two places (a doc and a header) guarantees drift, so `src/Theme.hpp` is the single source of truth after item 03 creates it. This file explains what each token is for.

---

## Canvas and Window

P5.1 (18 October): existing card stack now mixes passive and ability upgrades. Ability cards show the name, AUTO/Q activation, uncapped resulting level, and a growth summary. Titles/descriptions fit the card's inner width, including Point-Defense Interceptor. The selected Q HUD includes earned level. Drones draw separate markers with real-health bars; collapse zones and rift dimensions use the same cast-level tuning as collisions, with physical size stopping at level 5. Layout/font/health-bar constants remain in Theme.

P5 (17 October): skill effects use existing player/shot art plus simple world-space outlines, arcs and a translucent rift. No asset generation. Selected manual skill/Q prompt and cooldown appear at Theme::SKILL_STATUS_POSITION (220,470), below the scrap readout and inside the CRT safe area. Automatic effects can coexist; F5/autocomplete exposes their state without adding acquisition UI. Clone uses the existing ship sprite tinted sky blue; drone uses a small outlined marker.

15 October unique destruction update: each DebrisKind selects its own 768 x 96 destruction sheet (eight 96px frames) through DebrisInfo::destructTexture. Keep the accepted clump sheet; nine new sheets preserve each variant's shape and break into matching pipe sections, panels, cables, shell plates or struts. Theme::DEBRIS_SCRAP_VISUALS stores each sheet's measured final-fleck coordinates: clump 4 selected exits, pipe 3, wing 10, canister 5, dish 5, coil 4, tank 11, thruster 7, beam 11, hull 15. Small/medium/large orb diameters remain 1.25/1.8/2.5 units. Whole frames play at 0.075 s/frame; at 0.525 s the saved positions become real soft red glow textures, holding 0.05 s before homing. SCRAP stays at (220,390). Red collectible glow remains an explicit user palette override. No runtime sprite slicing.

P3 event UI: sky-blue BARRICADE countdown and the existing camera/orbit behavior. The 15 October follow-up restores the original legacy asteroid sprite and seven-frame breakup. Keys: barricade_asteroid and barricade_asteroid_destruct. The 96px transparent frame has its original centered rock; padded draw sizes are 15/25/30 units for small/medium/large. Each rock receives a random initial angle and stable 5-240 degrees/s spin. Breakup runs at 0.075 s/frame with no collectible particles or scrap reward. Cosmetic death uses the same simulation clock/reset path as debris effects; it does not enter harvesting.

14 October reskin (destruction playback restored in the 15 October correction): muted lavender-gray plates, dented canister, broken panel, bent pipe and wiring replace the debris art. Preserve 96 x 96 transparent frames and the roughly 36-pixel centered body. Destruction now has eight horizontal frames (768 x 96), ending fully transparent, at 0.075 seconds per frame after the 15 October speed tuning. `Theme::FRAMES_DEBRIS_DESTRUCT` applies to normal debris. Original seven-frame sheet and intact sprite under `assets/textures/legacy/` are reused by barricades after the 15 October restoration. User's explicit eight-frame request supersedes the old seven-frame asset constraint.

| Item | Value | Where |
|---|---|---|
| Virtual canvas | 3840 x 2160 | `GAME_SCREEN_WIDTH`, `GAME_SCREEN_HEIGHT` (moving to `Config.hpp`) |
| Initial window | 1280 x 720, resizable, VSync hint | `Application::Application` |
| Target FPS | 60 | `SetTargetFPS(60)` |
| Scaling | Uniform scale to fit the window, letterboxed, bilinear filter on the canvas | `Application::Run` |
| Mouse | Already mapped to canvas coordinates by `SetMouseOffset` / `SetMouseScale` | `Application::Run` |
| Post-processing | CRT shader (curvature, scanlines, vignette, slight color fringe) plus a barrel-distorted border image | `shader.fs`, `barrel_distortion.fs`, texture `border` |

Lay out every screen element in canvas coordinates (3840 x 2160). Never use `GetScreenWidth()` or `GetScreenHeight()` for layout.

### Safe area

The CRT shader scales the image to 92% and curves it, so content near the edges bends and the corners are cut off.

| Zone | Rule |
|---|---|
| Text and buttons | Inside x 200 to 3640, y 150 to 2010 |
| Important HUD (health, timer, boss bar) | Inside x 220 to 3620, y 150 to 2000 |
| Corners (within 300 px of both edges) | Decoration only, never text |
| World-space gameplay | No restriction; the camera keeps the player centered |

The current HUD already respects this: the kill counter sits at (220, 220), the timer at y 150, the health bar ends at x 3640.

---

## Two Coordinate Spaces

P3 follow-up: `hitbox` and `stats` independently toggle world collision geometry and canvas diagnostics. Stats adds event phase, remaining seconds, live segment count, radius, orbital speed and automatic-trigger state; its expanded panel remains within the safe area. Console background opacity is 0.92 and dropdown opacity 0.95. The stats panel keeps its existing separate 0.25 opacity.

P2 console suggestions: draw a separate vertical dropdown immediately below the input. Show six rows at most, a range/count, and a highlighted keyboard selection. Up/Down and PageUp/PageDown keep the selected row visible. All five shield choices fit together. Theme owns row count, dimensions and opacity; the maximum panel bottom remains inside the canvas safe area. Ctrl+Up/Down preserves command-history navigation.

P2 enemy layering: Animator draws WORLD then FLYING; mid-level ships and their destruction effects use FLYING so low-level crowd sprites never cover them. This changes draw order only, preserving their flight and overlap behavior.

| Draw in | When | Units | Examples |
|---|---|---|---|
| **World space** (between `BeginMode2D(utils::gameCamera)` and `EndMode2D()`) | The object exists in the game world and moves with the camera | World units; camera zoom 20 means 1 unit = 20 canvas px | Ships, bullets, scrap, dock, debris, damage numbers, boss telegraph rings |
| **Screen space** (after `EndMode2D()`) | The element is fixed on screen | Canvas px | HUD, cards, shop, menus, pause, game over, dock arrow |

Font sizes follow the space: damage numbers are 4 units tall in world space (80 canvas px on screen); HUD text is 80 px in screen space. A screen-space size used in world space draws 20 times too big.

To place screen UI over a world object, convert with `GetWorldToScreen2D(worldPos, utils::gameCamera)`.

---

## Fonts

| Key | File | Role | Notes |
|---|---|---|---|
| `primary_font` | `assets/fonts/PerfectDOSVGA437.ttf` | Display: titles, numbers, HUD values, card titles, damage numbers | Pixel DOS look |
| `secondary_font` | `assets/fonts/3270-Regular.ttf` | Body: button labels, card descriptions, shop descriptions, cutscene text | Terminal look |

- Both load with `LoadFontEx(path, 126, nullptr, 0)`: glyphs are rasterized at 126 px. Sizes above 126 are upscaled, which suits the pixel style.
- Both font licenses must be confirmed and recorded in `assets/ASSETS.md` before submission. If either cannot be confirmed, replace it with an OFL-licensed pixel font of similar style and keep the same keys.
- Only the default Raylib font is allowed besides these two, and only on the loading screen (it draws before fonts are needed).
- Use `MeasureTextEx` with the same font, size and spacing you draw with when centering.

### Type scale (screen space, canvas px)

| Token | Size | Font | Use | Current example |
|---|---|---|---|---|
| `TEXT_DISPLAY` | 400 | primary | Main menu title | "SPACE / ABLAZE" |
| `TEXT_TITLE` | 200 | primary | Screen titles, wave banner, "PAUSED", "VICTORY" | new |
| `TEXT_BUTTON_LG` | 150 | secondary | Main menu buttons | menu buttons |
| `TEXT_H1` | 120 | primary/secondary | Kill counter, game-over buttons, shop heading | `KillCounter`, Restart |
| `TEXT_CARD_TITLE` | 100 | primary | Augment card titles, boss name | `Card` |
| `TEXT_BODY` | 80 | primary | HUD timer, stats, shop rows | `GameTimer`, game-over stats |
| `TEXT_BODY_SM` | 64 | secondary | Card and upgrade descriptions, cutscene text | `Card` description |
| `TEXT_CAPTION` | 50 | secondary | Hints, footer, "Press Space to skip" | menu footer |
| `TEXT_WORLD_DAMAGE` | 4 (world units) | primary | Damage numbers | `DamageIndicator` |
| `TEXT_WORLD_LABEL` | 5 (world units) | primary | World labels (tutorial, "DOCK") | controls guide |

No other sizes. If a layout needs a new size, add a token first and record why.

Item 04 adds `Theme::DEBUG_TEXT_WORLD_ID = 2` world units for compact debug IDs. Debug text uses `TEXT_CAPTION` (50 canvas pixels). The F5 terminal is `(220, 310, 2000, 720)` with 30-pixel padding and 64-pixel rows, keeping its first text below the cropped corner. Six recent output rows sit above the input and completion hint; overlong lines fit within the panel (input keeps its end visible). Diagnostics occupy `(220, 1060, 1700, 540)` below the console and the invincibility indicator sits at `(220, 1620)`. All tokens live in Theme. Hitboxes use player accent, enemy toxic and debris muted colors; bullets use crosses at their collision points.

---

## Colors

P1 supplied-pack exception (14 October): preserve the user's CC0 pack pixel colors, including green engine/shield effects and gold guard art, for the requested equipment prototypes. This is an explicit asset-integration scope exception to the palette below; do not recolor or replace the supplied files. A final theme reskin remains the separate art track. Runtime PNGs are in `assets/textures/player/`; combined reference sheets and editable files are in `assets/source/player/` with the original license.

P1 sprite layout: hull/engine/effect/weapon layers use 48×48 frames drawn at 12 world units. Shields use 64×64 frames drawn at 16 units, sharing the same center and rotation. Weapon strips have 7 cannon, 12 heavy, 17 rockets, 14 zapper frames; shield strips have 10 front, 6 sides, 12 round and 10 invincibility frames. Engine idle/powering counts: base 3/4, pulse 4/4, burst 7/6, supercharged 4/4. Projectiles are 32×32 frames: cannon 4, heavy 10, rocket 3, zapper 8. Counts derive from sheet width divided by the Theme frame-size tokens; all new sheets are separate assets, with no changes to old sheet dimensions.

The zapper beam crops columns 13–18 of each 32-pixel frame to remove transparent padding, then tiles at 8 world units along the damage capsule. Its visible width matches the 3-unit damage width. Equipment status starts at (2300,350), inside the safe area: weapon/engine, shield capacity or guard state, equipped Space skill cooldown. `hitbox on` outlines beam, directional shield arcs and projectile swept paths/radii. Player-owned sprite timers pause with simulation.

Debug diagnostic text/IDs use 55% opacity, console text 85%, and both panels 25%. World outlines and the invincibility indicator retain normal opacity. The audio status row reports ON or MUTED; use the console's `mute` command to change it.

Semantic colors make the action readable in a 3-second glance and in a trailer.

| Token | Value | Meaning | Use only for |
|---|---|---|---|
| `COLOR_BG` | `BLACK` | Space | Clear color, letterbox |
| `COLOR_TEXT` | `RAYWHITE` | Neutral text | Body text, card text |
| `COLOR_TEXT_MUTED` | `{128,128,128,255}` | Secondary text | Hints, tutorial labels (SA uses this gray) |
| `COLOR_ACCENT` | `SKYBLUE` | The player and the UI | Buttons, player effects, menu title first line, dock beacon |
| `COLOR_DANGER` | `{255,50,50,255}` | Damage and threat | Kill counter (SA), enemy bullets tint, low-health warning, "Killed by" |
| `COLOR_TOXIC` | `{120,255,90,255}` | Contamination | Enemy glow and tint, windup flash, boss attacks telegraph, toxic UI accents |
| `COLOR_SCRAP` | `{255,196,64,255}` | Reward | Scrap pickups, cargo and credit numbers, buy buttons when affordable |
| `COLOR_LIFE` | `{90,200,120,255}` | Restoration, life support, hope | Ending cutscene, victory screen, heal effects |
| `COLOR_PANEL` | `{20,20,30,255}` | Panels | Card background (SA), shop rows, pause box |
| `COLOR_PANEL_LINE` | `{60,60,80,255}` | Panel borders | Card inner border (SA), dividers |
| `COLOR_OVERLAY` | `Fade(BLACK, 0.7f)` | Dimming | Behind pause, shop, game over; kill counter box (SA) |
| `COLOR_DISABLED` | `Fade(SKYBLUE, 0.2f)` | Unavailable | Unaffordable or maxed upgrade buttons |

Rules:

- **Red only for damage and danger.** Never for decoration or a selected state.
- **Toxic green only for contamination.** The player's shots and UI never use it.
- **Gold only for scrap and credits.**
- Pair color with a second signal (shape, text or icon) for anything the player must act on, so colorblind players can play.
- Confetti and explosion particles keep their multicolor palettes (SA); they are celebration effects, not signals.

---

## Layout Constants (screen space)

Current positions (SA) and planned additions. All move into `Theme.hpp`.

| Element | Rectangle or position | Notes |
|---|---|---|
| Kill counter | top-left at (220, 220), `TEXT_H1`, red on a dark rounded box | (SA) |
| Game timer | top center, y 150, `TEXT_BODY` | (SA) |
| Health bar | x 2640, y 150, 1000 x 150, images `health_bar` and `health` | (SA); width now uses current / max health |
| Cargo | under the health bar: x 2640, y 330, `TEXT_BODY`, gold, "CARGO 34/60" | new |
| Credits | x 2640, y 430, `TEXT_BODY`, gold, "CREDITS 210" | new |
| Wave label | top center under the timer, y 250, `TEXT_BODY`, "WAVE 4" | new |
| Wave banner | centered, y 700, `TEXT_TITLE`, fades in and out over `WAVE_BANNER_TIME` | new |
| Boss bar | x 920, y 1900, 2000 x 60, name above in `TEXT_CARD_TITLE`, phase tick marks | new |
| Dock arrow | on an ellipse 1500 x 800 around the screen center, pointing to the dock; hidden when the dock is on screen | new, return phase only |
| Tutorial prompt | centered, y 1750, `TEXT_BODY`, muted gray | new |
| Augment cards | 1200 x 300, gap 75, stacked vertically at the center | (SA) |
| Game-over buttons | 800 x 120 at (1520, 1600) and (1520, 1780) | (SA) |
| Menu buttons | 1500 x 150 at x 250, y 1200 + 170 × index | (SA) |

### Dock shop layout (S-06)

```
┌──────────────────────────────────────────────────────────────────────────┐
│  BAYANIHAN DOCK                                        CREDITS  1,240    │  title row y 200
│  Scrap deposited +86                                                     │
│                                                                          │
│  ┌──────────────────────────────────────────────┐   ┌──────────────────┐ │
│  │ BLASTER        ■■□□□  +30% damage   140  [BUY]│   │ HULL  72 / 120   │ │  7 rows, 140 px each
│  │ FIRE CONTROL   ■□□□□  -10% cooldown  90  [BUY]│   │ [REPAIR  24]     │ │  starting y 450
│  │ HULL PLATING   □□□□□  +20 max HP     40  [BUY]│   │                  │ │
│  │ ARMOR          ...                            │   │                  │ │
│  │ THRUSTERS      ...                            │   │                  │ │
│  │ TRACTOR BEAM   ...                            │   │ [ LAUNCH WAVE 5 ]│ │  launch = primary
│  │ CARGO HOLD     ...                            │   └──────────────────┘ │
│  └──────────────────────────────────────────────┘                        │
└──────────────────────────────────────────────────────────────────────────┘
 rows panel x 220..2700        side panel x 2800..3620
```

- One primary action on this screen: **Launch**, in `COLOR_ACCENT`.
- Level pips: filled squares in `COLOR_SCRAP`, empty squares in `COLOR_PANEL_LINE`.
- An unaffordable or maxed row uses `COLOR_DISABLED` and its button does nothing; "MAX" replaces the price at level 5.
- Buying plays `button_click` and briefly flashes the row gold.

---

## Sprites and AI-Generated Assets

### Orientation and size rules

15 October low-enemy reskin: three recognizable mutated trash objects, with fronts/claws toward the top and trailing cables toward the bottom. Variant A is a crushed ribbed tin can with torn-lid jaws; B a leaking rectangular battery with two terminals; C a cracked monitor with a green eye and broken bracket claws. Shared dusty mauve/copper metal, dark purple mutation and toxic-green eyes; crisp binary-alpha pixel art. Original 64px frame padding and 15-unit world size are retained, with the animated body bounded to 32px. Idle loops remain 10/5/5 frames at 0.1 s/frame; corresponding object-specific breakups remain 8/8/7 frames at 0.1 s/frame. Death starts with the exact exported idle frame and ends transparent.

- **All ship and enemy sprites face UP** in the source image. The code rotates sprites by `atan2(direction) + 90°`, which assumes the art points toward the top of the image.
- Sprite sheets are **horizontal strips**: frames left to right, all the same size, no padding. The code divides the width by the frame count.
- Transparent PNG. Pixel art, consistent pixel density across all sprites.
- **A reskin keeps the exact pixel size and frame count of the file it replaces.** Then no code changes. If a new frame count is unavoidable, update the matching `Theme::FRAMES_*` constant in the same commit.

### Sprite table

Existing sheets (sizes measured from the current files). "Frame" is width x height of one frame.

| Key | File | Frame | Frames | World size | Reskin as |
|---|---|---|---|---|---|
| `player_acceleration` | player_accelerating.png | 32 x 32 | 4 | 8 | Collector ship, thrusters on |
| `player_deacceleration` | player_deaccelerating.png | 32 x 32 | 3 | 8 | Collector ship, idle |
| `player_bullet` | player_bullet.png | 249 x 144 | 1 | 8 x 5 | Sky-blue bolt |
| `enemy_bullet` | enemy_bullet.png | 233 x 134 | 1 | 8 x 8 | Toxic glob |
| `projectile_impact` | projectile_impact.png | 64 x 64 | 8 | 10 (14 heavy) | Sky-blue contact burst through fading aftermath |
| `low_level_enemy1` | low_level_enemy1.png | 64 x 64 | 10 | 15 | Can biter |
| `low_level_enemy2` | low_level_enemy2.png | 64 x 64 | 5 | 15 | Battery crawler |
| `low_level_enemy3` | low_level_enemy3.png | 64 x 64 | 5 | 15 | Monitor parasite |
| `low_level_enemy1_destruct` | | 64 x 64 | 8 | 15 | Burst into scrap |
| `low_level_enemy2_destruct` | | 64 x 64 | 8 | 15 | |
| `low_level_enemy3_destruct` | | 64 x 64 | 7 | 15 | |
| `mid_level_enemy` | mid_level_enemy.png | 64 x 64 | 12 | 15 | Rogue Satellite (spinning panels) |
| `mid_level_enemy_destruct` | | 64 x 64 | 7 | 15 | |
| `debris` | debris.png | 96 x 96 | 1 | fixed by variant | Scrap clump plus nine variants |
| `debris_destruct` | debris_destruct.png | 96 x 96 | 8 | reference only | Previous breakup sheet; live fragments now use intact art |
| `background1` to `background4` | background1-4.png | 500 x 500 | 1 | tiled parallax | Shared space layers; draw order is 1,3,4,2. Unique Earth/station landmarks do not repeat in tiles; see background brief |
| `health_bar`, `health` | healthBar.png, health.png | 128 x 16 | 1 | screen 1000 x 150 | Hull bar frame and fill |
| `wasd_keys` | wasd_keys.png | 67 x 43 | 3 | world 16 x 10 | Keep |
| `e_key` | e_key.png | 19 x 21 | 3 | world 5 x 5 | Keep |
| `game_over_text` | game_over_text.png | 394 x 47 | 10 | screen 1800 x 300 | "SIGNAL LOST" or keep |
| `main_menu_background` | MainMenuBackground.png | 900 x 512 | 5 x 2 grid | full screen | New menu backdrop (Earth and orbit) |
| `exit_animation` | ExitAnimation.png | 1920 x 1080 | 4 x 7 grid | full screen | Keep or replace |
| `border` | border_raw.png | 480 x 320 | 1 | full screen | Keep (CRT bezel) |
| `window` | window.png | 100 x 114 | 1 | | Unused; available for panels |

New sheets (planned). Sizes are recommendations; record the final ones here and in `Theme.hpp`.

| Key | Frame | Frames | World size | Content |
|---|---|---|---|---|
| `high_level_enemy` | 64 x 64 | 6 | 22 | Compactor: boxy crusher with glowing toxic seams |
| `high_level_enemy_destruct` | 64 x 64 | 8 | 22 | |
| `boss_hoarder` | 192 x 192 | 6 | 50 | The Hoarder: sphere of fused junk |
| `boss_hoarder_destruct` | 192 x 192 | 10 | 50 | |
| `boss_core` | 256 x 256 | 8 | 60 | The Core: junk shell around a pulsing green core |
| `boss_core_destruct` | 256 x 256 | 12 | 60 | |
| `boss_bullet` | 32 x 32 | 1 | 6 x 6 | Large toxic orb |
| `scrap_small`, `scrap_medium`, `scrap_large` | 16 x 16 | 1 | 2, 3, 4 | Gold metal bits (values 1, 5, 10) |
| `dock` | 256 x 256 | 1 | 40 | HOPE Colony mothership berth, top-down |
| `dock_arrow` | 64 x 64 | 1 | screen 120 | Chevron |
| `cutscene_01` to `cutscene_07` | 1920 x 1080 | 1 | full screen | Intro slides |
| `ending_01` to `ending_04` | 1920 x 1080 | 1 | full screen | Ending slides |

### AI asset prompt rules

- Describe the subject and style only. Never name an existing game, studio, film, artist or brand.
- Keep a shared style line and reuse it for every prompt, for example: "top-down 2D pixel art sprite, 64x64, facing up, dark outline, limited palette, toxic green glow accents, transparent background".
- Save the prompt, tool, model and date in `assets/ASSETS.md` for every generated file. Form 03 needs it.
- Clean up AI output by hand: fix frame alignment, remove stray pixels, unify the palette. Note the edits in `ASSETS.md`.

---

## Audio

| Key | Kind | Use | Status |
|---|---|---|---|
| `home_music` | music | Main menu | Exists; confirm provenance or replace |
| `game_music` | music | Waves | Currently a third-party track; **must be replaced** |
| `boss_music` | music | Boss waves | New |
| `dock_music` | music | Dock shop (optional, can reuse `home_music`) | New |
| `cutscene_music` | music | Intro and ending | New |
| `player_damaged`, `player_damaged_2` | sound | Player hit | Exists |
| `button_click` | sound | UI clicks | Exists |
| `exit_sound` | sound | Exit animation | Exists |
| `game_over` | sound | Death | Exists |
| `player_atk_sound.mp3` | sound | Player shot (loaded by path in `Player`) | Register as `player_shoot` in item 05 |
| `bullet_impact` | sound | Player projectile contact | New; original synthesized PCM |
| `score_sound.wav` | sound | Kill (loaded by path in `Game`) | Register as `kill` in item 05 |
| `scrap_pickup` | sound | Scrap collected | New |
| `dock_deposit` | sound | Deposit at the dock | New |
| `boss_roar` | sound | Boss intro | New |
| `charge_windup` | sound | Compactor windup | New |

- Music streams need `UpdateMusicStream` every frame from the active scene. Switching tracks: `StopMusicStream(old)`, `PlayMusicStream(new)`.
- Overlapping SFX use sound aliases (see `library-docs.md`).
- Every music and sound file needs a provenance row.

---

## Feedback ("Juice") Rules

Reuse what exists before adding new effects.

| Event | Feedback | Exists? |
|---|---|---|
| Enemy hit | Damage number, 0.08 s red reaction tint, contact burst and aftermath | Yes |
| Enemy killed | Destruct animation, kill sound, kill counter wobble | Yes |
| Player hit | Red edge overlay, red flashing ship, hit sounds, knockback | Yes |
| Augment pick | Confetti, card animations | Yes |
| Player death | Explosion confetti, overlay slide, game-over text | Yes |
| Scrap collected | Pickup sound, cargo number pulse | New |
| Cargo full | "CARGO FULL" in gold under the cargo number for 1.5 s | New |
| Deposit | Numbers count from cargo into credits over 0.6 s | New |
| Wave start | Banner "WAVE N" | New |
| Boss intro | Name banner, `boss_roar`, background tint shifts toward toxic green | New (the code has a note to tint the background during bosses) |
| Compactor windup | Toxic flash on the sprite | New |
| Boss death | Explosion confetti at the boss, large scrap spray | Reuse |

No camera shake by default; the CRT shader already adds motion. Add shake only if the balance pass finds hits feel weak, and keep it under 1 world unit.

---

## Screen Specifications

Top-to-bottom composition. Screen IDs from `project-overview.md`.

### S-01 Loading (`LoadingScreen`)
Default-font progress text centered at y 1800. Replace with a `TEXT_BODY` progress bar only if time allows (fonts are already loaded before this scene).

### S-02 Intro cutscene (`IntroCutscene`)
Full-screen slide image with a slow 3% zoom over its duration. Bottom text box: `COLOR_OVERLAY` panel x 300 to 3540, y 1550 to 1950, text in `secondary_font` `TEXT_BODY_SM`, typewriter at 40 characters per second. Caption bottom-right "SPACE: NEXT   ESC: SKIP" in `TEXT_CAPTION`, muted.

### S-03 Main menu (`MainMenu`)
Animated background. Title (`TEXT_DISPLAY`): new game title in two lines (first line sky blue, second line toxic green, both at 55% opacity like the SA title). Buttons, left-aligned: Story, Endless, Leaderboard, Credits, Exit. Footer: "DOST Level Up 3.0 - 2026" in `TEXT_CAPTION`. Remove "Equity Quest - 2024" and the Settings button.

### S-04 Gameplay HUD
Health bar, cargo and credits top right. Kill counter top left. Timer and wave label top center. Boss bar bottom center during boss waves. Dock arrow during the return phase. Tutorial prompts during wave 1. "SIGNAL WEAK" warning near the arena edge.

### S-05 Augment pick
Existing card stack and confetti. Header above the cards: "WAVE N CLEARED" in `TEXT_TITLE`.

### S-06 Dock shop
See the layout above. Entering plays the deposit count-up first, then enables the buttons.

### S-07 Pause (`PauseOverlay`)
`COLOR_OVERLAY` over the frozen game. "PAUSED" in `TEXT_TITLE` at y 700. Buttons: Resume (primary), Quit to Menu. P or Esc resumes.

### S-08 Game over
Existing overlay and stats, plus: mode, wave reached, scrap lost (cargo at death). If the score qualifies, a name entry box appears before the buttons (`NameEntry`, `TEXT_H1`, blinking cursor, Enter to save).

### S-09 Ending cutscene (`EndingCutscene`)
Same layout as the intro, `COLOR_LIFE` accents. Final card shows run stats and "ENDLESS MODE: THE JUNK KEEPS COMING".

### S-10 Leaderboard (`LeaderboardScene`)
Title "LEADERBOARD". Current-rules mode/difficulty filters and top-10 rows: rank, name, score, active time and outcome, plus Boss clears or Campaign progress as relevant. Highlight latest run ID in COLOR_SCRAP; Back returns to MainMenu. Use the 25 October result contract; old two-column Story/Endless layout is retired.

### S-11 Credits (`CreditsScene`)
Scrolling `secondary_font` text: game title, team and roles, coach, built with Raylib, AI tools and what they were used for, asset and font licenses, "Made for DOST Level Up 3.0". Back button.

---

## Do Nots

- Never draw text outside the safe area.
- Never hard-code a color, font size or UI position in a `.cpp`; use `Theme`.
- Never use red, toxic green or gold outside their meanings.
- Never draw HUD inside `BeginMode2D`, or world objects after `EndMode2D`.
- Never use more than one primary action on a screen.
- Never add art that faces a direction other than up.
- Never change a sprite's frame count without updating `Theme.hpp` and the sprite table.

---

## Initial `src/Theme.hpp`

Item 03 creates this file. After that, the header is the source of truth.

```cpp
#pragma once
#include "raylib.h"

namespace Theme {

// ---------- Fonts (ResourceManager keys) ----------
inline constexpr const char* FONT_PRIMARY   = "primary_font";
inline constexpr const char* FONT_SECONDARY = "secondary_font";

// ---------- Type scale (canvas px unless noted) ----------
inline constexpr float TEXT_DISPLAY      = 400.0f;
inline constexpr float TEXT_TITLE        = 200.0f;
inline constexpr float TEXT_BUTTON_LG    = 150.0f;
inline constexpr float TEXT_H1           = 120.0f;
inline constexpr float TEXT_CARD_TITLE   = 100.0f;
inline constexpr float TEXT_BODY         = 80.0f;
inline constexpr float TEXT_BODY_SM      = 64.0f;
inline constexpr float TEXT_CAPTION      = 50.0f;
inline constexpr float TEXT_WORLD_DAMAGE = 4.0f;   // world units
inline constexpr float TEXT_WORLD_LABEL  = 5.0f;   // world units
inline constexpr float TEXT_SPACING      = 1.0f;

// ---------- Colors ----------
inline constexpr Color COLOR_BG         = {0, 0, 0, 255};
inline constexpr Color COLOR_TEXT       = {245, 245, 245, 255};   // RAYWHITE
inline constexpr Color COLOR_TEXT_MUTED = {128, 128, 128, 255};
inline constexpr Color COLOR_ACCENT     = {102, 191, 255, 255};   // SKYBLUE
inline constexpr Color COLOR_DANGER     = {255, 50, 50, 255};
inline constexpr Color COLOR_TOXIC      = {120, 255, 90, 255};
inline constexpr Color COLOR_SCRAP      = {255, 196, 64, 255};
inline constexpr Color COLOR_LIFE       = {90, 200, 120, 255};
inline constexpr Color COLOR_PANEL      = {20, 20, 30, 255};
inline constexpr Color COLOR_PANEL_LINE = {60, 60, 80, 255};
inline constexpr float OVERLAY_ALPHA    = 0.7f;                   // Fade(BLACK, OVERLAY_ALPHA)
inline constexpr float DISABLED_ALPHA   = 0.2f;                   // Fade(COLOR_ACCENT, DISABLED_ALPHA)

// ---------- Safe area ----------
inline constexpr Rectangle SAFE_AREA = {200.0f, 150.0f, 3440.0f, 1860.0f};

// ---------- HUD layout ----------
inline constexpr Vector2   KILL_COUNTER_POS = {220.0f, 220.0f};
inline constexpr float     TIMER_Y          = 150.0f;
inline constexpr float     WAVE_LABEL_Y     = 250.0f;
inline constexpr Rectangle HEALTH_BAR       = {2640.0f, 150.0f, 1000.0f, 150.0f};
inline constexpr Vector2   CARGO_POS        = {2640.0f, 330.0f};
inline constexpr Vector2   CREDITS_POS      = {2640.0f, 430.0f};
inline constexpr float     WAVE_BANNER_Y    = 700.0f;
inline constexpr Rectangle BOSS_BAR         = {920.0f, 1900.0f, 2000.0f, 60.0f};
inline constexpr Vector2   DOCK_ARROW_RADII = {1500.0f, 800.0f};
inline constexpr float     TUTORIAL_Y       = 1750.0f;

// ---------- Cards and buttons (SA values) ----------
inline constexpr float CARD_WIDTH  = 1200.0f;
inline constexpr float CARD_HEIGHT = 300.0f;
inline constexpr float CARD_GAP    = 75.0f;
inline constexpr Rectangle MENU_BUTTON_FIRST = {250.0f, 1200.0f, 1500.0f, 150.0f};
inline constexpr float     MENU_BUTTON_STEP  = 170.0f;

// ---------- Sprite sheet frame counts (horizontal strips) ----------
inline constexpr int FRAMES_PLAYER_ACCEL          = 4;
inline constexpr int FRAMES_PLAYER_IDLE           = 3;
inline constexpr int FRAMES_LOW_ENEMY[3]          = {10, 5, 5};
inline constexpr int FRAMES_LOW_ENEMY_DESTRUCT[3] = {8, 8, 7};
inline constexpr int FRAMES_MID_ENEMY             = 12;
inline constexpr int FRAMES_MID_ENEMY_DESTRUCT    = 7;
inline constexpr int FRAMES_HIGH_ENEMY            = 6;    // planned
inline constexpr int FRAMES_HIGH_ENEMY_DESTRUCT   = 8;    // planned
inline constexpr int FRAMES_DEBRIS_DESTRUCT     = 7;
inline constexpr int FRAMES_BOSS_HOARDER          = 6;    // planned
inline constexpr int FRAMES_BOSS_HOARDER_DESTRUCT = 10;   // planned
inline constexpr int FRAMES_BOSS_CORE             = 8;    // planned
inline constexpr int FRAMES_BOSS_CORE_DESTRUCT    = 12;   // planned
inline constexpr float FRAME_TIME                 = 0.1f; // SA

} // namespace Theme
```

P1 default restoration: Default uses the existing `player_acceleration` (4 frames) / `player_deacceleration` (3 frames) sheets at 32×32 pixels per frame, 8×8 world-unit draw size and 0.1 s per frame. The original `player_bullet` is retained. Gunner names the modular cannon/base-engine/no-shield preset. All presets draw without shield overlays; the separate supplied shield sheets are used only when explicitly equipped. No assets were changed.
