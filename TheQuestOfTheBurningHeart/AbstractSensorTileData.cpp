#include "AbstractSensorTileData.h"

const PhysicType AbstractSensorTileData::physicType = PhysicType::pSensorBlockTile;

AbstractSensorTileData::AbstractSensorTileData(
	std::string texturePath,
	sf::Vector2i entitySize)
	: AbstractTileData::AbstractTileData(
		texturePath,
		AbstractSensorTileData::physicType,
		entitySize
	)
{
}

AbstractSensorTileData::AbstractSensorTileData(
	std::string texturePath,
	sf::Vector2i entitySize,
	float timedMovementTimer,
	b2Vec2 velocity)
	: AbstractTileData::AbstractTileData(
		texturePath,
		AbstractSensorTileData::physicType,
		entitySize,
		timedMovementTimer,
		velocity
	)
{

}

AbstractSensorTileData::~AbstractSensorTileData()
{
}
