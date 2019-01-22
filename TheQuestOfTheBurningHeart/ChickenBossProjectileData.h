#pragma once
#include "AbstractProjectileData.h"
#include "AnimationStateComponent.h"

class ChickenBossProjectileData: public AbstractProjectileData
{
public:
	ChickenBossProjectileData();
	~ChickenBossProjectileData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;

protected:
	static const std::string texturePath;
	static const sf::Vector2i entitySize;
	static const float lifeSpan;
	static const AnimationStateComponent animationState;
};

