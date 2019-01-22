#pragma once
#include "GameScreen.h"
#include <anax/anax.hpp>
#include <SFML/Graphics.hpp>
#include "PhysicType.h"

class AbstractEntityData
{
public:
	AbstractEntityData(
		PhysicType physicType,
		sf::Vector2i entitySize
	);
	~AbstractEntityData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) = 0;

protected:
	PhysicType m_physicType;
	sf::Vector2i m_entitySize;
};

