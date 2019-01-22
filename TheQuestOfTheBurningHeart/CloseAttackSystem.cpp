#include "CloseAttackSystem.h"
#include "GameScreen.h"
#include "GameScreenDeadPlayerState.h"


CloseAttackSystem::CloseAttackSystem(GameScreen& gameInstance)
	: m_gameInstance(gameInstance)
{
}

void CloseAttackSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& closePattern = entity.getComponent<CloseAttackPatternComponent>();
		closePattern.currentTimer -= elapsedTime;
		if (closePattern.currentTimer <= 0.f) {
			if (closePattern.removed) {
				if (entity.hasComponent<GroundCharacterStateComponent>()) {
					auto& state = entity.getComponent<GroundCharacterStateComponent>().state;
					state = GroundCharacterState::WALK;
					auto& orientation = entity.getComponent<CharacterOrientationComponent>().orientation;
					orientation = closePattern.previousOrientation;
				}
			}
			else {
				/// If the player did not get out of the colliding box
				/// before the end of the animation,
				/// then he is hitten by the knife and lose a life
				uint64_t playerId = closePattern.playerId;
				anax::Entity player = entity.getWorld().getEntity(playerId);

				auto& state = player.getComponent<GroundCharacterStateComponent>().state;
				auto& lifes = player.getComponent<LifeComponent>().lifes;
				state = GroundCharacterState::DYING;
				lifes--;
				if (lifes < 0)
					throw std::runtime_error("Life canno't be negative");

				m_gameInstance.getState()->setState(m_gameInstance, new GameScreenDeadPlayerState());

			}
			entity.removeComponent<CloseAttackPatternComponent>();
			entity.activate();
		}
	}
}