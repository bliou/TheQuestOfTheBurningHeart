#pragma once
#include "AbstractRatData.h"

class AnimationRatData: public AbstractRatData
{
public:
	AnimationRatData(ElementalType elementalType);
	~AnimationRatData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;
};

