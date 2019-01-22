#include "ClearDyingMonstersSystem.h"



ClearDyingMonstersSystem::ClearDyingMonstersSystem()
{
}

void ClearDyingMonstersSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		entity.kill();
		entity.activate();
	}
}