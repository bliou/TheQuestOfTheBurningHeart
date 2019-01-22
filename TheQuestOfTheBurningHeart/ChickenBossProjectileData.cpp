#include "ChickenBossProjectileData.h"
#include "ProjectileComponent.h"

const std::string ChickenBossProjectileData::texturePath = "chickenBoss.png";
const sf::Vector2i ChickenBossProjectileData::entitySize = sf::Vector2i(32, 32);
const float ChickenBossProjectileData::lifeSpan = 4.5f;
const AnimationStateComponent ChickenBossProjectileData::animationState(
	std::vector<SpriteBox> {
		SpriteBox(
			sf::Vector2i(44, 836),
			sf::Vector2i(33, 32)
		),
		SpriteBox(
			sf::Vector2i(186, 835),
			sf::Vector2i(36, 34)
		),
		SpriteBox(
			sf::Vector2i(328, 835),
			sf::Vector2i(38, 35)
		)
	},
	0.2f
);

ChickenBossProjectileData::ChickenBossProjectileData()
	: AbstractProjectileData::AbstractProjectileData(
		ChickenBossProjectileData::texturePath,
		ChickenBossProjectileData::entitySize,
		ChickenBossProjectileData::lifeSpan
	)
{
}


ChickenBossProjectileData::~ChickenBossProjectileData()
{
}

void ChickenBossProjectileData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	AbstractProjectileData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);
	entity.addComponent<InfiniteMovementComponent>();

	uint64_t playerId = gameInstance.getPlayerId();
	anax::Entity player = gameInstance.getWorld()->getEntity(playerId);
	sf::Vector2f playerPosition = player.getComponent<PositionComponent>().position;

	b2Vec2 velocity = b2Vec2(
		(playerPosition.x - position.x) / 50.f,
		(playerPosition.y - position.y) / 50.f
	);
	entity.getComponent<ProjectileComponent>().velocity = velocity;
	entity.addComponent<AnimationComponent>().state = ChickenBossProjectileData::animationState;
}