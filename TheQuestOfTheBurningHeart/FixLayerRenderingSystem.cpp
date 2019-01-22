#include "FixLayerRenderingSystem.h"
#include "Helpers.h"


FixLayerRenderingSystem::FixLayerRenderingSystem()
{
}

void FixLayerRenderingSystem::render(sf::RenderWindow& window)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		sf::Vector2f centerView = window.getView().getCenter();
		sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(
			entity.getComponent<DrawableComponent>().drawable
		);
		if (sprite)
			sprite->setPosition(
				centerView.x - screenSize.x / 2.f,
				centerView.y - screenSize.y / 2.f
			);
	}
}