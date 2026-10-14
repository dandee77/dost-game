#include "TestAccess.hpp"

#ifdef _WIN32
extern "C" __declspec(dllimport) int __stdcall PostMessageA(void*, unsigned int, unsigned long long, long long);
#endif

int main(int argc, char** argv)
{
    if (argc != 2) return 1;
    SetTraceLogLevel(LOG_WARNING);
    SetConfigFlags(FLAG_WINDOW_HIDDEN);
    InitWindow(1280, 720, "Collision regression");
    InitAudioDevice();
    SetMasterVolume(0.0f);
    auto& resources = ResourceManager::GetInstance();
    resources.LoadFonts(); resources.LoadSounds(); resources.LoadMusics(); resources.LoadTextures();
    while (resources.GetTextureLoadingProgress() < 100) {
        resources.ProcessLoadedTextures();
        BeginDrawing(); EndDrawing();
    }
    Game game;
    game.onSwitch();
    auto& em = EnemyManager::GetInstance();
    auto& am = testAsteroidManager();
    auto& bm = BulletManager::GetInstance();
    std::ofstream output(argv[1]);
    std::mt19937 random(20261014);
    std::uniform_real_distribution<float> coordinate(-70.0f, 70.0f);

    // Each case uses actual Game::update and real damage/death/removal handlers.
    // Freeze motion so two independent executables have identical snapshots.
    for (int scenario = 0; scenario < 160; ++scenario) {
        em.reset(); am.reset(); bm.reset();
        DamageIndicatorManager::GetInstance().reset();
        game.killCounter.reset();
        game.gameState = GAME_RUNNING;
        game.playerEntity.position = {250.0f, 250.0f};
        game.playerEntity.velocity = {0.0f, 0.0f};
        game.playerEntity.playerState = scenario % 7 == 0 ? PLAYER_IFRAME : PLAYER_DEFAULT;
        game.playerEntity.timeStateEntered = static_cast<float>(GetTime());
        game.playerEntity.health = scenario % 5 == 0 ? 10 : 100;
        game.playerEntity.playerScore = 0;
        game.playerEntity.totalDamageDealt = 0;
        game.playerEntity.autoShoot = false;
        game.playerEntity.minDamage = 10;
        game.playerEntity.maxDamage = 10;
        game.gameTimer.reset(); game.gameTimer.start();
        em.enemySpawnCooldown.startCooldown();
        am.asteroidSpawnCooldown.startCooldown();
        SetRandomSeed(static_cast<unsigned>(scenario));
        std::vector<Vector2> positions;
        const int count = scenario < 10 ? scenario : 90;
        for (int i = 0; i < count; ++i) {
            Vector2 point = {250.0f + coordinate(random), 250.0f + coordinate(random)};
            if (scenario % 4 == 0) point = {280.0f, 250.0f};
            if (i == 0 && scenario % 3 == 0) point = {250.0f, 250.0f};
            const auto id = "regression_enemy_" + std::to_string(i);
            std::unique_ptr<Enemy> enemy;
            if (i % 2 == 0) {
                auto mid = std::make_unique<MidLevelEnemy>(id, MID_LEVEL_ENEMY, point, Vector2{250.0f, 250.0f});
                mid->fireCooldown.startCooldown();
                enemy = std::move(mid);
            } else enemy = std::make_unique<LowLevelEnemy>(id, LOW_LEVEL_ENEMY, point, Vector2{250.0f, 250.0f});
            enemy->speed = 0.0f;
            enemy->velocity = {0.0f, 0.0f};
            enemy->knockbackVelocity = {0.0f, 0.0f};
            enemy->health = i % 2 == 0 ? 10 : 30;
            positions.push_back(point);
            em.getEnemies()[id] = std::move(enemy);
        }
        for (int i = 0; i < count; ++i) {
            auto asteroid = std::make_unique<Asteroid>(Vector2{250.0f, 250.0f});
            asteroid->position = {250.0f + coordinate(random), 250.0f + coordinate(random)};
            if (scenario % 4 == 1) asteroid->position = {280.0f, 250.0f};
            if (i == 0 && scenario % 3 == 1) asteroid->position = {250.0f, 250.0f};
            asteroid->velocity = {0.0f, 0.0f};
            if (scenario % 9 == 0 && GetFrameTime() > 0.0f) {
                asteroid->velocity.x = 5.0f / GetFrameTime();
            }
            asteroid->size = i % 2 == 0 ? 1.5f : 3.0f;
            am.getAsteroids()[asteroid->getAsteroidID()] = std::move(asteroid);
        }
        for (int i = 0; i < count * 3 + 1; ++i) {
            Vector2 point = {250.0f + coordinate(random), 250.0f + coordinate(random)};
            if (!positions.empty() && i % 2 == 0) point = positions[i % positions.size()];
            if (i == 0 && scenario % 3 == 2) point = {250.0f, 250.0f};
            bm.addBullet(Bullet(point, Vector2{0.0f, 0.0f}, i % 3 == 0, 1 + i % 3));
        }
        // Three frames test persistent piercing and same-frame destruction.
        for (int frame = 0; frame < 3; ++frame) {
            em.enemySpawnCooldown.startCooldown(); am.asteroidSpawnCooldown.startCooldown();
            game.playerEntity.position = {250.0f, 250.0f};
            game.playerEntity.velocity = {0.0f, 0.0f};
            if (game.gameState == GAME_RUNNING) game.update();
            output << scenario << ':' << frame << ':' << game.playerEntity.getHealth() << ':'
                   << game.playerEntity.getScore() << ':' << game.playerEntity.getTotalDamageDealt() << ':'
                   << game.killCounter.getCount() << ':' << game.gameState << ':' << game.playerEntity.getPlayerState();
            if (game.gameState == GAME_OVER) output << ':' << game.deathInfo.killerType << ':' << game.deathInfo.killerID << ':' << game.deathInfo.killerName;
            std::map<std::string, int> health;
            for (const auto& [id, enemy] : em.getEnemies()) health[id] = enemy->getHealth();
            for (const auto& [id, hp] : health) output << '|' << id << '=' << hp;
            std::vector<std::string> asteroids;
            for (const auto& [id, asteroid] : am.getAsteroids()) asteroids.push_back(id);
            std::sort(asteroids.begin(), asteroids.end());
            for (const auto& id : asteroids) output << '|' << id;
            for (const auto& bullet : bm.getBullets()) output << "|b=" << bullet.getPosition().x << ',' << bullet.getPosition().y << ',' << bullet.isEnemyBullet() << ',' << bullet.getPiercePower();
            output << '\n';
        }
    }
    output.close();
#ifdef _WIN32
    // Exercise the actual Restart button instead of calling a private helper.
    game.gameState = GAME_OVER;
    SetMouseScale(3.0f, 3.0f);
    PostMessageA(GetWindowHandle(), 0x200, 0, (553LL << 16) | 640);
    PostMessageA(GetWindowHandle(), 0x201, 1, (553LL << 16) | 640);
    PollInputEvents();
    game.update();
    PostMessageA(GetWindowHandle(), 0x202, 0, (553LL << 16) | 640);
    PollInputEvents();
    if (!em.getEnemies().empty() || !am.getAsteroids().empty() || !bm.getBullets().empty() ||
        game.gameState != GAME_RUNNING || game.playerEntity.getHealth() != 100 ||
        !game.collisionEnemies.empty() || !game.collisionAsteroids.empty()) return 3;
    std::printf("PASS: actual Restart button cleared run and collision observers.\n");
#endif
    game.onExit();
    game.onSwitch();
    if (!em.getEnemies().empty() || !am.getAsteroids().empty() || !bm.getBullets().empty() ||
        game.gameState != GAME_RUNNING || game.playerEntity.getHealth() != 100) return 2;
    std::printf("PASS: 480 real collision frames recorded; new-run reset cleared all managers.\n");
}
