#include "ScrapPickup.hpp"
#include <algorithm>
#include "Balance.hpp"
#include "ResourceManager.hpp"
#include "Theme.hpp"
#include "raymath.h"

ScrapPickup::ScrapPickup(Vector2 spawnPosition, int scrapValue, float drawSize)
    : ScrapPickup(spawnPosition, ScrapReward{scrapValue, scrapValue}, drawSize, false) {}

ScrapPickup::ScrapPickup(Vector2 spawnPosition, ScrapReward value, float drawSize, bool keep)
    : reward(value), persistent(keep)
{
    position = spawnPosition;
    rect = {position.x, position.y, drawSize, drawSize};
    origin = {rect.width / 2.0f, rect.height / 2.0f};
    rotation = 0.0f;
    health = damage = 0;
    speed = Balance::SCRAP_MAGNET_SPEED;
    velocity = {};
}

void ScrapPickup::update() { advance(GetFrameTime(), attractTarget); }

void ScrapPickup::advance(float dt, Vector2 target)
{
    if (collected || isExpired() || dt <= 0.0f) return;
    const float previous = elapsed;
    elapsed += dt;
    // Show the glow at the exact fleck position briefly before absorption.
    if (elapsed <= Theme::SCRAP_ORB_HOLD_TIME) return;
    const float travelTime = elapsed - std::max(previous, Theme::SCRAP_ORB_HOLD_TIME);
    const Vector2 difference = Vector2Subtract(target, position);
    const float distance = Vector2Length(difference), step = speed * travelTime;
    if (distance <= step + Balance::SCRAP_PICKUP_RADIUS) {
        position = target;
        collected = true;
    } else {
        position = Vector2Add(position, Vector2Scale(difference, step / distance));
    }
}

bool ScrapPickup::isExpired() const { return !persistent && elapsed >= Balance::SCRAP_LIFETIME; }

void ScrapPickup::draw()
{
    if (collected || isExpired()) return;
    const auto& texture = ResourceManager::GetInstance().GetTextureRef("scrap_orb");
    if (texture.id == 0) return;
    DrawTexturePro(texture, {0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)},
        {position.x, position.y, rect.width, rect.height}, origin, 0.0f, WHITE);
}
