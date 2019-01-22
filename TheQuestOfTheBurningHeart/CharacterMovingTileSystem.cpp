#include "CharacterMovingTileSystem.h"
#include "VelocityComponent.h"
#include "SizeComponent.h"
#include "Helpers.h"

CharacterMovingTileSystem::CharacterMovingTileSystem()
{
}

void CharacterMovingTileSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& footContacts = entity.getComponent<CharacterComponent>().footContacts;
		for (auto& footContact : footContacts)
		{
			anax::Entity tile = entity.getWorld().getEntity(footContact);
			if (!tile.hasComponent<VelocityComponent>()
				|| (tile.getComponent<VelocityComponent>().velocity.x == 0.f
					&& tile.getComponent<VelocityComponent>().velocity.y == 0.f))
				continue;

			auto& tilePosComp = tile.getComponent<PositionComponent>();
			sf::Vector2f deltaPos = tilePosComp.position - tilePosComp.previousPosition;

			// Update the physic body first
			b2Body* body = entity.getComponent<PhysicComponent>().body;
			sf::Vector2i size = entity.getComponent<SizeComponent>().size;
			sf::Vector2f sfBodyPos = sf::Vector2f(
				body->GetPosition().x * B2SCALE - size.x / 2,
				body->GetPosition().y * B2SCALE - size.y / 2
			);
			sfBodyPos.x += size.x / 2.f;
			sfBodyPos.y += size.y / 2.f;
			sfBodyPos.x += deltaPos.x;
			if (deltaPos.y > 0) {
				sfBodyPos.y += deltaPos.y;
			}
			b2Vec2 bodyPos = b2Vec2(
				(sfBodyPos.x) / B2SCALE,
				(sfBodyPos.y) / B2SCALE
			);
			body->SetTransform(bodyPos, 0.f);

			break;
		}
	}
}