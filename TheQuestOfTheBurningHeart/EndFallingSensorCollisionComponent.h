#pragma once
#include <anax/anax.hpp>

struct EndFallingSensorCollisionComponent : public anax::Component {
	uint64_t collidedEntityId;
};