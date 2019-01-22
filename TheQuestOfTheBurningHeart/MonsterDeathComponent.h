#pragma once
#include <SFML/Graphics.hpp>
#include <anax/Component.hpp>

struct MonsterDeathComponent : anax::Component {
	MonsterDeathComponent(
		std::string i,
		bool usePos,
		sf::Vector2f pos = sf::Vector2f(0.f, 0.f))
		: id(i),
		useCurrentPosition(usePos),
		position(pos)
	{
	}

	std::string id;
	bool useCurrentPosition;
	sf::Vector2f position;
};