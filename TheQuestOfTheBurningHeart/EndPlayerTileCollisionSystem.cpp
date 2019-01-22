#include "EndPlayerTileCollisionSystem.h"
#include "DoorTileComponent.h"
#include "HelperTileComponent.h"


EndPlayerTileCollisionSystem::EndPlayerTileCollisionSystem()
{
}


void EndPlayerTileCollisionSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities) 
	{
		uint64_t collidedEntityId = entity.getComponent<EndEntityCollisionComponent>().collidedEntityId;
		anax::Entity collidedEntity = entity.getWorld().getEntity(collidedEntityId);
		
		if (collidedEntity.hasComponent<DoorTileComponent>())
		{
			auto& doorComponent = collidedEntity.getComponent<DoorTileComponent>();
			doorComponent.activated = false;
		}
		if (collidedEntity.hasComponent<HelperTileComponent>())
		{
			auto& helperComponent = collidedEntity.getComponent<HelperTileComponent>();
			helperComponent.activated = false;
		}

		// DO NOT REMOVE THE COMPONENT, IT WILL BE REMOVED LATER ON
	}
}