#include "GroupSolidSlopeTileData.h"
#include "GroupComponent.h"
#include <stdexcept>


GroupSolidSlopeTileData::GroupSolidSlopeTileData(
	SlopeType slopeType,
	BaseTileType tileType)
	: SolidSlopeTileData::SolidSlopeTileData(
		slopeType,
		tileType)
{
}


GroupSolidSlopeTileData::~GroupSolidSlopeTileData()
{
}

void GroupSolidSlopeTileData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	// First add the group component, and then call the
	// base classes that will create the physic
	auto& groupComponent = entity.addComponent<GroupComponent>();
	groupComponent.widthNumber = specificData["sideNumber"];
	groupComponent.heightNumber = specificData["sideNumber"];

	if (groupComponent.widthNumber != groupComponent.heightNumber)
		throw std::runtime_error("The slope group must have the same width and height");

	SolidSlopeTileData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);

	entity.getComponent<TileComponent>().isOneSided = specificData.at("isOneSided");
}
