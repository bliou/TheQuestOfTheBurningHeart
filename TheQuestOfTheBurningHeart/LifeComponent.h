#pragma once
#include <anax/Component.hpp>

struct LifeComponent : anax::Component {
	struct LifeComponent(int l)
		: lifes(l),
		defaultLifes(l)
	{

	}

	int lifes;
	const int defaultLifes;
};