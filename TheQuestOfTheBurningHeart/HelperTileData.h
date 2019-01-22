#pragma once
#include "AbstractSensorTileData.h"

class HelperTileData: public AbstractSensorTileData
{
public:
	HelperTileData();
	~HelperTileData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;

protected:
	static const std::string texturePath;
	static const sf::Vector2i entitySize;
};

