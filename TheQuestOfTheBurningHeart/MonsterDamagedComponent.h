#pragma once
#include <Box2D/Box2D.h>
#include <anax/Component.hpp>

struct MonsterDamagedComponent : anax::Component {
	b2Vec2 velocity;
};