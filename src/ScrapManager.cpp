#include "ScrapManager.hpp"
#include <algorithm>
#include <limits>
#include "Balance.hpp"
#include "ResourceManager.hpp"
#include "Theme.hpp"
#include "raymath.h"

void ScrapManager::spawnScrap(Vector2 position, int value)
{
    if (value <= 0) return;
    if (pickups.size() >= Balance::SCRAP_MAX_PICKUPS) { pickups.front()->addValue(value); return; }
    pickups.push_back(std::make_unique<ScrapPickup>(position, value, Theme::SCRAP_ORB_SIZE));
}

int ScrapManager::collectAll()
{
    int value = 0;
    for (const auto& pickup : pickups) value += pickup->getValue();
    pickups.clear();
    return value; // Pending destruction stays intact until its visible handoff.
}

void ScrapManager::spawnDebris(Vector2 center, float angle, DebrisKind kind, float drawSize, bool harvestable)
{
    destructions.push_back({center, angle, drawSize,
        harvestable ? Balance::DEBRIS_SCRAP_VALUES[kind] : 0, harvestable, kind, DEBRIS_INFO[kind].destructTexture,
        Theme::FRAMES_DEBRIS_DESTRUCT});
}

void ScrapManager::spawnDestruction(Vector2 center, float angle, float drawSize, const std::string& textureKey)
{
    // Cosmetic deaths share the simulation clock/reset path, with no pickup phase.
    const auto& sheet = ResourceManager::GetInstance().GetTextureRef(textureKey);
    const int frames = sheet.width / Theme::DEBRIS_FRAME;
    if (sheet.id == 0 || frames <= 0) return;
    destructions.push_back({center, angle, drawSize, 0, false, DEBRIS_CLUMP, textureKey, frames});
}

int ScrapManager::releasePickups(const Destruction& destruction, float remainingDt, Vector2 playerPosition)
{
    const auto& visual = Theme::DEBRIS_SCRAP_VISUALS[destruction.kind];
    const int exitCount = static_cast<int>(visual.exitPixels.size());
    if (pickups.size() + exitCount > Balance::SCRAP_MAX_PICKUPS) {
        // Preserve earned value under load, after the complete visible explosion.
        ScrapPickup* nearest = nullptr;
        float nearestDistance = std::numeric_limits<float>::max();
        for (auto& pickup : pickups) {
            const float distance = Vector2DistanceSqr(destruction.center, pickup->getPosition());
            if (distance < nearestDistance) { nearest = pickup.get(); nearestDistance = distance; }
        }
        if (nearest) { nearest->addValue(destruction.value); return 0; }
    }
    int collected = 0;
    for (int i = 0; i < exitCount; ++i) {
        const auto pixel = visual.exitPixels[i];
        const float scale = destruction.drawSize / Theme::DEBRIS_FRAME;
        const Vector2 offset = {(pixel.x - Theme::DEBRIS_FRAME / 2.0f) * scale,
            (pixel.y - Theme::DEBRIS_FRAME / 2.0f) * scale};
        const auto position = Vector2Add(destruction.center, Vector2Rotate(offset, destruction.angle * DEG2RAD));
        const int value = destruction.value / exitCount +
            (i < destruction.value % exitCount ? 1 : 0);
        auto pickup = std::make_unique<ScrapPickup>(position, value, visual.orbSize);
        // Only time beyond the handoff belongs to the newly spawned orb.
        pickup->advance(remainingDt, playerPosition);
        if (pickup->isCollected()) collected += value;
        else if (!pickup->isExpired()) pickups.push_back(std::move(pickup));
    }
    return collected;
}

int ScrapManager::update(float dt, Vector2 playerPosition)
{
    if (dt <= 0.0f) return 0;
    int collected = 0;
    for (auto& pickup : pickups) {
        pickup->advance(dt, playerPosition);
        if (pickup->isCollected()) collected += pickup->getValue();
    }
    std::erase_if(pickups, [](const auto& pickup) { return pickup->isCollected() || pickup->isExpired(); });
    for (auto& destruction : destructions) {
        destruction.elapsed += dt;
        if (!destruction.released && destruction.elapsed >= Theme::SCRAP_HANDOFF_TIME) {
            destruction.released = true;
            if (destruction.harvestable)
                collected += releasePickups(destruction, destruction.elapsed - Theme::SCRAP_HANDOFF_TIME, playerPosition);
        }
    }
    std::erase_if(destructions, [](const auto& destruction) {
        return destruction.elapsed >= destruction.frameCount * Theme::DEBRIS_DESTRUCT_FRAME_TIME;
    });
    return collected;
}

void ScrapManager::draw()
{
    for (const auto& destruction : destructions) {
        const auto& sheet = ResourceManager::GetInstance().GetTextureRef(destruction.textureKey);
        if (sheet.id == 0) continue;
        const int frame = std::min(static_cast<int>(destruction.elapsed / Theme::DEBRIS_DESTRUCT_FRAME_TIME),
            destruction.frameCount - 1);
        const float frameSize = static_cast<float>(Theme::DEBRIS_FRAME);
        DrawTexturePro(sheet, {frame * frameSize, 0, frameSize, frameSize},
            {destruction.center.x, destruction.center.y, destruction.drawSize, destruction.drawSize},
            {destruction.drawSize / 2.0f, destruction.drawSize / 2.0f}, destruction.angle, WHITE);
    }
    for (auto& pickup : pickups) pickup->draw();
}

int ScrapManager::pendingValue() const
{
    int value = 0;
    for (const auto& destruction : destructions) if (!destruction.released) value += destruction.value;
    for (const auto& pickup : pickups) value += pickup->getValue();
    return value;
}
