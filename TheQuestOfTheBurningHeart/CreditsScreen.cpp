#include "CreditsScreen.h"
#include "InputManager.h"
#include "Helpers.h"
#include <cassert>


CreditsScreen::CreditsScreen()
	: m_scroll(true)
{
	m_gameByLabel.setFillColor(sf::Color::White);
	m_gameByLabel.setFont(FontsManager::getFont(Font::ARIAL));
	m_gameByLabel.setCharacterSize(35);
	m_gameByLabel.setString("A game by");
	sf::FloatRect textBounds(m_gameByLabel.getLocalBounds());
	m_gameByLabel.setOrigin(
		(textBounds.width - screenSize.x) / 2.f + textBounds.left,
		0.f
	);
	m_gameByLabel.setPosition(0.f, (float)screenSize.y);

	m_gameBy.setFillColor(sf::Color::White);
	m_gameBy.setFont(FontsManager::getFont(Font::ARIAL));
	m_gameBy.setCharacterSize(45);
	m_gameBy.setString("Jacques EID - Josselin ROUSSET");
	sf::Vector2f prevPos = m_gameByLabel.getPosition();
	m_gameBy.setPosition(0.f, prevPos.y + textBounds.height + 10.f);
	textBounds = m_gameBy.getLocalBounds();
	m_gameBy.setOrigin(
		(textBounds.width - screenSize.x) / 2.f + textBounds.left,
		0.f
	);

	m_gameMadeWithLabel.setFillColor(sf::Color::White);
	m_gameMadeWithLabel.setFont(FontsManager::getFont(Font::ARIAL));
	m_gameMadeWithLabel.setCharacterSize(35);
	m_gameMadeWithLabel.setString("Credits to");
	prevPos = m_gameBy.getPosition();
	m_gameMadeWithLabel.setPosition(0.f, prevPos.y + textBounds.height + 150.f);
	textBounds = m_gameMadeWithLabel.getLocalBounds();
	m_gameMadeWithLabel.setOrigin(
		(textBounds.width - screenSize.x) / 2.f + textBounds.left,
		0.f
	);

	m_gameMadeWith.setFillColor(sf::Color::White);
	m_gameMadeWith.setFont(FontsManager::getFont(Font::ARIAL));
	m_gameMadeWith.setCharacterSize(45);
	m_gameMadeWith.setString("SFML - Box2D - Anax Entity System");
	prevPos = m_gameMadeWithLabel.getPosition();
	m_gameMadeWith.setPosition(0.f, prevPos.y + textBounds.height + 10.f);
	textBounds = m_gameMadeWith.getLocalBounds();
	m_gameMadeWith.setOrigin(
		(textBounds.width - screenSize.x) / 2.f + textBounds.left,
		0.f
	);

	m_thanksToLabel.setFillColor(sf::Color::White);
	m_thanksToLabel.setFont(FontsManager::getFont(Font::ARIAL));
	m_thanksToLabel.setCharacterSize(35);
	m_thanksToLabel.setString("Special thanks to");
	prevPos = m_gameMadeWith.getPosition();
	m_thanksToLabel.setPosition(0.f, prevPos.y + textBounds.height + 150.f);
	textBounds = m_thanksToLabel.getLocalBounds();
	m_thanksToLabel.setOrigin(
		(textBounds.width - screenSize.x) / 2.f + textBounds.left,
		0.f
	);

	m_thanksTo.setFillColor(sf::Color::White);
	m_thanksTo.setFont(FontsManager::getFont(Font::ARIAL));
	m_thanksTo.setCharacterSize(45);
	m_thanksTo.setString("Kenney.nl - strangedragon81");
	prevPos = m_thanksToLabel.getPosition();
	m_thanksTo.setPosition(0.f, prevPos.y + textBounds.height + 10.f);
	textBounds = m_thanksTo.getLocalBounds();
	m_thanksTo.setOrigin(
		(textBounds.width - screenSize.x) / 2.f + textBounds.left,
		0.f
	);


	m_leaveCredits.setFillColor(sf::Color::White);
	m_leaveCredits.setFont(FontsManager::getFont(Font::ARIAL));
	m_leaveCredits.setCharacterSize(25);
	m_leaveCredits.setString("Press enter to exit...");
	textBounds = m_leaveCredits.getLocalBounds();
	m_leaveCredits.setOrigin(
		9.f * (textBounds.width - screenSize.x) / 10.f + textBounds.left,
		14.f * (textBounds.height - screenSize.y) / 15.f + textBounds.top
	);
}


CreditsScreen::~CreditsScreen()
{
}

int CreditsScreen::run(sf::RenderWindow& window)
{
	window.setView(window.getDefaultView());
	sf::Clock clock;
	sf::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				return -1;
			}
			InputManager::updateEvent(event);
			if (!m_scroll
				&& InputManager::keyPressed(sf::Keyboard::Enter)) {
				return (int)Screen::GAME_TITLE;
			}
		}
		update(clock.restart().asSeconds());

		window.clear(sf::Color::Black);
		draw(window);
		window.display();
	}
	return -1;
}

void CreditsScreen::update(float elapsedTime)
{
	if (!m_scroll)
		return;
	const float factor = 100.f;

	sf::Vector2f pos = m_gameByLabel.getPosition();
	m_gameByLabel.setPosition(pos.x, pos.y - factor * elapsedTime);
	
	if (pos.y <= 150.f)
		m_scroll = false;

	pos = m_gameBy.getPosition();
	m_gameBy.setPosition(pos.x, pos.y - factor * elapsedTime);

	pos = m_gameMadeWithLabel.getPosition();
	m_gameMadeWithLabel.setPosition(pos.x, pos.y - factor * elapsedTime);

	pos = m_gameMadeWith.getPosition();
	m_gameMadeWith.setPosition(pos.x, pos.y - factor * elapsedTime);

	pos = m_thanksToLabel.getPosition();
	m_thanksToLabel.setPosition(pos.x, pos.y - factor * elapsedTime);

	pos = m_thanksTo.getPosition();
	m_thanksTo.setPosition(pos.x, pos.y - factor * elapsedTime);
}

void CreditsScreen::draw(sf::RenderWindow& window)
{
	window.draw(m_gameByLabel);
	window.draw(m_gameBy);
	window.draw(m_gameMadeWithLabel);
	window.draw(m_gameMadeWith);
	window.draw(m_thanksToLabel);
	window.draw(m_thanksTo);

	if (!m_scroll)
		window.draw(m_leaveCredits);
}