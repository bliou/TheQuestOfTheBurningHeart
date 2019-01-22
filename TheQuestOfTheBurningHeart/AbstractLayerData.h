#pragma once
#include "AbstractSpriteEntityData.h"

class AbstractLayerData: public AbstractSpriteEntityData
{
public:
	AbstractLayerData();
	~AbstractLayerData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override = 0;

protected:
	static const PhysicType physicType;
};

