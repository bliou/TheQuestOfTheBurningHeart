#include "CheckpointTileData.h"
#include "CheckpointTileComponent.h"
#include "Helpers.h"
#include "ActivateTileAnimationComponent.h"

const std::string CheckpointTileData::texturePath = "checkpointTiles.png";
const sf::Vector2i CheckpointTileData::entitySize = sf::Vector2i(64, 64);
const std::map<bool, AnimationStateComponent> CheckpointTileData::animationStates = {
	{ 
		false,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(0, 0),
					sf::Vector2i(64, 64)
				),
				SpriteBox(
					sf::Vector2i(64, 0),
					sf::Vector2i(64, 64)
				)
			},
			0.2f
		)
	},
	{
		true,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(128, 0),
					sf::Vector2i(64, 64)
				)
			}
		)
	}
};

CheckpointTileData::CheckpointTileData()
	: CheckpointTileData::AbstractSensorTileData(
		CheckpointTileData::texturePath,
		CheckpointTileData::entitySize
	)
{
}


CheckpointTileData::~CheckpointTileData()
{
}

void CheckpointTileData::initializeEntity(
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

	entity.addComponent<CheckpointTileComponent>();
	entity.addComponent<AnimationComponent>();
	entity.addComponent<ActivateTileAnimationComponent>().states = CheckpointTileData::animationStates;
	entity.getComponent<AnimationComponent>().state = CheckpointTileData::animationStates.at(false);
}