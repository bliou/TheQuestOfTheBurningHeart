#pragma once
#include <string>
#include "sPlayerData.h"

class ConfigManager
{
public:
	ConfigManager();
	~ConfigManager();

	static bool doesConfigExists();
	static void saveDefaultConfig();
	static void saveConfig(int gameLevel);
	static void saveConfig(
		sPlayerData playerData,
		int gameLevel
	);
	static void clearConfig();
	static sPlayerData getPlayerData();
	static int getGameLevel();
	static void setPlayerData(sPlayerData);

protected:
	static const std::string configPath;
};
