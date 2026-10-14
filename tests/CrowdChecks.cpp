#include "TestAccess.hpp"
#include "Balance.hpp"
#include "raymath.h"
#include <stdexcept>

int runCrowdChecks(const std::string& artifactDirectory)
{
    int checks = 0;
    const auto require = [&](bool condition, const char* message) {
        ++checks;
        if (!condition) throw std::runtime_error(message);
    };
    auto& manager = EnemyManager::GetInstance();
    auto& animator = Animator::GetInstance();
    const auto clear = [&]() {
        for (const auto& [id, enemy] : manager.getEnemies()) animator.Remove(id);
        manager.reset();
    };
    const auto low = [&](const std::string& id, Vector2 point) -> Enemy& {
        auto value = std::make_unique<LowLevelEnemy>(id, LOW_LEVEL_ENEMY, point, Vector2{0, -100});
        value->rotation = 0.0f;
        auto& result = *value;
        manager.getEnemies()[id] = std::move(value);
        return result;
    };
    clear();
    auto& a = low("crowd_a", {});
    auto& b = low("crowd_b", {});
    manager.separateEnemies(0.0f);
    require(Vector2Length(a.getPosition()) == 0.0f, "Paused separation does not move enemies");
    manager.separateEnemies(1.0f / 60.0f);
    require(Vector2Distance(a.getPosition(), b.getPosition()) > 0.1f, "Coincident enemies separate");
    require(Vector2Length(Vector2Add(a.getPosition(), b.getPosition())) < 0.001f, "Pair push preserves center of mass");
    require(Vector2Length(a.getPosition()) <= Balance::CROWD_MAX_PUSH_SPEED / 60.0f + 0.001f, "Crowd displacement is speed limited");
    require(a.getHitbox().x == a.getPosition().x, "Separation updates collision rectangle position");
    const auto start = a.getPosition();
    manager.separateEnemies(10.0f);
    require(Vector2Distance(a.getPosition(), start) <= Balance::CROWD_MAX_PUSH_SPEED * Balance::CROWD_MAX_STEP_TIME + 0.001f,
        "Long frames cannot launch enemies across the screen");

    std::vector<float> distances;
    for (int fps : {30, 60, 144}) {
        clear();
        auto& first = low("crowd_a", {-0.5f, 0});
        auto& second = low("crowd_b", {0.5f, 0});
        for (int frame = 0; frame < fps * 2; ++frame) manager.separateEnemies(1.0f / fps);
        distances.push_back(Vector2Distance(first.getPosition(), second.getPosition()));
    }
    require(std::abs(distances.front() - distances.back()) < 0.01f, "Crowd settling agrees at 30 and 144 FPS");
    require(distances.front() > 12.0f && distances.front() < 13.0f, "Soft bodies settle at their configured spacing");

    clear();
    auto& isolated = low("crowd_isolated", {10, 10});
    manager.getEnemies()["crowd_flyer"] = std::make_unique<MidLevelEnemy>("crowd_flyer", MID_LEVEL_ENEMY, Vector2{10, 10}, Vector2{});
    auto& flyer = *manager.getEnemies().at("crowd_flyer");
    flyer.rotation = 0.0f;
    flyer.velocity = {12, 8};
    const Vector2 flightDirection = flyer.viewDirection;
    manager.separateEnemies(1.0f / 60.0f);
    require(Vector2Distance(flyer.getPosition(), {10, 10}) == 0.0f && Vector2Distance(isolated.getPosition(), {10, 10}) == 0.0f,
        "Flying enemies can overlap low enemies without pushing either");
    require(Vector2Distance(flyer.getVelocity(), {12, 8}) == 0.0f && Vector2Distance(flyer.viewDirection, flightDirection) == 0.0f,
        "Crowd pass preserves flying velocity and steering");
    require(animator.animations.at("crowd_flyer").layer == ANIMATION_FLYING &&
        animator.animations.at("crowd_isolated").layer == ANIMATION_WORLD, "Mid enemy uses the top animation layer");
    animator.StopAll();
    animator.Play("crowd_isolated"); animator.Play("crowd_flyer");
    const auto layered = LoadRenderTexture(96, 96);
    Camera2D layerCamera = {{48, 48}, {10, 10}, 0, 5};
    BeginTextureMode(layered); ClearBackground(BLANK); BeginMode2D(layerCamera);
    manager.draw(); animator.Draw(); EndMode2D(); EndTextureMode();
    Image both = LoadImageFromTexture(layered.texture);
    animator.Stop("crowd_isolated");
    BeginTextureMode(layered); ClearBackground(BLANK); BeginMode2D(layerCamera);
    animator.Draw(); EndMode2D(); EndTextureMode();
    Image flyingOnly = LoadImageFromTexture(layered.texture);
    require(both.format == PIXELFORMAT_UNCOMPRESSED_R8G8B8A8 && flyingOnly.format == both.format, "Layer comparison uses RGBA pixels");
    const auto* bothPixels = static_cast<const Color*>(both.data);
    const auto* flyingPixels = static_cast<const Color*>(flyingOnly.data);
    int opaquePixels = 0, mismatches = 0;
    for (int pixel = 0; pixel < both.width * both.height; ++pixel) {
        if (flyingPixels[pixel].a != 255) continue;
        ++opaquePixels;
        if (bothPixels[pixel].r != flyingPixels[pixel].r || bothPixels[pixel].g != flyingPixels[pixel].g ||
            bothPixels[pixel].b != flyingPixels[pixel].b) ++mismatches;
    }
    require(opaquePixels > 0 && mismatches == 0, "Mid sprite stays visible above overlapping low sprite in native render");
    UnloadImage(both); UnloadImage(flyingOnly); UnloadRenderTexture(layered);
    flyer.destruct();
    require(animator.animations.at("crowd_flyer").layer == ANIMATION_FLYING, "Mid destruction retains top layer");
    clear();
    require(manager.crowdEnemies.empty(), "Reset drops crowd observers");
    manager.separateEnemies(1.0f / 60.0f);
    require(manager.crowdEnemies.empty(), "Empty crowd rebuild is safe");

    for (int index = 0; index < 80; ++index) low("crowd_line_" + std::to_string(index), {static_cast<float>(index), 0});
    for (int frame = 0; frame < 240; ++frame) {
        // Fixed-step chase fixture leaves real separation free to spread the queue.
        for (auto& [id, value] : manager.getEnemies())
            value->position = Vector2Add(value->position, Vector2Scale(Vector2Normalize(Vector2Subtract(Vector2{150, 0}, value->position)), 0.4f));
        manager.separateEnemies(1.0f / 60.0f);
    }
    float minY = 0.0f, maxY = 0.0f;
    for (const auto& [id, value] : manager.getEnemies()) {
        minY = std::min(minY, value->position.y); maxY = std::max(maxY, value->position.y);
    }
    require(maxY - minY > 25.0f, "Collinear chasing enemies spread sideways into a crowd");
    animator.StopAll();
    for (const auto& [id, value] : manager.getEnemies()) animator.Play(id);
    const auto target = LoadRenderTexture(1600, 900);
    BeginTextureMode(target); ClearBackground(Color{18, 22, 32, 255});
    Camera2D camera = {{250, 450}, {0, 0}, 0, 7};
    BeginMode2D(camera); manager.draw(); animator.Draw(); EndMode2D(); EndTextureMode();
    Image capture = LoadImageFromTexture(target.texture); ImageFlipVertical(&capture);
    require(ExportImage(capture, (artifactDirectory + "/crowd-chase.png").c_str()), "Export settled crowd preview");
    UnloadImage(capture); UnloadRenderTexture(target);
    clear();

    for (int index = 0; index < 500; ++index) low("crowd_pile_" + std::to_string(index), {});
    for (int frame = 0; frame < 180; ++frame) manager.separateEnemies(1.0f / 60.0f);
    float extent = 0.0f;
    for (const auto& [id, value] : manager.getEnemies()) {
        require(std::isfinite(value->position.x) && std::isfinite(value->position.y), "Dense crowd remains finite");
        extent = std::max(extent, Vector2Length(value->position));
    }
    require(extent > 25.0f, "Dense coincident pile expands");
    clear();

#ifndef GAME_DEBUG
    // Isolate real manager separation cost. Restore positions outside the timer.
    std::ofstream timings(artifactDirectory + "/crowd-solver.csv");
    timings << "layout,low_enemies,mean_ms,p95_ms\n";
    for (const bool pile : {false, true}) {
        for (int count : {1000, 2000, 5000, 10000}) {
            std::vector<Vector2> positions;
            std::vector<Enemy*> observers;
            for (int index = 0; index < count; ++index) {
                const Vector2 point = pile ? Vector2{} : Vector2{static_cast<float>(index % 100) * 5.0f, static_cast<float>(index / 100) * 5.0f};
                positions.push_back(point);
                observers.push_back(&low("crowd_perf_" + std::to_string(index), point));
            }
            std::vector<double> samples;
            for (int frame = 0; frame < 220; ++frame) {
                for (std::size_t index = 0; index < observers.size(); ++index) observers[index]->position = positions[index];
                const auto begin = std::chrono::steady_clock::now();
                manager.separateEnemies(1.0f / 60.0f);
                const auto end = std::chrono::steady_clock::now();
                if (frame >= 20) samples.push_back(std::chrono::duration<double, std::milli>(end - begin).count());
            }
            double sum = 0.0;
            for (double time : samples) sum += time;
            std::sort(samples.begin(), samples.end());
            timings << (pile ? "coincident" : "packed") << ',' << count << ',' << sum / samples.size() << ',' << samples[samples.size() * 95 / 100] << '\n';
            clear();
        }
    }
#endif
    return checks;
}
