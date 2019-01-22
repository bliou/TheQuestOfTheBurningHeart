#include "PlayerElementalTypeSystem.h"



PlayerElementalTypeSystem::PlayerElementalTypeSystem()
{
}

void PlayerElementalTypeSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& playerElementalComponent = entity.getComponent<PlayerElementalTypeComponent>();
		if (playerElementalComponent.currentElementalType == ElementalType::DEFAULT)
			continue;

		auto& remainingTime = playerElementalComponent.playerElementalTypes[playerElementalComponent.currentElementalType].remainingTime;
		remainingTime -= elapsedTime;

		if (remainingTime <= 0)
			playerElementalComponent.currentElementalType = ElementalType::DEFAULT;
	}
}