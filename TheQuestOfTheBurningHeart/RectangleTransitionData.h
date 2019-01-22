#pragma once
#include "TransitionType.h"
#include "AbstractShapeEntityData.h"

class RectangleTransitionData : public AbstractShapeEntityData
{
public:
	RectangleTransitionData(TransitionType transitionType);
	~RectangleTransitionData();

	void initializeEntity(
		std::string dataId,
		anax::Entity& entity,
		GameScreen& gameInstance,
		sf::Vector2f position,
		nlohmann::json::value_type specificData) override;

protected:
	TransitionType m_transitionType;
};

