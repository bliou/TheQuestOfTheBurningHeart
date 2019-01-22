#pragma once
#include <anax/Component.hpp>

struct BreakableTileComponent : anax::Component {
	BreakableTileComponent(std::string tile)
		: tileToCreate(tile),
		broken(false)
	{

	}

	const std::string tileToCreate;
	bool broken;
};