#include "GroupSolidBlockTileData.h"
#include "GroupComponent.h"


GroupSolidBlockTileData::GroupSolidBlockTileData(BaseTileType tileType)
	: SolidBlockTileData::SolidBlockTileData(tileType)
{
}


GroupSolidBlockTileData::~GroupSolidBlockTileData()
{
}

void GroupSolidBlockTileData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	// First add the group component, and then call the
	// base classes that will create the physic
	auto& groupComponent = entity.addComponent<GroupComponent>();
	groupComponent.widthNumber = specificData["widthNumber"];
	groupComponent.heightNumber = specificData["heightNumber"];

	SolidBlockTileData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);

	sf::Vector2i size = entity.getComponent<SizeComponent>().size;
	entity.removeComponent<SizeComponent>();
	entity.addComponent<SizeComponent>(sf::Vector2i(
		size.x * groupComponent.widthNumber,
		size.y * groupComponent.heightNumber
	));
	
	entity.getComponent<TileComponent>().isOneSided = specificData.at("isOneSided");
}
