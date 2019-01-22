#include "AbstractPlayerData.h"
#include "PlayerElementalTypeAnimationComponent.h"
#include "LayerLevel.h"

const std::string AbstractPlayerData::texturePath = "players.png";
const PhysicType AbstractPlayerData::physicType = PhysicType::pPlayer;
const sf::Vector2i AbstractPlayerData::entitySize = sf::Vector2i(52, 47);
const b2Vec2 AbstractPlayerData::velocity = b2Vec2(12.f, -10.f);
const int AbstractPlayerData::lifes = 3;
const std::map<ElementalType, float> AbstractPlayerData::typeOffset = {
	{ ElementalType::DEFAULT, 0.f },
	{ ElementalType::FIRE, 0.5f }
};
const std::map<GroundCharacterState, AnimationStateComponent> AbstractPlayerData::animationStates{
	{
		GroundCharacterState::IDLE,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(0, 3),
					sf::Vector2i(52, 45),
					sf::Vector2f(0, 3)
				)
			}
		)
	},
	{
		GroundCharacterState::WALK,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(54, 0),
					sf::Vector2i(55, 48)
				),
				SpriteBox(
					sf::Vector2i(109, 3),
					sf::Vector2i(52, 45),
					sf::Vector2f(0, 3)
				),
				SpriteBox(
					sf::Vector2i(170, 3),
					sf::Vector2i(44, 45),
					sf::Vector2f(0, 3)
				),
				SpriteBox(
					sf::Vector2i(218, 0),
					sf::Vector2i(53, 48)
				),
				SpriteBox(
					sf::Vector2i(274, 3),
					sf::Vector2i(53, 45),
					sf::Vector2f(0, 3)
				),
				SpriteBox(
					sf::Vector2i(329, 3),
					sf::Vector2i(51, 45),
					sf::Vector2f(0, 3)
				)
			}
		)
	},
	{
		GroundCharacterState::JUMP,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(5, 58),
					sf::Vector2i(51, 50)
				)
			}
		)
	},
	{
		GroundCharacterState::FALL,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(56, 58),
					sf::Vector2i(53, 48)
				)
			}
		)
	},
	{
		GroundCharacterState::DYING,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(8, 122),
					sf::Vector2i(52, 46)
				)
			}
		)
	}
};


AbstractPlayerData::AbstractPlayerData()
	: AbstractCharacterData::AbstractCharacterData(
		AbstractPlayerData::texturePath,
		AbstractPlayerData::physicType,
		AbstractPlayerData::entitySize,
		AbstractPlayerData::velocity,
		AbstractPlayerData::animationStates,
		AbstractPlayerData::lifes
	)
{
}


AbstractPlayerData::~AbstractPlayerData()
{
}

void AbstractPlayerData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	AbstractCharacterData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);

	entity.addComponent<PlayerElementalTypeAnimationComponent>().typeOffset = AbstractPlayerData::typeOffset;

	entity.getComponent<DrawableComponent>().layer = (int)LayerLevel::CHARACTER_1;
}