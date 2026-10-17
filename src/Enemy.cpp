#include "Enemy.hpp"
#include "Theme.hpp"
#include "Balance.hpp"
#include "raymath.h"
#include <algorithm>

void Enemy::applyStun(float duration)
{
    // Formation segments must keep the event's shared movement clock.
    if (enemyType != BARRICADE_ENEMY) stunRemaining = std::max(stunRemaining, duration);
}
void Enemy::applyCorrosion(float duration)
{
    if (enemyType != BARRICADE_ENEMY) corrosionRemaining = std::max(corrosionRemaining, duration);
}

void Enemy::updateWithStatus(float dt)
{
    const bool stunned = isStunned();
    const float originalSpeed = speed;
    const Vector2 before = position;
    if (isCorroded()) speed *= Balance::SKILL_SLOW_MULTIPLIER;
    if (!stunned) update();
    // Include inertia/knockback movement in slow, without permanently editing base stats.
    if (isCorroded()) {
        const Vector2 moved = Vector2Subtract(position, before);
        const float allowed = originalSpeed * Balance::SKILL_SLOW_MULTIPLIER * dt;
        if (Vector2Length(moved) > allowed)
            applySeparation(Vector2Subtract(Vector2Scale(Vector2Normalize(moved), allowed), moved));
    }
    speed = originalSpeed;
    stunRemaining = std::max(0.0f, stunRemaining - dt);
    corrosionRemaining = std::max(0.0f, corrosionRemaining - dt);
}

int Enemy::getContactDamage() const
{
    return isCorroded() ? std::max(1, static_cast<int>(Balance::PLAYER_CONTACT_DAMAGE * Balance::SKILL_WEAKEN_MULTIPLIER)) :
        Balance::PLAYER_CONTACT_DAMAGE;
}

void Enemy::applySeparation(Vector2 displacement)
{
    position = Vector2Add(position, displacement);
    rect.x = hitbox.x = position.x;
    rect.y = hitbox.y = position.y;
}

void Enemy::takeDamage(int damage) {
    health -= damage;
    hitReactionRemaining = Theme::PROJECTILE_HIT_FLASH_TIME;
    hitReactionFresh = true;
    if (health < 0) {
        health = 0;
    }
}

void Enemy::advanceHitReaction(float dt)
{
    if (hitReactionFresh) {
        hitReactionFresh = false;
        return;
    }
    hitReactionRemaining = std::max(0.0f, hitReactionRemaining - dt);
}

Color Enemy::getHitTint() const
{
    return hitReactionRemaining > 0.0f ? Theme::COLOR_PROJECTILE_HIT : WHITE;
}

void Enemy::applyKnockback(Vector2 direction, float force) {
    knockbackVelocity = Vector2Scale(Vector2Normalize(direction), force);
    knockbackDecay = 0.9f; 
    knockbackCooldown.startCooldown(); 
}

bool Enemy::canReceiveKnockback() const {
    return !knockbackCooldown.isOnCooldown();
}
