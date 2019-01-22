#pragma once
#include "CameraComponent.h"
#include "PositionComponent.h"
#include <anax/System.hpp>

class CameraSystem: public anax::System<anax::Requires<
	CameraComponent,
	PositionComponent
	>>
{
public:
	CameraSystem();

	void render(sf::RenderWindow& window);
	
	void setMapSize(sf::Vector2i mapSize);

protected:
	sf::Vector2i m_mapSize;
	sf::View m_view;
};

