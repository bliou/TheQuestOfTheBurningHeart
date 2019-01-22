#pragma once
#include "AbstractMonsterData.h"

class AbstractRatData : public AbstractMonsterData
{
public:
	AbstractRatData(ElementalType elementalType);
	~AbstractRatData();

protected:
	static const std::string texturePath;
	static const sf::Vector2i entitySize;
	static const b2Vec2 velocity;
	static const std::map<GroundCharacterState, AnimationStateComponent> animationStates;
	static const int lifes;
};

