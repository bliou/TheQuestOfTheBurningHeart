#include "TimedMovementSystem.h"
#include "DisableComponent.h"
#include "TileComponent.h"
#include "CharacterComponent.h"
#include "CharacterOrientationComponent.h"
#include "GroundCharacterStateComponent.h"
#include "GameScreen.h"

TimedMovementSystem::TimedMovementSystem(GameScreen& gameInstance)
	: m_gameInstance(gameInstance)
{
}

void TimedMovementSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		if (entity.hasComponent<DisableComponent>())
			continue;

		auto& velocity = entity.getComponent<VelocityComponent>().velocity;
		auto& timedMovementComponent = entity.getComponent<TimedMovementComponent>();

		timedMovementComponent.currentTimer -= elapsedTime;
		if (timedMovementComponent.currentTimer > 0.f) {
			if (timedMovementComponent.hasVelocity) {
				velocity = timedMovementComponent.velocity;
			}
			else if (entity.hasComponent<TileComponent>()) {
				velocity = entity.getComponent<TileComponent>().velocity;
			}
			else if (entity.hasComponent<CharacterComponent>()) {
				auto& orientation = entity.getComponent<CharacterOrientationComponent>().orientation;
				velocity = entity.getComponent<CharacterComponent>().velocity;
				if (orientation == CharacterOrientation::LEFT)
					velocity.x *= -1;

				if (entity.hasComponent<GroundCharacterStateComponent>()) {
					entity.getComponent<GroundCharacterStateComponent>().state = GroundCharacterState::WALK;
				}
			}
			
		}
		else {
			std::string nextPattern = entity.getComponent<TimedMovementComponent>().nextPattern;
			entity.removeComponent<TimedMovementComponent>();
			entity.activate();
			if (nextPattern != "") {
				m_gameInstance.addPatternToEntity(
					nextPattern,
					entity.getId().index
				);
			}
			if (entity.hasComponent<GroundCharacterStateComponent>()) {
				entity.getComponent<GroundCharacterStateComponent>().state = GroundCharacterState::IDLE;
			}

			velocity = b2Vec2(0.f, 0.f);
		}
	}
}
