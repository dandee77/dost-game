#include "TestAccess.hpp"
#include "EquipmentAccess.hpp"
#include <stdexcept>

#ifdef _WIN32
extern "C" __declspec(dllimport) int __stdcall PostMessageA(void*, unsigned int, unsigned long long, long long);
#endif

namespace {
    int checks = 0;
    void require(bool condition, const char* message)
    {
        ++checks;
        if (!condition) throw std::runtime_error(message);
    }
}

int runPauseChecks()
{
    checks = 0;
    // No simulation update: a query must not spend cooldown while a menu is open.
    Cooldown cooldown(0.02f);
    cooldown.startCooldown();
    const float before = cooldown.remainingCooldown();
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    require(cooldown.remainingCooldown() == before && cooldown.isOnCooldown(),
        "Cooldown must not expire from wall time without a simulation update");
    cooldown.update(0.005f);
    cooldown.pause();
    cooldown.update(10.0f);
    require(std::abs(cooldown.remainingCooldown() - 0.015f) < 0.00001f,
        "Explicit pause preserves cooldown remainder");
    cooldown.unpause();
    cooldown.update(0.015f);
    require(!cooldown.isOnCooldown(), "Cooldown expires after remaining simulation time");
    cooldown.startCooldown();
    cooldown.update(0.005f);
    cooldown.updateCooldownDuration(0.01f);
    require(std::abs(cooldown.remainingCooldown() - 0.005f) < 0.00001f,
        "Changing duration preserves already elapsed cooldown time");
    for (float dt : {0.0f, -1.0f, std::numeric_limits<float>::infinity(),
                     std::numeric_limits<float>::quiet_NaN()}) cooldown.update(dt);
    require(std::abs(cooldown.remainingCooldown() - 0.005f) < 0.00001f,
        "Invalid delta cannot rewind or poison a cooldown");

    Game game;
    game.onSwitch();
    game.playerEntity.position = {};
    game.gameState = GAME_PAUSED;
    game.gameTimer.pause();
    auto& animator = Animator::GetInstance();
    const auto animation = animator.animations.at("wasd_keys_tutorial").animation;
    const float animationBefore = animation->currentTime;
    BeginDrawing();
    game.draw();
    EndDrawing();
    require(animation->currentTime == animationBefore,
        "Rendering the paused world must not advance its animations");

    auto& enemies = EnemyManager::GetInstance();
    auto& debris = testDebrisManager();
    auto& bullets = BulletManager::GetInstance();
    auto& scrap = ScrapManager::GetInstance();
    auto shooter = std::make_unique<MidLevelEnemy>("pause_shooter", MID_LEVEL_ENEMY,
        Vector2{0.0f, -60.0f}, game.playerEntity.getPosition());
    auto* mid = shooter.get();
    mid->rotation = 0.0f;
    mid->fireCooldown.startCooldown();
    mid->applyKnockback({1.0f, 0.0f}, 1.0f);
    enemies.getEnemies()["pause_shooter"] = std::move(shooter);
    enemies.spawnCredit = 0.5;
    debris.debrisSpawnCooldown.startCooldown();
    scrap.spawnScrap({90.0f, 90.0f}, 5);
    bullets.addBullet(Bullet({30.0f, 30.0f}, {1.0f, 0.0f}, true));
    game.killCounter.increment();
    game.skills.equip(ABILITY_LASER_RINGS);
    game.gameState = GAME_RUNNING;
    EquipmentTestAccess::skillStep(game, 0.01f, {});
    game.gameState = GAME_PAUSED;
    game.playerEntity.boostCooldown = 2.0f;
    const float fireBefore = mid->fireCooldown.remainingCooldown();
    const double spawnBefore = enemies.spawnCredit;
    const float debrisBefore = debris.debrisSpawnCooldown.remainingCooldown();
    const float knockbackBefore = mid->knockbackCooldown.remainingCooldown();
    const float killBefore = game.killCounter.cooldown.remainingCooldown();
    const float skillBefore = game.skills.cooldown(ABILITY_LASER_RINGS);
    const float timeBefore = game.gameTimer.getElapsedTime();
    const auto positionBefore = mid->getPosition();
    const auto bulletBefore = bullets.getBullets().front().getPosition();
    const auto scrapBefore = scrap.getPickups().front()->getPosition();

    // Real wall time passes while the production pause/update/draw path runs.
    std::this_thread::sleep_for(std::chrono::seconds(10));
    for (GameState state : {GAME_PAUSED, GAME_AUGMENT_SELECTION}) {
        game.gameState = state;
        game.update();
        BeginDrawing(); game.draw(); EndDrawing();
        require(mid->fireCooldown.remainingCooldown() == fireBefore &&
            enemies.spawnCredit == spawnBefore &&
            debris.debrisSpawnCooldown.remainingCooldown() == debrisBefore &&
            mid->knockbackCooldown.remainingCooldown() == knockbackBefore,
            "Pause and card selection preserve shooting, spawn and knockback clocks");
        require(mid->getPosition().x == positionBefore.x && mid->getPosition().y == positionBefore.y &&
            bullets.getBullets().front().getPosition().x == bulletBefore.x &&
            bullets.getBullets().front().getPosition().y == bulletBefore.y &&
            scrap.getPickups().front()->getPosition().x == scrapBefore.x &&
            scrap.getPickups().front()->getPosition().y == scrapBefore.y,
            "Paused entities, projectiles and scrap retain exact positions");
        require(game.killCounter.cooldown.remainingCooldown() == killBefore &&
            game.skills.cooldown(ABILITY_LASER_RINGS) == skillBefore &&
            game.playerEntity.boostCooldown == 2.0f && game.gameTimer.getElapsedTime() == timeBefore &&
            animation->currentTime == animationBefore,
            "Pause and selection preserve HUD, skill, equipment, run and animation clocks");
    }
#ifdef GAME_DEBUG
    game.gameState = GAME_RUNNING;
    game.debugTools.consoleVisible = true;
    game.updateDebugConsole(true);
    game.update();
    BeginDrawing(); game.draw(); EndDrawing();
    require(mid->fireCooldown.remainingCooldown() == fireBefore &&
        animation->currentTime == animationBefore && game.gameTimer.getElapsedTime() == timeBefore,
        "Console capture freezes simulation and rendered world");
    game.debugTools.reset();
#endif
    // A fresh short frame after the long pause must not discharge the shooter.
    BeginDrawing(); EndDrawing();
    BeginDrawing(); EndDrawing();
    game.gameState = GAME_RUNNING;
    game.gameTimer.unpause();
    const auto bulletCount = bullets.getBullets().size();
    game.update();
    require(bullets.getBullets().size() == bulletCount && mid->fireCooldown.isOnCooldown() &&
        mid->fireCooldown.remainingCooldown() < fireBefore,
        "Resuming consumes only simulation delta and does not burst-fire the paused shooter");
    const float beforeStun = mid->fireCooldown.remainingCooldown();
    mid->applyStun(1.0f);
    mid->updateWithStatus(0.125f);
    require(std::abs(mid->fireCooldown.remainingCooldown() - (beforeStun - 0.125f)) < 0.00001f,
        "Stun stops movement and firing but still advances running-game recharge");
    const float fireAfterResume = mid->fireCooldown.remainingCooldown();
    const float animationAfterResume = animation->currentTime;
    game.gameState = GAME_OVER;
    game.update();
    BeginDrawing(); game.draw(); EndDrawing();
    require(mid->fireCooldown.remainingCooldown() == fireAfterResume && animation->currentTime == animationAfterResume,
        "Game-over presentation leaves world clocks and animations frozen");
    EquipmentTestAccess::restart(game);
    require(enemies.spawnCredit == 0 && !debris.debrisSpawnCooldown.isOnCooldown() &&
        !game.killCounter.cooldown.isOnCooldown() && game.gameTimer.getElapsedTime() == 0.0f,
        "Restart clears old cooldown debt and resets the simulation clock");

#ifdef _WIN32
    SetExitKey(KEY_NULL);
    game.playerEntity.autoShoot = true;
    game.playerEntity.shotCooldown = 0.0f;
    PostMessageA(GetWindowHandle(), 0x100, 0x1b, 1LL << 16); PollInputEvents();
    game.update();
    require(game.gameState == GAME_PAUSED && !WindowShouldClose(), "Escape pauses without closing window");
    PostMessageA(GetWindowHandle(), 0x101, 0x1b, (1LL << 31) | (1LL << 30) | (1LL << 16)); PollInputEvents();
    PostMessageA(GetWindowHandle(), 0x100, 0x50, 0x19LL << 16); PollInputEvents();
    game.update();
    require(game.gameState == GAME_RUNNING && bullets.getBullets().empty() &&
        game.gameTimer.getElapsedTime() == 0.0f, "P resumes without firing or advancing on transition frame");
    PostMessageA(GetWindowHandle(), 0x101, 0x50, (1LL << 31) | (1LL << 30) | (0x19LL << 16)); PollInputEvents();
    game.playerEntity.autoShoot = false;
#endif
    game.onExit();

    GameTimer timer;
    require(timer.setStartTime(120.0f) == 0 && timer.isRunning(),
        "Setting run time must work even when it exceeds process uptime");
    const float runBefore = timer.getElapsedTime();
    std::this_thread::sleep_for(std::chrono::milliseconds(30));
    require(timer.getElapsedTime() == runBefore,
        "Run timer advances only with simulation, not between update calls");
    timer.update(0.25f);
    timer.pause(); timer.update(10.0f);
    require(timer.getElapsedTime() == 120.25f && !timer.isRunning(), "Run timer pauses after debug time seek");
    timer.unpause(); timer.update(0.25f);
    require(timer.getElapsedTime() == 120.5f, "Run timer resumes without counting paused time");
    require(timer.setStartTime(-1.0f) == -1 && timer.getElapsedTime() == 120.5f,
        "Invalid time seek leaves the run timer intact");
    timer.reset(); timer.unpause(); timer.update(1.0f);
    require(timer.getElapsedTime() == 0.0f && !timer.isRunning(), "Reset timer stays stopped until start");
    for (int fps : {30, 60, 144}) {
        timer.start();
        for (int frame = 0; frame < fps * 10; ++frame) timer.update(1.0f / fps);
        require(std::abs(timer.getElapsedTime() - 10.0f) < 0.001f, "Simulation timer has frame-rate parity");
    }
    return checks;
}
