#include "HelperTileRenderingSystem.h"
#include "FontsManager.h"


HelperTileRenderingSystem::HelperTileRenderingSystem()
{
	m_helperText.setFont(FontsManager::getFont(Font::ARIAL));
	m_helperText.setStyle(sf::Text::Style::Bold);
	m_helperText.setCharacterSize(25);
	m_helperText.setFillColor(sf::Color::White);
	m_helperText.setString("Press E for information...");

	m_helperBackground.setFillColor(sf::Color::Black);
	sf::FloatRect textLocal = m_helperText.getLocalBounds();
	m_helperBackground.setSize(sf::Vector2f(
		textLocal.width + 10.f,
		textLocal.height + 10.f
	));
}

void HelperTileRenderingSystem::render(sf::RenderWindow& window)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& helperComponent = entity.getComponent<HelperTileComponent>();
		auto& position = entity.getComponent<PositionComponent>().position;
		auto& size = entity.getComponent<SizeComponent>().size;
		
		if (helperComponent.activated) {
			sf::Vector2f backgroundSize = m_helperBackground.getSize();
			m_helperBackground.setPosition(
				position.x + size.x / 2 - backgroundSize.x / 2,
				position.y - size.y / 2 - 10.f
			);
			sf::FloatRect textLocal = m_helperText.getLocalBounds();
			m_helperText.setPosition(
				position.x + size.x / 2 - textLocal.width / 2,
				position.y - size.y / 2 - textLocal.height / 2
			);
			window.draw(m_helperBackground);
			window.draw(m_helperText);
		}
	}
}