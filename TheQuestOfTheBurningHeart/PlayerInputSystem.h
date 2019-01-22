#pragma once
#include "GamePlayerComponent.h"
#include "CharacterComponent.h"
#include "VelocityComponent.h"
#include "GroundCharacterStateComponent.h"
#include "CharacterOrientationComponent.h"
#include "PlayerElementalTypeComponent.h"
#include <anax/System.hpp>

class PlayerInputSystem: public anax::System<anax::Requires<
	GamePlayerComponent,
	CharacterComponent,
	VelocityComponent,
	GroundCharacterStateComponent,
	CharacterOrientationComponent,
	PlayerElementalTypeComponent>>
{
public:
	PlayerInputSystem();

	void updateEvent(bool releasedOnly);
};