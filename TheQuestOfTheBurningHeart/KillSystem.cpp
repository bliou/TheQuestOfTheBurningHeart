#include "KillSystem.h"
#include <anax/anax.hpp>


KillSystem::KillSystem()
{
}

void KillSystem::update()
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		entity.kill();
		entity.activate();
	}
	getWorld().refresh();
}