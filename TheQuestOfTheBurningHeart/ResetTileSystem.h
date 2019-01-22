#pragma once
#include "ResetTileComponent.h"
#include <anax/System.hpp>

class ResetTileSystem: public anax::System<anax::Requires<
	ResetTileComponent
	>>
{
public:
	ResetTileSystem();

	void update(float elapsedTime);
};

