#include "AbstractChickenData.h"

const std::string AbstractChickenData::texturePath = "chickens.png";
const sf::Vector2i AbstractChickenData::entitySize = sf::Vector2i(56, 52);
const b2Vec2 AbstractChickenData::velocity = b2Vec2(7.5f, 0.f);

const std::map<ElementalType, float> AbstractChickenData::typeGraphicOffset{
	{ ElementalType::DEFAULT, 0.f },
	{ ElementalType::FIRE, 0.5f }
};
const std::map<GroundCharacterState, AnimationStateComponent> AbstractChickenData::animationStates{
	{
		GroundCharacterState::IDLE,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(0, 0),
					sf::Vector2i(56, 52)
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
					sf::Vector2i(56, 52)
				),
				SpriteBox(
					sf::Vector2i(56, 5),
					sf::Vector2i(58, 47),
					sf::Vector2f(0, 5)
				),
				SpriteBox(
					sf::Vector2i(114, 0),
					sf::Vector2i(55, 52)
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
					sf::Vector2i(56, 52)
				)
			}
		)
	},
	{
		GroundCharacterState::DYING,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(0, 52),
					sf::Vector2i(56, 52)
				)
			}
		)
	}
};



AbstractChickenData::AbstractChickenData(ElementalType elementalType)
	: AbstractMonsterData::AbstractMonsterData(
		AbstractChickenData::texturePath,
		AbstractChickenData::entitySize,
		AbstractChickenData::velocity,
		AbstractChickenData::animationStates,
		elementalType
	)
{
}


AbstractChickenData::~AbstractChickenData()
{
}

void AbstractChickenData::initializeEntity(
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
	entity.getComponent<ElementalAnimationOffsetComponent>().offset = typeGraphicOffset.at(m_elementalType);
}