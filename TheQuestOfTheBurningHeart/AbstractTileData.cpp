#include "AbstractTileData.h"
#include "TileComponent.h"
#include "LayerLevel.h"

AbstractTileData::AbstractTileData(
	std::string texturePath,
	PhysicType physicType,
	sf::Vector2i entitySize)
	: AbstractSpriteEntityData::AbstractSpriteEntityData(
		texturePath,
		physicType,
		entitySize
	),
	m_timedMovementTimer(0.f),
	m_velocity(0.f, 0.f)
{
}

AbstractTileData::AbstractTileData(
	std::string texturePath,
	PhysicType physicType,
	sf::Vector2i entitySize,
	float timedMovementTimer,
	b2Vec2 velocity)
	: AbstractSpriteEntityData::AbstractSpriteEntityData(
		texturePath,
		physicType,
		entitySize
	),
	m_timedMovementTimer(timedMovementTimer),
	m_velocity(velocity)
{

}


AbstractTileData::~AbstractTileData()
{
}

void AbstractTileData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	AbstractSpriteEntityData::initializeEntity(
		dataId,
		entity,
		gameInstance,
		position,
		specificData
	);

	entity.addComponent<TileComponent>();
	entity.getComponent<DrawableComponent>().layer = (int)LayerLevel::TILE_1;


	if (m_timedMovementTimer != 0.f) {
		entity.getComponent<TileComponent>().velocity = m_velocity;
		entity.addComponent<TimedMovementComponent>(m_timedMovementTimer);
		entity.addComponent<VelocityComponent>();
		entity.getComponent<DrawableComponent>().layer = (int)LayerLevel::TILE_0;
	}
}