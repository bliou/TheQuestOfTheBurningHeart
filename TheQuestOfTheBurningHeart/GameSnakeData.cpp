#include "GameSnakeData.h"
#include "InfiniteMovementComponent.h"


GameSnakeData::GameSnakeData(ElementalType elementalType)
	: AbstractSnakeData::AbstractSnakeData(elementalType)
{
}


GameSnakeData::~GameSnakeData()
{
}


void GameSnakeData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	AbstractSnakeData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);
	entity.addComponent<InfiniteMovementComponent>();
}