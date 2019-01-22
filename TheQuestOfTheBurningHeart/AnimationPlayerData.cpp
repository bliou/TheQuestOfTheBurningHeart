#include "AnimationPlayerData.h"
#include "AnimationIdComponent.h"


AnimationPlayerData::AnimationPlayerData()
	: AbstractPlayerData::AbstractPlayerData()
{
}


AnimationPlayerData::~AnimationPlayerData()
{
}

void AnimationPlayerData::initializeEntity(
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
	entity.addComponent<AnimationIdComponent>().id = "player";
}