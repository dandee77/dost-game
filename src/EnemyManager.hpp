#pragma once
#include <vector>
#include <unordered_map>
#include <memory>
#include <random>
#include "BulletManager.hpp"
#include "Timer.hpp"
#include "raylib.h"
#include "Enemy.hpp"
#include <string>
#include "Animator.hpp"
#include "GameTimer.hpp"
#include "SpatialGrid.hpp"

class EnemyManager
{
public:

    static EnemyManager& GetInstance()
    {
        static EnemyManager instance;
        return instance;
    }

    void update(Vector2 playerPos, const GameTimer& gameTimer, const Vector2* decoy = nullptr, float decoyRange = 0.0f);
    void draw();
    std::unordered_map<std::string, std::unique_ptr<Enemy>>& getEnemies() { return enemies; };
    void removeEnemy(const std::string& id);
    void reset();
    void separateEnemies(float dt);
    std::vector<std::string> spawnBarricade(Vector2 center);
#ifdef GAME_DEBUG
    int spawnLowEnemies(Vector2 playerPos, int quantity);
#endif
private:

    EnemyManager() = default;
    void spawnEnemy(Vector2 playerPos, float elapsedTime);
    void advanceSpawning(Vector2 playerPos, double elapsed, double dt);

    int enemyCounter = 0; 
    std::unordered_map<std::string, std::unique_ptr<Enemy>> enemies; 
    double spawnCredit = 0;
    std::mt19937 lootRng{Balance::LOOT_SEED};
    SpatialGrid crowdGrid;
    std::vector<Enemy*> crowdEnemies;
};
