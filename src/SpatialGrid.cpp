#include "SpatialGrid.hpp"
#include "raymath.h"
#include <algorithm>
#include <cmath>
#include <cstdint>

void SpatialGrid::clear()
{
    entries.clear();
    maxRadius = 0.0f;
    linear = true;
}

void SpatialGrid::reserve(std::size_t count)
{
    if (count > entries.capacity()) entries.reserve(std::max(count, entries.capacity() * 2));
}

void SpatialGrid::add(Vector2 position, float radius)
{
    entries.push_back({position, radius});
    maxRadius = std::max(maxRadius, radius);
}

std::size_t SpatialGrid::bucket(int x, int y) const
{
    // Unsigned arithmetic gives well-defined hashing for negative cells too.
    const auto hash = static_cast<std::uint32_t>(x) * 0x8da6b343U
                    ^ static_cast<std::uint32_t>(y) * 0xd8163841U;
    return hash & (buckets.size() - 1);
}

void SpatialGrid::build()
{
    linear = entries.size() <= Config::COLLISION_LINEAR_THRESHOLD;
    if (linear) return;
    std::size_t count = 1;
    while (count < entries.size() * Config::COLLISION_BUCKETS_PER_TARGET) count *= 2;
    buckets.resize(count);
    std::fill(buckets.begin(), buckets.end(), Bucket{});
    // Reverse insertion makes each bucket walk in original target order.
    for (std::size_t i = entries.size(); i-- > 0;) {
        auto& entry = entries[i];
        const double x = std::floor(static_cast<double>(entry.position.x) / Config::COLLISION_CELL_SIZE);
        const double y = std::floor(static_cast<double>(entry.position.y) / Config::COLLISION_CELL_SIZE);
        if (!std::isfinite(x) || !std::isfinite(y) ||
            x <= std::numeric_limits<int>::min() || x >= std::numeric_limits<int>::max() ||
            y <= std::numeric_limits<int>::min() || y >= std::numeric_limits<int>::max()) {
            linear = true;
            return;
        }
        entry.cellX = static_cast<int>(x);
        entry.cellY = static_cast<int>(y);
        auto& slot = buckets[bucket(entry.cellX, entry.cellY)];
        if (slot.head == NO_HIT) {
            slot.minimum = entry.position;
            slot.maximum = entry.position;
        } else {
            slot.minimum.x = std::min(slot.minimum.x, entry.position.x);
            slot.minimum.y = std::min(slot.minimum.y, entry.position.y);
            slot.maximum.x = std::max(slot.maximum.x, entry.position.x);
            slot.maximum.y = std::max(slot.maximum.y, entry.position.y);
        }
        slot.maxRadius = std::max(slot.maxRadius, entry.radius);
        entry.next = slot.head;
        slot.head = i;
    }
}

void SpatialGrid::deactivate(std::size_t index)
{
    entries[index].active = false;
}

bool SpatialGrid::isActive(std::size_t index) const
{
    return entries[index].active;
}

std::size_t SpatialGrid::firstHit(Vector2 point) const
{
    return find(point, maxRadius, true, NO_HIT);
}

std::size_t SpatialGrid::firstWithin(Vector2 point, float radius, std::size_t exclude) const
{
    return find(point, radius, false, exclude);
}

std::size_t SpatialGrid::find(Vector2 point, float radius, bool targetRadius, std::size_t exclude) const
{
    // Retain sqrt and inclusive comparison for identical boundary rounding.
    const auto matches = [&](std::size_t i) {
        const auto& entry = entries[i];
        return i != exclude && entry.active &&
            Vector2Distance(point, entry.position) <= (targetRadius ? entry.radius : radius);
    };
    const auto scan = [&]() {
        for (std::size_t i = 0; i < entries.size(); ++i) {
            if (matches(i)) return i;
        }
        return NO_HIT;
    };
    if (linear) return scan();
    // Conservative padding includes floating-point boundary cases.
    const double left = std::floor((static_cast<double>(point.x) - radius) / Config::COLLISION_CELL_SIZE) - 1;
    const double right = std::floor((static_cast<double>(point.x) + radius) / Config::COLLISION_CELL_SIZE) + 1;
    const double top = std::floor((static_cast<double>(point.y) - radius) / Config::COLLISION_CELL_SIZE) - 1;
    const double bottom = std::floor((static_cast<double>(point.y) + radius) / Config::COLLISION_CELL_SIZE) + 1;
    if (!std::isfinite(left) || !std::isfinite(right) || !std::isfinite(top) || !std::isfinite(bottom) ||
        left <= std::numeric_limits<int>::min() || right >= std::numeric_limits<int>::max() ||
        top <= std::numeric_limits<int>::min() || bottom >= std::numeric_limits<int>::max()) return scan();
    const double cells = (right - left + 1) * (bottom - top + 1);
    // Large future hitboxes must not walk millions of empty cells.
    if (cells > static_cast<double>(entries.size())) {
        return scan();
    }
    const int minX = static_cast<int>(left), maxX = static_cast<int>(right);
    const int minY = static_cast<int>(top), maxY = static_cast<int>(bottom);
    std::size_t best = NO_HIT;
    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            const auto& slot = buckets[bucket(x, y)];
            if (slot.head == NO_HIT || slot.head >= best) continue;
            // Tight center bounds reject clustered misses without scanning the
            // entire crowd. Hash collisions only enlarge these bounds safely.
            const Vector2 nearest = {std::clamp(point.x, slot.minimum.x, slot.maximum.x),
                                     std::clamp(point.y, slot.minimum.y, slot.maximum.y)};
            if (Vector2Distance(point, nearest) > (targetRadius ? slot.maxRadius : radius)) continue;
            for (auto i = slot.head; i != NO_HIT && i < best; i = entries[i].next) {
                const auto& entry = entries[i];
                if (entry.cellX == x && entry.cellY == y && matches(i)) {
                    best = i;
                    break;
                }
            }
        }
    }
    return best;
}
