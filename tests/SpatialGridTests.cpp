#include "SpatialGrid.hpp"
#include "raymath.h"
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <random>

struct Target { Vector2 position; float radius; bool active = true; };

int main()
{
    std::mt19937 random(20261014);
    std::uniform_real_distribution<float> coordinate(-1000.0f, 1000.0f);
    std::uniform_real_distribution<float> radius(0.0f, 80.0f);
    SpatialGrid grid;
    std::size_t checks = 0;
    for (int scene = 0; scene < 300; ++scene) {
        grid.clear();
        std::vector<Target> targets;
        const int count = scene % 3 == 0 ? scene % 34 : 100 + scene * 3;
        for (int i = 0; i < count; ++i) {
            Vector2 point = {coordinate(random), coordinate(random)};
            if (scene % 7 == 0) point = {16.0f, -16.0f};
            if (scene == 298 && i == 0) point.x = std::numeric_limits<float>::max();
            if (scene == 299 && i == 0) point.x = std::numeric_limits<float>::quiet_NaN();
            const float r = scene % 11 == 0 ? 0.0f : radius(random);
            targets.push_back({point, r});
            grid.add(point, r);
        }
        grid.build();
        for (int query = 0; query < 1000; ++query) {
            Vector2 point = {coordinate(random), coordinate(random)};
            if (!targets.empty() && query % 3 == 0) {
                const auto& target = targets[query % targets.size()];
                point = {target.position.x + target.radius, target.position.y};
                if (query % 2 == 0) point.x = std::nextafter(point.x, target.position.x);
            }
            if (query == 998) point.x = std::numeric_limits<float>::max();
            const float r = query == 999 ? std::numeric_limits<float>::infinity() :
                (query % 13 == 0 ? 10000.0f : radius(random));
            const auto exclude = targets.empty() ? SpatialGrid::NO_HIT : query % targets.size();
            auto hit = SpatialGrid::NO_HIT;
            auto within = SpatialGrid::NO_HIT;
            for (std::size_t i = 0; i < targets.size(); ++i) {
                const auto& target = targets[i];
                if (!target.active) continue;
                const float distance = Vector2Distance(point, target.position);
                if (hit == SpatialGrid::NO_HIT && distance <= target.radius) hit = i;
                if (within == SpatialGrid::NO_HIT && i != exclude && distance <= r) within = i;
            }
            if (grid.firstHit(point) != hit || grid.firstWithin(point, r, exclude) != within) {
                std::fprintf(stderr, "Mismatch scene=%d query=%d\n", scene, query);
                return 1;
            }
            checks += 2;
            if (!targets.empty() && query % 5 == 0) {
                targets[exclude].active = false;
                grid.deactivate(exclude);
            }
        }
    }
    std::printf("PASS: %zu ordered queries match brute force, including resets/removals/boundaries/clusters/large radii.\n", checks);
}
