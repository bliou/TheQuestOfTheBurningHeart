#include "ResetTileRenderingSystem.h"



ResetTileRenderingSystem::ResetTileRenderingSystem()
{
}

void ResetTileRenderingSystem::render(sf::RenderWindow& window)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(
			entity.getComponent<DrawableComponent>().drawable
		);

		if (entity.getComponent<ResetTileComponent>().activated)
			sprite->setColor(sf::Color(255, 255, 255, 0));
		else
			sprite->setColor(sf::Color(255, 255, 255, 255));
	}
}