#include "AbstractProjectileData.h"
#include "ProjectileComponent.h"
#include "LayerLevel.h"

const PhysicType AbstractProjectileData::physicType = PhysicType::pProjectile;


AbstractProjectileData::AbstractProjectileData(
	std::string texturePath,
	sf::Vector2i entitySize,
	float lifeSpan)
	: AbstractSpriteEntityData::AbstractSpriteEntityData(
		texturePath,
		AbstractProjectileData::physicType,
		entitySize
	),
	m_lifeSpan(lifeSpan)
{
}


AbstractProjectileData::~AbstractProjectileData()
{
}

void AbstractProjectileData::initializeEntity(
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

	entity.addComponent<ProjectileComponent>(m_lifeSpan);
	entity.addComponent<VelocityComponent>();
	entity.getComponent<DrawableComponent>().layer = (int)LayerLevel::CHARACTER_3;
}