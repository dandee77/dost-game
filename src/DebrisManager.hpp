#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "Debris.hpp"
#include "GameTimer.hpp"
#include "Timer.hpp"
class DebrisManager {
public:
    static DebrisManager& GetInstance() { static DebrisManager instance; return instance; }
    void update(Vector2 playerPos, const GameTimer& gameTimer);
    void draw();
    void reset();
    bool removeDebris(const std::string& id, bool harvestable = false);
    std::unordered_map<std::string, std::unique_ptr<Debris>>& getDebris() { return debris; }
#ifdef GAME_DEBUG
    void spawnGallery(Vector2 playerPos);
#endif
private:
    DebrisManager();
    void spawnDebris(Vector2 playerPos);
    std::unordered_map<std::string, std::unique_ptr<Debris>> debris;
    Cooldown debrisSpawnCooldown;
};
