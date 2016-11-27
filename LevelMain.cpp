#include <vector>

#include <Outpost2DLL/Outpost2DLL.h>
#include <OP2Helper/OP2Helper.h>

#include "VictoryDefeatConditions.h"
#include "EnemyFightGroups.h"
#include "StartingConvoys.h"
#include "ScriptGlobal.h"
#include "UnitHelper.h"
#include "DisasterHelper.h"


// Required data exports  (Description, Map, TechTree, GameType, NumPlayers)
ExportLevelDetailsEx("Campaign - Ply, Pursued, Ep 3, 'Rescue Escort'", "RescueEscort.map", "MULTITEK.TXT", MissionTypes::Colony, 3, 12, true);
//Original map: ply07.map

extern void ShowBriefing();

DisasterHelper disasterHelper;

void CreateAcidCloudFightGroup();

ScriptGlobal scriptGlobal;
ExportSaveLoadData(scriptGlobal);

Export int InitProc()
{
	HFLInit();

	ShowBriefing();

	//NOTE: Sets mapWidth as 512 instead of 256. MapWidth appears to be set correctly.
	//disasterHelper.SetMapProperties(GameMapEx::GetMapWidth(), GameMapEx::GetMapHeight(), false);
	disasterHelper.SetMapProperties(256, 64, false);

	TethysGame::SetDaylightEverywhere(false);
	TethysGame::SetDaylightMoves(false);
	GameMap::SetInitialLightLevel(-1);

	Player[0].CenterViewOn(30 + X_, 0 + Y_);

	Player[Player0].GoPlymouth();
	Player[Player0].SetColorNumber(PlayerColor::PlayerRed);
	Player[Player0].GoHuman();
	Player[Player0].SetKids(0);
	Player[Player0].SetWorkers(0);
	Player[Player0].SetScientists(0);
	Player[Player0].SetFoodStored(0);
	TethysGame::ForceMoraleGood(Player0);
	TethysGame::ForceMoraleGood(Player0);

	Player[Player1].GoEden();
	Player[Player1].SetColorNumber(PlayerColor::PlayerBlue);
	Player[Player1].GoAI();
	TethysGame::ForceMoraleGood(Player1);

	Player[Player2].GoPlymouth();
	Player[Player2].SetColorNumber(PlayerColor::PlayerGreen);
	Player[Player2].GoAI();
	TethysGame::ForceMoraleGood(Player2);

	Player[Player0].AllyWith(Player2);
	Player[Player2].AllyWith(Player0);

	Unit marker;
	TethysGame::PlaceMarker(marker, 6 + X_, 6 + Y_, MarkerTypes::Circle);

	InitializeRescueConvoy(vehicleBuilderAI);

	int initialConvyVehicleCount = InitializeEvacuationConvoy(vehicleBuilderAI);

	vehicleBuilderAI.SetPlayer(Player1);
	vehicleBuilderAI.SetVehicleDirection(UnitDirection::South);

	std::vector<Unit> units;
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(80 + X_, 5 + Y_), UnitDirection::South, 2, map_id::mapLynx, map_id::mapLaser, 3);

	vehicleBuilderAI.MoveRelativeAmount(units, LOCATION(0, -10));
	
	Trigger victoryTrigger;

	PlayerDifficulty playerDifficulty = (PlayerDifficulty)Player[Player0].Difficulty();
	SetVictoryConvoyCounts(playerDifficulty, initialConvyVehicleCount);
	char* victoryConditionText = FormatVictoryConditionMessage(playerDifficulty);
	CreateTimeVictoryCondition(scriptGlobal.TrigVictoryWaitTime, victoryTrigger, 90, victoryConditionText);

	scriptGlobal.TrigFailureWaitTime = CreateTimeTrigger(false, false, 90, "NoResponseToTrigger");
	CreateFailureCondition(true, true, scriptGlobal.TrigFailureWaitTime, "Ignored");

	CreateAcidCloudFightGroup();

	scriptGlobal.TrigFightGroup1 = CreateTimeTrigger(true, true, 20 + TethysGame::GetRand(5), "CreateFightGroup1");
	scriptGlobal.TrigFightGroup2 = CreateTimeTrigger(true, true, 20 + TethysGame::GetRand(5), "CreateFightGroup2");
	scriptGlobal.TrigFightGroup3 = CreateTimeTrigger(true, true, 20 + TethysGame::GetRand(5), "CreateFightGroup3");

	scriptGlobal.TrigFinalfightGroup = CreateTimeTrigger(true, true, 300 + TethysGame::GetRand(20), "CreateFinalFightGroup");


	//TethysGame::SetLightning(1 + X_, 1 + Y_, 40, 15 + X_, 15 + Y_);

	TethysGame::SetEarthquake(100 + X_, 7 + Y_, 1);

	TethysGame::SetTornado(1 + X_, 1 + Y_, 0, 15 + X_, 15 + Y_, true);

	//Unit unit;
	//TethysGame::CreateUnit(unit, map_id::mapCommandCenter, LOCATION(4 + X_, 5 + Y_), Player0, map_id::mapNone, 0);
	//TethysGame::CreateUnit(unit, map_id::mapCommandCenter, LOCATION(8 + X_, 5 + Y_), Player0, map_id::mapNone, 0);
	//TethysGame::CreateUnit(unit, map_id::mapCommandCenter, LOCATION(10 + X_, 8 + Y_), Player0, map_id::mapNone, 0);
	//TethysGame::CreateUnit(unit, map_id::mapCommandCenter, LOCATION(17 + X_, 7 + Y_), Player0, map_id::mapNone, 0);

	std::vector<LOCATION> locs = disasterHelper.GetLocationsOnLine(LOCATION(21 + X_, 1 + Y_), LOCATION(25 + X_, 20 + Y_));

	Unit unit;
	for (auto& loc : locs)
	{
		vehicleBuilderAI.CreateVechLightsOn(unit, map_id::mapRoboDozer, loc, map_id::mapNone);
	}

	disasterHelper.AddSafeRect(MAP_RECT(1 + X_, 1 + Y_, 256 + X_, 64 + Y_));

	disasterHelper.CreateVortex();

	return true;	// Level loaded successfully
}

Export void AIProc() 
{
	if (IsScenarioLost())
	{
		//scriptGlobal.TrigFailureWaitTime.Enable();
	}
}

Export void NoResponseToTrigger() {}	// Optional function export, supposed to be empty
