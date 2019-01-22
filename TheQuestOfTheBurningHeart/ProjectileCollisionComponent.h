#pragma once
#include <anax/Component.hpp>

struct ProjectileCollisionComponent : anax::Component {
	uint64_t collidedEntityId;
};