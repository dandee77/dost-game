#include "TestAccess.hpp"
#include "EquipmentAccess.hpp"
#include "Balance.hpp"
#include "Theme.hpp"
#include "ScrapManager.hpp"
#include "raymath.h"
#include <stdexcept>

int runDebrisChecks(const std::string& artifactDirectory)
{
    int checks = 0;
    const auto require = [&](bool condition, const char* message) {
        ++checks;
        if (!condition) throw std::runtime_error(message);
    };
    auto& scraps = ScrapManager::GetInstance();
    auto& debris = testDebrisManager();
    Game game;
    game.onSwitch();
    auto& player = game.playerEntity;
    const auto clear = [&]() {
        EquipmentTestAccess::restart(game);
        player.position = {};
        player.rotation = 0;
        game.gameTimer.setStartTime(1.0f);
        EnemyManager::GetInstance().enemySpawnCooldown.startCooldown();
        debris.debrisSpawnCooldown.startCooldown();
    };
    const auto spawn = [&](DebrisKind kind, Vector2 position) {
        auto item = std::make_unique<Debris>(Vector2{}, kind);
        item->position = position;
        item->velocity = {};
        item->rotation = 0;
        const auto id = item->getDebrisID();
        debris.getDebris().emplace(id, std::move(item));
        return id;
    };
    for (int type = 0; type < DEBRIS_KIND_COUNT; ++type) {
        const auto kind = static_cast<DebrisKind>(type);
        const auto& texture = ResourceManager::GetInstance().GetTextureRef(DEBRIS_INFO[type].texture);
        require(texture.id != 0 && texture.width == 96 && texture.height == 96, "Every debris variant loads as 96x96");
        for (int repeat = 0; repeat < 30; ++repeat) {
            Debris item({}, kind);
            require(item.getDebrisSize() == Balance::DEBRIS_RADII[type], "Variant collision size never varies");
            require(item.getSize().x == Theme::DEBRIS_DRAW_SIZES[type], "Variant draw size never varies");
        }
        clear();
        const auto id = spawn(kind, {30, 0});
        require(debris.removeDebris(id, true), "Player destruction succeeds");
        require(scraps.count() == Theme::SCRAP_FRAGMENTS, "Every variant uses the same eight fragment exits");
        require(scraps.pendingValue() == Balance::DEBRIS_SCRAP_VALUES[type], "Breakup preserves exact variant value");
        require(!debris.removeDebris(id, true), "Repeated destruction is harmless");
        require(scraps.update(0.5f, {}) == 0, "No credit during scatter");
        int total = 0;
        for (int frame = 0; frame < 180; ++frame) total += scraps.update(1.0f / 60.0f, {});
        require(total == Balance::DEBRIS_SCRAP_VALUES[type] && scraps.count() == 0, "All shards home and credit exactly once");
        require(scraps.update(1.0f, {}) == 0, "No duplicate collection");
    }
    require(Theme::DEBRIS_DRAW_SIZES[DEBRIS_WING] > Theme::DEBRIS_DRAW_SIZES[DEBRIS_PIPE], "Satellite wing is larger than small junk");
    clear();
    debris.removeDebris(spawn(DEBRIS_WING, {30, 0}), false);
    require(scraps.pendingValue() == 0 && scraps.update(1, {}) == 0 && scraps.count() == 0, "Environmental breakup fades without rewards");
    clear();
    spawn(DEBRIS_WING, {1000, 0});
    debris.update({}, game.gameTimer);
    require(debris.getDebris().empty() && scraps.count() == 0, "Offscreen cleanup produces no fragments or rewards");

    // Fixed analytic scatter is independent of frame rate and hands off continuously.
    ScrapPickup single({}, 33, DEBRIS_WING, 48, 2, 1, true);
    ScrapPickup many({}, 33, DEBRIS_WING, 48, 2, 1, true);
    single.advance(0.8f, {500, 0});
    for (int i = 0; i < 80; ++i) many.advance(0.01f, {500, 0});
    require(Vector2Distance(single.getPosition(), many.getPosition()) < 0.001f, "Scatter agrees across frame rates");
    const auto endpoint = single.getPosition();
    single.advance(0, {500, 0});
    require(Vector2Distance(endpoint, single.getPosition()) == 0, "Zero dt freezes pickup");
    single.advance(0.001f, {500, 0});
    require(Vector2Distance(endpoint, single.getPosition()) <= 0.091f, "Homing begins at exact scatter endpoint");
    single.advance(10, {});
    require(single.isCollected() && Vector2Length(single.getPosition()) == 0, "Large frame cannot overshoot player");
    clear();
    for (int i = 0; i < 200; ++i) scraps.spawnDebris({30, 0}, 0, DEBRIS_WING, 48, true);
    require(scraps.count() <= Balance::SCRAP_MAX_PICKUPS, "Pickup cap bounds render workload");
    require(scraps.pendingValue() == 200 * Balance::DEBRIS_SCRAP_VALUES[DEBRIS_WING], "Overflow merges all earned value");
    int massCollected = 0;
    for (int i = 0; i < 180; ++i) massCollected += scraps.update(1.0f / 60.0f, {});
    require(massCollected == 1600, "Merged pickup value is collected without cargo cap");
    clear();
    game.harvestedScrap = 100;
    scraps.spawnDebris({}, 0, DEBRIS_WING, 48, true);
    require(scraps.update(0.8f, {}) == 0, "Breakup reaches pickup phase without early credit");
    SetTargetFPS(60);
    for (int frame = 0; frame < 30; ++frame) { BeginDrawing(); EndDrawing(); game.update(); }
    SetTargetFPS(0);
    require(game.harvestedScrap == 108 && scraps.count() == 0, "Live Game updates counter beyond planned cargo cap");

    // Actual weapon integration, including legacy bullets through Game::update.
    for (auto weapon : {WEAPON_DEFAULT, WEAPON_CANNON, WEAPON_HEAVY, WEAPON_ROCKETS, WEAPON_LASER}) {
        clear();
        const auto id = spawn(DEBRIS_CANISTER, {0, -20});
        player.setWeapon(weapon);
        if (weapon == WEAPON_LASER) {
            player.laserActive = true; player.pendingLaserTicks = 1;
            EquipmentTestAccess::resolve(game);
        } else {
            Bullet shot({0, -20}, {0, -1}, false);
            if (weapon != WEAPON_DEFAULT) {
                const auto kind = weapon == WEAPON_HEAVY ? PROJECTILE_HEAVY : weapon == WEAPON_ROCKETS ? PROJECTILE_ROCKET : PROJECTILE_CANNON;
                shot.configure(kind, 40, 1, 0);
            } else shot.setBulletSpeed(0);
            BulletManager::GetInstance().addBullet(shot);
            if (weapon == WEAPON_DEFAULT) game.update();
            else EquipmentTestAccess::resolve(game);
        }
        require(!debris.getDebris().contains(id), "Every player weapon destroys debris");
        require(scraps.pendingValue() == Balance::DEBRIS_SCRAP_VALUES[DEBRIS_CANISTER], "Every player weapon enables harvest");
    }
    clear();
    scraps.spawnDebris({30, 0}, 0, DEBRIS_CLUMP, 20, true);
    game.gameState = GAME_PAUSED; game.update();
    require(scraps.getPickups().front()->getElapsed() == 0, "Pause freezes fragments");
    game.gameState = GAME_AUGMENT_SELECTION; game.update();
    require(scraps.getPickups().front()->getElapsed() == 0, "Augment choice freezes fragments");
#ifdef GAME_DEBUG
    game.debugTools.inputCaptured = true;
    game.gameState = GAME_RUNNING; game.update();
    require(scraps.getPickups().front()->getElapsed() == 0, "Debug console freezes fragments");
    game.debugTools.inputCaptured = false;
    game.debugTools.input = "spawn debris all";
    EquipmentTestAccess::execute(game.debugTools, &player, &game.barricadeEvent);
    require(debris.getDebris().size() == DEBRIS_KIND_COUNT, "Debug gallery spawns exactly ten types");
#endif
    game.harvestedScrap = 123;
    EquipmentTestAccess::restart(game);
    require(scraps.count() == 0 && game.harvestedScrap == 0, "Restart clears particles and harvested balance");
    scraps.spawnDebris({30, 0}, 0, DEBRIS_CLUMP, 20, true);
    game.harvestedScrap = 321; game.onExit();
    require(scraps.count() == 0 && game.harvestedScrap == 0, "Scene exit clears harvesting state");
    clear();
    scraps.spawnDebris({30, 0}, 0, DEBRIS_CLUMP, 20, true);
    game.harvestedScrap = 321; game.gameState = GAME_OVER; game.update();
    require(scraps.count() == 0 && game.harvestedScrap == 0, "Death loses harvested scrap and cancels flight");

    // Native renderer: actual fixed-size variants and continuous pickup phases.
    const auto render = LoadRenderTexture(1600, 900);
    BeginTextureMode(render); ClearBackground(Color{18, 14, 30, 255});
    for (int i = 0; i < DEBRIS_KIND_COUNT; ++i) {
        const int column = i % 5, row = i / 5;
        Camera2D camera = {{160.0f + column * 320, 160.0f + row * 280}, {}, 0, 9};
        Debris item({}, static_cast<DebrisKind>(i)); item.position = {}; item.rotation = 0;
        BeginMode2D(camera); item.draw(); EndMode2D();
        DrawText(DEBRIS_INFO[i].name, 45 + column * 320, 260 + row * 280, 20, WHITE);
    }
    const char* stages[] = {"BREAK", "SCATTER", "RED GLOW", "ABSORB"};
    for (int phase = 0; phase < 4; ++phase) {
        scraps.reset();
        scraps.spawnDebris({}, 0, DEBRIS_WING, 48, true);
        scraps.update(phase == 0 ? 0 : phase == 1 ? 0.3f : phase == 2 ? 0.8f : 1.0f, {35, 0});
        Camera2D camera = {{120.0f + phase * 400, 710}, {}, 0, 5};
        BeginMode2D(camera); scraps.draw(); EndMode2D();
        DrawText(stages[phase], 65 + phase * 400, 830, 22, Theme::COLOR_HARVEST);
    }
    EndTextureMode();
    Image capture = LoadImageFromTexture(render.texture); ImageFlipVertical(&capture);
    require(ExportImage(capture, (artifactDirectory + "/debris-harvest-preview.png").c_str()), "Export native debris and harvest render");
    UnloadImage(capture); UnloadRenderTexture(render);
    game.onExit();
    std::cout << "Debris: " << checks << " checks\n";
    return checks;
}
