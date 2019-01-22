#include "DialogSystem.h"
#include "Helpers.h"
#include "SkipTextComponent.h"

const float DialogSystem::updateContent = 0.02f;

DialogSystem::DialogSystem()
{
}

void DialogSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& dialogComponent = entity.getComponent<DialogComponent>();
		dialogComponent.updateContent += elapsedTime;
		if (dialogComponent.updateContent < DialogSystem::updateContent)
			continue;
		dialogComponent.updateContent = 0.f;

		sf::RectangleShape* background = dynamic_cast<sf::RectangleShape*>(
			entity.getComponent<DrawableComponent>().drawable
		);

		// If the text is fully displayed, then display the
		// "press enter to continue" text
		if (dialogComponent.contentCout == (int)dialogComponent.dialogContent.size()
			&& !entity.hasComponent<SkipTextComponent>()) {
			const sf::Vector2f backgroundBox(background->getSize());
			auto& skipText = entity.addComponent<SkipTextComponent>().skipText;

			if (dialogComponent.dialogSide == DialogSide::FULL) {
				sf::Vector2f textOrigin = dialogComponent.dialogContentText.getOrigin();
				sf::FloatRect textLocal = dialogComponent.dialogContentText.getLocalBounds();
				skipText.setPosition(
					textLocal.width - textOrigin.x + 25,
					textLocal.height - textOrigin.y + 25
				);
			}
			else {
				skipText.setPosition(
					backgroundBox.x - skipText.getLocalBounds().width - 25,
					backgroundBox.y - skipText.getLocalBounds().height - 25
				);
			}
		}
		else {
			std::string content = dialogComponent.dialogContent.substr(0, ++dialogComponent.contentCout);
			dialogComponent.dialogContentText.setString(content);
			if (dialogComponent.dialogSide == DialogSide::FULL) {
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