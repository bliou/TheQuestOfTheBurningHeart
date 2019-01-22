#pragma once
#include <Box2D/Box2D.h>
#include <anax/anax.hpp>

struct TileComponent : anax::Component {
	TileComponent()
		: isOneSided(false),
		collideFoot(false),
		velocity(0.f, 0.f)
	{
	}

	bool isOneSided;
	bool collideFoot;
	b2Vec2 velocity;
};