#include "GameChickenData.h"
#include "InfiniteMovementComponent.h"

GameChickenData::GameChickenData(ElementalType elementalType)
	: AbstractChickenData::AbstractChickenData(elementalType)
{
}


GameChickenData::~GameChickenData()
{
}

void GameChickenData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	AbstractChickenData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);
	entity.addComponent<InfiniteMovementComponent>();
}