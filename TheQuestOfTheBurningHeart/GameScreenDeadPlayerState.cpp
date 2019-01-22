#include "GameScreenDeadPlayerState.h"
#include "GameScreenLoadingState.h"
#include "GameScreen.h"
#include "FontsManager.h"
#include "LifeComponent.h"
#include "Helpers.h"
#include "ConfigManager.h"
#include <anax/anax.hpp>

GameScreenDeadPlayerState::GameScreenDeadPlayerState()
	: m_loadingRect(),
	m_loading(0.0f)
{
	m_loadingRect.setSize(sf::Vector2f(screenSize));
	m_loadingRect.setPosition(sf::Vector2f(0.0f, 0.0f));
}


GameScreenDeadPlayerState::~GameScreenDeadPlayerState()
{
}

void GameScreenDeadPlayerState::update(
	GameScreen& gameScreen, 
	float elapsedTime)
{
	// Clear the projectiles
	gameScreen.m_projectileClearSystem.update(elapsedTime);

	// Clear the monsters
	gameScreen.m_clearDyingMonstersSystem.update(elapsedTime);

	// Change the transparency of the dead rectangle
	m_loading += 100.0f * elapsedTime;

	// When the loading is over, then switch to the ready game state
	if (m_loading >= 255.0f) {
		uint64_t playerId = gameScreen.m_getPlayerSystem.getPlayerId();
		anax::Entity player = gameScreen.getWorld()->getEntity(playerId);
		if (player.getComponent<LifeComponent>().lifes == 0) {
			gameScreen.changeScreen(Screen::GAME_TITLE, ConfigAction::CLEAR);
		}
		else {
			if (gameScreen.m_isBonusLevel) {
				gameScreen.nextGameLevel();
				gameScreen.changeScreen(Screen::GAME, ConfigAction::FULL_SAVE);
			}
			else {
				defaultStatesSystems(gameScreen, elapsedTime);
				gameScreen.m_gameScreenState->setState(
					gameScreen,
					new GameScreenLoadingState(gameScreen.getConfigPath())
				);
			}
		}
	}
}

void GameScreenDeadPlayerState::updateEvent(GameScreen& gameScreen)
{
}

void GameScreenDeadPlayerState::draw(sf::RenderWindow& window, GameScreen& gameScreen)
{
	AbstractGameScreenState::draw(window, gameScreen);
	sf::Vector2f viewCenter = window.getView().getCenter();

	m_loadingRect.setFillColor(sf::Color(0, 0, 0, (int)m_loading));
	m_loadingRect.setPosition(sf::Vector2f(
		viewCenter.x - screenSize.x / 2.f,
		viewCenter.y - screenSize.y / 2.f
	));
	window.draw(m_loadingRect);
}

void GameScreenDeadPlayerState::defaultStatesSystems(
	GameScreen& gameScreen,
	float elapsedTime)
{
	gameScreen.m_defaultStatesSystem.update(elapsedTime);
}

void GameScreenDeadPlayerState::renderSystems(
	GameScreen& gameScreen,
	sf::RenderWindow& window)
{
	gameScreen.m_spriteRenderingSystem.render(window);
	gameScreen.m_fixLayerRenderingSystem.render(window);
	gameScreen.m_drawableRenderingSystem.render(window);
}