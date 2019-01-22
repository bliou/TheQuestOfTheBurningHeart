#pragma once
#include "AbstractGameScreenState.h"

class GameScreenDeadPlayerState : public AbstractGameScreenState
{
public:
	GameScreenDeadPlayerState();
	~GameScreenDeadPlayerState();

	virtual void update(
		GameScreen& gameScreen, 
		float elapsedTime) override;
	virtual void updateEvent(GameScreen& gameScreen) override;
	virtual void draw(
		sf::RenderWindow& window, 
		GameScreen& gameScreen) override;

protected:
	float m_loading;
	sf::RectangleShape m_loadingRect;

	void defaultStatesSystems(
		GameScreen& gameScreen,
		float elapsedTime
	);

	virtual void renderSystems(
		GameScreen& gameScreen,
		sf::RenderWindow& window) override;
};

