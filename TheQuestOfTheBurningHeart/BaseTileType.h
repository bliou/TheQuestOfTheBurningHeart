#pragma once
#include <map>
#include <SFML/Graphics.hpp>

enum class BaseTileType {
	GRASS_CORNER_LEFT,
	GRASS_TOP,
	GRASS_CENTER,
	GRASS_CORNER_RIGHT,
	GRASS_HALF,
	GRASS_SLOPE,
	DIRT_CORNER_LEFT,
	DIRT_TOP,
	DIRT_CENTER,
	DIRT_CORNER_RIGHT,
	DIRT_HALF,
	DIRT_SLOPE,
	TRANSPARENT
};

const std::map<BaseTileType, sf::Vector2i> baseTileOffset {
	{ BaseTileType::GRASS_CORNER_LEFT, sf::Vector2i(0, 0) },
	{ BaseTileType::GRASS_TOP, sf::Vector2i(64, 0) },
	{ BaseTileType::GRASS_CENTER, sf::Vector2i(128, 0) },
	{ BaseTileType::GRASS_CORNER_RIGHT, sf::Vector2i(192, 0) },
	{ BaseTileType::GRASS_HALF, sf::Vector2i(256, 0) },
	{ BaseTileType::GRASS_SLOPE, sf::Vector2i(0, 0) },
	{ BaseTileType::DIRT_CORNER_LEFT, sf::Vector2i(0, 64) },
	{ BaseTileType::DIRT_TOP, sf::Vector2i(64, 64) },
	{ BaseTileType::DIRT_CENTER, sf::Vector2i(128, 64) },
	{ BaseTileType::DIRT_CORNER_RIGHT, sf::Vector2i(192, 64) },
	{ BaseTileType::DIRT_HALF, sf::Vector2i(256, 64) },
	{ BaseTileType::DIRT_SLOPE, sf::Vector2i(0, 64) },
	{ BaseTileType::TRANSPARENT, sf::Vector2i(0, 0) }
};