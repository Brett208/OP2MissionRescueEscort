#pragma once

#include "EnemyFightGroups.h"
#include "StartingConvoys.h"
#include "VictoryDefeatConditions.h"
#include "DisasterHelper.h"
#include "ScriptGlobal.h"
#include "Outpost2DLL\Outpost2DLL.h"
#include <vector>
#include <array>

void SetMultipleResearchedTechs(int playerNumb, std::vector<int> completedResearch);
void SetResearchedTech();
Export void CreateDisaster();

ScriptGlobal scriptGlobal;
ExportSaveLoadData(scriptGlobal);
DisasterHelper disasterHelper;

// List of songs to play
SongIds PlayList[] = {
	SongIds::songEP62,
	SongIds::songEP63
};

std::vector<LOCATION> waypointLocs = { 
	LOCATION(201 + X_, 29 + Y_), LOCATION(184 + X_, 15 + Y_), LOCATION(145 + X_, 59 + Y_), 
	LOCATION(110 + X_, 57 + Y_), LOCATION(96 + X_, 7 + Y_), LOCATION(65 + X_, 11 + Y_), 
	LOCATION(41 + X_, 50 + Y_), LOCATION(19 + X_, 40 + Y_), LOCATION(10 + X_, 5 + Y_) };
int waypointMoveCheckTickInterval = 30;

void InitializeScenario(bool multiplayer)
{
	scriptGlobal.Multiplayer = multiplayer;

	TethysGame::SetDaylightEverywhere(false);
	TethysGame::SetDaylightMoves(false);
	GameMap::SetInitialLightLevel(-1);

	Player[0].CenterViewOn(167 + X_, 3 + Y_);

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

	if (TethysGame::CanHaveDisasters())
	{ 
		scriptGlobal.DisasterTimeTrig = CreateTimeTrigger(true, false, 1500, 3500, "CreateDisaster"); //Set time in ticks (marks / 100)
	}

	SetResearchedTech();

	InitializeRescueConvoy(vehicleBuilderAI);

	InitializeEvacuationConvoy(multiplayer, vehicleBuilderAI);

	vehicleCounter.Clear();
	vehicleCounter.PullVehiclesFromPlayer(Player1);
	int evacConvoyNonCombatVehicleCount = vehicleCounter.GetNonCombatVehicleCount();

	InitializeVictoryConditions(evacConvoyNonCombatVehicleCount);

	scriptGlobal.TrigChaseFightGroup = CreateTimeTrigger(true, true, 1800 + TethysGame::GetRand(200), "CreateFinalFightGroup");
	scriptGlobal.TrigFightGroupSE = CreateTimeTrigger(true, true, 1200 + TethysGame::GetRand(200), "CreateFightGroupSE");
	scriptGlobal.TrigFightGroupNE = CreateTimeTrigger(true, true, 1600 + TethysGame::GetRand(200), "CreateFightGroupNE");
	
	
	scriptGlobal.TrigFightGroupS = CreateTimeTrigger(true, true, 3500 + TethysGame::GetRand(200), "CreateFightGroupS");
	//South2: 5000
	scriptGlobal.TrigFightGroupN = CreateTimeTrigger(true, true, 8000 + TethysGame::GetRand(200), "CreateFightGroupN");
	scriptGlobal.TrigFightGroupNW = CreateTimeTrigger(true, true, 9000 + TethysGame::GetRand(200), "CreateFightGroupNW");
	//NW2: 10000
	scriptGlobal.TrigFightGroupSW = CreateTimeTrigger(true, true, 12000 + TethysGame::GetRand(200), "CreateFightGroupSW");
	//W: 13500
	

	InitializeStartingEnemyUnits(vehicleBuilderAI);

	TethysGame::SetMusicPlayList(2, 0, PlayList);

	
	if (multiplayer)
	{
		scriptGlobal.CurrentWaypointIndex = waypointLocs.size() - 1;
	}
	else
	{
		scriptGlobal.CurrentWaypointIndex = 0;
	}

	Unit marker;
	LOCATION loc = waypointLocs[scriptGlobal.CurrentWaypointIndex];
	TethysGame::PlaceMarker(marker, loc.x, loc.y, MarkerTypes::Circle);
}

MAP_RECT GetRectCenteredOnLoc(const LOCATION& loc, int width, int height)
{
	return MAP_RECT(loc.x - width / 2, loc.y - height / 2, loc.x + width / 2, loc.y + height / 2);
}

MAP_RECT GetRectCenteredOnLoc(const LOCATION& loc, int rectSize)
{
	return GetRectCenteredOnLoc(loc, rectSize, rectSize);
}

bool NextWaypointReached()
{
	LOCATION loc = waypointLocs[scriptGlobal.CurrentWaypointIndex];

	vehicleCounter.Clear();
	vehicleCounter.PullVehiclesFromPlayer(PlayerUnitEnum(Player1));
	int numberOfUnits = vehicleCounter.GetVehicleCount();

	vehicleCounter.Clear();
	vehicleCounter.PullVehiclesFromRectangle(Player1, InRectEnumerator(GetRectCenteredOnLoc(loc, 18)));
	int numberOfUnitsAtWaypoint = vehicleCounter.GetVehicleCount();

	return numberOfUnits > 0 && numberOfUnits == numberOfUnitsAtWaypoint;
}

bool ReachedFinalWaypoint()
{
	return (int)waypointLocs.size() == scriptGlobal.CurrentWaypointIndex;
}

void TransitionNextWaypoint()
{
	scriptGlobal.CurrentWaypointIndex++;

	if (ReachedFinalWaypoint())
	{
		return;
	}

	Unit unit;
	LOCATION loc = waypointLocs[scriptGlobal.CurrentWaypointIndex];
	TethysGame::PlaceMarker(unit, loc.x, loc.y, MarkerTypes::Circle);
}

void MoveConvoyToCurrentWaypoint()
{
	LOCATION loc = waypointLocs[scriptGlobal.CurrentWaypointIndex];

	PlayerVehicleEnum playerVechicleEnum(Player1);

	MAP_RECT mapRect = GetRectCenteredOnLoc(loc, 12);

	Unit unit;
	while (playerVechicleEnum.GetNext(unit))
	{
		if (mapRect.Check(unit.Location()))
		{
			continue;
		}

		unit.DoMove(waypointLocs[scriptGlobal.CurrentWaypointIndex]);
	}
}

void ForcePatrolsToCounterAttack()
{
	if (scriptGlobal.LynxPatrolFightGroup.HasBeenAttacked())
	{
		scriptGlobal.LynxPatrolFightGroup.DoAttackEnemy();
	}
	if (scriptGlobal.FirstPatrolFightGroup.HasBeenAttacked())
	{
		scriptGlobal.FirstPatrolFightGroup.DoAttackEnemy();
	}
}

Export void AIProc()
{
	if (IsScenarioLost())
	{
		scriptGlobal.TrigFailureWaitTime.Enable();
	}
	else if (TethysGame::Tick() > scriptGlobal.LastTickMoveWaypointSet + waypointMoveCheckTickInterval)
	{
		if (ReachedFinalWaypoint())
		{
			scriptGlobal.TrigVictoryWaitTime.Enable();
			return;
		}

		if (NextWaypointReached())
		{
			TransitionNextWaypoint();
		}

		scriptGlobal.LastTickMoveWaypointSet = TethysGame::Tick();

		if (!ReachedFinalWaypoint())
		{
			MoveConvoyToCurrentWaypoint();
		}
	}
	else
	{
		ForcePatrolsToCounterAttack();
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
		10303, // Advanced Armoring Systems

		7212, //Extended Range Projectile Launcher
		10306 //Grenade Loading Mechanism
	};

	if (Player[0].Difficulty() == PlayerDifficulty::DiffEasy)
	{
		//researchedTech.push_back(8320); //Reduced Foam Evaporation	
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