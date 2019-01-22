#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class InputManager
{
public:
	InputManager();
	~InputManager();

	InputManager(const InputManager&) = delete;
	InputManager& operator=(const InputManager&) = delete;

	static void updateEvent(const sf::Event&);

	static bool keyPressed(sf::Keyboard::Key);
	static bool keyPressed(std::vector<sf::Keyboard::Key>);

	static bool keyReleased(sf::Keyboard::Key);
	static bool keyReleased(std::vector<sf::Keyboard::Key>);

private:
	static sf::Event event;
};

