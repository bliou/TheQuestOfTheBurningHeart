#pragma once
#include <anax/anax.hpp>

struct EndEntityCollisionComponent : anax::Component {
	uint64_t collidedEntityId;
};