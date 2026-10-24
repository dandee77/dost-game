#include "TestAccess.hpp"
#include "EquipmentAccess.hpp"
#include "Augment.hpp"
#include "SkillSystem.hpp"
#include "Balance.hpp"
#include "Theme.hpp"
#include "raymath.h"
#include <set>
#include <stdexcept>

namespace {
    int checks = 0;
    void require(bool value, const char* message) { ++checks; if (!value) throw std::runtime_error(message); }
    void clear(Game& game)
    {
        EnemyManager::GetInstance().reset();
        BulletManager::GetInstance().reset();
        ScrapManager::GetInstance().reset();
        DamageIndicatorManager::GetInstance().reset();
        game.skills.reset();
        game.playerEntity.init();
        game.playerEntity.position = {};
        game.playerEntity.rect = {-2.0f, -2.0f, 4.0f, 4.0f};
        game.gameState = GAME_RUNNING;
        game.progress.reset();
        game.killCounter.reset();
        utils::gameCamera = {{1920.0f, 1080.0f}, {}, 0.0f, 20.0f};
    }
    Enemy& enemy(const std::string& id, Vector2 at, int hp = 100)
    {
        auto object = std::make_unique<LowLevelEnemy>(id, LOW_LEVEL_ENEMY, at, Vector2{});
        object->health = hp;
        object->speed = 0.0f;
        object->velocity = object->knockbackVelocity = {};
        auto& result = *object;
        EnemyManager::GetInstance().getEnemies()[id] = std::move(object);
        return result;
    }
    int health(const std::string& id)
    {
        const auto& map = EnemyManager::GetInstance().getEnemies();
        const auto found = map.find(id);
        return found == map.end() ? 0 : found->second->getHealth();
    }
    void cast(Game& game, AbilityId id, Vector2 target = {0.0f, -30.0f}, float dt = 0.01f)
    {
        require(game.skills.queueCast(id, target), "Skill accepts first activation");
        EquipmentTestAccess::skillStep(game, dt, target);
    }
    void step(Game& game, float seconds, float dt = 0.01f)
    {
        const int frames = static_cast<int>(std::round(seconds / dt));
        for (int i = 0; i < frames; ++i) EquipmentTestAccess::skillStep(game, dt, {0.0f, -30.0f});
    }
}

int runSkillChecks(const std::string& artifactDirectory)
{
    checks = 0;
    Game game;
    game.onSwitch();
    auto& player = game.playerEntity;
    auto& bullets = BulletManager::GetInstance().getBullets();
    clear(game);
    enemy("weapon-reward", {0, -10}, 1);
    EquipmentTestAccess::damageEquipmentEnemy(game, "weapon-reward", 100, {}, 0);
    require(ScrapManager::GetInstance().pendingValue() == 2,
        "Ordinary weapon kills earn the same salvage as automatic skills");
    EquipmentTestAccess::damageEquipmentEnemy(game, "weapon-reward", 100, {}, 0);
    const auto earned = ScrapManager::GetInstance().collectAll();
    require(earned.trade == 2 && earned.salvage == 2,
        "Repeated damage on a removed enemy cannot duplicate its reward");
    clear(game);
    auto& salvage = ScrapManager::GetInstance();
    for (int i = 0; i < Balance::SCRAP_MAX_PICKUPS + 10; ++i)
        salvage.spawnScrap({10000, 0}, ScrapReward{3, 2});
    salvage.update(21, {});
    const auto merged = salvage.collectAll();
    require(merged.trade == 480 && merged.salvage == 320,
        "Enemy loot merging and lifetime preserve separate trade and salvage values");
    clear(game);
    game.progress.reset();
    game.progress.collect(1, 370);
    game.gameTimer.setStartTime(1);
    game.update();
    require(game.gameState == GAME_AUGMENT_SELECTION && game.progress.queuedChoices == 3,
        "Earned salvage opens a card choice without waiting for a timer");
    game.augmentCards.front().isAnimationComplete = true;
    game.augmentCards.front().isIntroPlaying = false;
    require(EquipmentTestAccess::chooseUpgrade(game, 0) && game.progress.queuedChoices == 2 && !EquipmentTestAccess::chooseUpgrade(game, 0),
        "One selected card consumes exactly one queued level");
    // Repeating an ability pick must change real combat, not only its label.
    clear(game);
    game.skills.equip(ABILITY_RADIANT_HALO);
    game.skills.equip(ABILITY_RADIANT_HALO);
    enemy("upgrade-halo", {0, -10}, 1000);
    cast(game, ABILITY_RADIANT_HALO);
    require(health("upgrade-halo") < 940, "Second ability pick increases actual halo damage");
    for (const auto& info : abilityCatalog()) {
        clear(game);
        for (int pick = 1; pick <= 12; ++pick) {
            require(game.skills.upgrade(info.id), "Each ability accepts repeated upgrades beyond level five");
            require(game.skills.level(info.id) == pick, "Each pick grants exactly one level");
        }
        cast(game, info.id);
        const float debt = game.skills.cooldown(info.id);
        game.skills.unequip(info.id, player);
        game.skills.equip(info.id);
        require(game.skills.level(info.id) == 12 && game.skills.cooldown(info.id) == debt,
            "Unequip/re-equip preserves earned levels and recharge debt");
        game.skills.reset();
        require(game.skills.level(info.id) == 0, "Run reset removes earned ability levels");
    }
    clear(game);
    require(!game.skills.upgrade(ABILITY_COUNT) && !game.skills.upgrade(static_cast<AbilityId>(-1)), "Upgrade rejects invalid IDs");
    require(std::abs(abilityTuning(ABILITY_SPACE_COLLAPSE, 5).radius - 51.2f) < 0.001f &&
        abilityTuning(ABILITY_SPACE_COLLAPSE, 6).radius == abilityTuning(ABILITY_SPACE_COLLAPSE, 12).radius,
        "Collapse zones stop growing after level five");
    for (const auto& info : abilityCatalog())
        require(abilityTuning(info.id, 5).radius == abilityTuning(info.id, 6).radius &&
            abilityTuning(info.id, 6).radius == abilityTuning(info.id, 12).radius,
            "Every ability keeps its level-five physical size at higher levels");
    require(abilityTuning(ABILITY_PLASMA_BEAM, 12).damage > abilityTuning(ABILITY_PLASMA_BEAM, 6).damage,
        "Damage-only progression continues above level five");
    require(abilityTuning(ABILITY_BLINK_DRIVE, 25).cooldown > 0.0f &&
        abilityTuning(ABILITY_BLINK_DRIVE, 25).cooldown < abilityTuning(ABILITY_BLINK_DRIVE, 5).cooldown,
        "Repeated recharge upgrades remain positive beyond level five");
    require(abilityUpgradeDescription(ABILITY_SPACE_COLLAPSE, 6).find("/ 5") == std::string::npos,
        "Ability card labels show an uncapped level");
    require(abilityUpgradeDescription(ABILITY_SPACE_COLLAPSE, 6).find("size max") != std::string::npos,
        "High-level cards explain that zone size is finished growing");
    // Overlapping collapse zones may erase a target only once and never produce scrap.
    for (int rank : {1, 2, 5, 6, 12}) {
        clear(game);
        for (int pick = 0; pick < rank; ++pick) game.skills.upgrade(ABILITY_SPACE_COLLAPSE);
        enemy("center", {0, -30}, 5000);
        enemy("expanded", {-40, -30}, 5000);
        enemy("second-zone", {90, -30}, 5000);
        enemy("overlap", {30, -30}, 5000);
        cast(game, ABILITY_SPACE_COLLAPSE);
        require(game.skills.flashes.size() == static_cast<std::size_t>(rank), "Collapse creates one visible zone per level");
        require(health("center") == 0 && health("overlap") == 0, "Collapse retains its primary erasure zone");
        require((health("expanded") == 0) == (rank > 1), "Upgraded collapse radius reaches previously safe targets");
        require((health("second-zone") == 0) == (rank > 1), "Additional collapse reaches a separate target region");
        require(game.killCounter.getCount() == (rank == 1 ? 2 : 4) && ScrapManager::GetInstance().pendingValue() == 0,
            "Overlapping collapse counts kills once and never drops scrap");
    }
    clear(game);
    for (int pick = 0; pick < 6; ++pick) game.skills.upgrade(ABILITY_COMBAT_DRONE);
    enemy("six-drones", {0, -25}, 1000); cast(game, ABILITY_COMBAT_DRONE);
    require(game.skills.drones.size() == 6 && bullets.size() == 6,
        "Level six summons six independently firing drones");
    require(game.skills.drones.front().health == 105 && bullets.front().getDamage() == 34,
        "High-level drones continue gaining real health and damage");
    clear(game);
    for (int pick = 0; pick < 6; ++pick) game.skills.upgrade(ABILITY_DEFLECTOR_SHIELD);
    cast(game, ABILITY_DEFLECTOR_SHIELD);
    require(player.getDeflectorHits() == 8, "Level-six shield adds one more real hit charge");
    clear(game);
    for (int pick = 0; pick < 6; ++pick) game.skills.upgrade(ABILITY_ARMAGEDDON);
    cast(game, ABILITY_ARMAGEDDON);
    require(game.skills.flashes.size() == 6, "Level-six barrage creates one additional blast");
    clear(game);
    for (int pick = 0; pick < 6; ++pick) game.skills.upgrade(ABILITY_CHAIN_LIGHTNING);
    for (int target = 0; target < 12; ++target)
        enemy("high-chain-" + std::to_string(target), {static_cast<float>(target * 5), -10.0f}, 1000);
    cast(game, ABILITY_CHAIN_LIGHTNING);
    int highChainHits = 0;
    for (const auto& [id, object] : EnemyManager::GetInstance().getEnemies())
        if (object->getHealth() < 1000) ++highChainHits;
    require(highChainHits == 11, "Level-six chain reaches exactly one extra target per upgrade");
    // Upgrade an active shield without replenishing charges or restarting the cast.
    clear(game); game.skills.equip(ABILITY_DEFLECTOR_SHIELD); cast(game, ABILITY_DEFLECTOR_SHIELD);
    player.takeDamage(0.0f, {0, -1}, 1.0f);
    const float shieldDebt = game.skills.cooldown(ABILITY_DEFLECTOR_SHIELD);
    game.skills.upgrade(ABILITY_DEFLECTOR_SHIELD);
    require(player.getDeflectorHits() == 2 && game.skills.cooldown(ABILITY_DEFLECTOR_SHIELD) == shieldDebt,
        "Upgrading a live shield cannot refresh protection or cooldown");
    require(game.skills.states[ABILITY_DEFLECTOR_SHIELD].castLevel == 1, "Existing effect retains activation level");
    step(game, 16.0f); cast(game, ABILITY_DEFLECTOR_SHIELD);
    require(player.getDeflectorHits() == 4, "Next shield cast gains its upgraded hit capacity");
    clear(game); game.skills.upgrade(ABILITY_BLINK_DRIVE); game.skills.upgrade(ABILITY_BLINK_DRIVE);
    cast(game, ABILITY_BLINK_DRIVE, {0, -1000});
    require(player.getPosition().y < -40.0f && game.skills.cooldown(ABILITY_BLINK_DRIVE) < 4.0f,
        "Blink gains real range and faster recharge");
    clear(game); game.skills.upgrade(ABILITY_COMBAT_DRONE); game.skills.upgrade(ABILITY_COMBAT_DRONE);
    enemy("drone-victim", {0, -25}, 1000); cast(game, ABILITY_COMBAT_DRONE);
    require(game.skills.drones.size() == 2 && bullets.size() == 2, "Two drone picks summon two independently firing drones");
    require(bullets.front().getDamage() == 19 && game.skills.drones.front().health == 45,
        "Drone upgrades increase projectile damage and actual health");
    bullets.clear();
    const Vector2 droneAt = game.skills.drones.front().position;
    Bullet droneHit(droneAt, {0, 1}, true); droneHit.configure(PROJECTILE_CANNON, 40, 1.0f, 0.0f);
    BulletManager::GetInstance().addBullet(droneHit);
    step(game, 0.01f);
    require(bullets.empty() && game.skills.drones.front().health == 5, "Drone health absorbs real hostile projectile damage");
    droneHit.position = droneHit.previousPosition = game.skills.drones.front().position;
    BulletManager::GetInstance().addBullet(droneHit); step(game, 0.01f);
    require(game.skills.drones.size() == 1, "Destroyed drone is removed independently of its squad");
    game.skills.unequip(ABILITY_COMBAT_DRONE, player);
    require(game.skills.drones.empty() && game.skills.level(ABILITY_COMBAT_DRONE) == 2,
        "Unequip cleans up drones but preserves earned rank");
    clear(game); game.skills.upgrade(ABILITY_CHAIN_LIGHTNING); game.skills.upgrade(ABILITY_CHAIN_LIGHTNING);
    for (int i = 0; i < 9; ++i) enemy("up-chain" + std::to_string(i), {static_cast<float>(i * 5), -10}, 1000);
    cast(game, ABILITY_CHAIN_LIGHTNING);
    int upgradedChainHits = 0;
    for (const auto& [id, object] : EnemyManager::GetInstance().getEnemies()) if (object->getHealth() == 956) ++upgradedChainHits;
    require(upgradedChainHits == 7, "Second chain level adds one distinct target and damage");
    // Old acid pools retain the radius/damage of their cast after a mid-effect upgrade.
    clear(game); game.skills.upgrade(ABILITY_CORROSIVE_TRAIL); cast(game, ABILITY_CORROSIVE_TRAIL);
    game.skills.upgrade(ABILITY_CORROSIVE_TRAIL);
    require(game.skills.trails.front().radius == 8.0f && game.skills.trails.front().damage == 6,
        "Existing pools are not retroactively retuned by a pick");
    // Every other damaging ability uses upgraded combat tuning, not only larger visuals.
    for (AbilityId id : {ABILITY_LASER_RINGS, ABILITY_LIGHTNING_RING, ABILITY_PLASMA_BEAM,
        ABILITY_CORROSIVE_TRAIL, ABILITY_SINGULARITY, ABILITY_REALM_BREAKER}) {
        clear(game); game.skills.upgrade(id); game.skills.upgrade(id);
        Vector2 at = {0, -20};
        if (id == ABILITY_LASER_RINGS) at = {19.44f, 0};
        if (id == ABILITY_LIGHTNING_RING) at = {27.5f, 0};
        if (id == ABILITY_CORROSIVE_TRAIL) at = {0, 9.2f};
        enemy("scaled", at, 10000); cast(game, id, at);
        require(health("scaled") < 10000 - Balance::ABILITIES[id].damage, "Upgraded skill increases real damage");
    }
    clear(game); game.skills.upgrade(ABILITY_REPULSOR_PULSE); game.skills.upgrade(ABILITY_REPULSOR_PULSE);
    enemy("far-push", {0, -36}); cast(game, ABILITY_REPULSOR_PULSE);
    require(EnemyManager::GetInstance().getEnemies().at("far-push")->getPosition().y < -60,
        "Repulsor upgrades increase reach and push strength");
    clear(game); game.skills.upgrade(ABILITY_INTERCEPTOR); game.skills.upgrade(ABILITY_INTERCEPTOR);
    Bullet outerBullet({41, 0}, {0, 1}, true); BulletManager::GetInstance().addBullet(outerBullet);
    cast(game, ABILITY_INTERCEPTOR);
    require(bullets.empty() && game.skills.states[ABILITY_INTERCEPTOR].remaining > 8.0f,
        "Interceptor upgrades improve real interception radius and duration");
    clear(game); game.skills.upgrade(ABILITY_SCRAP_MAGNET); game.skills.upgrade(ABILITY_SCRAP_MAGNET);
    cast(game, ABILITY_SCRAP_MAGNET); step(game, 5.2f);
    ScrapManager::GetInstance().spawnScrap({1000, 1000}, 11); step(game, 0.3f);
    require(game.progress.wallet == 11, "Upgraded magnet still collects after level-one duration ends");
    clear(game); game.skills.upgrade(ABILITY_HOLOGRAM_CLONE); game.skills.upgrade(ABILITY_HOLOGRAM_CLONE);
    cast(game, ABILITY_HOLOGRAM_CLONE); step(game, 0.45f);
    require(bullets.size() == 2, "Upgraded clone fires its second shot before the base half-second interval");
    clear(game); game.skills.upgrade(ABILITY_NUCLEAR_MISSILE); game.skills.upgrade(ABILITY_NUCLEAR_MISSILE);
    enemy("nuke-edge", {65, -30}, 5000); cast(game, ABILITY_NUCLEAR_MISSILE); step(game, 0.75f);
    require(health("nuke-edge") == 0, "Upgraded nuclear blast reaches beyond original radius");
    clear(game); game.skills.upgrade(ABILITY_ARMAGEDDON); game.skills.upgrade(ABILITY_ARMAGEDDON);
    cast(game, ABILITY_ARMAGEDDON);
    require(game.skills.flashes.size() == 2, "Upgraded barrage emits two separate blasts per volley");
    // Actual card dispatch, one-pick lock, unlimited abilities, deterministic mixed offers.
    clear(game);
    for (int pick = 1; pick <= 2; ++pick) {
        game.gameState = GAME_AUGMENT_SELECTION;
        game.progress.queuedChoices = 1;
        game.augmentCards.clear();
        game.augmentCards.emplace_back(Vector2{}, Vector2{1200, 300}, ABILITY_SPACE_COLLAPSE, pick);
        game.augmentCards.emplace_back(Vector2{}, Vector2{1200, 300}, ABILITY_COMBAT_DRONE, 1);
        for (auto& card : game.augmentCards) { card.isAnimationComplete = true; card.isIntroPlaying = false; }
        require(EquipmentTestAccess::chooseUpgrade(game, 0) && game.skills.level(ABILITY_SPACE_COLLAPSE) == pick, "Real card selection learns then upgrades ability");
        require(!EquipmentTestAccess::chooseUpgrade(game, 0) && !EquipmentTestAccess::chooseUpgrade(game, 1) && game.skills.level(ABILITY_COMBAT_DRONE) == 0,
            "One choice locks all cards until the selection exits");
    }
    clear(game);
    std::set<int> offered;
    for (int round = 0; round < 100; ++round) {
        EquipmentTestAccess::createUpgradeOffer(game); std::set<int> distinct;
        for (const auto& card : game.augmentCards) {
            const int key = card.getAbilityId() == ABILITY_COUNT ? static_cast<int>(card.getAugmentId()) : AUG_COUNT + static_cast<int>(card.getAbilityId());
            require(distinct.insert(key).second, "Offer never contains duplicate choices"); offered.insert(key);
        }
    }
    require(offered.size() == 32, "Actual offers expose all augments and active abilities");
    for (const auto& info : abilityCatalog()) for (int pick = 0; pick < 5; ++pick) game.skills.upgrade(info.id);
    for (const auto& info : augmentCatalog()) if (info.id != AUG_NANO_REPAIR)
        for (int pick = 0; pick < 10; ++pick) applyAugment(player, info.id);
    EquipmentTestAccess::createUpgradeOffer(game);
    require(game.augmentCards.size() == Balance::UPGRADE_OFFER_COUNT &&
        std::any_of(game.augmentCards.begin(), game.augmentCards.end(), [](const Card& card) { return card.getAbilityId() != ABILITY_COUNT; }),
        "Level-five abilities remain available after passive augments are maxed");
    game.gameState = GAME_AUGMENT_SELECTION;
    game.progress.queuedChoices = 1;
    game.augmentCards.front().isAnimationComplete = true; game.augmentCards.front().isIntroPlaying = false;
    require(EquipmentTestAccess::chooseUpgrade(game, 0), "Full-health run can still finish the picker");
    clear(game);
    std::set<std::string> keys;
    for (const auto& info : augmentCatalog()) {
        require(keys.insert(info.key).second && findAugment(info.key) == info.id, "Unique augment command resolves");
        clear(game);
        if (info.id == AUG_NANO_REPAIR) player.health = 50;
        require(applyAugment(player, info.id), "All fourteen augments apply to a live player");
        if (info.id != AUG_NANO_REPAIR) require(player.getAugmentLevel(info.id) == 1, "Augment level recorded");
    }
    for (const auto& info : abilityCatalog()) {
        require(keys.insert(info.key).second && findAbility(info.key) == info.id, "Unique ability command resolves");
        clear(game);
        cast(game, info.id);
        require(!game.skills.queueCast(info.id, {}), "Recharge prevents immediate duplicate activation");
        const float cooldown = game.skills.cooldown(info.id);
        for (GameState state : {GAME_PAUSED, GAME_AUGMENT_SELECTION, GAME_OVER}) {
            game.gameState = state;
            EquipmentTestAccess::skillStep(game, 1.0f, {});
            require(game.skills.cooldown(info.id) == cooldown, "All skill timers freeze outside gameplay");
        }
        game.gameState = GAME_RUNNING;
        game.skills.unequip(info.id, player);
        game.skills.equip(info.id);
        require(!game.skills.queueCast(info.id, {}), "Unequip does not bypass recharge");
    }
    require(keys.size() == 32, "Exactly 32 unique skill commands");
    clear(game);
    require(!applyAugment(player, AUG_COUNT) && !game.skills.equip(ABILITY_COUNT), "Reject invalid typed IDs");
    require(!game.skills.queueCast(ABILITY_BLINK_DRIVE, {std::numeric_limits<float>::infinity(), 0.0f}), "Reject nonfinite target");
    for (int i = 0; i < Balance::AUG_MAX_LEVEL; ++i) applyAugment(player, AUG_WEAPONS_PAYLOAD);
    require(!applyAugment(player, AUG_WEAPONS_PAYLOAD), "Augment cap enforced");
    require(player.scaleAttackDamage(40) == 100, "Payload scales fixed-damage weapons");
    clear(game);
    applyAugment(player, AUG_REINFORCED_HULL);
    require(player.getMaxHealth() == 120 && player.getHealth() == 120, "Hull increases max/current health");
    player.health = 40;
    applyAugment(player, AUG_NANO_REPAIR);
    require(player.getHealth() == 70, "Nano repairs 25 percent of upgraded maximum");
    for (int i = 0; i < 10; ++i) applyAugment(player, AUG_NANO_REPAIR);
    require(player.getHealth() == 120 && !applyAugment(player, AUG_NANO_REPAIR), "Repair clamps and reports full hull");
    clear(game);
    applyAugment(player, AUG_CRITICAL_MATRIX);
    bool critical = false, normal = false;
    for (int i = 0; i < 2000; ++i) { const int damage = player.scaleAttackDamage(20); critical |= damage == 40; normal |= damage == 20; }
    require(critical && normal, "Critical Matrix actually produces both normal and doubled attacks");
    clear(game);
    applyAugment(player, AUG_OVERCLOCKED_CHAMBERS);
    require(std::abs(EquipmentTestAccess::weaponCooldown(player) - 0.45f) < 0.001f, "Overclock shortens cooldown");
    applyAugment(player, AUG_THRUSTER_OVERDRIVE); applyAugment(player, AUG_GYRO_CONTROL); applyAugment(player, AUG_PHASE_SHIFT);
    require(player.speed > Balance::PLAYER_SPEED && player.rotationSpeedMultiplier > 1.0f && player.iframeDuration > Balance::PLAYER_IFRAME_TIME, "Mobility, turn, iframes increase");
    for (PlayerWeapon weapon : {WEAPON_DEFAULT, WEAPON_CANNON, WEAPON_ROCKETS, WEAPON_HEAVY, WEAPON_LASER}) {
        clear(game); player.setWeapon(weapon);
        applyAugment(player, AUG_SCATTER_SHOT); applyAugment(player, AUG_BROADSIDE_CANNONS);
        applyAugment(player, AUG_TAIL_GUNNER); applyAugment(player, AUG_ARMOR_PIERCING); applyAugment(player, AUG_INERTIA_IMPACT);
        EquipmentTestAccess::updateWeapon(player, 0.001f, true);
        require(bullets.size() >= 4, "Every weapon supports scatter/side/rear fire");
        bool left = false, right = false, rear = false;
        for (const auto& bullet : bullets) {
            require(bullet.getPiercePower() >= 2 && bullet.getKnockbackPower() > 0.0f, "Every projectile inherits pierce/knockback");
            left |= bullet.getDirection().x < -0.8f; right |= bullet.getDirection().x > 0.8f; rear |= bullet.getDirection().y > 0.8f;
        }
        require(left && right && rear, "Side/rear shots face distinct directions");
    }
    clear(game); player.setWeapon(WEAPON_CANNON); applyAugment(player, AUG_RAPID_FIRE);
    EquipmentTestAccess::updateWeapon(player, 0.11f, true);
    require(bullets.size() == 2, "Rapid Fire adds a shot within the burst");
    clear(game); player.setWeapon(WEAPON_LASER); applyAugment(player, AUG_RAPID_FIRE);
    EquipmentTestAccess::updateWeapon(player, 0.001f, true);
    require(player.consumeLaserTicks() == 2, "Rapid Fire adds a laser pulse");

    clear(game); enemy("near", {0, -10}); enemy("far", {0, -100});
    cast(game, ABILITY_RADIANT_HALO);
    require(health("near") == 40 && health("far") == 100, "Halo damages nearby hostiles only");
    clear(game); enemy("target", {0, -30}, 5000);
    cast(game, ABILITY_NUCLEAR_MISSILE);
    require(health("target") == 5000, "Nuclear missile has travel time");
    step(game, 0.75f);
    require(health("target") == 0 && game.killCounter.getCount() == 1, "Nuclear missile obliterates standard targets once");
    require(ScrapManager::GetInstance().pendingValue() == Balance::SKILL_LOW_SCRAP, "Normal skill kill awards scrap");
    clear(game); enemy("target", {0, -30}, 5000);
    cast(game, ABILITY_SPACE_COLLAPSE);
    require(health("target") == 0 && ScrapManager::GetInstance().pendingValue() == 0, "Collapse erases with zero scrap");
    require(player.getScore() == Balance::LOW_SCORE && game.killCounter.getCount() == 1, "Collapse still awards score/kill");
    clear(game); auto& pulseEnemy = enemy("pushed", {0, -10});
    cast(game, ABILITY_REPULSOR_PULSE);
    require(pulseEnemy.getPosition().y < -30.0f && pulseEnemy.getHealth() == 100, "Repulsor creates space without damage");
    clear(game); enemy("ring", {25, 0}); enemy("center", {0, 0});
    cast(game, ABILITY_LIGHTNING_RING);
    require(health("ring") == 92 && health("center") == 100, "Lightning damages perimeter, not center");
    auto& shocked = *EnemyManager::GetInstance().getEnemies().at("ring");
    shocked.speed = 50.0f; const auto frozen = shocked.getPosition(); shocked.updateWithStatus(0.1f);
    require(shocked.isStunned() && Vector2Distance(frozen, shocked.getPosition()) == 0.0f, "Stun stops movement");
    shocked.updateWithStatus(1.0f); require(!shocked.isStunned(), "Stun expires");
    clear(game);
    cast(game, ABILITY_DEFLECTOR_SHIELD);
    for (int i = 0; i < Balance::SKILL_SHIELD_HITS; ++i) player.takeDamage(0.0f, {0, -1}, 1.0f);
    require(player.getHealth() == 100 && player.getDeflectorHits() == 0, "Deflector absorbs exactly three hits");
    player.takeDamage(0.0f, {0, -1}, 1.0f); require(player.getHealth() == 90, "Fourth hit damages hull");
    clear(game); cast(game, ABILITY_BLINK_DRIVE, {0, -1000});
    require(std::abs(player.getPosition().y + 35.0f) < 0.001f && player.getPlayerState() == PLAYER_IFRAME, "Blink caps range and grants short protection");
    clear(game); enemy("front", {0, -20}); enemy("behind", {0, 20});
    cast(game, ABILITY_PLASMA_BEAM); step(game, 0.3f);
    require(health("front") < 88 && health("behind") == 100, "Sustained plasma cone damages forward only");
    clear(game);
    for (int i = 0; i < 8; ++i) enemy("chain" + std::to_string(i), {static_cast<float>(i * 5), -10});
    cast(game, ABILITY_CHAIN_LIGHTNING);
    int damaged = 0;
    for (const auto& [id, object] : EnemyManager::GetInstance().getEnemies()) if (object->getHealth() == 65) ++damaged;
    require(damaged == 6, "Chain visits six distinct targets");
    clear(game); enemy("acid", {0, 8});
    cast(game, ABILITY_CORROSIVE_TRAIL);
    auto& corroded = *EnemyManager::GetInstance().getEnemies().at("acid");
    require(health("acid") == 94 && corroded.isCorroded(), "Acid deals damage and applies corrosion");
    require(corroded.getContactDamage() == 5, "Corrosion reduces combat damage");
    corroded.speed = 50.0f; const Vector2 acidPosition = corroded.getPosition(); corroded.updateWithStatus(0.1f);
    require(Vector2Distance(acidPosition, corroded.getPosition()) <= 2.501f, "Corrosion limits movement speed");
    corroded.updateWithStatus(2.0f); require(!corroded.isCorroded() && corroded.getContactDamage() == 10, "Corrosion restores stats after expiry");
    clear(game); enemy("pulled", {30, -30});
    cast(game, ABILITY_SINGULARITY, {0, -30});
    require(EnemyManager::GetInstance().getEnemies().at("pulled")->getPosition().x < 30.0f && health("pulled") == 90, "Singularity pulls and crushes");
    step(game, 2.0f);
    require(health("pulled") == 0 && ScrapManager::GetInstance().pendingValue() == 2, "Singularity kills with ordinary drops");
    clear(game);
    Bullet hostile({-60, 0}, {1, 0}, true); hostile.position = {60, 0};
    Bullet friendly({-60, 0}, {1, 0}, false); friendly.position = {60, 0};
    BulletManager::GetInstance().addBullet(hostile); BulletManager::GetInstance().addBullet(friendly);
    cast(game, ABILITY_INTERCEPTOR);
    require(bullets.size() == 1 && !bullets.front().isEnemyBullet(), "Interceptor catches swept hostile projectiles only");
    clear(game); enemy("rift", {0, -30});
    hostile.previousPosition = {-40, -30}; hostile.position = {40, -30}; BulletManager::GetInstance().addBullet(hostile);
    cast(game, ABILITY_REALM_BREAKER, {0, -30});
    require(bullets.empty() && health("rift") == 80, "Rift swallows crossing bullets and damages enemies");
    clear(game); ScrapManager::GetInstance().spawnScrap({1000, 1000}, 17);
    cast(game, ABILITY_SCRAP_MAGNET);
    require(game.progress.wallet == 17 && ScrapManager::GetInstance().count() == 0, "Magnet collects battlefield-wide once");
    step(game, 0.5f); require(game.progress.wallet == 17, "Magnet cannot duplicate scrap");
    clear(game); cast(game, ABILITY_HOLOGRAM_CLONE);
    require(game.skills.decoy() && !bullets.empty(), "Clone exists and mimics primary fire");
    enemy("lured", {0, -20});
    EnemyManager::GetInstance().update(player.getPosition(), game.gameTimer, game.skills.decoy(), 60.0f);
    require(Vector2Distance(EnemyManager::GetInstance().getEnemies().at("lured")->playerPosition, *game.skills.decoy()) == 0.0f, "Nearby enemy targets clone");
    step(game, 10.0f); require(!game.skills.decoy(), "Clone expires without dangling target");
    clear(game); player.setWeapon(WEAPON_HEAVY); applyAugment(player, AUG_RAPID_FIRE);
    cast(game, ABILITY_HOLOGRAM_CLONE);
    require(bullets.size() == 2 && bullets.front().getKind() == PROJECTILE_HEAVY, "Clone inherits weapon and burst upgrades");
    clear(game); player.setWeapon(WEAPON_LASER); enemy("clone-beam", {18, -20});
    cast(game, ABILITY_HOLOGRAM_CLONE);
    require(health("clone-beam") == 96, "Laser clone uses a damaging beam along primary facing");
    clear(game); enemy("drone-target", {0, -25}); cast(game, ABILITY_COMBAT_DRONE);
    require(!bullets.empty() && game.skills.states[ABILITY_COMBAT_DRONE].position.y < 0.0f, "Drone independently pursues and fires");
    clear(game); enemy("blade", {18, 0}); cast(game, ABILITY_LASER_RINGS);
    require(health("blade") == 88, "Orbiting laser blade deals contact damage");
    clear(game);
    for (int x = -80; x <= 80; x += 20) for (int y = -40; y <= 40; y += 20)
        enemy("barrage" + std::to_string(x) + "/" + std::to_string(y), {static_cast<float>(x), static_cast<float>(y)}, 10000);
    cast(game, ABILITY_ARMAGEDDON); step(game, 1.0f);
    int barrageHits = 0;
    for (const auto& [id, object] : EnemyManager::GetInstance().getEnemies()) if (object->getHealth() < 10000) ++barrageHits;
    require(barrageHits > 3, "Armageddon barrages multiple screen regions over time");
    // Continuous damage count should be independent of 30 vs 144 FPS.
    int referenceHealth = 0;
    for (int fps : {30, 144}) {
        clear(game); enemy("rate", {0, -20}, 10000); game.skills.queueCast(ABILITY_PLASMA_BEAM, {0, -20});
        step(game, 3.0f, 1.0f / fps);
        if (fps == 30) referenceHealth = health("rate");
        else require(health("rate") == referenceHealth, "Plasma tick damage is frame-rate independent");
    }
    clear(game);
    const auto invalid = game.skills.command("skill cast blink-drive trailing", &player);
    require(!game.skills.states[ABILITY_BLINK_DRIVE].queued && !invalid.empty(), "Malformed command never mutates state");
    game.skills.command("augment weapons-payload trailing", &player);
    require(player.getAugmentLevel(AUG_WEAPONS_PAYLOAD) == 0, "Extra augment arguments rejected");
    player.health = 0;
    game.skills.command("skill equip combat-drone", &player);
    require(!game.skills.states[ABILITY_COMBAT_DRONE].equipped, "Dead player cannot equip skills");
    clear(game);
#ifdef GAME_DEBUG
    game.executeDebugCommand("augment weapons-payload");
    game.executeDebugCommand("skill equip combat-drone");
    require(player.getAugmentLevel(AUG_WEAPONS_PAYLOAD) == 1 && game.skills.states[ABILITY_COMBAT_DRONE].equipped, "Real F5/startup command routing");
    game.executeDebugCommand("skill upgrade combat-drone");
    require(game.skills.level(ABILITY_COMBAT_DRONE) == 2, "F5 upgrade command grants exactly one level");
    game.executeDebugCommand("skill upgrade combat-drone extra");
    require(game.skills.level(ABILITY_COMBAT_DRONE) == 2, "Malformed upgrade command cannot grant a level");
    game.debugTools.input = "skill equip ";
    require(EquipmentTestAccess::completions(game.debugTools).size() == 18, "Autocomplete exposes all eighteen abilities");
#endif
    EquipmentTestAccess::restart(game);
    require(player.getMaxHealth() == 100 && player.getAugmentLevel(AUG_WEAPONS_PAYLOAD) == 0 &&
        !game.skills.states[ABILITY_COMBAT_DRONE].equipped && game.skills.level(ABILITY_COMBAT_DRONE) == 0 &&
        game.skills.drones.empty() && game.skills.flashes.empty() && game.skills.trails.empty(), "Real restart clears augments, abilities and effects");
    clear(game); cast(game, ABILITY_DEFLECTOR_SHIELD); game.onExit();
    require(player.getDeflectorHits() == 0 && !game.skills.isActive(ABILITY_DEFLECTOR_SHIELD), "Scene exit clears ability protection and effects");
    clear(game); cast(game, ABILITY_DEFLECTOR_SHIELD); player.health = 0; game.gameState = GAME_OVER; game.update();
    require(player.getDeflectorHits() == 0 && !game.skills.isActive(ABILITY_DEFLECTOR_SHIELD), "Death clears ability protection and effects");

    // Native placeholder gallery: one cell per skill, captured using production draw.
    RenderTexture2D preview = LoadRenderTexture(1800, 1200);
    BeginTextureMode(preview); ClearBackground(Theme::COLOR_PANEL);
    int index = 0;
    for (const auto& info : abilityCatalog()) {
        clear(game);
        enemy("preview", {20.0f, -20.0f});
        cast(game, info.id, {0.0f, -20.0f}, 0.05f);
        const float x = static_cast<float>((index % 6) * 300), y = static_cast<float>((index / 6) * 400);
        Camera2D camera = {{x + 150, y + 210}, {}, 0.0f, 2.0f};
        BeginMode2D(camera); game.skills.draw(); player.draw(); EndMode2D();
        DrawText(info.name, static_cast<int>(x + 10), static_cast<int>(y + 20), 15, WHITE);
        ++index;
    }
    EndTextureMode();
    Image capture = LoadImageFromTexture(preview.texture); ImageFlipVertical(&capture);
    require(ExportImage(capture, (artifactDirectory + "/skills-preview.png").c_str()), "Export native skills gallery");
    UnloadImage(capture); UnloadRenderTexture(preview);
    // Native side-by-side upgrade preview: five levels using the production renderer.
    RenderTexture2D upgradePreview = LoadRenderTexture(1800, 900);
    BeginTextureMode(upgradePreview); ClearBackground(Theme::COLOR_PANEL);
    int row = 0;
    for (AbilityId id : {ABILITY_SPACE_COLLAPSE, ABILITY_COMBAT_DRONE, ABILITY_LASER_RINGS}) {
        for (int rank = 1; rank <= 5; ++rank) {
            clear(game);
            for (int pick = 0; pick < rank; ++pick) game.skills.upgrade(id);
            cast(game, id, {}, 0.01f);
            const float x = static_cast<float>((rank - 1) * 360), y = static_cast<float>(row * 300);
            Camera2D camera = {{x + 180, y + 160}, {}, 0.0f, id == ABILITY_SPACE_COLLAPSE ? 0.9f : 3.0f};
            BeginMode2D(camera); game.skills.draw(); player.draw(); EndMode2D();
            const std::string label = std::string(abilityCatalog()[id].name) + " Lv " + std::to_string(rank);
            DrawText(label.c_str(), static_cast<int>(x + 12), static_cast<int>(y + 16), 18, WHITE);
        }
        ++row;
    }
    EndTextureMode();
    capture = LoadImageFromTexture(upgradePreview.texture); ImageFlipVertical(&capture);
    require(ExportImage(capture, (artifactDirectory + "/ability-upgrades-preview.png").c_str()), "Export native level comparisons");
    UnloadImage(capture); UnloadRenderTexture(upgradePreview);
    RenderTexture2D cardPreview = LoadRenderTexture(GAME_SCREEN_WIDTH, GAME_SCREEN_HEIGHT);
    BeginTextureMode(cardPreview); ClearBackground(Theme::COLOR_PANEL);
    int cardRow = 0;
    for (AbilityId id : {ABILITY_INTERCEPTOR, ABILITY_SPACE_COLLAPSE, ABILITY_COMBAT_DRONE}) {
        Card card({1320.0f, 555.0f + cardRow * 375.0f}, {1200.0f, 300.0f}, id, 2);
        card.draw(); ++cardRow;
    }
    EndTextureMode();
    capture = LoadImageFromTexture(cardPreview.texture); ImageFlipVertical(&capture);
    require(ExportImage(capture, (artifactDirectory + "/ability-cards-preview.png").c_str()), "Export native upgrade cards");
    UnloadImage(capture); UnloadRenderTexture(cardPreview);
    clear(game);
    TraceLog(LOG_WARNING, "PASS: %d skill checks", checks);
    return checks;
}
