#include "TilePhysicSystem.h"

TilePhysicSystem::TilePhysicSystem()
{
}

void TilePhysicSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		b2Body* body = entity.getComponent<PhysicComponent>().body;
		b2Vec2 velocity = entity.getComponent<VelocityComponent>().velocity;

		body->SetLinearVelocity(b2Vec2(
			velocity.x,
			velocity.y
		));
	}
}