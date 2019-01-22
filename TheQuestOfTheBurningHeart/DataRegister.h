#pragma once
#include <map>
#include "AbstractEntityData.h"
#include "GamePlayerData.h"
#include "AnimationPlayerData.h"
#include "KirbabyData.h"

#include "SolidBlockTileData.h"
#include "GroupSolidBlockTileData.h"
#include "SensorBlockTileData.h"
#include "NoPhysicBlockTileData.h"
#include "DecorativeTileData.h"
#include "SolidSlopeTileData.h"
#include "GroupSolidSlopeTileData.h"
#include "SensorSlopeTileData.h"
#include "BonusTileData.h"
#include "HelperTileData.h"
#include "DoorTileData.h"
#include "CheckpointTileData.h"
#include "ElementalTileData.h"
#include "TimedTileData.h"
#include "BreakableTileData.h"

#include "GameChickenData.h"
#include "GameSnakeData.h"
#include "GameRatData.h"
#include "AnimationRatData.h"
#include "GameChickenBossData.h"

#include "ChickenBossProjectileData.h"

#include "DialogData.h"
#include "RectangleTransitionData.h"

#include "FixLayerData.h"

class DataRegistrer {
public:
	DataRegistrer() {
		m_dataRegistrar = {
			{ "p00", new GamePlayerData() },
			{ "p10", new AnimationPlayerData() },
			{ "p20", new KirbabyData() },
			{ "t00", new SolidBlockTileData(BaseTileType::GRASS_CORNER_LEFT) },
			{ "t01", new SolidBlockTileData(BaseTileType::GRASS_TOP) },
			{ "t02", new SolidBlockTileData(BaseTileType::GRASS_CENTER) },
			{ "t03", new SolidBlockTileData(BaseTileType::GRASS_CORNER_RIGHT) },
			{ "t04", new SolidBlockTileData(BaseTileType::GRASS_HALF) },
			{ "t05", new SolidBlockTileData(BaseTileType::DIRT_CORNER_LEFT) },
			{ "t06", new SolidBlockTileData(BaseTileType::DIRT_TOP) },
			{ "t07", new SolidBlockTileData(BaseTileType::DIRT_CENTER) },
			{ "t08", new SolidBlockTileData(BaseTileType::DIRT_CORNER_RIGHT) },
			{ "t09", new SolidBlockTileData(BaseTileType::DIRT_HALF) },
			{ "t0z", new SolidBlockTileData(BaseTileType::TRANSPARENT) },
			{ "g0", new GroupSolidBlockTileData(BaseTileType::GRASS_CORNER_LEFT) },
			{ "g1", new GroupSolidBlockTileData(BaseTileType::GRASS_TOP) },
			{ "g2", new GroupSolidBlockTileData(BaseTileType::GRASS_HALF) },
			{ "g3", new GroupSolidSlopeTileData(SlopeType::SLOPE_UP, BaseTileType::GRASS_SLOPE) },
			{ "g4", new GroupSolidSlopeTileData(SlopeType::SLOPE_DOWN, BaseTileType::GRASS_SLOPE) },
			{ "g5", new GroupSolidBlockTileData(BaseTileType::DIRT_CORNER_LEFT) },
			{ "g6", new GroupSolidBlockTileData(BaseTileType::DIRT_TOP) },
			{ "g7", new GroupSolidBlockTileData(BaseTileType::DIRT_HALF) },
			{ "g8", new GroupSolidSlopeTileData(SlopeType::SLOPE_UP, BaseTileType::DIRT_SLOPE) },
			{ "g9", new GroupSolidSlopeTileData(SlopeType::SLOPE_DOWN, BaseTileType::DIRT_SLOPE) },
			{ "gz", new GroupSolidBlockTileData(BaseTileType::TRANSPARENT) },
			{ "t10", new SensorBlockTileData(BaseTileType::GRASS_CORNER_LEFT) },
			{ "t11", new SensorBlockTileData(BaseTileType::GRASS_TOP) },
			{ "t12", new SensorBlockTileData(BaseTileType::GRASS_CENTER) },
			{ "t13", new SensorBlockTileData(BaseTileType::GRASS_CORNER_RIGHT) },
			{ "t14", new SensorBlockTileData(BaseTileType::GRASS_HALF) },
			{ "t15", new SensorBlockTileData(BaseTileType::DIRT_CORNER_LEFT) },
			{ "t16", new SensorBlockTileData(BaseTileType::DIRT_TOP) },
			{ "t17", new SensorBlockTileData(BaseTileType::DIRT_CENTER) },
			{ "t18", new SensorBlockTileData(BaseTileType::DIRT_CORNER_RIGHT) },
			{ "t19", new SensorBlockTileData(BaseTileType::DIRT_HALF) },
			{ "t1z", new SensorBlockTileData(BaseTileType::TRANSPARENT) },
			{ "t20", new NoPhysicBlockTileData(BaseTileType::GRASS_CORNER_LEFT) },
			{ "t21", new NoPhysicBlockTileData(BaseTileType::GRASS_TOP) },
			{ "t22", new NoPhysicBlockTileData(BaseTileType::GRASS_CENTER) },
			{ "t23", new NoPhysicBlockTileData(BaseTileType::GRASS_CORNER_RIGHT) },
			{ "t24", new NoPhysicBlockTileData(BaseTileType::GRASS_HALF) },
			{ "t25", new NoPhysicBlockTileData(BaseTileType::DIRT_CORNER_LEFT) },
			{ "t26", new NoPhysicBlockTileData(BaseTileType::DIRT_TOP) },
			{ "t27", new NoPhysicBlockTileData(BaseTileType::DIRT_CENTER) },
			{ "t28", new NoPhysicBlockTileData(BaseTileType::DIRT_CORNER_RIGHT) },
			{ "t29", new NoPhysicBlockTileData(BaseTileType::DIRT_HALF) },
			{ "t2z", new NoPhysicBlockTileData(BaseTileType::TRANSPARENT) },
			{ "t30", new DecorativeTileData(DecorativeTileType::FIELD) },
			{ "t31", new DecorativeTileData(DecorativeTileType::FIELD_TRUCK) },
			{ "t32", new DecorativeTileData(DecorativeTileType::FIELD_BARN) },
			{ "t33", new DecorativeTileData(DecorativeTileType::CENTER_CORN_FIELD) },
			{ "t34", new DecorativeTileData(DecorativeTileType::LEFT_CORN_FIELD) },
			{ "t35", new DecorativeTileData(DecorativeTileType::RIGHT_CORN_FIELD) },
			{ "t36", new DecorativeTileData(DecorativeTileType::LEFT_RIGHT_CORN_FIELD) },
			{ "t37", new DecorativeTileData(DecorativeTileType::CORN_FIELD_TREE) },
			{ "t38", new DecorativeTileData(DecorativeTileType::KIRBY_HOUSE_CLOSE) },
			{ "t39", new DecorativeTileData(DecorativeTileType::KIRBY_HOUSE_OPEN) },
			{ "t3a", new DecorativeTileData(DecorativeTileType::FIELD_HOUSE) },
			{ "t3b", new DecorativeTileData(DecorativeTileType::MEADOW_NEUTRAL) },
			{ "t3c", new DecorativeTileData(DecorativeTileType::MEADOW_ROCK) },
			{ "t3d", new DecorativeTileData(DecorativeTileType::MEADOW_CHURCH) },
			{ "t3e", new DecorativeTileData(DecorativeTileType::MEADOW_TRUCK) },
			{ "t3f", new DecorativeTileData(DecorativeTileType::MEADOW_WINDMILL) },
			{ "t3g", new DecorativeTileData(DecorativeTileType::MEADOW_WRECK) },
			{ "ts0", new SolidSlopeTileData(SlopeType::SLOPE_UP, BaseTileType::GRASS_SLOPE) },
			{ "ts1", new SolidSlopeTileData(SlopeType::SLOPE_DOWN, BaseTileType::GRASS_SLOPE) },
			{ "ts2", new SensorSlopeTileData(SlopeType::SLOPE_UP, BaseTileType::GRASS_SLOPE) },
			{ "ts3", new SensorSlopeTileData(SlopeType::SLOPE_DOWN, BaseTileType::GRASS_SLOPE) },
			{ "ts4", new SolidSlopeTileData(SlopeType::SLOPE_UP, BaseTileType::DIRT_SLOPE) },
			{ "ts5", new SolidSlopeTileData(SlopeType::SLOPE_DOWN, BaseTileType::DIRT_SLOPE) },
			{ "ts6", new SensorSlopeTileData(SlopeType::SLOPE_UP, BaseTileType::DIRT_SLOPE) },
			{ "ts7", new SensorSlopeTileData(SlopeType::SLOPE_DOWN, BaseTileType::DIRT_SLOPE) },
			{ "bt0", new BonusTileData(BonusType::HEART) },
			{ "bt1", new BonusTileData(BonusType::COPPER_COIN) },
			{ "bt2", new BonusTileData(BonusType::SILVER_COIN) },
			{ "bt3", new BonusTileData(BonusType::GOLD_COIN) },
			{ "bta", new BonusTileData(BonusType::HEART, 1.f, b2Vec2(0.f, -64.f / B2SCALE)) },
			{ "btb", new BonusTileData(BonusType::COPPER_COIN, 1.f, b2Vec2(0.f, -64.f / B2SCALE)) },
			{ "btc", new BonusTileData(BonusType::SILVER_COIN, 1.f, b2Vec2(0.f, -64.f / B2SCALE)) },
			{ "btd", new BonusTileData(BonusType::GOLD_COIN, 1.f, b2Vec2(0.f, -64.f / B2SCALE)) },
			{ "kt0", new BreakableTileData() },
			{ "kt1", new BreakableTileData("bta") },
			{ "kt2", new BreakableTileData("btb") },
			{ "kt3", new BreakableTileData("btc") },
			{ "kt4", new BreakableTileData("btd") },
			{ "ht", new HelperTileData() },
			{ "dt0", new DoorTileData(Screen::GAME) },
			{ "dt1", new DoorTileData(Screen::CREDITS) },
			{ "tc0", new CheckpointTileData() },
			{ "ef0", new ElementalTileData(ElementalType::FIRE) },
			{ "ef1", new ElementalTileData(ElementalType::FIRE, true, 5.f) },
			{ "ef", new ElementalTileData(ElementalType::FIRE) },
			{ "tt0", new TimedTileData() },
			{ "tt1", new TimedTileData(2.f, true, 5.f) },
			{ "tt", new TimedTileData() },
			{ "m00", new GameChickenData(ElementalType::DEFAULT) },
			{ "m01", new GameChickenData(ElementalType::FIRE)},
			{ "m10", new GameSnakeData(ElementalType::DEFAULT) },
			{ "m11", new GameSnakeData(ElementalType::FIRE) },
			{ "m20", new GameRatData(ElementalType::DEFAULT) },
			{ "ma0", new AnimationRatData(ElementalType::DEFAULT) },
			{ "b00", new GameChickenBossData() },
			{ "mp0", new ChickenBossProjectileData() },
			{ "topDialog", new DialogData(DialogSide::TOP) },
			{ "bottomDialog", new DialogData(DialogSide::BOTTOM) },
			{ "fullDialog", new DialogData(DialogSide::FULL) },
			{ "fadeInRTransition", new RectangleTransitionData(TransitionType::FADE_IN) },
			{ "fadeOutRTransition", new RectangleTransitionData(TransitionType::FADE_OUT) },
			{ "fixLayer", new FixLayerData() }
		};

		m_complexDataRegistrar["c00"] = std::list<std::string>{
			"t22",
			"m00"
		};
		m_complexDataRegistrar["c01"] = std::list<std::string>{
			"t22",
			"m10"
		};
		m_complexDataRegistrar["c05"] = std::list<std::string>{
			"t22",
			"bt0"
		};
		m_complexDataRegistrar["c06"] = std::list<std::string>{
			"t22",
			"bt1"
		};
		m_complexDataRegistrar["c07"] = std::list<std::string>{
			"t22",
			"bt2"
		};
		m_complexDataRegistrar["c08"] = std::list<std::string>{
			"t22",
			"bt3"
		};
		m_complexDataRegistrar["c10"] = std::list<std::string>{
			"t27",
			"m00"
		};
		m_complexDataRegistrar["c11"] = std::list<std::string>{
			"t27",
			"m10"
		};
		m_complexDataRegistrar["c15"] = std::list<std::string>{
			"t27",
			"bt0"
		};
		m_complexDataRegistrar["c16"] = std::list<std::string>{
			"t27",
			"bt1"
		};
		m_complexDataRegistrar["c17"] = std::list<std::string>{
			"t27",
			"bt2"
		};
		m_complexDataRegistrar["c18"] = std::list<std::string>{
			"t27",
			"bt3"
		};
	}

	std::map<std::string, AbstractEntityData*> getDataRegistrar() const
	{
		return m_dataRegistrar;
	}


	std::map<std::string, std::list<std::string>> getComplexDataRegistrar() const
	{
		return m_complexDataRegistrar;
	}

private:
	std::map<std::string, AbstractEntityData*> m_dataRegistrar;
	std::map<std::string, std::list<std::string>> m_complexDataRegistrar;
};