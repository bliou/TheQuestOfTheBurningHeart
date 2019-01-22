#pragma once
#include "AbstractSensorTileData.h"

class ElementalTileData: public AbstractSensorTileData
{
public:
	ElementalTileData(
		ElementalType elementalType,
		bool reset = false,
		float resetTimer = 0.f);
	~ElementalTileData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;


protected:
	static const std::string texturePath;
	static const sf::Vector2i entitySize;
	static const AnimationStateComponent animationState;

	static const std::map<ElementalType, float> typeGraphicOffset;

	const ElementalType m_elementalType;

	bool m_reset;
	float m_resetTimer;
};

