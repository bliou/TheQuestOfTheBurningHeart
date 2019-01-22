#pragma once
#include "GroupComponent.h"
#include "TileComponent.h"
#include "PositionComponent.h"
#include <anax/System.hpp>

class GroupTileSystem: public anax::System<anax::Requires<
	GroupComponent,
	TileComponent,
	PositionComponent
	>>
{
public:
	GroupTileSystem();

	void update(float elapsedTime);
};

