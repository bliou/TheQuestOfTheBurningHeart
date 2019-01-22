#include "GetEntitiesIdByDataIdSystem.h"



GetEntitiesIdByDataIdSystem::GetEntitiesIdByDataIdSystem()
{
}

std::list<uint64_t> GetEntitiesIdByDataIdSystem::getIds(std::string dataId)
{
	std::list<uint64_t> ids;

	auto entities = getEntities();
	for (auto& entity : entities)
	{
		if (entity.getComponent<DataIdComponent>().dataId == dataId)
			ids.push_back(entity.getId().index);
	}

	return ids;
}