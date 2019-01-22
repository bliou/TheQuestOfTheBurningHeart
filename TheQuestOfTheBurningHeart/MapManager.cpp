#include "MapManager.h"
#include "Helpers.h"
#include <fstream>
#include <sstream>
#include <cassert>
#include <SFML/Graphics.hpp>
#include <climits>


MapManager::MapManager()
	: m_map(),
	m_mapSize(0, 0)
{
}


MapManager::~MapManager()
{
}

void MapManager::loadMap(std::string mapPath)
{
	std::ifstream file(mapPath);
	std::string line;
	std::vector<std::string> tempMap;

	while (std::getline(file, line)) 
	{
		std::string mapCase;
		std::stringstream stream(line);
		while (std::getline(stream, mapCase, ' ')) 
		{
			tempMap.push_back(mapCase);
		}
		m_mapSize.x = std::max(m_mapSize.x, (int)tempMap.size() * tileSize.x);
		m_map.push_back(tempMap);
		tempMap.clear();
	}
	m_mapSize.y = (int)m_map.size() * tileSize.y;

	for (unsigned int i = 0; i < m_map.size(); ++i) {
		for (unsigned int j = 0; j < m_map[i].size(); ++j) {
			std::string mapCase = m_map[i][j];
			if (mapCase[0] != 'x') {
				++m_entitiesToLoad;
			}
		}
	}
}

std::vector<std::vector<std::string>> MapManager::getMap() const
{
	assert(m_map.size() != 0);

	return m_map;
}

sf::Vector2i MapManager::getMapSize() const
{
	return m_mapSize;
}

int MapManager::getEntitiesToLoad() const
{
	return m_entitiesToLoad;
}