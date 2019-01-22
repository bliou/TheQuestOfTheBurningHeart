#include "GetTileIdByPositionSystem.h"



GetTileIdByPositionSystem::GetTileIdByPositionSystem()
{
}

uint64_t GetTileIdByPositionSystem::getId(sf::Vector2f position)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		sf::Vector2f tilePosition = entity.getComponent<PositionComponent>().position;
		if (tilePosition.x == position.x
			&& tilePosition.y == position.y)
			return entity.getId().index;
	}
	return std::numeric_limits<uint64_t>::max();
}