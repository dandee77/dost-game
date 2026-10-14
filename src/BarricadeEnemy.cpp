#include "BarricadeEnemy.hpp"
#include "Animator.hpp"
#include "Balance.hpp"
#include "ResourceManager.hpp"
#include "Theme.hpp"
#include "raymath.h"
#include <algorithm>
#include <cmath>

BarricadeEnemy::BarricadeEnemy(const std::string& id, Vector2 eventCenter, float angle)
    : Enemy(id, BARRICADE_ENEMY, eventCenter, eventCenter), center(eventCenter)
{
    health = Balance::BARRICADE_HEALTH;
    damage = Balance::PLAYER_CONTACT_DAMAGE;
    speed = 0.0f;
    velocity = knockbackVelocity = {};
    knockbackDecay = 0.0f;
    radialDirection = {std::cos(angle), std::sin(angle)};
    position = Vector2Add(center, Vector2Scale(radialDirection, Balance::BARRICADE_START_RADIUS));
    previousPosition = position;
    rotation = angle * RAD2DEG;
    spriteSize = Theme::BARRICADE_DRAW_SIZE;
    origin = {spriteSize / 2.0f, spriteSize / 2.0f};
    rect = {position.x, position.y, spriteSize, spriteSize};
    hitbox = {position.x, position.y, Balance::BARRICADE_BODY_RADIUS, Balance::BARRICADE_BODY_RADIUS};
    const auto& texture = ResourceManager::GetInstance().GetTextureRef("asteroid");
    auto& animator = Animator::GetInstance();
    animator.AddAnimation(enemyID, std::make_shared<Animation>(texture, texture.width, texture.height,
        Theme::BARRICADE_IDLE_FRAME_TIME, true, rect, false, WHITE));
    animator.SetOrigin(enemyID, origin);
    animator.SetRotation(enemyID, rotation);
    animator.Play(enemyID);
}

void BarricadeEnemy::update() { advance(GetFrameTime()); }

void BarricadeEnemy::advance(float dt)
{
    previousPosition = position;
    elapsed += std::max(0.0f, dt);
    const float fraction = std::min(1.0f, elapsed / Balance::BARRICADE_DURATION);
    const float radius = Lerp(Balance::BARRICADE_START_RADIUS, Balance::BARRICADE_END_RADIUS, fraction) +
        std::max(0.0f, elapsed - Balance::BARRICADE_DURATION) * Balance::BARRICADE_SCATTER_SPEED;
    // Freeze the orbit heading at release so scattered rocks travel straight out.
    const float orbit = Balance::BARRICADE_ORBIT_SPEED * DEG2RAD * std::min(elapsed, Balance::BARRICADE_DURATION);
    position = Vector2Add(center, Vector2Scale(Vector2Rotate(radialDirection, orbit), radius));
    rect.x = hitbox.x = position.x;
    rect.y = hitbox.y = position.y;
    rotation += Theme::BARRICADE_SPIN * dt;
}

void BarricadeEnemy::draw()
{
    auto& animator = Animator::GetInstance();
    animator.SetPosition(enemyID, position);
    animator.SetRotation(enemyID, rotation);
}

void BarricadeEnemy::destruct()
{
    const auto& sheet = ResourceManager::GetInstance().GetTextureRef("asteroid_destruct");
    if (sheet.id == 0) return;
    auto& animator = Animator::GetInstance();
    animator.Remove(enemyID);
    animator.AddAnimation(enemyID, std::make_shared<Animation>(sheet, sheet.width / Theme::BARRICADE_DESTRUCT_FRAMES,
        sheet.height, Theme::BARRICADE_DESTRUCT_FRAME_TIME, false, rect, false, WHITE));
    animator.SetOrigin(enemyID, origin);
    animator.SetRotation(enemyID, rotation);
    animator.Play(enemyID);
}
