#include "EquipmentAccess.hpp"
#include "Game.hpp"
void EquipmentTestAccess::updateWeapon(Player& player, float dt, bool firing) { player.updateWeapon(dt, firing); }
void EquipmentTestAccess::updateEquipment(Player& player, float dt, bool skill) { player.updateEquipment(dt, skill); }
float EquipmentTestAccess::weaponCooldown(const Player& player) { return player.weaponCooldown(); }
void EquipmentTestAccess::resolve(Game& game) { game.resolveEquipmentAttacks(); }
void EquipmentTestAccess::restart(Game& game) { game.restartGame(); }
void EquipmentTestAccess::camera(Game& game, float dt) { game.updateCameraZoom(dt); }
void EquipmentTestAccess::barricadeContact(Game& game, Vector2 previousPosition) { game.resolveBarricadeContact(previousPosition); }
#ifdef GAME_DEBUG
void EquipmentTestAccess::execute(DebugTools& debug, Player* player, BarricadeEvent* barricade) { debug.execute(player, barricade); }
void EquipmentTestAccess::complete(DebugTools& debug) { debug.complete(); }
void EquipmentTestAccess::moveSuggestion(DebugTools& debug, int direction) { debug.moveSuggestion(direction); }
#endif
