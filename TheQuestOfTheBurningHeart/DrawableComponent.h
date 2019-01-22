#pragma once
#include <anax/Component.hpp>
#include <SFML/Graphics.hpp>

struct DrawableComponent: anax::Component
{
	DrawableComponent()
		: scale(sf::Vector2f(1.f, 1.f)),
		layer(0)
	{

	}

	~DrawableComponent()
	{
		delete drawable;
		drawable = nullptr;
	}

	sf::Drawable* drawable;
	int layer;
	sf::Vector2f scale;
};

