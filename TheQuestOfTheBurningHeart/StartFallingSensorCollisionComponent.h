#pragma once
#include <anax/anax.hpp>

struct StartFallingSensorCollisionComponent : public anax::Component {
	uint64_t collidedEntityId;
};