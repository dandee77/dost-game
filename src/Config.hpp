#pragma once
#include <cstddef>

namespace Config {
    // World units. Broad-phase tuning only; hitbox radii are unchanged.
    inline constexpr float COLLISION_CELL_SIZE = 16.0f;
    inline constexpr std::size_t COLLISION_LINEAR_THRESHOLD = 32;
    inline constexpr std::size_t COLLISION_BUCKETS_PER_TARGET = 2;
}
