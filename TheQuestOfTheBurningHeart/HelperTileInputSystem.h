#pragma once
#include "HelperTileComponent.h"
#include <anax/System.hpp>

class GameScreen;

class HelperTileInputSystem: public anax::System<anax::Requires<
	HelperTileComponent
	>>
{
public:
	HelperTileInputSystem(GameScreen& gameInstance);

	void updateEvent();

protected:
	GameScreen& m_gameInstance;
};

