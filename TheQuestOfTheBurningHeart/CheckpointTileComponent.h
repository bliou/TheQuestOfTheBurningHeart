#pragma once
#include <anax/Component.hpp>

struct CheckpointTileComponent : anax::Component {
	CheckpointTileComponent() : isUsed(false) {}
	bool isUsed;
};