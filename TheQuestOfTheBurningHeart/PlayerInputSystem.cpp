#include "PlayerInputSystem.h"
#include "InputManager.h"
#include "SoundsManager.h"
#include "PlayerJumpLoaderComponent.h"


PlayerInputSystem::PlayerInputSystem()
{
}

void PlayerInputSystem::updateEvent(bool releasedOnly)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& characterVel = entity.getComponent<CharacterComponent>().velocity;
		auto& state = entity.getComponent<GroundCharacterStateComponent>().state;
		auto& orientation = entity.getComponent<CharacterOrientationComponent>().orientation;
		auto& velocity = entity.getComponent<VelocityComponent>().velocity;
		auto& elementalComponent = entity.getComponent<PlayerElementalTypeComponent>();

		if (state == GroundCharacterState::DYING)
			continue;

		if (InputManager::keyPressed(sf::Keyboard::Left)
			&& !releasedOnly) {
			if (state == GroundCharacterState::IDLE)
				state = GroundCharacterState::WALK;
			orientation = CharacterOrientation::LEFT;
			velocity.x = -characterVel.x;
		}
		if (InputManager::keyPressed(sf::Keyboard::Right)
			&& !releasedOnly) {
			if (state == GroundCharacterState::IDLE)
				state = GroundCharacterState::WALK;
			orientation = CharacterOrientation::RIGHT;
			velocity.x = characterVel.x;
		}
		if (InputManager::keyReleased(sf::Keyboard::Left)) {
			if (orientation == CharacterOrientation::LEFT) {
				if (state == GroundCharacterState::WALK)
					state = GroundCharacterState::IDLE;
				velocity.x = 0.f;
			}
		}
		if (InputManager::keyReleased(sf::Keyboard::Right)) {
			if (orientation == CharacterOrientation::RIGHT) {
				if (state == GroundCharacterState::WALK)
					state = GroundCharacterState::IDLE;
				velocity.x = 0.f;
			}
		}
		if ((state == GroundCharacterState::IDLE
			|| state == GroundCharacterState::CLOSE_ATTACK
			|| state == GroundCharacterState::WALK)
			&& (InputManager::keyPressed(sf::Keyboard::Space)
				|| InputManager::keyPressed(sf::Keyboard::Up))
			&& !releasedOnly) {
			state = GroundCharacterState::JUMP;
			entity.addComponent<PlayerJumpLoaderComponent>(0.5f);
			entity.activate();
			velocity.y = characterVel.y;
			SoundsManager::playSound(SoundType::PLAYER_JUMP);
		}
		if ((InputManager::keyReleased(sf::Keyboard::Space)
			|| InputManager::keyReleased(sf::Keyboard::Up))) {
			if (entity.hasComponent<PlayerJumpLoaderComponent>()) {
				entity.removeComponent<PlayerJumpLoaderComponent>();
				entity.activate();
			}
		}
		if (InputManager::keyPressed(sf::Keyboard::Num1)
			&& !releasedOnly) {
			elementalComponent.currentElementalType = ElementalType::DEFAULT;
		}
		if (InputManager::keyPressed(sf::Keyboard::Num2)
			&& !releasedOnly) {
			if (elementalComponent.playerElementalTypes[ElementalType::FIRE].remainingTime > 0.f) {
				elementalComponent.currentElementalType = ElementalType::FIRE;
			}
		}
	}

}