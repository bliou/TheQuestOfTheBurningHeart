#pragma once
#include "EndFallingSensorCollisionComponent.h"
#include "FallingTriggerComponent.h"
#include "CharacterOrientationComponent.h"
#include <anax/System.hpp>

class EndFallingSensorCollisionSystem : public anax::System<anax::Requires<
	EndFallingSensorCollisionComponent,
	FallingTriggerComponent,
	CharacterOrientationComponent>>
{
public:
	EndFallingSensorCollisionSystem();

	void update(float elapsedTime);
};

