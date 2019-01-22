#pragma once
#include <map>

enum class DecorativeTileType {
	FIELD = 0,
	FIELD_TRUCK = 1,
	FIELD_BARN = 2,
	FIELD_HOUSE = 3,
	CENTER_CORN_FIELD = 4,
	LEFT_CORN_FIELD = 5,
	RIGHT_CORN_FIELD = 6,
	LEFT_RIGHT_CORN_FIELD = 7,
	CORN_FIELD_TREE = 8,
	KIRBY_HOUSE_CLOSE = 9,
	KIRBY_HOUSE_OPEN = 10,
	MEADOW_NEUTRAL = 11,
	MEADOW_ROCK = 12,
	MEADOW_CHURCH = 13,
	MEADOW_TRUCK = 14,
	MEADOW_WINDMILL = 15,
	MEADOW_WRECK = 16
};

const std::map<DecorativeTileType, std::string> decorativeTileTextures {
	{ DecorativeTileType::FIELD, "Champs/field.png" },
	{ DecorativeTileType::FIELD_TRUCK, "Champs/field_truck.png" },
	{ DecorativeTileType::FIELD_BARN, "Champs/field_barn.png" },
	{ DecorativeTileType::FIELD_HOUSE, "Champs/field_house.png" },
	{ DecorativeTileType::CENTER_CORN_FIELD, "Champs/center_corn_field.png" },
	{ DecorativeTileType::LEFT_CORN_FIELD, "Champs/left_corn_field.png" },
	{ DecorativeTileType::RIGHT_CORN_FIELD, "Champs/right_corn_field.png" },
	{ DecorativeTileType::LEFT_RIGHT_CORN_FIELD, "Champs/left_right_corn_field.png" },
	{ DecorativeTileType::CORN_FIELD_TREE, "Introduction/corn_field_tree.png" },
	{ DecorativeTileType::KIRBY_HOUSE_CLOSE, "Introduction/kirby_house_close.png" },
	{ DecorativeTileType::KIRBY_HOUSE_OPEN, "Introduction/kirby_house_open.png" },
	{ DecorativeTileType::MEADOW_NEUTRAL, "Prairies/meadow_neutral.png" },
	{ DecorativeTileType::MEADOW_ROCK, "Prairies/meadow_rock.png" },
	{ DecorativeTileType::MEADOW_CHURCH, "Prairies/meadow_church.png" },
	{ DecorativeTileType::MEADOW_TRUCK, "Prairies/meadow_truck.png" },
	{ DecorativeTileType::MEADOW_WINDMILL, "Prairies/meadow_windmill.png" },
	{ DecorativeTileType::MEADOW_WRECK, "Prairies/meadow_wreck.png" }
};