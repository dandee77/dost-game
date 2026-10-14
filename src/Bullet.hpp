#pragma once
#include "raylib.h"
#include <string>
#include <vector>

enum PlayerWeapon { WEAPON_CANNON, WEAPON_LASER, WEAPON_ROCKETS, WEAPON_HEAVY };
enum ProjectileKind { PROJECTILE_LEGACY, PROJECTILE_CANNON, PROJECTILE_ROCKET, PROJECTILE_HEAVY };

class Bullet
{
public:
    Bullet(Vector2 position, Vector2 direction, bool isEnemy, int piercePower = 1, float knockbackPower = 0.0f);

    void update();        
    void draw(const Texture2D &texture) const;             
    Vector2 getPosition() const { return position; }
    Vector2 getDirection() const { return fireDirection; }
    bool isEnemyBullet() const { return enemyBullet; }
    void setBulletSpeed(float s) { speed = s; }
    int getPiercePower() const { return piercePower; }
    void reducePiercePower() { piercePower--; }
    bool canPierce() const { return piercePower > 0; }
    float getKnockbackPower() const { return knockbackPower; }
    void configure(ProjectileKind kind, int damage, float radius, float speed);
    ProjectileKind getKind() const { return kind; }
    int getDamage() const { return damage; }
    float getRadius() const { return radius; }
    Vector2 getPreviousPosition() const { return previousPosition; }
    bool hasHit(const std::string& id) const;
    void recordHit(const std::string& id);
    // Earliest intersection of a swept circle with a target; -1 means no hit.
    static float hitFraction(Vector2 from, Vector2 to, Vector2 center, float radius);

private:
    ProjectileKind kind = PROJECTILE_LEGACY;
    int damage = 0;
    float radius = 0.0f;
    float animationTime = 0.0f;
    Vector2 previousPosition = {};
    std::vector<std::string> hitIds;
    Vector2 position;
    Vector2 fireDirection;
    float speed = 200.0f;
    bool enemyBullet;
    int piercePower;
    float knockbackPower;

    float angle = 0.0f;
};
