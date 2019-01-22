#pragma once
#include "MonsterActivatorCollisionComponent.h"
#include "DisableComponent.h"
#include "MonsterComponent.h"
#include "CharacterComponent.h"
#include "GroundCharacterStateComponent.h"
#include "VelocityComponent.h"
#include <anax/System.hpp>

class MonsterActivatorCollisionSystem : public anax::System < anax::Requires <
	MonsterActivatorCollisionComponent,
	DisableComponent,
	MonsterComponent,
	CharacterComponent,
	GroundCharacterStateComponent,
	VelocityComponent
	>>
{
public:
	MonsterActivatorCollisionSystem();

	void update(float elapsedTime);
};

