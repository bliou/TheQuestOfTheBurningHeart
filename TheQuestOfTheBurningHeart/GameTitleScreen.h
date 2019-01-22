#pragma once
#include "AbstractScreen.h"
#include "GameOption.h"
#include <list>

enum class GameTitleOption {
	NEW_GAME,
	CONTINUE,
	CREDITS,
	EXIT
};

class GameTitleScreen : public AbstractScreen
{
public:
	GameTitleScreen();
	virtual ~GameTitleScreen();

	GameTitleScreen(const GameTitleScreen&) = delete;
	GameTitleScreen& operator=(const GameTitleScreen) = delete;

	virtual int run(sf::RenderWindow&);

private:
	// Text that holds the possibility
	std::vector<GameOption<GameTitleOption>*> m_options;

	// Current option
	std::vector<GameOption<GameTitleOption>*>::iterator m_currentOption;

	// The chosen option
	std::string m_chosenOption;

	void init();
};

