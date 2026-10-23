#pragma once
#include <algorithm>
#include <cmath>
#include "Balance.hpp"

// Pure calculations shared by runtime spawning and deterministic balance checks.
namespace CombatMath {
    inline int enemyHealth(int base, double elapsed)
    {
        if (!std::isfinite(elapsed)) elapsed = 0;
        const double multiplier = std::clamp(1.0 +
            (elapsed - Balance::ENEMY_HP_GRACE_SECONDS) * Balance::ENEMY_HP_GROWTH_PER_SECOND,
            1.0, Balance::ENEMY_HP_MAX_MULTIPLIER);
        return static_cast<int>(std::floor(std::max(1, base) * multiplier + 0.5));
    }
    inline double spawnBudget(double from, double to)
    {
        if (!std::isfinite(from) || !std::isfinite(to) || to <= from) return 0;
        from = std::max(0.0, from);
        double total = 0;
        const auto& curve = Balance::ENEMY_SPAWN_CURVE;
        for (std::size_t i = 1; i < curve.size(); ++i) {
            const auto& a = curve[i - 1];
            const auto& b = curve[i];
            const double start = std::max(from, a.seconds), end = std::min(to, b.seconds);
            if (end <= start) continue;
            const double slope = (b.perSecond - a.perSecond) / (b.seconds - a.seconds);
            total += (end - start) * (a.perSecond + slope * ((start + end) / 2 - a.seconds));
        }
        total += std::max(0.0, to - std::max(from, curve.back().seconds)) * curve.back().perSecond;
        return total;
    }
    inline double rangedChance(double elapsed)
    {
        if (!std::isfinite(elapsed)) return 0;
        return Balance::ENEMY_RANGED_MAX_CHANCE * std::clamp(
            (elapsed - Balance::ENEMY_RANGED_START_SECONDS) /
            (Balance::ENEMY_RANGED_FULL_SECONDS - Balance::ENEMY_RANGED_START_SECONDS), 0.0, 1.0);
    }
    inline int populationLimit(double elapsed)
    {
        const auto& curve = Balance::ENEMY_SPAWN_CURVE;
        if (!std::isfinite(elapsed) || elapsed <= 0) return curve.front().population;
        for (std::size_t i = 1; i < curve.size(); ++i) {
            if (elapsed >= curve[i].seconds) continue;
            const auto& a = curve[i - 1];
            const auto& b = curve[i];
            return a.population + static_cast<int>((b.population - a.population) *
                (elapsed - a.seconds) / (b.seconds - a.seconds));
        }
        return curve.back().population;
    }
}
