#include "AbstractShapeEntityData.h"



AbstractShapeEntityData::AbstractShapeEntityData(
	sf::Vector2i entitySize,
	sf::Color color)
	: AbstractEntityData::AbstractEntityData(
		PhysicType::pNone,
		entitySize
	),
	m_color(color)
{
}


AbstractShapeEntityData::~AbstractShapeEntityData()
{
}

void AbstractShapeEntityData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	AbstractEntityData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);

	entity.addComponent<DrawableComponent>().drawable = new sf::RectangleShape();
	sf::RectangleShape* rectangleShape = dynamic_cast<sf::RectangleShape*>(
		entity.getComponent<DrawableComponent>().drawable
	);
	rectangleShape->setSize(sf::Vector2f(m_entitySize));
	rectangleShape->setPosition(position);
	rectangleShape->setFillColor(m_color);
}