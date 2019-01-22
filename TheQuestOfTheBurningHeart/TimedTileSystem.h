#pragma once
#include "TimedTileComponent.h"
#include <anax/System.hpp>

class TimedTileSystem: public anax::System<anax::Requires<
	TimedTileComponent
	>>
{
public:
	TimedTileSystem();

	void update(float elapsedTime);
};

