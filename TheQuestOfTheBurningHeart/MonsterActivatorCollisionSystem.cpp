#include "MonsterActivatorCollisionSystem.h"

MonsterActivatorCollisionSystem::MonsterActivatorCollisionSystem()
{
}

void MonsterActivatorCollisionSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& monsterVel = entity.getComponent<CharacterComponent>().velocity;
		auto& velocity = entity.getComponent<VelocityComponent>().velocity;
		auto& state = entity.getComponent<GroundCharacterStateComponent>().state;
		state = GroundCharacterState::WALK;

		entity.removeComponent<DisableComponent>();
		entity.removeComponent<MonsterActivatorCollisionComponent>();
		entity.activate();
	}
}