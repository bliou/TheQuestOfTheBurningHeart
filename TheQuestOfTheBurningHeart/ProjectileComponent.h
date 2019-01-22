#pragma once
#include <Box2D/Box2D.h>
#include <anax/Component.hpp>

struct ProjectileComponent : anax::Component {
	ProjectileComponent(float ls)
		: lifeSpan(ls),
		velocity(0.f, 0.f)
	{

	}

	b2Vec2 velocity;
	float lifeSpan;
};