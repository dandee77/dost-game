#include "CombatMath.hpp"
#include <cmath>
#include <cstdio>
#include <limits>

int main()
{
    int failures = 0;
    const auto check = [&](bool pass, const char* message) {
        if (!pass) { std::fprintf(stderr, "FAIL: %s\n", message); ++failures; }
    };
    check(CombatMath::enemyHealth(30, 0) == 30 && CombatMath::enemyHealth(30, 300) == 30,
        "Opening enemies retain base health for five combat minutes");
    check(CombatMath::enemyHealth(30, 1500) == 45 && CombatMath::enemyHealth(50, 1500) == 75,
        "Twenty-five minute enemies remain killable at only 1.5 times base health");
    check(CombatMath::enemyHealth(30, 1e9) == 60 && CombatMath::enemyHealth(50, 1e9) == 100,
        "Endless health growth cannot escape its two-times bound");
    check(CombatMath::enemyHealth(30, -1) == 30 &&
        CombatMath::enemyHealth(30, std::numeric_limits<double>::quiet_NaN()) == 30,
        "Invalid elapsed time cannot corrupt spawn health");
    check(std::abs(CombatMath::spawnBudget(0, 300) - 330.0) < 0.001,
        "First five minutes contain 330 potential spawns, not the old four-minute flood");
    check(std::abs(CombatMath::spawnBudget(1200, 1500) - 4200.0) < 0.001,
        "Late-game pressure comes from sustained population flow");
    for (int fps : {30, 60, 144}) {
        double budget = 0;
        for (int frame = 0; frame < fps * 1800; ++frame)
            budget += CombatMath::spawnBudget(static_cast<double>(frame) / fps,
                static_cast<double>(frame + 1) / fps);
        check(std::abs(budget - CombatMath::spawnBudget(0, 1800)) < 0.001,
            "Spawn budget is conserved across frame rates and interval boundaries");
    }
    check(CombatMath::spawnBudget(10, 10) == 0 && CombatMath::spawnBudget(10, 9) == 0,
        "Paused or reversed simulation cannot accrue spawns");
    check(CombatMath::rangedChance(0) == 0 && CombatMath::rangedChance(180) == 0 &&
        CombatMath::rangedChance(1e9) <= 0.15,
        "Ranged pressure is delayed and capped independently of health");
    if (failures == 0) std::puts("PASS: bounded enemy growth and frame-independent population pacing");
    return failures == 0 ? 0 : 1;
}
