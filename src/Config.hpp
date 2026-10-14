#pragma once
#include <cstddef>

namespace Config {
    inline constexpr float TIMER_EPSILON = 0.00001f;
    inline constexpr std::size_t DEBUG_INPUT_LIMIT = 80;
    inline constexpr std::size_t DEBUG_HISTORY_LIMIT = 32;
    inline constexpr std::size_t DEBUG_OUTPUT_LINES = 6;
    // World units. Broad-phase tuning only; hitbox radii are unchanged.
    inline constexpr float COLLISION_CELL_SIZE = 16.0f;
    inline constexpr std::size_t COLLISION_LINEAR_THRESHOLD = 32;
    inline constexpr std::size_t COLLISION_BUCKETS_PER_TARGET = 2;
    // Hard bound per queried hash cell, including hash collisions.
    inline constexpr std::size_t CROWD_CANDIDATES_PER_CELL = 24;
    inline constexpr float CROWD_DIRECTION_EPSILON = 0.0001f;
    inline constexpr double CROWD_MAX_QUERY_CELLS = 16.0;
}
