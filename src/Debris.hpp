#pragma once
#include <string>
#include "Entity.hpp"
#include "DebrisKind.hpp"
class Debris : public Entity {
public:
    explicit Debris(Vector2 playerPos);
    Debris(Vector2 playerPos, DebrisKind kind);
    void update() override;
    void draw() override;
    const std::string& getDebrisID() const { return debrisID; }
    float getDebrisSize() const;
    DebrisKind getKind() const { return kind; }
    const char* getTextureKey() const { return DEBRIS_INFO[kind].texture; }
    const char* getDisplayName() const { return DEBRIS_INFO[kind].name; }
    void destruct(bool harvestable = false);
private:
    friend class DebrisManager;
    DebrisKind kind;
    float rotationSpeed = 0.0f;
    std::string debrisID;
    static unsigned long long debrisCounter;
};
