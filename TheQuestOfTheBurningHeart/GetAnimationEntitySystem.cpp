#include "GetAnimationEntitySystem.h"
#include <stdexcept>


GetAnimationEntityIdSystem::GetAnimationEntityIdSystem()
{
}

uint64_t GetAnimationEntityIdSystem::getEntityId(std::string animationId)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		if (entity.getComponent<AnimationIdComponent>().id == animationId)
			return entity.getId().index;
	}

	throw std::runtime_error("No animation entity with custom id " + animationId);
}