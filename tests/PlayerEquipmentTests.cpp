#include "TestAccess.hpp"
#include "EquipmentAccess.hpp"
#include "Balance.hpp"
#include "Theme.hpp"
#include "raymath.h"
#include <stdexcept>
int runCrowdChecks(const std::string& artifactDirectory);

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
        clearWorld(game);
        require(player.getWeapon() == WEAPON_DEFAULT, "Original ship is the initial default");
        player.shotCooldown = 0.0f;
        EquipmentTestAccess::updateWeapon(player, 0.0f, true);
        require(bm.getBullets().size() == 1 && bm.getBullets().front().getKind() == PROJECTILE_LEGACY,
            "Default fires the original bullet and collision behavior");
        near(Vector2Distance(bm.getBullets().front().getPosition(), player.getPosition()), 0.0f,
            "Original bullet spawns at the original ship position");
        bm.reset();
        player.setBuild(BUILD_GUNNER);
        require(player.getWeapon() == WEAPON_CANNON && player.getEngine() == ENGINE_BASE && player.getShield() == SHIELD_NONE,
            "Gunner preserves the modular base loadout");
        EquipmentTestAccess::updateWeapon(player, 0.0f, true);
        require(bm.getBullets().front().getKind() == PROJECTILE_CANNON, "Gunner fires modular cannon shots");
        player.setBuild(BUILD_DEFAULT);
        require(player.getWeapon() == WEAPON_DEFAULT && !player.isLaserActive(), "Default command restores original ship");

        // Presets must remove both passive shields and an already active guard skill.
        for (PlayerBuild build : {BUILD_DEFAULT, BUILD_GUNNER, BUILD_CANNON, BUILD_LASER, BUILD_ROCKETS, BUILD_HEAVY}) {
            for (PlayerShield shield : {SHIELD_ROUND, SHIELD_INVINCIBILITY}) {
                player.setShield(shield);
                EquipmentTestAccess::updateEquipment(player, 0.0f, true);
                require(player.tryBlockHit({0, -20}), "Explicit shield protects before preset change");
                player.setBuild(build);
                require(player.getShield() == SHIELD_NONE && player.getShieldCharge() == 0.0f,
                    "Every preset clears equipped shield and charge");
                require(player.invincibilityTime == 0.0f && player.invincibilityCooldown == 0.0f && player.shieldDelay == 0.0f,
                    "Preset clears shield skill and recharge timers");
                EquipmentTestAccess::updateEquipment(player, 1.0f, true);
                require(!player.tryBlockHit({0, -20}) && !player.tryBlockHit({0, 20}),
                    "Preset has no protection after regeneration time or skill press");
            }
        }
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
        clearWorld(game);
        auto& spawnManager = EnemyManager::GetInstance();
        for (const std::string text : {"spawn", "spawn lowlevel enemy", "spawn lowlevel enemy 0",
            "spawn lowlevel enemy -1", "spawn lowlevel enemy 1.5", "spawn lowlevel enemy 2000oops",
            "spawn lowlevel enemy 99999999999999999999999", "spawn lowlevel enemy 10001",
            "spawn midlevel enemy 2", "spawn lowlevel enemy 2 extra"}) {
            command(text);
            require(spawnManager.getEnemies().empty(), "Invalid spawn command has no side effects");
        }
        debug.input = "spawn lowlevel enemy 2000"; EquipmentTestAccess::execute(debug, nullptr);
        require(spawnManager.getEnemies().empty(), "Spawn rejects missing run");
        player.health = 0; command("spawn lowlevel enemy 2000");
        require(spawnManager.getEnemies().empty(), "Spawn rejects dead player");
        player.health = Balance::PLAYER_MAX_HEALTH;
        debug.input = "spa"; EquipmentTestAccess::complete(debug);
        require(debug.input == "spawn", "Spawn command autocomplete");
        debug.input = "spawn l"; EquipmentTestAccess::complete(debug);
        require(debug.input == "spawn lowlevel enemy ", "Spawn argument autocomplete leaves quantity editable");
        command("spawn lowlevel enemy 2000");
        require(spawnManager.getEnemies().size() == 2000, "Spawn creates requested 2000 real enemies");
        bool validSpawns = true;
        for (const auto& [id, value] : spawnManager.getEnemies()) {
            validSpawns = validSpawns && value->getEnemyType() == LOW_LEVEL_ENEMY && value->getHealth() > 0 &&
                std::isfinite(value->getRotation()) && Animator::GetInstance().animations.at(id).isActive &&
                std::abs(Vector2Distance(value->getPosition(), player.getPosition()) - Balance::ENEMY_SPAWN_RADIUS) < 0.001f;
        }
        require(validSpawns, "Spawned enemies are alive, animated and on the spawn ring");
        command("spawn lowlevel enemy 2000");
        require(spawnManager.getEnemies().size() == 4000, "Repeated spawn uses unique IDs");
        command("spawn lowlevel enemy 10000");
        require(spawnManager.getEnemies().size() == Balance::ENEMY_LIMIT, "Spawn clamps to available enemy capacity");
        require(debug.output.back() == "Enemy limit reached: 10000.", "Partial spawn reports capacity limit");
        command("spawn lowlevel enemy 1");
        require(spawnManager.getEnemies().size() == Balance::ENEMY_LIMIT, "Full capacity rejects further spawns");
        EquipmentTestAccess::restart(game);
        require(spawnManager.getEnemies().empty() && spawnManager.enemyCounter == 0, "Restart clears debug-spawned enemies and IDs");
        command("spawn lowlevel enemy 1");
        require(spawnManager.getEnemies().contains("enemy_0"), "Spawn works after restart");
        EquipmentTestAccess::restart(game);
        for (const auto& preset : std::vector<std::pair<std::string, PlayerWeapon>>{
            {"default", WEAPON_DEFAULT}, {"gunner", WEAPON_CANNON}, {"cannon", WEAPON_CANNON}, {"laser", WEAPON_LASER},
            {"rockets", WEAPON_ROCKETS}, {"heavy", WEAPON_HEAVY}}) {
            command("player shield round");
            command("player " + preset.first + " build"); require(player.getWeapon() == preset.second, "Preset debug command");
            require(player.getShield() == SHIELD_NONE, "Preset command removes separately equipped shield");
        }
        command("player engine supercharged"); require(player.getEngine() == ENGINE_SUPERCHARGED, "Engine debug command");
        command("player shield round"); require(player.getShield() == SHIELD_ROUND, "Shield debug command");
        command("player weapon laser"); require(player.getWeapon() == WEAPON_LASER, "Weapon debug command");
        command("player weapon cannon extra"); require(player.getWeapon() == WEAPON_LASER, "Reject trailing tokens");
        command("player unknown build"); require(player.getWeapon() == WEAPON_LASER, "Reject unknown preset");
        debug.input = "player l"; EquipmentTestAccess::complete(debug); require(debug.input == "player laser build", "Preset autocomplete");
        debug.input = "player g"; EquipmentTestAccess::complete(debug); require(debug.input == "player gunner build", "Gunner autocomplete");
        debug.input = "player shield r"; EquipmentTestAccess::complete(debug); require(debug.input == "player shield round", "Shield autocomplete");
        debug.input = "player ";
        for (int index = 0; index < 19; ++index) EquipmentTestAccess::moveSuggestion(debug, 1);
        require(debug.selectedSuggestion == 18 && debug.suggestionOffset == 13, "Dropdown scroll reaches the last equipment command");
        EquipmentTestAccess::complete(debug);
        require(debug.input == "player shield invincibility" && debug.selectedSuggestion == -1, "Dropdown accepts last suggestion without executing");
        debug.input = "player shield ";
        EquipmentTestAccess::moveSuggestion(debug, -1);
        require(debug.selectedSuggestion == 4, "Dropdown wraps upward to last shield");
        EquipmentTestAccess::moveSuggestion(debug, -Theme::DEBUG_SUGGESTION_ROWS);
        require(debug.selectedSuggestion >= 0 && debug.selectedSuggestion < 5, "Page navigation handles short lists");
        debug.consoleVisible = true;
        const auto consoleTarget = LoadRenderTexture(3840, 2160);
        BeginTextureMode(consoleTarget); ClearBackground(Color{18, 22, 32, 255}); debug.drawConsole(); EndTextureMode();
        Image consoleCapture = LoadImageFromTexture(consoleTarget.texture); ImageFlipVertical(&consoleCapture);
        require(ExportImage(consoleCapture, (artifactDirectory + "/console-dropdown.png").c_str()), "Export dropdown preview");
        UnloadImage(consoleCapture); UnloadRenderTexture(consoleTarget);
        debug.reset();
        require(debug.selectedSuggestion == -1 && debug.suggestionOffset == 0, "Dropdown reset clears navigation state");
#ifdef _WIN32
        debug.consoleVisible = true;
        debug.input = "player shield ";
        PostMessageA(GetWindowHandle(), 0x100, 0x28, (1LL << 24) | (0x50LL << 16)); PollInputEvents(); debug.update(&player);
        require(debug.selectedSuggestion == 0, "Native Down selects first dropdown row");
        PostMessageA(GetWindowHandle(), 0x101, 0x28, (1LL << 31) | (1LL << 30) | (1LL << 24) | (0x50LL << 16)); PollInputEvents(); debug.update(&player);
        PostMessageA(GetWindowHandle(), 0x100, 0x0d, 0x1cLL << 16); PollInputEvents(); debug.update(&player);
        require(debug.input == "player shield none" && debug.selectedSuggestion == -1, "Native Enter fills selected command");
        PostMessageA(GetWindowHandle(), 0x101, 0x0d, (1LL << 31) | (1LL << 30) | (0x1cLL << 16)); PollInputEvents(); debug.update(&player);
        debug.reset();
#endif
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
        require(player.getWeapon() == WEAPON_DEFAULT && player.getEngine() == ENGINE_BASE && player.getShield() == SHIELD_NONE,
            "Restart restores default equipment");
        require(!player.isLaserActive() && player.consumeLaserTicks() == 0 && player.blasts.empty() && bm.getBullets().empty(),
            "Restart clears attacks and effects");
        near(player.boostCooldown, 0, "Restart clears cooldowns");
        player.setBuild(BUILD_HEAVY); game.onSwitch();
        require(player.getWeapon() == WEAPON_DEFAULT && player.getShield() == SHIELD_NONE, "New run resets build");

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
        const auto target = LoadRenderTexture(1920, 1000);
        BeginTextureMode(target); ClearBackground(Color{18, 22, 32, 255});
        const char* presetNames[] = {"DEFAULT", "CANNON", "LASER", "ROCKETS", "HEAVY", "GUNNER"};
        for (int index = 0; index < 6; ++index) {
            player.setBuild(static_cast<PlayerBuild>(index));
            for (int row = 0; row < 4; ++row) {
                player.health = 100 - row * 25;
                player.position = {static_cast<float>(160 + index * 320), static_cast<float>(130 + row * 240)};
                player.rotation = row == 1 ? 45.0f : row == 2 ? 90.0f : 0.0f;
                player.playerAccelerating = row % 2 == 0;
                player.animationTime = 0.2f;
                Camera2D camera = {{0, 0}, {0, 0}, 0, 10};
                player.position = Vector2Scale(player.position, 0.1f);
                BeginMode2D(camera); player.draw(); EndMode2D();
            }
            DrawText(presetNames[index], 70 + index * 320, 15, 24, WHITE);
        }
        EndTextureMode();
        Image capture = LoadImageFromTexture(target.texture); ImageFlipVertical(&capture);
        require(ExportImage(capture, (artifactDirectory + "/player-equipment-preview.png").c_str()), "Export render preview");
        UnloadImage(capture); UnloadRenderTexture(target);
        checks += runCrowdChecks(artifactDirectory);
        std::cout << "PASS: " << checks << " equipment, console and crowd checks\n";
    } catch (const std::exception& error) {
        std::cerr << "FAIL after " << checks << " checks: " << error.what() << '\n';
        return 1;
    }
    return 0;
}
