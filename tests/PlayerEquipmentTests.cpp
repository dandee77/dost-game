#include "TestAccess.hpp"
#include "EquipmentAccess.hpp"
#include "Balance.hpp"
#include "Theme.hpp"
#include "raymath.h"
#include <stdexcept>

#ifdef _WIN32
extern "C" __declspec(dllimport) int __stdcall PostMessageA(void*, unsigned int, unsigned long long, long long);
#endif

namespace {
    int checks = 0;
    void require(bool condition, const char* description)
    {
        ++checks;
        if (!condition) throw std::runtime_error(description);
    }
    void near(float actual, float expected, const char* description)
    {
        require(std::abs(actual - expected) < 0.001f, description);
    }
    void clearWorld(Game& game)
    {
        EnemyManager::GetInstance().reset();
        testAsteroidManager().reset();
        BulletManager::GetInstance().reset();
        DamageIndicatorManager::GetInstance().reset();
        game.playerEntity.init();
        game.playerEntity.position = {0.0f, 0.0f};
        game.playerEntity.rotation = 0.0f;
        game.killCounter.reset();
        game.gameState = GAME_RUNNING;
    }
    void enemy(const std::string& id, Vector2 position, int health = 100)
    {
        auto target = std::make_unique<LowLevelEnemy>(id, LOW_LEVEL_ENEMY, position, Vector2{});
        target->health = health;
        target->speed = 0.0f;
        target->velocity = {};
        target->knockbackVelocity = {};
        EnemyManager::GetInstance().getEnemies()[id] = std::move(target);
    }
    int hp(const std::string& id)
    {
        const auto& enemies = EnemyManager::GetInstance().getEnemies();
        const auto found = enemies.find(id);
        return found == enemies.end() ? 0 : found->second->getHealth();
    }
    void projectile(ProjectileKind kind, Vector2 from, Vector2 to, int damage, int pierce = 1)
    {
        Bullet shot(from, Vector2Subtract(to, from), false, pierce);
        shot.configure(kind, damage, kind == PROJECTILE_HEAVY ? Balance::HEAVY_RADIUS : Balance::CANNON_RADIUS, 0.0f);
        shot.position = to;
        BulletManager::GetInstance().addBullet(shot);
    }
}

int main(int argc, char** argv)
{
    const std::string artifactDirectory = argc > 1 ? argv[1] : "build";
    SetTraceLogLevel(LOG_WARNING);
    SetConfigFlags(FLAG_WINDOW_HIDDEN);
    InitWindow(1280, 720, "Player equipment validation");
    InitAudioDevice();
    SetMasterVolume(0.0f);
    auto& resources = ResourceManager::GetInstance();
    resources.LoadFonts(); resources.LoadSounds(); resources.LoadMusics(); resources.LoadTextures();
    while (resources.GetTextureLoadingProgress() < 100) {
        resources.ProcessLoadedTextures();
        BeginDrawing(); EndDrawing();
    }
    resources.ProcessLoadedTextures();
    try {
        Game game;
        game.onSwitch();
        auto& player = game.playerEntity;
        auto& bm = BulletManager::GetInstance();
        for (const auto& [key, path] : resources.texturePaths) {
            if (key.starts_with("player_") && path.find("textures/player/") != std::string::npos)
                require(resources.GetTexture(key).id != 0, "New texture failed to load");
        }
        require(resources.GetSound("player_shoot").stream.buffer != nullptr, "Managed shooting sound");
        near(Bullet::hitFraction({-10, 0}, {10, 0}, {0, 0}, 2), 0.4f, "Swept circle entry");
        require(Bullet::hitFraction({-10, 3}, {10, 3}, {0, 0}, 2) < 0, "Swept miss");
        near(Bullet::hitFraction({0, 0}, {0, 0}, {0, 0}, 2), 0, "Stationary overlap");
        near(Bullet::hitFraction({-10, 2}, {10, 2}, {0, 0}, 2), 0.5f, "Tangent hit");

        // Laser cadence is equivalent across frame rates and catches up long frames.
        for (int fps : {30, 60, 144}) {
            clearWorld(game);
            player.setBuild(BUILD_LASER);
            int ticks = 0;
            for (int frame = 0; frame < fps; ++frame) {
                EquipmentTestAccess::updateWeapon(player, 1.0f / static_cast<float>(fps), true);
                ticks += player.consumeLaserTicks();
            }
            require(ticks == 11, "Laser immediate tick plus ten ticks per second");
            EquipmentTestAccess::updateWeapon(player, 0.0f, false);
            require(!player.isLaserActive() && player.consumeLaserTicks() == 0, "Laser stops on release");
        }
        clearWorld(game);
        player.setWeapon(WEAPON_LASER);
        EquipmentTestAccess::updateWeapon(player, 0.35f, true);
        require(player.consumeLaserTicks() == 4, "Laser catches up a long frame");
        EquipmentTestAccess::updateWeapon(player, 0.0f, false);
        EquipmentTestAccess::updateWeapon(player, 0.0f, true);
        require(player.consumeLaserTicks() == 0, "Tapping laser cannot bypass tick cooldown");
        player.increasePlayerAttackSpeed();
        near(EquipmentTestAccess::weaponCooldown(player), 0.09f, "Rapid fire affects beam cadence");

        clearWorld(game);
        player.setWeapon(WEAPON_LASER);
        enemy("beam_near", {0, -20}); enemy("beam_far", {0, -80});
        enemy("beam_side", {20, -20}); enemy("beam_behind", {0, 20}); enemy("beam_beyond", {0, -120});
        EquipmentTestAccess::updateWeapon(player, 0.0f, true);
        EquipmentTestAccess::resolve(game);
        require(hp("beam_near") == 96 && hp("beam_far") == 96, "Beam damages every target along its segment");
        require(hp("beam_side") == 100 && hp("beam_behind") == 100 && hp("beam_beyond") == 100, "Beam rejects targets outside hitbox");
        EquipmentTestAccess::resolve(game);
        require(hp("beam_near") == 96, "Damage ticks consumed only once");
        player.rotation = 90.0f;
        enemy("beam_rotated", {50, 0});
        EquipmentTestAccess::updateWeapon(player, 0.1f, true);
        EquipmentTestAccess::resolve(game);
        require(hp("beam_rotated") == 96, "Beam rotates with ship");
        player.setWeapon(WEAPON_CANNON);
        require(!player.isLaserActive() && player.consumeLaserTicks() == 0, "Switch removes beam and pending damage");

        clearWorld(game);
        enemy("cannon_first", {0, -20}); enemy("cannon_second", {0, -40});
        projectile(PROJECTILE_CANNON, {0, 0}, {0, -60}, 12);
        EquipmentTestAccess::resolve(game);
        require(hp("cannon_first") == 88 && hp("cannon_second") == 100, "Cannon hits nearest target despite crossing both");
        require(bm.getBullets().empty(), "Cannon consumed on impact");

        clearWorld(game);
        enemy("heavy_1", {0, -20}); enemy("heavy_2", {0, -40});
        enemy("heavy_3", {0, -60}); enemy("heavy_4", {0, -80});
        projectile(PROJECTILE_HEAVY, {0, 0}, {0, -100}, 40, 3);
        EquipmentTestAccess::resolve(game);
        require(hp("heavy_1") == 60 && hp("heavy_2") == 60 && hp("heavy_3") == 60 && hp("heavy_4") == 100,
            "Heavy pierces three distinct targets in travel order");
        clearWorld(game);
        enemy("pierce_once", {0, -20});
        projectile(PROJECTILE_HEAVY, {0, 0}, {0, -20}, 40, 3);
        EquipmentTestAccess::resolve(game); EquipmentTestAccess::resolve(game);
        require(hp("pierce_once") == 60, "Piercing projectile never repeats damage on same target");
        player.setWeapon(WEAPON_LASER);
        require(bm.getBullets().front().getDamage() == 40, "Existing projectile keeps its damage after build change");

        clearWorld(game);
        enemy("rocket_direct", {0, -20}, 30); enemy("rocket_nearby", {8, -20}, 100);
        enemy("rocket_outside", {40, -20}, 100);
        projectile(PROJECTILE_ROCKET, {0, 0}, {0, -30}, 30);
        EquipmentTestAccess::resolve(game);
        require(hp("rocket_direct") == 0 && hp("rocket_nearby") == 70 && hp("rocket_outside") == 100, "Rocket impact and splash damage once each");
        require(player.getScore() == Balance::LOW_SCORE && game.killCounter.getCount() == 1, "Equipment kills award score and count once");
        require(player.getTotalDamageDealt() == 60, "Damage accounting excludes extra direct rocket hit");
        require(bm.getBullets().empty() && player.blasts.size() == 1, "Rocket removed and explosion visible");
        EquipmentTestAccess::updateEquipment(player, Theme::EXPLOSION_TIME, false);
        require(player.blasts.empty(), "Explosion expires in simulation time");

        clearWorld(game);
        auto asteroid = std::make_unique<Asteroid>(Vector2{});
        asteroid->position = {0, -20}; asteroid->velocity = {};
        const std::string asteroidId = asteroid->getAsteroidID();
        testAsteroidManager().getAsteroids()[asteroidId] = std::move(asteroid);
        player.setWeapon(WEAPON_LASER); EquipmentTestAccess::updateWeapon(player, 0.0f, true); EquipmentTestAccess::resolve(game);
        require(testAsteroidManager().getAsteroids().empty() && player.getScore() == Balance::DEBRIS_SCORE, "Laser destroys debris and awards score");

        clearWorld(game);
        player.setShield(SHIELD_FRONT);
        require(player.tryBlockHit({0, -20}) && !player.tryBlockHit({0, 20}), "Front shield coverage");
        near(player.getShieldCharge(), 20, "Shield consumes capacity per hit");
        player.takeDamage(0, {0, 20}, 1);
        require(player.getHealth() == 90, "Unprotected rear takes hull damage");
        player.setShield(SHIELD_SIDES);
        require(player.tryBlockHit({20, 0}) && !player.tryBlockHit({0, 20}), "Side shield half-circle");
        player.setShield(SHIELD_FRONT); player.rotation = 90.0f;
        require(player.tryBlockHit({20, 0}) && !player.tryBlockHit({-20, 0}), "Directional shield rotates");
        player.setShield(SHIELD_ROUND);
        for (int hit = 0; hit < 5; ++hit) require(player.tryBlockHit({0, 20}), "Round shield blocks every direction");
        require(!player.tryBlockHit({0, 20}), "Depleted shield cannot block");
        EquipmentTestAccess::updateEquipment(player, 2.0f, false); near(player.getShieldCharge(), 0, "Shield regeneration delay");
        EquipmentTestAccess::updateEquipment(player, 2.0f, false); near(player.getShieldCharge(), 10, "Shield regenerates only time after delay");
        EquipmentTestAccess::updateEquipment(player, 10.0f, false); near(player.getShieldCharge(), 50, "Shield regeneration capped");
        player.setShield(SHIELD_INVINCIBILITY);
        require(!player.tryBlockHit({0, 20}), "Guard inactive until skill press");
        EquipmentTestAccess::updateEquipment(player, 0.0f, true);
        require(player.tryBlockHit({0, 20}), "Guard skill blocks hits");
        EquipmentTestAccess::updateEquipment(player, Balance::INVINCIBILITY_DURATION, false);
        require(!player.tryBlockHit({0, 20}), "Guard ends at duration");
        EquipmentTestAccess::updateEquipment(player, 0.0f, true);
        require(!player.tryBlockHit({0, 20}), "Guard respects cooldown");
        EquipmentTestAccess::updateEquipment(player, Balance::INVINCIBILITY_COOLDOWN, true);
        require(player.tryBlockHit({0, 20}), "Guard becomes reusable");
        player.setEngine(ENGINE_BURST); EquipmentTestAccess::updateEquipment(player, 0.0f, true);
        near(player.boostTime, Balance::BOOST_DURATION, "Burst engine activates boost");
        EquipmentTestAccess::updateEquipment(player, Balance::BOOST_DURATION, true);
        near(player.boostTime, 0, "Boost cannot reactivate during cooldown");

        // All projectile weapons support scatter/burst; presets preserve earned augments and health.
        for (PlayerWeapon weapon : {WEAPON_CANNON, WEAPON_ROCKETS, WEAPON_HEAVY}) {
            clearWorld(game); player.setWeapon(weapon);
            player.increaseScatterShot(); player.increaseTriggerHappyBurst();
            EquipmentTestAccess::updateWeapon(player, 0.0f, true); require(bm.getBullets().size() == 2, "Scatter produces two shots");
            EquipmentTestAccess::updateWeapon(player, Balance::BURST_DELAY, false); require(bm.getBullets().size() == 4, "Burst completes after release");
        }
        player.health = 42; player.setBuild(BUILD_DEFAULT);
        require(player.getHealth() == 42 && player.scatterCount == 2, "Build swap preserves HP and augments");

#ifdef GAME_DEBUG
        DebugTools debug;
        const auto command = [&](const std::string& text) { debug.input = text; EquipmentTestAccess::execute(debug, &player); };
        for (const auto& preset : std::vector<std::pair<std::string, PlayerWeapon>>{
            {"default", WEAPON_CANNON}, {"cannon", WEAPON_CANNON}, {"laser", WEAPON_LASER},
            {"rockets", WEAPON_ROCKETS}, {"heavy", WEAPON_HEAVY}}) {
            command("player " + preset.first + " build"); require(player.getWeapon() == preset.second, "Preset debug command");
        }
        command("player engine supercharged"); require(player.getEngine() == ENGINE_SUPERCHARGED, "Engine debug command");
        command("player shield round"); require(player.getShield() == SHIELD_ROUND, "Shield debug command");
        command("player weapon laser"); require(player.getWeapon() == WEAPON_LASER, "Weapon debug command");
        command("player weapon cannon extra"); require(player.getWeapon() == WEAPON_LASER, "Reject trailing tokens");
        command("player unknown build"); require(player.getWeapon() == WEAPON_LASER, "Reject unknown preset");
        debug.input = "player l"; EquipmentTestAccess::complete(debug); require(debug.input == "player laser build", "Preset autocomplete");
        debug.input = "player shield r"; EquipmentTestAccess::complete(debug); require(debug.input == "player shield round", "Shield autocomplete");
        debug.input = "player default build"; EquipmentTestAccess::execute(debug, nullptr);
        require(player.getWeapon() == WEAPON_LASER, "Commands reject missing run");
        player.health = 0; command("player default build");
        require(player.getWeapon() == WEAPON_LASER, "Build commands cannot revive player");
        player.health = 100;
        // Exercise actual F5/character/Enter/closing input routing, not just parser calls.
#ifdef _WIN32
        PostMessageA(GetWindowHandle(), 0x100, 0x74, 0); PollInputEvents();
        game.updateDebugConsole(true);
        require(game.debugTools.capturesInput(), "F5 captures gameplay input");
        PostMessageA(GetWindowHandle(), 0x101, 0x74, 0); PollInputEvents(); game.updateDebugConsole(true);
        for (const char character : std::string("player laser build")) PostMessageA(GetWindowHandle(), 0x102, character, 0);
        PostMessageA(GetWindowHandle(), 0x100, 0x0d, 0); PollInputEvents(); game.updateDebugConsole(true);
        require(player.getWeapon() == WEAPON_LASER, "Native console equips laser");
        player.shotCooldown = 0.4f; player.boostCooldown = 2.0f;
        game.update();
        near(player.shotCooldown, 0.4f, "Console pauses attack timer");
        near(player.boostCooldown, 2.0f, "Console pauses ability cooldown");
        PostMessageA(GetWindowHandle(), 0x101, 0x0d, 0); PollInputEvents();
        PostMessageA(GetWindowHandle(), 0x100, 0x74, 0); PollInputEvents(); game.updateDebugConsole(true);
        PostMessageA(GetWindowHandle(), 0x101, 0x74, 0); PollInputEvents(); game.updateDebugConsole(true);
#endif
#endif
        clearWorld(game);
        player.setBuild(BUILD_LASER); EquipmentTestAccess::updateWeapon(player, 0.0f, true);
        player.boostCooldown = 2.0f; player.shieldDelay = 1.0f;
        game.gameState = GAME_PAUSED; game.update();
        near(player.boostCooldown, 2.0f, "Pause freezes skill timer");
        near(player.shieldDelay, 1.0f, "Pause freezes shield recharge");
        player.addBlast({0, 0});
        EquipmentTestAccess::restart(game);
        require(player.getWeapon() == WEAPON_CANNON && player.getEngine() == ENGINE_BASE && player.getShield() == SHIELD_NONE,
            "Restart restores default equipment");
        require(!player.isLaserActive() && player.consumeLaserTicks() == 0 && player.blasts.empty() && bm.getBullets().empty(),
            "Restart clears attacks and effects");
        near(player.boostCooldown, 0, "Restart clears cooldowns");
        player.setBuild(BUILD_HEAVY); game.onSwitch();
        require(player.getWeapon() == WEAPON_CANNON && player.getShield() == SHIELD_NONE, "New run resets build");

#ifdef _WIN32
        SetTargetFPS(120);
        PostMessageA(GetWindowHandle(), 0x100, 0x57, 0); PollInputEvents();
        for (PlayerEngine engine : {ENGINE_BASE, ENGINE_PULSE, ENGINE_BURST, ENGINE_SUPERCHARGED}) {
            player.init(); player.setEngine(engine); player.rotationSpeedMultiplier = 0.0f;
            for (int frame = 0; frame < 120; ++frame) {
                BeginDrawing(); EndDrawing(); player.update();
            }
            near(Vector2Length(player.getVelocity()), Balance::PLAYER_SPEED * Balance::ENGINE_SPEED[engine],
                "Native movement reaches selected engine speed");
            require(player.getPosition().y < Balance::PLAYER_SPAWN.y, "Native WASD moves player");
        }
        PostMessageA(GetWindowHandle(), 0x101, 0x57, 0); PollInputEvents();
        SetTargetFPS(0);
#endif

        clearWorld(game);
        player.setBuild(BUILD_LASER);
        player.rotationSpeedMultiplier = 0.0f;
        player.autoShoot = true;
        enemy("live_beam", {0, -30});
        EnemyManager::GetInstance().enemySpawnCooldown.startCooldown();
        testAsteroidManager().asteroidSpawnCooldown.startCooldown();
        game.update();
        require(hp("live_beam") < 100 && player.isLaserActive(), "Game update fires and resolves the equipped laser");

        clearWorld(game);
        player.setShield(SHIELD_FRONT);
        player.rotationSpeedMultiplier = 0.0f;
        Bullet incoming({0, -6}, {0, 1}, true);
        incoming.setBulletSpeed(0);
        bm.addBullet(incoming);
        EnemyManager::GetInstance().enemySpawnCooldown.startCooldown();
        testAsteroidManager().asteroidSpawnCooldown.startCooldown();
        game.update();
        require(bm.getBullets().empty() && player.getHealth() == 100, "Game intercepts enemy bullet before the hull");
        near(player.getShieldCharge(), 20, "Actual interception drains shield capacity once");

        clearWorld(game);
        player.setBuild(BUILD_LASER);
        EquipmentTestAccess::updateWeapon(player, 0.0f, true);
        player.setShield(SHIELD_NONE);
        player.health = Balance::PLAYER_CONTACT_DAMAGE;
        player.takeDamage(0, {0, 10}, 1);
        require(player.getPlayerState() == PLAYER_DEAD && !player.isLaserActive() && player.consumeLaserTicks() == 0,
            "Death cancels beam and damage ticks");

        clearWorld(game);
        player.setBuild(BUILD_LASER);
        player.position = {250, 250}; player.rotation = 45.0f;
        EquipmentTestAccess::updateWeapon(player, 0.0f, true);
        enemy("preview_target", Vector2Add(player.position, Vector2Scale(Vector2Rotate(Vector2{0, -1}, player.getRotation() * DEG2RAD), 55.0f)));
        utils::gameCamera = {{1920, 1080}, player.position, 0, 20};
        game.gameState = GAME_PAUSED;
#ifdef GAME_DEBUG
        game.debugTools.overlayVisible = true;
#endif
        const auto gameplay = LoadRenderTexture(3840, 2160);
        BeginTextureMode(gameplay); ClearBackground(BLACK); game.draw(); EndTextureMode();
        Image gameplayCapture = LoadImageFromTexture(gameplay.texture); ImageFlipVertical(&gameplayCapture);
        require(ExportImage(gameplayCapture, (artifactDirectory + "/player-laser-gameplay.png").c_str()), "Export gameplay and beam hitbox preview");
        UnloadImage(gameplayCapture); UnloadRenderTexture(gameplay);

        // Export a native render contact sheet for inspection of every preset and hull state.
        const auto target = LoadRenderTexture(1600, 1000);
        BeginTextureMode(target); ClearBackground(Color{18, 22, 32, 255});
        for (int index = 0; index < 5; ++index) {
            player.setBuild(static_cast<PlayerBuild>(index));
            for (int row = 0; row < 4; ++row) {
                player.health = 100 - row * 25;
                player.position = {static_cast<float>(160 + index * 320), static_cast<float>(130 + row * 240)};
                player.rotation = row == 1 ? 45.0f : row == 2 ? 90.0f : 0.0f;
                player.playerAccelerating = row % 2 == 0;
                player.animationTime = 0.2f;
                player.invincibilityTime = 1.0f;
                Camera2D camera = {{0, 0}, {0, 0}, 0, 10};
                player.position = Vector2Scale(player.position, 0.1f);
                BeginMode2D(camera); player.draw(); EndMode2D();
            }
            DrawText(TextFormat("PRESET %d", index), 70 + index * 320, 15, 24, WHITE);
        }
        EndTextureMode();
        Image capture = LoadImageFromTexture(target.texture); ImageFlipVertical(&capture);
        require(ExportImage(capture, (artifactDirectory + "/player-equipment-preview.png").c_str()), "Export render preview");
        UnloadImage(capture); UnloadRenderTexture(target);
        std::cout << "PASS: " << checks << " equipment checks\n";
    } catch (const std::exception& error) {
        std::cerr << "FAIL after " << checks << " checks: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
