#pragma once
#include <memory>
#include <vector>
#include "ScrapPickup.hpp"
#include "DebrisKind.hpp"
class ScrapManager {
public:
    static ScrapManager& GetInstance() { static ScrapManager instance; return instance; }
    void spawnDebris(Vector2 center, float angle, DebrisKind kind, float drawSize, bool harvestable);
    int update(float dt, Vector2 playerPosition);
    void draw();
    void reset() { pickups.clear(); destructions.clear(); }
    std::size_t count() const { return pickups.size(); }
    int pendingValue() const;
    const std::vector<std::unique_ptr<ScrapPickup>>& getPickups() const { return pickups; }
    std::size_t destructionCount() const { return destructions.size(); }
private:
    struct Destruction {
        Vector2 center;
        float angle, drawSize;
        int value;
        bool harvestable;
        DebrisKind kind;
        float elapsed = 0.0f;
        bool released = false;
    };
    int releasePickups(const Destruction& destruction, float remainingDt, Vector2 playerPosition);
    std::vector<Destruction> destructions;
    std::vector<std::unique_ptr<ScrapPickup>> pickups;
};
