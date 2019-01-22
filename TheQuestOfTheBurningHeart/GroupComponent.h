#pragma once
#include <list>
#include <anax/Component.hpp>

struct GroupComponent : anax::Component {
	int widthNumber;
	int heightNumber;
	std::list<uint64_t> entitiesId;
};