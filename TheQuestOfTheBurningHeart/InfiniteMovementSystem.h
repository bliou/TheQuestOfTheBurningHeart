#pragma once
#include "InfiniteMovementComponent.h"
#include "VelocityComponent.h"
#include <anax/System.hpp>

class InfiniteMovementSystem: public anax::System<anax::Requires<
	InfiniteMovementComponent,
	VelocityComponent
	>>
{
public:
	InfiniteMovementSystem();

	void update(float elapsedTime);
};

