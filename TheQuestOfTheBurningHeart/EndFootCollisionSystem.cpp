#include "EndFootCollisionSystem.h"
#include "SlopeTileComponent.h"
#include "CharacterSlopeTileComponent.h"



EndFootCollisionSystem::EndFootCollisionSystem()
{
}

void EndFootCollisionSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities) {
		auto& footContacts = entity.getComponent<CharacterComponent>().footContacts;
		auto collidedEntitiesId = entity.getComponent<EndFootCollisionComponent>().collidedEntitiesId;

		for (uint64_t collidedEntityId : collidedEntitiesId)
		{
			footContacts.erase(
				std::remove(footContacts.begin(), footContacts.end(), collidedEntityId),
				footContacts.end()
			);

			if (entity.hasComponent<CharacterSlopeTileComponent>()) {
				bool remove = true;
				for (auto& footContact : footContacts) {
					auto footContactEntity = entity.getWorld().getEntity(footContact);
					if (footContactEntity.hasComponent<SlopeTileComponent>()) {
						remove = false;
						break;
					}
				}

				if (remove)
					entity.removeComponent<CharacterSlopeTileComponent>();
			}
		}

		entity.removeComponent<EndFootCollisionComponent>();
		entity.activate();
	}
}