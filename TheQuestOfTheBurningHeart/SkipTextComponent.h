#pragma once
#include "FontsManager.h"
#include <SFML/Graphics.hpp>
#include <anax/Component.hpp>

struct SkipTextComponent : anax::Component {
	SkipTextComponent() {
		skipText.setFont(FontsManager::getFont(Font::ARIAL));
		skipText.setCharacterSize(15);
		skipText.setString("Press enter to continue...");
		skipText.setFillColor(sf::Color::White);
	};

	sf::Text skipText;
};