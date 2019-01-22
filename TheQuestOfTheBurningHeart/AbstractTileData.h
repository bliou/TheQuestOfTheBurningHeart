#pragma once
#include "AbstractSpriteEntityData.h"
#include <Box2D/Box2D.h>

class AbstractTileData: public AbstractSpriteEntityData
{
public:
	AbstractTileData(
		std::string texturePath,
		PhysicType physicType,
		sf::Vector2i entitySize
	);
	AbstractTileData(
		std::string texturePath,
		PhysicType physicType,
		sf::Vector2i entitySize,
		float timedMovementTimer,
		b2Vec2 velocity
	);
	~AbstractTileData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override = 0;

protected:
	float m_timedMovementTimer;
	b2Vec2 m_velocity;
};

