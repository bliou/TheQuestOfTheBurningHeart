#include "ProjectileClearSystem.h"



ProjectileClearSystem::ProjectileClearSystem()
{
}

void ProjectileClearSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		entity.kill();
		entity.activate();
	}
}