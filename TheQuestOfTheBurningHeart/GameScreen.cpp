#include "GameScreen.h"
#include "b2GLDraw.h"
#include "Helpers.h"
#include "InputManager.h"
#include "ContactsListener.h"
#include "GameScreenLoadingState.h"
#include "GameScreenRunningState.h"
#include "GameScreenDeadPlayerState.h"
#include "ConfigManager.h"
#include "PhysicsEntityCategory.h"
#include "MusicsManager.h"
#include "SoundsManager.h"
#include <sstream>

GameScreen::GameScreen()
	: m_world(nullptr),
	m_nextScreen(-1),
	m_gameScreenState(nullptr),
	m_physicWorld(nullptr),
	m_mapManager(nullptr),
	m_gameScreenLoader(nullptr),
	m_gameLevel(1),
	m_doorTileInputSystem(*this),
	m_startPlayerTileCollisionSystem(*this),
	m_startEntityCollisionSystem(*this),
	m_screenCollisionSystem(*this),
	m_closeAttackSystem(*this),
	m_rangeAttackSystem(*this),
	m_helperTileInputSystem(*this),
	m_groundCharacterStateSystem(*this),
	m_projectileCollisionSystem(*this),
	m_timedMovementSystem(*this),
	m_defaultStatesSystem(*this),
	m_isBonusLevel(false)
{
#ifdef _DEBUG
	m_isDebugging = true;
#endif
}


GameScreen::~GameScreen()
{
	unLoadGameScreen();
}

int GameScreen::run(sf::RenderWindow& window)
{
	sf::Clock clock;
	m_world = new anax::World();

	/** Prepare the world */
	b2Vec2 gravity(0.f, 18.f);
	m_physicWorld = new b2World(gravity);
	b2GLDraw debugDraw;
	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	flags += b2Draw::e_centerOfMassBit;
	debugDraw.SetFlags(flags);
	m_physicWorld->SetDebugDraw(&debugDraw);
	ContactsListener contactsListener = ContactsListener(*this);
	m_physicWorld->SetContactListener(&contactsListener);

	init();
	createScreenBody();

	sf::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				unLoadGameScreen();
				return -1;
			}
			InputManager::updateEvent(event);
#ifdef _DEBUG
			if (InputManager::keyPressed(sf::Keyboard::D)) {
				m_isDebugging = !m_isDebugging;
			}

			if (InputManager::keyPressed(sf::Keyboard::R)) {
				unLoadGameScreen();
				return (int)Screen::GAME;
			}
#endif
			m_gameScreenState->updateEvent(*this);
		}
		// Start by updating the world
		float elapsedTime = clock.restart().asSeconds();

		window.clear(sf::Color::White);

		if (!m_changeScreen)
			m_gameScreenState->update(*this, elapsedTime);
		else {
			unLoadGameScreen();
			return m_nextScreen;
		}

		m_gameScreenState->draw(window, *this);
		window.display();
	}
	
	return -1;
}

void GameScreen::unLoadGameScreen()
{
	MusicsManager::stopMusic();

	delete m_mapManager;
	m_mapManager = nullptr;

	delete m_gameScreenState;
	m_gameScreenState = nullptr;

	delete m_gameScreenLoader;
	m_gameScreenLoader = nullptr;

	if (m_world)
		m_world->clear();
	delete m_world;
	m_world = nullptr;

	delete m_physicWorld;
	m_physicWorld = nullptr;
}

void GameScreen::init()
{
	std::stringstream ss;
	ss << "Resources/Maps/map" << m_gameLevel << ".txt";
	std::string mapPath = ss.str();
	ss.str("");
	ss << "Resources/Data/data" << m_gameLevel << ".json";
	m_configPath = ss.str();

	m_changeScreen = false;
	m_mapManager = new MapManager();
	m_mapManager->loadMap(mapPath);

	initSystems();

	m_gameScreenState = new GameScreenLoadingState(m_configPath);
	m_gameScreenLoader = new GameScreenLoader(
		*this,
		m_mapManager->getMap(),
		m_mapManager->getEntitiesToLoad(),
		m_configPath
	);
}

void GameScreen::initSystems()
{
	m_world->addSystem(m_playerInputSystem);
	m_world->addSystem(m_helperTileInputSystem);
	m_world->addSystem(m_doorTileInputSystem);
	m_world->addSystem(m_dialogInputSystem);

	m_world->addSystem(m_timedMovementSystem);
	m_world->addSystem(m_infiniteMovementSystem);
	m_world->addSystem(m_closeAttackSystem);
	m_world->addSystem(m_rangeAttackSystem);
	m_world->addSystem(m_groundCharacterStateSystem);
	m_world->addSystem(m_characterSlopeTileSystem);
	m_world->addSystem(m_characterMovingTileSystem);
	m_world->addSystem(m_characterPhysicSystem);
	m_world->addSystem(m_tilePhysicSystem);
	m_world->addSystem(m_projectilePhysicSystem);
	m_world->addSystem(m_playerElementalTypeSystem);
	m_world->addSystem(m_projectileSystem);
	m_world->addSystem(m_timedTileSystem);
	m_world->addSystem(m_resetTileSystem);
	m_world->addSystem(m_dialogSystem);
	m_world->addSystem(m_transitionSystem);

	m_world->addSystem(m_characterFootAdjustmentSystem);
	m_world->addSystem(m_monsterActivatorCollisionSystem);
	m_world->addSystem(m_startFootCollisionSystem);
	m_world->addSystem(m_startFallingSensorCollisionSystem);
	m_world->addSystem(m_startMonsterSensorCollisionSystem);
	m_world->addSystem(m_startPlayerTileCollisionSystem);
	m_world->addSystem(m_startCloseAttackCollisionSystem);
	m_world->addSystem(m_startRangeAttackCollisionSystem);
	m_world->addSystem(m_screenCollisionSystem);
	m_world->addSystem(m_projectileCollisionSystem);
	m_world->addSystem(m_startEntityCollisionSystem);
	m_world->addSystem(m_endFootCollisionSystem);
	m_world->addSystem(m_endFallingSensorCollisionSystem);
	m_world->addSystem(m_endMonsterSensorCollisionSystem);
	m_world->addSystem(m_endPlayerTileCollisionSystem);
	m_world->addSystem(m_endCloseAttackCollisionSystem);
	m_world->addSystem(m_endEntityCollisionSystem);

	m_world->addSystem(m_physicsToPositionSystem);
	m_world->addSystem(m_groupTileSystem);
	m_world->addSystem(m_groundCharacterAnimationSystem);
	m_world->addSystem(m_activateTileAnimationSystem);
	m_world->addSystem(m_playerElementalTypeAnimationSystem);
	m_world->addSystem(m_animationSystem);
	m_world->addSystem(m_characterAnimationSystem);

	m_world->addSystem(m_cameraSystem);
	m_cameraSystem.setMapSize(m_mapManager->getMapSize());
	m_world->addSystem(m_playerDataRenderingSystem);
	m_world->addSystem(m_helperTileRenderingSystem);
	m_world->addSystem(m_monsterRenderingSystem);
	m_world->addSystem(m_timedTileRenderingSystem);
	m_world->addSystem(m_resetTileRenderingSystem);
	m_world->addSystem(m_spriteRenderingSystem);
	m_world->addSystem(m_fixLayerRenderingSystem);
	m_world->addSystem(m_drawableRenderingSystem);
	m_world->addSystem(m_dialogRenderingSystem);

	m_world->addSystem(m_defaultStatesSystem);
	m_world->addSystem(m_getPlayerSystem);
	m_world->addSystem(m_getAnimationEntityIdSystem);
	m_world->addSystem(m_getTileIdByPositionSystem);
	m_world->addSystem(m_getEntitiesIdByDataIdSystem);
	m_world->addSystem(m_killSystem);
	m_world->addSystem(m_projectileClearSystem);
	m_world->addSystem(m_clearDyingMonstersSystem);
}

void GameScreen::clearConfig()
{
	m_gameLevel = 1;
}

void GameScreen::nextGameLevel()
{
	m_gameLevel++;
}

void GameScreen::changeScreen(
	Screen screen,
	ConfigAction configAction)
{
	MusicsManager::stopMusic();

	m_nextScreen = (int)screen;
	m_changeScreen = true;

	switch (configAction)
	{
	case ConfigAction::FULL_SAVE:
	{
		anax::Entity player = m_world->getEntity(m_getPlayerSystem.getPlayerId());
		sPlayerData playerData;
		playerData.playerLife = player.getComponent<LifeComponent>().lifes;
		playerData.playerCoins = player.getComponent<PlayerCoinsComponent>().coins;
		auto& playerElementalTypes = player.getComponent<PlayerElementalTypeComponent>().playerElementalTypes;
		playerData.playerElementalTypes.fire = playerElementalTypes[ElementalType::FIRE].remainingTime;

		ConfigManager::saveConfig(
			playerData,
			m_gameLevel
		);
		break;
	}
	case ConfigAction::LEVEL_SAVE:
		ConfigManager::saveConfig(m_gameLevel);
		break;
	case ConfigAction::CLEAR:
		ConfigManager::clearConfig();
		break;
	}
}

void GameScreen::update(int gameLevel)
{
	m_gameLevel = gameLevel;
}

b2World* GameScreen::getPhysicWorld() const
{
	return m_physicWorld;
}

anax::World* GameScreen::getWorld() const
{
	return m_world;
}

AbstractGameScreenState* GameScreen::getState() const
{
	return m_gameScreenState;
}

std::string GameScreen::getConfigPath() const
{
	return m_configPath;
}

uint64_t GameScreen::getPlayerId()
{
	return m_getPlayerSystem.getPlayerId();
}

uint64_t GameScreen::getTileIdByPosition(sf::Vector2f position)
{
	return m_getTileIdByPositionSystem.getId(position);
}

std::list<uint64_t> GameScreen::getEntitiesIdByDataId(
	std::string dataId)
{
	return m_getEntitiesIdByDataIdSystem.getIds(dataId);
}

void GameScreen::addEntityToCreate(
	std::string id,
	sf::Vector2f position)
{
	m_gameScreenLoader->addEntityToCreate(
		id,
		position
	);
}

void GameScreen::addEntityToCreate(
	std::string id,
	sf::Vector2f position,
	nlohmann::json data)
{
	m_gameScreenLoader->addEntityToCreate(
		id,
		position,
		data
	);
}

void GameScreen::addPatternToEntity(
	std::string patternId,
	uint64_t entityId)
{
	m_gameScreenLoader->addPatternToEntity(
		patternId,
		entityId
	);
}


void GameScreen::killPlayer(anax::Entity& player)
{
	auto& lifes = player.getComponent<LifeComponent>().lifes;
	auto& state = player.getComponent<GroundCharacterStateComponent>().state;
	state = GroundCharacterState::DYING;
	MusicsManager::stopMusic();
	SoundsManager::playSound(SoundType::PLAYER_DEATH);
	if (!m_isBonusLevel)
		lifes--;
	if (lifes < 0)
		throw std::runtime_error("Life canno't be negative");

	m_gameScreenState->setState(*this, new GameScreenDeadPlayerState());
}

void GameScreen::setIsBonusLevel(bool isBonusLevel)
{
	m_isBonusLevel = isBonusLevel;
}

void GameScreen::createScreenBody()
{
	b2BodyDef BodyDef;
	sf::Vector2i mapSize = m_mapManager->getMapSize();
	BodyDef.position = b2Vec2(mapSize.x / 2 / B2SCALE, mapSize.y / 2 / B2SCALE);
	BodyDef.type = b2_staticBody;
	BodyDef.fixedRotation = true;
	m_body = m_physicWorld->CreateBody(&BodyDef);
	m_body->SetUserData(this);


	b2PolygonShape leftShape;
	leftShape.SetAsBox(1 / 2 / B2SCALE, mapSize.y / 2 / B2SCALE, b2Vec2(-mapSize.x / 2 / B2SCALE, 0.f), 0.f);
	b2FixtureDef leftFixture;
	leftFixture.density = 0.f;
	leftFixture.friction = 0.f;
	leftFixture.shape = &leftShape;
	leftFixture.filter.categoryBits = (uint16)PhysicsEntityCategory::SCREEN;
	leftFixture.filter.maskBits = (uint16)PhysicsEntityCategory::PLAYER 
		| (uint16)PhysicsEntityCategory::MONSTER;
	leftFixture.userData = reinterpret_cast<uint64_t*>(
		ScreenSide::LEFT_SCREEN
	);
	m_body->CreateFixture(&leftFixture);

	b2PolygonShape topShape;
	topShape.SetAsBox(mapSize.x / 2 / B2SCALE, 1 / 2 / B2SCALE, b2Vec2(0.f, -mapSize.y / 2 / B2SCALE), 0.f);
	b2FixtureDef topFixture;
	topFixture.density = 0.f;
	topFixture.friction = 0.f;
	topFixture.shape = &topShape;
	topFixture.filter.categoryBits = (uint16)PhysicsEntityCategory::SCREEN;
	topFixture.filter.maskBits = (uint16)PhysicsEntityCategory::PLAYER 
		| (uint16)PhysicsEntityCategory::MONSTER;
	topFixture.userData = reinterpret_cast<uint64_t*>(
		ScreenSide::TOP_SCREEN
	);
	m_body->CreateFixture(&topFixture);

	b2PolygonShape rightShape;
	rightShape.SetAsBox(1 / 2 / B2SCALE, mapSize.y / 2 / B2SCALE, b2Vec2(mapSize.x / 2 / B2SCALE, 0.f), 0.f);
	b2FixtureDef rightFixture;
	rightFixture.density = 0.f;
	rightFixture.friction = 0.f;
	rightFixture.shape = &rightShape;
	rightFixture.filter.categoryBits = (uint16)PhysicsEntityCategory::SCREEN;
	rightFixture.filter.maskBits = (uint16)PhysicsEntityCategory::PLAYER
		| (uint16)PhysicsEntityCategory::MONSTER;
	rightFixture.userData = reinterpret_cast<uint64_t*>(
		ScreenSide::RIGHT_SCREEN
	);
	m_body->CreateFixture(&rightFixture);

	b2PolygonShape bottomShape;
	bottomShape.SetAsBox(mapSize.x / 2 / B2SCALE, 1 / 2 / B2SCALE, b2Vec2(0.f, mapSize.y / 2 / B2SCALE), 0.f);
	b2FixtureDef bottomFixture;
	bottomFixture.density = 0.f;
	bottomFixture.friction = 0.f;
	bottomFixture.shape = &bottomShape;
	bottomFixture.filter.categoryBits = (uint16)PhysicsEntityCategory::SCREEN;
	bottomFixture.filter.maskBits = (uint16)PhysicsEntityCategory::PLAYER 
		| (uint16)PhysicsEntityCategory::MONSTER;
	bottomFixture.userData = reinterpret_cast<uint64_t*>(
		ScreenSide::BOTTOM_SCREEN
	);
	m_body->CreateFixture(&bottomFixture);
}