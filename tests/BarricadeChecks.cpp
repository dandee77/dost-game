#include "TestAccess.hpp"
#include "EquipmentAccess.hpp"
#include "BarricadeEnemy.hpp"
#include "Balance.hpp"
#include "raymath.h"
#include <stdexcept>

int runBarricadeChecks(const std::string& artifactDirectory)
{
    const float startRadius = Balance::BARRICADE_START_RADIUS;
    const float endRadius = Balance::BARRICADE_END_RADIUS;
    const float eventZoom = Config::CAMERA_ZOOM_BARRICADE;
    int checks = 0;
    const auto require = [&](bool condition, const char* message) {
        ++checks;
        if (!condition) throw std::runtime_error(message);
    };
    Game game;
    game.onSwitch();
    auto& event = game.barricadeEvent;
    auto& player = game.playerEntity;
    auto& manager = EnemyManager::GetInstance();
    auto& enemies = manager.getEnemies();
    const auto reset = [&]() {
        event.reset();
        for (const auto& [id, enemy] : enemies) Animator::GetInstance().Remove(id);
        manager.reset();
        testDebrisManager().reset();
        BulletManager::GetInstance().reset();
        player.init(); player.position = {}; player.rotation = 0;
        game.gameState = GAME_RUNNING;
        game.gameTimer.setStartTime(1.0f);
        game.killCounter.reset();
        utils::gameCamera = {{1920, 1080}, {}, 0, Config::CAMERA_ZOOM_PLAY};
    };
    const auto start = [&]() { reset(); require(event.start({}), "Start complete barricade"); };
    const auto advance = [&](float dt, float runTime = 0.0f) {
        event.update(dt, runTime, player.getPosition());
        for (auto& [id, enemy] : enemies)
            if (enemy->getEnemyType() == BARRICADE_ENEMY) static_cast<BarricadeEnemy&>(*enemy).advance(dt);
    };
    const auto low = [&](Vector2 position) {
        auto enemy = std::make_unique<LowLevelEnemy>("event_bystander", LOW_LEVEL_ENEMY, position, Vector2{});
        enemy->rotation = 0;
        enemies["event_bystander"] = std::move(enemy);
    };

    reset();
    event.update(0, 119.99f, {});
    require(!event.isActive(), "No automatic event before two minutes");
    event.update(0, 120, {});
    require(event.isContaining() && enemies.size() == Balance::BARRICADE_SEGMENTS, "Automatic complete ring at two minutes");
    for (const auto& [id, enemy] : enemies) {
        require(enemy->getEnemyType() == BARRICADE_ENEMY && enemy->getHealth() == Balance::BARRICADE_HEALTH,
            "Barricade has its own enemy type and durable health");
        require(!enemy->canReceiveKnockback(), "Weapon knockback cannot dislodge barricade");
    }
    advance(34, 154);
    event.update(0, 160, {});
    require(!event.isActive() && enemies.empty(), "Automatic event fires once per run");
    reset(); event.update(0, 120, {});
    require(event.isActive(), "Reset rearms automatic event");

    // Cover both ends of the shrinking geometry, every seam and long boosted steps.
    for (float age : {0.0f, 29.99f}) {
        start(); advance(age); advance(0);
        const float radius = Lerp(Balance::BARRICADE_START_RADIUS, Balance::BARRICADE_END_RADIUS, age / 30);
        for (int sample = 0; sample < 720; ++sample) {
            const float angle = sample * 2 * PI / 720;
            const Vector2 direction = {std::cos(angle), std::sin(angle)};
            player.position = Vector2Scale(direction, radius + 80);
            player.velocity = Vector2Scale(direction, 200);
            player.playerState = PLAYER_IFRAME; player.stateElapsed = 0.25f;
            const int health = player.getHealth();
            require(event.constrainPlayer(player, {}), "Intact ring stops a swept boost at every angle");
            require(Vector2Length(player.getPosition()) < radius, "Seam resolution keeps player inside");
            require(player.getHealth() == health && player.stateElapsed == 0.25f, "Physical blocking preserves iframe health and clock");
            require(Vector2DotProduct(player.getVelocity(), direction) <= 0, "Wall nudges boosted velocity inward");
        }
        const Vector2 gapDirection = Vector2Normalize(enemies.at("enemy_0")->getPosition());
        enemies.at("enemy_0")->takeDamage(Balance::BARRICADE_HEALTH);
        // As 64 rocks compress to the original small radius, neighboring bodies
        // narrow a single opening. Clear the neighbors for a ship-sized late gap.
        if (age > 0.0f) {
            enemies.at("enemy_1")->takeDamage(Balance::BARRICADE_HEALTH);
            enemies.at("enemy_63")->takeDamage(Balance::BARRICADE_HEALTH);
        }
        player.position = Vector2Scale(gapDirection, radius + 80);
        require(!event.constrainPlayer(player, {}), "Destroyed sections open traversable gaps at both radii");
        require(std::abs(Vector2Length(player.position) - radius - 80) < 0.001f, "No invisible circle blocks destroyed gap");
    }

    std::vector<Vector2> orbitPositions;
    for (int fps : {30, 144}) {
        start();
        for (int frame = 0; frame < fps * 10; ++frame) advance(1.0f / fps);
        orbitPositions.push_back(enemies.at("enemy_0")->getPosition());
        require(std::abs(std::atan2(orbitPositions.back().y, orbitPositions.back().x) * RAD2DEG - 40) < 0.01f,
            "Whole ring orbits at four degrees per second");
        require(std::abs(event.getRadius() - (startRadius - (startRadius - endRadius) / 3)) < 0.001f,
            "Larger ring shrinks at the rate required to reach its endpoint in thirty seconds");
        for (int sample = 0; sample < 360; ++sample) {
            advance(1.0f / fps);
            const float angle = sample * DEG2RAD;
            const Vector2 direction = {std::cos(angle), std::sin(angle)};
            player.position = Vector2Scale(direction, event.getRadius() + 40);
            player.playerState = PLAYER_IFRAME;
            require(event.constrainPlayer(player, {}) && Vector2Length(player.position) < event.getRadius(),
                "Moving rotating ring blocks swept travel through every angle");
        }
    }
    require(Vector2Distance(orbitPositions.front(), orbitPositions.back()) < 0.01f, "Orbit agrees at 30 and 144 FPS");

    start();
    player.position = {startRadius + 40, 0};
    require(event.constrainPlayer(player, {}) && player.getHealth() == 90, "First touch damages hull");
    player.position = {startRadius + 40, 0};
    require(event.constrainPlayer(player, {}) && player.getHealth() == 90, "Stunned contact blocks without repeated damage");
    player.playerState = PLAYER_IFRAME; player.position = {startRadius + 40, 0};
    event.constrainPlayer(player, {});
    require(player.getHealth() == 90, "Iframe contact causes no additional damage");
    player.playerState = PLAYER_DEFAULT; player.position = {startRadius + 40, 0};
    event.constrainPlayer(player, {});
    require(player.getHealth() == 80, "Renewed vulnerability allows next contact damage");
    player.playerState = PLAYER_IFRAME; player.stateElapsed = player.iframeDuration;
    player.velocity = {}; player.update(); player.position = {startRadius + 40, 0};
    event.constrainPlayer(player, {});
    require(player.getHealth() == 70, "Actual player update expires iframe and enables wall damage again");
    start(); player.setShield(SHIELD_ROUND); player.position = {startRadius + 40, 0};
    require(event.constrainPlayer(player, {}) && player.getHealth() == 100 && player.position.x < startRadius,
        "Shield protects health without bypassing containment");
    start(); player.position = {startRadius - Balance::BARRICADE_BODY_RADIUS - Balance::PLAYER_RADIUS + 0.1f, 0}; player.playerState = PLAYER_IFRAME;
    const auto stationary = player.position;
    advance(1);
    require(event.constrainPlayer(player, stationary) && player.position.x < stationary.x, "Shrinking wall moves stationary player inward");
    low(enemies.at("enemy_0")->getPosition());
    const auto rockPosition = enemies.at("enemy_0")->getPosition();
    manager.separateEnemies(1.0f / 60);
    require(Vector2Distance(enemies.at("event_bystander")->getPosition(), rockPosition) == 0 &&
        Vector2Distance(enemies.at("enemy_0")->getPosition(), rockPosition) == 0, "Normal enemies overlap barricade without separation");

    // Actual equipment damage resolution and a lethal gap, including piercing and splash.
    for (ProjectileKind kind : {PROJECTILE_CANNON, PROJECTILE_HEAVY, PROJECTILE_ROCKET}) {
        start();
        Bullet shot({}, {1, 0}, false, 1);
        shot.configure(kind, 40, 1, 10); shot.position = {startRadius + 40, 0};
        BulletManager::GetInstance().addBullet(shot);
        EquipmentTestAccess::resolve(game);
        require(enemies.at("enemy_0")->getHealth() == 80, "Projectile weapon damages durable barricade");
        require(Vector2Length(enemies.at("enemy_0")->getVelocity()) == 0, "Equipment damage leaves ring anchored");
    }
    start(); player.position = {startRadius - 50, 0}; player.rotation = 90; player.setWeapon(WEAPON_LASER);
    EquipmentTestAccess::updateWeapon(player, 0, true); EquipmentTestAccess::resolve(game);
    require(enemies.at("enemy_0")->getHealth() == Balance::BARRICADE_HEALTH - Balance::LASER_DAMAGE, "Laser tick damages barricade");
    EquipmentTestAccess::resolve(game);
    require(enemies.at("enemy_0")->getHealth() == Balance::BARRICADE_HEALTH - Balance::LASER_DAMAGE, "Laser cannot duplicate a consumed tick");
    EquipmentTestAccess::updateWeapon(player, 3, true); EquipmentTestAccess::resolve(game);
    require(!enemies.contains("enemy_0") && game.killCounter.getCount() > 0, "Sustained beam kills and removes segment through normal combat");

    // Exercise real Game::update scheduling and the original player's bullet path.
    reset(); BeginDrawing(); EndDrawing(); BeginDrawing(); EndDrawing();
    game.gameTimer.setStartTime(120);
    game.update();
    require(game.gameState == GAME_AUGMENT_SELECTION && !event.isActive(), "Two-minute augment transition freezes event until resume");
    game.gameState = GAME_RUNNING; game.augmentCards.clear(); game.gameTimer.setStartTime(121);
    manager.enemySpawnCooldown.lastUsedTime = -100;
    testDebrisManager().debrisSpawnCooldown.startCooldown();
    game.update();
    require(event.isContaining() && enemies.size() > Balance::BARRICADE_SEGMENTS, "Game starts event while normal enemy spawning continues");
    require(std::abs(Vector2Length(enemies.at("enemy_0")->getPosition()) - Lerp(startRadius, endRadius, event.getElapsed() / 30)) < 0.001f,
        "Game keeps event and segment clocks synchronized");
    const auto hitPoint = enemies.at("enemy_0")->getPosition();
    Bullet legacy(hitPoint, {}, false, 1); legacy.setBulletSpeed(0);
    BulletManager::GetInstance().addBullet(legacy);
    auto debris = std::make_unique<Debris>(Vector2{}, DEBRIS_CLUMP);
    debris->position = hitPoint; debris->velocity = {};
    const auto debrisId = debris->getDebrisID();
    testDebrisManager().getDebris()[debrisId] = std::move(debris);
    game.update();
    require(enemies.contains("enemy_0") && enemies.at("enemy_0")->getHealth() < 120,
        "Original default bullet damages barricade in live update");
    require(testDebrisManager().getDebris().contains(debrisId), "Ordinary debris overlap cannot destroy event segment");
    start();
    for (auto& [id, enemy] : enemies) enemy->takeDamage(Balance::BARRICADE_HEALTH);
    event.update(0, 0, {});
    require(!event.isActive() && enemies.empty(), "Destroying all segments ends event immediately");

    start(); low({});
    advance(30);
    require(event.getPhase() == BARRICADE_SCATTERING, "Thirty seconds ends containment");
    require(std::abs(event.getRadius() - 45.0f) < 0.001f, "Thirty-second radius matches original compact barricade");
    for (const auto& [id, enemy] : enemies) {
        if (enemy->getEnemyType() == BARRICADE_ENEMY)
            require(std::abs(Vector2Length(enemy->getPosition()) - 45.0f) < 0.001f,
                "Every surviving segment reaches the original radius at thirty seconds");
    }
    const auto releaseDirection = Vector2Normalize(enemies.at("enemy_0")->getPosition());
    player.position = {100, 0};
    require(!event.constrainPlayer(player, {}), "Scattering releases physical containment");
    advance(1);
    require(Vector2Distance(Vector2Normalize(enemies.at("enemy_0")->getPosition()), releaseDirection) < 0.001f,
        "Scattering keeps release direction instead of continuing orbit");
    require(std::abs(Vector2Length(enemies.at("enemy_0")->getPosition()) - (endRadius + Balance::BARRICADE_SCATTER_SPEED)) < 0.001f, "Surviving barricade scatters outward");
    require(Vector2Length(enemies.at("event_bystander")->getPosition()) == 0, "Event never scatters unrelated enemies");
    advance(3);
    require(!event.isActive() && enemies.size() == 1 && enemies.contains("event_bystander"), "Timeout removes only event enemies");
    require(player.getScore() == 0, "Timed despawn awards no kill rewards");

    start(); utils::gameCamera.zoom = Config::CAMERA_ZOOM_BARRICADE;
    event.finishIfEscaped({500, 0}, utils::gameCamera);
    require(event.isActive(), "Distance alone cannot despawn a visible ring");
    utils::gameCamera.target = {500, 0};
    event.finishIfEscaped({70, 0}, utils::gameCamera);
    require(event.isActive(), "Offscreen alone cannot despawn a nearby ring");
    event.finishIfEscaped({500, 0}, utils::gameCamera);
    require(!event.isActive() && enemies.empty(), "Distance plus fully offscreen ring cleans up escape");

    std::vector<float> zooms;
    for (int fps : {30, 144}) {
        start(); EquipmentTestAccess::camera(game, 1.0f / fps);
        require(utils::gameCamera.zoom < 20 && utils::gameCamera.zoom > eventZoom, "Zoom out begins smoothly");
        for (int frame = 1; frame < fps * 3; ++frame) EquipmentTestAccess::camera(game, 1.0f / fps);
        zooms.push_back(utils::gameCamera.zoom);
        require(std::abs(utils::gameCamera.zoom - eventZoom) < 0.01f, "Event zoom converges");
        advance(30); EquipmentTestAccess::camera(game, 1.0f / fps);
        require(utils::gameCamera.zoom > eventZoom && utils::gameCamera.zoom < 20, "Timeout smoothly restores zoom");
        for (int frame = 1; frame < fps * 3; ++frame) EquipmentTestAccess::camera(game, 1.0f / fps);
        require(std::abs(utils::gameCamera.zoom - 20) < 0.01f, "Normal zoom restored");
    }
    require(std::abs(zooms.front() - zooms.back()) < 0.001f, "Zoom agrees at 30 and 144 FPS");

    start();
    for (auto state : {GAME_PAUSED, GAME_AUGMENT_SELECTION}) {
        game.gameState = state; game.update();
        require(event.getElapsed() == 0 && enemies.at("enemy_0")->getPosition().x == startRadius && utils::gameCamera.zoom == 20,
            "Pause and augment selection freeze event movement, time and zoom");
    }
#ifdef GAME_DEBUG
    reset(); DebugTools debug;
    debug.input = "spawn b"; EquipmentTestAccess::complete(debug);
    require(debug.input == "spawn barricade event", "Barricade command autocompletes");
    EquipmentTestAccess::execute(debug, nullptr, &event);
    require(!event.isActive(), "Command requires active player");
    debug.input = "spawn barricade event"; EquipmentTestAccess::execute(debug, &player);
    require(!event.isActive(), "Command requires Game event owner");
    player.health = 0; debug.input = "spawn barricade event"; EquipmentTestAccess::execute(debug, &player, &event);
    require(!event.isActive(), "Command rejects dead player");
    player.health = 100;
    for (const char* invalid : {"spawn barricade", "spawn barricade event extra", "spawn barricade event 2"}) {
        debug.input = invalid; EquipmentTestAccess::execute(debug, &player, &event);
        require(!event.isActive(), "Malformed event command has no side effects");
    }
    debug.input = "spawn barricade event"; EquipmentTestAccess::execute(debug, &player, &event);
    require(event.isActive() && enemies.size() == Balance::BARRICADE_SEGMENTS, "Command creates complete event");
    debug.input = "spawn barricade event"; EquipmentTestAccess::execute(debug, &player, &event);
    require(enemies.size() == Balance::BARRICADE_SEGMENTS, "Duplicate event command cannot stack rings");
    const auto command = [&](const std::string& text) {
        debug.input = text; EquipmentTestAccess::execute(debug, &player, &event);
    };
    command("hitbox on");
    require(debug.overlayVisible && !debug.statsVisible, "Hitbox command only enables collision drawing");
    const auto debugTarget = LoadRenderTexture(3840, 2160);
    BeginTextureMode(debugTarget); ClearBackground(BLANK); debug.drawOverlay(player, GAME_RUNNING, event); EndTextureMode();
    Image hitboxOnly = LoadImageFromTexture(debugTarget.texture);
    const auto* pixels = static_cast<const Color*>(hitboxOnly.data);
    bool emptyOverlay = true;
    for (int index = 0; index < hitboxOnly.width * hitboxOnly.height; ++index)
        emptyOverlay = emptyOverlay && pixels[index].a == 0;
    require(emptyOverlay, "Hitbox-only mode renders no statistics panel");
    UnloadImage(hitboxOnly);
    debug.input = "sta"; EquipmentTestAccess::complete(debug);
    require(debug.input == "stats", "Stats command autocompletes");
    command("stats on"); command("hitbox off");
    require(debug.statsVisible && !debug.overlayVisible, "Stats and hitboxes toggle independently");
    command("stats on"); command("stats invalid");
    require(debug.statsVisible, "Stats on is idempotent and malformed arguments do not change state");
    require(event.getAliveSegments() == Balance::BARRICADE_SEGMENTS && event.getRadius() == startRadius,
        "Event diagnostics report live count and radius");
    enemies.at("enemy_0")->takeDamage(Balance::BARRICADE_HEALTH);
    require(event.getAliveSegments() == Balance::BARRICADE_SEGMENTS - 1, "Event diagnostics exclude destroyed segments");
    BeginTextureMode(debugTarget); ClearBackground(BLACK); debug.drawOverlay(player, GAME_RUNNING, event); EndTextureMode();
    Image statsCapture = LoadImageFromTexture(debugTarget.texture); ImageFlipVertical(&statsCapture);
    require(ExportImage(statsCapture, (artifactDirectory + "/barricade-stats.png").c_str()), "Export event stats preview");
    UnloadImage(statsCapture); UnloadRenderTexture(debugTarget);
    command("stats"); require(!debug.statsVisible, "Stats without argument toggles off");
    command("stats toggle"); command("stats off"); require(!debug.statsVisible, "Explicit stats toggle and off work");
    command("stats on"); debug.reset();
    require(!debug.statsVisible && !debug.overlayVisible, "Reset clears both diagnostic modes");
    debug.input = "stats on"; EquipmentTestAccess::execute(debug, nullptr, &event);
    require(!debug.statsVisible, "Stats rejects missing run");
    game.gameState = GAME_RUNNING; game.debugTools.inputCaptured = true; game.update();
    require(event.getElapsed() == 0, "Console freezes event");
    game.debugTools.reset();
    reset(); manager.spawnLowEnemies({}, Balance::ENEMY_LIMIT - 1);
    require(!event.start({}) && enemies.size() == Balance::ENEMY_LIMIT - 1, "Insufficient capacity never spawns partial ring");
#endif

    start(); player.health = 10; player.position = {startRadius + 40, 0};
    EquipmentTestAccess::barricadeContact(game, {});
    require(game.gameState == GAME_OVER && game.deathInfo.killerName == "Barricade", "Lethal wall contact reaches game over");
    game.update(); require(!event.isActive(), "Game over clears event");
    start(); EquipmentTestAccess::restart(game);
    require(!event.isActive() && enemies.empty() && utils::gameCamera.zoom == 20, "Restart clears event and restores camera");

    start(); low({-18, 15});
    game.gameTimer.setStartTime(121);
    utils::gameCamera.zoom = Config::CAMERA_ZOOM_BARRICADE;
    game.gameState = GAME_PAUSED;
    const auto target = LoadRenderTexture(3840, 2160);
    BeginTextureMode(target); ClearBackground(BLACK); game.draw(); EndTextureMode();
    Image capture = LoadImageFromTexture(target.texture); ImageFlipVertical(&capture);
    require(ExportImage(capture, (artifactDirectory + "/barricade-event.png").c_str()), "Export native barricade preview");
    UnloadImage(capture); UnloadRenderTexture(target);
    game.onExit();
    require(!event.isActive() && utils::gameCamera.zoom == 20, "Leaving scene clears event and camera");
    reset();
    std::cout << "Barricade: " << checks << " checks\n";
    return checks;
}
