#include "DialogInputSystem.h"
#include "SkipTextComponent.h"
#include "InputManager.h"
#include "KillComponent.h"
#include "DrawableComponent.h"

DialogInputSystem::DialogInputSystem()
{
}

void DialogInputSystem::updateEvent()
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& dialogComponent = entity.getComponent<DialogComponent>();
		if (entity.hasComponent<SkipTextComponent>()) {
			if (InputManager::keyPressed(sf::Keyboard::Enter)) {
				entity.addComponent<KillComponent>();
				entity.activate();
			}
		}
		else {
			if (InputManager::keyPressed(sf::Keyboard::Enter)) {
				dialogComponent.dialogContentText.setString(dialogComponent.dialogContent);
				dialogComponent.contentCout = static_cast<int>(
					dialogComponent.dialogContent.size()
				);
				if (dialogComponent.dialogSide == DialogSide::FULL) {
					sf::RectangleShape* background = dynamic_cast<sf::RectangleShape*>(
						entity.getComponent<DrawableComponent>().drawable
					);

					const sf::FloatRect textBounds(dialogComponent.dialogContentText.getLocalBounds());
					const sf::Vector2f backgroundBox(background->getSize());
					dialogComponent.dialogContentText.setPosition(background->getPosition());
					dialogComponent.dialogContentText.setOrigin(
						(textBounds.width - backgroundBox.x) / 2 + textBounds.left,
						(textBounds.height - backgroundBox.y) / 2 + textBounds.top
					);
				}
			}
		}
	}
}