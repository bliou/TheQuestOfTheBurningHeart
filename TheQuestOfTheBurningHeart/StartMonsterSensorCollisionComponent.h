#pragma once
#include <anax/anax.hpp>

struct StartMonsterSensorCollisionComponent : anax::Component {
	uint64_t collidedEntityId;
};