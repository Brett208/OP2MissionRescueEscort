#include <vector>

#include <Outpost2DLL/Outpost2DLL.h>
#include <OP2Helper/OP2Helper.h>

#include "UnitHelper.h"
#include "VehicleCounter.h"

// Required data exports  (Description, Map, TechTree, GameType, NumPlayers)
ExportLevelDetailsEx("Campaign - Ply, Pursued, Ep 3, 'Rescue Escort'", "RescueEscort.map", "MULTITEK.TXT", MissionTypes::Colony, 3, 12, true);
//Original map: ply07.map

extern void ShowBriefing();

UnitHelper::VehicleBuilder vehicleBuilderAI;
UnitHelper::VehicleCounter vehicleCounter;

void CreateAcidCloudFightGroup();

void CreateTimeVictoryCondition(Trigger& trigger, Trigger& victoryTrigger, int time, char* missionObjective)
{
	trigger = CreateTimeTrigger(false, false, time, "NoResponseToTrigger");
	victoryTrigger = CreateVictoryCondition(true, false, trigger, missionObjective);
}

struct ScriptGlobal
{
	Trigger TrigVictoryWaitTime;
	Trigger TrigFailureWaitTime;

	int MinConvoySurvivingUnits;
	int MinEvacuationTransports;

	Trigger TrigFightGroup1;
	Trigger TrigFightGroup2;
	Trigger TrigFightGroup3;
	Trigger TrigFinalfightGroup;

	FightGroup AcidCloudSneakFightGroup;
	FightGroup FightGroup1;
	FightGroup FightGroup2;
	FightGroup FightGroup3;
	FightGroup FinalFightGroup;

} scriptGlobal;
ExportSaveLoadData(scriptGlobal);

void InitializeRescueConvoy()
{
	std::vector<Unit> units;

	vehicleBuilderAI.SetPlayer(Player0);
	vehicleBuilderAI.SetVehicleDirection(UnitDirection::East);

	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(8 + X_, 5 + Y_), UnitDirection::South, 2, map_id::mapLynx, map_id::mapMicrowave, 4);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(6 + X_, 5 + Y_), UnitDirection::South, 2, map_id::mapLynx, map_id::mapStickyfoam, 4);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(6 + X_, 5 + Y_), UnitDirection::South, 2, map_id::mapLynx, map_id::mapRPG, 4);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(6 + X_, 5 + Y_), UnitDirection::South, 2, map_id::mapLynx, map_id::mapEMP, 4);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(6 + X_, 5 + Y_), UnitDirection::South, 2, map_id::mapLynx, map_id::mapESG, 4);

	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(8 + X_, 5 + Y_), UnitDirection::South, 2, map_id::mapPanther, map_id::mapMicrowave, 3);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(6 + X_, 5 + Y_), UnitDirection::South, 2, map_id::mapPanther, map_id::mapStickyfoam, 3);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(6 + X_, 5 + Y_), UnitDirection::South, 2, map_id::mapPanther, map_id::mapRPG, 3);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(6 + X_, 5 + Y_), UnitDirection::South, 2, map_id::mapPanther, map_id::mapEMP, 3);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(6 + X_, 5 + Y_), UnitDirection::South, 2, map_id::mapPanther, map_id::mapESG, 3);

	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(5 + X_, 5 + Y_), UnitDirection::South, 2, map_id::mapSpider, map_id::mapNone, 3);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(5 + X_, 5 + Y_), UnitDirection::South, 2, map_id::mapSpider, map_id::mapNone, 3);

	Unit unit;
	vehicleBuilderAI.CreateVechLightsOn(unit, map_id::mapScout, LOCATION(5 + X_, 5 + Y_), map_id::mapNone);
	vehicleBuilderAI.CreateVechLightsOn(unit, map_id::mapScout, LOCATION(5 + X_, 5 + Y_), map_id::mapNone);
}

int InitializeEvacuationConvoy()
{
	std::vector<Unit> units;

	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.SetVehicleDirection(UnitDirection::West);

	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(120 + X_, 5 + Y_), UnitDirection::South, 2, map_id::mapLynx, map_id::mapMicrowave, 3);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(120 + X_, 5 + Y_), UnitDirection::South, 2, map_id::mapLynx, map_id::mapRPG, 3);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(120 + X_, 5 + Y_), UnitDirection::South, 2, map_id::mapLynx, map_id::mapESG, 3);

	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(120 + X_, 5 + Y_), UnitDirection::South, 2, map_id::mapPanther, map_id::mapMicrowave, 3);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(120 + X_, 5 + Y_), UnitDirection::South, 2, map_id::mapPanther, map_id::mapRPG, 3);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(120 + X_, 5 + Y_), UnitDirection::South, 2, map_id::mapPanther, map_id::mapESG, 3);

	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(120 + X_, 5 + Y_), UnitDirection::South, 2, map_id::mapEvacuationTransport, map_id::mapNone, 3);

	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(120 + X_, 5 + Y_), UnitDirection::South, 2, std::vector<map_id>{ map_id::mapRoboMiner, map_id::mapRoboMiner, map_id::mapRoboDozer, map_id::mapRoboSurveyor, map_id::mapRoboSurveyor, map_id::mapConVec, map_id::mapConVec, map_id::mapConVec, map_id::mapConVec, map_id::mapConVec, map_id::mapConVec, map_id::mapScout, map_id::mapSpider, map_id::mapSpider, map_id::mapEarthworker });

	vehicleBuilderAI.MoveRelativeAmount(units, LOCATION(-20, 0));

	return units.size();
}

bool IsScenarioLost()
{
	vehicleCounter.Clear();
	vehicleCounter.PullVehiclesFromPlayer(PlayerUnitEnum(Player2));

	if (vehicleCounter.GetCombatVehicleCount() < scriptGlobal.MinConvoySurvivingUnits)
	{
		return true;
	}

	if (vehicleCounter.GetVehicleCount(map_id::mapEvacuationTransport) < scriptGlobal.MinEvacuationTransports)
	{
		return true;
	}

	return false;
}

bool IsScenarioWon()
{
	vehicleCounter.Clear();
	vehicleCounter.PullVehiclesFromPlayer(PlayerUnitEnum(Player2));
	int convoyVehicleCount = vehicleCounter.GetCombatVehicleCount();


	vehicleCounter.Clear();
	MAP_RECT convoyFinishRect(LOCATION(X_, Y_), LOCATION(X_, Y_));
	vehicleCounter.PullVehiclesFromRectangle(Player2, InRectEnumerator(convoyFinishRect));

	//Check if all remaining convoy vehicles have made it to the objective area.
	return vehicleCounter.GetVehicleCount() == convoyVehicleCount;
}

char* FormatVictoryConditionMessage(PlayerDifficulty playerDifficulty)
{
	switch (playerDifficulty)
	{
	case PlayerDifficulty::DiffEasy:
		return "Extract at least 2 evacuation transports and 50% of starting convoy units. Leave no functioning convoy unit behind.";
	case PlayerDifficulty::DiffNormal:
		return "Extract at least 3 evacuation transports and 70% of starting convoy units. Leave no functioning convoy unit behind.";
	default:
		return "Extract all evacuation transports and 80% of starting convoy units. Leave no functioning convoy unit behind.";
	}
}

void SetVictoryConvoyCounts(PlayerDifficulty playerDifficulty, int initialConvoyVehicleCount)
{
	switch (playerDifficulty)
	{
	case PlayerDifficulty::DiffEasy:
		scriptGlobal.MinConvoySurvivingUnits = (int)(initialConvoyVehicleCount * 0.5);
		scriptGlobal.MinEvacuationTransports = 2;
		return;
	case PlayerDifficulty::DiffNormal:
		scriptGlobal.MinConvoySurvivingUnits = (int)(initialConvoyVehicleCount * 0.7);
		scriptGlobal.MinEvacuationTransports = 3;
		return;
	default:
		scriptGlobal.MinConvoySurvivingUnits = (int)(initialConvoyVehicleCount * 0.8);
		scriptGlobal.MinEvacuationTransports = 4;
		return;
	}
}

Export int InitProc()
{
	HFLInit();

	ShowBriefing();

	TethysGame::SetDaylightEverywhere(false);
	TethysGame::SetDaylightMoves(false);
	GameMap::SetInitialLightLevel(-1);

	Player[0].CenterViewOn(113 + X_, 69 + Y_);

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

	InitializeRescueConvoy();

	int initialConvyVehicleCount = InitializeEvacuationConvoy();

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

	return true;	// Level loaded successfully
}

bool scenarioInitialized;
Export void AIProc() 
{
	if (!scenarioInitialized)
	{
		scenarioInitialized = true;
		TethysGame::SetEarthquake(5 + X_, 5 + Y_, 4);
	}

	if (IsScenarioLost())
	{
		scriptGlobal.TrigFailureWaitTime.Enable();
	}
}

void CreateFightGroup1()
{
	std::vector<Unit> units;
	PlayerDifficulty difficulty = (PlayerDifficulty)Player[Player0].Difficulty();

	vehicleBuilderAI.SetPlayer(Player1);
	vehicleBuilderAI.SetVehicleDirection(UnitDirection::South);

	std::vector<map_id> turrets{ map_id::mapLaser, map_id::mapRailGun, map_id::mapEMP, map_id::mapThorsHammer };

	if (difficulty == PlayerDifficulty::DiffNormal || difficulty == PlayerDifficulty::DiffHard)
	{
		turrets.push_back(map_id::mapLaser);
	}

	if (difficulty == PlayerDifficulty::DiffHard)
	{
		turrets.push_back(map_id::mapAcidCloud);
	}

	turrets = { map_id::mapLaser, map_id::mapRailGun, map_id::mapEMP, map_id::mapThorsHammer };

	if (difficulty == PlayerDifficulty::DiffNormal || difficulty == PlayerDifficulty::DiffHard)
	{
		turrets.push_back(map_id::mapRailGun);
	}

	if (difficulty == PlayerDifficulty::DiffHard)
	{
		turrets.push_back(map_id::mapAcidCloud);
	}

	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(1 + X_, 1 + Y_), UnitDirection::East, 1, map_id::mapLynx, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FightGroup1, units);

	scriptGlobal.TrigFightGroup1.Destroy();
}

void CreateFightGroup2()
{
	std::vector<Unit> units;

	std::vector<map_id> turrets{ map_id::mapStickyfoam, map_id::mapMicrowave, map_id::mapMicrowave,
		map_id::mapRPG, map_id::mapEMP, map_id::mapEMP, map_id::mapStickyfoam };

	if (Player[0].Difficulty() == PlayerDifficulty::DiffHard)
	{
		turrets.push_back(map_id::mapESG);
		turrets.push_back(map_id::mapESG);
		turrets.push_back(map_id::mapEMP);
	}

	vehicleBuilderAI.SetPlayer(Player1);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(1 + X_, 1 + Y_), UnitDirection::East, 1, map_id::mapPanther, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FightGroup2, units);

	scriptGlobal.TrigFightGroup2.Destroy();
}

void CreateFightGroup3()
{
	std::vector<Unit> units;

	std::vector<map_id> turrets{ map_id::mapStickyfoam, map_id::mapMicrowave, map_id::mapMicrowave,
		map_id::mapRPG, map_id::mapEMP, map_id::mapEMP, map_id::mapStickyfoam };

	if (Player[0].Difficulty() == PlayerDifficulty::DiffHard)
	{
		turrets.push_back(map_id::mapESG);
		turrets.push_back(map_id::mapESG);
		turrets.push_back(map_id::mapEMP);
	}

	vehicleBuilderAI.SetPlayer(Player1);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(1 + X_, 1 + Y_), UnitDirection::East, 1, map_id::mapPanther, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FightGroup3, units);

	scriptGlobal.TrigFightGroup3.Destroy();
}

void CreateAcidCloudFightGroup()
{
	std::vector<Unit> units;
	
	vehicleBuilderAI.SetPlayer(Player1);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(1 + X_, 1 + Y_), UnitDirection::East, 2, map_id::mapLynx, map_id::mapAcidCloud, 2);
	
	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.AcidCloudSneakFightGroup, units);
	//scriptGlobal.AcidCloudSneakFightGroup.DoPatrolOnly();
}

void CreateFinalFightGroup()
{
	std::vector<Unit> units;
	PlayerDifficulty difficulty = (PlayerDifficulty)Player[Player0].Difficulty();

	std::vector<map_id> turrets{ map_id::mapLaser, map_id::mapRailGun, map_id::mapEMP, 
		map_id::mapThorsHammer, map_id::mapAcidCloud, map_id::mapThorsHammer };

	if (difficulty == PlayerDifficulty::DiffNormal || difficulty == PlayerDifficulty::DiffHard)
	{
		turrets.push_back(map_id::mapEMP);
	}

	if (difficulty == PlayerDifficulty::DiffHard)
	{
		turrets.push_back(map_id::mapAcidCloud);
	}



	turrets = { map_id::mapLaser, map_id::mapRailGun, map_id::mapEMP, map_id::mapThorsHammer };

	if (difficulty == PlayerDifficulty::DiffNormal || difficulty == PlayerDifficulty::DiffHard)
	{
		turrets.push_back(map_id::mapRailGun);
	}

	if (difficulty == PlayerDifficulty::DiffHard)
	{
		turrets.push_back(map_id::mapAcidCloud);
	}

	vehicleBuilderAI.SetPlayer(Player1);
	vehicleBuilderAI.SetVehicleDirection(UnitDirection::West);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(1 + X_, 1 + Y_), UnitDirection::South, 1, map_id::mapLynx, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FinalFightGroup, units);

	scriptGlobal.FinalFightGroup.Destroy();
}

Export void NoResponseToTrigger() {}	// Optional function export, supposed to be empty
