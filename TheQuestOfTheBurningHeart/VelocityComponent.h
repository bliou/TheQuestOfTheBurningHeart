#pragma once
#include <anax/Component.hpp>
#include <Box2D/Box2D.h>

struct VelocityComponent: anax::Component
{
	b2Vec2 velocity;
};

