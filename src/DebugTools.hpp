#pragma once

#ifdef GAME_DEBUG
#include <string>
#include <vector>

class Player;
class BarricadeEvent;
class SkillSystem;
enum GameState : int;

class DebugTools
{
public:
    void reset();
    void bindSkills(SkillSystem* system) { skills = system; }
    void runCommand(const std::string& command, Player* player, BarricadeEvent* barricade = nullptr);
    void update(Player* player, BarricadeEvent* barricade = nullptr);
    void drawConsole() const;
    bool capturesInput() const { return inputCaptured; }
    void drawWorld(const Player& player) const;
    void drawOverlay(const Player& player, GameState state, const BarricadeEvent& barricade) const;

private:
    friend struct EquipmentTestAccess;
    void execute(Player* player, BarricadeEvent* barricade = nullptr);
    void complete();
    void moveSuggestion(int direction);
    void addOutput(const std::string& line);
    std::vector<std::string> completions() const;

    bool overlayVisible = false;
    SkillSystem* skills = nullptr;
    bool statsVisible = false;
    bool consoleVisible = false;
    bool inputCaptured = false;
    bool audioMuted = false;
    float volumeBeforeMute = 1.0f;
    std::string input;
    std::string historyDraft;
    std::vector<std::string> history;
    std::vector<std::string> output;
    std::size_t historyIndex = 0;
    int selectedSuggestion = -1;
    int suggestionOffset = 0;
};
#endif
