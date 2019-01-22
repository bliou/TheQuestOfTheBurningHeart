#pragma once
#include "AbstractCharacterData.h"
#include "ElementalType.h"

class AbstractMonsterData: public AbstractCharacterData
{
public:
	AbstractMonsterData(
		std::string texturePath,
		sf::Vector2i entitySize,
		b2Vec2 velocity,
		const std::map<GroundCharacterState, AnimationStateComponent> animationStates,
		ElementalType elementalType,
		int lifes = 1);
	~AbstractMonsterData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override = 0;

protected:
	static const PhysicType physicType;

	ElementalType m_elementalType;
};

