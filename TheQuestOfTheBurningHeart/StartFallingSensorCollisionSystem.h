#pragma once
#include "FallingTriggerComponent.h"
#include "StartFallingSensorCollisionComponent.h"
#include "CharacterOrientationComponent.h"
#include <anax/System.hpp>

class StartFallingSensorCollisionSystem : public anax::System<anax::Requires<
	FallingTriggerComponent,
	StartFallingSensorCollisionComponent,
	CharacterOrientationComponent>>
{
public:
	StartFallingSensorCollisionSystem();

	void update(float elapsedTime);
};

