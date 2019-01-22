#include "AbstractChickenBossData.h"
#include "MonsterDamagedComponent.h"

const std::string AbstractChickenBossData::texturePath = "chickenBoss.png";
const sf::Vector2i AbstractChickenBossData::entitySize = sf::Vector2i(55, 142);
const b2Vec2 AbstractChickenBossData::velocity = b2Vec2(6.5f, 0.f);
const int AbstractChickenBossData::lifes = 5;

const std::map<GroundCharacterState, AnimationStateComponent> AbstractChickenBossData::animationStates{
	{
		GroundCharacterState::IDLE,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(32, 477),
					sf::Vector2i(50, 144)
				)
			}
		)
	},
	{
		GroundCharacterState::WALK,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(13, 17),
					sf::Vector2i(50, 145)
				),
				SpriteBox(
					sf::Vector2i(155, 22),
					sf::Vector2i(65, 140)
				),
				SpriteBox(
					sf::Vector2i(299, 18),
					sf::Vector2i(50, 144)
				),
				SpriteBox(
					sf::Vector2i(440, 22),
					sf::Vector2i(66, 142)
				)
			},
			0.3f
		)
	},
	{
		GroundCharacterState::CLOSE_ATTACK,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(4, 180),
					sf::Vector2i(121, 136)
				),
				SpriteBox(
					sf::Vector2i(147, 180),
					sf::Vector2i(138, 137)
				),
				SpriteBox(
					sf::Vector2i(4, 180),
					sf::Vector2i(121, 136)
				)
			},
			0.2f
		)
	},
	{
		GroundCharacterState::RANGE_ATTACK,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(10, 332),
					sf::Vector2i(82, 118),
					sf::Vector2f(0, 13)
				),
				SpriteBox(
					sf::Vector2i(155, 328),
					sf::Vector2i(89, 122),
					sf::Vector2f(0, 12)
				),
				SpriteBox(
					sf::Vector2i(296, 340),
					sf::Vector2i(96, 110),
					sf::Vector2f(0, 17)
				)
			},
			0.3f
		)
	},
	{
		GroundCharacterState::FALL,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(32, 477),
					sf::Vector2i(50, 144)
				)
			}
		)
	},
	{
		GroundCharacterState::DYING,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(24, 650),
					sf::Vector2i(68, 142)
				)
			}
		)
	},
	{
		GroundCharacterState::DAMAGED,
		AnimationStateComponent(
			std::vector<SpriteBox> {
			SpriteBox(
				sf::Vector2i(24, 650),
				sf::Vector2i(68, 142)
			)
		}
		)
	},
	{
		GroundCharacterState::SPECIAL_STATE,
		AnimationStateComponent(
			std::vector<SpriteBox> {
				SpriteBox(
					sf::Vector2i(32, 477),
					sf::Vector2i(50, 144)
				),
				SpriteBox(
					sf::Vector2i(174, 477),
					sf::Vector2i(51, 144)
				)
			},
			0.2f
		)
	}
};


AbstractChickenBossData::AbstractChickenBossData()
	: AbstractMonsterData::AbstractMonsterData(
		AbstractChickenBossData::texturePath,
		AbstractChickenBossData::entitySize,
		AbstractChickenBossData::velocity,
		AbstractChickenBossData::animationStates,
		ElementalType::DEFAULT,
		AbstractChickenBossData::lifes
	)
{
}


AbstractChickenBossData::~AbstractChickenBossData()
{
}

void AbstractChickenBossData::initializeEntity(
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
	entity.getComponent<MonsterDamagedComponent>().velocity = b2Vec2(15.f, 0.f);
}