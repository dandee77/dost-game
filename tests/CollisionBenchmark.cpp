#include "TestAccess.hpp"
#include "raymath.h"

namespace {
using Clock = std::chrono::steady_clock;
constexpr int WARMUP_FRAMES = 120;
constexpr int SAMPLE_FRAMES = 600;
constexpr float CENTER = 250.0f;

double milliseconds(Clock::time_point start, Clock::time_point end)
{
    return std::chrono::duration<double, std::milli>(end - start).count();
}

double percentile(std::vector<double> values, double fraction)
{
    std::sort(values.begin(), values.end());
    return values[static_cast<std::size_t>((values.size() - 1) * fraction)];
}

// Real Game update/draw inside the unmodified Application render pipeline.
class BenchmarkScene final : public Scene
{
public:
    BenchmarkScene(int count, int shots, const std::string& layout, const std::string& output, int samples, Texture2D target)
        : count(count), bulletCount(shots), layout(layout), output(output), sampleFrames(samples), target(target)
    {
        game.onSwitch();
        SetRandomSeed(20261014);
        std::mt19937 random(20261014);
        std::uniform_real_distribution<float> x(-78.0f, 78.0f), y(-25.0f, 32.0f);
        auto& enemies = EnemyManager::GetInstance().getEnemies();
        for (int i = 0; i < count; ++i) {
            Vector2 point = {CENTER + x(random), CENTER + y(random)};
            if (Vector2Distance(point, {CENTER, CENTER}) < 18.0f) point.x += 36.0f;
            if (layout == "cluster") point = {CENTER + 40.0f, CENTER};
            const auto id = "benchmark_enemy_" + std::to_string(i);
            // Mixed real enemy types, including the existing shooter update path.
            std::unique_ptr<Enemy> enemy;
            if (i % 4 == 0) enemy = std::make_unique<MidLevelEnemy>(id, MID_LEVEL_ENEMY, point, Vector2{CENTER, CENTER});
            else enemy = std::make_unique<LowLevelEnemy>(id, LOW_LEVEL_ENEMY, point, Vector2{CENTER, CENTER});
            positions.push_back(point);
            observers.push_back(enemy.get());
            enemies[id] = std::move(enemy);
        }
        for (int i = 0; i < bulletCount; ++i) {
            // Visible miss-heavy scatter lane exercises the original worst scan.
            Vector2 point = {CENTER - 78.0f + static_cast<float>(i % 157), CENTER - 43.0f};
            if (layout == "cluster") point = {CENTER + 48.0f, CENTER};
            if (layout == "combat" && i < 8 && !positions.empty()) point = positions[i % positions.size()];
            if (layout == "burst" && i < 80 && !positions.empty()) point = positions[i % positions.size()];
            bullets.emplace_back(point, Vector2{0.0f, 0.0f}, i % 5 == 0, 1000000);
        }
    }

    std::string update() override
    {
        const auto now = Clock::now();
        if (frame > WARMUP_FRAMES) frameTimes.push_back(milliseconds(frameStart, now));
        if (frame >= WARMUP_FRAMES + sampleFrames) {
            double sum = 0.0;
            for (double value : frameTimes) sum += value;
            const double mean = sum / frameTimes.size();
            std::ofstream file(output);
            file << "layout,enemies,bullets,total_entities,frames,mean_ms,p95_ms,p99_ms,max_ms,mean_fps,update_p95_ms,min_live_bullets,max_live_bullets\n";
            file << layout << ',' << count << ',' << bulletCount << ',' << count + bulletCount + 1 << ','
                 << frameTimes.size() << ',' << mean << ',' << percentile(frameTimes, 0.95) << ','
                 << percentile(frameTimes, 0.99) << ',' << percentile(frameTimes, 1.0) << ',' << 1000.0 / mean
                 << ',' << percentile(updateTimes, 0.95) << ',' << minBullets << ',' << maxBullets << '\n';
            file.close();
            std::ofstream samples(output + ".frames.csv");
            samples << "frame,frame_ms,update_ms\n";
            for (std::size_t i = 0; i < frameTimes.size(); ++i) samples << i << ',' << frameTimes[i] << ',' << updateTimes[i] << '\n';
            samples.close();
            std::printf("RESULT %s enemies=%d bullets=%d mean=%.3f p99=%.3f FPS=%.1f update_p95=%.3f\n",
                layout.c_str(), count, bulletCount, mean, percentile(frameTimes, 0.99), 1000.0 / mean, percentile(updateTimes, 0.95));
            std::exit(0);
        }
        // Fixture maintenance is outside measured work. Keep real entities on
        // screen and avoid benchmarking the progressively emptied/dead scene.
        game.gameState = GAME_RUNNING;
        game.gameTimer.reset();
        game.gameTimer.start();
        game.playerEntity.position = {CENTER, CENTER};
        game.playerEntity.velocity = {0.0f, 0.0f};
        game.playerEntity.playerState = PLAYER_DEFAULT;
        game.playerEntity.health = 100;
        game.playerEntity.autoShoot = false;
        EnemyManager::GetInstance().enemySpawnCooldown.startCooldown();
        testDebrisManager().debrisSpawnCooldown.startCooldown();
        for (std::size_t i = 0; i < observers.size(); ++i) {
            observers[i]->position = positions[i];
            observers[i]->health = 1000000;
        }
        BulletManager::GetInstance().getBullets() = bullets;
        utils::gameCamera.zoom = 20.0f;
        utils::gameCamera.target = {CENTER, CENTER};
        frameStart = Clock::now();
        game.update();
        const auto end = Clock::now();
        if (frame >= WARMUP_FRAMES) {
            updateTimes.push_back(milliseconds(frameStart, end));
            const auto liveBullets = bmCount();
            minBullets = std::min(minBullets, liveBullets);
            maxBullets = std::max(maxBullets, liveBullets);
        }
        ++frame;
        return "Benchmark";
    }
    void draw() override
    {
        game.draw();
        if (frame == WARMUP_FRAMES / 2) {
            Image screenshot = LoadImageFromTexture(target);
            ImageFlipVertical(&screenshot);
            ExportImage(screenshot, (output + ".png").c_str());
            UnloadImage(screenshot);
        }
    }
    void onSwitch() override {}
    void onExit() override {}

private:
    static std::size_t bmCount() { return BulletManager::GetInstance().getBullets().size(); }
    Game game;
    int count;
    int bulletCount;
    std::string layout;
    std::string output;
    int frame = 0;
    int sampleFrames = SAMPLE_FRAMES;
    Texture2D target;
    std::size_t minBullets = std::numeric_limits<std::size_t>::max();
    std::size_t maxBullets = 0;
    Clock::time_point frameStart;
    std::vector<Vector2> positions;
    std::vector<Enemy*> observers;
    std::vector<Bullet> bullets;
    std::vector<double> frameTimes;
    std::vector<double> updateTimes;
};
}

int main(int argc, char** argv)
{
    if (argc != 5 && argc != 6) {
        std::fprintf(stderr, "Usage: CollisionBenchmark enemies bullets spread|cluster|combat|burst output.csv [frames]\n");
        return 1;
    }
    SetTraceLogLevel(LOG_WARNING);
    Application app;
    SetMasterVolume(0.0f);
    ClearWindowState(FLAG_VSYNC_HINT);
    SetTargetFPS(0);
    auto& resources = ResourceManager::GetInstance();
    while (resources.GetTextureLoadingProgress() < 100) {
        resources.ProcessLoadedTextures();
        BeginDrawing(); EndDrawing();
    }
    app.m_sceneFactory["Benchmark"] = std::make_shared<BenchmarkScene>(std::stoi(argv[1]), std::stoi(argv[2]), argv[3], argv[4], argc == 6 ? std::max(1, std::stoi(argv[5])) : SAMPLE_FRAMES, app.m_target.texture);
    app.m_currentScene = "Benchmark";
    app.Run();
}
