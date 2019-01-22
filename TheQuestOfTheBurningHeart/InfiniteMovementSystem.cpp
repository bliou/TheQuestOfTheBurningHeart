#include "InfiniteMovementSystem.h"
#include "DisableComponent.h"
#include "CharacterComponent.h"
#include "CharacterOrientationComponent.h"
#include "GroundCharacterStateComponent.h"
#include "MonsterDamagedComponent.h"
#include "ProjectileComponent.h"

InfiniteMovementSystem::InfiniteMovementSystem()
{
}


void InfiniteMovementSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		if (entity.hasComponent<DisableComponent>())
			continue;

		auto& velocity = entity.getComponent<VelocityComponent>().velocity;
		b2Vec2 vel = b2Vec2(0.f, 0.f);
		if (entity.hasComponent<CharacterComponent>())
		{
			auto& state = entity.getComponent<GroundCharacterStateComponent>().state;
			if (state == GroundCharacterState::DAMAGED) {
				vel = entity.getComponent<MonsterDamagedComponent>().velocity;
			}
			else if (state == GroundCharacterState::WALK
				|| state == GroundCharacterState::FALL) {
				vel = entity.getComponent<CharacterComponent>().velocity;
			}
			
			auto& orientation = entity.getComponent<CharacterOrientationComponent>().orientation;
			if (orientation == CharacterOrientation::LEFT)
				velocity = b2Vec2(
					-vel.x,
					vel.y
				);
			else
				velocity = vel;
		}
		if (entity.hasComponent<ProjectileComponent>())
		{
			velocity = entity.getComponent<ProjectileComponent>().velocity;
		}
	}
}
