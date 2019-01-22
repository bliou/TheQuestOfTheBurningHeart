#pragma once
#include "json.hpp"
#include "GameScreenLoadingThread.h"
#include <SFML/Graphics.hpp>
#include <list>

class AbstractEntityData;
class GameScreen;
class GameScreenLoadingState;

class GameScreenLoader
{
public:
	GameScreenLoader(
		GameScreen& gameInstance,
		std::vector<std::vector<std::string>> map,
		int entitiesToLoad,
		std::string jsonFile);
	~GameScreenLoader();

	void setGameScreenLoadingThread(
		GameScreenLoadingState* state,
		GameScreen& gameInstance,
		sf::RenderWindow& window,
		std::string titleContent);

	bool isReadyToLoad() const;
	bool isLoaded() const;

	void loadLayer(nlohmann::json dataJson);
	void loadMusics();
	void loadSounds();
	void loadEntities();
	void loadGroups();
	void loadPatterns();

	void loadEntity(
		std::string id,
		sf::Vector2f position,
		nlohmann::json specificData);

	void addEntityToCreate(
		std::string id,
		sf::Vector2f position);
	void addEntityToCreate(
		std::string id,
		sf::Vector2f position,
		nlohmann::json specificData);
	void createEntities();
	void addPatternToEntity(
		std::string patternId,
		uint64_t entityId);

protected:

	struct EntityToCreate {
		std::string id;
		sf::Vector2f position;
		nlohmann::json specificData;
	};
	
	GameScreenLoadingThread* m_loadingThread;
	bool m_isLoaded;

	std::vector<std::vector<std::string>> m_map;
	int m_entitiesToLoad;
	int m_musicsToLoad;
	int m_soundsToLoad;
	int m_groupsToLoad;
	int m_patternsToLoad;
	std::map<std::string, nlohmann::json::value_type> m_layers;
	std::list<std::string> m_musics;
	std::list<int> m_sounds;
	std::map<std::string, nlohmann::json::value_type> m_specificDatas;
	std::vector<std::pair<std::string, std::string>> m_patternsInit;
	std::map<std::string, nlohmann::json::value_type> m_patterns;
	std::map<std::string, AbstractEntityData*> m_dataRegister;
	std::map<std::string, std::list<std::string>> m_complexDataRegister;
	GameScreen& m_gameInstance;

	std::list<EntityToCreate> m_entitiesToCreate;
};
