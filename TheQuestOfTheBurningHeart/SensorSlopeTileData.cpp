#include "SensorSlopeTileData.h"

const std::map<SlopeType, PhysicType> SensorSlopeTileData::typePhysic = {
	{ SlopeType::SLOPE_DOWN, PhysicType::pSensorSlopeDownTile },
	{ SlopeType::SLOPE_UP, PhysicType::pSensorSlopeUpTile }
};


SensorSlopeTileData::SensorSlopeTileData(
	SlopeType slopeType,
	BaseTileType tileType)
	: AbstractSlopeTileData::AbstractSlopeTileData(
		slopeType,
		tileType,
		typePhysic
	)
{
}


SensorSlopeTileData::~SensorSlopeTileData()
{
}

void SensorSlopeTileData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	AbstractSlopeTileData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);
}