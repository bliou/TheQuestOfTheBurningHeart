#include "GameRatData.h"
#include "InfiniteMovementComponent.h"
#include "CloseAttackTriggerComponent.h"


const float GameRatData::closeAttackTimer = 0.4f;

GameRatData::GameRatData(ElementalType elementalType)
	: AbstractRatData::AbstractRatData(elementalType)
{
}


GameRatData::~GameRatData()
{
}

void GameRatData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	AbstractRatData::initializeEntity(
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
		sf::Vector2i(size.x + 20, size.y)
	);
	entity.addComponent<CloseAttackDataComponent>(
		GameRatData::closeAttackTimer
	);
}