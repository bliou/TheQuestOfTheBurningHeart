#pragma once
#include "PhysicsEntityCategory.h"
#include <Box2D/Box2D.h>

class PhysicsEntityCategoryHelper {
public:
	static const uint16 solidTileMaskBits;

	static const uint16 sensorTileMaskBits;
};

const uint16 PhysicsEntityCategoryHelper::solidTileMaskBits = 
(uint16)PhysicsEntityCategory::PLAYER
| (uint16)PhysicsEntityCategory::CHARACTER_FOOT
| (uint16)PhysicsEntityCategory::MONSTER
| (uint16)PhysicsEntityCategory::MONSTER_SENSOR
| (uint16)PhysicsEntityCategory::FALLING_TRIGGER
| (uint16)PhysicsEntityCategory::PROJECTILE;

const uint16 PhysicsEntityCategoryHelper::sensorTileMaskBits = 
(uint16)PhysicsEntityCategory::PLAYER
| (uint16)PhysicsEntityCategory::CHARACTER_FOOT;