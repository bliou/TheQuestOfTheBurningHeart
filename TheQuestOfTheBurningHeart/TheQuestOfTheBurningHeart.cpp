#include <SFML/Graphics.hpp>
#include "Helpers.h"
#include "ScreensManager.h"

int main()
{
	////Window creation
	sf::RenderWindow window(
		sf::VideoMode(screenSize.x, screenSize.y), 
		"The quest for the Burning Heart");
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	ScreensManager::run(window);

	return EXIT_SUCCESS;
}