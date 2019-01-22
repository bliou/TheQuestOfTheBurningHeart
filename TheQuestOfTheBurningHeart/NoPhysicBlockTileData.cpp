#include "NoPhysicBlockTileData.h"

const std::string NoPhysicBlockTileData::texturePath = "tiles.png";
const PhysicType NoPhysicBlockTileData::physicType = PhysicType::pNone;
const sf::Vector2i NoPhysicBlockTileData::entitySize = sf::Vector2i(64, 64);

NoPhysicBlockTileData::NoPhysicBlockTileData(BaseTileType tileType)
	: AbstractTileData::AbstractTileData(
		NoPhysicBlockTileData::texturePath,
		NoPhysicBlockTileData::physicType,
		NoPhysicBlockTileData::entitySize
	),
	m_offset(baseTileOffset.at(tileType)),
	m_tileType(tileType)
{
}


NoPhysicBlockTileData::~NoPhysicBlockTileData()
{
}

void NoPhysicBlockTileData::initializeEntity(
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
	sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(
		entity.getComponent<DrawableComponent>().drawable
	);
	sf::Vector2u textSize = sprite->getTexture()->getSize();
	sprite->setTextureRect(sf::IntRect(
		m_offset,
		NoPhysicBlockTileData::entitySize
	));
	if (m_tileType == BaseTileType::TRANSPARENT)
		sprite->setColor(sf::Color(255, 255, 255, 0));
}