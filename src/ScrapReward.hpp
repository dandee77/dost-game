#pragma once
#include <cstdint>

struct ScrapReward {
    std::int64_t trade = 0, salvage = 0;
    ScrapReward& operator+=(ScrapReward other)
    {
        trade += other.trade;
        salvage += other.salvage;
        return *this;
    }
};
