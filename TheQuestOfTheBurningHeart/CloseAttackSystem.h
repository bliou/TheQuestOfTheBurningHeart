#pragma once
#include "CloseAttackPatternComponent.h"
#include <anax/System.hpp>

class GameScreen;

class CloseAttackSystem: public anax::System<anax::Requires<
	CloseAttackPatternComponent
	>>
{
public:
	CloseAttackSystem(GameScreen& gameInstance);

	void update(float elapsedTime);

protected:
	GameScreen & m_gameInstance;
};

