#pragma once
#include "AbstractPlayerData.h"
#include "ElementalType.h"

class GamePlayerData: public AbstractPlayerData
{
public:
	GamePlayerData();
	~GamePlayerData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;
};

