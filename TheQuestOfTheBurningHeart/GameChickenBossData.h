#pragma once
#include "AbstractChickenBossData.h"

class GameChickenBossData: public AbstractChickenBossData
{
public:
	GameChickenBossData();
	~GameChickenBossData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;

protected:
	static const float closeAttackTimer;
	static const std::string projectileId;
	static const int rangeAttackCount;
	static const float rangeAttackSpeed;
};

