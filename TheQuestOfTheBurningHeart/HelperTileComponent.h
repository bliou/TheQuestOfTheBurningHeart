#pragma once
#include <anax/Component.hpp>

struct HelperTileComponent : anax::Component {
	
	HelperTileComponent(std::string content)
		: helperContent(content),
		activated(false)
	{

	}

	const std::string helperContent;
	bool activated;
};