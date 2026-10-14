#pragma once
#include "raylib.h"
#include <cstddef>
#include <limits>
#include <vector>
#include "Config.hpp"

// Frame index. Insertion order preserves the managers' first-hit priority.
class SpatialGrid
{
public:
    static constexpr std::size_t NO_HIT = std::numeric_limits<std::size_t>::max();
    void clear();
    void reserve(std::size_t count);
    void add(Vector2 position, float radius);
    void build();
    void deactivate(std::size_t index);
    bool isActive(std::size_t index) const;
    std::size_t firstHit(Vector2 point) const;
    std::size_t firstWithin(Vector2 point, float radius, std::size_t exclude = NO_HIT) const;
    // Soft overlap correction, with bounded work even for coincident crowds.
    Vector2 separation(std::size_t index, float slide = 0.0f) const;

private:
    struct Entry {
        Vector2 position;
        float radius;
        int cellX = 0;
        int cellY = 0;
        std::size_t next = NO_HIT;
        bool active = true;
    };
    struct Bucket {
        std::size_t head = NO_HIT;
        Vector2 minimum = {0.0f, 0.0f};
        Vector2 maximum = {0.0f, 0.0f};
        float maxRadius = 0.0f;
    };
    std::size_t bucket(int x, int y) const;
    std::size_t find(Vector2 point, float radius, bool targetRadius, std::size_t exclude) const;
    std::vector<Entry> entries;
    std::vector<Bucket> buckets;
    float maxRadius = 0.0f;
    bool linear = true;
};
