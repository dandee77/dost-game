# Boss roster for review — 24 October 2026

**25 October adoption:** [Complete encounter appendix](beta-encounters.md) adopts all four identities/base tuning, 60%/30% phases, attack geometry/selection, adds/ownership/death and legal arenas. Older proposal/review language below is historical. Written PREP-01 data is complete; actual bosses/art/telegraphs/playtesting remain T06/PROJECT-07/T10.

**25 October Q28 boss art:** Living cores remain mostly hidden behind scrap shells, with small organic seams. Shellback recovery parts armor enough to suggest binding tissue, not a fully exposed body. All four follow [creature direction](../09-art/creature-direction.md); visual seams create no extra weak point, hitbox, phase or damage rule.

**24 October Q25 retirement:** A living Boss-mode player at the station can confirm Retire Run, preserving earned score, boss clears and active time as Retired. No pending encounter credit, extra reward or cycle advance. Cancel preserves the upcoming automatic boss. No mid-fight retirement/travel or revival; [current contract](../../context/game-design.md#24-october-boss-mode-retirement---q25-confirmed).

**24 October Q24 sequence:** Boss mode uses an automatic repeating Shellback -> Coilmaw -> Brood Hauler -> Nestheart order, with each next spawn waiting for deliberate station launch. No boss picker. [Current sequence contract](../../context/game-design.md#24-october-automatic-boss-sequence---q24-confirmed) covers ordinals, resets, failures and repeats. All four are required for the authored beta; implementing one at a time does not reduce that scope.

**Confirmed Boss-mode rule:** no retreat during a fight. Only the post-kill portal returns to base, without shield/energy requirements. The old starting-energy workaround is retired; zero energy cannot strand a victorious living player. Pause/settings remain available and quit abandons the run.

**Owner follow-up:** Boss mode now repeats boss kill -> base portal -> services -> launch next boss, preserving the current run. It does not end after one boss. Boss phases and a named HP bar per living boss are requested. The [latest numerical authority](../../context/game-design.md#24-october-boss-mode-loop--owner-revision) records proposed phase thresholds, safe transitions, encounter cleanup and the confirmed boss-clear shield/energy bypass. The old Boss-mode half-energy start below is superseded, not adopted.

The owner asked us to draft the bosses and attacks. These concepts are **proposals**, not approved names, finished art or implemented encounters. Numerical authority, attack tables and timing rules are in [game-design.md](../../context/game-design.md#24-october-fresh-run-rule-and-boss-review-draft).

All bosses are mutated organisms inside salvaged shells. They fit the existing biological/source-containment story; they are not autonomous machines. Each boss derives from the planned Boss/Enemy boundary. Reuse encounters across modes rather than creating a separate boss class for every mode.

| Proposed boss | Identity and core fight | Modes |
|---|---|---|
| **Shellback** | A broad organism armored with compressed panels. It marks a charge lane, rushes through it, then exposes its body during recovery. Its scrap fan prevents standing directly in front forever. | Campaign C01; Boss sequence slot 1; Chaos |
| **Coilmaw** | A narrow organism wrapped in cable and coil fragments. It fires aimed volleys and a clearly indicated sweeping discharge. The player moves around it instead of outrunning a homing laser. | Campaign C02; Boss sequence slot 2; Chaos |
| **Brood Hauler** | A mobile nest inside a broken cargo shell. It releases small enemies and places temporary residue pools. Killing adds opens space; occupied spawn slots suppress further releases. | Campaign C03; Boss sequence slot 3; Chaos |
| **Nestheart** | A large nest attached to the contaminated recovery infrastructure. It combines broad volleys, a ring with a visible safe opening and small reinforcement groups. Defeating it isolates the campaign's main source. | Campaign C04; Boss sequence slot 4; Chaos |

**Current beta scope:** all four bosses serve the authored Campaign and automatic Boss sequence; none is an optional final-beta omission. Implement and test one encounter at a time without marking the full mode complete early. Chaos uses finished enabled types, including reinforcement instances with unique identity/state; Swarm remains boss-free and shares ordinary mechanics with Chaos. Campaign assignments are C01/C02/C03/C04 as above; no beta miniboss is required. Older two-boss scope/miniboss recommendations are superseded.

## Intended progression and fairness

Early bosses teach one readable behavior. Later chaos comes from overlapping pursuers, ordinary enemies and player abilities. Boss health grows slowly and stops at 1.5x; damage does not scale with elapsed time or difficulty. Every phase retains room to dodge, no mandatory weapon counter, no untelegraphed spawn hit and no automatic full heal.

Only two major telegraphs reserve space simultaneously. This limits unavoidable attack combinations without limiting how many bosses can pursue. Increasing boss count and ordinary add pressure must still fit the measured frame-time budget. A full population budget delays adds without queuing a giant release later.

At 100 actual single-target DPS, base-health kill times before interruptions are 12/16/20/28 seconds. At 40 actual DPS they are 30/40/50/70 seconds. These are analytical checks, not measured encounter times; movement, target access, adds and player AoE change the result. If later builds melt a boss, increase encounter variety before increasing HP.

Boss mode starts with a fresh build and the confirmed basic shield. Ordinary mid-fight retreat is forbidden. Only the post-kill portal returns a surviving player without energy/shield gates; the older half-energy starting grant is retired. A same-step player/boss death counts the kill but ends the run under Q19/Q20, without revival.

## Implementation and review gates

- Complete state/attack/add/cleanup data for all four required beta encounters; do not treat the old optional-pair recommendation as a scope cut.
- Implement the shared boss base and encounter ownership, then one boss at a time. The written roster is not T06 completion.
- Verify attack tell/active/recovery timing at several frame rates, pause/hub suspension, finite boss damage from erasure skills, shared add caps and one-time rewards/source resolution.
- Test every weapon family against each boss, overlapping attacks, portal re-entry, simultaneous defeat/victory and repeated instances with unique Animator IDs.
- Profile progressively larger Chaos overlaps; document supported load rather than promising unlimited concurrent simulation.

No new assets, names in shipped UI, enemy stats in source or mode behavior are changed by this draft.
