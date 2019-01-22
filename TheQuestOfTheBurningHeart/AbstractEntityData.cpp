#include "AbstractEntityData.h"
#include "DrawableComponent.h"
#include "PhysicComponent.h"
#include "PositionComponent.h"
#include "SizeComponent.h"
#include "DefaultStateComponent.h"
#include "DataIdComponent.h"

AbstractEntityData::AbstractEntityData(
	PhysicType physicType,
	sf::Vector2i entitySize)
	: m_physicType(physicType),
	m_entitySize(entitySize)
{
}


AbstractEntityData::~AbstractEntityData()
{
}

void AbstractEntityData::initializeEntity(
	std::string dataId,
	anax::Entity& entity,
	GameScreen& gameInstance,
	sf::Vector2f position,
	nlohmann::json::value_type specificData)
{
	if (m_physicType != PhysicType::pNone)
		entity.addComponent<PhysicComponent>().initialize(
			entity,
			position,
			m_entitySize,
			*gameInstance.getPhysicWorld(),
			m_physicType
		);
	entity.addComponent<PositionComponent>(position);
	entity.addComponent<SizeComponent>(m_entitySize);
	entity.addComponent<DefaultStateComponent>();
	entity.addComponent<DataIdComponent>().dataId = dataId;
}