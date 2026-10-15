#include "BulletManager.hpp"
#include "Config.hpp"
#include "ResourceManager.hpp"
#include "Theme.hpp"
#include "raymath.h"
#include <algorithm>
#include <cmath>

namespace {
    template<typename T>
    void keepEffectCapacity(std::vector<T>& effects)
    {
        if (effects.size() >= Config::PROJECTILE_EFFECT_LIMIT) effects.erase(effects.begin());
    }
}

void BulletManager::update(Vector2 position)
{
    const float dt = GetFrameTime();
    for (int index = 0; index < static_cast<int>(bullets.size()); ++index) {
        const float distance = Vector2Distance(bullets[index].getPosition(), position);
        if (distance > BULLET_DESPAWN_DISTANCE) {
            bullets.erase(bullets.begin() + index--);
            continue;
        }
        bullets[index].update();
    }

    for (auto& effect : chargeEffects) effect.elapsed += dt;
    std::erase_if(chargeEffects, [](const ChargeEffect& effect) {
        return effect.elapsed >= Theme::PROJECTILE_CHARGE_TIME;
    });
    for (auto& effect : impactEffects) effect.elapsed += dt;
    std::erase_if(impactEffects, [](const ImpactEffect& effect) {
        return effect.elapsed >= Theme::PROJECTILE_IMPACT_FRAMES * Theme::PROJECTILE_IMPACT_FRAME_TIME;
    });
    for (auto& particle : aftermathParticles) {
        particle.position = Vector2Add(particle.position, Vector2Scale(particle.velocity, dt));
        particle.velocity = Vector2Scale(particle.velocity, std::exp(-Theme::PROJECTILE_PARTICLE_DRAG * dt));
        particle.remaining -= dt;
    }
    std::erase_if(aftermathParticles, [](const AftermathParticle& particle) {
        return particle.remaining <= 0.0f;
    });
}

void BulletManager::draw(const Texture2D& playerBulletTexture, const Texture2D& enemyBulletTexture) const
{
    for (const auto& effect : chargeEffects) {
        const float fraction = effect.elapsed / Theme::PROJECTILE_CHARGE_TIME;
        const float kindScale = effect.kind == PROJECTILE_HEAVY ? Theme::PROJECTILE_HEAVY_SCALE :
            effect.kind == PROJECTILE_ROCKET ? Theme::PROJECTILE_ROCKET_SCALE : 1.0f;
        const Color color = effect.enemy ? Theme::COLOR_TOXIC : Theme::COLOR_ACCENT;
        const Vector2 center = Vector2Add(effect.position,
            Vector2Scale(effect.direction, Theme::PROJECTILE_CHARGE_SIZE * fraction));
        const float radius = Theme::PROJECTILE_CHARGE_SIZE * kindScale *
            (1.0f - Theme::PROJECTILE_CHARGE_COLLAPSE * fraction);
        DrawRing(center, radius, radius + Theme::PROJECTILE_TRAIL_WIDTH, 0.0f, 360.0f,
            Theme::PROJECTILE_RING_SEGMENTS, Fade(color, 1.0f - fraction));
    }
    for (const auto& bullet : bullets) {
        bullet.draw(bullet.isEnemyBullet() ? enemyBulletTexture : playerBulletTexture);
    }

    const auto& impactSheet = ResourceManager::GetInstance().GetTextureRef("projectile_impact");
    for (const auto& effect : impactEffects) {
        const int frame = std::min(Theme::PROJECTILE_IMPACT_FRAMES - 1,
            static_cast<int>(effect.elapsed / Theme::PROJECTILE_IMPACT_FRAME_TIME));
        const float size = effect.kind == PROJECTILE_HEAVY ? Theme::PROJECTILE_HEAVY_IMPACT_SIZE :
            Theme::PROJECTILE_IMPACT_SIZE;
        if (!effect.enemy && impactSheet.id != 0) {
            DrawTexturePro(impactSheet,
                {static_cast<float>(frame * Theme::PROJECTILE_IMPACT_FRAME), 0.0f,
                 static_cast<float>(Theme::PROJECTILE_IMPACT_FRAME), static_cast<float>(Theme::PROJECTILE_IMPACT_FRAME)},
                {effect.position.x, effect.position.y, size, size}, {size / 2.0f, size / 2.0f}, 0.0f, WHITE);
        } else {
            const float fraction = effect.elapsed /
                (Theme::PROJECTILE_IMPACT_FRAMES * Theme::PROJECTILE_IMPACT_FRAME_TIME);
            DrawRing(effect.position, size * Theme::PROJECTILE_IMPACT_RING_START,
                size * (Theme::PROJECTILE_IMPACT_RING_START + Theme::PROJECTILE_IMPACT_RING_GROWTH * fraction),
                0.0f, 360.0f,
                Theme::PROJECTILE_RING_SEGMENTS, Fade(Theme::COLOR_TOXIC, 1.0f - fraction));
        }
    }
    for (const auto& particle : aftermathParticles) {
        const float fraction = std::max(0.0f, particle.remaining / Theme::PROJECTILE_PARTICLE_TIME);
        DrawCircleV(particle.position, Theme::PROJECTILE_PARTICLE_SIZE * fraction,
            Fade(particle.enemy ? Theme::COLOR_TOXIC : Theme::COLOR_ACCENT, fraction));
    }
}

void BulletManager::addBullet(Bullet bullet)
{
    keepEffectCapacity(chargeEffects);
    chargeEffects.push_back({bullet.getPosition(), bullet.getDirection(), bullet.getKind(), bullet.isEnemyBullet()});
    bullets.push_back(bullet);
}

void BulletManager::spawnImpact(Vector2 position, ProjectileKind kind, bool enemy, Vector2 direction)
{
    keepEffectCapacity(impactEffects);
    impactEffects.push_back({position, kind, enemy});
    for (int index = 0; index < Theme::PROJECTILE_PARTICLE_COUNT; ++index) {
        keepEffectCapacity(aftermathParticles);
        const float spread = static_cast<float>(GetRandomValue(
            -Theme::PROJECTILE_PARTICLE_SPREAD, Theme::PROJECTILE_PARTICLE_SPREAD)) * DEG2RAD;
        const float speed = static_cast<float>(GetRandomValue(
            Theme::PROJECTILE_PARTICLE_SPEED_MIN, Theme::PROJECTILE_PARTICLE_SPEED_MAX));
        const Vector2 away = Vector2Rotate(Vector2Negate(direction), spread);
        aftermathParticles.push_back({position, Vector2Scale(away, speed), enemy,
            Theme::PROJECTILE_PARTICLE_TIME});
    }
    Sound sound = ResourceManager::GetInstance().GetSound("bullet_impact");
    if (!enemy && sound.stream.buffer != nullptr && !IsSoundPlaying(sound)) PlaySound(sound);
}

void BulletManager::clear() { reset(); }

void BulletManager::reset()
{
    bullets.clear();
    chargeEffects.clear();
    impactEffects.clear();
    aftermathParticles.clear();
}
