#pragma once
#include <anax/Component.hpp>
#include "ElementalType.h"

struct ElementalTypeComponent : anax::Component {
	ElementalTypeComponent(ElementalType et)
		: elementalType(et)
	{

	}

	const ElementalType elementalType;
};
