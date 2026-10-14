#include "Bullet.hpp"
#include "raymath.h"
#include "ResourceManager.hpp"
#include "Theme.hpp"
#include <algorithm>
#include <cmath>

Bullet::Bullet(Vector2 pos, Vector2 direction, bool isEnemy, int pierce, float knockback)
    : position(pos), fireDirection(Vector2Normalize(direction)), enemyBullet(isEnemy), piercePower(pierce), knockbackPower(knockback)
{
    previousPosition = position;
    angle = atan2f(fireDirection.y, fireDirection.x) * RAD2DEG;
}

void Bullet::update()
{
    previousPosition = position;
    animationTime += GetFrameTime();
    position = Vector2Add(Vector2Scale(fireDirection, speed * GetFrameTime()), position);
}

void Bullet::draw(const Texture2D &texture) const
{
    if (kind != PROJECTILE_LEGACY) {
        const char* key = kind == PROJECTILE_CANNON ? "player_projectile_auto_cannon_bullet" :
            kind == PROJECTILE_ROCKET ? "player_projectile_rocket" : "player_projectile_big_space_gun";
        const auto& sheet = ResourceManager::GetInstance().GetTextureRef(key);
        if (sheet.id == 0) return;
        const int frames = sheet.width / Theme::PROJECTILE_FRAME;
        const int frame = static_cast<int>(animationTime / Theme::EQUIPMENT_FRAME_TIME) % frames;
        const float size = kind == PROJECTILE_HEAVY ? Theme::HEAVY_DRAW_SIZE :
            kind == PROJECTILE_ROCKET ? Theme::ROCKET_DRAW_SIZE : Theme::CANNON_DRAW_SIZE;
        DrawTexturePro(sheet, {static_cast<float>(frame * Theme::PROJECTILE_FRAME), 0.0f,
            static_cast<float>(Theme::PROJECTILE_FRAME), static_cast<float>(Theme::PROJECTILE_FRAME)},
            {position.x, position.y, size, size}, {size / 2.0f, size / 2.0f}, angle + 90.0f, WHITE);
        return;
    }
    Vector2 size = isEnemyBullet() ? Vector2{8.0f, 8.0f} : Vector2{8.0f, 5.0f};
    Vector2 drawPos = position;

    DrawTexturePro(
        texture,
        {0, 0, (float)texture.width, (float)texture.height},
        {drawPos.x, drawPos.y, size.x, size.y},
        {size.x / 2.0f, size.y / 2.0f},
        angle,
        WHITE
    );
}

void Bullet::configure(ProjectileKind newKind, int newDamage, float newRadius, float newSpeed)
{
    kind = newKind;
    damage = newDamage;
    radius = newRadius;
    speed = newSpeed;
}

bool Bullet::hasHit(const std::string& id) const
{
    return std::find(hitIds.begin(), hitIds.end(), id) != hitIds.end();
}

void Bullet::recordHit(const std::string& id) { hitIds.push_back(id); }

float Bullet::hitFraction(Vector2 from, Vector2 to, Vector2 center, float targetRadius)
{
    const Vector2 offset = Vector2Subtract(from, center);
    const Vector2 travel = Vector2Subtract(to, from);
    const float c = Vector2DotProduct(offset, offset) - targetRadius * targetRadius;
    if (c <= 0.0f) return 0.0f;
    const float a = Vector2DotProduct(travel, travel);
    if (a == 0.0f) return -1.0f;
    const float b = Vector2DotProduct(offset, travel);
    const float discriminant = b * b - a * c;
    if (discriminant < 0.0f) return -1.0f;
    const float t = (-b - std::sqrt(discriminant)) / a;
    return t >= 0.0f && t <= 1.0f ? t : -1.0f;
}
