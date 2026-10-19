#include "Timer.hpp"
#include <algorithm>
#include <cmath>
#include <string>

Cooldown::Cooldown() 
    : cooldownDuration(0.0f), isPaused(false) {}

Cooldown::Cooldown(float cooldown) 
    : cooldownDuration(std::max(0.0f, cooldown)), isPaused(false) {}

bool Cooldown::isOnCooldown() const 
{
    return active && elapsed < cooldownDuration;
}

void Cooldown::startCooldown() 
{
    elapsed = 0.0f;
    active = true;
}

void Cooldown::update(float dt)
{
    if (!isPaused && active && dt > 0.0f && std::isfinite(dt)) elapsed += dt;
}

float Cooldown::remainingCooldown() const 
{
    return active ? std::max(0.0f, cooldownDuration - elapsed) : 0.0f;
}

std::string Cooldown::remainingCooldownString() const 
{
    int remainingSeconds = static_cast<int>(remainingCooldown());
    int minutes = remainingSeconds / 60;
    int seconds = remainingSeconds % 60;
    return std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
}

void Cooldown::updateCooldownDuration(float newCooldownDuration) 
{
    cooldownDuration = std::max(0.0f, newCooldownDuration);
}

void Cooldown::pause() 
{
    isPaused = true;
}

void Cooldown::unpause() 
{
    isPaused = false;
}
