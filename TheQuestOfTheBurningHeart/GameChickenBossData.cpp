#include "GameChickenBossData.h"
#include "InfiniteMovementComponent.h"
#include "CloseAttackTriggerComponent.h"
#include "MonsterDeathComponent.h"
#include "ChickenBossPatternComponent.h"

const float GameChickenBossData::closeAttackTimer = 0.2f;
const std::string GameChickenBossData::projectileId = "mp0";
const int GameChickenBossData::rangeAttackCount = 4;
const float GameChickenBossData::rangeAttackSpeed = 0.9f;

GameChickenBossData::GameChickenBossData()
{
}


GameChickenBossData::~GameChickenBossData()
{
}

void GameChickenBossData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	AbstractChickenBossData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);
	entity.addComponent<InfiniteMovementComponent>();
	b2Body* body = entity.getComponent<PhysicComponent>().body;
	sf::Vector2i size = entity.getComponent<SizeComponent>().size;
	entity.addComponent<CloseAttackTriggerComponent>(
		body,
		sf::Vector2i(size.x + 80, size.y)
	);
	entity.addComponent<CloseAttackDataComponent>(
		GameChickenBossData::closeAttackTimer
	);
	entity.addComponent<RangeAttackDataComponent>(
		GameChickenBossData::projectileId,
		GameChickenBossData::rangeAttackCount,
		GameChickenBossData::rangeAttackSpeed
	);
	entity.addComponent<MonsterDeathComponent>(
		"dt1",
		false,
		sf::Vector2f(448, 704)
	);
	entity.addComponent<ChickenBossPatternComponent>();
}
