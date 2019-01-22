#pragma once
#include "AbstractGameScreenState.h"

class GameScreenRunningState: public AbstractGameScreenState
{
public:
	GameScreenRunningState();
	virtual ~GameScreenRunningState();

	virtual void update(
		GameScreen& gameScreen, 
		float elapsedTime) override;
	virtual void updateEvent(GameScreen& gameScreen) override;
	virtual void draw(
		sf::RenderWindow& window, 
		GameScreen& gameScreen) override;

protected:
	void updateInputSystems(GameScreen& gameScreen);
	void updatePrePhysicSystems(
		GameScreen& gameScreen,
		float elapsedTime);
	void updatePostPhysicsSystems(
		GameScreen& gameScreen,
		float elapsedTime);
	virtual void renderSystems(
		GameScreen& gameScreen,
		sf::RenderWindow& window) override;
};

