#include "GameScreenLoadingState.h"
#include "GameScreenRunningState.h"
#include "GameScreenAnimationState.h"
#include "GameScreenInformationState.h"
#include "GameScreen.h"
#include "GameScreenStartState.h"
#include "MusicsManager.h"
#include <fstream>

GameScreenLoadingState::GameScreenLoadingState(std::string configPath)
{
	nlohmann::json json;
	std::ifstream file(configPath);
	file >> json;

	m_startStateJson = json.at("startState");
	m_musicToPlay = json.at("musics").begin().value().get<std::string>();
	m_titleContent = json.at("levelTitle").get<std::string>();
}


GameScreenLoadingState::~GameScreenLoadingState()
{
}

void GameScreenLoadingState::update(
	GameScreen& gameScreen,
	float elapsedTime)
{
	if (gameScreen.m_gameScreenLoader->isReadyToLoad()
		&& !gameScreen.m_gameScreenLoader->isLoaded()) {
		gameScreen.m_gameScreenLoader->loadMusics();
		gameScreen.m_gameScreenLoader->loadSounds();
		gameScreen.m_gameScreenLoader->loadEntities();
		gameScreen.m_world->refresh();
		gameScreen.m_gameScreenLoader->loadGroups();
		gameScreen.m_world->refresh();
		gameScreen.m_gameScreenLoader->loadPatterns();
		gameScreen.m_world->refresh();
	}
	else {
		if (gameScreen.m_gameScreenLoader->isLoaded()) {
			MusicsManager::playMusic(m_musicToPlay);
			switch ((GameScreenStartState)m_startStateJson.at("state")) 
			{
			case GameScreenStartState::ANIMATION:
				gameScreen.m_gameScreenState->setState(
					gameScreen,
					new GameScreenAnimationState(
						m_startStateJson.at("data").get<std::string>()
					)
				);
				break;
			case GameScreenStartState::RUNNING:
				gameScreen.m_gameScreenState->setState(
					gameScreen,
					new GameScreenRunningState()
				);
				break;
			case GameScreenStartState::INFORMATION:
				gameScreen.m_gameScreenState->setState(
					gameScreen,
					new GameScreenInformationState(
						m_startStateJson.at("data").get<std::string>()
					)
				);
				gameScreen.getState()->update(gameScreen, elapsedTime);
				break;
			}
		}
	}
}

void GameScreenLoadingState::updateEvent(GameScreen&)
{

}

void GameScreenLoadingState::draw(
	sf::RenderWindow& window,
	GameScreen& gameScreen)
{
	if (!gameScreen.m_gameScreenLoader->isLoaded())
		gameScreen.m_gameScreenLoader->setGameScreenLoadingThread(
			this,
			gameScreen,
			window,
			m_titleContent);
	AbstractGameScreenState::draw(window, gameScreen);
} 

void GameScreenLoadingState::renderSystems(
	GameScreen& gameScreen,
	sf::RenderWindow& window)
{
}

void GameScreenLoadingState::renderLayer(
	sf::RenderWindow& window,
	GameScreen& gameScreen)
{
	gameScreen.m_fixLayerRenderingSystem.render(window);
	gameScreen.m_drawableRenderingSystem.render(
		window,
		(uint16)RenderElement::FIX_LAYER
	);
}