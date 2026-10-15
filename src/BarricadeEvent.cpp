#include "BarricadeEvent.hpp"
#include "Balance.hpp"
#include "Bullet.hpp"
#include "Config.hpp"
#include "EnemyManager.hpp"
#include "Player.hpp"
#include "ResourceManager.hpp"
#include "Scene.hpp"
#include "Theme.hpp"
#include "Utils.hpp"
#include "raymath.h"
#include <algorithm>
#include <cmath>

bool BarricadeEvent::start(Vector2 playerPosition)
{
    if (isActive()) return false;
    auto ids = EnemyManager::GetInstance().spawnBarricade(playerPosition);
    if (ids.empty()) return false; // Never create a partial ring at the population cap.
    segmentIds = std::move(ids);
    center = playerPosition;
    elapsed = 0.0f;
    phase = BARRICADE_CONTAINING;
    TraceLog(LOG_INFO, "[BarricadeEvent::start] Barricade enclosing player");
    return true;
}

void BarricadeEvent::update(float dt, float runTime, Vector2 playerPosition)
{
    if (!automaticTriggered && runTime >= Balance::BARRICADE_TRIGGER_TIME) {
        if (isActive() || start(playerPosition)) automaticTriggered = true;
    }
    if (!isActive()) return;
    elapsed += std::max(0.0f, dt);
    if (getAliveSegments() == 0 || elapsed >= Balance::BARRICADE_DURATION + Balance::BARRICADE_SCATTER_TIME) {
        clearSegments();
        return;
    }
    if (elapsed >= Balance::BARRICADE_DURATION && phase == BARRICADE_CONTAINING) {
        phase = BARRICADE_SCATTERING;
        TraceLog(LOG_INFO, "[BarricadeEvent::update] Barricade scattering");
    }
}

bool BarricadeEvent::constrainPlayer(Player& player, Vector2 previousPosition) const
{
    if (!isContaining() || player.getHealth() <= 0) return false;
    const auto& enemies = EnemyManager::GetInstance().getEnemies();
    const float playerRadius = player.getHitbox().width;
    float earliest = 2.0f;
    const Enemy* contact = nullptr;
    Vector2 normal = {};
    Vector2 corrected = player.getPosition();
    // Relative sweep catches boosts, long frames and an inward-moving wall.
    for (const auto& id : segmentIds) {
        const auto found = enemies.find(id);
        if (found == enemies.end() || found->second->isDead()) continue;
        const auto& segment = *found->second;
        const float radius = playerRadius + segment.getHitbox().width;
        const Vector2 from = Vector2Subtract(previousPosition, segment.getPreviousPosition());
        const Vector2 to = Vector2Subtract(player.getPosition(), segment.getPosition());
        const float hit = Bullet::hitFraction(from, to, {}, radius);
        if (hit < 0.0f || hit >= earliest) continue;
        earliest = hit;
        contact = &segment;
        normal = Vector2Normalize(Vector2Lerp(from, to, hit));
        if (Vector2LengthSqr(normal) < Config::TIMER_EPSILON)
            normal = Vector2Normalize(Vector2Subtract(center, segment.getPosition()));
    }
    if (!contact) return false;
    corrected = Vector2Add(contact->getPosition(), Vector2Scale(normal,
        playerRadius + contact->getHitbox().width + Config::BARRICADE_CONTACT_SKIN));
    // Resolve neighboring disks at seams without allowing a gap between intact rocks.
    for (int pass = 0; pass < Config::BARRICADE_CONTACT_PASSES; ++pass) {
        bool moved = false;
        for (const auto& id : segmentIds) {
            const auto found = enemies.find(id);
            if (found == enemies.end() || found->second->isDead()) continue;
            const auto& segment = *found->second;
            const float radius = playerRadius + segment.getHitbox().width;
            const Vector2 offset = Vector2Subtract(corrected, segment.getPosition());
            const float distance = Vector2Length(offset);
            if (distance >= radius) continue;
            normal = distance > Config::TIMER_EPSILON ? Vector2Scale(offset, 1.0f / distance) :
                Vector2Normalize(Vector2Subtract(center, segment.getPosition()));
            corrected = Vector2Add(segment.getPosition(), Vector2Scale(normal, radius + Config::BARRICADE_CONTACT_SKIN));
            moved = true;
        }
        if (!moved) break;
    }
    // At a seam, the last disk's tangent can point toward its neighbor. Interior
    // impacts should bounce into the arena instead of rattling between rocks.
    if (Vector2Distance(previousPosition, center) <= Vector2Distance(contact->getPreviousPosition(), center))
        normal = Vector2Normalize(Vector2Subtract(center, corrected));
    player.resolveBarricadeContact(corrected, normal, contact->getPosition());
    return true;
}

void BarricadeEvent::finishIfEscaped(Vector2 playerPosition, const Camera2D& camera)
{
    if (!isActive()) return;
    const float radius = getRadius();
    if (Vector2Distance(playerPosition, center) <= radius + Balance::BARRICADE_ESCAPE_MARGIN) return;
    // Require both distance and the whole ring to leave the view, not just one missing rock.
    const float maxDrawSize = *std::max_element(Theme::BARRICADE_DRAW_SIZES.begin(), Theme::BARRICADE_DRAW_SIZES.end());
    const float extent = (radius + maxDrawSize / 2.0f) * camera.zoom;
    const Vector2 screenCenter = GetWorldToScreen2D(center, camera);
    if (screenCenter.x + extent < 0.0f || screenCenter.x - extent > GAME_SCREEN_WIDTH ||
        screenCenter.y + extent < 0.0f || screenCenter.y - extent > GAME_SCREEN_HEIGHT) clearSegments();
}

void BarricadeEvent::clearSegments()
{
    auto& enemies = EnemyManager::GetInstance().getEnemies();
    for (const auto& id : segmentIds) {
        enemies.erase(id);
        Animator::GetInstance().Remove(id);
    }
    segmentIds.clear();
    phase = BARRICADE_IDLE;
    elapsed = 0.0f;
}

void BarricadeEvent::reset()
{
    clearSegments();
    automaticTriggered = false;
    center = {};
}

void BarricadeEvent::drawStatus() const
{
    if (!isActive()) return;
    const char* label = isContaining() ? TextFormat("BARRICADE %ds - BREAK A GAP",
        static_cast<int>(std::ceil(Balance::BARRICADE_DURATION - elapsed))) : "BARRICADE DISPERSING";
    DrawTextEx(ResourceManager::GetInstance().GetFont(Theme::FONT_PRIMARY), label,
        Theme::BARRICADE_STATUS_POSITION, Theme::BARRICADE_STATUS_SIZE, Theme::TEXT_SPACING, Theme::COLOR_ACCENT);
}

float BarricadeEvent::getRadius() const
{
    if (!isActive()) return 0.0f;
    return Lerp(Balance::BARRICADE_START_RADIUS, Balance::BARRICADE_END_RADIUS,
        std::min(1.0f, elapsed / Balance::BARRICADE_DURATION)) +
        std::max(0.0f, elapsed - Balance::BARRICADE_DURATION) * Balance::BARRICADE_SCATTER_SPEED;
}

int BarricadeEvent::getAliveSegments() const
{
    const auto& enemies = EnemyManager::GetInstance().getEnemies();
    return static_cast<int>(std::count_if(segmentIds.begin(), segmentIds.end(), [&](const auto& id) {
        const auto found = enemies.find(id);
        return found != enemies.end() && !found->second->isDead();
    }));
}
