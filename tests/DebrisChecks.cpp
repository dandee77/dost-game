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
        EnemyManager::GetInstance().spawnCredit = 0;
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
    std::array<std::vector<Vector2>, DEBRIS_KIND_COUNT> sheetCenters;
    std::unordered_set<std::size_t> sheetSignatures;
    // Read actual art independently, then verify each sheet and its saved handoff.
    for (int type = 0; type < DEBRIS_KIND_COUNT; ++type) {
        const auto kind = static_cast<DebrisKind>(type);
        Image sheetImage = LoadImageFromTexture(ResourceManager::GetInstance().GetTextureRef(DEBRIS_INFO[type].destructTexture));
        require(sheetImage.width == 768 && sheetImage.height == 96 &&
            sheetImage.format == PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, "Destruction remains eight RGBA frames");
        const auto* pixels = static_cast<const Color*>(sheetImage.data);
        std::array<bool, 96 * 96> visited = {};
        auto& centers = sheetCenters[type];
        for (int y = 0; y < 96; ++y) for (int x = 0; x < 96; ++x) {
            const int start = y * 96 + x;
            if (visited[start] || pixels[y * 768 + 6 * 96 + x].a == 0) continue;
            std::vector<int> pending = {start}; visited[start] = true;
            Vector2 sum = {}; int count = 0;
            while (!pending.empty()) {
                const int point = pending.back(); pending.pop_back();
                const int px = point % 96, py = point / 96;
                sum.x += px + 0.5f; sum.y += py + 0.5f; ++count;
                for (int dy = -1; dy <= 1; ++dy) for (int dx = -1; dx <= 1; ++dx) {
                    const int nx = px + dx, ny = py + dy;
                    if (nx < 0 || nx >= 96 || ny < 0 || ny >= 96) continue;
                    const int next = ny * 96 + nx;
                    if (!visited[next] && pixels[ny * 768 + 6 * 96 + nx].a != 0) {
                        visited[next] = true; pending.push_back(next);
                    }
                }
            }
            centers.push_back(Vector2Scale(sum, 1.0f / count));
        }
        const auto exits = Theme::DEBRIS_SCRAP_VISUALS[type].exitPixels;
        require(!exits.empty(), "Every kind has its own saved particle positions");
        if (kind != DEBRIS_CLUMP)
            require(centers.size() == exits.size(), "Each new sheet has one orb per final fleck");
        for (const auto exit : exits)
            require(std::any_of(centers.begin(), centers.end(), [&](Vector2 center) {
                return Vector2Distance(center, exit) < 0.0001f;
            }), "Saved coordinate belongs to this variant's actual final flecks");
        const auto signature = std::hash<std::string>{}(std::string(static_cast<const char*>(sheetImage.data), 768 * 96 * 4));
        require(sheetSignatures.insert(signature).second, "Every debris kind has a different destruction sheet");
        bool blankEnd = true;
        for (int y = 0; y < 96; ++y) for (int x = 0; x < 96; ++x)
            blankEnd = blankEnd && pixels[y * 768 + 7 * 96 + x].a == 0;
        require(blankEnd, "Every destruction ends with a transparent frame");
        // Exercise actual rendering: every complete frame must match the preserved sheet.
        const auto frameRender = LoadRenderTexture(96, 96);
        for (int frame = 0; frame < 8; ++frame) {
            scraps.reset(); scraps.spawnDebris({48, 48}, 0, kind, 96, false);
            scraps.update((frame + 0.5f) * Theme::DEBRIS_DESTRUCT_FRAME_TIME, {});
            BeginTextureMode(frameRender); ClearBackground(BLANK); scraps.draw(); EndTextureMode();
            Image actual = LoadImageFromTexture(frameRender.texture); ImageFlipVertical(&actual);
            require(actual.format == PIXELFORMAT_UNCOMPRESSED_R8G8B8A8, "Capture has readable RGBA pixels");
            const auto* rendered = static_cast<const Color*>(actual.data);
            bool same = true;
            for (int y = 0; y < 96; ++y) for (int x = 0; x < 96; ++x) {
                const auto expected = pixels[y * 768 + frame * 96 + x], found = rendered[y * 96 + x];
                same = same && expected.a == found.a && (expected.a == 0 ||
                    (expected.r == found.r && expected.g == found.g && expected.b == found.b));
            }
            require(same, "Whole destruction frame renders unchanged, including blank terminal frame");
            UnloadImage(actual);
        }
        UnloadRenderTexture(frameRender); UnloadImage(sheetImage);
    }
    Image orb = LoadImage("assets/textures/scrap_orb.png");
    require(orb.width == 96 && orb.height == 96 && orb.format == PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,
        "Generated orb loads as a 96px RGBA asset");
    const auto* glowPixels = static_cast<const Color*>(orb.data);
    std::array<bool, 256> alphaLevels = {};
    for (int i = 0; i < 96 * 96; ++i) alphaLevels[glowPixels[i].a] = true;
    require(glowPixels[0].a == 0 && std::count(alphaLevels.begin(), alphaLevels.end(), true) > 100,
        "Glow texture has transparent margins and a continuous soft alpha halo");
    UnloadImage(orb);

    const auto centers = Theme::DEBRIS_SCRAP_VISUALS[DEBRIS_WING].exitPixels;
    for (const float angle : {0.0f, 33.0f, 90.0f, 245.0f}) {
        clear();
        scraps.spawnDebris({12, -9}, angle, DEBRIS_WING, 48, true);
        require(scraps.update(Theme::SCRAP_HANDOFF_TIME - 0.001f, {500, 0}).trade == 0 && scraps.count() == 0,
            "Last visible frame finishes before any orb appears");
        scraps.update(0.001f, {500, 0});
        require(scraps.count() == centers.size(), "One orb replaces every final fleck");
        for (std::size_t i = 0; i < centers.size(); ++i) {
            const auto local = Vector2Scale(Vector2Subtract(centers[i], {48, 48}), 0.5f);
            const auto expected = Vector2Add({12, -9}, Vector2Rotate(local, angle * DEG2RAD));
            require(Vector2Distance(scraps.getPickups()[i]->getPosition(), expected) < 0.0001f,
                "Orb starts at rotated/scaled destruction pixel coordinate");
        }
        scraps.update(0.05f, {500, 0});
        require(scraps.count() == centers.size(), "Handoff runs only once");
    }

    clear(); scraps.spawnDebris({}, 33, DEBRIS_WING, 48, true);
    scraps.update(0.9f, {500, 0});
    std::vector<Vector2> largeStep;
    for (const auto& pickup : scraps.getPickups()) largeStep.push_back(pickup->getPosition());
    clear(); scraps.spawnDebris({}, 33, DEBRIS_WING, 48, true);
    for (int i = 0; i < 90; ++i) scraps.update(0.01f, {500, 0});
    require(scraps.count() == largeStep.size(), "Crossing animation boundary creates identical pickups");
    for (std::size_t i = 0; i < largeStep.size(); ++i)
        require(Vector2Distance(scraps.getPickups()[i]->getPosition(), largeStep[i]) < 0.001f,
            "Handoff carries only residual frame time into homing");
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
        require(scraps.count() == 0 && scraps.destructionCount() == 1, "Destruction sheet plays before pickups spawn");
        require(scraps.pendingValue() == Balance::DEBRIS_SCRAP_VALUES[type], "Breakup preserves exact variant value");
        require(!debris.removeDebris(id, true), "Repeated destruction is harmless");
        require(scraps.update(Theme::SCRAP_HANDOFF_TIME, {}).trade == 0, "No credit before absorption");
        const float expectedSizes[] = {1.25f, 1.25f, 2.5f, 1.25f, 1.8f, 1.25f, 2.5f, 1.8f, 2.5f, 2.5f};
        require(scraps.count() == Theme::DEBRIS_SCRAP_VISUALS[type].exitPixels.size(), "Every variant uses its own saved particle count");
        std::vector<Vector2> seenPositions;
        for (const auto& pickup : scraps.getPickups()) {
            require(pickup->getSize().x == expectedSizes[type], "Orb diameter follows debris size tier");
            const auto local = Vector2Add(Vector2Scale(Vector2Subtract(pickup->getPosition(), {30, 0}),
                96.0f / Theme::DEBRIS_DRAW_SIZES[type]), {48, 48});
            require(std::any_of(sheetCenters[type].begin(), sheetCenters[type].end(), [&](Vector2 center) {
                return Vector2Distance(center, local) < 0.001f;
            }), "Reduced burst still spawns at an actual saved explosion fleck");
            require(std::none_of(seenPositions.begin(), seenPositions.end(), [&](Vector2 previous) {
                return Vector2Distance(previous, local) < 0.001f;
            }), "Reduced burst does not duplicate an exit");
            seenPositions.push_back(local);
        }
        require(scraps.pendingValue() == Balance::DEBRIS_SCRAP_VALUES[type], "Fewer visual orbs preserve full scrap yield");
        int total = 0;
        for (int frame = 0; frame < 180; ++frame) total += scraps.update(1.0f / 60.0f, {}).trade;
        require(total == Balance::DEBRIS_SCRAP_VALUES[type] && scraps.count() == 0, "All shards home and credit exactly once");
        require(scraps.update(1.0f, {}).trade == 0, "No duplicate collection");
    }
    require(Theme::DEBRIS_DRAW_SIZES[DEBRIS_WING] > Theme::DEBRIS_DRAW_SIZES[DEBRIS_PIPE], "Satellite wing is larger than small junk");
    clear();
    debris.removeDebris(spawn(DEBRIS_WING, {30, 0}), false);
    require(scraps.pendingValue() == 0 && scraps.update(1, {}).trade == 0 && scraps.count() == 0, "Environmental breakup fades without rewards");
    clear();
    spawn(DEBRIS_WING, {1000, 0});
    debris.update({}, game.gameTimer);
    require(debris.getDebris().empty() && scraps.count() == 0, "Offscreen cleanup produces no fragments or rewards");

    // Homing agrees across frame rates and cannot overshoot.
    ScrapPickup single({}, 1, Theme::SCRAP_ORB_SIZE);
    ScrapPickup many({}, 1, Theme::SCRAP_ORB_SIZE);
    single.advance(0.8f, {500, 0});
    for (int i = 0; i < 80; ++i) many.advance(0.01f, {500, 0});
    require(Vector2Distance(single.getPosition(), many.getPosition()) < 0.001f, "Homing agrees across frame rates");
    const auto endpoint = single.getPosition();
    single.advance(0, {500, 0});
    require(Vector2Distance(endpoint, single.getPosition()) == 0, "Zero dt freezes pickup");
    single.advance(0.001f, {500, 0});
    require(Vector2Distance(endpoint, single.getPosition()) <= Balance::SCRAP_MAGNET_SPEED * 0.001f + 0.001f, "Homing movement follows configured speed");
    single.advance(10, {});
    require(single.isCollected() && Vector2Length(single.getPosition()) == 0, "Large frame cannot overshoot player");
    clear();
    for (int i = 0; i < 200; ++i) scraps.spawnDebris({30, 0}, 0, DEBRIS_WING, 48, true);
    require(scraps.count() == 0 && scraps.destructionCount() == 200, "Mass kills preserve the destruction animations");
    scraps.update(Theme::SCRAP_HANDOFF_TIME, {});
    require(scraps.count() <= Balance::SCRAP_MAX_PICKUPS, "Pickup cap bounds render workload");
    require(scraps.pendingValue() == 200 * Balance::DEBRIS_SCRAP_VALUES[DEBRIS_WING], "Overflow merges all earned value");
    int massCollected = 0;
    for (int i = 0; i < 180; ++i) massCollected += scraps.update(1.0f / 60.0f, {}).trade;
    require(massCollected == 1600, "Merged pickup value is collected without cargo cap");
    clear();
    const int wingCount = static_cast<int>(Theme::DEBRIS_SCRAP_VISUALS[DEBRIS_WING].exitPixels.size());
    const int wingBursts = (Balance::SCRAP_MAX_PICKUPS - 8) / wingCount;
    for (int i = 0; i < wingBursts; ++i) scraps.spawnDebris({30, 0}, 0, DEBRIS_WING, 48, true);
    for (int i = 0; i < 8; ++i) scraps.spawnDebris({30, 0}, 0, DEBRIS_CLUMP, 20, true);
    scraps.update(Theme::SCRAP_HANDOFF_TIME, {});
    require(scraps.count() <= Balance::SCRAP_MAX_PICKUPS && scraps.count() > wingBursts * wingCount &&
        scraps.pendingValue() == wingBursts * 8 + 24,
        "Small bursts fit remaining cap slots; overflow preserves their value");
    int mixedCollected = 0;
    for (int i = 0; i < 180; ++i) mixedCollected += scraps.update(1.0f / 60.0f, {}).trade;
    require(mixedCollected == wingBursts * 8 + 24, "Mixed-size overflow credits the complete reward");
    clear();
    game.progress.wallet = 100;
    scraps.spawnDebris({}, 0, DEBRIS_WING, 48, true);
    require(scraps.update(Theme::SCRAP_HANDOFF_TIME, {}).trade == 0, "Breakup reaches pickup phase without early credit");
    SetTargetFPS(60);
    for (int frame = 0; frame < 30; ++frame) { BeginDrawing(); EndDrawing(); game.update(); }
    SetTargetFPS(0);
    require(game.progress.wallet == 108 && scraps.count() == 0, "Live Game updates counter beyond planned cargo cap");

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
    require(scraps.destructions.front().elapsed == 0 && scraps.count() == 0, "Pause freezes destruction and handoff");
    game.gameState = GAME_AUGMENT_SELECTION; game.update();
    require(scraps.destructions.front().elapsed == 0, "Augment choice freezes destruction");
#ifdef GAME_DEBUG
    game.debugTools.inputCaptured = true;
    game.gameState = GAME_RUNNING; game.update();
    require(scraps.destructions.front().elapsed == 0, "Debug console freezes destruction");
    game.debugTools.inputCaptured = false;
    game.debugTools.input = "spawn debris all";
    EquipmentTestAccess::execute(game.debugTools, &player, &game.barricadeEvent);
    require(debris.getDebris().size() == DEBRIS_KIND_COUNT, "Debug gallery spawns exactly ten types");
#endif
    scraps.update(Theme::SCRAP_HANDOFF_TIME, {});
    game.gameState = GAME_PAUSED; game.update();
    require(scraps.getPickups().front()->getElapsed() == 0, "Pause also freezes spawned glow orbs");
    game.progress.wallet = 123;
    EquipmentTestAccess::restart(game);
    require(scraps.count() == 0 && scraps.destructionCount() == 0 && game.progress.wallet == 0, "Restart clears explosions, particles and balance");
    scraps.spawnDebris({30, 0}, 0, DEBRIS_CLUMP, 20, true);
    game.progress.wallet = 321; game.onExit();
    require(scraps.count() == 0 && scraps.destructionCount() == 0 && game.progress.wallet == 0, "Scene exit clears harvesting state");
    clear();
    scraps.spawnDebris({30, 0}, 0, DEBRIS_CLUMP, 20, true);
    game.progress.wallet = 321; game.gameState = GAME_OVER; game.update();
    require(scraps.count() == 0 && scraps.destructionCount() == 0 && game.progress.wallet == 0, "Death loses harvested scrap and cancels effects");

    // Native renderer: actual fixed-size variants and continuous pickup phases.
    const auto render = LoadRenderTexture(1600, 1200);
    BeginTextureMode(render); ClearBackground(Color{18, 14, 30, 255});
    for (int i = 0; i < DEBRIS_KIND_COUNT; ++i) {
        const int column = i % 5, row = i / 5;
        Camera2D camera = {{160.0f + column * 320, 160.0f + row * 280}, {}, 0, 9};
        Debris item({}, static_cast<DebrisKind>(i)); item.position = {}; item.rotation = 0;
        BeginMode2D(camera); item.draw(); EndMode2D();
        DrawText(DEBRIS_INFO[i].name, 45 + column * 320, 260 + row * 280, 20, WHITE);
    }
    const char* stages[] = {"DESTRUCTION", "LAST FLECKS", "GLOW HANDOFF", "ABSORB"};
    const float times[] = {3.5f * Theme::DEBRIS_DESTRUCT_FRAME_TIME,
        (Theme::DEBRIS_LAST_VISIBLE_FRAME + 0.5f) * Theme::DEBRIS_DESTRUCT_FRAME_TIME,
        Theme::SCRAP_HANDOFF_TIME, Theme::SCRAP_HANDOFF_TIME + Theme::SCRAP_ORB_HOLD_TIME + 0.1f};
    for (int phase = 0; phase < 4; ++phase) {
        scraps.reset();
        scraps.spawnDebris({}, 0, DEBRIS_WING, 48, true);
        scraps.update(times[phase], {35, 0});
        Camera2D camera = {{120.0f + phase * 400, 710}, {}, 0, 5};
        BeginMode2D(camera); scraps.draw(); EndMode2D();
        DrawText(stages[phase], 65 + phase * 400, 830, 22, Theme::COLOR_HARVEST);
    }
    const DebrisKind tierKinds[] = {DEBRIS_PIPE, DEBRIS_DISH, DEBRIS_WING};
    const char* tierLabels[] = {"PIPE", "DISH", "WING"};
    for (int tier = 0; tier < 3; ++tier) {
        scraps.reset();
        const auto kind = tierKinds[tier];
        scraps.spawnDebris({}, 0, kind, Theme::DEBRIS_DRAW_SIZES[kind], true);
        scraps.update(Theme::SCRAP_HANDOFF_TIME, {100, 0});
        Camera2D camera = {{260.0f + tier * 530, 1040}, {}, 0, 5};
        BeginMode2D(camera); scraps.draw(); EndMode2D();
        DrawText(TextFormat("%s: %d ORBS", tierLabels[tier], static_cast<int>(scraps.count())),
            140 + tier * 530, 1140, 22, Theme::COLOR_HARVEST);
    }
    EndTextureMode();
    Image capture = LoadImageFromTexture(render.texture); ImageFlipVertical(&capture);
    require(ExportImage(capture, (artifactDirectory + "/debris-harvest-preview.png").c_str()), "Export native debris and harvest render");
    UnloadImage(capture); UnloadRenderTexture(render);
    const auto sheetPreview = LoadRenderTexture(1440, 1320);
    BeginTextureMode(sheetPreview); ClearBackground(Color{18, 14, 30, 255});
    DrawText("DEBRIS / EIGHT DESTRUCTION FRAMES / GLOW HANDOFF", 20, 20, 24, WHITE);
    for (int type = 0; type < DEBRIS_KIND_COUNT; ++type) {
        const auto kind = static_cast<DebrisKind>(type);
        const float y = 120.0f + type * 120;
        DrawText(DEBRIS_INFO[type].name, 12, static_cast<int>(y), 16, WHITE);
        for (int frame = 0; frame < 9; ++frame) {
            scraps.reset(); scraps.spawnDebris({}, 0, kind, 96, frame == 8);
            scraps.update(frame == 8 ? Theme::SCRAP_HANDOFF_TIME :
                (frame + 0.5f) * Theme::DEBRIS_DESTRUCT_FRAME_TIME, {500, 0});
            Camera2D camera = {{250.0f + frame * 128, y}, {}, 0, 1.25f};
            BeginMode2D(camera); scraps.draw(); EndMode2D();
        }
    }
    EndTextureMode();
    Image allSheets = LoadImageFromTexture(sheetPreview.texture); ImageFlipVertical(&allSheets);
    require(ExportImage(allSheets, (artifactDirectory + "/debris-destruction-preview.png").c_str()),
        "Export every unique destruction and its glow handoff");
    UnloadImage(allSheets); UnloadRenderTexture(sheetPreview);
    game.onExit();
    std::cout << "Debris: " << checks << " checks\n";
    return checks;
}
