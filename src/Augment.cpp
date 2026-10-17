#include "Augment.hpp"
#include "Player.hpp"

const std::array<AugmentInfo, AUG_COUNT>& augmentCatalog()
{
    static constexpr std::array<AugmentInfo, AUG_COUNT> catalog = {{
        {AUG_WEAPONS_PAYLOAD, "weapons-payload", "Weapons Payload", "Standard attack damage +15%"},
        {AUG_CRITICAL_MATRIX, "critical-matrix", "Critical Matrix", "+5% chance for double damage"},
        {AUG_OVERCLOCKED_CHAMBERS, "overclocked-chambers", "Overclocked Chambers", "Attack cooldown reduced by 10%"},
        {AUG_RAPID_FIRE, "rapid-fire", "Rapid Fire", "An extra shot in each burst"},
        {AUG_REINFORCED_HULL, "reinforced-hull", "Reinforced Hull", "+20 maximum hull and current hull"},
        {AUG_NANO_REPAIR, "nano-repair", "Nano Repair", "Restore 25% of maximum hull"},
        {AUG_PHASE_SHIFT, "phase-shift", "Phase Shift", "Post-hit invincibility +10%"},
        {AUG_THRUSTER_OVERDRIVE, "thruster-overdrive", "Thruster Overdrive", "Movement speed +10%"},
        {AUG_GYRO_CONTROL, "gyro-control", "Gyro Control", "Turn speed +10%"},
        {AUG_ARMOR_PIERCING, "armor-piercing", "Armor Piercing", "Projectiles pierce one more target"},
        {AUG_INERTIA_IMPACT, "inertia-impact", "Inertia Impact", "Shots push enemies back"},
        {AUG_SCATTER_SHOT, "scatter-shot", "Scatter Shot", "Add a projectile to the forward fan"},
        {AUG_BROADSIDE_CANNONS, "broadside-cannons", "Broadside Cannons", "Fire from both sides of the ship"},
        {AUG_TAIL_GUNNER, "tail-gunner", "Tail Gunner", "Add a rear-facing cannon"}
    }};
    return catalog;
}

AugmentId findAugment(std::string_view key)
{
    for (const auto& info : augmentCatalog()) if (key == info.key) return info.id;
    return AUG_COUNT;
}

bool applyAugment(Player& player, AugmentId id)
{
    return player.applyAugment(id);
}
