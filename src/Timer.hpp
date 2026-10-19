#pragma once

#include <string>

class Cooldown 
{
private:
    float cooldownDuration;
    float elapsed = 0.0f;
    bool active = false;

public:
    bool isPaused;

    Cooldown();
    Cooldown(float cooldown);

    bool isOnCooldown() const;
    void startCooldown();
    void update(float dt);
    float remainingCooldown() const;
    float getCooldownDuration() const { return cooldownDuration; }
    std::string remainingCooldownString() const;
    void updateCooldownDuration(float newCooldownDuration);
    void pause();
    void unpause();
};
