#include "Game.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include "Animator.hpp"
#include "Bullet.hpp"
#include "raymath.h" 
#include "BulletManager.hpp"
#include "Utils.hpp"
#include "DebrisManager.hpp"
#include <algorithm>
#include <unordered_set>
#include <memory>
#include "DamageIndicatorManager.hpp"
#include "ConfettiManager.hpp"
#include "ExplosionConfettiManager.hpp"
#include "GameOverOverlay.hpp"
#include "DamageOverlay.hpp"
#include "Balance.hpp"
#include "ScrapManager.hpp"
#include "Theme.hpp"


static bool CheckCollisions(Vector2 bulletPos, Vector2 shipPos, float shipSize) // circled hitbox so edit the draw hitbox
{
    return Vector2Distance(bulletPos, shipPos) <= shipSize;
}

// TODO: ENEMY PATTERN, STOP SPAWNING MOBS WHEN BOSS FIGJT
// TODO: GLITTERS WHEN AUGMENT SELECTION
// TODO: SPINNING COLORS ON THE RECTANGLE ON AUGMENTS BORDER]
// todo: cursor
static int prevGameTimer = 0;
static bool gameOverTextStarted = false;

Game::Game() 
{
    restartButton = nullptr;
    mainMenuButton = nullptr;
}

Game::~Game()
{
    skills.reset();
    barricadeEvent.reset();
    ScrapManager::GetInstance().reset();
    if (restartButton) delete restartButton;
    if (mainMenuButton) delete mainMenuButton;
}

void Game::resetRun()
{
    skills.reset();
    augmentRng.seed(Balance::SKILL_SEED);
    prevGameTimer = 0;
    barricadeEvent.reset();
    ScrapManager::GetInstance().reset();
    harvestedScrap = 0;
    enemyCollisionGrid.clear();
    debrisCollisionGrid.clear();
    collisionEnemies.clear();
    collisionDebris.clear();
    gameOverTextStarted = false;
    EnemyManager::GetInstance().reset();
    DebrisManager::GetInstance().reset();
    BulletManager::GetInstance().reset();
    DamageIndicatorManager::GetInstance().reset();
    ConfettiManager::GetInstance().reset();
    ExplosionConfettiManager::GetInstance().reset();
    GameOverOverlay::GetInstance().reset();
    DamageOverlay::GetInstance().reset();
}

void Game::onSwitch()
{
    resetRun();
#ifdef GAME_DEBUG
    debugTools.reset();
    debugPausedTimer = false;
#endif
    gameState = GAME_RUNNING;
    worldTileSize = 500.0f; 
    playerEntity = Player();
    playerEntity.init();
    utils::gameCamera = {};
    utils::gameCamera.target = { playerEntity.getPosition().x, playerEntity.getPosition().y };
    utils::gameCamera.offset = {GAME_SCREEN_WIDTH/2.0f, GAME_SCREEN_HEIGHT/2.0f};
    utils::gameCamera.rotation = 0.0f;
    utils::gameCamera.zoom = Config::CAMERA_ZOOM_INTRO;

    backgroundLayers = {
        {ResourceManager::GetInstance().GetTexture("background1"), 0.2f, worldTileSize},  // 0.2
        {ResourceManager::GetInstance().GetTexture("background3"), 0.4f, worldTileSize},  // 0.4
        {ResourceManager::GetInstance().GetTexture("background4"), 0.7f, worldTileSize},  // 0.7
        {ResourceManager::GetInstance().GetTexture("background2"), 1.0f, worldTileSize}   // 1.0
    };

    gameMusic = ResourceManager::GetInstance().GetMusic("game_music");
    PlayMusicStream(gameMusic);


    playerBulletTexture = ResourceManager::GetInstance().GetTexture("player_bullet");
    enemyBulletTexture = ResourceManager::GetInstance().GetTexture("enemy_bullet");

    killCounter = KillCounter();
    killCounter.reset();
    gameTimer = GameTimer();
    gameTimer.reset();
    gameTimer.start();

    //? setup control guides keyboard keys animations
    Animator::GetInstance().AddAnimation("wasd_keys_tutorial",std::make_shared<Animation>(
        ResourceManager::GetInstance().GetTextureRef("wasd_keys"),
        ResourceManager::GetInstance().GetTextureRef("wasd_keys").width / 3,
        ResourceManager::GetInstance().GetTextureRef("wasd_keys").height,
        0.5f,
        true,
        Rectangle{0, 0, 16, 10},
        false,
        WHITE
    ));

    Animator::GetInstance().AddAnimation("e_key_tutorial", std::make_shared<Animation>(
        ResourceManager::GetInstance().GetTextureRef("e_key"),
        ResourceManager::GetInstance().GetTextureRef("e_key").width / 3,
        ResourceManager::GetInstance().GetTextureRef("e_key").height,
        0.5f,
        true,
        Rectangle{0, 0, 5, 5},
        false,
        WHITE
    ));

    Animator::GetInstance().AddAnimation("game_over_text", std::make_shared<Animation>(
        ResourceManager::GetInstance().GetTextureRef("game_over_text"),
        ResourceManager::GetInstance().GetTextureRef("game_over_text").width / 10,
        ResourceManager::GetInstance().GetTextureRef("game_over_text").height,
        0.5f,
        true,
        Rectangle{0, 0, 1800, 300},
        false,
        WHITE
    ));

    Animator::GetInstance().Play("wasd_keys_tutorial");
    Animator::GetInstance().Play("e_key_tutorial");

    for (int i = 0; i < MAX_SOUND_INSTANCES; i++) {
        scoreSounds[i] = LoadSound("assets/sounds/score_sound.wav");
    }

    // Initialize game over buttons
    if (restartButton) delete restartButton;
    if (mainMenuButton) delete mainMenuButton;
    restartButton = new Button(Rectangle{GAME_SCREEN_WIDTH/2.0f - 400, 1600, 800, 120}, "RESTART", 120, BUTTON_CENTERED);
    mainMenuButton = new Button(Rectangle{GAME_SCREEN_WIDTH/2.0f - 400, 1780, 800, 120}, "MAIN MENU", 120, BUTTON_CENTERED);

    augmentCards.clear();
}


void Game::restartGame() { //ts kinda useless ngl
    resetRun();
#ifdef GAME_DEBUG
    debugTools.reset();
    debugPausedTimer = false;
#endif
    
    PlayMusicStream(gameMusic);
    
    
    Animator::GetInstance().StopAll();
    // Clean up the killer display animation if it exists
    Animator::GetInstance().Remove("killer_display");

    playerEntity.init();
    utils::gameCamera.zoom = Config::CAMERA_ZOOM_PLAY;
    utils::gameCamera.target = playerEntity.getPosition();
    
    killCounter.reset();
    gameTimer.reset();
    gameTimer.start();
    augmentCards.clear();
    
    Animator::GetInstance().Play("wasd_keys_tutorial");
    Animator::GetInstance().Play("e_key_tutorial");
    
    gameState = GAME_RUNNING;
}


bool Game::updateSkills(float dt, Vector2 aim, bool activateSelected)
{
    if (gameState != GAME_RUNNING) return false;
    const auto result = skills.update(dt, playerEntity, aim, activateSelected);
    for (const auto& hit : result.hits)
        damageEquipmentEnemy(hit.enemyId, hit.damage, {}, 0.0f, hit.dropsScrap);
    harvestedScrap += result.scrap;
    return result.teleported;
}

void Game::damageEquipmentEnemy(const std::string& id, int amount, Vector2 direction, float knockback, bool dropSkillScrap)
{
    auto& enemies = EnemyManager::GetInstance().getEnemies();
    const auto found = enemies.find(id);
    if (found == enemies.end()) return;
    auto& enemy = *found->second;
    const int dealt = std::min(amount, enemy.getHealth());
    enemy.takeDamage(amount);
    playerEntity.addDamageDealt(dealt);
    DamageIndicatorManager::GetInstance().addDamageIndicator(enemy.getPosition(), dealt, amount);
    if (knockback > 0.0f && enemy.canReceiveKnockback()) enemy.applyKnockback(direction, knockback);
    if (!enemy.isDead()) return;
    if (dropSkillScrap && enemy.getEnemyType() != BARRICADE_ENEMY)
        ScrapManager::GetInstance().spawnScrap(enemy.getPosition(), enemy.getEnemyType() == MID_LEVEL_ENEMY ?
            Balance::SKILL_MID_SCRAP : Balance::SKILL_LOW_SCRAP);
    killCounter.increment();
    playerEntity.addScore(enemy.getEnemyType() == LOW_LEVEL_ENEMY ? Balance::LOW_SCORE :
        enemy.getEnemyType() == MID_LEVEL_ENEMY ? Balance::MID_SCORE : Balance::DEBRIS_SCORE);
    for (const auto& sound : scoreSounds) {
        if (!IsSoundPlaying(sound)) { PlaySound(sound); break; }
    }
    EnemyManager::GetInstance().removeEnemy(id);
}

void Game::destroyEquipmentDebris(const std::string& id)
{
    auto& manager = DebrisManager::GetInstance();
    if (manager.getDebris().find(id) == manager.getDebris().end()) return;
    killCounter.increment();
    playerEntity.addScore(Balance::DEBRIS_SCORE);
    manager.removeDebris(id, true);
}

void Game::detonateRocket(Vector2 center, int amount, float knockback)
{
    playerEntity.addBlast(center);
    std::vector<std::pair<std::string, Vector2>> targets;
    for (const auto& [id, enemy] : EnemyManager::GetInstance().getEnemies()) {
        if (Vector2Distance(center, enemy->getPosition()) <= Balance::ROCKET_SPLASH_RADIUS + enemy->getHitbox().width)
            targets.push_back({id, Vector2Subtract(enemy->getPosition(), center)});
    }
    for (const auto& [id, direction] : targets) damageEquipmentEnemy(id, amount, direction, knockback);
    std::vector<std::string> debrisTargets;
    for (const auto& [id, debris] : DebrisManager::GetInstance().getDebris()) {
        if (Vector2Distance(center, debris->getPosition()) <= Balance::ROCKET_SPLASH_RADIUS + debris->getDebrisSize())
            debrisTargets.push_back(id);
    }
    for (const auto& id : debrisTargets) destroyEquipmentDebris(id);
}

void Game::resolveEquipmentAttacks()
{
    auto& em = EnemyManager::GetInstance();
    auto& am = DebrisManager::GetInstance();
    const int ticks = playerEntity.consumeLaserTicks();
    if (playerEntity.isLaserActive() && ticks > 0) {
        const Vector2 from = playerEntity.getLaserStart(), to = playerEntity.getLaserEnd();
        std::vector<std::string> targets;
        for (const auto& [id, enemy] : em.getEnemies()) {
            if (Bullet::hitFraction(from, to, enemy->getPosition(), Balance::LASER_RADIUS + enemy->getHitbox().width) >= 0.0f)
                targets.push_back(id);
        }
        for (const auto& id : targets) damageEquipmentEnemy(id, ticks * playerEntity.scaleAttackDamage(Balance::LASER_DAMAGE),
            Vector2Subtract(to, from), playerEntity.getKnockbackPower());
        targets.clear();
        for (const auto& [id, debris] : am.getDebris()) {
            if (Bullet::hitFraction(from, to, debris->getPosition(), Balance::LASER_RADIUS + debris->getDebrisSize()) >= 0.0f)
                targets.push_back(id);
        }
        for (const auto& id : targets) destroyEquipmentDebris(id);
    }

    auto& bulletManager = BulletManager::GetInstance();
    auto& bullets = bulletManager.getBullets();
    for (auto& bullet : bullets) {
        if (bullet.isEnemyBullet() || bullet.getKind() == PROJECTILE_LEGACY) continue;
        struct Hit { float fraction; std::string id; bool debris; };
        std::vector<Hit> hits;
        for (const auto& [id, enemy] : em.getEnemies()) {
            if (bullet.hasHit(id)) continue;
            const float t = Bullet::hitFraction(bullet.getPreviousPosition(), bullet.getPosition(),
                enemy->getPosition(), bullet.getRadius() + enemy->getHitbox().width);
            if (t >= 0.0f) hits.push_back({t, id, false});
        }
        for (const auto& [id, debris] : am.getDebris()) {
            if (bullet.hasHit(id)) continue;
            const float t = Bullet::hitFraction(bullet.getPreviousPosition(), bullet.getPosition(),
                debris->getPosition(), bullet.getRadius() + debris->getDebrisSize());
            if (t >= 0.0f) hits.push_back({t, id, true});
        }
        std::sort(hits.begin(), hits.end(), [](const Hit& a, const Hit& b) {
            return a.fraction == b.fraction ? a.id < b.id : a.fraction < b.fraction;
        });
        for (const auto& hit : hits) {
            if (!bullet.canPierce()) break;
            // An earlier rocket splash may already have destroyed this target.
            if (hit.debris ? !am.getDebris().contains(hit.id) : !em.getEnemies().contains(hit.id)) continue;
            const Vector2 impactPosition = Vector2Lerp(
                bullet.getPreviousPosition(), bullet.getPosition(), hit.fraction);
            if (bullet.getKind() == PROJECTILE_ROCKET) {
                bulletManager.spawnImpact(impactPosition, bullet.getKind(), false, bullet.getDirection());
                detonateRocket(impactPosition, bullet.getDamage(), bullet.getKnockbackPower());
                bullet.reducePiercePower();
                bullet.recordHit(hit.id);
                continue;
            }
            if (hit.debris) destroyEquipmentDebris(hit.id);
            else damageEquipmentEnemy(hit.id, bullet.getDamage(), bullet.getDirection(), bullet.getKnockbackPower());
            bulletManager.spawnImpact(impactPosition, bullet.getKind(), false, bullet.getDirection());
            bullet.recordHit(hit.id);
            bullet.reducePiercePower();
        }
    }
    std::erase_if(bullets, [](const Bullet& bullet) {
        return bullet.getKind() != PROJECTILE_LEGACY && !bullet.canPierce();
    });
}

void Game::updateCameraZoom(float dt)
{
    const float target = barricadeEvent.isContaining() ? Config::CAMERA_ZOOM_BARRICADE : Config::CAMERA_ZOOM_PLAY;
    const float response = !barricadeEvent.isContaining() && utils::gameCamera.zoom > Config::CAMERA_ZOOM_PLAY ?
        Config::CAMERA_INTRO_RESPONSE : Config::CAMERA_EVENT_RESPONSE;
    utils::gameCamera.zoom += (target - utils::gameCamera.zoom) * (1.0f - std::exp(-response * dt));
}

void Game::resolveBarricadeContact(Vector2 previousPlayerPosition)
{
    if (!barricadeEvent.constrainPlayer(playerEntity, previousPlayerPosition) || playerEntity.getHealth() > 0) return;
    deathInfo.killerType = KILLER_DEBRIS;
    deathInfo.killerID = "barricade";
    deathInfo.killerName = "Barricade";
    deathInfo.killerTexture = ResourceManager::GetInstance().GetTexture("debris");
    gameState = GAME_OVER;
    ExplosionConfettiManager::GetInstance().startExplosion(playerEntity.getPosition());
    GameOverOverlay::GetInstance().startOverlay();
    PlaySound(ResourceManager::GetInstance().GetSound("game_over"));
    StopMusicStream(gameMusic);
}

std::string Game::update() 
{
    // if (IsKeyPressed(KEY_ENTER)) return "MainMenu"; 
    UpdateMusicStream(gameMusic);

#ifdef GAME_DEBUG
    if (debugTools.capturesInput()) {
        if (gameTimer.isRunning()) {
            gameTimer.pause();
            debugPausedTimer = true;
        }
        return "Game";
    }
    if (debugPausedTimer) {
        gameTimer.unpause();
        debugPausedTimer = false;
    }
#endif

    if (IsKeyPressed(KEY_P)) {
        if (gameState == GAME_RUNNING) {
            gameTimer.pause();
            gameState = GAME_PAUSED;
        } else if (gameState == GAME_PAUSED) {
            gameTimer.unpause();
            gameState = GAME_RUNNING;
        }
    }

    // std::cout << "Game Timer: " << (int)gameTimer.getElapsedTime() << " seconds" << std::endl;

    switch (gameState) {
    case GAME_RUNNING:
    {
#pragma region AugmentSelection

        if ((int)gameTimer.getElapsedTime() % 20 == 0 && (int)gameTimer.getElapsedTime() > 0 && (int)gameTimer.getElapsedTime() != prevGameTimer) {
            
            auto offers = augmentCatalog();
            std::shuffle(offers.begin(), offers.end(), augmentRng);
            
            float cardWidth = 1200.0f;
            float cardHeight = 300.0f;
            float gap = 75.0f;
            
            float centerX = GAME_SCREEN_WIDTH / 2.0f - cardWidth / 2.0f;
            float centerY = GAME_SCREEN_HEIGHT / 2.0f - cardHeight / 2.0f;
            
            std::vector<Vector2> cardPositions = {
                {centerX, centerY - cardHeight - gap},   
                {centerX, centerY},                       
                {centerX, centerY + cardHeight + gap}     
            };
            
            for (int i = 0; i < 3; i++) {
                augmentCards.push_back(Card(
                    cardPositions[i], 
                    {cardWidth, cardHeight}, 
                    offers[i].id
                ));
            }
            
            for (auto& card : augmentCards) {
                card.startIntroAnimation();
            }

            ConfettiManager::GetInstance().startConfetti();

            prevGameTimer = (int)gameTimer.getElapsedTime();
            gameTimer.pause();
            gameState = GAME_AUGMENT_SELECTION;
        }

#pragma endregion AugmentSelection

        if (gameState != GAME_RUNNING) break;

#pragma region StartAnimation

        float deltaTime = GetFrameTime();
        barricadeEvent.update(deltaTime, gameTimer.getElapsedTime(), playerEntity.getPosition());
        updateCameraZoom(deltaTime);

#pragma endregion

        // handle playr shooting

#pragma region UpdatePlayer

        const Vector2 previousPlayerPosition = playerEntity.getPosition();
        playerEntity.update();
        // ?  the enemies bullet shares the same bullet max range since it is relative to the player
        BulletManager::GetInstance().update(playerEntity.getPosition()); // ?  it only gets player position to calculate the distance to the bullets
        const bool skillTeleported = updateSkills(deltaTime,
            GetScreenToWorld2D(GetMousePosition(), utils::gameCamera), IsKeyPressed(KEY_Q));
        DamageIndicatorManager::GetInstance().update();
        ConfettiManager::GetInstance().update();
        DamageOverlay::GetInstance().update();

#pragma endregion


#pragma region CameraMovement

        Vector2 playerPos = playerEntity.getPosition();
        Vector2 playerVelocity = playerEntity.getVelocity();

        float leadStrength = 0.35f; 
        Vector2 leadOffset = Vector2Scale(playerVelocity, leadStrength);

        Vector2 desiredCameraTarget = Vector2Add(playerPos, leadOffset);


        float cameraLerpSpeed = 5.0f; 
        utils::gameCamera.target.x += (desiredCameraTarget.x - utils::gameCamera.target.x) * (1.0f - expf(-cameraLerpSpeed * deltaTime));
        utils::gameCamera.target.y += (desiredCameraTarget.y - utils::gameCamera.target.y) * (1.0f - expf(-cameraLerpSpeed * deltaTime));

#pragma endregion

        
        BulletManager& bm = BulletManager::GetInstance();
        EnemyManager& em = EnemyManager::GetInstance();
        DebrisManager& am = DebrisManager::GetInstance();


#pragma region UpdateBulletsCollision

        resolveEquipmentAttacks();

        // Snapshot before movement, matching the original bullet collision phase.
        enemyCollisionGrid.clear();
        collisionEnemies.clear();
        enemyCollisionGrid.reserve(em.getEnemies().size());
        for (auto& [id, enemy] : em.getEnemies()) {
            enemyCollisionGrid.add(enemy->getPosition(), enemy->getHitbox().width);
            collisionEnemies.push_back(enemy.get());
        }
        enemyCollisionGrid.build();
        debrisCollisionGrid.clear();
        collisionDebris.clear();
        debrisCollisionGrid.reserve(am.getDebris().size());
        for (auto& [id, debris] : am.getDebris()) {
            debrisCollisionGrid.add(debris->getPosition(), debris->getDebrisSize());
            collisionDebris.push_back(debris.get());
        }
        debrisCollisionGrid.build();


        for (int i = 0; i < static_cast<int>(bm.getBullets().size()); i++) {

            if (bm.getBullets()[i].getKind() != PROJECTILE_LEGACY) continue;

            if (!bm.getBullets()[i].isEnemyBullet()) {
                // Player bullets vs enemies
                std::vector<std::string> enemiesToRemove;
                bool hitSomething = false;
                
                if (const auto target = enemyCollisionGrid.firstHit(bm.getBullets()[i].getPosition());
                    target != SpatialGrid::NO_HIT) {
                    auto* enemy = collisionEnemies[target];
                    const auto id = enemy->getEnemyID();
                    if (CheckCollisions(bm.getBullets()[i].getPosition(), 
                                    enemy->getPosition(), 
                                    enemy->getHitbox().width)) {
                        
                        int damage = playerEntity.getRandomDamage();
                        enemy->takeDamage(damage);
                        playerEntity.addDamageDealt(damage);
                        
                        if (bm.getBullets()[i].getKnockbackPower() > 0.0f && enemy->canReceiveKnockback()) {
                            enemy->applyKnockback(bm.getBullets()[i].getDirection(), 
                                                bm.getBullets()[i].getKnockbackPower());
                        }
                        
                        DamageIndicatorManager::GetInstance().addDamageIndicator(
                            enemy->getPosition(), damage, playerEntity.getMaxDamage());
            
                        
                        if (enemy->isDead()) {
                            killCounter.increment();
                            for (int j = 0; j < MAX_SOUND_INSTANCES; j++) {
                                if (!IsSoundPlaying(scoreSounds[j])) {
                                    PlaySound(scoreSounds[j]);
                                    break;
                                }
                            }
                            switch (enemy->getEnemyType()) {
                            case LOW_LEVEL_ENEMY:
                                playerEntity.addScore(10);
                                break;
                            case MID_LEVEL_ENEMY:
                                playerEntity.addScore(50);
                                break;
                            default:
                                playerEntity.addScore(5);
                                break;
                            }
                            enemiesToRemove.push_back(id);
                            enemyCollisionGrid.deactivate(target);
                        }
                        
                        hitSomething = true;
                        bm.spawnImpact(bm.getBullets()[i].getPosition(), PROJECTILE_LEGACY, false,
                            bm.getBullets()[i].getDirection());
                    }
                }
                
                // Player bullets vs debris
                std::vector<std::string> debrisToRemove;
                if (!hitSomething) {
                    if (const auto target = debrisCollisionGrid.firstHit(bm.getBullets()[i].getPosition());
                        target != SpatialGrid::NO_HIT) {
                        auto* debris = collisionDebris[target];
                        const auto id = debris->getDebrisID();
                        if (CheckCollisions(bm.getBullets()[i].getPosition(),
                                        debris->getPosition(),
                                        debris->getDebrisSize())) {
                            for (int j = 0; j < MAX_SOUND_INSTANCES; j++) {
                                if (!IsSoundPlaying(scoreSounds[j])) {
                                    PlaySound(scoreSounds[j]);
                                    break;
                                }
                            }
                            killCounter.increment();
                            playerEntity.addScore(5);
                            debrisToRemove.push_back(id);
                            debrisCollisionGrid.deactivate(target);
                            hitSomething = true;
                            bm.spawnImpact(bm.getBullets()[i].getPosition(), PROJECTILE_LEGACY, false,
                                bm.getBullets()[i].getDirection());
                        }
                    }
                }
        

                if (hitSomething) {
   
                    bm.getBullets()[i].reducePiercePower();
                    
                    if (!bm.getBullets()[i].canPierce()) {
                        bm.removeBullet(i);
                        i--; 
                    }
                    
                    for (auto& id : enemiesToRemove) {
                        em.removeEnemy(id);
                    }
                    for (auto& id : debrisToRemove) {
                        am.removeDebris(id, true);
                    }
                }
            }
            else {
                // Enemy bullets vs player
                const auto& incoming = bm.getBullets()[i];
                const float shieldHit = Bullet::hitFraction(incoming.getPreviousPosition(), incoming.getPosition(),
                    playerEntity.getPosition(), Balance::SHIELD_RADIUS);
                if (shieldHit >= 0.0f && playerEntity.tryBlockHit(Vector2Lerp(
                    incoming.getPreviousPosition(), incoming.getPosition(), shieldHit))) {
                    bm.spawnImpact(Vector2Lerp(incoming.getPreviousPosition(), incoming.getPosition(), shieldHit),
                        incoming.getKind(), true, incoming.getDirection());
                    bm.removeBullet(i--);
                    continue;
                }
                if (CheckCollisions(bm.getBullets()[i].getPosition(),
                                playerEntity.getPosition(),
                                playerEntity.getHitbox().width) &&
                                playerEntity.getPlayerState() == PLAYER_DEFAULT) {
                    Vector2 bulletPosition = bm.getBullets()[i].getPosition(); 
                    const int incomingDamage = incoming.getDamage() > 0 ? incoming.getDamage() : Balance::PLAYER_CONTACT_DAMAGE;
                    bm.spawnImpact(bulletPosition, bm.getBullets()[i].getKind(), true,
                        bm.getBullets()[i].getDirection());
                    bm.removeBullet(i);
                    playerEntity.takeContactDamage(GetTime(), bulletPosition, 3.0f,
                        incomingDamage);
                    if (playerEntity.getHealth() <= 0) {
                        deathInfo.killerType = KILLER_ENEMY_BULLET;
                        deathInfo.killerID = "enemy_bullet";
                        deathInfo.killerName = "Enemy Bullet";
                        deathInfo.killerTexture = ResourceManager::GetInstance().GetTexture("enemy_bullet");
                        gameState = GAME_OVER;
                        ExplosionConfettiManager::GetInstance().startExplosion(playerEntity.getPosition());
                        GameOverOverlay::GetInstance().startOverlay();
                        PlaySound(ResourceManager::GetInstance().GetSound("game_over"));
                        StopMusicStream(gameMusic);
                    }
                    i--; 
                    continue;
                }
                
                // Enemy bullets vs debris
                std::vector<std::string> debrisToRemove;
                if (const auto target = debrisCollisionGrid.firstHit(bm.getBullets()[i].getPosition());
                    target != SpatialGrid::NO_HIT) {
                    auto* debris = collisionDebris[target];
                    const auto id = debris->getDebrisID();
                    if (CheckCollisions(bm.getBullets()[i].getPosition(),
                                    debris->getPosition(),
                                    debris->getDebrisSize())) {
                        debrisToRemove.push_back(id);
                        debrisCollisionGrid.deactivate(target);
                    }
                }
        
                if (!debrisToRemove.empty()) {
                    bm.spawnImpact(bm.getBullets()[i].getPosition(), bm.getBullets()[i].getKind(), true,
                        bm.getBullets()[i].getDirection());
                    bm.removeBullet(i);
                    i--;
                    
                    for (auto& id : debrisToRemove) {
                        am.removeDebris(id);
                    }
                }
            }
        }
        

#pragma endregion



#pragma region UpdateDebris

    
        am.update(playerEntity.getPosition(), gameTimer); 
        // TraceLog(LOG_INFO, "Debris count: %d", debris.size());

#pragma endregion


        EnemyManager::GetInstance().update(playerEntity.getPosition(), gameTimer, skills.decoy(),
            Balance::ABILITIES[ABILITY_HOLOGRAM_CLONE].radius);

        resolveBarricadeContact(skillTeleported ? playerEntity.getPosition() : previousPlayerPosition);
        barricadeEvent.finishIfEscaped(playerEntity.getPosition(), utils::gameCamera);



#pragma region UpdateEntitiesCollision

        // Movement/spawning invalidates the earlier debris snapshot.
        debrisCollisionGrid.clear();
        collisionDebris.clear();
        for (auto& [id, debris] : am.getDebris()) {
            debrisCollisionGrid.add(debris->getPosition(), debris->getDebrisSize());
            collisionDebris.push_back(debris.get());
        }
        debrisCollisionGrid.build();

        std::vector<std::string> enemiesToRemove;
        std::vector<std::string> debrisToRemove;
    
        for (auto& [enemyId, enemy] : EnemyManager::GetInstance().getEnemies()) {   
            // Event segments use persistent swept contact; debris cannot delete them.
            if (enemy->getEnemyType() == BARRICADE_ENEMY) continue;
            
            // player to enemy collision
            if (CheckCollisions(enemy->getPosition(), playerEntity.getPosition(), playerEntity.getHitbox().width)
                && playerEntity.getPlayerState() == PLAYER_DEFAULT) {
                playerEntity.takeContactDamage(GetTime(), enemy->getPosition(), enemy->getHitbox().width, enemy->getContactDamage());
                if (playerEntity.getHealth() <= 0) {
                    deathInfo.killerType = KILLER_ENEMY_COLLISION;
                    deathInfo.killerID = enemyId;
                    if (enemy->getEnemyType() == LOW_LEVEL_ENEMY) {
                        deathInfo.killerName = "Low Level Enemy";
                        // Create a temporary animation for the game over screen
                        Animator::GetInstance().AddAnimation("killer_display", std::make_shared<Animation>(
                            ResourceManager::GetInstance().GetTextureRef("low_level_enemy1"),
                            ResourceManager::GetInstance().GetTexture("low_level_enemy1").width / 10,
                            ResourceManager::GetInstance().GetTexture("low_level_enemy1").height,
                            0.1f,
                            true,
                            Rectangle{0, 0, 256, 256}, // Larger rectangle for scaling
                            false,
                            WHITE
                        ));
                        Animator::GetInstance().Play("killer_display");
                    } else if (enemy->getEnemyType() == MID_LEVEL_ENEMY) {
                        deathInfo.killerName = "Mid Level Enemy";
                        // Create a temporary animation for the game over screen
                        Animator::GetInstance().AddAnimation("killer_display", std::make_shared<Animation>(
                            ResourceManager::GetInstance().GetTextureRef("mid_level_enemy"),
                            ResourceManager::GetInstance().GetTexture("mid_level_enemy").width / 12,
                            ResourceManager::GetInstance().GetTexture("mid_level_enemy").height,
                            0.1f,
                            true,
                            Rectangle{0, 0, 256, 256}, // Larger rectangle for scaling
                            false,
                            WHITE
                        ));
                        Animator::GetInstance().Play("killer_display");
                    } else {
                        deathInfo.killerName = "Enemy";
                        deathInfo.killerTexture = ResourceManager::GetInstance().GetTexture("low_level_enemy1");
                    }
                    gameState = GAME_OVER;
                    ExplosionConfettiManager::GetInstance().startExplosion(playerEntity.getPosition());
                    GameOverOverlay::GetInstance().startOverlay();
                    PlaySound(ResourceManager::GetInstance().GetSound("game_over"));
                    StopMusicStream(gameMusic);
                }
                enemiesToRemove.push_back(enemyId);
                continue; 
            }
            
            // enemy to debris collision
            if (const auto target = debrisCollisionGrid.firstHit(enemy->getPosition());
                target != SpatialGrid::NO_HIT) {
                auto* debris = collisionDebris[target];
                const auto debrisId = debris->getDebrisID();
                if (CheckCollisions(enemy->getPosition(), debris->getPosition(), debris->getDebrisSize())) {
                    enemiesToRemove.push_back(enemyId);
                    debrisToRemove.push_back(debrisId);
                }
            }
        }
        
        // player to debris collision
        for (auto& [debrisId, debris] : DebrisManager::GetInstance().getDebris()) {
            if (CheckCollisions(debris->getPosition(), playerEntity.getPosition(), playerEntity.getHitbox().width)
                && playerEntity.getPlayerState() == PLAYER_DEFAULT) {
                playerEntity.takeDamage(GetTime(), debris->getPosition(), debris->getDebrisSize());
                if (playerEntity.getHealth() <= 0) {
                    deathInfo.killerType = KILLER_DEBRIS;
                    deathInfo.killerID = debrisId;
                    deathInfo.killerName = debris->getDisplayName();
                    deathInfo.killerTexture = ResourceManager::GetInstance().GetTexture(debris->getTextureKey());
                    gameState = GAME_OVER;
                    ExplosionConfettiManager::GetInstance().startExplosion(playerEntity.getPosition());
                    GameOverOverlay::GetInstance().startOverlay();
                    PlaySound(ResourceManager::GetInstance().GetSound("game_over"));
                    StopMusicStream(gameMusic);
                }
                debrisToRemove.push_back(debrisId);
            }
        }
        
        // debris to debris collision
        std::unordered_set<std::string> collidedDebris;
        for (std::size_t index = 0; index < collisionDebris.size(); ++index) {
            if (!debrisCollisionGrid.isActive(index)) continue;
            auto* debris = collisionDebris[index];
            // This pair uses the SOURCE radius, not the target radius or sum.
            const auto target = debrisCollisionGrid.firstWithin(
                debris->getPosition(), debris->getDebrisSize(), index);
            if (target != SpatialGrid::NO_HIT) {
                collidedDebris.insert(debris->getDebrisID());
                collidedDebris.insert(collisionDebris[target]->getDebrisID());
                debrisCollisionGrid.deactivate(index);
                debrisCollisionGrid.deactivate(target);
            }
        }
        
        std::sort(debrisToRemove.begin(), debrisToRemove.end());
        debrisToRemove.erase(std::unique(debrisToRemove.begin(), debrisToRemove.end()), debrisToRemove.end());
        
        for (const auto& id : collidedDebris) {
            if (std::find(debrisToRemove.begin(), debrisToRemove.end(), id) == debrisToRemove.end()) {
                debrisToRemove.push_back(id);
            }
        }
        
        for (const auto& id : enemiesToRemove) {
            em.removeEnemy(id);
        }
        
        for (const auto& id : debrisToRemove) {
            am.removeDebris(id);
        }
        
#pragma endregion

        killCounter.update();
        if (gameState == GAME_RUNNING && playerEntity.getHealth() > 0)
            harvestedScrap += ScrapManager::GetInstance().update(GetFrameTime(), playerEntity.getPosition());
        break;
    }
    
    case GAME_AUGMENT_SELECTION:
    {
        // Update confetti effect
        ConfettiManager::GetInstance().update();
        
        for (auto& card : augmentCards) {
            card.update();
            if (card.isIntroComplete() && !card.hasStartedExit() && card.isClicked()) {
                PlaySound(ResourceManager::GetInstance().GetSound("button_click"));
                applyAugment(playerEntity, card.getAugmentId());
                card.startExitAnimation();
                break;
            }
            if (card.isExitComplete()) {
                augmentCards.clear();
                ConfettiManager::GetInstance().stopConfetti();
                gameTimer.unpause();
                gameState = GAME_RUNNING; 
                break;
            }
        }
        break; 
    }
    
    case GAME_PAUSED:
    {
        // cant draw here as it is an update function (a prob to solved latr)
        // const Texture2D& pauseTexture = ResourceManager::GetInstance().GetTextureRef("window");
        break;
    }
    
    case GAME_OVER:
    {
        skills.reset();
        playerEntity.setDeflectorHits(0);
        barricadeEvent.reset();
        ScrapManager::GetInstance().reset();
        harvestedScrap = 0;
        updateCameraZoom(GetFrameTime());
        //TODO: STOP THE GAME OVER SOUND AFTER CLICKING THE BUTTON
        gameTimer.pause();
        ExplosionConfettiManager::GetInstance().update();
        GameOverOverlay::GetInstance().update();
        
        if (GameOverOverlay::GetInstance().shouldShowText() && !gameOverTextStarted) {
            Animator::GetInstance().Play("game_over_text");
            gameOverTextStarted = true;
        }
        
        if (restartButton && restartButton->isClicked()) {
            this->restartGame();
            StopSound(ResourceManager::GetInstance().GetSound("game_over"));
            PlaySound(ResourceManager::GetInstance().GetSound("button_click"));
        }
        
        if (mainMenuButton && mainMenuButton->isClicked()) {
            StopSound(ResourceManager::GetInstance().GetSound("game_over"));
            PlaySound(ResourceManager::GetInstance().GetSound("button_click"));
            return "MainMenu";
        }
        
        Animator::GetInstance().Update();
        break;
    }
    
    default:
        TraceLog(LOG_ERROR, "Unknown game state: %d", gameState);
    }

    // std:: cout << "Player Health: " << playerEntity.getHealth() << std::endl;

    return "Game";
}


void Game::DrawLayer(const BackgroundLayer& layer, const Vector2& viewCenter) 
{
    Vector2 parallaxOffset = {
        viewCenter.x * (1.0f - layer.parallaxFactor),
        viewCenter.y * (1.0f - layer.parallaxFactor)
    };

    int startX = static_cast<int>(std::floor((viewCenter.x - parallaxOffset.x) / layer.size));
    int startY = static_cast<int>(std::floor((viewCenter.y - parallaxOffset.y) / layer.size));

    for (int y = -1; y <= 1; y++) { 
        for (int x = -1; x <= 1; x++) {
            Vector2 tilePos = {
                (startX + x) * layer.size + parallaxOffset.x,
                (startY + y) * layer.size + parallaxOffset.y
            };

            DrawTextureV(layer.texture, tilePos, WHITE); // TODO: MAKE IT RED WHEN THE BOSS APPEARS
        }
    }
}


void Game::DrawParallaxBackground()
{
    Vector2 viewCenter = utils::gameCamera.target;
    
    for (const auto& layer : backgroundLayers) {
        DrawLayer(layer, viewCenter);
    }
}

void Game::draw()
{
    BeginMode2D(utils::gameCamera);

        DrawParallaxBackground();
        BulletManager::GetInstance().draw(playerBulletTexture, enemyBulletTexture);

        // Equipment layers draw directly in a fixed order.
        playerEntity.draw();
        skills.draw();

        EnemyManager::GetInstance().draw();
        DebrisManager::GetInstance().draw();
        ScrapManager::GetInstance().draw();
        DamageIndicatorManager::GetInstance().draw();

#pragma region ControlsGuide

        if (gameTimer.getElapsedTime() > 0.4f && gameTimer.getElapsedTime() < 10.0f) {
            Vector2 wasdScreenPos = {1000, 1800}; // Top-left corner
            Vector2 eKeyScreenPos = {2000, 1850}; // Below WASD keys
            
            Vector2 wasdWorldPos = GetScreenToWorld2D(wasdScreenPos, utils::gameCamera);
            Vector2 eKeyWorldPos = GetScreenToWorld2D(eKeyScreenPos, utils::gameCamera);
            
            float elapsed = gameTimer.getElapsedTime();
            float alpha = 1.0f;
            
            //? fade in from 0.4s to 1.4s (1 second fade in)
            if (elapsed < 1.4f) {
                alpha = (elapsed - 0.4f) / 1.0f; // 0.0 to 1.0
                alpha = std::max(0.0f, std::min(1.0f, alpha));
            }
            //? fade out from 9.0s to 10.0s (1 second fade out)
            else if (elapsed > 9.0f) {
                alpha = (10.0f - elapsed) / 1.0f; // 1.0 to 0.0
                alpha = std::max(0.0f, std::min(1.0f, alpha));
            }
            //? apply alpha to animations
            Color animationTint = {255, 255, 255, (unsigned char)(alpha * 255)};
            Animator::GetInstance().SetTint("wasd_keys_tutorial", animationTint);
            Animator::GetInstance().SetTint("e_key_tutorial", animationTint);
            
            Animator::GetInstance().SetPosition("wasd_keys_tutorial", wasdWorldPos);
            Animator::GetInstance().SetPosition("e_key_tutorial", eKeyWorldPos);

            Font font = ResourceManager::GetInstance().GetFont("primary_font");
            
            Color textTint = {128, 128, 128, (unsigned char)(alpha * 255)}; 
            
            // WASD text
            Vector2 wasdTextScreenPos = {wasdScreenPos.x + 380, wasdScreenPos.y + 50}; 
            Vector2 wasdTextWorldPos = GetScreenToWorld2D(wasdTextScreenPos, utils::gameCamera);
            DrawTextEx(font, "MOVEMENT", wasdTextWorldPos, 5, 0, textTint);
            
            // E key text
            Vector2 eKeyTextScreenPos = {eKeyScreenPos.x + 160, eKeyScreenPos.y}; 
            Vector2 eKeyTextWorldPos = GetScreenToWorld2D(eKeyTextScreenPos, utils::gameCamera);
            DrawTextEx(font, "AUTO-SHOOT", eKeyTextWorldPos, 5, 0, textTint);
        }
        else if (gameTimer.getElapsedTime() > 10.0f) {
            Animator::GetInstance().Stop("wasd_keys_tutorial");
            Animator::GetInstance().Stop("e_key_tutorial");
        }

#pragma endregion ControlsGuide

        Animator::GetInstance().Update();
        Animator::GetInstance().Draw(); 

        // std::cout << "Player Position: (" << playerEntity.getPosition().x << ", " << playerEntity.getPosition().y << ")" << std::endl;
        if(gameState == GAME_OVER) ExplosionConfettiManager::GetInstance().draw();

#ifdef GAME_DEBUG
        debugTools.drawWorld(playerEntity);
#endif

    EndMode2D();

    if (gameState != GAME_OVER) playerEntity.drawEquipmentStatus();
    if (gameState != GAME_OVER) skills.drawStatus();

    if(gameState == GAME_AUGMENT_SELECTION) ConfettiManager::GetInstance().draw();

    if (!augmentCards.empty()) {
        for (auto& card : augmentCards) {
            card.draw();
        }
    }
    
    if(gameState == GAME_OVER) {
        GameOverOverlay::GetInstance().draw();
        
        if (GameOverOverlay::GetInstance().shouldShowText()) {
            float textY = GameOverOverlay::GetInstance().getTextYPosition() + 100;
            float textX = (GAME_SCREEN_WIDTH - 1800.0f) / 2.0f; 
            
            Animator::GetInstance().SetPosition("game_over_text", {textX, textY});
            Animator::GetInstance().Draw();
            
            Font font = ResourceManager::GetInstance().GetFont("primary_font");
            float detailsStartY = textY + 500; 
            float leftColumnX = GAME_SCREEN_WIDTH / 2.0f - 800;
            float rightColumnX = GAME_SCREEN_WIDTH / 2.0f + 150;
            float lineHeight = 80;
            
            DrawTextEx(font, TextFormat("Destroyed: %d", killCounter.getCount()), 
                      Vector2{leftColumnX, detailsStartY}, 80, 0, WHITE);
            
            DrawTextEx(font, TextFormat("Total Score: %d", playerEntity.getScore()), 
                      Vector2{leftColumnX, detailsStartY + lineHeight}, 80, 0, WHITE);
            
            DrawTextEx(font, TextFormat("Time Survived: %s", gameTimer.getElapsedTimeString().c_str()), 
                      Vector2{leftColumnX, detailsStartY + lineHeight * 2}, 80, 0, WHITE);
            
            DrawTextEx(font, TextFormat("Damage Dealt: %d", playerEntity.getTotalDamageDealt()), 
                      Vector2{leftColumnX, detailsStartY + lineHeight * 3}, 80, 0, WHITE);
            
            DrawTextEx(font, "Killed by:", 
                      Vector2{rightColumnX, detailsStartY}, 80, 0, WHITE);
            
            DrawTextEx(font, deathInfo.killerName.c_str(), 
                      Vector2{rightColumnX, detailsStartY + lineHeight}, 80, 0, RED);
            
            float killerImageY = detailsStartY + lineHeight * 2;
            Vector2 killerPos = {rightColumnX, killerImageY}; 
            
            if (deathInfo.killerType == KILLER_ENEMY_COLLISION) {
                Animator::GetInstance().SetPosition("killer_display", killerPos);
                Animator::GetInstance().Draw();
            } else {
                Rectangle killerRect = {rightColumnX, killerImageY, 256, 256};
                DrawTexturePro(deathInfo.killerTexture,
                              Rectangle{0, 0, (float)deathInfo.killerTexture.width, (float)deathInfo.killerTexture.height},
                              killerRect,
                              Vector2{0, 0},
                              0.0f,
                              WHITE);
            }
            
            if (restartButton) restartButton->draw();
            if (mainMenuButton) mainMenuButton->draw();
        }
    } 
    else {
#pragma region HealtBar
 
        const Texture2D& healthbarTexture = ResourceManager::GetInstance().GetTextureRef("health_bar");
        DrawTexturePro(healthbarTexture,
                    Rectangle{0, 0, (float)healthbarTexture.width, (float)healthbarTexture.height},
                    Rectangle{GAME_SCREEN_WIDTH - 1200, 150, 1000, 150},
                    Vector2{0, 0},
                    0.0f,
                    WHITE);

        const Texture2D& healthTexture = ResourceManager::GetInstance().GetTextureRef("health");
        float healthBarWidth = 1000.0f * (static_cast<float>(playerEntity.getHealth()) / playerEntity.getMaxHealth());
        DrawTexturePro(healthTexture,
                    Rectangle{0, 0, (float)healthTexture.width, (float)healthTexture.height},
                    Rectangle{GAME_SCREEN_WIDTH - 1200, 150, healthBarWidth, 150},
                    Vector2{0, 0},
                    0.0f,
                    WHITE);

#pragma endregion HealtBar

        killCounter.draw();
        DrawTextEx(ResourceManager::GetInstance().GetFont("primary_font"),
            TextFormat("SCRAP %d", harvestedScrap), Theme::SCRAP_HUD_POSITION,
            Theme::SCRAP_HUD_SIZE, 0.0f, Theme::COLOR_HARVEST);
        gameTimer.draw(GAME_SCREEN_WIDTH);
        barricadeEvent.drawStatus();
        
        DamageOverlay::GetInstance().draw();
    }
#ifdef GAME_DEBUG
    debugTools.drawOverlay(playerEntity, gameState, barricadeEvent);
#endif
}

void Game::onExit()
{
    skills.reset();
    playerEntity.setDeflectorHits(0);
    barricadeEvent.reset();
    ScrapManager::GetInstance().reset();
    harvestedScrap = 0;
    utils::gameCamera.zoom = Config::CAMERA_ZOOM_PLAY;
    Animator::GetInstance().StopAll();
    Animator::GetInstance().Remove("killer_display"); // Clean up killer animation
    StopMusicStream(gameMusic);
}

#ifdef GAME_DEBUG
bool Game::updateDebugConsole(bool activeGame)
{
    debugTools.bindSkills(&skills);
    debugTools.update(activeGame ? &playerEntity : nullptr, activeGame ? &barricadeEvent : nullptr);
    return debugTools.capturesInput();
}

void Game::drawDebugConsole() const
{
    debugTools.drawConsole();
}

void Game::executeDebugCommand(const std::string& command)
{
    debugTools.bindSkills(&skills);
    debugTools.runCommand(command, &playerEntity, &barricadeEvent);
}
#endif
