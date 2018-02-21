#pragma once

#include "EnemyFightGroups.h"
#include "StartingConvoys.h"
#include "VictoryDefeatConditions.h"
#include "DisasterHelper.h"
#include "Technology.h"
#include "ScriptGlobal.h"
#include "Outpost2DLL\Outpost2DLL.h"
#include <vector>
#include <array>

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
	LOCATION(201 + X_, 29 + Y_), LOCATION(172 + X_, 21 + Y_), LOCATION(145 + X_, 57 + Y_), 
	LOCATION(117 + X_, 55 + Y_), LOCATION(95 + X_, 10 + Y_), LOCATION(61 + X_, 14 + Y_), 
	LOCATION(37 + X_, 48 + Y_), LOCATION(24 + X_, 44 + Y_), LOCATION(10 + X_, 5 + Y_) };
int waypointMoveCheckTickInterval = 30;

//Note: Scenario must have 5 or fewer human players to work.
PlayerColor GetAIColor(bool allowBlack = false)
{
	int totalColors = 6;
	if (allowBlack) {
		totalColors++;
	}

	std::vector<int> availableColors;
	for (int i = 0; i < totalColors; ++i)
	{
		availableColors.push_back(ExtPlayer[i].GetColorNumber());
	}

	for (int i = 0; i < TethysGame::NoPlayers() - 1; ++i)
	{
		availableColors.erase(
			std::remove(availableColors.begin(), availableColors.end(), ExtPlayer[i].GetColorNumber()), availableColors.end());
	}
	
	if (availableColors.size() == 0) {
		return PlayerColor::PlayerBlue;
	}

	int colorIndex = TethysGame::GetRand(availableColors.size());

	return (PlayerColor)availableColors[colorIndex];
}

void InitializeSurpriseAttackTriggers()
{
	//W: 13500
	int numberOfPossibleSurpriseAttacks = 6;

	int indexToSkip = TethysGame::GetRand(numberOfPossibleSurpriseAttacks);

	for (int i = 0; i < numberOfPossibleSurpriseAttacks; ++i)
	{
		switch (i)
		{
		case 0:
			scriptGlobal.TrigFightGroupSE = CreateTimeTrigger(true, true, 1200 + TethysGame::GetRand(200), "CreateFightGroupSE");
			break;
		case 1:
			scriptGlobal.TrigFightGroupNE = CreateTimeTrigger(true, true, 1400 + TethysGame::GetRand(200), "CreateFightGroupNE");
			break;
		case 2:
			if (TethysGame::GetRand(2) == 0)
				scriptGlobal.TrigFightGroupS = CreateTimeTrigger(true, true, 3500 + TethysGame::GetRand(200), "CreateFightGroupS");
			else
				scriptGlobal.TrigFightGroupS2 = CreateTimeTrigger(true, true, 5000 + TethysGame::GetRand(200), "CreateFightGroupS2");
			break;
		case 3:
			scriptGlobal.TrigFightGroupN = CreateTimeTrigger(true, true, 8000 + TethysGame::GetRand(200), "CreateFightGroupN");
			break;
		case 4:
			if (TethysGame::GetRand(2) == 0)
				scriptGlobal.TrigFightGroupNW = CreateTimeTrigger(true, true, 9000 + TethysGame::GetRand(200), "CreateFightGroupNW");
			else
				scriptGlobal.TrigFightGroupNW2 = CreateTimeTrigger(true, true, 10000 + TethysGame::GetRand(200), "CreateFightGroupNW2");
			break;
		case 5:
			scriptGlobal.TrigFightGroupSW = CreateTimeTrigger(true, true, 12000 + TethysGame::GetRand(200), "CreateFightGroupSW");
			break;
		}
	}
}

void InitializeScenario(bool multiplayer)
{
	//MAP_RECT mapRect(25, 25, 10, 10);
	//MAP_RECT mapRect(10, 10, 25, 25);

	//bool inside = mapRect.Check(LOCATION(15, 15));

	scriptGlobal.Multiplayer = multiplayer;

	TethysGame::SetDaylightMoves(false);
	if (multiplayer && TethysGame::UsesDayNight())
	{
		TethysGame::SetDaylightEverywhere(false);
		GameMap::SetInitialLightLevel(1);
	}

	Player[0].CenterViewOn(167 + X_, 3 + Y_);

	if (multiplayer) {
		Player[1].CenterViewOn(256 + X_, 25 + Y_);
	}

	Player[Player0].GoHuman();
	Player[Player0].GoPlymouth();

	if (!multiplayer) {
		Player[Player0].SetColorNumber(PlayerColor::PlayerRed);
	}

	Player[Player1].GoPlymouth();

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
	Player[Player2].GoAI();
	if (multiplayer)
	{
		Player[Player2].SetColorNumber(GetAIColor());
	}
	else
	{
		Player[Player2].SetColorNumber(PlayerColor::PlayerBlue);
	}

	Player[Player0].AllyWith(Player1);
	Player[Player1].AllyWith(Player0);

	if (TethysGame::CanHaveDisasters())
	{ 
		scriptGlobal.DisasterTimeTrig = CreateTimeTrigger(true, false, 1500, 3500, "CreateDisaster"); //Set time in ticks (marks / 100)
	}

	SetResearchedTech();

	InitializeRescueConvoy(Player[0].IsEden() != 0, multiplayer, vehicleBuilderAI);

	InitializeEvacuationConvoy(multiplayer, Player[1].IsEden() != 0, vehicleBuilderAI);

	vehicleCounter.Clear();
	vehicleCounter.PullVehiclesFromPlayer(Player1);
	int evacConvoyNonCombatVehicleCount = vehicleCounter.NonCombatVehicleCount();

	InitializeVictoryConditions(evacConvoyNonCombatVehicleCount);

	scriptGlobal.TrigChaseFightGroup = CreateTimeTrigger(true, true, 1800 + TethysGame::GetRand(200), "CreateFinalFightGroup");
	
	InitializeSurpriseAttackTriggers();
	

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
	vehicleCounter.PullVehiclesFromPlayer(Player1);
	int numberOfUnits = vehicleCounter.GetVehicleCount();

	vehicleCounter.Clear();
	vehicleCounter.PullVehiclesFromRectangle(Player1, GetRectCenteredOnLoc(loc, 18));
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

	if (ReachedFinalWaypoint()) {
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
		if (mapRect.Check(unit.Location())) {
			continue;
		}

		unit.DoMove(waypointLocs[scriptGlobal.CurrentWaypointIndex]);
	}
}

void FightGroupRespondToAttacked(FightGroup& fightGroup)
{
	if (fightGroup.IsInitialized() && fightGroup.HasBeenAttacked())
	{
		fightGroup.DoAttackEnemy();
	}
}

void ForcePatrolsToCounterAttack()
{
	FightGroupRespondToAttacked(scriptGlobal.FirstPatrolFightGroup);
	FightGroupRespondToAttacked(scriptGlobal.EastPatrolFightGroup);
	FightGroupRespondToAttacked(scriptGlobal.CenterPatrolFightGroup);
	FightGroupRespondToAttacked(scriptGlobal.WestPatrolFightGroup);
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

		if (!scriptGlobal.Multiplayer && !ReachedFinalWaypoint())
		{
			MoveConvoyToCurrentWaypoint();
		}
	}
	else
	{
		ForcePatrolsToCounterAttack();
	}
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