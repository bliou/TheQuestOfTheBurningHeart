#include "PhysicToPositionSystem.h"
#include "Helpers.h"
#include "CharacterComponent.h"

PhysicToPositionSystem::PhysicToPositionSystem()
{
}

void PhysicToPositionSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		b2Body* body = entity.getComponent<PhysicComponent>().body;
		auto& positionComponent = entity.getComponent<PositionComponent>();
		auto& size = entity.getComponent<SizeComponent>().size;

		positionComponent.previousPosition = 
			positionComponent.position;

		positionComponent.position = sf::Vector2f(
			body->GetPosition().x * B2SCALE - size.x / 2,
			body->GetPosition().y * B2SCALE - size.y / 2
		);

		// Center the sprite for the characters
		if (entity.hasComponent<CharacterComponent>()) {
			positionComponent.position.x += size.x / 2.f;
			positionComponent.position.y += size.y / 2.f;
		}
	}
}