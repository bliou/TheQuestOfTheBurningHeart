#include "RectangleTransitionData.h"
#include "DrawableComponent.h"
#include "TransitionComponent.h"
#include "Helpers.h"
#include "LayerLevel.h"

RectangleTransitionData::RectangleTransitionData(TransitionType transitionType)
	: AbstractShapeEntityData::AbstractShapeEntityData(
		sf::Vector2i(screenSize)
	),
	m_transitionType(transitionType)
{
}


RectangleTransitionData::~RectangleTransitionData()
{
}

void RectangleTransitionData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	AbstractShapeEntityData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);
	if (m_transitionType == TransitionType::FADE_IN) {
		sf::RectangleShape* shape = dynamic_cast<sf::RectangleShape*>(
			entity.getComponent<DrawableComponent>().drawable
		);
		sf::Color color = shape->getFillColor();
		color.a = 0;
		shape->setFillColor(color);
	}
	float period = specificData.at("period");
	entity.addComponent<TransitionComponent>(
		period,
		m_transitionType);

	entity.getComponent<DrawableComponent>().layer = (int)LayerLevel::ACTION_1;
}