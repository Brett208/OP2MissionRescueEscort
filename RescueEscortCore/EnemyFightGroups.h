#pragma once

#include "ScriptGlobal.h"
#include "UnitHelper.h"
#include "Outpost2DLL\Outpost2DLL.h"
#include <vector>

UnitHelper::VehicleBuilder vehicleBuilderAI;

int GetDifficultyLevel()
{
	if (scriptGlobal.Multiplayer)
	{
		return TethysGame::InitialUnits();
	}

	PlayerDifficulty playerDiff = (PlayerDifficulty)Player[Player0].Difficulty();

	if (playerDiff == PlayerDifficulty::DiffEasy)
	{
		return 0;
	}

	if (playerDiff == PlayerDifficulty::DiffNormal)
	{
		return 4;
	}

	return 8;
}

map_id turretsNE[]
{
	map_id::mapRailGun, 
	map_id::mapEMP, 
	map_id::mapThorsHammer,
	map_id::mapAcidCloud,
	map_id::mapLaser,
	map_id::mapEMP,
	map_id::mapRailGun,
	map_id::mapEMP,
	map_id::mapLaser,
	map_id::mapThorsHammer,
	map_id::mapEMP,
	map_id::mapThorsHammer
};

map_id laserTurrets[]
{
	map_id::mapLaser,
	map_id::mapLaser,
	map_id::mapLaser,
	map_id::mapLaser,
	map_id::mapLaser,
	map_id::mapLaser,
	map_id::mapLaser,
	map_id::mapLaser,
	map_id::mapLaser,
	map_id::mapLaser,
	map_id::mapLaser,
	map_id::mapLaser
};

map_id turretsThors[]
{
	map_id::mapThorsHammer,
	map_id::mapNone,
	map_id::mapThorsHammer,
	map_id::mapNone,
	map_id::mapThorsHammer,
	map_id::mapNone,
	map_id::mapThorsHammer,
	map_id::mapNone,
	map_id::mapThorsHammer,
	map_id::mapNone,
	map_id::mapThorsHammer,
	map_id::mapNone
};

map_id turretsEmpRailGun[]
{
	map_id::mapRailGun,
	map_id::mapEMP,
	map_id::mapRailGun,
	map_id::mapEMP,
	map_id::mapRailGun,
	map_id::mapEMP,
	map_id::mapRailGun,
	map_id::mapEMP,
	map_id::mapRailGun,
	map_id::mapEMP,
	map_id::mapRailGun,
	map_id::mapEMP
};

map_id turrestAcidLaserEMP[]
{
	map_id::mapAcidCloud,
	map_id::mapLaser,
	map_id::mapEMP,
	map_id::mapLaser,
	map_id::mapAcidCloud,
	map_id::mapLaser,
	map_id::mapEMP,
	map_id::mapLaser,
	map_id::mapAcidCloud,
	map_id::mapLaser,
	map_id::mapEMP,
	map_id::mapLaser
};

void AddDifficultyTurrets(const map_id turretsIn[], std::vector<map_id>& turretsOut)
{
	for (int i = 0; i < GetDifficultyLevel(); ++i)
	{
		if (turretsIn[i] == map_id::mapNone)
		{
			continue;
		}

		turretsOut.push_back(turretsIn[i]);
	}
}

Export void CreateFightGroupNE()
{
	std::vector<Unit> units;
	PlayerDifficulty difficulty = (PlayerDifficulty)Player[Player0].Difficulty();

	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.SetVehicleDirection(UnitDirection::South);


	std::vector<map_id> turrets{ map_id::mapLaser };
	AddDifficultyTurrets(turretsNE, turrets);

	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(206 + X_, 1 + Y_), UnitDirection::East, 1, map_id::mapPanther, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FightGroupNE, units);
	scriptGlobal.FightGroupNE.DoAttackEnemy();

	scriptGlobal.TrigFightGroupNE.Destroy();
}

Export void CreateFightGroupSE()
{
	std::vector<Unit> units;

	std::vector<map_id> turrets{ map_id::mapThorsHammer };
	AddDifficultyTurrets(turretsNE, turrets);

	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(214 + X_, 64 + Y_), UnitDirection::East, 1, map_id::mapLynx, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FightGroupSE, units);
	scriptGlobal.FightGroupSE.DoAttackEnemy();

	scriptGlobal.TrigFightGroupSE.Destroy();
}

Export void CreateFightGroupN()
{
	std::vector<Unit> units;

	std::vector<map_id> turrets{ map_id::mapThorsHammer };
	AddDifficultyTurrets(turretsThors, turrets);

	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(121 + X_, 1 + Y_), UnitDirection::East, 1, map_id::mapPanther, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FightGroupN, units);
	scriptGlobal.FightGroupN.DoAttackEnemy();

	scriptGlobal.TrigFightGroupN.Destroy();
}

Export void CreateFightGroupS()
{
	std::vector<Unit> units;

	std::vector<map_id> turrets{ map_id::mapEMP };
	AddDifficultyTurrets(laserTurrets, turrets);

	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(147 + X_, 64 + Y_), UnitDirection::East, 1, map_id::mapLynx, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FightGroupS, units);
	scriptGlobal.FightGroupS.DoAttackEnemy();

	scriptGlobal.TrigFightGroupS.Destroy();
}

Export void CreateFightGroupNW()
{
	std::vector<Unit> units;

	std::vector<map_id> turrets{ map_id::mapEMP };
	AddDifficultyTurrets(turretsEmpRailGun, turrets);

	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(64 + X_, 1 + Y_), UnitDirection::East, 1, map_id::mapLynx, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FightGroupNW, units);
	scriptGlobal.FightGroupNW.DoAttackEnemy();

	scriptGlobal.TrigFightGroupNW.Destroy();
}

Export void CreateFightGroupSW()
{
	std::vector<Unit> units;

	std::vector<map_id> turrets{ map_id::mapEMP };
	AddDifficultyTurrets(turrestAcidLaserEMP, turrets);

	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(37 + X_, 64 + Y_), UnitDirection::East, 1, map_id::mapLynx, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FightGroupSW, units);
	scriptGlobal.FightGroupSW.DoAttackEnemy();

	scriptGlobal.TrigFightGroupSW.Destroy();
}

Export void CreateFinalFightGroup()
{
	std::vector<map_id> turrets{ map_id::mapAcidCloud, map_id::mapThorsHammer, map_id::mapEMP, map_id::mapRailGun, map_id::mapEMP,
		map_id::mapAcidCloud, map_id::mapThorsHammer, map_id::mapEMP, map_id::mapRailGun, map_id::mapEMP,
		map_id::mapAcidCloud, map_id::mapThorsHammer, map_id::mapEMP, map_id::mapRailGun, map_id::mapEMP};

	std::vector<Unit> units;
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(255 + X_, 10 + Y_), UnitDirection::South, 1, map_id::mapTiger, turrets);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(256 + X_, 10 + Y_), UnitDirection::South, 1, map_id::mapTiger, turrets);

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FinalTigerFightGroup, units);
	scriptGlobal.FinalTigerFightGroup.DoAttackEnemy();
	scriptGlobal.TrigChaseFightGroup.Destroy();

	units.clear();

	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(256 + X_, 30 + Y_), UnitDirection::South, 1, map_id::mapLynx, turrets);
	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FinalLynxFightGroup, units);
	scriptGlobal.FinalLynxFightGroup.DoAttackEnemy();
}
