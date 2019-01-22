#include "AbstractGameScreenState.h"
#include "GameScreen.h"


AbstractGameScreenState::AbstractGameScreenState()
{
}


AbstractGameScreenState::~AbstractGameScreenState()
{
}

void AbstractGameScreenState::setState(GameScreen& gameScreen, AbstractGameScreenState* newState)
{
	AbstractGameScreenState* oldState = gameScreen.m_gameScreenState;
	gameScreen.m_gameScreenState = newState;
	delete oldState;
	oldState = nullptr;
}

void AbstractGameScreenState::draw(sf::RenderWindow& window, GameScreen& gameScreen)
{
	renderSystems(gameScreen, window);
}