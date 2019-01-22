#pragma once
#include <anax/anax.hpp>

struct StartEntityCollisionComponent : anax::Component {
	std::vector<uint64_t> collidedEntitiesId;
};