#pragma once
#include "AbstractEntityData.h"

class AbstractSpriteEntityData: public AbstractEntityData
{
public:
	AbstractSpriteEntityData(
		std::string texturePath,
		PhysicType physicType,
		sf::Vector2i entitySize);
	~AbstractSpriteEntityData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override = 0;

protected:
	std::string m_texturePath;
};

