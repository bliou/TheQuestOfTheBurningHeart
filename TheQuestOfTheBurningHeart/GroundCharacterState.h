#pragma once

enum class GroundCharacterState {
	IDLE = 0,
	WALK = 1,
	JUMP = 2,
	FALL = 3,
	CLOSE_ATTACK = 4,
	RANGE_ATTACK = 5,
	DAMAGED = 6,
	DYING = 7,
	SPECIAL_STATE = 8
};
