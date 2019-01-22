#pragma once
#include <SFML/Graphics.hpp>
#include <anax/Component.hpp>

struct RangeAttackDataComponent : anax::Component {
	RangeAttackDataComponent(
		std::string id,
		int count,
		float as,
		sf::Vector2f off = sf::Vector2f(0.f, 0.f))
		: projectileId(id),
		rangeAttackCount(count),
		attackSpeed(as),
		offset(off)
	{

	}

	std::string projectileId;
	const float attackSpeed;
	const int rangeAttackCount;
	sf::Vector2f offset;
};