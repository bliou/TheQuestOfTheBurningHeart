#pragma once
#include "TileComponent.h"
#include "VelocityComponent.h"
#include "PhysicComponent.h"

class TilePhysicSystem: public anax::System<anax::Requires<
	TileComponent,
	PhysicComponent,
	VelocityComponent
	>>
{
public:
	TilePhysicSystem();
	
	void update(float elapsedTime);
};

