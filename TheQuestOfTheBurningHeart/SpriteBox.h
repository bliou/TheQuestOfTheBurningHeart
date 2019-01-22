#pragma once
#include <SFML/Graphics.hpp>
struct SpriteBox {
	SpriteBox(
		sf::Vector2i position, 
		sf::Vector2i size,
		sf::Vector2f offset = sf::Vector2f(0, 0))
	{
		this->position = position;
		this->size = size;
		this->offset = offset;
	}

	sf::Vector2i position;
	sf::Vector2i size;
	sf::Vector2f offset;
};