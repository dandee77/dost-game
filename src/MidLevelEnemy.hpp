#pragma once
#include "raylib.h"
#include "Enemy.hpp"
#include <string>
#include "Timer.hpp"

class MidLevelEnemy : public Enemy
{
private:
    Vector2 currentDirection;
    float turnSpeed;
    const std::string textureName;
    float bulletSpeed;
    Cooldown fireCooldown; 
    float fireRange = 1.85f;

public:
    MidLevelEnemy(std::string enemyID, EnemyType type, Vector2 spawnPos, Vector2 playerPos, double combatSeconds = 0);
    void update() override;
    void draw() override;
    void destruct() override;

protected:
    void advanceCooldowns(float dt) override;
};
