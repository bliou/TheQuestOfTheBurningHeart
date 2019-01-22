#pragma once
#include "ProjectileComponent.h"
#include "VelocityComponent.h"
#include "PhysicComponent.h"

class ProjectilePhysicSystem : public anax::System<anax::Requires<
	ProjectileComponent,
	PhysicComponent,
	VelocityComponent
	>>
{
public:
	ProjectilePhysicSystem();

	void update(float elapsedTime);
};

