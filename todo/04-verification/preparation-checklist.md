# Preparation Review and Future Acceptance

**21 October 2026.** This is a documentation checklist. Future runtime checks below are instructions for a later authorized implementation session, not tests performed now. [Gameplay](../02-gameplay/gameplay.md) contains the detailed T01-T10 verification cases.

## 1. Context-only change boundary

- [ ] Latest requested pull of origin/dev completed before edits; record result in the tracker.
- [ ] Changed files are Markdown beneath context/ and todo/ only.
- [ ] No source, tests, assets, generated builds, project configuration or dependencies changed by this preparation work.
- [ ] Shared references stay at AGENTS.md's required paths; pending handoffs live in topic folders under todo/.
- [ ] Local Markdown links resolve after moving files; obsolete root handoff paths are gone.
- [ ] Existing completed work retains its status; proposals are not marked implemented.
- [ ] Whitespace checks pass and the AI usage log describes documentation work accurately.
- [ ] If published, staged scope contains only intended documents and the remote branch matches the resulting commit.

## 2. Canon and story review

| Requirement | Reference | Pass condition |
|---|---|---|
| Hopeful acronym | [World](../01-story/world-and-campaign.md) | H.O.P.E. has one exact expansion; settlement name and final game title are distinct |
| Five-year development | World | 2723 minus 2718 equals five; all text agrees |
| Under-decade collapse | World | 2732 minus 2723 equals nine; approximately 99% is explicitly fiction |
| Surface and orbital catastrophe | World | Both waste sources and a plausible fictional transport route are described |
| Scientific framing | [Science notes](../01-story/science-notes.md) | Primary sources support narrow atmospheric claims; no invented warming percentage |
| Grounded fiction | Science notes | Living waste-eaters predate the treatment; fictional DNA/behavior changes affect biology, while scrap stays nonliving |
| Retired plot | Active story/overview/UI briefs | No tree quest, magical seed ending or radiation origin remains outside explicit historical explanation |
| Scrap armor | World section 4.1/science notes | Uncontrolled intake differs from digestion; binding creates nonliving armor; evolution occurs across generations; no new combat armor system is implied |
| Biological continuity | World/science notes | Protected orbital cores and physical contamination transport are clear; no claim of an atmosphere spreading through vacuum |
| Narrative theme | [Theme and slogans](../01-story/narrative-theme.md) | Neglect has consequences; organisms do not judge humanity; recovery demonstrates sustained responsibility |
| Colony purpose | World/story | Humans inhabit reused stations; player stays in the ship; repairs and salvage support survival |
| Source campaign | World/gameplay | Source stop, remaining-hostile resolution, no-loot kill and local recovery consequence agree |
| Trailer grammar | [Storyboard](../01-story/story-context.md) | Text then moving footage; intro 40 seconds, ending 24, trailer 90; no timing gaps |
| Truthful footage | Storyboard | No unfinished mechanic is advertised as recorded working gameplay |

## 3. Economy review

- [ ] Biological remains do not create a new currency, pickup or corpse-harvesting requirement.
- [ ] Four owner-selected materials (Metal Fragments, Circuit Parts, Polymer Pieces, Power Cells) map to recognizable sources; Mixed Salvage is a label, not another currency. Enemy-tier reward values remain unchanged.
- [ ] Material families introduce no exchange multiplier, random reroll, crafting prerequisite or second wallet.
- [ ] Enemy trade ranges and fixed salvage values agree with game-design.md.
- [ ] Existing ordinary debris yields/animations and no-reward exclusions are preserved.
- [ ] Shop acquisition prices, rank formulas and paid repair rates are unchanged by material flavor.
- [ ] Pickup merging/splitting preserves trade and salvage independently; family metadata cannot multiply rewards.
- [ ] Source shutdown never requires a random boss drop or purification item.
- [ ] Spending trade currency never subtracts salvage level progress or Return Home charge.

- [ ] Weapon quotes are 500/1500/4000/10000 with 16000 total on every path; 20–25-minute Swarm timing is measured, not inferred from prices. Survival shares prices and normally ends with a lower-tier build.
- [ ] Attribute/owned-rank prices are 5x, special acquisitions 10x; gains do not multiply with prices.
- [ ] Hull repair quotes 10 scrap per missing HP and restores exactly payment/full-quote of the deficit, preserving fractional HP. Full Repair/Repair What I Can Afford show exact previews; zero wallet yields no free heal.
- [ ] Verify the adopted five-size battery contract at runtime: remove old overcharge before adding charge, preserve damaged normal shield, quote proportional prices, commit payment/shield atomically, preview weaker replacements and cap regeneration at normal capacity. PREP-28 design is adopted; runtime checks remain pending.

## Upgrade proposal checks before adoption

- [ ] Accepted graph is 1/3/5/7/10 nodes; only immediate descendants can be bought. Full proposed profiles/signatures exist; numerical adoption, exact card compatibility and live balance/performance remain open.
- [ ] Quarter-strength numeric grants do not buy full field ranks, heal, reset cooldowns or produce fractional bullets.
- [ ] Deflector stays in field cards; paid capacity preserves current shield and broken/reboot state.
- [ ] Legendary Blink intercepts a validated incoming direct hit once; legal on-screen rescue/cooldown/protection commit together.
- [ ] Blink no-safe-spot behavior, protection duration and cooldown floor are reviewed before code.
- [ ] All 19 abilities and 13 augments have unique proposed grades; Luck stays a separate proposed support node.
- [ ] Legendary gating is not promoted by ordinary-pool exhaustion; Luck does not change card rarity or reroll existing rewards.
- [ ] Boss/schedule/name/layout/general-economy deferrals remain open, without repeated questions now.
## 4. Handoff completeness gates

Review [decisions and gaps](../00-planning/decisions-and-gaps.md) before each affected checkpoint. An unresolved item is visible work; do not silently fill it with an unrelated feature.

| Before checkpoint | Data/content needed |
|---|---|
| T01 | Adopted mode/difficulty/progress contracts, numeric bounds and run reset ownership |
| T02 | Shared reward paths, material assignment, merge policy and no-drop exclusions |
| T03 | Eligible card catalog, duplicate/rarity policy, overflow and queue behavior |
| T04 | Per-ability auto-target/trigger matrix, mobility rules, shield/equipment interaction |
| T05 | Hub geometry, stations/gates, input focus, entry and resume locations |
| T06 | Actual boss definitions, complete spawn tables, source behavior and outcome ordering |
| T07 | Shield/charge gates, suspension ownership, repair quote/commit/cancel behavior |
| T08 | Shop stock, rank effects, atomic price/ownership validation and no-free-heal constraints |
| T09 | Screen states, tutorial triggers, settings/audio routing and safe-area layout |
| T10 | Performance ceilings, complete reset checklist, release scope and human balance criteria |

Leaderboard, story playback, credits, release and submission deliverables remain separate tracked work alongside T01-T10. These documents do not collapse all project tasks into one unchecked mega-feature.

## 5. Future runtime scenarios, not run in this session

1. New application -> optional intro skip -> Start -> difficulty -> HOPE hub -> valid portal launch.
2. Collect random trade/fixed salvage from each supported reward tier; cross a level threshold with overflow and choose cards in the field.
3. Return below threshold fails; broken shield blocks even full charge; eligible return consumes charge only on successful transition.
4. Hub return preserves enemies, boss phase, pending attacks, pickups, material metadata, clocks and RNG; Resume consumes the transition frame.
5. Paid repair commits cost and restoration together; cancel/insufficient funds gives neither free healing nor lost currency; partial affordable repair is correct.
6. Skill rank purchases share actual effects with field cards while preserving paid-heal exclusions; stock does not reroll by reopening the shop.
7. Each mode meets its own objective; a boss kill in Chaos continues the run and a final Campaign source clearance enters the ending once.
8. No-loot effects can complete source objectives; simultaneous player death defeats the run under the proposed tie rule.
9. Ending skip reaches one finalized result; New Run removes source flags, wallet, upgrades, timers and suspended objects.
10. Approved load/performance targets hold at the highest supported effect/rank combination; separate repeatable smoke checks confirm release packaging and actual demo-machine behavior.

Record real measured results and their commit when implementation occurs. A document audit cannot establish build success, runtime correctness, scientific possibility of the fictional technology or balanced gameplay.
