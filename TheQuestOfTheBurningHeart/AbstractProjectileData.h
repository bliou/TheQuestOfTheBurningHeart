#pragma once
#include "AbstractSpriteEntityData.h"

class AbstractProjectileData: public AbstractSpriteEntityData
{
public:
	AbstractProjectileData(
		std::string texturePath,
		sf::Vector2i entitySize,
		float lifeSpan
	);
	~AbstractProjectileData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override = 0;

protected:
	static const PhysicType physicType;
	
	const float m_lifeSpan;
};

