#include "Enemy.hpp"
#include "Theme.hpp"
#include "raymath.h"
#include <algorithm>

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
