#pragma once
#include "AbstractSensorTileData.h"
#include "BaseTileType.h"

class SensorBlockTileData: public AbstractSensorTileData
{
public:
	SensorBlockTileData(BaseTileType tileType);
	~SensorBlockTileData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;

protected:
	static const std::string texturePath;
	static const sf::Vector2i entitySize;
	static const sf::Vector2i graphicSize;

	const sf::Vector2i m_offset;
};

