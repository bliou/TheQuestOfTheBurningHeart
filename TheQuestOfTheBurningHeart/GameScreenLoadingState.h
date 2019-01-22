#pragma once
#include "AbstractGameScreenState.h"
#include "json.hpp"

class GameScreenLoadingState: public AbstractGameScreenState
{
public:
	GameScreenLoadingState(std::string configPath);
	virtual ~GameScreenLoadingState();

	virtual void update(
		GameScreen& gameScreen, 
		float elapsedTime) override;
	virtual void updateEvent(GameScreen& gameScreen) override;
	virtual void draw(
		sf::RenderWindow& window, 
		GameScreen& gameScreen) override;

	void renderLayer(
		sf::RenderWindow& window,
		GameScreen& gameScreen
	);

private:
	nlohmann::json m_startStateJson;

	virtual void renderSystems(
		GameScreen& gameScreen,
		sf::RenderWindow& window) override;

	std::string m_titleContent;
	std::string m_musicToPlay;
};

