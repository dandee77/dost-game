#include "DebrisManager.hpp"
#include <algorithm>
#include <cmath>
#include <vector>
#include "Balance.hpp"
#include "raymath.h"
DebrisManager::DebrisManager() : debrisSpawnCooldown(Balance::DEBRIS_SPAWN_START) {}
void DebrisManager::reset()
{
    debris.clear();
    debrisSpawnCooldown = Cooldown(Balance::DEBRIS_SPAWN_START);
}
void DebrisManager::update(Vector2 playerPos, const GameTimer& gameTimer)
{
    const float elapsed = gameTimer.getElapsedTime();
    const float cooldown = std::max(Balance::DEBRIS_SPAWN_MIN, Balance::DEBRIS_SPAWN_START -
        elapsed / Balance::DEBRIS_SPAWN_RAMP_TIME * (Balance::DEBRIS_SPAWN_START - Balance::DEBRIS_SPAWN_MIN));
    debrisSpawnCooldown.updateCooldownDuration(cooldown);
    if (!debrisSpawnCooldown.isOnCooldown()) {
        const int count = GetRandomValue(1, Balance::DEBRIS_MAX_SPAWN_BATCH);
        for (int i = 0; i < count; ++i) spawnDebris(playerPos);
        debrisSpawnCooldown.startCooldown();
    }
    std::vector<std::string> removed;
    for (auto& [id, item] : debris) {
        item->update();
        if (Vector2Distance(item->getPosition(), playerPos) > Balance::DEBRIS_DESPAWN_DISTANCE) removed.push_back(id);
    }
    for (const auto& id : removed) debris.erase(id);
}
void DebrisManager::draw() { for (auto& [id, item] : debris) item->draw(); }
void DebrisManager::spawnDebris(Vector2 playerPos)
{
    auto item = std::make_unique<Debris>(playerPos);
    const auto id = item->getDebrisID();
    debris.emplace(id, std::move(item));
}
bool DebrisManager::removeDebris(const std::string& id, bool harvestable)
{
    const auto found = debris.find(id);
    if (found == debris.end()) return false;
    found->second->destruct(harvestable);
    debris.erase(found);
    return true;
}
#ifdef GAME_DEBUG
void DebrisManager::spawnGallery(Vector2 playerPos)
{
    for (int i = 0; i < DEBRIS_KIND_COUNT; ++i) {
        auto item = std::make_unique<Debris>(playerPos, static_cast<DebrisKind>(i));
        const float angle = 2.0f * PI * i / static_cast<float>(DEBRIS_KIND_COUNT);
        item->position = Vector2Add(playerPos, Vector2Scale({std::cos(angle), std::sin(angle)}, Balance::DEBRIS_PREVIEW_RADIUS));
        item->velocity = {};
        const auto id = item->getDebrisID();
        debris.emplace(id, std::move(item));
    }
}
#endif
