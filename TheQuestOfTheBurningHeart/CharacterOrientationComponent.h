#pragma once
#include "CharacterOrientation.h"
#include <anax/Component.hpp>

struct CharacterOrientationComponent : anax::Component {
	CharacterOrientationComponent(CharacterOrientation orientation = CharacterOrientation::LEFT)
		: orientation(orientation),
		defaultOrientation(orientation)
	{

	}

	CharacterOrientation orientation;
	const CharacterOrientation defaultOrientation;
};