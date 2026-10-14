#include "Debris.hpp"
#include <cmath>
#include "Balance.hpp"
#include "ResourceManager.hpp"
#include "ScrapManager.hpp"
#include "Theme.hpp"
#include "raymath.h"

unsigned long long Debris::debrisCounter = 0;
Debris::Debris(Vector2 playerPos)
    : Debris(playerPos, static_cast<DebrisKind>(GetRandomValue(0, DEBRIS_KIND_COUNT - 1))) {}
Debris::Debris(Vector2 playerPos, DebrisKind debrisKind)
    : kind(debrisKind >= DEBRIS_CLUMP && debrisKind < DEBRIS_KIND_COUNT ? debrisKind : DEBRIS_CLUMP)
{
    health = 1;
    damage = Balance::PLAYER_CONTACT_DAMAGE;
    rotation = static_cast<float>(GetRandomValue(0, 359));
    rotationSpeed = static_cast<float>(GetRandomValue(Balance::DEBRIS_ROT_SPEED_MIN, Balance::DEBRIS_ROT_SPEED_MAX));
    speed = static_cast<float>(GetRandomValue(Balance::DEBRIS_SPEED_MIN, Balance::DEBRIS_SPEED_MAX));
    const float angle = DEG2RAD * static_cast<float>(GetRandomValue(0, 359));
    position = Vector2Add(playerPos, Vector2Scale({std::cos(angle), std::sin(angle)}, Balance::DEBRIS_SPAWN_DISTANCE));
    const float variation = DEG2RAD * static_cast<float>(GetRandomValue(-Balance::DEBRIS_ANGLE_VARIATION, Balance::DEBRIS_ANGLE_VARIATION));
    velocity = Vector2Scale(Vector2Rotate(Vector2Normalize(Vector2Subtract(playerPos, position)), variation), speed);
    const float drawSize = Theme::DEBRIS_DRAW_SIZES[kind];
    origin = {drawSize / 2.0f, drawSize / 2.0f};
    rect = {position.x, position.y, drawSize, drawSize};
    debrisID = "debris_" + std::to_string(debrisCounter++);
}
float Debris::getDebrisSize() const { return Balance::DEBRIS_RADII[kind]; }
void Debris::update()
{
    position = Vector2Add(position, Vector2Scale(velocity, GetFrameTime()));
    rotation += rotationSpeed * GetFrameTime();
}
void Debris::draw()
{
    const auto& texture = ResourceManager::GetInstance().GetTextureRef(getTextureKey());
    if (texture.id == 0) return;
    DrawTexturePro(texture, {0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)},
        {position.x, position.y, rect.width, rect.height}, origin, rotation, WHITE);
}
void Debris::destruct(bool harvestable)
{
    ScrapManager::GetInstance().spawnDebris(position, rotation, kind, rect.width, harvestable);
}
