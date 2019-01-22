#include "TimedTileRenderingSystem.h"



TimedTileRenderingSystem::TimedTileRenderingSystem()
{
}

void TimedTileRenderingSystem::render(sf::RenderWindow& window)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(
			entity.getComponent<DrawableComponent>().drawable
		);
		auto& timedTileComponent = entity.getComponent<TimedTileComponent>();
		if (timedTileComponent.active) {
			float transparency = timedTileComponent.currentTimer * 255.f / timedTileComponent.defaultTimer;
			sprite->setColor(sf::Color(255, 255, 255, transparency));
		}
	}
}