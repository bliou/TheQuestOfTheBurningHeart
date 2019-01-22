#include "GetPlayerSystem.h"



GetPlayerSystem::GetPlayerSystem()
{
}

uint64_t GetPlayerSystem::getPlayerId()
{
	auto entities = getEntities();

	return (*entities.begin()).getId().index;
}