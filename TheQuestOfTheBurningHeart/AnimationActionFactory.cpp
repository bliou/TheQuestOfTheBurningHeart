#include "AnimationActionFactory.h"
#include "AnimationActionType.h"
#include "GameScreenAnimationState.h"
#include "TimedMovementComponent.h"
#include "CharacterComponent.h"
#include "CharacterOrientationComponent.h"
#include "GroundCharacterStateComponent.h"
#include "SoundsManager.h"

AnimationActionFactory::AnimationActionFactory()
{
}


AnimationActionFactory::~AnimationActionFactory()
{
}

void AnimationActionFactory::createAnimationActions(
	nlohmann::json& animationJson,
	GameScreen& gameInstance,
	const float currentTimer)
{
	nlohmann::json::iterator it = animationJson["actions"].begin();
	bool isBlocked = false;
	for (it; it != animationJson["actions"].end(); ++it) {
		bool isUsed = it.value().find("isUsed") != it.value().end()
			? (bool)it.value().at("isUsed")
			: false;
		if (isUsed
			|| it.value().at("startTimer") > currentTimer)
			continue;

		createAnimationAction(
			it.value(),
			gameInstance,
			isBlocked);
		it.value()["isUsed"] = true;

		if (isBlocked)
			return;
	}
}

void AnimationActionFactory::createAnimationAction(
	nlohmann::json::value_type data,
	GameScreen& gameInstance,
	bool& isBlocked)
{
	AnimationActionType actionType = data.at("actionType");
	switch (actionType)
	{
	case AnimationActionType::DIALOG:
		gameInstance.addEntityToCreate(
			data.at("dialogType").get<std::string>(), 
			sf::Vector2f(0.f, 0.f),
			data
		);
		isBlocked = true;
		break;
	case AnimationActionType::RECTANGLE_TRANSITION:
		gameInstance.addEntityToCreate(
			data.at("transitionType").get<std::string>(),
			sf::Vector2f(0.f, 0.f),
			data
		);
		break;
	case AnimationActionType::TIMED_MOVEMENT:
	{
		GameScreenAnimationState* animationState = dynamic_cast<GameScreenAnimationState*>(
			gameInstance.getState()
		);
		if (!animationState)
			throw std::runtime_error("The expected state should be animation");
		uint64_t entityId = animationState->getAnimationEntity(
			gameInstance,
			data.at("targetId").get<std::string>()
		);
		anax::Entity entity = gameInstance.getWorld()->getEntity(entityId);
		b2Vec2 velocity;
		if (data.find("velocity") != data.end()) {
			velocity = b2Vec2(
				data.at("velocity").at("x"),
				data.at("velocity").at("y")
			);
			entity.addComponent<TimedMovementComponent>(
				static_cast<float>(data.at("timer")),
				true,
				velocity
			);
		}
		else {
			entity.addComponent<TimedMovementComponent>(
				static_cast<float>(data.at("timer"))
			);
		}
		entity.activate();
		break;
	}
	case AnimationActionType::CHANGE_ORIENTATION:
	{
		GameScreenAnimationState* animationState = dynamic_cast<GameScreenAnimationState*>(
			gameInstance.getState()
		);
		if (!animationState)
			throw std::runtime_error("The expected state should be animation");
		uint64_t entityId = animationState->getAnimationEntity(
			gameInstance,
			data.at("targetId").get<std::string>()
		);
		anax::Entity entity = gameInstance.getWorld()->getEntity(entityId);
		if (!entity.hasComponent<CharacterOrientationComponent>())
			throw std::runtime_error("The expected entity should have an orientation component");

		auto& orientation = entity.getComponent<CharacterOrientationComponent>().orientation;
		orientation = (CharacterOrientation)data.at("orientation");

		break;
	}
	case AnimationActionType::CHANGE_STATE:
	{
		GameScreenAnimationState* animationState = dynamic_cast<GameScreenAnimationState*>(
			gameInstance.getState()
		);
		if (!animationState)
			throw std::runtime_error("The expected state should be animation");
		uint64_t entityId = animationState->getAnimationEntity(
			gameInstance,
			data.at("targetId").get<std::string>()
		);
		anax::Entity entity = gameInstance.getWorld()->getEntity(entityId);
		if (entity.hasComponent<GroundCharacterStateComponent>()) {
			auto& state = entity.getComponent<GroundCharacterStateComponent>().state;
			state = (GroundCharacterState)data.at("state");
		}
		else {
			throw std::runtime_error("The expected entity should have an orientation component");
		}
			
		break;
	}
	case AnimationActionType::REMOVE_ENTITY:
	{
		GameScreenAnimationState* animationState = dynamic_cast<GameScreenAnimationState*>(
			gameInstance.getState()
		);
		if (!animationState)
			throw std::runtime_error("The expected state should be animation");
		uint64_t entityId = animationState->getAnimationEntity(
			gameInstance,
			data.at("targetId").get<std::string>()
		);
		anax::Entity entity = gameInstance.getWorld()->getEntity(entityId);
		entity.addComponent<KillComponent>();
		entity.activate();

		break;
	}
	case AnimationActionType::ADD_ENTITY:
	{
		gameInstance.addEntityToCreate(
			data.at("dataId").get<std::string>(),
			sf::Vector2f(
				data.at("positionX"),
				data.at("positionY")
			)
		);
		break;
	}
	case AnimationActionType::PLAY_SOUND:
	{
		SoundsManager::playSound((SoundType)data.at("soundId"));
		break;
	}
	case AnimationActionType::NEXT_LEVEL:
	{
		gameInstance.nextGameLevel();
		break;
	}
	case AnimationActionType::CHANGE_SCREEN:
	{
		gameInstance.changeScreen(
			data.at("screen"), 
			data.at("configAction"));
		break;
	}
	default:
		throw std::range_error((int)actionType + " was not yet implemented");
	}
}