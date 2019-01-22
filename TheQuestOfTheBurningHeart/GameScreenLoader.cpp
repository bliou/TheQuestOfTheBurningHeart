#include "GameScreenLoader.h"
#include "AbstractEntityData.h"
#include "DataRegister.h"
#include "Helpers.h"
#include "MusicsManager.h"
#include "SoundsManager.h"
#include "GroupComponent.h"
#include "SlopeTileComponent.h"
#include "PatternType.h"
#include "DefaultPatternComponent.h"
#include <fstream>


GameScreenLoader::GameScreenLoader(
	GameScreen& gameInstance,
	std::vector<std::vector<std::string>> map,
	int entitiesToLoad,
	std::string jsonFile)
	: m_dataRegister(),
	m_complexDataRegister(),
	m_gameInstance(gameInstance),
	m_map(map),
	m_entitiesToLoad(entitiesToLoad),
	m_loadingThread(nullptr),
	m_isLoaded(false)
{
	nlohmann::json dataJson;
	std::ifstream file(jsonFile);
	file >> dataJson;

	nlohmann::json::iterator it = dataJson["specificData"].begin();
	for (it; it != dataJson["specificData"].end(); ++it) {
		m_specificDatas[it.value().at("id")] = it.value();
	}
	
	it = dataJson["musics"].begin();
	for (it; it != dataJson["musics"].end(); ++it) {
		m_musics.push_back(it.value());
		++m_musicsToLoad;
	}

	it = dataJson["sounds"].begin();
	for (it; it != dataJson["sounds"].end(); ++it) {
		m_sounds.push_back(it.value());
		++m_soundsToLoad;
	}

	it = dataJson["patterns"].begin();
	for (it; it != dataJson["patterns"].end(); ++it) {
		m_patterns[it.value().at("id")] = it.value();
	}

	it = dataJson["patternsInit"].begin();
	for (it; it != dataJson["patternsInit"].end(); ++it) {
		m_patternsInit.push_back(std::pair<std::string, std::string>(
			it.value().at("patternId").get<std::string>(),
			it.value().at("targetId").get<std::string>()
		));
		++m_patternsToLoad;
	}

	m_dataRegister = DataRegistrer().getDataRegistrar();
	m_complexDataRegister = DataRegistrer().getComplexDataRegistrar();

	loadLayer(dataJson);
	
	/// Set if the current level is a bonus one
	m_gameInstance.setIsBonusLevel(dataJson["bonusLevel"]);
}


GameScreenLoader::~GameScreenLoader()
{
	delete m_loadingThread;
	m_loadingThread = nullptr;
}

void GameScreenLoader::setGameScreenLoadingThread(
	GameScreenLoadingState* state,
	GameScreen& gameInstance,
	sf::RenderWindow& window,
	std::string titleContent)
{
	if (m_loadingThread)
		throw std::runtime_error("The loading thread already exists");
	m_loadingThread = new GameScreenLoadingThread(
		state, 
		gameInstance,
		window, 
		titleContent
	);
}

bool GameScreenLoader::isReadyToLoad() const
{
	return m_loadingThread;
}

bool GameScreenLoader::isLoaded() const
{
	return m_isLoaded;
}

void GameScreenLoader::loadLayer(nlohmann::json dataJson)
{
	anax::Entity entity = m_gameInstance.getWorld()->createEntity();
	AbstractEntityData* data = m_dataRegister.at("fixLayer");
	data->initializeEntity(
		"",
		entity,
		m_gameInstance,
		sf::Vector2f(0.f, 0.f),
		dataJson["layer"]
	);
	entity.activate();
	m_gameInstance.getWorld()->refresh();
}

void GameScreenLoader::loadMusics()
{
	m_loadingThread->setProgressContent("Loading musics...");
	m_loadingThread->setProgress(0.f);
	m_loadingThread->draw();

	for (auto& music : m_musics)
	{
		MusicsManager::loadMusic(music);

		float progress = m_loadingThread->getProgress();
		progress += 1.0f / (float)m_musicsToLoad * 100.0f;
		m_loadingThread->setProgress(progress);
		m_loadingThread->draw();
	}
}

void GameScreenLoader::loadSounds()
{
	m_loadingThread->setProgressContent("Loading sounds...");
	m_loadingThread->setProgress(0.f);
	m_loadingThread->draw();

	for (auto& sound : m_sounds)
	{
		SoundsManager::loadSound((SoundType)sound);

		float progress = m_loadingThread->getProgress();
		progress += 1.0f / (float)m_soundsToLoad * 100.0f;
		m_loadingThread->setProgress(progress);
		m_loadingThread->draw();
	}
}

void GameScreenLoader::loadEntities()
{
	m_loadingThread->setProgressContent("Loading entities...");
	m_loadingThread->setProgress(0.f);
	m_loadingThread->draw();

	sf::Clock drawClock;

	for (unsigned int i = 0; i < m_map.size(); ++i) {
		for (unsigned int j = 0; j < m_map[i].size(); ++j) {
			std::string id = m_map[i][j];
			sf::Vector2f position =
				sf::Vector2f((float)j * tileSize.x, (float)i * tileSize.y);
			if (id[0] == 'x')
				continue;

			if (id[0] == 'g')
				m_groupsToLoad++;
			
			if (id[0] == 'c') {
				std::list<std::string> dataIds = m_complexDataRegister[id];
				for (std::string dataId : dataIds) {
					nlohmann::json::value_type specificData = m_specificDatas[dataId];
					loadEntity(dataId, position, specificData);
				}
			}
			else {
				nlohmann::json::value_type specificData = m_specificDatas[id];
				loadEntity(id, position, specificData);
			}

			float progress = m_loadingThread->getProgress();
			progress += 1.0f / (float)m_entitiesToLoad * 100.0f;
			m_loadingThread->setProgress(progress);
			if (drawClock.getElapsedTime().asSeconds() >= 1.f / 60.f) {
				m_loadingThread->draw();
				drawClock.restart();
			}
		}
	}
	m_isLoaded = true;
}

void GameScreenLoader::loadGroups()
{
	m_loadingThread->setProgressContent("Loading groups...");
	m_loadingThread->setProgress(0.f);
	m_loadingThread->draw();

	sf::Clock drawClock;

	auto entities = m_gameInstance.getWorld()->getEntities();
	for (auto& entity : entities)
	{
		if (!entity.hasComponent<GroupComponent>()
			||	entity.hasComponent<SlopeTileComponent>())
			continue;

		sf::Vector2f position = entity.getComponent<PositionComponent>().position;
		auto& groupComponent = entity.getComponent<GroupComponent>();

		for (int i = 0; i < groupComponent.widthNumber; ++i) {
			for (int j = 0; j < groupComponent.heightNumber; ++j) {
				uint64_t tileId = m_gameInstance.getTileIdByPosition(
					sf::Vector2f(
						position.x + tileSize.x * i,
						position.y + tileSize.y * j
					)
				);
				/// The group does not contain its own id
				if (tileId != entity.getId().index
					&& tileId != std::numeric_limits<uint64_t>::max()) {
					groupComponent.entitiesId.push_back(tileId);
				}
			}
		}

		float progress = m_loadingThread->getProgress();
		progress += 1.0f / (float)m_groupsToLoad * 100.0f;
		m_loadingThread->setProgress(progress);
		if (drawClock.getElapsedTime().asSeconds() >= 1.f / 60.f) {
			m_loadingThread->draw();
			drawClock.restart();
		}
	}
}

void GameScreenLoader::loadPatterns()
{
	m_loadingThread->setProgressContent("Loading patterns...");
	m_loadingThread->setProgress(0.f);
	m_loadingThread->draw();

	sf::Clock drawClock;

	for (auto patternInit : m_patternsInit)
	{
		std::list<uint64_t> entitiesId = m_gameInstance.getEntitiesIdByDataId(
			patternInit.second);
		for (uint64_t entityId : entitiesId)
		{
			addPatternToEntity(
				patternInit.first,
				entityId
			);
			anax::Entity entity = m_gameInstance.getWorld()->getEntity(entityId);
			entity.addComponent<DefaultPatternComponent>().patternId = patternInit.first;
			entity.activate();
		}

		float progress = m_loadingThread->getProgress();
		progress += 1.0f / (float)m_patternsToLoad * 100.0f;
		m_loadingThread->setProgress(progress);
		if (drawClock.getElapsedTime().asSeconds() >= 1.f / 60.f) {
			m_loadingThread->draw();
			drawClock.restart();
		}
	}
}

void GameScreenLoader::loadEntity(
	std::string id,
	sf::Vector2f position,
	nlohmann::json specificData)
{
	AbstractEntityData* data = nullptr;
	std::string dataId = id;
	if (m_dataRegister.count(id) != 0) {
		data = m_dataRegister[id];
	}
	else {
		id = id.substr(0, 2);
		data = m_dataRegister[id];
	}
	anax::Entity entity = m_gameInstance.getWorld()->createEntity();
	data->initializeEntity(
		dataId,
		entity,
		m_gameInstance,
		position,
		specificData
	);
	entity.activate();
}

void GameScreenLoader::addEntityToCreate(
	std::string id,
	sf::Vector2f position)
{
	EntityToCreate entityToCreate = EntityToCreate();
	entityToCreate.id = id;
	entityToCreate.position = position;
	entityToCreate.specificData = m_specificDatas[id];
	m_entitiesToCreate.push_back(
		entityToCreate
	);
}

void GameScreenLoader::addEntityToCreate(
	std::string id,
	sf::Vector2f position,
	nlohmann::json specificData)
{
	EntityToCreate entityToCreate = EntityToCreate();
	entityToCreate.id = id;
	entityToCreate.position = position;
	entityToCreate.specificData = specificData;
	m_entitiesToCreate.push_back(
		entityToCreate
	);
}

void GameScreenLoader::addPatternToEntity(
	std::string patternId,
	uint64_t targetId)
{
	nlohmann::json pattern = m_patterns[patternId];
	anax::Entity entity = m_gameInstance.getWorld()->getEntity(targetId);
	switch ((PatternType)pattern.at("patternType"))
	{
	case PatternType::TIMED_MOVEMENT:
	{
		b2Vec2 velocity = b2Vec2(
			pattern.at("velocity").at("x"),
			pattern.at("velocity").at("y")
		);
		entity.addComponent<TimedMovementComponent>(
			pattern.at("timer"),
			true,
			velocity);
		entity.addComponent<VelocityComponent>();

		if (pattern.find("nextPatternId") != pattern.end())
			entity.getComponent<TimedMovementComponent>().nextPattern =
				pattern.at("nextPatternId").get<std::string>();
		break;
	}
	}
	entity.activate();
}

void GameScreenLoader::createEntities()
{
	std::list<EntityToCreate>::iterator it = m_entitiesToCreate.begin();
	while (it != m_entitiesToCreate.end())
	{
		std::string id = (*it).id;
		std::string dataId = id;
		AbstractEntityData* data = nullptr;
		if (m_dataRegister.count(id) != 0) {
			data = m_dataRegister[id];
		}
		else {
			id = id.substr(0, 2);
			data = m_dataRegister[id];
		}
		anax::Entity entity = m_gameInstance.getWorld()->createEntity();
		data->initializeEntity(
			dataId,
			entity,
			m_gameInstance,
			(*it).position,
			(*it).specificData
		);
		entity.activate();

		it = m_entitiesToCreate.erase(it);
	}
}