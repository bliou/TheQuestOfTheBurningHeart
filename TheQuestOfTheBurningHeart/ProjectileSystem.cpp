#include "ProjectileSystem.h"


ProjectileSystem::ProjectileSystem()
{
}

void ProjectileSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& projectileComponent = entity.getComponent<ProjectileComponent>();
		projectileComponent.lifeSpan -= elapsedTime;
		if (projectileComponent.lifeSpan <= 0) {
			entity.kill();
			entity.activate();
		}
	}
}