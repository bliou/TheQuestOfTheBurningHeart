#include "GameScreenPauseState.h"
#include "GameScreenRunningState.h"
#include "GameScreenLoadingState.h"
#include "GameScreen.h"
#include "InputManager.h"
#include <cassert>


GameScreenPauseState::GameScreenPauseState()
	: m_currentOption(),
	m_options(),
	m_chosenOption(PauseOptions::CONTINUE),
	m_optionSelected(false)
{
	// Init the options
	assert(m_options.size() == 0);
	std::vector<std::pair<PauseOptions, std::string>> optionsMap{
		{ PauseOptions::CONTINUE, "Continue" },
		{ PauseOptions::RESTART, "Restart" },
		{ PauseOptions::MAIN_MENU, "Main menu" }
	};

	for (unsigned int i = 0; i < optionsMap.size(); ++i) {
		m_options.push_back(new GameOption<PauseOptions>(
			optionsMap[i].first,
			optionsMap[i].second, 
			i, 
			(float)optionsMap.size(), 80
		));
	}
	m_currentOption = m_options.begin();
}


GameScreenPauseState::~GameScreenPauseState()
{
	std::vector<GameOption<PauseOptions>*>::iterator it = m_options.begin();
	for (it; it != m_options.end(); ++it) {
		delete *it;
		*it = nullptr;
	}
}

void GameScreenPauseState::updateEvent(GameScreen& gameScreen)
{
	gameScreen.m_playerInputSystem.updateEvent(true);

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
		m_chosenOption = (*m_currentOption)->GetValue();
		m_optionSelected = true;
	}
}

void GameScreenPauseState::update(GameScreen& gameScreen, float elapsedTime)
{
	if (!m_optionSelected)
		return;
	switch (m_chosenOption) {
	case PauseOptions::CONTINUE:
		gameScreen.m_gameScreenState->setState(gameScreen, new GameScreenRunningState());
		break;
	case PauseOptions::RESTART:
		gameScreen.changeScreen(Screen::GAME, ConfigAction::NOTHING);
		break;
	case PauseOptions::MAIN_MENU:
		gameScreen.changeScreen(Screen::GAME_TITLE, ConfigAction::NOTHING);
		break;
	}
}

void GameScreenPauseState::draw(sf::RenderWindow& window, GameScreen& gameScreen)
{
	assert(m_options.size() != 0);

	AbstractGameScreenState::draw(window, gameScreen);

	std::vector<GameOption<PauseOptions>*>::iterator it = m_options.begin();
	for (it; it != m_options.end(); ++it) {
		bool selected = (*m_currentOption)->GetValue() == (*it)->GetValue();
		(*it)->Draw(window, selected);
	}
}

void GameScreenPauseState::renderSystems(
	GameScreen& gameScreen,
	sf::RenderWindow& window)
{
	gameScreen.m_spriteRenderingSystem.render(window);
	gameScreen.m_fixLayerRenderingSystem.render(window);
	gameScreen.m_drawableRenderingSystem.render(window);
	gameScreen.m_playerDataRenderingSystem.render(window);
}