#pragma once
#include "raylib.h"
#include <string>

class GameTimer
{
private:
    float elapsed = 0.0f;
    bool running = false;
    bool started = false;

public:
    GameTimer();

    void start();
    void pause();
    void unpause();
    void reset();
    void update(float dt);

    int setStartTime(float time);

    float getElapsedTime() const;
    std::string getElapsedTimeString() const;
    bool isRunning() const { return running; }

    void draw(int screenWidth); 
};
