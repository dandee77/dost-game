#pragma once
#include "Scene.hpp"
#include "raylib.h"
#include <string>
#include "ResourceManager.hpp"
#include <vector>
#include "Player.hpp"
#include "EnemyManager.hpp"
#include "Debris.hpp"
#include "KillCounter.hpp"
#include "GameTimer.hpp"
#include <array>
#include "Card.hpp"
#include <vector>
#include "Utils.hpp"
#include "DamageIndicatorManager.hpp"
#include "ConfettiManager.hpp"
#include "ExplosionConfettiManager.hpp"
#include "GameOverOverlay.hpp"
#include "Button.hpp"
#include "SpatialGrid.hpp"
#include "BarricadeEvent.hpp"
#ifdef GAME_DEBUG
#include "DebugTools.hpp"
#endif

#define MAX_SOUND_INSTANCES 10

enum KillerType
{
    KILLER_ENEMY_BULLET = 0,
    KILLER_ENEMY_COLLISION,
    KILLER_DEBRIS
};

struct DeathInfo
{
    KillerType killerType;
    std::string killerID;
    std::string killerName;
    Texture2D killerTexture;
};

enum GameState : int
{
    GAME_RUNNING = 0,
    GAME_AUGMENT_SELECTION,
    GAME_PAUSED,
    GAME_OVER,
};

class Game : public Scene
{
public:
    Game();
    ~Game();
    std::string update() override;
    void draw() override;
    void onSwitch() override;
    void onExit() override;
#ifdef GAME_DEBUG
    bool updateDebugConsole(bool activeGame);
    void drawDebugConsole() const;
#endif

private:        
    friend struct EquipmentTestAccess;
    struct BackgroundLayer {
        Texture2D texture;
        float parallaxFactor; // 0.0 (stationary) to 1.0 (moves with player)
        float size;
    };

    void restartGame();
    void resetRun();
    void resolveEquipmentAttacks();
    void damageEquipmentEnemy(const std::string& id, int damage, Vector2 direction, float knockback);
    void destroyEquipmentDebris(const std::string& id);
    void detonateRocket(Vector2 center, int damage, float knockback);
    void updateCameraZoom(float dt);
    void resolveBarricadeContact(Vector2 previousPlayerPosition);

    GameState gameState;
    int harvestedScrap = 0;
    BarricadeEvent barricadeEvent;
    SpatialGrid enemyCollisionGrid;
    SpatialGrid debrisCollisionGrid;
    std::vector<Enemy*> collisionEnemies;
    std::vector<Debris*> collisionDebris;
#ifdef GAME_DEBUG
    DebugTools debugTools;
    bool debugPausedTimer = false;
#endif

    std::vector<BackgroundLayer> backgroundLayers;
    float worldTileSize;
    
    void DrawParallaxBackground();
    void DrawLayer(const BackgroundLayer& layer, const Vector2& viewCenter);

    Music gameMusic;
    Player playerEntity;

    Texture2D playerBulletTexture; 
    Texture2D enemyBulletTexture;

    std::array<Sound, MAX_SOUND_INSTANCES> scoreSounds;

    KillCounter killCounter;
    GameTimer gameTimer;

    std::vector<Card> augmentCards;
    
    DeathInfo deathInfo;
    Button* restartButton;
    Button* mainMenuButton;
};
