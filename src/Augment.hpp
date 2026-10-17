#pragma once
#include <array>
#include <string_view>

class Player;
enum AugmentId {
    AUG_WEAPONS_PAYLOAD, AUG_CRITICAL_MATRIX, AUG_OVERCLOCKED_CHAMBERS, AUG_RAPID_FIRE,
    AUG_REINFORCED_HULL, AUG_NANO_REPAIR, AUG_PHASE_SHIFT, AUG_THRUSTER_OVERDRIVE,
    AUG_GYRO_CONTROL, AUG_ARMOR_PIERCING, AUG_INERTIA_IMPACT, AUG_SCATTER_SHOT,
    AUG_BROADSIDE_CANNONS, AUG_TAIL_GUNNER, AUG_COUNT
};
struct AugmentInfo { AugmentId id; const char* key; const char* title; const char* description; };
const std::array<AugmentInfo, AUG_COUNT>& augmentCatalog();
AugmentId findAugment(std::string_view key);
bool applyAugment(Player& player, AugmentId id);
