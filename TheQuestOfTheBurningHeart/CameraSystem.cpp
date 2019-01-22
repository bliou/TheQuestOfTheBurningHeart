#include "CameraSystem.h"
#include "Helpers.h"


CameraSystem::CameraSystem()
{
	m_view.setSize(sf::Vector2f(screenSize));
	m_view.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));
}

void CameraSystem::setMapSize(sf::Vector2i mapSize)
{
	m_mapSize = mapSize;
}

void CameraSystem::render(sf::RenderWindow& window)
{
	auto entities = getEntities();
	for (auto& entity : entities)
	{
		sf::Vector2f center;
		auto& position = entity.getComponent<PositionComponent>().position;
		if (position.x < screenSize.x / 2
			|| m_mapSize.x <= screenSize.x)
			center.x = screenSize.x / 2.f;
		else if (position.x > m_mapSize.x - screenSize.x / 2)
			center.x = m_mapSize.x - screenSize.x / 2.f;
		else
			center.x = position.x;

		if (position.y < screenSize.y / 2
			|| m_mapSize.y <= screenSize.y)
			center.y = screenSize.y / 2.f;
		else if (position.y > m_mapSize.y - screenSize.y / 2)
			center.y = m_mapSize.y - screenSize.y / 2.f;
		else
			center.y = position.y;

		m_view.setCenter(center);
		window.setView(m_view);
	}

	// If no entities has the camera component,
	// fix it in the middle of the screen
	if (entities.size() == 0) {
		m_view.setCenter(sf::Vector2f(
			screenSize.x / 2.f,
			screenSize.y / 2.f
		));
		window.setView(m_view);
	}
}