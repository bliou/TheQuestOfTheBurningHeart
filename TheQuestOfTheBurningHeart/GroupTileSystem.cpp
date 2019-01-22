#include "GroupTileSystem.h"
#include "PhysicComponent.h"
#include "SizeComponent.h"
#include "Helpers.h"

GroupTileSystem::GroupTileSystem()
{
}

void GroupTileSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& groupEntitiesId = entity.getComponent<GroupComponent>().entitiesId;
		auto& positionComp = entity.getComponent<PositionComponent>();
		sf::Vector2f deltaPos = positionComp.position - positionComp.previousPosition;

		for (auto& groupEntityId : groupEntitiesId)
		{
			anax::Entity groupEntity = entity.getWorld().getEntity(groupEntityId);
			if (groupEntity.hasComponent<PhysicComponent>()) {
				b2Body* body = groupEntity.getComponent<PhysicComponent>().body;
				sf::Vector2i size = groupEntity.getComponent<SizeComponent>().size;
				sf::Vector2f sfBodyPos = sf::Vector2f(
					body->GetPosition().x * B2SCALE - size.x / 2,
					body->GetPosition().y * B2SCALE - size.y / 2
				);
				sfBodyPos += deltaPos;
				b2Vec2 bodyPos = b2Vec2(
					(sfBodyPos.x + size.x / 2) / B2SCALE,
					(sfBodyPos.y + size.y / 2) / B2SCALE
				);
				body->SetTransform(bodyPos, 0.f);
			}
			auto& groupPosComp = groupEntity.getComponent<PositionComponent>();
			groupPosComp.previousPosition = groupPosComp.position;

			groupPosComp.position += deltaPos;
		}
	}
}