#pragma once
#include <anax/Component.hpp>

struct EndRangeAttackCollisionComponent : anax::Component {
	uint64_t collidedEntityId;
};