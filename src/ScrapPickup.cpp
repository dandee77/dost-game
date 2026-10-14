#include "ScrapPickup.hpp"
#include <algorithm>
#include <cmath>
#include "Balance.hpp"
#include "ResourceManager.hpp"
#include "Theme.hpp"
#include "raymath.h"

ScrapPickup::ScrapPickup(Vector2 center, float angle, DebrisKind debrisKind, float drawSize,
    int fragment, int scrapValue, bool canCollect)
    : kind(debrisKind), initialRotation(angle), value(scrapValue), harvestable(canCollect)
{
    const int column = fragment % Theme::SCRAP_COLUMNS, row = fragment / Theme::SCRAP_COLUMNS;
    const float width = Theme::DEBRIS_BODY.width / Theme::SCRAP_COLUMNS;
    const float height = Theme::DEBRIS_BODY.height / Theme::SCRAP_ROWS;
    source = {Theme::DEBRIS_BODY.x + column * width, Theme::DEBRIS_BODY.y + row * height, width, height};
    const float scale = drawSize / Theme::DEBRIS_FRAME;
    const Vector2 offset = {(source.x + width / 2.0f - Theme::DEBRIS_FRAME / 2.0f) * scale,
        (source.y + height / 2.0f - Theme::DEBRIS_FRAME / 2.0f) * scale};
    startPosition = position = Vector2Add(center, Vector2Rotate(offset, angle * DEG2RAD));
    // Full-height strips keep thin/diagonal objects visible in every fragment.
    // Exit headings are identical for every variant, independent of its silhouette.
    const float exitAngle = 2.0f * PI * fragment / Theme::SCRAP_FRAGMENTS + angle * DEG2RAD;
    scatterDirection = {std::cos(exitAngle), std::sin(exitAngle)};
    rect = {position.x, position.y, width * scale, height * scale};
    origin = {rect.width / 2.0f, rect.height / 2.0f};
    rotation = angle;
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
    const float scatter = std::min(elapsed, Balance::SCRAP_SCATTER_TIME) / Balance::SCRAP_SCATTER_TIME;
    if (previous < Balance::SCRAP_SCATTER_TIME) {
        const float distance = Balance::SCRAP_SCATTER_DISTANCE * (1.0f - (1.0f - scatter) * (1.0f - scatter));
        position = Vector2Add(startPosition, Vector2Scale(scatterDirection, distance));
    }
    rotation = initialRotation + Theme::SCRAP_SPIN * std::min(elapsed, Balance::SCRAP_SCATTER_TIME);
    if (!harvestable || elapsed <= Balance::SCRAP_SCATTER_TIME) return;
    const float travelTime = elapsed - std::max(previous, Balance::SCRAP_SCATTER_TIME);
    const Vector2 difference = Vector2Subtract(target, position);
    const float distance = Vector2Length(difference), step = speed * travelTime;
    // Swept arrival: do not overshoot the ship at low frame rates.
    if (distance <= step + Balance::SCRAP_PICKUP_RADIUS) {
        position = target;
        collected = true;
    } else {
        position = Vector2Add(position, Vector2Scale(difference, step / distance));
    }
}

bool ScrapPickup::isExpired() const
{
    return elapsed >= (harvestable ? Balance::SCRAP_LIFETIME : Balance::SCRAP_SCATTER_TIME);
}

void ScrapPickup::draw()
{
    if (collected || isExpired()) return;
    const auto& texture = ResourceManager::GetInstance().GetTextureRef(DEBRIS_INFO[kind].texture);
    if (texture.id == 0) return;
    const float glow = harvestable ? std::clamp((elapsed - Balance::SCRAP_GLOW_START) /
        (Balance::SCRAP_SCATTER_TIME - Balance::SCRAP_GLOW_START), 0.0f, 1.0f) : 0.0f;
    const float alpha = harvestable ? 1.0f : 1.0f - elapsed / Balance::SCRAP_SCATTER_TIME;
    if (glow > 0.0f) {
        for (std::size_t i = 0; i < Theme::SCRAP_GLOW_SCALES.size(); ++i)
            DrawCircleV(position, Theme::SCRAP_GLOW_SIZE * Theme::SCRAP_GLOW_SCALES[i],
                Fade(Theme::COLOR_HARVEST, glow * Theme::SCRAP_GLOW_ALPHAS[i]));
    }
    const Color tint = {255, static_cast<unsigned char>(255.0f + (Theme::COLOR_HARVEST.g - 255.0f) * glow),
        static_cast<unsigned char>(255.0f + (Theme::COLOR_HARVEST.b - 255.0f) * glow),
        static_cast<unsigned char>(255.0f * alpha)};
    DrawTexturePro(texture, source, {position.x, position.y, rect.width, rect.height}, origin, rotation, tint);
}
