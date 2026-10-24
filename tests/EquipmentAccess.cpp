#include "EquipmentAccess.hpp"
#include "Game.hpp"
void EquipmentTestAccess::updateWeapon(Player& player, float dt, bool firing) { player.updateWeapon(dt, firing); }
void EquipmentTestAccess::updateEquipment(Player& player, float dt, bool skill) { player.updateEquipment(dt, skill); }
float EquipmentTestAccess::weaponCooldown(const Player& player) { return player.weaponCooldown(); }
void EquipmentTestAccess::resolve(Game& game) { game.resolveEquipmentAttacks(); }
void EquipmentTestAccess::skillStep(Game& game, float dt, Vector2 aim, bool activateSelected) { game.updateSkills(dt, aim, activateSelected); }
void EquipmentTestAccess::restart(Game& game) { game.restartGame(); }
void EquipmentTestAccess::camera(Game& game, float dt) { game.updateCameraZoom(dt); }
void EquipmentTestAccess::barricadeContact(Game& game, Vector2 previousPosition) { game.resolveBarricadeContact(previousPosition); }
void EquipmentTestAccess::createUpgradeOffer(Game& game) { game.createUpgradeOffer(); }
bool EquipmentTestAccess::chooseUpgrade(Game& game, std::size_t index) { return game.chooseUpgrade(index); }
void EquipmentTestAccess::damageEquipmentEnemy(Game& game, const std::string& id, int damage, Vector2 direction, float knockback, bool dropSkillScrap) {
    game.damageEquipmentEnemy(id, damage, direction, knockback, dropSkillScrap);
}
#ifdef GAME_DEBUG
void EquipmentTestAccess::execute(DebugTools& debug, Player* player, BarricadeEvent* barricade) { debug.execute(player, barricade); }
void EquipmentTestAccess::complete(DebugTools& debug) { debug.complete(); }
void EquipmentTestAccess::moveSuggestion(DebugTools& debug, int direction) { debug.moveSuggestion(direction); }
std::vector<std::string> EquipmentTestAccess::completions(const DebugTools& debug) { return debug.completions(); }
#endif
