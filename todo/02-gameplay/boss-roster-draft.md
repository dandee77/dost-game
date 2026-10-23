# Boss roster for review — 24 October 2026

The owner asked us to draft the bosses and attacks. These concepts are **proposals**, not approved names, finished art or implemented encounters. Numerical authority, attack tables and timing rules are in [game-design.md](../../context/game-design.md#24-october-fresh-run-rule-and-boss-review-draft).

All bosses are mutated organisms inside salvaged shells. They fit the existing biological/source-containment story; they are not autonomous machines. Each boss derives from the planned Boss/Enemy boundary. Reuse encounters across modes rather than creating a separate boss class for every mode.

| Proposed boss | Identity and core fight | Modes |
|---|---|---|
| **Shellback** | A broad organism armored with compressed panels. It marks a charge lane, rushes through it, then exposes its body during recovery. Its scrap fan prevents standing directly in front forever. | Campaign guardian at wave 5; Boss; Chaos |
| **Coilmaw** | A narrow organism wrapped in cable and coil fragments. It fires aimed volleys and a clearly indicated sweeping discharge. The player moves around it instead of outrunning a homing laser. | Optional Boss encounter; Chaos |
| **Brood Hauler** | A mobile nest inside a broken cargo shell. It releases small enemies and places temporary residue pools. Killing adds opens space; occupied spawn slots suppress further releases. | Optional Boss encounter; Chaos |
| **Nestheart** | A large nest attached to the contaminated recovery infrastructure. It combines broad volleys, a ring with a visible safe opening and small reinforcement groups. Defeating it isolates the campaign's main source. | Campaign final guardian at wave 10; Boss; Chaos |

**Scope recommendation:** finish Shellback and Nestheart first. Add Coilmaw and Brood Hauler only when their encounters are playable and tested. Chaos can already increase pursuit with reinforcement instances of finished types; every instance has its own identity and attack state. Swarm remains boss-free and Survival remains its selected five-minute crowd mode.

## Intended progression and fairness

Early bosses teach one readable behavior. Later chaos comes from overlapping pursuers, ordinary enemies and player abilities. Boss health grows slowly and stops at 1.5x; damage does not scale with elapsed time or difficulty. Every phase retains room to dodge, no mandatory weapon counter, no untelegraphed spawn hit and no automatic full heal.

Only two major telegraphs reserve space simultaneously. This limits unavoidable attack combinations without limiting how many bosses can pursue. Increasing boss count and ordinary add pressure must still fit the measured frame-time budget. A full population budget delays adds without queuing a giant release later.

At 100 actual single-target DPS, base-health kill times before interruptions are 12/16/20/28 seconds. At 40 actual DPS they are 30/40/50/70 seconds. These are analytical checks, not measured encounter times; movement, target access, adds and player AoE change the result. If later builds melt a boss, increase encounter variety before increasing HP.

Boss mode starts with a fresh build under the confirmed reset rule. The proposed half-energy start makes leaving that encounter possible before the boss pays salvage. It does not supply money, shield charge, levels or free repairs. This remains a review choice because it changes a mode's starting resources.

## Implementation and review gates

- Confirm the concepts and whether to include the optional pair in the first release.
- Implement the shared boss base and encounter ownership, then one boss at a time. The written roster is not T06 completion.
- Verify attack tell/active/recovery timing at several frame rates, pause/hub suspension, finite boss damage from erasure skills, shared add caps and one-time rewards/source resolution.
- Test every weapon family against each boss, overlapping attacks, portal re-entry, simultaneous defeat/victory and repeated instances with unique Animator IDs.
- Profile progressively larger Chaos overlaps; document supported load rather than promising unlimited concurrent simulation.

No new assets, names in shipped UI, enemy stats in source or mode behavior are changed by this draft.
