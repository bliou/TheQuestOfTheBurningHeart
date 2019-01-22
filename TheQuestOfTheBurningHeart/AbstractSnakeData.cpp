#include "AbstractSnakeData.h"
#include "FallingTriggerComponent.h"

const std::string AbstractSnakeData::texturePath = "snakes.png";
const sf::Vector2i AbstractSnakeData::entitySize = sf::Vector2i(40, 38);
const b2Vec2 AbstractSnakeData::velocity = b2Vec2(6.8f, 0.f);
const std::map<GroundCharacterState, AnimationStateComponent> AbstractSnakeData::animationStates{
	{
		GroundCharacterState::IDLE,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(0, 0),
					sf::Vector2i(40, 38)
				)
			}
		)
	},
	{
		GroundCharacterState::WALK,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(0, 0),
					sf::Vector2i(40, 38)
				),
				SpriteBox(
					sf::Vector2i(40, 0),
					sf::Vector2i(41, 38)
				),
				SpriteBox(
					sf::Vector2i(81, 0),
					sf::Vector2i(40, 38)
				)
			}
		)
	},
	{
		GroundCharacterState::FALL,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(0, 0),
					sf::Vector2i(40, 38)
				)
			}
		)
	},
	{
		GroundCharacterState::DYING,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(0, 38),
					sf::Vector2i(40, 38)
				)
			}
		)
	}
};



AbstractSnakeData::AbstractSnakeData(ElementalType elementalType)
	: AbstractMonsterData::AbstractMonsterData(
		AbstractSnakeData::texturePath,
		AbstractSnakeData::entitySize,
		AbstractSnakeData::velocity,
		AbstractSnakeData::animationStates,
		elementalType
	)
{
}


AbstractSnakeData::~AbstractSnakeData()
{
}

void AbstractSnakeData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	AbstractMonsterData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);
	b2Body* body = entity.getComponent<PhysicComponent>().body;
	entity.addComponent<FallingTriggerComponent>(
		body,
		AbstractSnakeData::entitySize
	);
}