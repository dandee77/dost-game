#pragma once
#include <vector>
#include "Bullet.hpp"
#include "raylib.h"

#define BULLET_DESPAWN_DISTANCE 150.0f


class BulletManager {
public:

    static BulletManager& GetInstance() {
        static BulletManager instance;
        return instance;
    }

    void update(Vector2 position);
    void draw(const Texture2D& playerBulletTexture, const Texture2D& enemyBulletTexture) const;
    void addBullet(Bullet bullet);
    void spawnImpact(Vector2 position, ProjectileKind kind, bool enemy, Vector2 direction);
    void clear();   
    std::vector<Bullet>& getBullets() { return bullets; }
    Bullet& getBullet(int index) { return bullets[index]; }
    void removeBullet(int index) { bullets.erase(bullets.begin() + index); }
    int getChargeEffectCount() const { return static_cast<int>(chargeEffects.size()); }
    int getImpactEffectCount() const { return static_cast<int>(impactEffects.size()); }
    int getAftermathParticleCount() const { return static_cast<int>(aftermathParticles.size()); }
    void reset();

private:
    struct ChargeEffect {
        Vector2 position;
        Vector2 direction;
        ProjectileKind kind;
        bool enemy;
        float elapsed = 0.0f;
    };
    struct ImpactEffect {
        Vector2 position;
        ProjectileKind kind;
        bool enemy;
        float elapsed = 0.0f;
    };
    struct AftermathParticle {
        Vector2 position;
        Vector2 velocity;
        bool enemy;
        float remaining;
    };

    BulletManager() = default;
    std::vector<Bullet> bullets;
    std::vector<ChargeEffect> chargeEffects;
    std::vector<ImpactEffect> impactEffects;
    std::vector<AftermathParticle> aftermathParticles;
};
