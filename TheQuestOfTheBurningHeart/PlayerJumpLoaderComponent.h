#pragma once
#include <anax/Component.hpp>

struct PlayerJumpLoaderComponent : anax::Component {
	PlayerJumpLoaderComponent(float load)
		: loader(load)
	{

	}
	float loader;
};