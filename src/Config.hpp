#pragma once
#include <cstddef>

namespace Config {
    inline constexpr std::size_t DEBUG_INPUT_LIMIT = 80;
    inline constexpr std::size_t DEBUG_HISTORY_LIMIT = 32;
    inline constexpr std::size_t DEBUG_OUTPUT_LINES = 6;
    // World units. Broad-phase tuning only; hitbox radii are unchanged.
    inline constexpr float COLLISION_CELL_SIZE = 16.0f;
    inline constexpr std::size_t COLLISION_LINEAR_THRESHOLD = 32;
    inline constexpr std::size_t COLLISION_BUCKETS_PER_TARGET = 2;
}
