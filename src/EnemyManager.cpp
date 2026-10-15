#include "EnemyManager.hpp"
#include "ResourceManager.hpp"
#include "raymath.h"
#include "LowLevelEnemy.hpp"
#include "MidLevelEnemy.hpp"
#include "BarricadeEnemy.hpp"
#include <iostream>
#include "Balance.hpp"
#include <cmath>
#include <algorithm>


#define ENEMY_MAX_DISTANCE 1000.0f
#define ENEMY_MAX_RANGE 100.0f
#define MID_LEVEL_ENEMY_SPAWN_START_TIME 150.0f 

void EnemyManager::update(Vector2 playerPos, const GameTimer& gameTimer)
{
    const float dt = GetFrameTime();
    float elapsed = gameTimer.getElapsedTime(); 

    float newCooldown = std::max(0.025f, 1.25f - (elapsed / 250.0f) * 1.25f);
    enemySpawnCooldown.updateCooldownDuration(newCooldown);

    if (enemies.size() < Balance::ENEMY_LIMIT && !enemySpawnCooldown.isOnCooldown()) {
        int spawns = 1 + GetRandomValue(0, 2);
        for (int i = 0; i < spawns; i++) {
            spawnEnemy(playerPos, elapsed);
        }
        enemySpawnCooldown.startCooldown();
    }

    std::vector<std::string> toRemove;
    for (auto& [id, enemy] : enemies) {
        float dist = Vector2Distance(enemy->getPosition(), playerPos);
        enemy->getPlayerPositionForEnemy(playerPos);
        
        enemy->update();
        enemy->advanceHitReaction(dt);
        if (dist > ENEMY_MAX_DISTANCE) {
            toRemove.push_back(id);
        }
    }

    for (const auto& id : toRemove) {
        removeEnemy(id);
    }
    separateEnemies(dt);
}

void EnemyManager::separateEnemies(float dt)
{
    if (dt <= 0.0f || !std::isfinite(dt)) return;
    crowdGrid.clear();
    crowdEnemies.clear();
    crowdGrid.reserve(enemies.size());
    for (const auto& [id, enemy] : enemies) {
        // Flying enemies overlap freely and do not participate as obstacles.
        if (enemy->getEnemyType() != LOW_LEVEL_ENEMY || enemy->isDead()) continue;
        crowdEnemies.push_back(enemy.get());
        crowdGrid.add(enemy->getPosition(), enemy->getHitbox().width * Balance::CROWD_RADIUS_SCALE);
    }
    crowdGrid.build();
    const float step = std::min(dt, Balance::CROWD_MAX_STEP_TIME);
    const float response = 1.0f - std::exp(-Balance::CROWD_RESPONSE * step);
    const float maxPush = Balance::CROWD_MAX_PUSH_SPEED * step;
    for (std::size_t index = 0; index < crowdEnemies.size(); ++index) {
        Vector2 correction = Vector2Scale(crowdGrid.separation(index, Balance::CROWD_SLIDE), response);
        const float length = Vector2Length(correction);
        if (length > maxPush) correction = Vector2Scale(correction, maxPush / length);
        crowdEnemies[index]->applySeparation(correction);
    }
}


void EnemyManager::draw()
{
    for (auto& [id, enemy] : enemies) {
        enemy->draw(); 
    }
}


void EnemyManager::spawnEnemy(Vector2 playerPos, float elapsed)
{
    if (enemies.size() >= Balance::ENEMY_LIMIT) return;
    Vector2 offset = {Balance::ENEMY_SPAWN_RADIUS, 0.0f};
    float angle = DEG2RAD * (float)GetRandomValue(0, 359);
    offset = Vector2Rotate(offset, angle);
    Vector2 spawnPos = Vector2Add(playerPos, offset);

    std::string enemyID = "enemy_" + std::to_string(enemyCounter++);

    // Mid-level spawn chance: Only after 5 minutes, then scales up
    // Time	       Approx. midChance
    // 0-300s (0-5min)    0%
    // 360s        (6min)	11.8%
    // 420s        (7min)	20.3%
    // 480s        (8min)	26.3%
    // 540s        (9min)	29.6%
    // 600s        (10min)	31.5%
    // 900s        (15min)	38.7%
    // ∞	        40% (asymptotic)
    float midChance = 0.0f;
    if (elapsed >= MID_LEVEL_ENEMY_SPAWN_START_TIME) { //?  only spawn mid-level enemies after 5 minutes
        float adjustedTime = elapsed - MID_LEVEL_ENEMY_SPAWN_START_TIME; //? start scaling from 0 after 5 minutes
        midChance = 40.0f * (1.0f - expf(-adjustedTime / 180.0f));
    }
    float randomValue = (float)GetRandomValue(0, 9999) / 100.0f;
    bool isMidLevel = randomValue < midChance;

    std::unique_ptr<Enemy> enemy;
    if (isMidLevel) {
        enemy = std::make_unique<MidLevelEnemy>(enemyID, MID_LEVEL_ENEMY, spawnPos, playerPos);
    } else {
        enemy = std::make_unique<LowLevelEnemy>(enemyID, LOW_LEVEL_ENEMY, spawnPos, playerPos);
    }

    enemies[enemyID] = std::move(enemy);

    // std::cout << "Elapsed: " << elapsed << "s, midChance: " << midChance << "%, randomValue: " << randomValue << ", isMidLevel: " << (isMidLevel ? "true" : "false") << std::endl;

    // ! Don't work anymore, as enemy class don't have this implementations
    // std::cout << enemyID << std::endl;
    
    // ShootingEnemy enemy = ShootingEnemy(spawnPos);
    // enemy.getPlayerPosition(playerPos);
  
    // enemy.setSpeed(GetRandomValue(25, 50)); 
    // enemy.setTurnSpeed(1.5f + GetRandomValue(0, 1000) / 1000.0f); 
    // enemy.getCooldown().updateCooldownDuration(0.5f + GetRandomValue(0, 750) / 1000.0f); 
    // // enemy.getCooldown().updateCooldownDuration(0.01f);
    // enemy.setBulletSpeed(GetRandomValue(150, 200)); 
    // enemies.push_back(enemy);
}


void EnemyManager::removeEnemy(const std::string& id)
{
    // Animator::GetInstance().Stop(enemies[index]->getEnemyID());
    enemies[id]->destruct(); 
    enemies.erase(id);
}

void EnemyManager::reset()
{
    crowdGrid.clear();
    crowdEnemies.clear();
    enemies.clear();
    enemyCounter = 0;
}

std::vector<std::string> EnemyManager::spawnBarricade(Vector2 center)
{
    if (enemies.size() + Balance::BARRICADE_SEGMENTS > Balance::ENEMY_LIMIT) return {};
    std::vector<std::string> ids;
    ids.reserve(Balance::BARRICADE_SEGMENTS);
    for (int index = 0; index < Balance::BARRICADE_SEGMENTS; ++index) {
        const std::string id = "enemy_" + std::to_string(enemyCounter++);
        const float angle = 2.0f * PI * static_cast<float>(index) / Balance::BARRICADE_SEGMENTS;
        enemies.emplace(id, std::make_unique<BarricadeEnemy>(id, center, angle));
        ids.push_back(id);
    }
    return ids;
}

#ifdef GAME_DEBUG
int EnemyManager::spawnLowEnemies(Vector2 playerPos, int quantity)
{
    const int available = std::max(0, Balance::ENEMY_LIMIT - static_cast<int>(enemies.size()));
    const int count = std::clamp(quantity, 0, available);
    if (count == 0) return 0;
    enemies.reserve(enemies.size() + static_cast<std::size_t>(count));
    for (int index = 0; index < count; ++index) {
        const float angle = 2.0f * PI * static_cast<float>(index) / static_cast<float>(count);
        const Vector2 position = Vector2Add(playerPos, Vector2Rotate({Balance::ENEMY_SPAWN_RADIUS, 0.0f}, angle));
        const std::string id = "enemy_" + std::to_string(enemyCounter++);
        enemies.emplace(id, std::make_unique<LowLevelEnemy>(id, LOW_LEVEL_ENEMY, position, playerPos));
    }
    return count;
}
#endif
