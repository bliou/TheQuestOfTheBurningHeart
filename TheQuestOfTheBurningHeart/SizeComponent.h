#pragma once
#include <anax/Component.hpp>
#include <SFML/Graphics.hpp>

struct SizeComponent : anax::Component {
	SizeComponent(sf::Vector2i size)
		: defaultSize(size)
	{
		this->size = size;
	}

	sf::Vector2i size;
	const sf::Vector2i defaultSize;
};