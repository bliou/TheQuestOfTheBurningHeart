#pragma once
#include "AnimationActionFactory.h"
#include "AbstractGameScreenState.h"
#include "json.hpp"

class GameScreenAnimationState: public AbstractGameScreenState
{
public:
	GameScreenAnimationState(std::string animationFileName);
	virtual ~GameScreenAnimationState();

	virtual void update(
		GameScreen& gameScreen,
		float elapsedTime) override;
	virtual void updateEvent(GameScreen& gameScreen) override;
	virtual void draw(
		sf::RenderWindow& window,
		GameScreen& gameScreen) override;

	uint64_t getAnimationEntity(
		GameScreen& gameScreen,
		std::string animationId) const;

protected:
	nlohmann::json m_startStateJson;
	const std::string m_animationFileName;
	static const std::string animationPath;
	AnimationActionFactory m_actionsFactory;

	float m_currentTimer;

	void updatePrePhysicSystems(
		GameScreen& gameScreen,
		float elapsedTime);

	void updatePostPhysicsSystems(
		GameScreen& gameScreen,
		float elapsedTime);

	virtual void renderSystems(
		GameScreen& gameScreen,
		sf::RenderWindow& window) override;
};

