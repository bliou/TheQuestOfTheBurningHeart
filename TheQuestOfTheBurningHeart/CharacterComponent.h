#pragma once
#include <anax/anax.hpp>
#include <Box2D/Box2D.h>
#include <vector>

struct CharacterComponent : anax::Component {

	CharacterComponent(b2Vec2 velocity)
	{
		this->velocity = velocity;
	}

	b2Vec2 velocity;
	std::vector<uint64_t> footContacts;
};