# Numerical safety and supported-load contract

25 October2026. Written PREP-14 defaults under existing delegation. No fixed gameplay ceiling is added to combat skill ranks, numeric purchases, projectile-count cards, droids or orbiting blades. Weapon tiersT1–T5 and Luck10 remain their selected exceptions. These are implementation requirements and repeatable measurements to collect, not measured performance or a claim of unlimited hardware.

## Representation and failure semantics

Use checked uint64 counts for ranks, purchases, earned slots, event ordinals and economy totals; checked multiplication/addition BEFORE changing the live state. Keep fractional HP/damage/capacity/progress in double where appropriate; exact integral Trade Scrap/Salvage/score stay checked integers. Store positive multiplicative rates/speed in log domain, not a repeatedly multiplied float. All values entering geometry/timers/audio/rendering must be finite and in-domain. Do not cast unbounded double to int or clamp damage to INT_MAX and call the upgrade successful. The current prototype's rounded int damage/saturated growth is not the full beta target.

Validate a transaction's complete prospective state, quote and derived effects before debit/rank grant. Unknown/invalid data makes the transaction fail with reason and unchanged wallet/rank. A machine representation/allocation failure is a visible technical fault, not a new MAX rank: freeze before the affected step/commit, retain earned state, show Simulation capacity reached, allow Retry or confirmed End Run. Retry resumes only after the condition can be resolved; it cannot reroll offers/loot or refresh timers. End Run freezes an explicitly unranked diagnostic result, preserving earned displayed score rather than pretending defeat/completion/retirement success. No permanent save/recovery promise. Overflow must never wrap negative, silently saturate a stat, erase an earned unit or reward, or leave combat running with a missing handler. The mathematical rank rules remain open-ended; finite representations have explicit fault behavior.

Integral counters approaching UINT64_MAX and float range/precision risks are synthetic safety tests, not realistic balance caps. If the implementation cannot meet the defined exact event semantics within available resources, expose that limitation in the handoff/release evidence and use the technical pause, not an undocumented progression nerf. Never hide unsupported high-rate builds merely by removing their cards from eligibility.

## Multiplicative rates and clocks

Primary log interval=`log(baseInterval)+n*log(0.90)+m*log(0.975)`. Compute accrued shot work over each piecewise-constant rate segment with checked arithmetic; retain fractional work. Do not floor at one shot/rendered frame or discard whole earned events. If conversion to a representable event count/rate is unsafe, pause before advancing that segment. Do not force a timer to zero, set an infinite rate, use NaN geometry or absorb underflow with a hidden minimum cooldown. Numeric ship speed/rotation/Phase Shift gains use their adopted field/quarter factors in the same checked/log-derived manner.

Critical rating uses exact source counts before quotient/remainder decomposition; independent root draws retain their distribution. A computational batch can use an exact binomial/multinomial tier-count algorithm only when damage/geometry/proc equivalence has been proven for that batch. Expected damage is not a substitute for random independent critical outcomes; a single coin flip for a thousand roots is incorrect. If such a sampler is absent, use scalar draws and the technical capacity rule rather than inventing a normal approximation.

Combat simulation processes bounded slices no larger than1/120 second; render FPS may differ. Carry remaining authorized time through slices, and interleave emits/collisions/damage/death/loot in timestamp order. Focus loss discards wall time while inactive; menu/station time is never accumulated as combat debt. After a render stall, process at most0.25 seconds of wall delta for ordinary real-time advance; longer stalls pause with Continue confirmation, discarding excess wall time rather than producing an instant attack storm or simulated survival bonus. Deterministic equivalence fixtures drive the same explicit combat-time intervals, not render frame count. Fixed-step/interpolated movement migration is implementation work, not delivered here.

## Scalar and aggregate paths

Use the scalar event path by default. Aggregation eligibility requires identical firing-time profile/aim/origin, swept path and time window, valid target set/contact order, per-target HP constraints, independent critical distribution, statuses, penetration, signature credit and attribution. A moving target/ship, changed aim, crossing projectile, target death or differing on-hit debt splits the batch. Keep damage bounded by actual remaining HP at that event; never transfer overkill to another victim or turn a missed projectile into auto-target damage. Existing spatial grids and pooled storage are implementation tools, not permission to drop collision candidates for damage queries.

Represent repeated identical shots as a logical multiplicity only while this proof holds. Split when a target dies or a signature threshold/time boundary is reached. Keep chronological roots for counters/exposure and independent crit outcomes. A generic damage-per-second aura is not an equivalent replacement for projectiles. Lazily materialized drone/blade slots retain stable earned IDs, HP/rebuild/fire debt and individual trajectories; common-state compression may share identical immutable parameters only. No selection of the first128 droids or replacing extra droids with a damage multiplier. If exact continuation cannot allocate/process safely, technical pause preserves the state instead of losing the earned tail.

## Ability rank defaults and continuations

Adopt the existing18-entry Balance ability base/growth rows as initial numerical data, with the explicit target replacements below. Derive from rank/source state once; do not reapply primary attributes. Let e=rank-1, z=min(e,4). Radius=base*(1+radiusGrowth*z); damage=base*(1+damageGrowth*e) preserving fractions; duration=base*(1+durationGrowth*e); tick interval=baseInterval/(1+frequencyGrowth*e). For recharge growth g, factor=1-g*e for e<=4, otherwise `(1-4*g)/(1+g*(e-4))`; positive checked arithmetic, no max-rank plateau. For g=0 cooldown remains base. Targets/armies/counts still grow under their named rule, independently of physical size stopping at rank5. Tagged Blast Radius applies afterward once.

| Target ability | Adopted base / explicit override | Extra rank semantics beyond shared source growth |
|---|---|---|
| Laser Rings | Persistent; radius18, damage12, hit interval0.2; no8-second expiry/12-second downtime | Blades3+e, radius+8%/rank through5, damage+25%/rank; individual blade/victim debt preserved |
| Deflector Shield | One persistent Player-owned point shield, never prototype3-hit timed cast | Capacity20+5*e+1.25*paidCapacity; online regen2*(1+0.1*e)/s; reboot max(5,10-e) seconds |
| Lightning Ring | C14,D8,R25,damage8,tick0.5 | Source growth R10%,damage25%,duration10% |
| Blink Drive | C=max(12,30*0.95^e),R=35*(1+0.15*z),guard2 | Incoming-hit safety contract overrides manual prototype4-second tuning |
| Nuclear Missile | C30,D0.7,R55,damage250 | R15%,damage30%,recharge g0.05 |
| Space Collapse | C35,resolve0.2,R32,boss damage300; erase eligible normal victims without drops | Zones1+e; R15%; once per victim/cast across overlapping zones; no boss erasure |
| Radiant Halo | C8,D0.2,R32,damage60 | R15%,damage30%,recharge g0.05 |
| Repulsor Pulse | C5,D0.2,R30,no damage,push22 | R10%,recharge g0.05,push+15%/rank; resistance/solids constrain movement |
| Point-Defense Interceptor | C12,D8,R38,tick0.1 | R10%,duration15%; interception only eligible hostile projectiles |
| Scrap Magnet | C15,D5,collection radius60,tick0.2 | Radius60 fixed; duration20%,recharge g0.05,frequency10%; replaces global vacuum and collects only released pickups |
| Chain Lightning | C7,instant,R45,damage35 | R10%,damage25%,targets6+e; distinct nearest hops, no repeat victim |
| Hologram Clone | C18,D10,acquisition60,emission interval0.5,offset18 | Duration15%,frequency15%; native copied geometry damage scales by clone rank+25%/rank from its native component, no player modifiers/pattern/signatures. One active clone; recast waits for expiry |
| Combat Drone | Persistent slots=rank,damage15,HP30,fire interval0.4,range35 | Damage25%/rank; new/rebuilt HP30+15*e;20-second individual rebuild. No duration despawn/global recast/upgrade heal |
| Shield Detonation | C18,instant,R35,damage50; real break only | R10%,damage25%,recharge g0.10; new nineteenth ability replaces Nano Repair |
| Plasma Beam | C12,D4,R65,damage12,tick0.15 | R10%,damage25%,duration10%; independent target geometry |
| Corrosive Trail | C14,D8,R8,damage6,tick0.3,pool lifetime3 | R15%,damage25%,duration10%; emission pool cadence0.3, no per-frame pool spawn |
| Singularity | C22,D6,R42,damage10,tick0.2 | R10%,damage25%,duration10%; pull28 units/s, legal movement, normal rewards |
| Realm Breaker | C20,D6,R24,damage20,tick0.2 | R15%,damage25%,duration10%; preserve native rift geometry/blocks; no inferred BR tag |
| Armageddon | C35,D6,R22,damage80,tick0.3 | R10%,damage20%,blasts per tick1+e; exact earned count, isolated ability RNG, normal rewards |

C=cooldown,D=duration,R=world radius/range; geometry distinction follows the targeting matrix and existing typed effects. A continuous ability with duration>=cooldown does not stack duplicate windows; after expiry, ready trigger may start another window, carrying existing debt. Rank changes do not recast an active effect. Count/rank increases affecting a persistent army add earned slots without healing existing ones; active transient casts retain their snapshot. Clone native tick damage/target rules are copied but its own fire cadence above drives supported native root emissions; flame burn/continuous geometry still requires real handlers before claiming compatibility.

Shield reboot details adopt the retained gameplay target: after delay, restore50% of current normal capacity once, then add the remaining captured half over3 combat seconds, with normal regen suspended during that restoration. Hits can deplete restored points and break again; never force a minimum percentage every frame. Capture capacity when restoration begins, preserve actual current points/debt when ranks change. Batteries may add paid charge immediately and revive online if positive, cancel pending reboot/restoration without extra free restoration; overcharge never regenerates. Normal capacity regen has no prototype3-second equipment delay in this target. Field/shopping/return protection do not refill shield; hull never passively regenerates.

## Resource budgets and measurements

| Work / presentation | Initial contract |
|---|---|
| Ordinary natural insertions | Max32 per simulation update; quotas retained and blocked opportunities discarded as encounter contract specifies |
| Pickup physical storage | Target enemy reward pool500, debris pool150; pool-full merges conserve exact trade/Salvage, family becomes Mixed when needed; no enemy expiry. Source currently shares150 and requires migration |
| Cosmetic transients | High max512 projectile trails/impacts,128 skill flashes,32 trail decorations; Medium half, Low quarter; required damage geometry/telegraphs/sprites/HUD unaffected |
| Collision / targeting | Spatial queries exact for damage; existing bounded crowd-neighbor separation remains approximate motion only. Never reuse its24-candidates-per-cell truncation for damage/reward queries |
| Benchmarks |1280x720 initial window,3840x2160 logical canvas, Medium and Low; report actual CPU/GPU/RAM/build/toolchain and seed, never invent minimum specs |
| Runtime release target |60 FPS target; over a120-combat-second sample, p95 update+draw CPU time<=16.67ms and p99<=33.33ms, no single unexplained stall>100ms; GPU/presentation frame times recorded separately |

Required reproducible loads: (A)300 normal enemies,50 droids,32 blades,500 logical projectiles; (B)1500 normal enemies,4 bosses,200 droids,128 blades,2000 logical projectiles; (C)10,000 normal debug enemies,16 bosses,1000 droids,1000 blades and10,000 logical projectiles as diagnostic stress, not promised release FPS. Debug mutations make results unranked. Repeat physical/aggregate comparisons at ranks1/5/100/1000 and synthetic near-counter/float boundaries. Record memory peak and plateau across ten reset/restart cycles; no surviving run IDs, reservations, pickups, emitters or animation entries. A load outside measured capacity must remain disclosed; no silent rank cap is justified by a failed benchmark.

Verify reward conservation under split/merge/death/Collapse/cleanup/overkill, exact T5 counters under coalescing, independent critical distribution, pause/hub/focus clocks, same-step death ordering, malformed values, failed allocations/quotes and retry idempotence. The checks in this documentation session verify tables/formulas/policies only. Actual scalar/aggregate correctness, release profiling, hardware evidence and numerical integration remain T04/T06/T08/T10/REVIEW tasks.
