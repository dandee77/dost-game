#include "DebugTools.hpp"

#ifdef GAME_DEBUG
#include <algorithm>
#include <array>
#include <cctype>
#include <charconv>
#include <sstream>

#include "Config.hpp"
#include "Balance.hpp"
#include "DebrisManager.hpp"
#include "BulletManager.hpp"
#include "EnemyManager.hpp"
#include "Game.hpp"
#include "Player.hpp"
#include "ResourceManager.hpp"
#include "Theme.hpp"

namespace {
    enum DebugCommand { DEBUG_HELP, DEBUG_HITBOX, DEBUG_STATS, DEBUG_MUTE, DEBUG_INVINCIBLE,
                        DEBUG_CREDITS, DEBUG_BOSS, DEBUG_WAVE, DEBUG_CLEAR, DEBUG_CLOSE, DEBUG_PLAYER, DEBUG_SPAWN };
    enum EquipmentCommand { EQUIP_BUILD, EQUIP_WEAPON, EQUIP_ENGINE, EQUIP_SHIELD };
    struct EquipmentInfo { const char* text; EquipmentCommand command; int value; };
    constexpr std::array equipmentCommands = {
        EquipmentInfo{"default build", EQUIP_BUILD, BUILD_DEFAULT},
        EquipmentInfo{"gunner build", EQUIP_BUILD, BUILD_GUNNER},
        EquipmentInfo{"cannon build", EQUIP_BUILD, BUILD_CANNON},
        EquipmentInfo{"laser build", EQUIP_BUILD, BUILD_LASER},
        EquipmentInfo{"rockets build", EQUIP_BUILD, BUILD_ROCKETS},
        EquipmentInfo{"heavy build", EQUIP_BUILD, BUILD_HEAVY},
        EquipmentInfo{"weapon cannon", EQUIP_WEAPON, WEAPON_CANNON},
        EquipmentInfo{"weapon laser", EQUIP_WEAPON, WEAPON_LASER},
        EquipmentInfo{"weapon rockets", EQUIP_WEAPON, WEAPON_ROCKETS},
        EquipmentInfo{"weapon heavy", EQUIP_WEAPON, WEAPON_HEAVY},
        EquipmentInfo{"engine base", EQUIP_ENGINE, ENGINE_BASE},
        EquipmentInfo{"engine pulse", EQUIP_ENGINE, ENGINE_PULSE},
        EquipmentInfo{"engine burst", EQUIP_ENGINE, ENGINE_BURST},
        EquipmentInfo{"engine supercharged", EQUIP_ENGINE, ENGINE_SUPERCHARGED},
        EquipmentInfo{"shield none", EQUIP_SHIELD, SHIELD_NONE},
        EquipmentInfo{"shield front", EQUIP_SHIELD, SHIELD_FRONT},
        EquipmentInfo{"shield sides", EQUIP_SHIELD, SHIELD_SIDES},
        EquipmentInfo{"shield round", EQUIP_SHIELD, SHIELD_ROUND},
        EquipmentInfo{"shield invincibility", EQUIP_SHIELD, SHIELD_INVINCIBILITY}
    };
    struct CommandInfo {
        const char* name;
        DebugCommand command;
        bool toggle;
        bool requiresPlayer;
    };
    constexpr std::array commands = {
        CommandInfo{"help", DEBUG_HELP, false, false},
        CommandInfo{"player", DEBUG_PLAYER, false, true},
        CommandInfo{"spawn", DEBUG_SPAWN, false, true},
        CommandInfo{"hitbox", DEBUG_HITBOX, true, true},
        CommandInfo{"stats", DEBUG_STATS, true, true},
        CommandInfo{"mute", DEBUG_MUTE, true, false},
        CommandInfo{"invincible", DEBUG_INVINCIBLE, true, true},
        CommandInfo{"credits", DEBUG_CREDITS, false, true},
        CommandInfo{"boss", DEBUG_BOSS, false, true},
        CommandInfo{"wave", DEBUG_WAVE, false, true},
        CommandInfo{"clear", DEBUG_CLEAR, false, false},
        CommandInfo{"close", DEBUG_CLOSE, false, false}
    };

    bool pressedOrRepeated(int key)
    {
        return IsKeyPressed(key) || IsKeyPressedRepeat(key);
    }

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
    statsVisible = false;
    consoleVisible = false;
    inputCaptured = false;
    input.clear();
    historyDraft.clear();
    history.clear();
    historyIndex = 0;
    selectedSuggestion = -1;
    suggestionOffset = 0;
    output.clear();
    // Master audio is a session preference and survives new runs.
}

void DebugTools::update(Player* player, BarricadeEvent* barricade)
{
    // Capture the closing frame too: Escape, Enter and mouse clicks must not leak.
    inputCaptured = consoleVisible;
    if (IsKeyPressed(KEY_F5)) consoleVisible = !consoleVisible;
    inputCaptured = inputCaptured || consoleVisible;
    if (!inputCaptured) return;

    if (IsKeyPressed(KEY_ESCAPE)) consoleVisible = false;
    const std::string previousInput = input;
    for (int character = GetCharPressed(); character != 0; character = GetCharPressed()) {
        // The command language is ASCII. Drain unsupported characters as well.
        if (consoleVisible && character >= ' ' && character <= '~' && input.size() < Config::DEBUG_INPUT_LIMIT) {
            input += static_cast<char>(std::tolower(static_cast<unsigned char>(character)));
        }
    }
    if (!consoleVisible) return;

    if (pressedOrRepeated(KEY_BACKSPACE) && !input.empty()) input.pop_back();
    if (input != previousInput) { selectedSuggestion = -1; suggestionOffset = 0; }
    const bool browsingHistory = input.empty() || IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL);
    if (!browsingHistory && !completions().empty()) {
        if (pressedOrRepeated(KEY_UP)) moveSuggestion(-1);
        if (pressedOrRepeated(KEY_DOWN)) moveSuggestion(1);
        if (pressedOrRepeated(KEY_PAGE_UP)) moveSuggestion(-Theme::DEBUG_SUGGESTION_ROWS);
        if (pressedOrRepeated(KEY_PAGE_DOWN)) moveSuggestion(Theme::DEBUG_SUGGESTION_ROWS);
    }
    if (browsingHistory && IsKeyPressed(KEY_UP) && historyIndex > 0) {
        if (historyIndex == history.size()) historyDraft = input;
        input = history[--historyIndex];
        selectedSuggestion = -1; suggestionOffset = 0;
    }
    if (browsingHistory && IsKeyPressed(KEY_DOWN) && historyIndex < history.size()) {
        ++historyIndex;
        input = historyIndex == history.size() ? historyDraft : history[historyIndex];
        selectedSuggestion = -1; suggestionOffset = 0;
    }
    if (IsKeyPressed(KEY_TAB)) complete();
    if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_KP_ENTER)) {
        if (selectedSuggestion >= 0) complete();
        else execute(player, barricade);
    }
}

void DebugTools::addOutput(const std::string& line)
{
    if (output.size() == Config::DEBUG_OUTPUT_LINES) output.erase(output.begin());
    output.push_back(line);
}

std::vector<std::string> DebugTools::completions() const
{
    std::vector<std::string> matches;
    if (input.starts_with("spawn ")) {
        for (const std::string prefix : {"spawn lowlevel enemy ", "spawn barricade event", "spawn debris all"})
            if (prefix.starts_with(input)) matches.push_back(prefix);
        return matches;
    }
    if (input.starts_with("player ")) {
        for (const auto& option : equipmentCommands) {
            const std::string candidate = std::string("player ") + option.text;
            if (candidate.starts_with(input)) matches.push_back(candidate);
        }
        return matches;
    }
    for (const auto& command : commands) {
        const std::string name = command.name;
        if (name.starts_with(input)) matches.push_back(name);
        if (command.toggle && input.starts_with(name + " ")) {
            for (const char* value : {"on", "off", "toggle"}) {
                const std::string candidate = name + " " + value;
                if (candidate.starts_with(input)) matches.push_back(candidate);
            }
        }
    }
    return matches;
}

void DebugTools::complete()
{
    const auto matches = completions();
    if (matches.empty()) return;
    if (selectedSuggestion >= 0 && selectedSuggestion < static_cast<int>(matches.size())) {
        input = matches[selectedSuggestion];
        selectedSuggestion = -1;
        suggestionOffset = 0;
        return;
    }
    std::string prefix = matches.front();
    for (const auto& match : matches) {
        while (!match.starts_with(prefix)) prefix.pop_back();
    }
    if (prefix.size() > input.size()) { input = prefix; suggestionOffset = 0; }
    else moveSuggestion(1);
}

void DebugTools::moveSuggestion(int direction)
{
    const int count = static_cast<int>(completions().size());
    if (count == 0) { selectedSuggestion = -1; suggestionOffset = 0; return; }
    if (selectedSuggestion < 0) selectedSuggestion = direction < 0 ? count - 1 : 0;
    else selectedSuggestion = ((selectedSuggestion + direction) % count + count) % count;
    if (selectedSuggestion < suggestionOffset) suggestionOffset = selectedSuggestion;
    if (selectedSuggestion >= suggestionOffset + Theme::DEBUG_SUGGESTION_ROWS)
        suggestionOffset = selectedSuggestion - Theme::DEBUG_SUGGESTION_ROWS + 1;
}

void DebugTools::execute(Player* player, BarricadeEvent* barricade)
{
    selectedSuggestion = -1;
    suggestionOffset = 0;
    std::istringstream stream(input);
    std::string name;
    std::string argument;
    std::string extra;
    stream >> name >> argument >> extra;
    if (name.empty()) {
        input.clear();
        return;
    }
    addOutput("> " + input);
    if (history.empty() || history.back() != input) {
        if (history.size() == Config::DEBUG_HISTORY_LIMIT) history.erase(history.begin());
        history.push_back(input);
    }
    historyIndex = history.size();
    historyDraft.clear();
    input.clear();

    const auto found = std::find_if(commands.begin(), commands.end(), [&](const CommandInfo& command) {
        return name == command.name;
    });
    if (found == commands.end()) {
        addOutput("Unknown command. Type help or press Tab.");
        return;
    }
    if (found->command != DEBUG_PLAYER && found->command != DEBUG_SPAWN && (!extra.empty() || (!found->toggle && !argument.empty()) ||
        (found->toggle && !argument.empty() && argument != "on" && argument != "off" && argument != "toggle"))) {
        addOutput("Usage: " + name + (found->toggle ? " [on|off|toggle]" : ""));
        return;
    }
    if (found->requiresPlayer && player == nullptr) {
        addOutput("Start a run to use " + name + ".");
        return;
    }
    const auto toggleValue = [&](bool current) {
        if (argument == "on") return true;
        if (argument == "off") return false;
        return !current;
    };
    switch (found->command) {
    case DEBUG_SPAWN: {
        std::string quantityText, trailing;
        stream >> quantityText >> trailing;
        if (argument == "debris" && extra == "all" && quantityText.empty() && trailing.empty()) {
            if (player->getHealth() <= 0) { addOutput("Restart the run before spawning debris."); break; }
            DebrisManager::GetInstance().spawnGallery(player->getPosition());
            addOutput("Spawned all 10 debris variants. Shoot them to harvest scrap.");
            break;
        }
        if (argument == "barricade" && extra == "event" && quantityText.empty() && trailing.empty()) {
            if (!barricade || player->getHealth() <= 0) { addOutput("Start a living run before spawning an event."); break; }
            if (barricade->isActive()) { addOutput("A barricade event is already active."); break; }
            addOutput(barricade->start(player->getPosition()) ? "Barricade started. Break a gap or survive 30 seconds." :
                "Not enough enemy capacity for a complete barricade.");
            break;
        }
        int quantity = 0;
        const auto parsed = std::from_chars(quantityText.data(), quantityText.data() + quantityText.size(), quantity);
        if (argument != "lowlevel" || extra != "enemy" || !trailing.empty() ||
            parsed.ec != std::errc{} || parsed.ptr != quantityText.data() + quantityText.size() ||
            quantity <= 0 || quantity > Balance::ENEMY_LIMIT) {
            addOutput("Usage: spawn lowlevel enemy <quantity>");
            addOutput("Or: spawn barricade event");
            addOutput("Quantity: whole number from 1 to " + std::to_string(Balance::ENEMY_LIMIT) + ".");
            break;
        }
        if (player->getHealth() <= 0) { addOutput("Restart the run before spawning enemies."); break; }
        auto& manager = EnemyManager::GetInstance();
        const int spawned = manager.spawnLowEnemies(player->getPosition(), quantity);
        addOutput("Spawned " + std::to_string(spawned) + " low-level enemies. Total: " + std::to_string(manager.getEnemies().size()) + ".");
        if (spawned < quantity) addOutput("Enemy limit reached: " + std::to_string(Balance::ENEMY_LIMIT) + ".");
        break;
    }
    case DEBUG_PLAYER: {
        std::string trailing;
        stream >> trailing;
        if (argument.empty()) {
            addOutput("player <default|gunner|cannon|laser|rockets|heavy> build");
            addOutput("player weapon <cannon|laser|rockets|heavy>");
            addOutput("player engine <base|pulse|burst|supercharged>");
            addOutput("player shield <none|front|sides|round|invincibility>");
            addOutput("Space: burst boost / invincibility shield");
            break;
        }
        const auto option = std::find_if(equipmentCommands.begin(), equipmentCommands.end(), [&](const EquipmentInfo& info) {
            return argument + " " + extra == info.text;
        });
        if (!trailing.empty() || option == equipmentCommands.end()) {
            addOutput("Unknown player option. Type player for commands.");
            break;
        }
        if (player->getHealth() <= 0) { addOutput("Restart the run before equipping a build."); break; }
        switch (option->command) {
        case EQUIP_BUILD: player->setBuild(static_cast<PlayerBuild>(option->value)); break;
        case EQUIP_WEAPON: player->setWeapon(static_cast<PlayerWeapon>(option->value)); break;
        case EQUIP_ENGINE: player->setEngine(static_cast<PlayerEngine>(option->value)); break;
        case EQUIP_SHIELD: player->setShield(static_cast<PlayerShield>(option->value)); break;
        }
        addOutput(std::string("Equipped: ") + option->text);
        addOutput("Hold LMB / E: auto-fire. Space: equipped skill.");
        break;
    }
    case DEBUG_HELP:
        addOutput("hitbox / stats / mute / invincible [on|off|toggle]");
        addOutput("player: builds, weapons, engines and shields");
        addOutput("spawn lowlevel enemy <quantity>");
        addOutput("spawn barricade event");
        addOutput("spawn debris all");
        addOutput("credits / boss / wave: pending systems");
        addOutput("help / clear / close | Ctrl+Up/Down: history");
        break;
    case DEBUG_HITBOX:
        overlayVisible = toggleValue(overlayVisible);
        addOutput(std::string("Hitboxes: ") + (overlayVisible ? "ON" : "OFF"));
        break;
    case DEBUG_STATS:
        statsVisible = toggleValue(statsVisible);
        addOutput(std::string("Stats and event diagnostics: ") + (statsVisible ? "ON" : "OFF"));
        break;
    case DEBUG_MUTE: {
        const bool muted = toggleValue(audioMuted);
        if (muted != audioMuted) {
            if (muted) {
                volumeBeforeMute = GetMasterVolume();
                SetMasterVolume(0.0f);
            } else {
                SetMasterVolume(volumeBeforeMute);
            }
            audioMuted = muted;
        }
        addOutput(std::string("Audio: ") + (audioMuted ? "MUTED" : "RESTORED"));
        break;
    }
    case DEBUG_INVINCIBLE:
        player->setDebugInvincible(toggleValue(player->isDebugInvincible()));
        addOutput(std::string("Invincibility: ") + (player->isDebugInvincible() ? "ON" : "OFF"));
        break;
    case DEBUG_CREDITS: addOutput("Unavailable: scrap and cargo (item 12)."); break;
    case DEBUG_BOSS: addOutput("Unavailable: bosses (item 17)."); break;
    case DEBUG_WAVE: addOutput("Unavailable: waves (item 11)."); break;
    case DEBUG_CLEAR: output.clear(); break;
    case DEBUG_CLOSE: consoleVisible = false; break;
    }
    TraceLog(LOG_INFO, "[DebugTools::execute] %s %s", name.c_str(), argument.c_str());
}

void DebugTools::drawConsole() const
{
    if (!consoleVisible) return;
    const Font font = ResourceManager::GetInstance().GetFont(Theme::FONT_PRIMARY);
    const Rectangle panel = Theme::DEBUG_CONSOLE_PANEL;
    DrawRectangleRec(panel, Fade(Theme::COLOR_PANEL, Theme::DEBUG_CONSOLE_OPACITY));
    Vector2 cursor = {panel.x + Theme::DEBUG_PADDING, panel.y + Theme::DEBUG_PADDING};
    const float availableWidth = panel.width - Theme::DEBUG_PADDING * 2.0f;
    const auto drawLine = [&](std::string text, Color color, bool keepEnd = false) {
        // Fit to the panel at the virtual canvas size, including long history lines.
        while (!text.empty() && MeasureTextEx(font, text.c_str(), Theme::TEXT_CAPTION, Theme::TEXT_SPACING).x > availableWidth) {
            if (keepEnd) text.erase(text.begin());
            else text.pop_back();
        }
        DrawTextEx(font, text.c_str(), cursor, Theme::TEXT_CAPTION, Theme::TEXT_SPACING,
                   Fade(color, Theme::DEBUG_CONSOLE_TEXT_OPACITY));
        cursor.y += Theme::DEBUG_LINE_HEIGHT;
    };
    drawLine("DEBUG CONSOLE | F5 / Esc: close", Theme::COLOR_ACCENT);
    drawLine("Enter: run | Tab: fill | Ctrl+Up/Down: history", Theme::COLOR_TEXT);
    for (const auto& line : output) drawLine(line, Theme::COLOR_TEXT);
    cursor.y = panel.y + Theme::DEBUG_PADDING + Theme::DEBUG_LINE_HEIGHT *
        static_cast<float>(Config::DEBUG_OUTPUT_LINES + 2);
    drawLine("> " + input + "_", Theme::COLOR_ACCENT, true);
    if (input.empty()) { drawLine("Type a command to see completions.", Theme::COLOR_TEXT); return; }
    if (input.starts_with("spawn lowlevel enemy ")) {
        drawLine("Quantity: 1-" + std::to_string(Balance::ENEMY_LIMIT) + " | Enter: spawn", Theme::COLOR_TEXT);
        return;
    }
    const auto matches = completions();
    if (matches.empty()) { drawLine("No matching commands.", Theme::COLOR_TEXT); return; }
    const int count = static_cast<int>(matches.size());
    const int first = std::clamp(suggestionOffset, 0, std::max(0, count - Theme::DEBUG_SUGGESTION_ROWS));
    const int last = std::min(count, first + Theme::DEBUG_SUGGESTION_ROWS);
    const Rectangle dropdown = {panel.x, cursor.y, panel.width,
        Theme::DEBUG_PADDING * 2.0f + Theme::DEBUG_LINE_HEIGHT * static_cast<float>(last - first + 1)};
    DrawRectangleRec(dropdown, Fade(Theme::COLOR_PANEL, Theme::DEBUG_DROPDOWN_OPACITY));
    cursor.y += Theme::DEBUG_PADDING;
    drawLine(TextFormat("Up/Down: choose | Tab/Enter: fill | %d-%d of %d", first + 1, last, count), Theme::COLOR_TEXT);
    for (int index = first; index < last; ++index) {
        const bool selected = index == selectedSuggestion;
        if (selected) DrawRectangleRec({cursor.x, cursor.y, availableWidth, Theme::DEBUG_LINE_HEIGHT},
            Fade(Theme::COLOR_ACCENT, Theme::DEBUG_SELECTION_OPACITY));
        drawLine(std::string(selected ? "> " : "  ") + matches[index], selected ? Theme::COLOR_ACCENT : Theme::COLOR_TEXT);
    }
}

void DebugTools::drawWorld(const Player& player) const
{
    if (!overlayVisible) return;

    const Font font = ResourceManager::GetInstance().GetFont(Theme::FONT_PRIMARY);
    // Collision checks use width as the radius, not half the sprite width.
    drawHitbox(font, player.getPosition(), player.getHitbox().width, "player", Theme::COLOR_ACCENT);
    player.drawAttackHitboxes();
    for (const auto& [id, enemy] : EnemyManager::GetInstance().getEnemies()) {
        drawHitbox(font, enemy->getPosition(), enemy->getHitbox().width, id.c_str(), Theme::COLOR_TOXIC);
    }
    for (const auto& [id, debris] : DebrisManager::GetInstance().getDebris()) {
        drawHitbox(font, debris->getPosition(), debris->getDebrisSize(), id.c_str(), Theme::COLOR_TEXT_MUTED);
    }
    // Bullets collide as points. Crosses mark their centers without inventing a radius.
    for (const auto& bullet : BulletManager::GetInstance().getBullets()) {
        const Vector2 position = bullet.getPosition();
        const Color color = bullet.isEnemyBullet() ? Theme::COLOR_DANGER : Theme::COLOR_ACCENT;
        if (bullet.getRadius() > 0.0f) {
            DrawCircleLinesV(position, bullet.getRadius(), color);
            DrawLineV(bullet.getPreviousPosition(), position, color);
        }
        const float halfSize = Theme::DEBUG_POINT_HALF_SIZE;
        DrawLineV(Vector2{position.x - halfSize, position.y}, Vector2{position.x + halfSize, position.y}, color);
        DrawLineV(Vector2{position.x, position.y - halfSize}, Vector2{position.x, position.y + halfSize}, color);
    }
}

void DebugTools::drawOverlay(const Player& player, GameState state, const BarricadeEvent& barricade) const
{
    if (!statsVisible && !player.isDebugInvincible()) return;

    const Font font = ResourceManager::GetInstance().GetFont(Theme::FONT_PRIMARY);
    if (player.isDebugInvincible()) {
        DrawTextEx(font, "INVINCIBLE", Theme::DEBUG_INVINCIBLE_POSITION,
                   Theme::TEXT_CAPTION, Theme::TEXT_SPACING, Theme::COLOR_ACCENT);
    }
    if (!statsVisible) return;

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
    drawLine(TextFormat("Enemies %d | Debris %d",
        static_cast<int>(EnemyManager::GetInstance().getEnemies().size()),
        static_cast<int>(DebrisManager::GetInstance().getDebris().size())));
    drawLine(TextFormat("Bullets: player %d | enemy %d", playerBullets, enemyBullets));
    drawLine(TextFormat("Invincibility: %s", player.isDebugInvincible() ? "ON" : "OFF"));
    const char* phase = barricade.isContaining() ? "CONTAINING" :
        barricade.isActive() ? "SCATTERING" : "IDLE";
    drawLine(TextFormat("Event: BARRICADE | %s", phase));
    const float duration = barricade.isContaining() ? Balance::BARRICADE_DURATION :
        Balance::BARRICADE_DURATION + Balance::BARRICADE_SCATTER_TIME;
    drawLine(TextFormat("Remaining %.1fs | Segments %d/%d",
        barricade.isActive() ? std::max(0.0f, duration - barricade.getElapsed()) : 0.0f,
        barricade.getAliveSegments(), Balance::BARRICADE_SEGMENTS));
    drawLine(TextFormat("Radius %.1f | Orbit %.1f deg/s", barricade.getRadius(),
        barricade.isContaining() ? Balance::BARRICADE_ORBIT_SPEED : 0.0f));
    drawLine(barricade.hasTriggeredAutomatically() ? "Automatic event: triggered this run" : "Automatic event: at 2:00 run time");
    drawLine(TextFormat("Audio: %s", GetMasterVolume() == 0.0f ? "MUTED" : "ON"));
    drawLine("F5: console | stats off: hide diagnostics");
}
#endif
