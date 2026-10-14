#pragma once
class Player;
class Game;
class DebugTools;

// Use normal declarations for method calls: MSVC encodes access in symbols.
struct EquipmentTestAccess {
    static void updateWeapon(Player& player, float dt, bool firing);
    static void updateEquipment(Player& player, float dt, bool skill);
    static float weaponCooldown(const Player& player);
    static void resolve(Game& game);
    static void restart(Game& game);
#ifdef GAME_DEBUG
    static void execute(DebugTools& debug, Player* player);
    static void complete(DebugTools& debug);
    static void moveSuggestion(DebugTools& debug, int direction);
#endif
};
