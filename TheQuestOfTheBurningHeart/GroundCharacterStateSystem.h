#pragma once
#include "CharacterComponent.h"
#include "VelocityComponent.h"
#include "GroundCharacterStateComponent.h"
#include "PhysicComponent.h"
#include <anax/System.hpp>

class GameScreen;

class GroundCharacterStateSystem: public anax::System<anax::Requires<
	CharacterComponent,
	VelocityComponent,
	GroundCharacterStateComponent,
	PhysicComponent
	>>
{
public:
	GroundCharacterStateSystem(GameScreen& gameInstance);

	void update(float elapsedTime);

protected:
	GameScreen & m_gameInstance;
};

