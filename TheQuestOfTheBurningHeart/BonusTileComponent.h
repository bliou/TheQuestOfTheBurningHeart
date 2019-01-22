#pragma once
#include <anax/Component.hpp>
#include "BonusType.h"

struct BonusTileComponent : anax::Component {
	BonusTileComponent(BonusType bt)
		: bonusType(bt)
	{

	}
	const BonusType bonusType;
};