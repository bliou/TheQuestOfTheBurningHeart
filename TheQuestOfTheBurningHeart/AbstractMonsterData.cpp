#include "AbstractMonsterData.h"
#include "MonsterComponent.h"
#include "MonsterDamagedComponent.h"
#include "DisableComponent.h"
#include "ElementalTypeComponent.h"


const PhysicType AbstractMonsterData::physicType = PhysicType::pMonster;

AbstractMonsterData::AbstractMonsterData(
	std::string texturePath,
	sf::Vector2i entitySize,
	b2Vec2 velocity,
	const std::map<GroundCharacterState, AnimationStateComponent> animationStates,
	ElementalType elementalType,
	int lifes)
	: AbstractCharacterData::AbstractCharacterData(
		texturePath,
		AbstractMonsterData::physicType,
		entitySize,
		velocity,
		animationStates,
		lifes
	),
	m_elementalType(elementalType)
{
}


AbstractMonsterData::~AbstractMonsterData()
{
}

void AbstractMonsterData::initializeEntity(
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
	entity.addComponent<MonsterComponent>();
	entity.addComponent<MonsterDamagedComponent>().velocity = b2Vec2(0.f, 0.f);
	entity.addComponent<DisableComponent>();
	entity.addComponent<ElementalTypeComponent>(m_elementalType);
}