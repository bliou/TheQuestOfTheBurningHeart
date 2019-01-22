#include "GamePlayerData.h"
#include "GamePlayerComponent.h"
#include "PlayerCoinsComponent.h"
#include "CharacterOrientationComponent.h"
#include "GroundCharacterStateComponent.h"
#include "PlayerElementalTypeComponent.h"
#include "CameraComponent.h"
#include "MonsterActivatorTriggerComponent.h"
#include "ConfigManager.h"


GamePlayerData::GamePlayerData()
{
}


GamePlayerData::~GamePlayerData()
{
}

void GamePlayerData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	AbstractPlayerData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);

	entity.addComponent<GamePlayerComponent>();
	entity.removeComponent<CharacterOrientationComponent>();
	entity.addComponent<CharacterOrientationComponent>(CharacterOrientation::RIGHT);
	entity.addComponent<CameraComponent>();

	b2Body* body = entity.getComponent<PhysicComponent>().body;
	entity.addComponent<MonsterActivatorTriggerComponent>(body);

	sPlayerData playerData = ConfigManager::getPlayerData();
	entity.addComponent<PlayerCoinsComponent>().coins = playerData.playerCoins;

	auto& playerElementalTypeComponent = entity.addComponent<PlayerElementalTypeComponent>();
	playerElementalTypeComponent.playerElementalTypes[ElementalType::FIRE].remainingTime = playerData.playerElementalTypes.fire;

	entity.getComponent<LifeComponent>().lifes = playerData.playerLife;
}
