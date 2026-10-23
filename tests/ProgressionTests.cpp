#include "RunProgress.hpp"
#include <cmath>
#include <cstdio>
#include <limits>

int main()
{
    int failures = 0;
    const auto check = [&](bool pass, const char* message) {
        if (!pass) { std::fprintf(stderr, "FAIL: %s\n", message); ++failures; }
    };
    RunProgress run;
    check(run.collect(7, 100) && run.wallet == 7 && run.level == 2 && run.queuedChoices == 1,
        "Random trade value is separate from fixed salvage XP");
    check(run.collect(20, 270) && run.level == 4 && run.xp == 10 && run.queuedChoices == 3,
        "Large pickups carry overflow and queue every earned level");
    check(run.spend(20) && run.wallet == 7 && run.xp == 10 && run.energy == 370,
        "Spending money cannot consume XP or return energy");
    check(!run.spend(8) && !run.spend(-1) && run.wallet == 7,
        "Insufficient or negative payments cannot mutate the wallet");
    check(!run.collect(-1, 20) && run.energy == 370,
        "Invalid pickups cannot partially credit another resource");
    run.collect(0, 2000);
    check(run.energy == 1000 && run.canReturn(true) && !run.canReturn(false),
        "Return charge caps and requires an online shield");
    check(run.consumeReturn(true) && run.energy == 0 && !run.consumeReturn(true),
        "Return spends energy exactly once");
    run.reset();
    check(run.level == 1 && run.wallet == 0 && run.xp == 0 && run.queuedChoices == 0,
        "Restart clears the entire economy and progression");
    run.collect(500, 500);
    check(run.canReturn(true) && run.level == 4 && run.xp == 140,
        "First return needs 500 salvage without a moving level-dependent target");
    check(ProgressionMath::batteryShield(80, 100, 0) == 100 &&
        ProgressionMath::batteryShield(80, 100, 4) == 280 &&
        ProgressionMath::batteryShield(280, 100, 0) == 120,
        "Batteries discard old excess, preserve damage, then add purchased charge");
    check(ProgressionMath::batteryPrice(75, 20, 1) == 938 &&
        ProgressionMath::batteryPrice(20, 20, 4) == 900,
        "Battery prices scale with normal capacity and round up once");
    const auto repair = ProgressionMath::repair(37, 185);
    check(repair.cost == 185 && std::abs(repair.healing - 18.5) < 1e-9,
        "Affordable repair restores the exact paid fraction");
    check(ProgressionMath::repair(0.15, 1).healing == 0.075 &&
        ProgressionMath::repair(10, 0).healing == 0,
        "Fractional repairs preserve value and zero payment cannot heal");
    if (failures == 0) std::puts("PASS: progression accounting, repair and replacement batteries");
    return failures == 0 ? 0 : 1;
}
