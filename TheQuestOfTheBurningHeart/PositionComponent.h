#pragma once
#include <anax/Component.hpp>
#include <SFML/Graphics.hpp>

struct PositionComponent : anax::Component {

	PositionComponent(sf::Vector2f position)
		: defaultPosition(position)
	{
		this->position = position;
		this->previousPosition = position;
	}

	sf::Vector2f position;
	sf::Vector2f previousPosition;
	const sf::Vector2f defaultPosition;
};