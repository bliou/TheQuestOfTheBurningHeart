#pragma once
#include <SFML/Graphics.hpp>
#include "Screen.h"

class AbstractScreen
{
public:
	AbstractScreen();
	~AbstractScreen();

	virtual int run(sf::RenderWindow&) = 0;

protected:
	bool m_changeScreen;
};

