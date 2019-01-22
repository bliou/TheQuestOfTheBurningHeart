#pragma once
#include "AbstractSensorTileData.h"
#include "Screen.h"

class DoorTileData : public AbstractSensorTileData
{
public:
	DoorTileData(Screen nextScreen);
	~DoorTileData();


	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;

protected:
	static const std::string texturePath;
	static const sf::Vector2i entitySize;

	const Screen m_nextScreen;
};

