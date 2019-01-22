#include "ProjectileCollisionSystem.h"
#include "TileComponent.h"
#include "GamePlayerComponent.h"
#include "GameScreen.h"

ProjectileCollisionSystem::ProjectileCollisionSystem(
	GameScreen& gameInstance)
	: m_gameInstance(gameInstance)
{
}

void ProjectileCollisionSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		if (entity.hasComponent<TileComponent>()) {
			uint64_t projectileId = entity.getComponent<ProjectileCollisionComponent>().collidedEntityId;
			anax::Entity projectile = entity.getWorld().getEntity(projectileId);

			projectile.kill();
			projectile.activate();
		}
		else if (entity.hasComponent<GamePlayerComponent>()) {
			m_gameInstance.killPlayer(entity);
		}
		else {
			throw std::runtime_error("It should not collide");
		}

		entity.removeComponent<ProjectileCollisionComponent>();
		entity.activate();
	}
}