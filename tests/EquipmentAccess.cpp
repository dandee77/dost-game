#include "EquipmentAccess.hpp"
#include "Game.hpp"
void EquipmentTestAccess::updateWeapon(Player& player, float dt, bool firing) { player.updateWeapon(dt, firing); }
void EquipmentTestAccess::updateEquipment(Player& player, float dt, bool skill) { player.updateEquipment(dt, skill); }
float EquipmentTestAccess::weaponCooldown(const Player& player) { return player.weaponCooldown(); }
void EquipmentTestAccess::resolve(Game& game) { game.resolveEquipmentAttacks(); }
void EquipmentTestAccess::restart(Game& game) { game.restartGame(); }
#ifdef GAME_DEBUG
void EquipmentTestAccess::execute(DebugTools& debug, Player* player) { debug.execute(player); }
void EquipmentTestAccess::complete(DebugTools& debug) { debug.complete(); }
void EquipmentTestAccess::moveSuggestion(DebugTools& debug, int direction) { debug.moveSuggestion(direction); }
#endif
