#pragma once
#include "SlopeType.h"
#include <anax/Component.hpp>

struct CharacterSlopeTileComponent : anax::Component {
	CharacterSlopeTileComponent(uint64_t id, SlopeType type)
		: slopeId(id),
		slopeType(type)
	{

	}

	uint64_t slopeId;
	SlopeType slopeType;
};