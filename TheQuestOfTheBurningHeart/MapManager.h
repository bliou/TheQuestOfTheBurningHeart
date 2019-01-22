#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

class MapManager
{
public:
	MapManager();
	~MapManager();

	MapManager(const MapManager&) = delete;
	MapManager& operator=(const MapManager&) = delete;

	void loadMap(std::string);

	std::vector<std::vector<std::string>> getMap() const;
	sf::Vector2i getMapSize() const;
	int getEntitiesToLoad() const;
private:
	std::vector<std::vector<std::string>> m_map;
	sf::Vector2i m_mapSize;
	int m_entitiesToLoad;
};

