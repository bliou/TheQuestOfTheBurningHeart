#pragma once
#include "AbstractCharacterData.h"

class AbstractPlayerData: public AbstractCharacterData
{
public:
	AbstractPlayerData();
	~AbstractPlayerData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override = 0;

protected:
	static const std::string texturePath;
	static const PhysicType physicType;
	static const sf::Vector2i entitySize;
	static const b2Vec2 velocity;
	static const int lifes;

	static const std::map<ElementalType, float> typeOffset;
	static const std::map<GroundCharacterState, AnimationStateComponent> animationStates;
};

