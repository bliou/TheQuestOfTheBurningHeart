#include "HelperTileData.h"
#include "Helpers.h"
#include "HelperTileComponent.h"

const std::string HelperTileData::texturePath = "helperTiles.png";
const sf::Vector2i HelperTileData::entitySize = sf::Vector2i(64, 64);

HelperTileData::HelperTileData()
	: AbstractSensorTileData::AbstractSensorTileData(
		HelperTileData::texturePath,
		HelperTileData::entitySize
	)
{
}


HelperTileData::~HelperTileData()
{
}

void HelperTileData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	position = sf::Vector2f(
		position.x + (tileSize.x - entitySize.x) / 2,
		position.y + tileSize.y - entitySize.y
	);
	AbstractSensorTileData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);
	std::string helperContent = specificData.at("helperContent").get<std::string>();
	entity.addComponent<HelperTileComponent>(helperContent);
}