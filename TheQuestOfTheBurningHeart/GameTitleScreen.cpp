#include "GameTitleScreen.h"
#include "InputManager.h"
#include "ConfigManager.h"
#include "ScreensManager.h"

GameTitleScreen::GameTitleScreen()
	: m_currentOption(),
	m_options(),
	m_chosenOption("")
{

}


GameTitleScreen::~GameTitleScreen()
{
	for (unsigned int i = 0; i < m_options.size(); ++i) {
		delete m_options[i];
		m_options[i] = nullptr;
	}
}

int GameTitleScreen::run(sf::RenderWindow& window)
{
	window.setView(window.getDefaultView());
	init();

	sf::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				return -1;
			}
			InputManager::updateEvent(event);
			// When pressing the down arrow button, go to the next option
			if (InputManager::keyPressed(sf::Keyboard::Down)) {
				m_currentOption = std::next(m_currentOption, 1);
				if (m_currentOption == m_options.end())
					m_currentOption = m_options.begin();
			}

			// When pressing the up arrow button, go to the previous option
			if (InputManager::keyPressed(sf::Keyboard::Up)) {
				if (m_currentOption == m_options.begin())
					m_currentOption = m_options.end() - 1;
				else
					m_currentOption = std::prev(m_currentOption, 1);
			}

			// When pressing the enter key button, return the current option value
			if (InputManager::keyPressed(sf::Keyboard::Enter)) {
				switch ((*m_currentOption)->GetValue()) {
				case GameTitleOption::CONTINUE:
					ScreensManager::updateGameScreen(ConfigManager::getGameLevel());
					return (int)Screen::GAME;
				case GameTitleOption::NEW_GAME:
					ConfigManager::saveDefaultConfig();
					ScreensManager::updateGameScreen(ConfigManager::getGameLevel());
					return (int)Screen::GAME;
				case GameTitleOption::CREDITS:
					return (int)Screen::CREDITS;
				case GameTitleOption::EXIT:
					return -1;
				}
			}
		}

		window.clear(sf::Color::Black);
		for (unsigned int i = 0; i < m_options.size(); ++i) {
			bool selected = (*m_currentOption)->GetValue() == m_options[i]->GetValue();
			m_options[i]->Draw(window, selected);
		}
		window.display();
	}
	return -1;
}


void GameTitleScreen::init()
{
	for (unsigned int i = 0; i < m_options.size(); ++i) {
		delete m_options[i];
		m_options[i] = nullptr;
	}
	m_options.clear();

	std::list<std::pair<GameTitleOption, std::string>> optionsMap{
		{ GameTitleOption::NEW_GAME, "New Game" },
		{ GameTitleOption::CREDITS, "Credits" },
		{ GameTitleOption::EXIT, "Exit" }
	};

	// If the config file is not empty, it means we have
	// a current save that we can load
	if (ConfigManager::doesConfigExists()) {
		optionsMap.insert(optionsMap.begin(),
			std::pair<GameTitleOption, std::string> {
			GameTitleOption::CONTINUE, "Continue"
		}
		);
	}

	std::list<std::pair<GameTitleOption, std::string>>::iterator it = optionsMap.begin();
	int index = 0;
	for (it; it != optionsMap.end(); ++it) {
		m_options.push_back(new GameOption<GameTitleOption>(
			(*it).first,
			(*it).second,
			index,
			(float)optionsMap.size(),
			60)
		);
		++index;
	}
	m_currentOption = m_options.begin();
}