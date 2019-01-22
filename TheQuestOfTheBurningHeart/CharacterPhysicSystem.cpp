#include "CharacterPhysicSystem.h"
#include "Helpers.h"
#include "PlayerJumpLoaderComponent.h"
#include "CharacterSlopeTileComponent.h"


CharacterPhysicSystem::CharacterPhysicSystem()
{
}

void CharacterPhysicSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& body = entity.getComponent<PhysicComponent>().body;
		auto& velocity = entity.getComponent<VelocityComponent>().velocity;
		auto& state = entity.getComponent<GroundCharacterStateComponent>().state;

		switch (state)
		{
		case GroundCharacterState::IDLE:
		case GroundCharacterState::WALK:
		case GroundCharacterState::FALL:
		case GroundCharacterState::DYING:
		case GroundCharacterState::DAMAGED:
		case GroundCharacterState::RANGE_ATTACK:
		case GroundCharacterState::CLOSE_ATTACK:
		{
			if (entity.hasComponent<CharacterSlopeTileComponent>())
				body->SetLinearVelocity(velocity);
			else {
				b2Vec2 vel = body->GetLinearVelocity();
				body->SetLinearVelocity(b2Vec2(
					velocity.x,
					vel.y
				));
			}
			break;
		}
		case GroundCharacterState::JUMP:
		{
			b2Vec2 vel = body->GetLinearVelocity();
			if (entity.hasComponent<PlayerJumpLoaderComponent>()) {
				auto& loader = entity.getComponent<PlayerJumpLoaderComponent>().loader;
				loader -= elapsedTime;
				if (loader <= 0.f) {
					entity.removeComponent<PlayerJumpLoaderComponent>();
					entity.activate();
				}

				body->SetLinearVelocity(b2Vec2(
					velocity.x,
					velocity.y
				));
			}
			else {
				body->SetLinearVelocity(b2Vec2(
					velocity.x,
					vel.y
				));
			}
			break;
		}
		}

	}
}