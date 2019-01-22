#pragma once
#include "AbstractTileData.h"

class AbstractSolidBlockTileData : public AbstractTileData
{
public:
	AbstractSolidBlockTileData(std::string texturePath);
	AbstractSolidBlockTileData(
		std::string texturePath,
		float timedMovementTimer,
		b2Vec2 velocity
	);
	~AbstractSolidBlockTileData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override = 0;

protected:
	static const PhysicType physicType;
	static const sf::Vector2i entitySize;
};

