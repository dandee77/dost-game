#include "GameTimer.hpp"
#include "ResourceManager.hpp"
#include <string>
#include <cmath>

GameTimer::GameTimer() = default;

void GameTimer::start() {
    elapsed = 0.0f;
    started = running = true;
}

void GameTimer::pause() {
    running = false;
}

void GameTimer::unpause() {
    if (started) running = true;
}

int GameTimer::setStartTime(float time) {
    if (time < 0.0f || !std::isfinite(time)) return -1;
    elapsed = time;
    started = running = true;
    return 0; // Success
}

void GameTimer::reset() {
    elapsed = 0.0f;
    started = running = false;
}

void GameTimer::update(float dt) {
    if (running && dt > 0.0f && std::isfinite(dt)) elapsed += dt;
}

float GameTimer::getElapsedTime() const {
    return elapsed;
}

std::string GameTimer::getElapsedTimeString() const {
    int totalSeconds = static_cast<int>(getElapsedTime());
    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;
    return std::to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + std::to_string(seconds);
}

void GameTimer::draw(int screenWidth) {
    const int fontSize = 80;
    const float padding = 150.0f;

    Vector2 screenPos = {screenWidth / 2.0f, padding};

    std::string timeText = getElapsedTimeString();

    Font font = ResourceManager::GetInstance().GetFont("primary_font");
    Vector2 textSize = MeasureTextEx(font, timeText.c_str(), fontSize, 1.0f);

    screenPos.x -= textSize.x / 2.0f;

    Rectangle textRect = {
        screenPos.x - 10,
        screenPos.y - 5,
        textSize.x + 20,
        textSize.y + 10
    };

    // bg tint
    // DrawRectangleRounded(textRect, 0.3f, 5, Fade(BLACK, 0.6f));
    
    DrawTextEx(
        font,
        timeText.c_str(),
        Vector2{screenPos.x, screenPos.y},
        fontSize,
        1.0f,
        WHITE
    );

    // border
    // DrawRectangleRoundedLines(textRect, 0.3f, 5, Fade(WHITE, 0.8f));
}
