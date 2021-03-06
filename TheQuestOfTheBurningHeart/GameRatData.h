#pragma once
#include "AbstractRatData.h"

class GameRatData: public AbstractRatData
{
public:
	GameRatData(ElementalType elementalType);
	~GameRatData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;

protected:
	static const float closeAttackTimer;
};

