#pragma once
#include "AbstractSolidBlockTileData.h"
#include "BaseTileType.h"

class SolidBlockTileData: public AbstractSolidBlockTileData
{
public:
	SolidBlockTileData(BaseTileType tileType);
	~SolidBlockTileData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;

protected:
	static const std::string texturePath;
	static const sf::Vector2i graphicSize;

	const sf::Vector2i m_offset;
	const BaseTileType m_tileType;
};

