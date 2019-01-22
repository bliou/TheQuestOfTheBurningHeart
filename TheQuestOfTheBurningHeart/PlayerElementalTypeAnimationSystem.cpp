#include "PlayerElementalTypeAnimationSystem.h"



PlayerElementalTypeAnimationSystem::PlayerElementalTypeAnimationSystem()
{
}

void PlayerElementalTypeAnimationSystem::update(float elapsedTime)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& elementalType = entity.getComponent<PlayerElementalTypeComponent>().currentElementalType;
		auto& offset = entity.getComponent<PlayerElementalTypeAnimationComponent>().typeOffset.at(elementalType);
		entity.getComponent<ElementalAnimationOffsetComponent>().offset = offset;
	}
}