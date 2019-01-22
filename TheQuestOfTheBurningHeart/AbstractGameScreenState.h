#pragma once
#include <SFML/Graphics.hpp>

class GameScreen;

class AbstractGameScreenState
{
public:
	AbstractGameScreenState();
	virtual ~AbstractGameScreenState();

	virtual void update(GameScreen& gameScreen, float elapsedTime) = 0;
	virtual void updateEvent(GameScreen& gameScreen) = 0;
	virtual void draw(sf::RenderWindow& window, GameScreen& gameScreen);

	void setState(GameScreen& gameScreen, AbstractGameScreenState* newState);

protected:
	virtual void renderSystems(
		GameScreen& gameScreen,
		sf::RenderWindow& window) = 0;
};

