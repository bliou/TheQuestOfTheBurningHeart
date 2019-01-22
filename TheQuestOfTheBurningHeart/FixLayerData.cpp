#include "FixLayerData.h"
#include "LayerLevel.h"
#include "FixLayerComponent.h"


FixLayerData::FixLayerData()
{
}


FixLayerData::~FixLayerData()
{
}

void FixLayerData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	AbstractLayerData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);
	entity.addComponent<FixLayerComponent>();
	entity.getComponent<DrawableComponent>().layer = (int)LayerLevel::LAYER_0;
}