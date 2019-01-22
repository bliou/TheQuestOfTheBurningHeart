#pragma once
#include "PositionComponent.h"
#include "TileComponent.h"
#include <anax/System.hpp>

class GetTileIdByPositionSystem: public anax::System<anax::Requires<
	PositionComponent,
	TileComponent>>
{
public:
	GetTileIdByPositionSystem();

	uint64_t getId(sf::Vector2f position);
};

