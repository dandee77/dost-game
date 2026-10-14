#pragma once
#include <array>
#include "raylib.h"
#include "DebrisKind.hpp"

// Item 04 introduces only the tokens needed by debug tools; item 03 migrates the rest.
namespace Theme {
    inline constexpr int DEBRIS_FRAME = 96;
    inline constexpr Rectangle DEBRIS_BODY = {30.0f, 30.0f, 36.0f, 36.0f};
    inline constexpr std::array<float, DEBRIS_KIND_COUNT> DEBRIS_DRAW_SIZES = {20.0f, 20.0f, 48.0f, 20.0f, 34.0f, 18.0f, 38.0f, 30.0f, 38.0f, 36.0f};
    // Centers of all 14 flecks in frame 7 (zero-based 6); frame 8 is blank.
    // Extraction notes: assets/source/debris/harvest-handoff.json.
    inline constexpr int DEBRIS_LAST_VISIBLE_FRAME = 6;
    inline constexpr float DEBRIS_DESTRUCT_FRAME_TIME = 0.075f;
    inline constexpr float SCRAP_HANDOFF_TIME = (DEBRIS_LAST_VISIBLE_FRAME + 1) * DEBRIS_DESTRUCT_FRAME_TIME;
    inline constexpr std::array<Vector2, 14> SCRAP_EXIT_PIXELS = {{
        {31.5f, 15.0f}, {46.5f, 20.5f}, {61.5f, 20.0f}, {24.0f, 21.5f},
        {74.833333f, 30.166667f}, {19.0f, 31.3f}, {15.0f, 45.5f}, {74.5f, 47.25f},
        {30.5f, 50.0f}, {58.0f, 61.0f}, {49.25f, 63.5f}, {18.5f, 65.5f},
        {71.5f, 65.5f}, {38.0f, 73.5f}
    }};
    inline constexpr int SCRAP_FRAGMENTS = static_cast<int>(SCRAP_EXIT_PIXELS.size());
    inline constexpr float SCRAP_ORB_SIZE = 2.5f, SCRAP_ORB_HOLD_TIME = 0.05f;
    struct ScrapVisual {
        float orbSize;
        int exitCount;
        std::array<int, SCRAP_FRAGMENTS> exitIndices;
    };
    // Smaller bursts use a spread-out subset of actual final-frame flecks.
    inline constexpr ScrapVisual SCRAP_SMALL = {1.25f, 4, {0, 4, 12, 11}};
    inline constexpr ScrapVisual SCRAP_MEDIUM = {1.8f, 8, {0, 2, 4, 7, 12, 13, 11, 6}};
    inline constexpr ScrapVisual SCRAP_LARGE = {SCRAP_ORB_SIZE, SCRAP_FRAGMENTS,
        {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}};
    // Clump, pipe, wing, canister, dish, coil, tank, thruster, beam, hull.
    inline constexpr std::array<ScrapVisual, DEBRIS_KIND_COUNT> DEBRIS_SCRAP_VISUALS = {{
        SCRAP_SMALL, SCRAP_SMALL, SCRAP_LARGE, SCRAP_SMALL, SCRAP_MEDIUM,
        SCRAP_SMALL, SCRAP_LARGE, SCRAP_MEDIUM, SCRAP_LARGE, SCRAP_LARGE
    }};
    inline constexpr Color COLOR_HARVEST = {255, 65, 75, 255};
    inline constexpr Vector2 SCRAP_HUD_POSITION = {220.0f, 390.0f};
    inline constexpr float SCRAP_HUD_SIZE = 64.0f;
    // The 96px debris frame has a roughly 36px body; account for transparent padding.
    inline constexpr float BARRICADE_DRAW_SIZE = 20.0f, BARRICADE_SPIN = 20.0f;
    inline constexpr float BARRICADE_IDLE_FRAME_TIME = 1.0f;
    inline constexpr float BARRICADE_DESTRUCT_FRAME_TIME = DEBRIS_DESTRUCT_FRAME_TIME;
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
