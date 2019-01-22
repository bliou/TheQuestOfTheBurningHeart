#include "GameScreenAnimationState.h"
#include "GameScreen.h"
#include "BlockAnimationTimerComponent.h"
#include <fstream>

const std::string GameScreenAnimationState::animationPath = "Resources/Animations/";

GameScreenAnimationState::GameScreenAnimationState(
	std::string animationFileName)
	: m_animationFileName(animationFileName),
	m_currentTimer(0.f),
	m_actionsFactory()
{
	std::ifstream file(animationPath + animationFileName);
	file >> m_startStateJson;
}


GameScreenAnimationState::~GameScreenAnimationState()
{
	nlohmann::json::iterator it = m_startStateJson.at("actions").begin();
	for (it; it != m_startStateJson.at("actions").end(); ++it) {
		it.value().at("isUsed") = false;
	}
	std::ofstream ofile(animationPath + m_animationFileName);
	ofile << m_startStateJson;
}

void GameScreenAnimationState::update(
	GameScreen& gameScreen,
	float elapsedTime)
{
	gameScreen.m_killSystem.update();

	bool isTimerBlocked = false;
	auto entities = gameScreen.m_world->getEntities();
	for (auto& entity : entities) {
		if (entity.hasComponent<BlockAnimationTimerComponent>()) {
			isTimerBlocked = true;
			break;
		}
	}
	if (!isTimerBlocked) {
		m_currentTimer += elapsedTime;

		m_actionsFactory.createAnimationActions(
			m_startStateJson,
			gameScreen,
			m_currentTimer
		);
	}

	gameScreen.m_gameScreenLoader->createEntities();
	gameScreen.m_world->refresh();

	updatePrePhysicSystems(gameScreen, elapsedTime);

	gameScreen.m_physicWorld->Step(elapsedTime, 10, 10);
	gameScreen.m_characterFootAdjustmentSystem.update(elapsedTime);
	gameScreen.m_world->refresh();
	updatePostPhysicsSystems(gameScreen, elapsedTime);

}

void GameScreenAnimationState::updateEvent(GameScreen& gameScreen)
{
	gameScreen.m_dialogInputSystem.updateEvent();
}

void GameScreenAnimationState::draw(
	sf::RenderWindow& window,
	GameScreen& gameScreen)
{
	AbstractGameScreenState::draw(window, gameScreen);

	#ifdef _DEBUG
		if (gameScreen.m_isDebugging)
			gameScreen.m_physicWorld->DrawDebugData();
	#endif
}

uint64_t GameScreenAnimationState::getAnimationEntity(
	GameScreen& gameScreen,
	std::string animationId) const
{
	return gameScreen.m_getAnimationEntityIdSystem.getEntityId(animationId);
}

void GameScreenAnimationState::updatePrePhysicSystems(
	GameScreen& gameScreen,
	float elapsedTime)
{
	gameScreen.m_timedMovementSystem.update(elapsedTime);
	gameScreen.m_infiniteMovementSystem.update(elapsedTime);
	gameScreen.m_groundCharacterStateSystem.update(elapsedTime);
	gameScreen.m_characterSlopeTileSystem.update(elapsedTime);
	gameScreen.m_characterMovingTileSystem.update(elapsedTime);
	gameScreen.m_characterPhysicSystem.update(elapsedTime);
	gameScreen.m_tilePhysicSystem.update(elapsedTime);
	gameScreen.m_playerElementalTypeSystem.update(elapsedTime);
	gameScreen.m_resetTileSystem.update(elapsedTime);
	gameScreen.m_timedTileSystem.update(elapsedTime);
	gameScreen.m_dialogSystem.update(elapsedTime);
	gameScreen.m_transitionSystem.update(elapsedTime);
}

void GameScreenAnimationState::updatePostPhysicsSystems(
	GameScreen& gameScreen,
	float elapsedTime)
{
	gameScreen.m_monsterActivatorCollisionSystem.update(elapsedTime);
	gameScreen.m_startMonsterSensorCollisionSystem.update(elapsedTime);
	gameScreen.m_startFootCollisionSystem.update(elapsedTime);
	gameScreen.m_startFallingSensorCollisionSystem.update(elapsedTime);
	gameScreen.m_startPlayerTileCollisionSystem.update(elapsedTime);
	gameScreen.m_screenCollisionSystem.update(elapsedTime);
	gameScreen.m_projectileCollisionSystem.update(elapsedTime);
	gameScreen.m_startEntityCollisionSystem.update(elapsedTime);

	gameScreen.m_endFootCollisionSystem.update(elapsedTime);
	gameScreen.m_endFallingSensorCollisionSystem.update(elapsedTime);
	gameScreen.m_endMonsterSensorCollisionSystem.update(elapsedTime);
	gameScreen.m_endPlayerTileCollisionSystem.update(elapsedTime);
	gameScreen.m_endEntityCollisionSystem.update(elapsedTime);

	gameScreen.m_physicsToPositionSystem.update(elapsedTime);
	gameScreen.m_groupTileSystem.update(elapsedTime);
	gameScreen.m_groundCharacterAnimationSystem.update(elapsedTime);
	gameScreen.m_activateTileAnimationSystem.update(elapsedTime);
	gameScreen.m_playerElementalTypeAnimationSystem.update(elapsedTime);
	gameScreen.m_animationSystem.update(elapsedTime);
	gameScreen.m_characterAnimationSystem.update(elapsedTime);
}

void GameScreenAnimationState::renderSystems(
	GameScreen& gameScreen,
	sf::RenderWindow& window)
{
	gameScreen.m_cameraSystem.render(window);
	gameScreen.m_helperTileRenderingSystem.render(window);
	gameScreen.m_monsterRenderingSystem.render(window);
	gameScreen.m_resetTileRenderingSystem.render(window);
	gameScreen.m_timedTileRenderingSystem.render(window);
	gameScreen.m_spriteRenderingSystem.render(window);
	gameScreen.m_fixLayerRenderingSystem.render(window);
	gameScreen.m_drawableRenderingSystem.render(window);
	gameScreen.m_dialogRenderingSystem.render(window);
}
