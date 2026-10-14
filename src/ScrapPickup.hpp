#pragma once
#include "Entity.hpp"

// A glowing orb born at a saved destruction-frame particle position.
class ScrapPickup : public Entity {
public:
    ScrapPickup(Vector2 spawnPosition, int value, float drawSize);
    void update() override;
    void draw() override;
    void advance(float dt, Vector2 target);
    void setAttractTarget(Vector2 target) { attractTarget = target; }
    bool isCollected() const { return collected; }
    bool isExpired() const;
    int getValue() const { return value; }
    void addValue(int amount) { value += amount; }
    float getElapsed() const { return elapsed; }
private:
    Vector2 attractTarget = {};
    float elapsed = 0.0f;
    int value = 0;
    bool collected = false;
};
