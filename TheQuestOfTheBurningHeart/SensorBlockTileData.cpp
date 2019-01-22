#include "SensorBlockTileData.h"
#include "DrawableComponent.h"

const std::string SensorBlockTileData::texturePath = "tiles.png";
const sf::Vector2i SensorBlockTileData::entitySize = sf::Vector2i(64, 64);
const sf::Vector2i SensorBlockTileData::graphicSize = sf::Vector2i(64, 64);

SensorBlockTileData::SensorBlockTileData(BaseTileType tileType)
	: AbstractSensorTileData::AbstractSensorTileData(
		SensorBlockTileData::texturePath,
		SensorBlockTileData::entitySize
	),
	m_offset(baseTileOffset.at(tileType))
{
}


SensorBlockTileData::~SensorBlockTileData()
{
}

void SensorBlockTileData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	AbstractSensorTileData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);
	sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(
		entity.getComponent<DrawableComponent>().drawable
	);
	sf::Vector2u textSize = sprite->getTexture()->getSize();
	sprite->setTextureRect(sf::IntRect(
		m_offset,
		SensorBlockTileData::graphicSize
	));

	entity.getComponent<TileComponent>().collideFoot = true;
	entity.getComponent<TileComponent>().isOneSided = true;
}