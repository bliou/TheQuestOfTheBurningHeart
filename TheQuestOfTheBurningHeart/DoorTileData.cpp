#include "DoorTileData.h"
#include "Helpers.h"
#include "DoorTileComponent.h"

const std::string DoorTileData::texturePath = "doorTiles.png";
const sf::Vector2i DoorTileData::entitySize = sf::Vector2i(64, 100);



DoorTileData::DoorTileData(Screen nextScreen)
	: AbstractSensorTileData::AbstractSensorTileData(
		DoorTileData::texturePath,
		DoorTileData::entitySize
	),
	m_nextScreen(nextScreen)
{
}


DoorTileData::~DoorTileData()
{
}

void DoorTileData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	position = sf::Vector2f(
		position.x + (tileSize.x - entitySize.x) / 2,
		position.y + tileSize.y - entitySize.y
	);
	AbstractSensorTileData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);
	entity.addComponent<DoorTileComponent>(m_nextScreen);
}