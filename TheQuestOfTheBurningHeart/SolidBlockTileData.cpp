#include "SolidBlockTileData.h"
#include "DrawableComponent.h"

const std::string SolidBlockTileData::texturePath = "tiles.png";
const sf::Vector2i SolidBlockTileData::graphicSize = sf::Vector2i(64, 64);

SolidBlockTileData::SolidBlockTileData(BaseTileType tileType)
	: AbstractSolidBlockTileData::AbstractSolidBlockTileData(
		SolidBlockTileData::texturePath
	),
	m_offset(baseTileOffset.at(tileType)),
	m_tileType(tileType)
{
}


SolidBlockTileData::~SolidBlockTileData()
{
}

void SolidBlockTileData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	AbstractSolidBlockTileData::initializeEntity(
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
		SolidBlockTileData::graphicSize
	));
	if (m_tileType == BaseTileType::TRANSPARENT)
		sprite->setColor(sf::Color(255, 255, 255, 0));
}