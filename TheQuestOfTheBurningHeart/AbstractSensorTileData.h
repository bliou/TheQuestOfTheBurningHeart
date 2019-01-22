#pragma once
#include "AbstractTileData.h"

class AbstractSensorTileData: public AbstractTileData
{
public:
	AbstractSensorTileData(
		std::string texturePath,
		sf::Vector2i entitySize
	);
	AbstractSensorTileData(
		std::string texturePath,
		sf::Vector2i entitySize,
		float timedMovementTimer,
		b2Vec2 velocity
	);
	~AbstractSensorTileData();

protected:
	static const PhysicType physicType;
};

