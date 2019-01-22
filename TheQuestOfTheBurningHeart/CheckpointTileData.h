#pragma once
#include "AbstractSensorTileData.h"

class CheckpointTileData : public AbstractSensorTileData
{
public:
	CheckpointTileData();
	~CheckpointTileData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;

protected:
	static const std::string texturePath;
	static const sf::Vector2i entitySize;
	static const std::map<bool, AnimationStateComponent> animationStates;
};

