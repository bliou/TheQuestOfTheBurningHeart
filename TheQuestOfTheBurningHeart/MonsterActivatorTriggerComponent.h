#pragma once
#include "PhysicsEntityCategory.h"
#include "Helpers.h"
#include <Box2D/Box2D.h>
#include <anax/Component.hpp>

struct MonsterActivatorTriggerComponent : anax::Component {
	MonsterActivatorTriggerComponent(b2Body* body)
	{
		b2PolygonShape activatorShape;
		activatorShape.SetAsBox(screenSize.x / B2SCALE, screenSize.y / B2SCALE, b2Vec2(0.f, 0.f), 0.f);
		b2FixtureDef activatorFixture;
		activatorFixture.isSensor = true;
		activatorFixture.shape = &activatorShape;
		activatorFixture.filter.categoryBits = (uint16)PhysicsEntityCategory::PLAYER_ACTIVATOR_SENSOR;
		activatorFixture.filter.maskBits = (uint16)PhysicsEntityCategory::MONSTER;
		body->CreateFixture(&activatorFixture);
	}
};