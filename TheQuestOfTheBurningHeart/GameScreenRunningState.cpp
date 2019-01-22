#include "GameScreenRunningState.h"
#include "GameScreenDeadPlayerState.h"
#include "GameScreenPauseState.h"
#include "GameScreen.h"
#include "InputManager.h"
#include <fstream>

GameScreenRunningState::GameScreenRunningState()
{
}


GameScreenRunningState::~GameScreenRunningState()
{
}

void GameScreenRunningState::update(GameScreen& gameScreen, float elapsedTime)
{
	gameScreen.m_gameScreenLoader->createEntities();
	gameScreen.m_world->refresh();

	updatePrePhysicSystems(gameScreen, elapsedTime);
	gameScreen.getWorld()->refresh();
	gameScreen.m_physicWorld->Step(elapsedTime, 10, 10);
	gameScreen.m_characterFootAdjustmentSystem.update(elapsedTime);
	gameScreen.getWorld()->refresh();
	updatePostPhysicsSystems(gameScreen, elapsedTime);
}

void GameScreenRunningState::updateEvent(GameScreen& gameScreen)
{
	updateInputSystems(gameScreen);
	if (InputManager::keyPressed(sf::Keyboard::P)
		|| InputManager::keyPressed(sf::Keyboard::Escape))
		gameScreen.m_gameScreenState->setState(gameScreen, new GameScreenPauseState());
}

void GameScreenRunningState::draw(
	sf::RenderWindow& window, 
	GameScreen& gameScreen)
{
	AbstractGameScreenState::draw(window, gameScreen);

	#ifdef _DEBUG
		if (gameScreen.m_isDebugging)
			gameScreen.m_physicWorld->DrawDebugData();
	#endif
}

void GameScreenRunningState::updateInputSystems(GameScreen& gameScreen)
{
	gameScreen.m_playerInputSystem.updateEvent(false);
	gameScreen.m_helperTileInputSystem.updateEvent();
	gameScreen.m_doorTileInputSystem.updateEvent();
}

void GameScreenRunningState::updatePrePhysicSystems(
	GameScreen& gameScreen, 
	float elapsedTime)
{
	gameScreen.m_timedMovementSystem.update(elapsedTime);
	gameScreen.m_infiniteMovementSystem.update(elapsedTime);
	gameScreen.m_closeAttackSystem.update(elapsedTime);
	gameScreen.m_rangeAttackSystem.update(elapsedTime);
	gameScreen.m_groundCharacterStateSystem.update(elapsedTime);
	gameScreen.m_characterSlopeTileSystem.update(elapsedTime);
	gameScreen.m_characterMovingTileSystem.update(elapsedTime);
	gameScreen.m_characterPhysicSystem.update(elapsedTime);
	gameScreen.m_tilePhysicSystem.update(elapsedTime);
	gameScreen.m_projectilePhysicSystem.update(elapsedTime);
	gameScreen.m_playerElementalTypeSystem.update(elapsedTime);
	gameScreen.m_projectileSystem.update(elapsedTime);
	gameScreen.m_resetTileSystem.update(elapsedTime);
	gameScreen.m_timedTileSystem.update(elapsedTime);
}

void GameScreenRunningState::updatePostPhysicsSystems(
	GameScreen& gameScreen,
	float elapsedTime)
{
	gameScreen.m_monsterActivatorCollisionSystem.update(elapsedTime);
	gameScreen.m_startMonsterSensorCollisionSystem.update(elapsedTime);
	gameScreen.m_startFootCollisionSystem.update(elapsedTime);
	gameScreen.m_startFallingSensorCollisionSystem.update(elapsedTime);
	gameScreen.m_startPlayerTileCollisionSystem.update(elapsedTime);
	gameScreen.m_startCloseAttackCollisionSystem.update(elapsedTime);
	gameScreen.m_startRangeAttackCollisionSystem.update(elapsedTime);
	gameScreen.m_screenCollisionSystem.update(elapsedTime);
	gameScreen.m_projectileCollisionSystem.update(elapsedTime);
	gameScreen.m_startEntityCollisionSystem.update(elapsedTime);

	gameScreen.m_endFootCollisionSystem.update(elapsedTime);
	gameScreen.m_endFallingSensorCollisionSystem.update(elapsedTime);
	gameScreen.m_endMonsterSensorCollisionSystem.update(elapsedTime);
	gameScreen.m_endPlayerTileCollisionSystem.update(elapsedTime);
	gameScreen.m_endCloseAttackCollisionSystem.update(elapsedTime);
	gameScreen.m_endEntityCollisionSystem.update(elapsedTime);

	gameScreen.m_physicsToPositionSystem.update(elapsedTime);
	gameScreen.m_groupTileSystem.update(elapsedTime);
	gameScreen.m_groundCharacterAnimationSystem.update(elapsedTime);
	gameScreen.m_activateTileAnimationSystem.update(elapsedTime);
	gameScreen.m_playerElementalTypeAnimationSystem.update(elapsedTime);
	gameScreen.m_animationSystem.update(elapsedTime);
	gameScreen.m_characterAnimationSystem.update(elapsedTime);
}

void GameScreenRunningState::renderSystems(
	GameScreen& gameScreen,
	sf::RenderWindow& window)
{
	gameScreen.m_cameraSystem.render(window);
	gameScreen.m_monsterRenderingSystem.render(window);
	gameScreen.m_timedTileRenderingSystem.render(window);
	gameScreen.m_resetTileRenderingSystem.render(window);
	gameScreen.m_spriteRenderingSystem.render(window);
	gameScreen.m_fixLayerRenderingSystem.render(window);
	gameScreen.m_drawableRenderingSystem.render(window);
	gameScreen.m_playerDataRenderingSystem.render(window);
	gameScreen.m_helperTileRenderingSystem.render(window);
#ifdef _DEBUG
	/// Added in debug so the physic boxes are well drawn
	gameScreen.m_drawableRenderingSystem.render(
		window, 
		(uint16)RenderElement::REST
	);
#endif
}