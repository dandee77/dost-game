#pragma once
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <limits>
#include "Balance.hpp"

namespace ProgressionMath {
    inline std::int64_t xpRequired(std::int64_t level)
    {
        const auto extra = std::clamp<std::int64_t>(level - 1, 0,
            (Balance::FIELD_XP_MAX - Balance::FIELD_XP_START) / Balance::FIELD_XP_STEP);
        return Balance::FIELD_XP_START + Balance::FIELD_XP_STEP * extra;
    }

    inline double batteryShield(double current, double capacity, int size)
    {
        if (!std::isfinite(current) || !std::isfinite(capacity) || capacity <= 0 ||
            size < 0 || size >= static_cast<int>(Balance::BATTERY_FRACTIONS.size())) return current;
        return std::clamp(current, 0.0, capacity) + Balance::BATTERY_FRACTIONS[size] * capacity;
    }

    inline std::int64_t batteryPrice(double capacity, double startingCapacity, int size)
    {
        if (!std::isfinite(capacity) || !std::isfinite(startingCapacity) || capacity <= 0 ||
            startingCapacity <= 0 || size < 0 || size >= static_cast<int>(Balance::BATTERY_PRICES.size())) return 0;
        const double price = std::ceil(Balance::BATTERY_PRICES[size] * capacity / startingCapacity);
        if (!std::isfinite(price) || price >= static_cast<double>(std::numeric_limits<std::int64_t>::max())) return 0;
        return static_cast<std::int64_t>(price);
    }

    struct RepairQuote { std::int64_t cost = 0; double healing = 0; };
    inline RepairQuote repair(double missingHp, std::int64_t wallet)
    {
        if (!std::isfinite(missingHp) || missingHp <= 0 || wallet <= 0) return {};
        const double fullCost = std::ceil(missingHp * Balance::REPAIR_SCRAP_PER_HP);
        if (!std::isfinite(fullCost) || fullCost >= static_cast<double>(std::numeric_limits<std::int64_t>::max())) return {};
        const auto paid = std::min(wallet, static_cast<std::int64_t>(fullCost));
        return {paid, missingHp * (static_cast<double>(paid) / fullCost)};
    }
}

// Game owns this value. Collection, spending and queued choices have independent accounting.
struct RunProgress {
    std::int64_t wallet = 0, totalCollected = 0, level = 1, xp = 0, queuedChoices = 0;
    int energy = 0;

    void reset() { *this = {}; }
    bool collect(std::int64_t trade, std::int64_t salvage)
    {
        constexpr auto maximum = std::numeric_limits<std::int64_t>::max();
        if (trade < 0 || salvage < 0 || trade > maximum - totalCollected ||
            trade > maximum - wallet || salvage > maximum - xp) return false;
        wallet += trade;
        totalCollected += trade;
        energy += static_cast<int>(std::min<std::int64_t>(salvage, Balance::RETURN_CAPACITY - energy));
        xp += salvage;
        while (xp >= ProgressionMath::xpRequired(level)) {
            const auto required = ProgressionMath::xpRequired(level);
            const auto levels = required == Balance::FIELD_XP_MAX ? xp / required : 1;
            xp -= required * levels;
            level += levels;
            queuedChoices += levels;
        }
        return true;
    }
    bool spend(std::int64_t cost)
    {
        if (cost <= 0 || cost > wallet) return false;
        wallet -= cost;
        return true;
    }
    bool canReturn(bool onlineShield) const { return onlineShield && energy >= Balance::RETURN_REQUIRED; }
    bool consumeReturn(bool onlineShield)
    {
        if (!canReturn(onlineShield)) return false;
        energy = 0;
        return true;
    }
};
