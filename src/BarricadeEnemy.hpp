#pragma once
#include "Enemy.hpp"

class BarricadeEnemy final : public Enemy
{
public:
    BarricadeEnemy(const std::string& id, Vector2 center, float angle);
    void update() override;
    void advance(float dt);
    void draw() override;
    void destruct() override;
    bool canReceiveKnockback() const override { return false; }
    Vector2 getPreviousPosition() const override { return previousPosition; }
private:
    Vector2 center = {};
    Vector2 radialDirection = {};
    Vector2 previousPosition = {};
    float elapsed = 0.0f;
    float spinSpeed = 0.0f;
};
