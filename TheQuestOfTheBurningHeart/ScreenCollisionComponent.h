#pragma once
#include <anax/Component.hpp>
#include "ScreenSide.h"

struct ScreenCollisionComponent : anax::Component {
	ScreenSide screenSide;
};