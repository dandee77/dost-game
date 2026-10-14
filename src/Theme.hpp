#pragma once
#include <array>
#include "raylib.h"
#include "DebrisKind.hpp"

// Item 04 introduces only the tokens needed by debug tools; item 03 migrates the rest.
namespace Theme {
    inline constexpr int DEBRIS_FRAME = 96;
    inline constexpr Rectangle DEBRIS_BODY = {30.0f, 30.0f, 36.0f, 36.0f};
    inline constexpr std::array<float, DEBRIS_KIND_COUNT> DEBRIS_DRAW_SIZES = {20.0f, 20.0f, 48.0f, 20.0f, 34.0f, 18.0f, 38.0f, 30.0f, 38.0f, 36.0f};
    inline constexpr int SCRAP_COLUMNS = 8, SCRAP_ROWS = 1;
    inline constexpr int SCRAP_FRAGMENTS = SCRAP_COLUMNS * SCRAP_ROWS;
    inline constexpr float SCRAP_SPIN = 180.0f, SCRAP_GLOW_SIZE = 1.1f;
    inline constexpr std::array<float, 3> SCRAP_GLOW_SCALES = {3.0f, 2.0f, 1.0f};
    inline constexpr std::array<float, 3> SCRAP_GLOW_ALPHAS = {0.10f, 0.22f, 0.5f};
    inline constexpr Color COLOR_HARVEST = {255, 65, 75, 255};
    inline constexpr Color COLOR_HARVEST_CORE = {255, 195, 180, 255};
    inline constexpr Vector2 SCRAP_HUD_POSITION = {220.0f, 390.0f};
    inline constexpr float SCRAP_HUD_SIZE = 64.0f;
    // The 96px debris frame has a roughly 36px body; account for transparent padding.
    inline constexpr float BARRICADE_DRAW_SIZE = 20.0f, BARRICADE_SPIN = 20.0f;
    inline constexpr float BARRICADE_IDLE_FRAME_TIME = 1.0f;
    inline constexpr float BARRICADE_DESTRUCT_FRAME_TIME = 0.1f;
    inline constexpr int FRAMES_DEBRIS_DESTRUCT = 8;
    inline constexpr int BARRICADE_DESTRUCT_FRAMES = FRAMES_DEBRIS_DESTRUCT;
    inline constexpr Vector2 BARRICADE_STATUS_POSITION = {1350.0f, 270.0f};
    inline constexpr float BARRICADE_STATUS_SIZE = 40.0f;
    inline constexpr float ORIGINAL_PLAYER_SIZE = 8.0f;
    inline constexpr int ORIGINAL_PLAYER_FRAME = 32;
    inline constexpr float ORIGINAL_PLAYER_FRAME_TIME = 0.1f;
    inline constexpr float PLAYER_LAYER_SIZE = 12.0f;
    inline constexpr float PLAYER_SHIELD_SIZE = 16.0f;
    inline constexpr int PLAYER_LAYER_FRAME = 48, PLAYER_SHIELD_FRAME = 64;
    inline constexpr int PROJECTILE_FRAME = 32;
    inline constexpr float EQUIPMENT_FRAME_TIME = 0.06f;
    inline constexpr float EQUIPMENT_FLASH_TIME = 0.15f;
    inline constexpr float HURT_FLASH_RATE = 6.0f;
    inline constexpr float CANNON_DRAW_SIZE = 6.0f, HEAVY_DRAW_SIZE = 8.0f, ROCKET_DRAW_SIZE = 6.0f;
    inline constexpr float LASER_TILE_LENGTH = 8.0f;
    inline constexpr float LASER_SOURCE_X = 13.0f, LASER_SOURCE_WIDTH = 6.0f;
    inline constexpr float EXPLOSION_TIME = 0.25f;
    inline constexpr float SHIELD_EMPTY_OPACITY = 0.15f, SHIELD_MIN_OPACITY = 0.35f;
    inline constexpr Vector2 EQUIPMENT_STATUS_POSITION = {2300.0f, 350.0f};
    inline constexpr float EQUIPMENT_STATUS_LINE = 60.0f;
    inline constexpr int EQUIPMENT_RING_SEGMENTS = 48;
    inline constexpr float DEBUG_OUTLINE_WIDTH = 0.15f;
    inline constexpr const char* FONT_PRIMARY = "primary_font";
    inline constexpr float TEXT_CAPTION = 50.0f;
    // Smaller than tutorial labels so IDs remain legible in the 30+ enemy overlay.
    inline constexpr float DEBUG_TEXT_WORLD_ID = 2.0f;
    inline constexpr float TEXT_SPACING = 0.0f;
    inline constexpr Color COLOR_TEXT = RAYWHITE;
    inline constexpr Color COLOR_TEXT_MUTED = {128, 128, 128, 255};
    inline constexpr Color COLOR_ACCENT = SKYBLUE;
    inline constexpr Color COLOR_DANGER = {255, 50, 50, 255};
    inline constexpr Color COLOR_TOXIC = {120, 255, 90, 255};
    inline constexpr Color COLOR_PANEL = {20, 20, 30, 255};
    inline constexpr float DEBUG_TEXT_OPACITY = 0.55f;
    inline constexpr float DEBUG_PANEL_OPACITY = 0.25f;
    inline constexpr Rectangle DEBUG_CONSOLE_PANEL = {220.0f, 310.0f, 2000.0f, 720.0f};
    inline constexpr float DEBUG_CONSOLE_OPACITY = 0.92f;
    inline constexpr Rectangle DEBUG_PANEL = {220.0f, 1060.0f, 1700.0f, 768.0f};
    inline constexpr Vector2 DEBUG_INVINCIBLE_POSITION = {220.0f, 1850.0f};
    inline constexpr float DEBUG_CONSOLE_TEXT_OPACITY = 0.85f;
    inline constexpr float DEBUG_PADDING = 30.0f;
    inline constexpr float DEBUG_LINE_HEIGHT = 64.0f;
    inline constexpr int DEBUG_SUGGESTION_ROWS = 6;
    inline constexpr float DEBUG_DROPDOWN_OPACITY = 0.95f;
    inline constexpr float DEBUG_SELECTION_OPACITY = 0.22f;
    inline constexpr float DEBUG_POINT_HALF_SIZE = 0.6f;
    inline constexpr int DEBUG_WINDOW_FPS_X = 10;
    inline constexpr int DEBUG_WINDOW_FPS_Y = 10;
}
