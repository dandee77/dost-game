#pragma once
#include <memory>
#include <vector>
#include "ScrapPickup.hpp"
class ScrapManager {
public:
    static ScrapManager& GetInstance() { static ScrapManager instance; return instance; }
    void spawnDebris(Vector2 center, float angle, DebrisKind kind, float drawSize, bool harvestable);
    int update(float dt, Vector2 playerPosition);
    void draw();
    void reset() { pickups.clear(); }
    std::size_t count() const { return pickups.size(); }
    int pendingValue() const;
    const std::vector<std::unique_ptr<ScrapPickup>>& getPickups() const { return pickups; }
private:
    std::vector<std::unique_ptr<ScrapPickup>> pickups;
};
