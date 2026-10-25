# Adopted cannon composition and signatures

25 October 2026. Detailed numerical appendix to game-design.md; completes written PREP-22/27 alongside the [26 capability profiles](card-compatibility.md) and [original26 stat/signature rows](../../context/game-design.md#23-october-weapon-stat-draft--accepted-tree-proposed-tuning). Adopt those existing draft numbers as initial beta tuning. Names/tree/prices were already selected; this adoption is delegated numerical design, not a claim of balanced or implemented cannons. No source or assets are edited.

## Root attack and snapshot

One primary trigger group starts when the mouse-aimed primary schedule earns an attack. Capture group ID/time, weapon node, native geometry, primary-only Payload/crit/knockback/pattern ranks, Blast Radius and aim. T1 rolls one uniform7..12 base damage per root. Each root rolls one critical outcome, shared by all its descendants; separate roots remain independent. Start ready on a fresh deliberate Shoot, then accrue cadence only while firing is authorized. Preserve remaining cooldown debt through cards, purchases, hub and focus; no extra attack from changing a tier.

At crit rating c (fraction, not percent text), tier=floor(c)+Bernoulli(frac(c)); multiplier=1+tier. Thus0%=1x,100%=2x,150%=half2x/half3x,250%=half3x/half4x. No clamp at100%. Apply `native damage * (1+0.15*fieldPayload+0.0375*paidPayload) * critMultiplier` once to each primary-owned damage component, including listed signature/secondary damage. Distance bonus modifies eligible direct sniper contacts only; secondary damage gets no distance or penetration bonus. Use actual applied damage for popups; never reroll critical for pellets, splash, burn, links or signature descendants. Automatic abilities and clones use their own damage contract without primary attribute copies.

Primary interval `T = 1/baseAttacksPerSecond * 0.9^fieldOverclock * 0.975^paidOverclock`. Tempest substitutes18 for12 during Overdrive before applying the same factors. Continuous beam/flame/arc cadence follows this rule per native tick/pulse. Burn has its separately fixed0.25-second tick interval and1.5-second refresh lifetime; attack speed increases direct flame contacts, not burn tick frequency or stacked burn instances.

Aim is snapshotted per root. Delayed burst members use that direction and firing-time interpolated ship position, retain root stats and begin travel at their actual emission time. Already flying effects retain their snapshot after an upgrade. A subframe simulation must process emission/collision order before later target death; do not resolve all shots against an end-of-frame enemy list.

## Exact projectile patterns

Only P-enabled profiles accept these cards; beams/arcs/flame keep earned ranks dormant. All five discrete cards remain full field ranks, not paid quarter increments. Let rapid r, scatter s, broadside b, tail t be earned ranks; native pellet count N is1 for bullets/missiles,6 for T2 Shotgun/T3 Flak,8 for T4 Shrapnel/T5 Shatterstorm.

| Card | Composition | Bounds and identity |
|---|---|---|
| Rapid Fire | B=1+r complete native/pattern volleys per root, at offsets `j*T/(2*B)` for j=0..B-1 | Occupies less than half a root interval; does not slow base cadence or use the obsolete fixed0.1-second burst delay. No rank/count cap |
| Scatter Shot | Each volley has N+s projectiles evenly spaced across its native full fan (30 degrees for originally single-shot weapons; native30/32 for pellet profiles) | One projectile stays centered when total1. Spread does not grow indefinitely with rank; count still grows |
| Broadside Cannons | b banks on each side, every bank fires that same N+s volley centered on aim±90 degrees | If b=1 center exactly±90; for b>1 bank centers span -15..15 around each side, evenly spaced |
| Tail Gunner | t rear banks, each fires the same N+s volley centered around aim+180 | t=1 centered rear; t>1 bank centers span -15..15 around rear, evenly spaced |
| Armor Piercing | AP-enabled direct projectile/beam allowance = native allowed contacts + rank | First victim100%, every later victim60% of its own distance-adjusted direct damage; not compounded and never wall penetration |

Total root projectile count `B*(N+s)*(1+2*b+t)`. Stable ordinal: burst member, bank (forward, left banks, right banks, rear banks), then pellet. Intrinsic damage/size/range/guidance stay native; no recursive card application to the resulting projectile. Native pellet fan never also becomes a duplicate central bullet. Broadside/rear missiles acquire in their own emission-direction cone. Extra projectiles can genuinely miss or overkill; no conversion of misses into guaranteed target damage.

Worked examples: Starter with r2/s1/b1/t1 emits3*2*4=24 projectiles per root. Shotgun with r1/s2/b1/t0 emits2*8*3=48 pellets. With T1's0.5-second interval and r2, offsets are0,1/12,1/6 seconds; the next root stays at0.5, without a fixed burst-rate floor. A native3-contact Sniper with AP2 reaches5 targets, still1x/0.6x/0.6x/0.6x/0.6x before each contact's own distance factor. Explosive pellets/missiles have AP disabled and detonate once; child fragments receive no AP/pattern ranks.

For beams AP extends the native enemy count per resolved tick with the same100%/60% rule, sorted by distance along the actual beam capsule, stable ID ties. Arc links and flame victims use their native fixed target rules. Inertia applies once per supported direct victim contact, not again on that contact's splash/burn/child/signature. Boss resistance remains authoritative; no new stun lock.

## Circular damage and status ordering

Blast Radius multiplies explicitly tagged native damaging circle radius by `1+0.10*fieldBR+0.025*paidBR`, after its base/ability-rank size calculation; no double multiplication on child effects. Target limits and per-victim damage remain unchanged. Native missile impact victim takes100% once; up to3 others50%. Explosive pellet primary takes100% once; up to2 others50%. Range-end bursts choose nearest eligible as primary. Contact and explosion do not damage that primary twice. World solids block traversal and area line of effect; a circular blast cannot pass through an intact barricade wall. Nearest-first/stable ID applies when a native target limit is smaller than the eligible set.

Keep one burn record per victim for the player primary. Stronger exposure replaces damage snapshot and expiry; equal exposure refreshes expiry; weaker secondary exposure cannot extend/downgrade an unexpired stronger burn. On expiry, a later contact may start its current weaker burn. Primary20 burn/s means5 per0.25-second tick before captured Payload/critical; secondary7/s means1.75 per tick. Preserve fractions. Burn carries no additional primary/signature contact credit. Debuff slow/stun from independent abilities stays separately owned and cannot recursively proc cannon signatures.

## One signature ledger per root

Each T5 keeps its existing named signature, threshold, fixed minimum interval, native damage and target limits. Those26 profiles/10 signature tables in game-design.md are now adopted, not silently replaced by prototype modular-weapon numbers. A root contributes at most one successful count regardless of burst/pellet/bank/victim multiplicity. First actual enemy contact determines success; walls/debris/misses/ability/clone hits cannot charge it. Successful root order uses contact timestamp then group ID. Crit does not make a count more valuable.

Count signatures saturate at their threshold while the minimum interval is closed; they cannot bank a second activation. The next eligible successful root when ready commits one effect and clears its count. At most one signature activation per root. Payload/crit comes from that root snapshot once. Once committed, an effect still resolves at its saved impact point if the primary victim dies; no transfer of that victim's overkill. Late contacts from the same root cannot recharge a consumed count.

| Signature type | Owner of its one activation with pattern cards |
|---|---|
| Hammerfall / Fracture / Breach Wave | First contacting projectile of the threshold-reaching ready root; only that impact receives the bonus and associated area |
| Terminal Shock | First contacting projectile is the empowered projectile; track only its actual distinct hits and last contact, explode on its termination excluding its victims |
| Pursuit Salvo | One set of3 extra missiles per committed root, not per missile/bank; descendants cannot earn another salvo |
| Fragment Bloom | First forward bank of the first burst member owns the signature; only its first8 native pellet ordinals may emit2 children each on actual impact, maximum16 children. Extra scatter/banks/bursts retain normal damage but cannot multiply the native signature |
| Core Rupture / Flashover | Real direct exposure on one enemy over combat time; each time interval counted once even if several descendants contact. Target/miss-gap reset follows original table |
| Storm Network | One enhanced primary pulse through its existing links after real2-second contact exposure, no extra links/recursive arcs |
| Overdrive | Real4-second primary enemy-contact time earns its existing2-second window; parallel hits do not accelerate the clock, and no charge accrues during Overdrive |

Snapshot/exposure intervals intersect only actual contact; allow the original0.2-second grace and specified reset gaps without treating missed time as successful contact. Phase/weapon upgrades cannot precharge a signature or reset its minimum interval. T5 acquisition begins empty. Full run reset clears ledgers; normal hub/pause freezes them. Existing profiles' stated signature target caps are native geometry, not a new combat skill-rank/army cap.

## Adoption and validation

PREP-22/27 writing is complete with this composition and the numerical/load contract. T08/T10 remains open. Compare the exact root event stream with a scalar reference for all26 profiles, each discrete card alone and combined, r/s/b/t=0/1/5/100, AP on/off, crit0/100/150/250%, and positive fractional Payload/BR. Check actual area target limits, wall blocking, snapshot upgrades and late descendant hits. At30/60/144 FPS verify the same emission timestamps, actual damage, signature counts, score/reward outcomes and pause/reset behavior. Reuse seeded fixtures; a paper DPS comparison never proves every path viable. Real target uptime, no-required-rare compensation, mode income and human playtests remain the original acceptance gates.
