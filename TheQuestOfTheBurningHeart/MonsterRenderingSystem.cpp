#include "MonsterRenderingSystem.h"
#include "DyingComponent.h"


MonsterRenderingSystem::MonsterRenderingSystem()
{
}

void MonsterRenderingSystem::render(sf::RenderWindow& window)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		if (entity.hasComponent<DyingComponent>()) {
			auto& dyingComponent = entity.getComponent<DyingComponent>();
			sf::Sprite* sprite = dynamic_cast<sf::Sprite*>(
				entity.getComponent<DrawableComponent>().drawable
			);

			float transparency = 255 * (dyingComponent.currentDyingTimer / dyingComponent.maxDyingTimer);
			sprite->setColor(sf::Color(255, 255, 255, transparency));
		}
	}
}