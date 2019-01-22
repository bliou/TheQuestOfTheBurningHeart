#pragma once
#include <anax/Component.hpp>

struct StartRangeAttackCollisionComponent : anax::Component {
	uint64_t collidedEntityId;
};