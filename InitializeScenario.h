#pragma once

#include "EnemyFightGroups.h"
#include "StartingConvoys.h"
#include "VictoryDefeatConditions.h"
#include "DisasterHelper.h"
#include "ScriptGlobal.h"
#include "Outpost2DLL\Outpost2DLL.h"
#include <vector>

void SetMultipleResearchedTechs(int playerNumb, std::vector<int> completedResearch);
void SetResearchedTech();
Export void CreateDisaster();

ScriptGlobal scriptGlobal;
ExportSaveLoadData(scriptGlobal);
DisasterHelper disasterHelper;

void InitializeScenario(bool multiplayer)
{
	TethysGame::SetDaylightEverywhere(false);
	TethysGame::SetDaylightMoves(false);
	GameMap::SetInitialLightLevel(-1);

	Player[0].CenterViewOn(30 + X_, 0 + Y_);

	if (multiplayer)
	{
		Player[1].CenterViewOn(256 + X_, 25 + Y_);
	}

	Player[Player0].GoPlymouth();

	if (!multiplayer)
	{
		Player[Player0].SetColorNumber(PlayerColor::PlayerRed);
	}

	Player[Player0].GoHuman();
	Player[Player0].SetKids(0);
	Player[Player0].SetWorkers(0);
	Player[Player0].SetScientists(0);
	Player[Player0].SetFoodStored(0);
	TethysGame::ForceMoraleGood(Player0);
	TethysGame::ForceMoraleGood(Player0);

	Player[Player1].GoPlymouth();

	TethysGame::ForceMoraleGood(Player1);
	TethysGame::ForceMoraleGood(Player1);
	if (multiplayer)
	{
		Player[Player1].GoHuman();
	}
	else
	{
		Player[Player1].SetColorNumber(PlayerColor::PlayerGreen);
		Player[Player1].GoAI();
	}

	Player[Player2].GoEden();
	if (!multiplayer)
	{
		Player[Player2].SetColorNumber(PlayerColor::PlayerBlue);
	}
	
	Player[Player2].GoAI();
	TethysGame::ForceMoraleGood(Player2);
	TethysGame::ForceMoraleGood(Player2);
	
	Player[Player0].AllyWith(Player1);
	Player[Player1].AllyWith(Player0);

	scriptGlobal.DisasterTimeTrig = CreateTimeTrigger(true, false, 1500, 3500, "CreateDisaster"); //Set time in ticks (marks / 100)

	SetResearchedTech();

	Unit marker;
	TethysGame::PlaceMarker(marker, 6 + X_, 6 + Y_, MarkerTypes::Circle);

	InitializeRescueConvoy(vehicleBuilderAI);

	InitializeEvacuationConvoy(multiplayer, vehicleBuilderAI);

	vehicleCounter.Clear();
	vehicleCounter.PullVehiclesFromPlayer(Player1);
	int evacConvoyNonCombatVehicleCount = vehicleCounter.GetNonCombatVehicleCount();

	InitializeVictoryConditions(evacConvoyNonCombatVehicleCount);

	CreateAcidCloudFightGroup();

	scriptGlobal.TrigFightGroup1 = CreateTimeTrigger(true, true, 20 + TethysGame::GetRand(5), "CreateFightGroup1");
	scriptGlobal.TrigFightGroup2 = CreateTimeTrigger(true, true, 20 + TethysGame::GetRand(5), "CreateFightGroup2");
	scriptGlobal.TrigFightGroup3 = CreateTimeTrigger(true, true, 20 + TethysGame::GetRand(5), "CreateFightGroup3");

	scriptGlobal.TrigFinalfightGroup = CreateTimeTrigger(true, true, 300 + TethysGame::GetRand(20), "CreateFinalFightGroup");

	InitializeStartingEnemyUnits(vehicleBuilderAI);
}

Export void AIProc()
{
	if (IsScenarioLost())
	{
		scriptGlobal.TrigFailureWaitTime.Enable();
	}
}

void SetMultipleResearchedTechs(int playerNumb, std::vector<int> completedResearch)
{
	for (int techID : completedResearch)
	{
		Player[0].MarkResearchComplete(techID);
	}
}

void SetResearchedTech()
{
	std::vector<int> researchedTech{
		//05052, // Garage
		2701, 2702, 2703, 2704, 2705,
		2706, // Cryptology
		2707, // Vehicle Encryption Patch
		3401, // Cybernetic Teleoperation
		3406, 3301, 3408, 7206, 7103, 8307, 5305,
		3303, 3402, 3405, 3302, 3304, 3305, 3201, 3202, 3901, 3306, 3851, 5110, 5201, 5202, 5111, 5317, 5508, 5116, 5599, 5307,
		7102, // Explosive Charges
		8203, // High-Powered Explosives
		8306, // Enhanced Defensive Fortifications
		8309, // Reinforced Panther Construction
		10303 // Advanced Armoring Systems
	};


	if (Player[0].Difficulty() == PlayerDifficulty::DiffEasy)
	{
		researchedTech.push_back(7212); //Extended Range Projectile Launcher
		researchedTech.push_back(8320); //Reduced Foam Evaporation
		researchedTech.push_back(10306); //Grenade Loading Mechanism
	}

	SetMultipleResearchedTechs(0, researchedTech);
}

Export void CreateDisaster()
{
	if (!disasterHelper.MapPropertiesSet())
	{
		disasterHelper.SetMapProperties(256, 64, false); //MapWidth, MapHeight, Does map wrap East/West
	}

	disasterHelper.CreateRandomDisaster();
}

Export void NoResponseToTrigger() {}