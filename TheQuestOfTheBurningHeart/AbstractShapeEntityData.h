#pragma once
#include "AbstractEntityData.h"

class AbstractShapeEntityData: public AbstractEntityData
{
public:
	AbstractShapeEntityData(
		sf::Vector2i entitySize,
		sf::Color color = sf::Color::Black);
	~AbstractShapeEntityData();

	virtual void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override = 0;

protected:
	sf::Color m_color;
};

