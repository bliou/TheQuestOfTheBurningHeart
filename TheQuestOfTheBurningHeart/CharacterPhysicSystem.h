#pragma once
#include "CharacterComponent.h"
#include "PhysicComponent.h"
#include "VelocityComponent.h"
#include "GroundCharacterStateComponent.h"

class CharacterPhysicSystem: public anax::System<anax::Requires<
	CharacterComponent,
	PhysicComponent,
	VelocityComponent,
	GroundCharacterStateComponent
	>>
{
public:
	CharacterPhysicSystem();

	void update(float elapsedTime);
};

