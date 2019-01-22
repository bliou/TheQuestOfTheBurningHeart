#pragma once
#include <anax/anax.hpp>
#include "GroundCharacterState.h"

struct GroundCharacterStateComponent: anax::Component {
	GroundCharacterStateComponent()
		: state(GroundCharacterState::IDLE),
		defaultState(GroundCharacterState::IDLE)
	{

	}
	GroundCharacterState state;
	const GroundCharacterState defaultState;
};