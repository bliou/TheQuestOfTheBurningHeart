#pragma once
#include "DefaultStateComponent.h"
#include <anax/System.hpp>

class GameScreen;

class DefaultStatesSystem: public anax::System<anax::Requires<
	DefaultStateComponent
	>>
{
public:
	DefaultStatesSystem(GameScreen& gameInstance);

	void update(float elapsedTime);

protected:
	GameScreen & m_gameInstance;
};

