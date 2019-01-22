#pragma once
#include <anax/anax.hpp>

struct EndMonsterSensorCollisionComponent : anax::Component {
	uint64_t collidedEntityId;
};