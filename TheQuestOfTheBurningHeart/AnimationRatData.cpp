#include "AnimationRatData.h"



AnimationRatData::AnimationRatData(ElementalType elementalType)
	: AbstractRatData::AbstractRatData(elementalType)
{
}


AnimationRatData::~AnimationRatData()
{
}

void AnimationRatData::initializeEntity(
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
	entity.addComponent<AnimationIdComponent>().id = "rat";
	entity.removeComponent<DisableComponent>();
}