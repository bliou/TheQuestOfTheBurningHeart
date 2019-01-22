#pragma once
#include "AbstractGameScreenState.h"
#include "GameOption.h"
#include <vector>

enum class PauseOptions {
	CONTINUE,
	RESTART,
	MAIN_MENU
};

class GameScreenPauseState: public AbstractGameScreenState
{
public:
	GameScreenPauseState();
	~GameScreenPauseState();

	virtual void update(
		GameScreen& gameScreen,
		float elapsedTime) override;
	virtual void updateEvent(GameScreen& gameScreen) override;
	virtual void draw(
		sf::RenderWindow& window,
		GameScreen& gameScreen) override;
private:
	// Text that holds the possibility
	std::vector<GameOption<PauseOptions>*> m_options;

	// Current option
	std::vector<GameOption<PauseOptions>*>::iterator m_currentOption;

	// The chosen option
	PauseOptions m_chosenOption;
	bool m_optionSelected;

	// A thin layout
	sf::RectangleShape m_loadingRect;


	virtual void renderSystems(
		GameScreen& gameScreen,
		sf::RenderWindow& window) override;
};

