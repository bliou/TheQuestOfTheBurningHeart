#pragma once
#include "AbstractSolidBlockTileData.h"

class BreakableTileData : public AbstractSolidBlockTileData
{
public:
	BreakableTileData(std::string tileToCreate = "");
	~BreakableTileData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;

protected:
	static const std::string texturePath;
	static const std::map<bool, AnimationStateComponent> animationStates;

	const std::string m_tileToCreate;
};

