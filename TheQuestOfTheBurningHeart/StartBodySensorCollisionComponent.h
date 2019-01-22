#pragma once
#include <anax/anax.hpp>

struct StartBodySensorCollisionComponent : anax::Component {
	uint64_t collidedEntityId;
};