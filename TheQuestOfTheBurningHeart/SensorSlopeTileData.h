#pragma once
#include "AbstractSlopeTileData.h"

class SensorSlopeTileData: public AbstractSlopeTileData
{
public:
	SensorSlopeTileData(
		SlopeType slopeType,
		BaseTileType tileType);
	~SensorSlopeTileData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;

protected:
	static const std::map<SlopeType, PhysicType> typePhysic;
};

