#pragma once
#include <anax/anax.hpp>

struct StartFootCollisionComponent: anax::Component {
	std::list<uint64_t> collidedEntitiesId;
};