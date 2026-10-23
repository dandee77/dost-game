#pragma once
#include "Entity.hpp"
#include "ScrapReward.hpp"

// A glowing orb born at a saved destruction-frame particle position.
class ScrapPickup : public Entity {
public:
    ScrapPickup(Vector2 spawnPosition, int value, float drawSize);
    ScrapPickup(Vector2 spawnPosition, ScrapReward reward, float drawSize, bool persistent);
    void update() override;
    void draw() override;
    void advance(float dt, Vector2 target);
    void setAttractTarget(Vector2 target) { attractTarget = target; }
    bool isCollected() const { return collected; }
    bool isExpired() const;
    std::int64_t getValue() const { return reward.trade; }
    ScrapReward getReward() const { return reward; }
    void addValue(int amount) { reward += {amount, amount}; }
    void addReward(ScrapReward amount) { reward += amount; persistent = true; }
    float getElapsed() const { return elapsed; }
private:
    Vector2 attractTarget = {};
    float elapsed = 0.0f;
    ScrapReward reward;
    bool persistent = false;
    bool collected = false;
};
