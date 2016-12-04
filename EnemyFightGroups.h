#pragma once

#include "ScriptGlobal.h"
#include "UnitHelper.h"
#include "Outpost2DLL\Outpost2DLL.h"
#include <vector>

UnitHelper::VehicleBuilder vehicleBuilderAI;

Export void CreateFightGroup1()
{
	std::vector<Unit> units;
	PlayerDifficulty difficulty = (PlayerDifficulty)Player[Player0].Difficulty();

	vehicleBuilderAI.SetPlayer(Player2);
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

Export void CreateFightGroup2()
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

	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(1 + X_, 1 + Y_), UnitDirection::East, 1, map_id::mapPanther, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FightGroup2, units);

	scriptGlobal.TrigFightGroup2.Destroy();
}

Export void CreateFightGroup3()
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

	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(1 + X_, 1 + Y_), UnitDirection::East, 1, map_id::mapPanther, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FightGroup3, units);

	scriptGlobal.TrigFightGroup3.Destroy();
}

void CreateAcidCloudFightGroup()
{
	std::vector<Unit> units;

	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(1 + X_, 22 + Y_), UnitDirection::East, 2, map_id::mapLynx, map_id::mapAcidCloud, 2);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.AcidCloudSneakFightGroup, units);
	//scriptGlobal.AcidCloudSneakFightGroup.DoPatrolOnly();
}

Export void CreateFinalFightGroup()
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

	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.SetVehicleDirection(UnitDirection::West);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(1 + X_, 1 + Y_), UnitDirection::South, 1, map_id::mapLynx, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FinalFightGroup, units);

	scriptGlobal.FinalFightGroup.Destroy();
}
