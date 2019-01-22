#pragma once
#include "SolidSlopeTileData.h"

class GroupSolidSlopeTileData: public SolidSlopeTileData
{
public:
	GroupSolidSlopeTileData(
		SlopeType slopeType,
		BaseTileType tileType);
	~GroupSolidSlopeTileData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;
};