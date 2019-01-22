#include "DecorativeTileData.h"
#include "LayerLevel.h"

const PhysicType DecorativeTileData::physicType = PhysicType::pNone;
const sf::Vector2i DecorativeTileData::entitySize = sf::Vector2i(640, 480);


DecorativeTileData::DecorativeTileData(DecorativeTileType type)
	: AbstractTileData::AbstractTileData(
		decorativeTileTextures.at(type),
		DecorativeTileData::physicType,
		DecorativeTileData::entitySize
	)
{
}


DecorativeTileData::~DecorativeTileData()
{
}


void DecorativeTileData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	AbstractTileData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);
	if (specificData.find("layer") != specificData.end())
		entity.getComponent<DrawableComponent>().layer = specificData.at("layer");
	else
		entity.getComponent<DrawableComponent>().layer = (int)LayerLevel::LAYER_1;
}