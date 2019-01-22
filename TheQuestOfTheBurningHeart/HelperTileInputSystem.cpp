#include "HelperTileInputSystem.h"
#include "InputManager.h"
#include "GameScreen.h"
#include "GameScreenInformationState.h"


HelperTileInputSystem::HelperTileInputSystem(
	GameScreen& gameInstance)
	: m_gameInstance(gameInstance)
{
}

void HelperTileInputSystem::updateEvent()
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& helperComponent = entity.getComponent<HelperTileComponent>();
		if (helperComponent.activated)
		{
			if (InputManager::keyPressed(sf::Keyboard::E)) {
				m_gameInstance.getState()->setState(
					m_gameInstance,
					new GameScreenInformationState(helperComponent.helperContent)
				);
			}
		}
	}
}