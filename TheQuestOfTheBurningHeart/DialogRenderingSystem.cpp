#include "DialogRenderingSystem.h"
#include "SkipTextComponent.h"


DialogRenderingSystem::DialogRenderingSystem()
{
}

void DialogRenderingSystem::render(sf::RenderWindow& window)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& dialogComponent = entity.getComponent<DialogComponent>();
		sf::RectangleShape* backgroundBox = dynamic_cast<sf::RectangleShape*>(
			entity.getComponent<DrawableComponent>().drawable
		);

		window.draw(dialogComponent.dialogTitleText);
		window.draw(dialogComponent.dialogContentText);

		if (entity.hasComponent<SkipTextComponent>()) {
			sf::Text& skipText = entity.getComponent<SkipTextComponent>().skipText;
			window.draw(skipText);
		}
	}
}