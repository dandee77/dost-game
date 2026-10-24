#pragma once
#include "raylib.h"
#include <cstddef>
#include <string>
#include <vector>
class Player;
class Game;
class DebugTools;
class BarricadeEvent;

// Use normal declarations for method calls: MSVC encodes access in symbols.
struct EquipmentTestAccess {
    static void updateWeapon(Player& player, float dt, bool firing);
    static void updateEquipment(Player& player, float dt, bool skill);
    static float weaponCooldown(const Player& player);
    static void resolve(Game& game);
    static void skillStep(Game& game, float dt, Vector2 aim, bool activateSelected = false);
    static void restart(Game& game);
    static void camera(Game& game, float dt);
    static void barricadeContact(Game& game, Vector2 previousPosition);
    static void createUpgradeOffer(Game& game);
    static bool chooseUpgrade(Game& game, std::size_t index);
    static void damageEquipmentEnemy(Game& game, const std::string& id, int damage, Vector2 direction, float knockback, bool dropSkillScrap = true);
#ifdef GAME_DEBUG
    static void execute(DebugTools& debug, Player* player, BarricadeEvent* barricade = nullptr);
    static void complete(DebugTools& debug);
    static void moveSuggestion(DebugTools& debug, int direction);
    static std::vector<std::string> completions(const DebugTools& debug);
#endif
};
