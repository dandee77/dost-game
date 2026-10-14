#pragma once

#ifdef GAME_DEBUG
class Player;
enum GameState : int;

class DebugTools
{
public:
    void reset();
    void update(Player& player);
    void drawWorld(const Player& player) const;
    void drawOverlay(const Player& player, GameState state) const;

private:
    bool overlayVisible = false;
    const char* statusMessage = "F1: hitboxes and diagnostics";
};
#endif
