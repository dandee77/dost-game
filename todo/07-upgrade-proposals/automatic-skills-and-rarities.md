# Automatic Skills, Blink and Proposed Rarity

**21 October 2026. Context only.** The owner confirmed automatic combat skills and Legendary reactive Blink; the 23 October field return portals supersede manual Return Home. Other tier assignments/weights remain proposals for later confirmation. Existing implementation behavior is recorded in [skills commands](../../context/skills-commands.md), not changed by these documents.

## 1. Complete target combat-ability list

The earlier Nano Repair -> Shield Detonation target remains. There are **19 combat abilities** below plus **13 attribute/pattern augments**, total 32 existing target entries. Luck is a separate proposed shop node. Field return portals are world interactions outside the card catalog, not an extra manual skill. New primary weapon families are equipment tree nodes, not added automatic-ability entries.

| Ability | Proposed rarity | Automatic behavior and duration category |
|---|---|---|
| Scrap Magnet | Common | Starts its timed local collection window when eligible released pickups are in range; respects radius and existing exclusions |
| Repulsor Pulse | Common | Periodic instantaneous push when nearby enemies make a pulse useful; otherwise stays ready |
| Deflector Shield | Uncommon | Persistent shield; starter grant and field ranks. Shop buys capacity only; broken shield blocks Return Home |
| Radiant Halo | Uncommon | Instant burst centered on the ship when enemies are within its authored radius |
| Corrosive Trail | Uncommon | Timed emission window while useful combat movement occurs; individual pools expire under existing duration rules |
| Point-Defense Interceptor | Uncommon | Timed defensive window triggered by relevant hostile projectiles; does not delete friendly fire |
| Laser Rings | Rare | Persistent orbiting blades once acquired; no duration gap. Existing rank/count/radius rules apply, without a fixed gameplay count cap; optimize cosmetic presentation separately |
| Lightning Ring | Rare | Temporary ring around the ship, then recharge; damages/stuns nearby enemies during the window |
| Chain Lightning | Rare | Selects a valid nearby target automatically and chains through distinct targets; instantaneous event |
| Combat Drone | Rare | Proposed persistent companions until destroyed; each missing slot returns after its combat respawn delay. No free revival on hub/shop opening |
| Shield Detonation | Rare | Instant shield-break event when its own cooldown is ready; does not restore the shield |
| Plasma Beam | Epic | Timed forward/cone damage; automatically aims toward a valid enemy while preserving the authored cast snapshot |
| Hologram Clone | Epic | Temporary decoy/firing copy, then recharge; primary weapon inherited at clone creation, not free future weapon replacement |
| Realm Breaker | Epic | Temporary targeted rift with automatic valid-target placement and projectile defense |
| Nuclear Missile | Epic | Automatically selects a valid threat/group, launches its existing delayed attack and resolves its blast once; not the primary Guided Missile tree node |
| Singularity | Epic | Temporary automatically placed pull/damage zone; ordinary eligible rewards remain |
| Space Collapse | Legendary | Automatic bounded group targeting; enemies erased by it yield no trade or salvage. Source objectives still resolve |
| Armageddon | Legendary | Timed automatic barrage with bounded effects; no manual target/cast button |
| Blink Drive | **Legendary — owner confirmed** | Reactive interception of a direct incoming hit, legal on-screen relocation and short protected breathing window; full contract below |

Rarity describes proposed field-offer frequency, not a random multiplier to skill damage. Already owned abilities can coexist. No limited active-slot inventory or skill swap button is introduced.

Companion persistence is owner-confirmed on 24 October: use a 20-combat-second per-destroyed-slot rebuild delay, frozen outside combat. Existing drone count/HP/damage growth remain; the owner rejected fixed army/count or combat-skill rank caps. Continued ranks depend on eligible random offers or established paid rank purchases, not guaranteed cards. A rank increase adds a slot under the normal spawn contract; it cannot heal an existing drone. Owner selected spread-fire targeting across nearby enemies, concentrating when fewer remain. Prefer under-covered targets while allowing multiple droids against durable enemies; exact range, reservation accounting and retarget cadence remain delegated implementation details. Per-slot timing prevents repeated whole-swarm creation while living drones remain. This differs from the current timed prototype and is not implemented.

For other timed abilities, retain the current duration/cooldown as the baseline until their numerical targeting review. Owning an automatic skill does not mean firing it while the hub or a modal has frozen combat. Primary movement/aim/fire controls remain separate; field return uses F inside portals and is not a manually activated skill. Existing equipment Space boosts/guards must not introduce a second normal-play skill button; engine chassis integration remains deferred.

## 2. Blink — incoming-hit rescue

**Confirmed intent:** very rare Legendary; teleport before a damaging hit, prevent that hit, stay within the current visible combat screen and offer breathing room. **Proposed exact tuning:** rank-1 cooldown 30 combat seconds; `max(12, 30 * 0.95^(rank - 1))`; two seconds of post-blink protection against direct hostile projectile/contact damage at every rank. Existing statuses are not cleared; non-spatial damage-over-time follows its ordinary rules. Rank 1 travel maximum is the existing 35 units, with the existing +15% per-rank distance growth capped at rank 5, maximum 56. Numerical authority: game-design.md's review ledger.

1. Trigger only when a direct hostile projectile/contact hit has been validated and is about to apply to a living player. A predicted projectile that misses cannot repeatedly trigger a free teleport. Existing invulnerability/debug no-damage conditions that already reject the hit take precedence; do not spend Blink on an already-negated hit.
2. If Blink is learned, ready and not already resolving, search for a legal destination before committing damage. Blink interception happens before shield/hull damage; success therefore preserves the triggering shield/hull points. A broken shield is not repaired or revived by Blink.
3. Candidate points must keep the whole ship inside the currently visible world-space combat viewport and legal arena, within current Blink distance, clear of solids, damaging bodies and immediate projectile paths. Keep the player inside the same legal arena/barricade region; do not use teleportation to bypass a closed wall or leave the encounter.
4. Proposed bounded search: three radial distances at one-third, two-thirds and full allowed travel, with eight fixed headings each, at most 24 candidates. Stable heading order resolves equal scores. Reject invalid candidates, then prefer greater clearance from predicted hostile paths and nearby enemies. Exact threat-envelope dimensions remain a targeting-data task; do not reopen arena layout design in this preparation.
5. If at least one candidate passes, cancel the triggering direct damage, move once, consume one cooldown and start the two-second protected window. Consume the relevant incoming projectile/contact event once. Other direct hits during the window do not chain Blink or apply damage.
6. If there is no legal safe candidate, **do not teleport, do not grant protection and do not consume cooldown**. Resolve the ordinary hit through shield/hull rules. Readiness is not a guarantee that an illegal escape will be invented. Retry only for the next valid damaging event.
7. Blink is not a response to non-spatial damage-over-time/status ticks or a scripted boundary violation; it cannot undo damage from a prior frame, revive the player or change the run result. No prediction-based resurrection occurs.
8. Freeze its clock during pause/cards/hub/console. Snapshot the cooldown on successful activation; upgrading a rank cannot erase current cooldown debt or grant protection. Lower cooldown applies on the next successful Blink. Reset on a true new run.
9. The protected window is fixed and separate from ordinary post-hit iframes; Phase Shift does not multiply it. No offensive contact damage, instant loot vacuum, free shield charge or Return Home charge is granted by the rescue.
10. New position becomes the start of later movement/collision checks. Do not sweep the entire teleport path for contact hits or pickup credit. Destination safety and legal-region checks are separate from normal movement collision.

Proposed cooldown examples: rank 1 = 30 s; rank 2 = 28.5; rank 5 approximately 24.44; rank 10 approximately 18.91; high ranks stop at 12. Short, dangerous cooldown-free chain escapes are excluded by the snapshot/floor rules.

## 3. Rarity of the 13 attribute/pattern cards

| Proposed rarity | Cards |
|---|---|
| Common | Weapons Payload, Overclocked Chambers, Reinforced Hull, Thruster Overdrive |
| Uncommon | Critical Matrix, Rapid Fire, Phase Shift, Gyro Control, Inertia Impact |
| Rare | Armor Piercing, Scatter Shot, Broadside Cannons, Tail Gunner |

Deflector remains in the ability table and the field pool. Numeric shop increments do not remove attribute cards. Luck is not in this field catalog in the initial recommendation; a Legendary Luck card remains an explicit later alternative.

## 4. Proposed field-offer weighting

The desired nominal per-slot proportions are Common 45%, Uncommon 30%, Rare 18%, Epic 6.5%, Legendary 0.5%. The three-option card panel still uses distinct eligible entries and the existing card RNG, isolated from loot/shop/cosmetic RNG. An entry's rarity does not increase the strength of an otherwise identical rank.

To keep Legendary genuinely rare when lower tiers become exhausted, first perform an independent **0.5% Legendary gate** for each slot. On success, choose uniformly among remaining eligible Legendary entries. If there are none, continue through ordinary tiers. On gate failure, sample only eligible Common/Uncommon/Rare/Epic tiers in relative weights 45/30/18/6.5, renormalized over available non-Legendary tiers; then choose uniformly from that tier's eligible entries. Do not automatically promote a failed gate into a Legendary.

Remove an offered entry from the current panel's remaining pool so it cannot appear twice. If no ordinary entry remains after a failed gate, show fewer options rather than silently increasing Legendary odds. The unbounded-rank ordinary ability pool normally supplies repeat candidates, but the empty-pool behavior must still be correct. Offers remain locked across panel reopen/pause; no free reroll, hidden pity system or Luck adjustment is proposed.

With eligible Legendary entries and three populated slots, the probability of at least one Legendary gate is `1 - 0.995^3`, about **1.49% per three-choice offer**. That is a gate probability, not a guaranteed Blink rate: the eligible Legendary pool also includes Space Collapse and Armageddon.

## 5. Workshop availability and grade versus price

The previous four acquisition offers remain a separate **Special Offers** selection: Singularity, Space Collapse, Nuclear Missile and Armageddon, at their existing draft prices. Their new field rarity labels do not automatically change those prices. These four can therefore be deliberately acquired at home if stocked; their card rarity describes field frequency, not universal scarcity.

**Blink first acquisition is field-only** in the proposal, to preserve the owner's request that it be very rare. It does not join the guaranteed or fixed acquisition shop stock. Once learned, its proposed whole-rank shop cost is `3000 + 750*r` for current rank r after the selected 5x owned-rank scale, so rank 1 -> 2 costs 3750. Blink's exact adoption remains pending. Cards can also grant later ranks. The selected 23 October scale makes special owned ranks `1000 + 375*r` and ordinary owned ranks `500 + 250*r`; special first acquisitions use 10x their prior prices. See the numerical ledger; no rank benefits or rarity weights change. Deflector capacity and numeric augments use the separate quarter-strength attribute contract instead.

No claim is made that the rarity or acquisition prices are balanced. The complete roster, grade assignments, confirmed persistent-drone behavior and proposed weighting are presented for later confirmation; don't mark PREP-04/05 complete solely because these candidate tables exist.
