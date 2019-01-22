#include "CharacterSlopeTileSystem.h"
#include "MonsterComponent.h"
#include "PositionComponent.h"
#include "SizeComponent.h"
#include "SlopeTileComponent.h"

CharacterSlopeTileSystem::CharacterSlopeTileSystem()
{
}

void CharacterSlopeTileSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& state = entity.getComponent<GroundCharacterStateComponent>().state;

		if (state != GroundCharacterState::WALK)
			continue;

		auto& orientation = entity.getComponent<CharacterOrientationComponent>().orientation;
		auto& velocity = entity.getComponent<VelocityComponent>().velocity;
		auto& charVel = entity.getComponent<CharacterComponent>().velocity;
		auto& slopeType = entity.getComponent<CharacterSlopeTileComponent>().slopeType;
		uint64_t slopeId = entity.getComponent<CharacterSlopeTileComponent>().slopeId;
		anax::Entity slopeTile = entity.getWorld().getEntity(slopeId);
		auto& slopePosition = slopeTile.getComponent<PositionComponent>().position;

		auto& charPosition = entity.getComponent<PositionComponent>().position;
		auto& charSize = entity.getComponent<SizeComponent>().size;

		// In the event the player is higher than the current slope tile
		// and if he does not have any other slope tiles under his feet,
		// then remove the component
		if (charPosition.y + charSize.y / 2.f < slopePosition.y) {
			auto footContacts = entity.getComponent<CharacterComponent>().footContacts;
			if (footContacts.size() > 1
				&& ((slopeType == SlopeType::SLOPE_UP
					&& orientation == CharacterOrientation::RIGHT)
					|| (slopeType == SlopeType::SLOPE_DOWN
						&& orientation == CharacterOrientation::LEFT))) {
				velocity.y = 0.f;
				continue;
			}
		}


		if (orientation == CharacterOrientation::LEFT) {
			velocity.x = -charVel.x;
			if (slopeType == SlopeType::SLOPE_DOWN)
				velocity.y = -charVel.x;
			else
				velocity.y = charVel.x;
		}
		else {
			velocity.x = charVel.x;

			if (slopeType == SlopeType::SLOPE_DOWN)
				velocity.y = charVel.x;
			else
				velocity.y = -charVel.x;
		}
	}
}