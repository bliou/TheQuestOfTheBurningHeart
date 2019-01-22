#pragma once
#include "DataIdComponent.h"
#include <list>
#include <anax/System.hpp>

class GetEntitiesIdByDataIdSystem: public anax::System<anax::Requires<
	DataIdComponent>>
{
public:
	GetEntitiesIdByDataIdSystem();

	std::list<uint64_t> getIds(std::string dataId);
};

