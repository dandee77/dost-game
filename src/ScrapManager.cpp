#include "ScrapManager.hpp"
#include <algorithm>
#include <limits>
#include "Balance.hpp"
#include "Theme.hpp"
#include "raymath.h"

void ScrapManager::spawnDebris(Vector2 center, float angle, DebrisKind kind, float drawSize, bool harvestable)
{
    const int total = harvestable ? Balance::DEBRIS_SCRAP_VALUES[kind] : 0;
    if (pickups.size() + Theme::SCRAP_FRAGMENTS > Balance::SCRAP_MAX_PICKUPS) {
        if (!harvestable) return;
        // Reclaim cosmetic-only bursts first. Never drop a player's earned value.
        std::erase_if(pickups, [](const auto& pickup) { return !pickup->canHarvest(); });
        if (pickups.size() + Theme::SCRAP_FRAGMENTS > Balance::SCRAP_MAX_PICKUPS) {
            ScrapPickup* nearest = nullptr;
            float nearestDistance = std::numeric_limits<float>::max();
            for (auto& pickup : pickups) {
                const float distance = Vector2DistanceSqr(center, pickup->getPosition());
                if (distance < nearestDistance) { nearest = pickup.get(); nearestDistance = distance; }
            }
            if (nearest) nearest->addValue(total);
            return;
        }
    }
    for (int i = 0; i < Theme::SCRAP_FRAGMENTS; ++i) {
        const int value = total / Theme::SCRAP_FRAGMENTS + (i < total % Theme::SCRAP_FRAGMENTS ? 1 : 0);
        pickups.push_back(std::make_unique<ScrapPickup>(center, angle, kind, drawSize, i, value, harvestable));
    }
}

int ScrapManager::update(float dt, Vector2 playerPosition)
{
    int collected = 0;
    for (auto& pickup : pickups) {
        pickup->advance(dt, playerPosition);
        if (pickup->isCollected()) collected += pickup->getValue();
    }
    std::erase_if(pickups, [](const auto& pickup) { return pickup->isCollected() || pickup->isExpired(); });
    return collected;
}
void ScrapManager::draw() { for (auto& pickup : pickups) pickup->draw(); }
int ScrapManager::pendingValue() const
{
    int value = 0;
    for (const auto& pickup : pickups) value += pickup->getValue();
    return value;
}
