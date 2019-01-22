#pragma once
#include "GamePlayerComponent.h"
#include <anax/System.hpp>

class GetPlayerSystem: public anax::System<anax::Requires<
	GamePlayerComponent
	>>
{
public:
	GetPlayerSystem();
	
	uint64_t getPlayerId();
};

