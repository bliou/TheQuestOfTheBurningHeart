#pragma once
#include "AbstractMonsterData.h"

class AbstractChickenBossData: public AbstractMonsterData
{
public:
	AbstractChickenBossData();
	~AbstractChickenBossData();

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
	static const int lifes;
};

