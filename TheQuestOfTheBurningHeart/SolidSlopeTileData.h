#pragma once
#include "AbstractSlopeTileData.h"

class SolidSlopeTileData: public AbstractSlopeTileData
{
public:
	SolidSlopeTileData(
		SlopeType slopeType,
		BaseTileType tileType);
	~SolidSlopeTileData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;

protected:
	static const std::map<SlopeType, PhysicType> typePhysic;
};

