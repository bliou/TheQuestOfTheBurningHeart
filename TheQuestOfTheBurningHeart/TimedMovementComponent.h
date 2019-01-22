#pragma once
#include <Box2D/Box2D.h>
#include <anax/Component.hpp>

struct TimedMovementComponent: anax::Component {
	TimedMovementComponent(
		float timer,
		bool hasVel = false,
		b2Vec2 vel = b2Vec2(0.f, 0.f))
		: defaultTimer(timer),
		currentTimer(timer),
		hasVelocity(hasVel),
		velocity(vel),
		nextPattern("")
	{

	}
	
	const float defaultTimer;
	float currentTimer;

	const bool hasVelocity;
	const b2Vec2 velocity;
	std::string nextPattern;
};