#include "TransitionSystem.h"


TransitionSystem::TransitionSystem()
{
}

void TransitionSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& transitionComponent = entity.getComponent<TransitionComponent>();
		transitionComponent.period -= elapsedTime;
		if (transitionComponent.period <= 0) {
			entity.kill();
			entity.activate();
		}

		sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(
			entity.getComponent<DrawableComponent>().drawable
		);
		if (sprite) {
			sf::Color color = sprite->getColor();
			updateColor(transitionComponent, color);
			sprite->setColor(color);
		}
		else {
			sf::RectangleShape* shape = dynamic_cast<sf::RectangleShape*>(
				entity.getComponent<DrawableComponent>().drawable
			);
			sf::Color color = shape->getFillColor();
			updateColor(transitionComponent, color);
			shape->setFillColor(color);
		}
	}
}

void TransitionSystem::updateColor(
	TransitionComponent& transitionComponent,
	sf::Color& color)
{
	if (transitionComponent.transitionType == TransitionType::FADE_OUT) {
		float transparency = 255 * (transitionComponent.period / transitionComponent.maxPeriod);
		color.a = transparency;
	}
	else {
		float transparency = 255 - (255 * (transitionComponent.period / transitionComponent.maxPeriod));
		color.a = transparency;
	}
}