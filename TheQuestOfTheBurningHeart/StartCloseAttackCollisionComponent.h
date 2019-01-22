#pragma once
#include <anax/Component.hpp>

struct StartCloseAttackCollisionComponent : anax::Component {
	uint64_t collidedEntityId;
};