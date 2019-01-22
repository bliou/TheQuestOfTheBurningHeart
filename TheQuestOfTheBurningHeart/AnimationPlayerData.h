#pragma once
#include "AbstractPlayerData.h"

class AnimationPlayerData : public AbstractPlayerData
{
public:
	AnimationPlayerData();
	~AnimationPlayerData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;
};

