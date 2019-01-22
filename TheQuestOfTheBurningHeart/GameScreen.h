#pragma once
#include "AbstractScreen.h"
#include "Box2D/Box2D.h"
#include "MapManager.h"
#include "AbstractGameScreenState.h"
#include "GameScreenLoader.h"
#include "Anax/anax.hpp"
#include "PlayerInputSystem.h"
#include "HelperTileInputSystem.h"
#include "DoorTileInputSystem.h"
#include "DialogInputSystem.h"
#include "CharacterFootAdjustmentSystem.h"
#include "TimedMovementSystem.h"
#include "InfiniteMovementSystem.h"
#include "CloseAttackSystem.h"
#include "RangeAttackSystem.h"
#include "GroundCharacterStateSystem.h"
#include "CharacterSlopeTileSystem.h"
#include "CharacterMovingTileSystem.h"
#include "CharacterPhysicSystem.h"
#include "TilePhysicSystem.h"
#include "ProjectilePhysicSystem.h"
#include "PlayerElementalTypeSystem.h"
#include "ProjectileSystem.h"
#include "TimedTileSystem.h"
#include "ResetTileSystem.h"
#include "DialogSystem.h"
#include "TransitionSystem.h"
#include "StartFootCollisionSystem.h"
#include "MonsterActivatorCollisionSystem.h"
#include "StartFallingSensorCollisionSystem.h"
#include "StartMonsterSensorCollisionSystem.h"
#include "StartPlayerTileCollisionSystem.h"
#include "StartCloseAttackCollisionSystem.h"
#include "StartRangeAttackCollisionSystem.h"
#include "ScreenCollisionSystem.h"
#include "ProjectileCollisionSystem.h"
#include "StartEntityCollisionSystem.h"
#include "EndFootCollisionSystem.h"
#include "EndFallingSensorCollisionSystem.h"
#include "EndMonsterSensorCollisionSystem.h"
#include "EndPlayerTileCollisionSystem.h"
#include "EndCloseAttackCollisionSystem.h"
#include "EndEntityCollisionSystem.h"
#include "PhysicToPositionSystem.h"
#include "GroupTileSystem.h"
#include "GroundCharacterAnimationSystem.h"
#include "ActivateTileAnimationSystem.h"
#include "PlayerElementalTypeAnimationSystem.h"
#include "AnimationSystem.h"
#include "CharacterAnimationSystem.h"
#include "CameraSystem.h"
#include "PlayerDataRenderingSystem.h"
#include "HelperTileRenderingSystem.h"
#include "MonsterRenderingSystem.h"
#include "TimedTileRenderingSystem.h"
#include "ResetTileRenderingSystem.h"
#include "SpriteRenderingSystem.h"
#include "FixLayerRenderingSystem.h"
#include "DrawableRenderingSystem.h"
#include "DialogRenderingSystem.h"
#include "DefaultStatesSystem.h"
#include "GetPlayerSystem.h"
#include "GetAnimationEntitySystem.h"
#include "GetTileIdByPositionSystem.h"
#include "GetEntitiesIdByDataIdSystem.h"
#include "KillSystem.h"
#include "ProjectileClearSystem.h"
#include "ClearDyingMonstersSystem.h"
#include "ConfigAction.h"

class GameScreen: public AbstractScreen
{
	friend class AbstractGameScreenState;
	friend class GameScreenLoadingState;
	friend class GameScreenRunningState;
	friend class GameScreenDeadPlayerState;
	friend class GameScreenPauseState;
	friend class GameScreenAnimationState;
	friend class GameScreenInformationState;

public:
	GameScreen();
	~GameScreen();

	virtual int run(sf::RenderWindow& window);

	void clearConfig();
	void nextGameLevel();
	void changeScreen(
		Screen screen,
		ConfigAction configAction
	);

	void update(int screen);

	b2World* getPhysicWorld() const;
	anax::World* getWorld() const;
	AbstractGameScreenState* getState() const;
	std::string getConfigPath() const;
	uint64_t getPlayerId();
	uint64_t getTileIdByPosition(sf::Vector2f position);
	std::list<uint64_t> getEntitiesIdByDataId(std::string dataId);

	void addEntityToCreate(
		std::string id,
		sf::Vector2f position);
	void addEntityToCreate(
		std::string id,
		sf::Vector2f position,
		nlohmann::json data);
	void addPatternToEntity(
		std::string patternId,
		uint64_t entityId
	);

	void killPlayer(anax::Entity& player);

	void setIsBonusLevel(bool isBonusLevel);

private:
#ifdef _DEBUG
	bool m_isDebugging;
#endif
	int m_nextScreen;
	int m_gameLevel;
	std::string m_configPath;
	AbstractGameScreenState* m_gameScreenState;
	bool m_isBonusLevel;

	MapManager* m_mapManager;
	GameScreenLoader* m_gameScreenLoader;

	b2World* m_physicWorld;
	anax::World* m_world;
	b2Body* m_body;

	void createScreenBody();

	void unLoadGameScreen();
	void init();
	void initSystems();

	// All the systems used in the game
	PlayerInputSystem m_playerInputSystem;
	HelperTileInputSystem m_helperTileInputSystem;
	DoorTileInputSystem m_doorTileInputSystem;
	DialogInputSystem m_dialogInputSystem;

	TimedMovementSystem m_timedMovementSystem;
	InfiniteMovementSystem m_infiniteMovementSystem;
	CloseAttackSystem m_closeAttackSystem;
	RangeAttackSystem m_rangeAttackSystem;
	GroundCharacterStateSystem m_groundCharacterStateSystem;
	CharacterSlopeTileSystem m_characterSlopeTileSystem;
	CharacterMovingTileSystem m_characterMovingTileSystem;
	CharacterPhysicSystem m_characterPhysicSystem;
	TilePhysicSystem m_tilePhysicSystem;
	ProjectilePhysicSystem m_projectilePhysicSystem;
	PlayerElementalTypeSystem m_playerElementalTypeSystem;
	ProjectileSystem m_projectileSystem;
	TimedTileSystem m_timedTileSystem;
	ResetTileSystem m_resetTileSystem;
	DialogSystem m_dialogSystem;
	TransitionSystem m_transitionSystem;

	CharacterFootAdjustmentSystem m_characterFootAdjustmentSystem;
	MonsterActivatorCollisionSystem m_monsterActivatorCollisionSystem;
	StartFootCollisionSystem m_startFootCollisionSystem;
	StartMonsterSensorCollisionSystem m_startMonsterSensorCollisionSystem;
	StartFallingSensorCollisionSystem m_startFallingSensorCollisionSystem;
	StartPlayerTileCollisionSystem m_startPlayerTileCollisionSystem;
	StartCloseAttackCollisionSystem m_startCloseAttackCollisionSystem;
	StartRangeAttackCollisionSystem m_startRangeAttackCollisionSystem;
	ScreenCollisionSystem m_screenCollisionSystem;
	ProjectileCollisionSystem m_projectileCollisionSystem;
	StartEntityCollisionSystem m_startEntityCollisionSystem;
	EndFootCollisionSystem m_endFootCollisionSystem;
	EndFallingSensorCollisionSystem m_endFallingSensorCollisionSystem;
	EndMonsterSensorCollisionSystem m_endMonsterSensorCollisionSystem;
	EndPlayerTileCollisionSystem m_endPlayerTileCollisionSystem;
	EndCloseAttackCollisionSystem m_endCloseAttackCollisionSystem;
	EndEntityCollisionSystem m_endEntityCollisionSystem;

	PhysicToPositionSystem m_physicsToPositionSystem;
	GroupTileSystem m_groupTileSystem;
	GroundCharacterAnimationSystem m_groundCharacterAnimationSystem;
	ActivateTileAnimationSystem m_activateTileAnimationSystem;
	PlayerElementalTypeAnimationSystem m_playerElementalTypeAnimationSystem;
	AnimationSystem m_animationSystem;
	CharacterAnimationSystem m_characterAnimationSystem;

	CameraSystem m_cameraSystem;
	PlayerDataRenderingSystem m_playerDataRenderingSystem;
	HelperTileRenderingSystem m_helperTileRenderingSystem;
	MonsterRenderingSystem m_monsterRenderingSystem;
	TimedTileRenderingSystem m_timedTileRenderingSystem;
	ResetTileRenderingSystem m_resetTileRenderingSystem;
	SpriteRenderingSystem m_spriteRenderingSystem;
	FixLayerRenderingSystem m_fixLayerRenderingSystem;
	DrawableRenderingSystem m_drawableRenderingSystem;
	DialogRenderingSystem m_dialogRenderingSystem;

	DefaultStatesSystem m_defaultStatesSystem;
	GetPlayerSystem m_getPlayerSystem;
	GetAnimationEntityIdSystem m_getAnimationEntityIdSystem;
	GetTileIdByPositionSystem m_getTileIdByPositionSystem;
	GetEntitiesIdByDataIdSystem m_getEntitiesIdByDataIdSystem;
	KillSystem m_killSystem;
	ProjectileClearSystem m_projectileClearSystem;
	ClearDyingMonstersSystem m_clearDyingMonstersSystem;
};

