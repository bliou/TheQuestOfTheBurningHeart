#pragma once
#include "AbstractScreen.h"
#include <vector>

class ScreensManager
{
public:
	ScreensManager();
	~ScreensManager();

	static void run(sf::RenderWindow& window);
	static void updateGameScreen(int screen);

protected:
	static std::vector<AbstractScreen*> m_screens;
};