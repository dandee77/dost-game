#pragma once
#include "raylib.h"
#include <string>
#include <vector>

class Player;
enum BarricadePhase { BARRICADE_IDLE, BARRICADE_CONTAINING, BARRICADE_SCATTERING };

// Run-local coordinator; EnemyManager owns the actual damageable segments.
class BarricadeEvent
{
public:
    bool start(Vector2 playerPosition);
    void update(float dt, float runTime, Vector2 playerPosition);
    bool constrainPlayer(Player& player, Vector2 previousPosition) const;
    void finishIfEscaped(Vector2 playerPosition, const Camera2D& camera);
    void reset();
    void drawStatus() const;
    bool isActive() const { return phase != BARRICADE_IDLE; }
    bool isContaining() const { return phase == BARRICADE_CONTAINING; }
    BarricadePhase getPhase() const { return phase; }
    Vector2 getCenter() const { return center; }
    float getElapsed() const { return elapsed; }
    float getRadius() const;
    int getAliveSegments() const;
    bool hasTriggeredAutomatically() const { return automaticTriggered; }
private:
    void clearSegments();
    BarricadePhase phase = BARRICADE_IDLE;
    Vector2 center = {};
    float elapsed = 0.0f;
    bool automaticTriggered = false;
    std::vector<std::string> segmentIds;
};
