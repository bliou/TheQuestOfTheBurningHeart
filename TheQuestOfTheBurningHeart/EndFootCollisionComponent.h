#pragma once
#include <anax/anax.hpp>

struct EndFootCollisionComponent : anax::Component {
	std::list<uint64_t> collidedEntitiesId;
};