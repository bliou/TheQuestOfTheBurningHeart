#pragma once
#include "TimedMovementComponent.h"
#include "VelocityComponent.h"
#include <anax/System.hpp>

class GameScreen;

class TimedMovementSystem: public anax::System<anax::Requires<
	TimedMovementComponent,
	VelocityComponent>>
{
public:
	TimedMovementSystem(GameScreen& gameInstance);

	void update(float elapsedTime);

protected:
	GameScreen & m_gameInstance;
};

