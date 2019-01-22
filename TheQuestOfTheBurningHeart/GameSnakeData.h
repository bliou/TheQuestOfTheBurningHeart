#pragma once
#include "AbstractSnakeData.h"

class GameSnakeData : public AbstractSnakeData
{
public:
	GameSnakeData(ElementalType elementalType);
	~GameSnakeData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;
};

