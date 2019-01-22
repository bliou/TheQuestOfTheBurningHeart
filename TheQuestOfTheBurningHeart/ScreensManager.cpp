#include "GameScreen.h"
#include "GameTitleScreen.h"
#include "CreditsScreen.h"
#include "ScreensManager.h"

std::vector<AbstractScreen*> ScreensManager::m_screens;

ScreensManager::ScreensManager()
{
}


ScreensManager::~ScreensManager()
{
	for (AbstractScreen* screen : m_screens)
	{
		delete screen;
		screen = nullptr;
	}
}

void ScreensManager::run(sf::RenderWindow& window)
{
	//Applications variables
	int screen = 0;

	//Screens preparations
	GameTitleScreen gameTitleScreen;
	GameScreen gameScreen;
	CreditsScreen creditsScreen;
	m_screens.push_back(&gameTitleScreen);
	m_screens.push_back(&gameScreen);
	m_screens.push_back(&creditsScreen);


	//Main loop
	while (screen >= 0)
	{
		screen = m_screens[screen]->run(window);
	}
}

void ScreensManager::updateGameScreen(int screen)
{
	((GameScreen*)m_screens[(int)Screen::GAME])->update(screen);
}