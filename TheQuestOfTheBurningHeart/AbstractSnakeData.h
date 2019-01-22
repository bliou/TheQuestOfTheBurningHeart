#pragma once
#include "AbstractMonsterData.h"

class AbstractSnakeData : public AbstractMonsterData
{
public:
	AbstractSnakeData(ElementalType elementalType);
	~AbstractSnakeData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override = 0;

protected:
	static const std::string texturePath;
	static const sf::Vector2i entitySize;
	static const b2Vec2 velocity;
	static const std::map<GroundCharacterState, AnimationStateComponent> animationStates;
};

