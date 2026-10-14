#include "DebugTools.hpp"

#ifdef GAME_DEBUG
#include "AsteroidManager.hpp"
#include "BulletManager.hpp"
#include "EnemyManager.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "ResourceManager.hpp"
#include "Theme.hpp"

namespace {
    const char* stateName(GameState state)
    {
        switch (state) {
        case GAME_RUNNING: return "GAME_RUNNING";
        case GAME_AUGMENT_SELECTION: return "GAME_AUGMENT_SELECTION";
        case GAME_PAUSED: return "GAME_PAUSED";
        case GAME_OVER: return "GAME_OVER";
        default: return "UNKNOWN";
        }
    }

    void drawHitbox(Font font, Vector2 position, float radius, const char* id, Color color)
    {
        DrawCircleLinesV(position, radius, color);
        DrawTextEx(font, id, Vector2{position.x + radius, position.y},
                   Theme::DEBUG_TEXT_WORLD_ID, Theme::TEXT_SPACING, Fade(color, Theme::DEBUG_TEXT_OPACITY));
    }
}

void DebugTools::reset()
{
    overlayVisible = false;
    statusMessage = "F1: hitboxes and diagnostics";
}

void DebugTools::update(Player& player)
{
    if (IsKeyPressed(KEY_F1)) {
        overlayVisible = !overlayVisible;
        TraceLog(LOG_INFO, "[DebugTools::update] Overlay %s", overlayVisible ? "on" : "off");
    }
    if (IsKeyPressed(KEY_F5)) {
        player.setDebugInvincible(!player.isDebugInvincible());
        TraceLog(LOG_INFO, "[DebugTools::update] Invincibility %s", player.isDebugInvincible() ? "on" : "off");
    }

    // These hooks become gameplay actions in items 11, 12 and 17.
    if (IsKeyPressed(KEY_F3)) {
        statusMessage = "F3 unavailable: scrap (item 12)";
        overlayVisible = true;
        TraceLog(LOG_INFO, "[DebugTools::update] %s", statusMessage);
    }
    if (IsKeyPressed(KEY_F4)) {
        statusMessage = "F4 unavailable: bosses (item 17)";
        overlayVisible = true;
        TraceLog(LOG_INFO, "[DebugTools::update] %s", statusMessage);
    }
    if (IsKeyPressed(KEY_F6)) {
        statusMessage = "F6 unavailable: waves (item 11)";
        overlayVisible = true;
        TraceLog(LOG_INFO, "[DebugTools::update] %s", statusMessage);
    }
}

void DebugTools::drawWorld(const Player& player) const
{
    if (!overlayVisible) return;

    const Font font = ResourceManager::GetInstance().GetFont(Theme::FONT_PRIMARY);
    // Collision checks use width as the radius, not half the sprite width.
    drawHitbox(font, player.getPosition(), player.getHitbox().width, "player", Theme::COLOR_ACCENT);
    for (const auto& [id, enemy] : EnemyManager::GetInstance().getEnemies()) {
        drawHitbox(font, enemy->getPosition(), enemy->getHitbox().width, id.c_str(), Theme::COLOR_TOXIC);
    }
    for (const auto& [id, asteroid] : AsteroidManager::GetInstance().getAsteroids()) {
        drawHitbox(font, asteroid->getPosition(), asteroid->getAsteroidSize(), id.c_str(), Theme::COLOR_TEXT_MUTED);
    }
    // Bullets collide as points. Crosses mark their centers without inventing a radius.
    for (const auto& bullet : BulletManager::GetInstance().getBullets()) {
        const Vector2 position = bullet.getPosition();
        const Color color = bullet.isEnemyBullet() ? Theme::COLOR_DANGER : Theme::COLOR_ACCENT;
        const float halfSize = Theme::DEBUG_POINT_HALF_SIZE;
        DrawLineV(Vector2{position.x - halfSize, position.y}, Vector2{position.x + halfSize, position.y}, color);
        DrawLineV(Vector2{position.x, position.y - halfSize}, Vector2{position.x, position.y + halfSize}, color);
    }
}

void DebugTools::drawOverlay(const Player& player, GameState state) const
{
    if (!overlayVisible && !player.isDebugInvincible()) return;

    const Font font = ResourceManager::GetInstance().GetFont(Theme::FONT_PRIMARY);
    if (player.isDebugInvincible()) {
        DrawTextEx(font, "F5 INVINCIBLE", Theme::DEBUG_INVINCIBLE_POSITION,
                   Theme::TEXT_CAPTION, Theme::TEXT_SPACING, Theme::COLOR_ACCENT);
    }
    if (!overlayVisible) return;

    int playerBullets = 0;
    int enemyBullets = 0;
    for (const auto& bullet : BulletManager::GetInstance().getBullets()) {
        if (bullet.isEnemyBullet()) ++enemyBullets;
        else ++playerBullets;
    }

    DrawRectangleRec(Theme::DEBUG_PANEL, Fade(Theme::COLOR_PANEL, Theme::DEBUG_PANEL_OPACITY));
    Vector2 cursor = {Theme::DEBUG_PANEL.x + Theme::DEBUG_PADDING, Theme::DEBUG_PANEL.y + Theme::DEBUG_PADDING};
    const auto drawLine = [&](const char* text) {
        DrawTextEx(font, text, cursor, Theme::TEXT_CAPTION, Theme::TEXT_SPACING,
                   Fade(Theme::COLOR_TEXT, Theme::DEBUG_TEXT_OPACITY));
        cursor.y += Theme::DEBUG_LINE_HEIGHT;
    };
    drawLine(TextFormat("DEBUG | FPS %d | HP %d", GetFPS(), player.getHealth()));
    drawLine(stateName(state));
    drawLine(TextFormat("Enemies %d | Asteroids %d",
        static_cast<int>(EnemyManager::GetInstance().getEnemies().size()),
        static_cast<int>(AsteroidManager::GetInstance().getAsteroids().size())));
    drawLine(TextFormat("Bullets: player %d | enemy %d", playerBullets, enemyBullets));
    drawLine(TextFormat("F5 Invincibility: %s", player.isDebugInvincible() ? "ON" : "OFF"));
    drawLine("Wave / phase / budget: unavailable");
    drawLine(TextFormat("F2 Audio: %s", GetMasterVolume() == 0.0f ? "MUTED" : "ON"));
    drawLine("F3 Credits / cargo: pending scrap");
    drawLine("F4 Next boss: pending bosses");
    drawLine("F6 Next wave: pending waves");
    drawLine("Bullets: point markers");
    drawLine(statusMessage);
}
#endif
