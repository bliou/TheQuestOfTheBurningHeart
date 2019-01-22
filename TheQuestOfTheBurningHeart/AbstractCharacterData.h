#pragma once
#include "AbstractSpriteEntityData.h"
#include <Box2D/Box2D.h>

class AbstractCharacterData: public AbstractSpriteEntityData
{
public:
	AbstractCharacterData(
		std::string texturePath,
		PhysicType physicType,
		sf::Vector2i entitySize,
		b2Vec2 velocity,
		const std::map<GroundCharacterState, AnimationStateComponent> animationStates,
		int lifes
	);
	~AbstractCharacterData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override = 0;

protected:
	const b2Vec2 m_velocity;
	const std::map<GroundCharacterState, AnimationStateComponent> m_animationStates;
	const int m_lifes;
};

