#pragma once
#include "CharacterSlopeTileComponent.h"
#include "CharacterComponent.h"
#include "VelocityComponent.h"
#include "GroundCharacterStateComponent.h"
#include "CharacterOrientationComponent.h"
#include <anax/System.hpp>

class CharacterSlopeTileSystem: public anax::System<anax::Requires<
	CharacterSlopeTileComponent,
	CharacterComponent,
	VelocityComponent,
	CharacterOrientationComponent>>
{
public:
	CharacterSlopeTileSystem();

	void update(float elapsedTime);
};

