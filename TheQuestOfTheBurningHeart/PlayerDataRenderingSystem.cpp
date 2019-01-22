#include "PlayerDataRenderingSystem.h"
#include "TexturesManager.h"
#include "FontsManager.h"

PlayerDataRenderingSystem::PlayerDataRenderingSystem()
{
	/// Lifes graphic data
	m_lifesView.setViewport(sf::FloatRect(0.0f, 0.0f, 0.25f, 0.10f));
	m_lifesSprite.setTexture(TexturesManager::getTexture("bonusTiles.png"));
	m_lifesSprite.setTextureRect(sf::IntRect(
		sf::Vector2i(0, 0),
		sf::Vector2i(45, 38)
	));
	m_lifesSprite.setPosition(100.0f, 100.0f);
	m_lifesSprite.setScale(3.f, 10.f);

	m_lifesText.setFont(FontsManager::getFont(Font::ARIAL));
	m_lifesText.setScale(2.5f, 10.0f);
	m_lifesText.setFillColor(sf::Color::Black);
	m_lifesText.setCharacterSize(45);
	m_lifesText.setPosition(sf::Vector2f(250.0f, 20.0f));

	/// Coins graphic data
	m_coinsView.setViewport(sf::FloatRect(0.30f, 0.0f, 0.25f, 0.10f));
	m_coinsSprite.setTexture(TexturesManager::getTexture("bonusTiles.png"));
	m_coinsSprite.setTextureRect(sf::IntRect(
		sf::Vector2i(0, 38),
		sf::Vector2i(26, 26)
	));
	m_coinsSprite.setPosition(100.0f, 100.0f);
	m_coinsSprite.setScale(4.f, 15.f);

	m_coinsText.setFont(FontsManager::getFont(Font::ARIAL));
	m_coinsText.setScale(2.5f, 10.0f);
	m_coinsText.setFillColor(sf::Color::Black);
	m_coinsText.setCharacterSize(45);
	m_coinsText.setPosition(sf::Vector2f(220.0f, 20.0f));

	/// Elemental graphic data
	m_elementalView.setViewport(sf::FloatRect(0.75f, 0.0f, 0.25f, 0.10f));
	m_elementalSprite.setTexture(TexturesManager::getTexture("elementalTiles.png"));
	m_elementalSprite.setPosition(100.0f, 100.0f);
	m_elementalSprite.setScale(4.0f, 12.0f);

	m_elementalTotalTime.setPosition(230.0f, 100.0f);
	m_elementalTotalTime.setSize(sf::Vector2f(100.0f, 25.0f));
	m_elementalTotalTime.setScale(3.0f, 12.0f);
	m_elementalTotalTime.setFillColor(sf::Color::Red);

	m_elementalRemainingTime.setPosition(230.0f, 100.0f);
	m_elementalRemainingTime.setSize(sf::Vector2f(100.0f, 25.0f));
	m_elementalRemainingTime.setScale(3.0f, 12.0f);
	m_elementalRemainingTime.setFillColor(sf::Color::Green);
}

void PlayerDataRenderingSystem::render(sf::RenderWindow& window)
{
	sf::View oldView = window.getView();

	auto entities = getEntities();
	for (auto& entity : entities)
	{
		int lifes = entity.getComponent<LifeComponent>().lifes;
		int coins = entity.getComponent<PlayerCoinsComponent>().coins;

		auto& elementalComponent = entity.getComponent<PlayerElementalTypeComponent>();

		renderLifes(window, lifes);
		renderCoins(window, coins);
		renderElemental(window, elementalComponent);
	}
	window.setView(oldView);
}

void PlayerDataRenderingSystem::renderLifes(
	sf::RenderWindow& window,
	int lifes)
{
	window.setView(m_lifesView);
	window.draw(m_lifesSprite);

	std::string content = "x " + std::to_string(lifes);
	m_lifesText.setString(content);
	window.draw(m_lifesText);
}

void PlayerDataRenderingSystem::renderCoins(
	sf::RenderWindow& window,
	int coins)
{
	window.setView(m_coinsView);
	window.draw(m_coinsSprite);

	std::string content = "x " + std::to_string(coins);
	m_coinsText.setString(content);
	window.draw(m_coinsText);
}

void PlayerDataRenderingSystem::renderElemental(
	sf::RenderWindow& window,
	PlayerElementalTypeComponent elementalComponent)
{
	if (elementalComponent.currentElementalType == ElementalType::DEFAULT)
		return;

	window.setView(m_elementalView);

	auto& currentElementalType = elementalComponent.playerElementalTypes[elementalComponent.currentElementalType];

	m_elementalSprite.setTextureRect(sf::IntRect(
		sf::Vector2i(0, 0),
		sf::Vector2i(28, 32)
	));
	m_elementalRemainingTime.setSize(sf::Vector2f(currentElementalType.remainingTime * 100.f / currentElementalType.maxTime, 25.0f));

	window.draw(m_elementalSprite);
	window.draw(m_elementalTotalTime);
	window.draw(m_elementalRemainingTime);
}