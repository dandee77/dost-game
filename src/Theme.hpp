#pragma once
#include <array>
#include <span>
#include "raylib.h"
#include "DebrisKind.hpp"

// Item 04 introduces only the tokens needed by debug tools; item 03 migrates the rest.
namespace Theme {
    inline constexpr int DEBRIS_FRAME = 96;
    inline constexpr Rectangle DEBRIS_BODY = {30.0f, 30.0f, 36.0f, 36.0f};
    inline constexpr std::array<float, DEBRIS_KIND_COUNT> DEBRIS_DRAW_SIZES = {20.0f, 20.0f, 48.0f, 20.0f, 34.0f, 18.0f, 38.0f, 30.0f, 38.0f, 36.0f};
    // Each sheet has its own measured final-fleck coordinates. Regenerate with
    // assets/source/debris/write-destruction-metadata.py after exporting art.
    inline constexpr int DEBRIS_LAST_VISIBLE_FRAME = 6;
    inline constexpr float DEBRIS_DESTRUCT_FRAME_TIME = 0.075f;
    inline constexpr float SCRAP_HANDOFF_TIME = (DEBRIS_LAST_VISIBLE_FRAME + 1) * DEBRIS_DESTRUCT_FRAME_TIME;
    inline constexpr float SCRAP_ORB_SIZE = 2.5f, SCRAP_ORB_HOLD_TIME = 0.05f;
    inline constexpr std::array<Vector2, 4> SCRAP_EXIT_CLUMP = {{
        {31.500000f, 15.000000f},
        {74.833333f, 30.166667f},
        {71.500000f, 65.500000f},
        {18.500000f, 65.500000f},
    }};
    inline constexpr std::array<Vector2, 3> SCRAP_EXIT_PIPE = {{
        {26.000000f, 39.700000f},
        {72.000000f, 39.500000f},
        {49.666667f, 49.666667f},
    }};
    inline constexpr std::array<Vector2, 10> SCRAP_EXIT_WING = {{
        {19.000000f, 27.000000f},
        {30.250000f, 30.500000f},
        {25.750000f, 39.500000f},
        {51.100000f, 39.300000f},
        {41.333333f, 40.666667f},
        {51.100000f, 51.700000f},
        {39.666667f, 52.666667f},
        {65.000000f, 55.500000f},
        {75.166667f, 59.166667f},
        {61.666667f, 62.500000f},
    }};
    inline constexpr std::array<Vector2, 5> SCRAP_EXIT_CANISTER = {{
        {53.115385f, 19.884615f},
        {26.250000f, 41.916667f},
        {61.166667f, 52.000000f},
        {84.500000f, 63.300000f},
        {35.000000f, 74.000000f},
    }};
    inline constexpr std::array<Vector2, 5> SCRAP_EXIT_DISH = {{
        {28.884615f, 26.500000f},
        {46.115385f, 45.115385f},
        {75.000000f, 56.666667f},
        {35.200000f, 59.800000f},
        {53.884615f, 67.423077f},
    }};
    inline constexpr std::array<Vector2, 4> SCRAP_EXIT_COIL = {{
        {32.500000f, 30.000000f},
        {67.785714f, 35.000000f},
        {30.000000f, 60.000000f},
        {66.954545f, 66.136364f},
    }};
    inline constexpr std::array<Vector2, 11> SCRAP_EXIT_TANK = {{
        {32.000000f, 22.000000f},
        {56.000000f, 26.000000f},
        {72.500000f, 34.000000f},
        {25.200000f, 39.800000f},
        {16.785714f, 46.500000f},
        {47.300000f, 48.000000f},
        {80.409091f, 48.772727f},
        {66.500000f, 52.700000f},
        {36.441176f, 63.088235f},
        {24.884615f, 64.115385f},
        {57.200000f, 70.800000f},
    }};
    inline constexpr std::array<Vector2, 7> SCRAP_EXIT_THRUSTER = {{
        {48.214286f, 26.500000f},
        {34.500000f, 38.000000f},
        {63.000000f, 42.500000f},
        {39.500000f, 56.500000f},
        {22.611111f, 62.055556f},
        {65.666667f, 61.666667f},
        {51.500000f, 73.500000f},
    }};
    inline constexpr std::array<Vector2, 11> SCRAP_EXIT_BEAM = {{
        {65.000000f, 36.000000f},
        {74.500000f, 40.500000f},
        {83.500000f, 43.500000f},
        {53.833333f, 43.833333f},
        {31.166667f, 46.833333f},
        {50.500000f, 48.000000f},
        {67.300000f, 49.100000f},
        {40.750000f, 53.500000f},
        {20.500000f, 55.250000f},
        {13.100000f, 56.700000f},
        {29.833333f, 59.833333f},
    }};
    inline constexpr std::array<Vector2, 15> SCRAP_EXIT_HULL = {{
        {68.250000f, 22.500000f},
        {31.500000f, 28.214286f},
        {77.500000f, 31.500000f},
        {45.500000f, 36.000000f},
        {21.375000f, 38.375000f},
        {35.000000f, 46.000000f},
        {65.000000f, 46.000000f},
        {57.500000f, 50.500000f},
        {20.750000f, 54.500000f},
        {76.500000f, 54.500000f},
        {35.625000f, 57.625000f},
        {65.500000f, 64.500000f},
        {44.166667f, 66.166667f},
        {78.000000f, 71.500000f},
        {33.333333f, 74.666667f},
    }};
    struct ScrapVisual {
        float orbSize;
        std::span<const Vector2> exitPixels;
    };
    inline constexpr std::array<ScrapVisual, DEBRIS_KIND_COUNT> DEBRIS_SCRAP_VISUALS = {{
        {1.25f, SCRAP_EXIT_CLUMP},
        {1.25f, SCRAP_EXIT_PIPE},
        {2.5f, SCRAP_EXIT_WING},
        {1.25f, SCRAP_EXIT_CANISTER},
        {1.8f, SCRAP_EXIT_DISH},
        {1.25f, SCRAP_EXIT_COIL},
        {2.5f, SCRAP_EXIT_TANK},
        {1.8f, SCRAP_EXIT_THRUSTER},
        {2.5f, SCRAP_EXIT_BEAM},
        {2.5f, SCRAP_EXIT_HULL},
    }};
    inline constexpr Color COLOR_HARVEST = {255, 65, 75, 255};
    inline constexpr Vector2 SCRAP_HUD_POSITION = {220.0f, 390.0f};
    inline constexpr float SCRAP_HUD_SIZE = 64.0f;
    // Original asteroid frame is 96px with a roughly 36px body and transparent padding.
    inline constexpr std::array<float, 3> BARRICADE_DRAW_SIZES = {15.0f, 25.0f, 30.0f};
    inline constexpr int BARRICADE_SPIN_MIN = 5, BARRICADE_SPIN_MAX = 240;
    inline constexpr float BARRICADE_IDLE_FRAME_TIME = 1.0f;
    inline constexpr float BARRICADE_DESTRUCT_FRAME_TIME = DEBRIS_DESTRUCT_FRAME_TIME;
    inline constexpr int FRAMES_DEBRIS_DESTRUCT = 8;
    inline constexpr int BARRICADE_DESTRUCT_FRAMES = 7;
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
