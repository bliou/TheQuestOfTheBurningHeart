#pragma once
#include "ElementalType.h"
#include <anax/Component.hpp>

struct PlayerElementalTypeComponent : anax::Component {

	PlayerElementalTypeComponent()
	{
		currentElementalType = ElementalType::DEFAULT;
		playerElementalTypes = {
			{ ElementalType::FIRE, PlayerElementalType(5.f) }
		};
	}

	~PlayerElementalTypeComponent()
	{
	}

	struct PlayerElementalType {
		PlayerElementalType()
			: maxTime(0.f),
			remainingTime(0.f)
		{

		}
		PlayerElementalType(float mTime, float remTime = 0.f)
			: maxTime(mTime),
			remainingTime(remTime)
		{

		}
		float remainingTime;
		const float maxTime;
	};
	std::map<ElementalType, PlayerElementalType> playerElementalTypes;
	ElementalType currentElementalType;
};