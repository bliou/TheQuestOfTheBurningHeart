#pragma once
#include <map>

enum class ElementalType {
	DEFAULT = 0,
	FIRE	= 1,
	ICE		= 2
};

const std::map<ElementalType, std::string> elementalTypeName {
	{ ElementalType::DEFAULT, "default" },
	{ ElementalType::FIRE, "fire" },
	{ ElementalType::ICE, "ice" }
};