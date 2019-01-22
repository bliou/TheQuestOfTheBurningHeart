#include "SolidSlopeTileData.h"

const std::map<SlopeType, PhysicType> SolidSlopeTileData::typePhysic = {
	{ SlopeType::SLOPE_DOWN, PhysicType::pSolidSlopeDownTile },
	{ SlopeType::SLOPE_UP, PhysicType::pSolidSlopeUpTile }
};


SolidSlopeTileData::SolidSlopeTileData(
	SlopeType slopeType,
	BaseTileType tileType)
	: AbstractSlopeTileData::AbstractSlopeTileData(
		slopeType,
		tileType,
		typePhysic
	)
{
}


SolidSlopeTileData::~SolidSlopeTileData()
{
}

void SolidSlopeTileData::initializeEntity(
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
