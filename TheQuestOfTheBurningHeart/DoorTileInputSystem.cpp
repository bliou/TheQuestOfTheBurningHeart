#include "DoorTileInputSystem.h"
#include "InputManager.h"
#include "GameScreen.h"
#include "ConfigManager.h"

DoorTileInputSystem::DoorTileInputSystem(GameScreen& gameInstance)
	: m_gameInstance(gameInstance)
{
}

void DoorTileInputSystem::updateEvent()
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		auto& doorComponent = entity.getComponent<DoorTileComponent>();
		if (doorComponent.activated)
		{
			if (InputManager::keyPressed(sf::Keyboard::E)) {
				if (!doorComponent.clearConfig)
					m_gameInstance.nextGameLevel();
				
				ConfigAction action = doorComponent.clearConfig
					? ConfigAction::CLEAR
					: ConfigAction::FULL_SAVE;
				m_gameInstance.changeScreen(
					doorComponent.nextScreen,
					action);
			}
		}
	}
}