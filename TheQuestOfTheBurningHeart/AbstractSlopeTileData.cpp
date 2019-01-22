#include "AbstractSlopeTileData.h"
#include "SlopeTileComponent.h"

const std::string AbstractSlopeTileData::texture = "slopeTiles.png";
const sf::Vector2i AbstractSlopeTileData::entitySize = sf::Vector2i(64, 64);

const std::map<SlopeType, sf::Vector2i> AbstractSlopeTileData::typeGraphicBox = {
	{ SlopeType::SLOPE_UP, sf::Vector2i(0, 0) },
	{ SlopeType::SLOPE_DOWN, sf::Vector2i(64, 0) }
};

AbstractSlopeTileData::AbstractSlopeTileData(
	SlopeType slopeType,
	BaseTileType tileType,
	std::map<SlopeType, PhysicType> typePhysic)
	: AbstractTileData::AbstractTileData(
		AbstractSlopeTileData::texture,
		typePhysic.at(slopeType),
		AbstractSlopeTileData::entitySize
	),
	m_graphicBox(
		AbstractSlopeTileData::typeGraphicBox.at(slopeType)
		+ baseTileOffset.at(tileType)),
	m_slopeType(slopeType)
{
}


AbstractSlopeTileData::~AbstractSlopeTileData()
{
}

void AbstractSlopeTileData::initializeEntity(
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
	sprite->setTextureRect(sf::IntRect(
		m_graphicBox,
		entitySize
	));

	entity.getComponent<TileComponent>().collideFoot = true;
	entity.addComponent<SlopeTileComponent>().slopeType = m_slopeType;
}