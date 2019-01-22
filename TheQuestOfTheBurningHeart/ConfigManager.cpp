#include "ConfigManager.h"
#include "json.hpp"
#include <fstream>

const std::string ConfigManager::configPath = "Resources/Saves/config.json";

ConfigManager::ConfigManager()
{
}


ConfigManager::~ConfigManager()
{
}

bool ConfigManager::doesConfigExists()
{
	std::ifstream file(ConfigManager::configPath);
	return file.peek() != std::ifstream::traits_type::eof();
}

void ConfigManager::saveDefaultConfig()
{
	nlohmann::json json;
	json["gameLevel"] = 1;
	json["playerLife"] = 3;
	json["playerCoins"] = 0;
	json["playerElementalTypes"]["fire"] = 0.0;

	std::ofstream file(ConfigManager::configPath);
	file << json;
}

void ConfigManager::saveConfig(
	int gameLevel)
{
	std::ifstream ifile(ConfigManager::configPath);
	nlohmann::json json;
	ifile >> json;

	json["gameLevel"] = gameLevel;

	std::ofstream ofile(ConfigManager::configPath);
	ofile << json;
}

void ConfigManager::saveConfig(
	sPlayerData playerData, 
	int gameLevel)
{
	std::ifstream ifile(ConfigManager::configPath);
	nlohmann::json json;
	ifile >> json;

	json["gameLevel"] = gameLevel;
	json["playerLife"] = playerData.playerLife;
	json["playerCoins"] = playerData.playerCoins;
	json["playerElementalTypes"]["fire"] = playerData.playerElementalTypes.fire;

	std::ofstream ofile(ConfigManager::configPath);
	ofile << json;
}

void ConfigManager::clearConfig()
{
	std::ofstream ofs;
	ofs.open(
		ConfigManager::configPath,
		std::ofstream::out | std::ofstream::trunc
	);
	ofs.close();
}

sPlayerData ConfigManager::getPlayerData()
{
	std::ifstream file(ConfigManager::configPath);
	nlohmann::json json;
	file >> json;

	sPlayerData playerData;
	playerData.playerLife = json["playerLife"];
	playerData.playerCoins = json["playerCoins"];
	playerData.playerElementalTypes.fire = json["playerElementalTypes"]["fire"];

	return playerData;
}

int ConfigManager::getGameLevel()
{
	std::ifstream file(ConfigManager::configPath);
	nlohmann::json json;
	file >> json;

	int gameLevel = json["gameLevel"];
	return gameLevel;
}

void ConfigManager::setPlayerData(sPlayerData playerData)
{
	std::ifstream ifile(ConfigManager::configPath);
	nlohmann::json json;
	ifile >> json;

	json["playerLife"] = playerData.playerLife;
	json["playerCoins"] = playerData.playerCoins;
	json["playerElementalTypes"]["fire"] = playerData.playerElementalTypes.fire;

	std::ofstream ofile(ConfigManager::configPath);
	ofile << json;
}