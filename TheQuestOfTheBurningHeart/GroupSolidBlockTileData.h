#pragma once
#include "SolidBlockTileData.h"

class GroupSolidBlockTileData: public SolidBlockTileData
{
public:
	GroupSolidBlockTileData(BaseTileType tileType);
	~GroupSolidBlockTileData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;
};

