#include "BreakableTileData.h"
#include "BreakableTileComponent.h"

const std::string BreakableTileData::texturePath = "breakableTiles.png";
const std::map<bool, AnimationStateComponent> BreakableTileData::animationStates = {
	{
		false,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(0, 0),
					sf::Vector2i(64, 64)
				)
			}
		)
	},
	{
		true,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(64, 0),
					sf::Vector2i(64, 64)
				)
			}
		)
	}
};


BreakableTileData::BreakableTileData(std::string tileToCreate)
	: AbstractSolidBlockTileData::AbstractSolidBlockTileData(
		BreakableTileData::texturePath
	),
	m_tileToCreate(tileToCreate)
{
}


BreakableTileData::~BreakableTileData()
{
}

void BreakableTileData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	AbstractSolidBlockTileData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);

	entity.addComponent<BreakableTileComponent>(m_tileToCreate);
	entity.addComponent<AnimationComponent>();
	entity.addComponent<ActivateTileAnimationComponent>().states = BreakableTileData::animationStates;
	entity.getComponent<AnimationComponent>().state = BreakableTileData::animationStates.at(false);
}