#pragma once
#include "FontsManager.h"
#include "DialogSide.h"
#include <SFML/Graphics.hpp>
#include <anax/Component.hpp>

struct DialogComponent : anax::Component {
	DialogComponent(
		DialogSide side,
		sf::Vector2f position,
		std::string text,
		std::string title = "")
		: dialogSide(side),
		dialogTitle(title),
		dialogContent(text),
		updateContent(0.f),
		contentCout(0)
	{
		if (title != "" && dialogSide != DialogSide::FULL) {
			dialogTitleText.setFillColor(sf::Color(249, 198, 31));
			dialogTitleText.setFont(FontsManager::getFont(Font::ARIAL));
			dialogTitleText.setCharacterSize(27);
			dialogTitleText.setString("- " + title + " -");

			if (side != DialogSide::FULL)
				dialogTitleText.setPosition(
					sf::Vector2f(
						position.x + 50,
						position.y + 20
					)
				);
		}

		dialogContentText.setFillColor(sf::Color::White);
		dialogContentText.setFont(FontsManager::getFont(Font::ARIAL));
		dialogContentText.setCharacterSize(24);
		dialogContentText.setString("");

		if (side != DialogSide::FULL)
			dialogContentText.setPosition(
				sf::Vector2f(
					position.x + 50,
					position.y + 55
				)
			);
	}

	const std::string dialogTitle;
	sf::Text dialogTitleText;

	const std::string dialogContent;
	sf::Text dialogContentText;

	float updateContent;
	int contentCout;
	DialogSide dialogSide;
};