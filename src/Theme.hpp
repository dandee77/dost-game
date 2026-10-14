#pragma once
#include "raylib.h"

// Item 04 introduces only the tokens needed by debug tools; item 03 migrates the rest.
namespace Theme {
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
    inline constexpr Rectangle DEBUG_PANEL = {220.0f, 450.0f, 1480.0f, 800.0f};
    inline constexpr Vector2 DEBUG_INVINCIBLE_POSITION = {220.0f, 360.0f};
    inline constexpr float DEBUG_PADDING = 30.0f;
    inline constexpr float DEBUG_LINE_HEIGHT = 64.0f;
    inline constexpr float DEBUG_POINT_HALF_SIZE = 0.6f;
    inline constexpr int DEBUG_WINDOW_FPS_X = 10;
    inline constexpr int DEBUG_WINDOW_FPS_Y = 10;
}
