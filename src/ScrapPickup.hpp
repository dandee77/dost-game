#pragma once
#include "Entity.hpp"
#include "DebrisKind.hpp"

// One fragment remains the same object from breakup through collection.
class ScrapPickup : public Entity {
public:
    ScrapPickup(Vector2 center, float angle, DebrisKind kind, float drawSize, int fragment, int value, bool harvestable);
    void update() override;
    void draw() override;
    void advance(float dt, Vector2 target);
    void setAttractTarget(Vector2 target) { attractTarget = target; }
    bool isCollected() const { return collected; }
    bool isExpired() const;
    bool canHarvest() const { return harvestable; }
    int getValue() const { return value; }
    void addValue(int amount) { value += amount; }
    float getElapsed() const { return elapsed; }
    Rectangle getSource() const { return source; }
private:
    DebrisKind kind;
    Rectangle source;
    Vector2 startPosition, scatterDirection, attractTarget = {};
    float initialRotation = 0.0f, elapsed = 0.0f;
    int value = 0;
    bool harvestable = false, collected = false;
};
