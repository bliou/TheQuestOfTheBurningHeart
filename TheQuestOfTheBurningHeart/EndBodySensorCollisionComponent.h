#pragma once
#include <anax/anax.hpp>

struct EndBodySensorCollisionComponent : anax::Component {
	uint64_t collidedEntityId;
};