#pragma once

#include "ScriptGlobal.h"
#include "UnitHelper.h"
#include "Outpost2DLL\Outpost2DLL.h"
#include <vector>
#include <array>

UnitHelper::VehicleBuilder vehicleBuilderAI;

const size_t turretArraySize = 13;

int GetDifficultyLevel()
{
	if (scriptGlobal.Multiplayer)
		return TethysGame::InitialUnits();

	PlayerDifficulty playerDiff = (PlayerDifficulty)Player[Player0].Difficulty();

	if (playerDiff == PlayerDifficulty::DiffEasy)
		return 4;

	if (playerDiff == PlayerDifficulty::DiffNormal)
		return 8;

	return 10;
}

std::array<map_id, turretArraySize> turretsMix
{
	map_id::mapRailGun,
	map_id::mapNone,
	map_id::mapNone, 
	map_id::mapThorsHammer,
	map_id::mapNone,
	map_id::mapNone,
	map_id::mapNone,
	map_id::mapLaser,
	map_id::mapNone,
	map_id::mapEMP,
	map_id::mapNone,
	map_id::mapRailGun,
	map_id::mapNone
};

std::array<map_id, turretArraySize> laserTurrets
{
	map_id::mapLaser,
	map_id::mapLaser,
	map_id::mapNone,
	map_id::mapNone,
	map_id::mapLaser,
	map_id::mapLaser,
	map_id::mapNone,
	map_id::mapLaser,
	map_id::mapNone,
	map_id::mapNone,
	map_id::mapLaser,
	map_id::mapNone,
	map_id::mapLaser
};

std::array<map_id, turretArraySize> turretsThors
{
	map_id::mapThorsHammer,
	map_id::mapNone,
	map_id::mapNone,
	map_id::mapThorsHammer,
	map_id::mapNone,
	map_id::mapNone,
	map_id::mapThorsHammer,
	map_id::mapNone,
	map_id::mapThorsHammer,
	map_id::mapNone,
	map_id::mapNone,
	map_id::mapNone,
	map_id::mapThorsHammer
};

std::array<map_id, turretArraySize> turretsEmpRailGun
{
	map_id::mapRailGun,
	map_id::mapNone,
	map_id::mapNone,
	map_id::mapEMP,
	map_id::mapNone,
	map_id::mapNone,
	map_id::mapRailGun,
	map_id::mapNone,
	map_id::mapNone,
	map_id::mapNone,
	map_id::mapEMP,
	map_id::mapNone,
	map_id::mapNone
};

std::array<map_id, turretArraySize> turrestAcidLaserEMP
{
	map_id::mapAcidCloud,
	map_id::mapNone,
	map_id::mapLaser,
	map_id::mapNone,
	map_id::mapAcidCloud,
	map_id::mapNone,
	map_id::mapNone,
	map_id::mapEMP,
	map_id::mapNone,
	map_id::mapNone,
	map_id::mapLaser,
	map_id::mapNone,
	map_id::mapNone,
};

void AddDifficultyTurrets(const std::array<map_id, turretArraySize> turretsIn, std::vector<map_id>& turretsOut)
{
	for (int i = 0; i < GetDifficultyLevel() + 1; ++i)
	{
		if (turretsIn[i] == map_id::mapNone)
			continue;

		turretsOut.push_back(turretsIn[i]);
	}
}

void AddDifficultyTurrets(std::vector<map_id>& turretsOut)
{
	std::array<map_id, turretArraySize> turretsIn;
	switch (TethysGame::GetRand(5))
	{
	case 0:
		turretsIn = turretsMix;
		break;
	case 1:
		turretsIn = laserTurrets;
		break;
	case 2:
		turretsIn = turretsThors;
		break;
	case 3:
		turretsIn = turretsEmpRailGun;
		break;
	case 4:
		turretsIn = turrestAcidLaserEMP;
		break;
	}

	AddDifficultyTurrets(turretsIn, turretsOut);
}

Export void CreateFightGroupNE()
{
	std::vector<Unit> units;
	PlayerDifficulty difficulty = (PlayerDifficulty)Player[Player0].Difficulty();

	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.SetVehicleDirection(UnitDirection::South);

	map_id tankType = UnitHelper::GetRandomTankType(false);

	std::vector<map_id> turrets;
	AddDifficultyTurrets(turrets);

	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(206 + X_, 1 + Y_), UnitDirection::East, 1, tankType, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FightGroupNE, units);
	scriptGlobal.FightGroupNE.DoAttackEnemy();

	scriptGlobal.TrigFightGroupNE.Destroy();
}

Export void CreateFightGroupSE()
{
	std::vector<Unit> units;

	std::vector<map_id> turrets;
	AddDifficultyTurrets(turrets);

	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(214 + X_, 64 + Y_), UnitDirection::East, 1, map_id::mapLynx, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FightGroupSE, units);
	scriptGlobal.FightGroupSE.DoAttackEnemy();

	scriptGlobal.TrigFightGroupSE.Destroy();
}

Export void CreateFightGroupN()
{
	std::vector<Unit> units;

	std::vector<map_id> turrets;
	AddDifficultyTurrets(turrets);

	map_id tankType = UnitHelper::GetRandomTankType(false);

	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(121 + X_, 1 + Y_), UnitDirection::East, 1, tankType, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FightGroupN, units);
	scriptGlobal.FightGroupN.DoAttackEnemy();

	scriptGlobal.TrigFightGroupN.Destroy();
}

Export void CreateFightGroupS()
{
	std::vector<Unit> units;

	std::vector<map_id> turrets;
	AddDifficultyTurrets(turrets);

	map_id tankType = UnitHelper::GetRandomTankType(false);

	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(150 + X_, 64 + Y_), UnitDirection::East, 1, tankType, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FightGroupS, units);
	scriptGlobal.FightGroupS.DoAttackEnemy();

	scriptGlobal.TrigFightGroupS.Destroy();
}

Export void CreateFightGroupS2()
{
	std::vector<Unit> units;

	std::vector<map_id> turrets;
	AddDifficultyTurrets(turrets);

	map_id tankType = UnitHelper::GetRandomTankType(false);

	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(108 + X_, 64 + Y_), UnitDirection::East, 1, tankType, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FightGroupS, units);
	scriptGlobal.FightGroupS.DoAttackEnemy();

	scriptGlobal.TrigFightGroupS2.Destroy();
}

Export void CreateFightGroupNW()
{
	std::vector<Unit> units;

	std::vector<map_id> turrets;
	AddDifficultyTurrets(turrets);

	map_id tankType = UnitHelper::GetRandomTankType(false);

	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(64 + X_, 1 + Y_), UnitDirection::East, 1, tankType, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FightGroupNW, units);
	scriptGlobal.FightGroupNW.DoAttackEnemy();

	scriptGlobal.TrigFightGroupNW.Destroy();
}

Export void CreateFightGroupNW2()
{
	std::vector<Unit> units;

	std::vector<map_id> turrets;
	AddDifficultyTurrets(turrets);

	map_id tankType = UnitHelper::GetRandomTankType(false);
	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(), UnitDirection::East, 1, tankType, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FightGroupNW2, units);
	scriptGlobal.FightGroupNW2.DoAttackEnemy();

	scriptGlobal.TrigFightGroupNW2.Destroy();
}

Export void CreateFightGroupSW()
{
	std::vector<Unit> units;

	std::vector<map_id> turrets;
	AddDifficultyTurrets(turrets);

	map_id tankType = UnitHelper::GetRandomTankType(false);

	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(37 + X_, 64 + Y_), UnitDirection::East, 1, tankType, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FightGroupSW, units);
	scriptGlobal.FightGroupSW.DoAttackEnemy();

	scriptGlobal.TrigFightGroupSW.Destroy();
}

Export void CreateFinalFightGroup()
{
	std::vector<map_id> turrets{ map_id::mapAcidCloud, map_id::mapThorsHammer, map_id::mapEMP, map_id::mapRailGun, map_id::mapEMP,
		map_id::mapAcidCloud, map_id::mapThorsHammer, map_id::mapEMP, map_id::mapRailGun, map_id::mapEMP,
		map_id::mapAcidCloud, map_id::mapThorsHammer, map_id::mapEMP, map_id::mapRailGun, map_id::mapEMP, map_id::mapAcidCloud};

	std::vector<Unit> units;
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(255 + X_, 10 + Y_), UnitDirection::South, 1, map_id::mapTiger, turrets);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(256 + X_, 10 + Y_), UnitDirection::South, 1, map_id::mapTiger, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FinalTigerFightGroup, units);
	scriptGlobal.FinalTigerFightGroup.DoAttackEnemy();
	scriptGlobal.TrigChaseFightGroup.Destroy();

	units.clear();
	
	std::vector<map_id> lynxTurrets;
	AddDifficultyTurrets(lynxTurrets);

	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(256 + X_, 30 + Y_), UnitDirection::South, 1, map_id::mapLynx, lynxTurrets);
	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FinalLynxFightGroup, units);
	scriptGlobal.FinalLynxFightGroup.DoAttackEnemy();
}

void SetPatrol(FightGroup& fightGroup, LOCATION* patrolPoints)
{
	PatrolRoute patrolRoute;
	patrolRoute.waypoints = patrolPoints;

	fightGroup.SetPatrolMode(patrolRoute);
}

void CreatePatrol(FightGroup& fightGroup, LOCATION* patrolPoints, int validPatrolPointCount, map_id tankType, const std::vector<map_id>& turrets)
{
	std::vector<Unit> units;
	
	LOCATION loc = patrolPoints[TethysGame::GetRand(validPatrolPointCount)];

	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.SetVehicleDirection(UnitDirection::South);
	vehicleBuilderAI.CreateLineOfVehicles(units, loc, UnitDirection::East, 1, tankType, turrets);
	vehicleBuilderAI.PopulateFightGroup(fightGroup, units);

	SetPatrol(fightGroup, patrolPoints);
}

void SetGuard(FightGroup& fightGroup, MAP_RECT& guardRect)
{
	fightGroup.AddGuardedRect(guardRect);
	fightGroup.SetRect(guardRect);
}

void CreateGuard(FightGroup& fightGroup, MAP_RECT& guardRect, map_id tankType, const std::vector<map_id>& turrets)
{
	std::vector<Unit> units;

	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.CreateVehiclesInRect(units, guardRect, tankType, turrets);
	vehicleBuilderAI.PopulateFightGroup(fightGroup, units);

	SetGuard(fightGroup, guardRect);
}

void CreatePatrolOrGuard(FightGroup& fightGroup, LOCATION* patrolLocs, int validPatrolPointCount, MAP_RECT& guardRect)
{
	map_id tankType = UnitHelper::GetRandomTankType(false);

	std::vector<map_id> turrets;
	AddDifficultyTurrets(turrets);

	if (TethysGame::GetRand(2) == 0)
	{
		CreatePatrol(fightGroup, patrolLocs, validPatrolPointCount, tankType, turrets);
	}
	else
	{
		CreateGuard(fightGroup, guardRect, tankType, turrets);
	}
}

void InitializeStartingEnemyUnits(UnitHelper::VehicleBuilder& vehicleBuilderAI)
{
	int totalPatrolCount = 3;
	int patrolToSkip = TethysGame::GetRand(totalPatrolCount);

	for (int i = 0; i < totalPatrolCount; ++i)
	{
		if (i == patrolToSkip)
			continue;

		switch (i)
		{
		case 0:
		{
			LOCATION patrolLocs[]{ LOCATION(170 + X_, 17 + Y_), LOCATION(140 + X_, 59 + Y_), LOCATION(-1, -1) };
			CreatePatrolOrGuard(scriptGlobal.EastPatrolFightGroup, patrolLocs, 2, MAP_RECT{ 151 + X_, 27 + Y_, 173 + X_, 44 + Y_ });
			break;
		}
		case 1:
		{
			LOCATION patrolLocs[]{ LOCATION(99 + X_, 12 + Y_), LOCATION(107 + X_, 40 + Y_), LOCATION(118 + X_, 57 + Y_), LOCATION(-1, -1) };
			CreatePatrolOrGuard(scriptGlobal.CenterPatrolFightGroup, patrolLocs, 3, MAP_RECT{ 95 + X_, 21 + Y_, 123 + X_, 44 + Y_ });
			break;
		}
		case 2:
			LOCATION patrolLocs[]{ LOCATION(58 + X_, 11 + Y_), LOCATION(48 + X_, 40 + Y_), LOCATION(20 + X_, 52 + Y_), LOCATION(-1, -1) };
			CreatePatrolOrGuard(scriptGlobal.WestPatrolFightGroup, patrolLocs, 3, MAP_RECT(36 + X_, 38 + Y_, 68 + X_, 58 + Y_));
			break;
		}
	}

	std::vector<Unit> units;

	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(223 + X_, 23 + Y_), UnitDirection::South, 1, map_id::mapLynx, std::vector<map_id> { map_id::mapEMP, map_id::mapRailGun, map_id::mapLaser, map_id::mapEMP });
	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FirstPatrolFightGroup, units);

	PatrolRoute patrolRoute2;
	LOCATION patrolPoints2[]{ LOCATION(223 + X_, 23 + Y_), LOCATION(222 + X_, 44 + Y_), LOCATION(-1, -1) };
	patrolRoute2.waypoints = patrolPoints2;

	scriptGlobal.FirstPatrolFightGroup.SetPatrolMode(patrolRoute2);
}