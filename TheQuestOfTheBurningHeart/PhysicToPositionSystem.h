#pragma once
#include "PhysicComponent.h"
#include "PositionComponent.h"
#include "SizeComponent.h"
#include <anax/System.hpp>

class PhysicToPositionSystem: public anax::System<anax::Requires<
	PhysicComponent,
	PositionComponent,
	SizeComponent>>
{
public:
	PhysicToPositionSystem();

	void update(float elapsedTime);
};

