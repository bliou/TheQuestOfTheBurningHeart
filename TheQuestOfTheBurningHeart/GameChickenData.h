#pragma once
#include "AbstractChickenData.h"

class GameChickenData: public AbstractChickenData
{
public:
	GameChickenData(ElementalType elementalType);
	~GameChickenData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;
};

