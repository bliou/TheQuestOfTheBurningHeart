#pragma once
#include "AbstractLayerData.h"

class FixLayerData: public AbstractLayerData
{
public:
	FixLayerData();
	~FixLayerData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;
};

