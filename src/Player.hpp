#pragma once
#include "Entity.hpp"
#include "BulletManager.hpp"

enum PlayerState { PLAYER_DEFAULT, PLAYER_STUNNED, PLAYER_IFRAME, PLAYER_DEAD };
enum PlayerEngine { ENGINE_BASE, ENGINE_PULSE, ENGINE_BURST, ENGINE_SUPERCHARGED };
enum PlayerShield { SHIELD_NONE, SHIELD_FRONT, SHIELD_SIDES, SHIELD_ROUND, SHIELD_INVINCIBILITY };
enum PlayerBuild { BUILD_DEFAULT, BUILD_CANNON, BUILD_LASER, BUILD_ROCKETS, BUILD_HEAVY };

class Player : public Entity
{
public:
    Player();
    void init();
    void update() override;
    void draw() override;
    void drawEquipmentStatus() const;
    Rectangle getHitbox() const { return rect; }
    void takeDamage(float timeStateEntered, Vector2 entityPosition, float entitySize);
    PlayerState getPlayerState() const { return playerState; }
    void addScore(int score) { playerScore += score; }
    int getScore() const { return playerScore; }
    void addDamageDealt(int amount) { totalDamageDealt += amount; }
    int getTotalDamageDealt() const { return totalDamageDealt; }
    void setBuild(PlayerBuild build);
    void setWeapon(PlayerWeapon weapon);
    void setEngine(PlayerEngine engine);
    void setShield(PlayerShield shield);
    PlayerWeapon getWeapon() const { return weapon; }
    PlayerEngine getEngine() const { return engine; }
    PlayerShield getShield() const { return shield; }
    float getShieldCharge() const { return shieldCharge; }
    bool tryBlockHit(Vector2 source);
    bool shieldCovers(Vector2 source) const;
    bool isLaserActive() const { return laserActive; }
    Vector2 getLaserStart() const;
    Vector2 getLaserEnd() const;
    int consumeLaserTicks();
    void addBlast(Vector2 center);
    void drawAttackHitboxes() const;
#ifdef GAME_DEBUG
    void setDebugInvincible(bool enabled) { debugInvincible = enabled; }
    bool isDebugInvincible() const { return debugInvincible; }
#endif
    void increasePlayerAttackSpeed();
    void increasePlayerHealth();
    void increasePlayerMovementSpeed();
    void increasePlayerIframeDuration();
    void increasePlayerRotationSpeed();
    void increaseTriggerHappyBurst();
    void increaseScatterShot();
    void increasePiercingRounds();
    void increaseInertiaImpact();
    int getRandomDamage() const;
    int getMinDamage() const { return minDamage; }
    int getMaxDamage() const { return maxDamage; }
    float getKnockbackPower() const { return knockbackPower; }

private:
    friend struct EquipmentTestAccess;
    void fireScatterBullets(Vector2 direction);
    void updateEquipment(float dt, bool skillPressed);
    void updateWeapon(float dt, bool firing);
    float weaponCooldown() const;
    Vector2 facing() const;
    struct Blast { Vector2 center; float remaining; };
    std::vector<Blast> blasts;
    PlayerWeapon weapon = WEAPON_CANNON;
    PlayerEngine engine = ENGINE_BASE;
    PlayerShield shield = SHIELD_NONE;
    float shieldCharge = 0.0f, shieldDelay = 0.0f;
    float boostTime = 0.0f, boostCooldown = 0.0f;
    float invincibilityTime = 0.0f, invincibilityCooldown = 0.0f;
    float animationTime = 0.0f, weaponAnimationTime = 0.0f, weaponFlash = 0.0f;
    float shotCooldown = 0.0f, laserClock = 0.0f, stateElapsed = 0.0f;
    int pendingLaserTicks = 0;
    bool laserActive = false;
#ifdef GAME_DEBUG
    bool debugInvincible = false;
#endif
    float attackSpeed = 0.0f, iframeDuration = 0.0f, rotationSpeedMultiplier = 1.0f;
    int burstCount = 1, currentBurstShot = 0, scatterCount = 1, bulletPiercePower = 1;
    bool isBurstActive = false;
    float knockbackPower = 0.0f;
    int minDamage = 0, maxDamage = 0, playerScore = 0, totalDamageDealt = 0;
    bool playerAccelerating = false, autoShoot = false;
    PlayerState playerState = PLAYER_DEFAULT;
    float timeStateEntered = 0.0f;
};
