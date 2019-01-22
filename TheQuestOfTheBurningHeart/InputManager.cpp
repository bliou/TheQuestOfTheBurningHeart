#include "InputManager.h"

sf::Event InputManager::event;

InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::updateEvent(const sf::Event& event)
{
	InputManager::event = event;
}

bool InputManager::keyPressed(sf::Keyboard::Key key)
{
	return InputManager::event.key.code == key
		&& InputManager::event.type == sf::Event::KeyPressed;
}

bool InputManager::keyPressed(std::vector<sf::Keyboard::Key> keys)
{
	for (unsigned int i = 0; i < keys.size(); ++i) {
		if (InputManager::keyPressed(keys[i]))
			return true;
	}
	return false;
}

bool InputManager::keyReleased(sf::Keyboard::Key key)
{
	return InputManager::event.key.code == key
		&& InputManager::event.type == sf::Event::KeyReleased;
}

bool InputManager::keyReleased(std::vector<sf::Keyboard::Key> keys)
{
	for (unsigned int i = 0; i < keys.size(); ++i) {
		if (InputManager::keyReleased(keys[i]))
			return true;
	}
	return false;
}