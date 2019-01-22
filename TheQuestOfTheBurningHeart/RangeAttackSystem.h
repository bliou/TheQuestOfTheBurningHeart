#pragma once
#include "RangeAttackPatternComponent.h"
#include <anax/System.hpp>

class GameScreen;

class RangeAttackSystem: public anax::System<anax::Requires<
	RangeAttackPatternComponent
	>>
{
public:
	RangeAttackSystem(GameScreen& gameInstance);

	void update(float elapsedTime);

protected:
	GameScreen & m_gameInstance;
};

