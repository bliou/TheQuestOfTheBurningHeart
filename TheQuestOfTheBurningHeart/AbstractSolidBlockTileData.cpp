#include "AbstractSolidBlockTileData.h"

const PhysicType AbstractSolidBlockTileData::physicType = PhysicType::pSolidBlockTile;
const sf::Vector2i AbstractSolidBlockTileData::entitySize = sf::Vector2i(64, 64);

AbstractSolidBlockTileData::AbstractSolidBlockTileData(std::string texturePath)
	: AbstractTileData::AbstractTileData(
		texturePath,
		AbstractSolidBlockTileData::physicType,
		AbstractSolidBlockTileData::entitySize
	)
{
}

AbstractSolidBlockTileData::AbstractSolidBlockTileData(
	std::string texturePath,
	float timedMovementTimer,
	b2Vec2 velocity)
	: AbstractTileData::AbstractTileData(
		texturePath,
		AbstractSolidBlockTileData::physicType,
		AbstractSolidBlockTileData::entitySize,
		timedMovementTimer,
		velocity
	)
{

}

AbstractSolidBlockTileData::~AbstractSolidBlockTileData()
{
}

void AbstractSolidBlockTileData::initializeEntity(
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
	entity.getComponent<TileComponent>().collideFoot = true;
}