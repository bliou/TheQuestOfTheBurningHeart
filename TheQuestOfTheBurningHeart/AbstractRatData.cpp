#include "AbstractRatData.h"

const std::string AbstractRatData::texturePath = "rats.png";
const sf::Vector2i AbstractRatData::entitySize = sf::Vector2i(60, 120);
const b2Vec2 AbstractRatData::velocity = b2Vec2(4.5f, 0.f);
const int AbstractRatData::lifes = 2;

const std::map<GroundCharacterState, AnimationStateComponent> AbstractRatData::animationStates{
	{
		GroundCharacterState::IDLE,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(18, 386),
					sf::Vector2i(60, 118)
				)
			}
		)
	},
	{
		GroundCharacterState::WALK,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(2, 9),
					sf::Vector2i(75, 122)
				),
				SpriteBox(
					sf::Vector2i(109, 11),
					sf::Vector2i(76, 119)
				),
				SpriteBox(
					sf::Vector2i(217, 14),
					sf::Vector2i(76, 117)
				),
				SpriteBox(
					sf::Vector2i(325, 14),
					sf::Vector2i(84, 117)
				),
				SpriteBox(
					sf::Vector2i(427, 8),
					sf::Vector2i(75, 123)
				),
				SpriteBox(
					sf::Vector2i(533, 9),
					sf::Vector2i(78, 121)
				),
				SpriteBox(
					sf::Vector2i(644, 14),
					sf::Vector2i(75, 116)
				),
				SpriteBox(
					sf::Vector2i(750, 17),
					sf::Vector2i(82, 115)
				)
			},
			0.2f
		)
	},
	{
		GroundCharacterState::CLOSE_ATTACK,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(10, 139),
					sf::Vector2i(60, 118)
				),
				SpriteBox(
					sf::Vector2i(103, 139),
					sf::Vector2i(72, 118)
				),
				SpriteBox(
					sf::Vector2i(197, 140),
					sf::Vector2i(85, 118)
				),
				SpriteBox(
					sf::Vector2i(103, 139),
					sf::Vector2i(72, 118)
				),
				SpriteBox(
					sf::Vector2i(10, 139),
					sf::Vector2i(60, 118)
				)
			},
			0.2f
		)
	},
	{
		GroundCharacterState::FALL,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(18, 386),
					sf::Vector2i(60, 118)
				)
			}
		)
	},
	{
		GroundCharacterState::DYING,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(18, 386),
					sf::Vector2i(60, 118)
				)
			}
		)
	},
	{
		GroundCharacterState::SPECIAL_STATE,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(8, 263),
					sf::Vector2i(70, 118)
				),
				SpriteBox(
					sf::Vector2i(116, 262),
					sf::Vector2i(64, 119)
				)
			},
			0.2f
		)
	}
};



AbstractRatData::AbstractRatData(ElementalType elementalType)
	: AbstractMonsterData::AbstractMonsterData(
		AbstractRatData::texturePath,
		AbstractRatData::entitySize,
		AbstractRatData::velocity,
		AbstractRatData::animationStates,
		elementalType,
		AbstractRatData::lifes
	)
{
}


AbstractRatData::~AbstractRatData()
{
}