#pragma once
#include "AbstractGameScreenState.h"

class GameScreenInformationState: public AbstractGameScreenState
{
public:
	GameScreenInformationState(
		std::string informationContent);
	~GameScreenInformationState();

	virtual void update(
		GameScreen& gameScreen,
		float elapsedTime) override;
	virtual void updateEvent(GameScreen& gameScreen) override;
	virtual void draw(
		sf::RenderWindow& window,
		GameScreen& gameScreen) override;

protected:
	sf::Sprite m_fullHelper;
	sf::Text m_informationText;
	sf::Text m_playText;

	virtual void renderSystems(
		GameScreen& gameScreen,
		sf::RenderWindow& window) override;
};

