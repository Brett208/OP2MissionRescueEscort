#pragma once

#include "UnitHelper.h"
#include "Outpost2DLL\Outpost2DLL.h"
#include <vector>

void InitializeRescueConvoy(UnitHelper::VehicleBuilder& vehicleBuilderAI)
{
	std::vector<Unit> units;

	vehicleBuilderAI.SetPlayer(Player0);
	vehicleBuilderAI.SetVehicleDirection(UnitDirection::South);

	LOCATION startLoc(156 + X_, 1 + Y_);

	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc, UnitDirection::South, 2, map_id::mapLynx, map_id::mapMicrowave, 4);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(2, 0), UnitDirection::South, 2, map_id::mapLynx, map_id::mapStickyfoam, 4);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(4, 0), UnitDirection::South, 2, map_id::mapLynx, map_id::mapRPG, 4);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(6, 0), UnitDirection::South, 2, map_id::mapLynx, map_id::mapEMP, 4);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(8, 0), UnitDirection::South, 2, map_id::mapLynx, map_id::mapESG, 4);

	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(14, 0), UnitDirection::South, 2, map_id::mapPanther, map_id::mapMicrowave, 3);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(16, 0), UnitDirection::South, 2, map_id::mapPanther, map_id::mapStickyfoam, 3);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(18, 0), UnitDirection::South, 2, map_id::mapPanther, map_id::mapRPG, 3);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(20, 0), UnitDirection::South, 2, map_id::mapPanther, map_id::mapEMP, 3);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(22, 0), UnitDirection::South, 2, map_id::mapPanther, map_id::mapESG, 3);

	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(10, 0), UnitDirection::South, 2, map_id::mapSpider, map_id::mapNone, 3);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(12, 0), UnitDirection::South, 2, map_id::mapSpider, map_id::mapNone, 3);

	Unit unit;
	vehicleBuilderAI.CreateVechLightsOn(unit, map_id::mapScout, startLoc + LOCATION(10, 6), map_id::mapNone);
	units.push_back(unit);
	vehicleBuilderAI.CreateVechLightsOn(unit, map_id::mapScout, startLoc + LOCATION(12, 6), map_id::mapNone);
	units.push_back(unit);

	vehicleBuilderAI.MoveRelativeAmount(units, LOCATION(0, 2));
}

void InitializeEvacuationConvoy(bool multiplayer, UnitHelper::VehicleBuilder& vehicleBuilderAI)
{
	std::vector<Unit> units;

	vehicleBuilderAI.SetPlayer(Player1);
	vehicleBuilderAI.SetVehicleDirection(UnitDirection::West);

	LOCATION startLoc(256 -5 + X_, 30 + Y_);

	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc, UnitDirection::South, 1, map_id::mapLynx, map_id::mapMicrowave, 3);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(0, 3), UnitDirection::South, 1, map_id::mapLynx, map_id::mapRPG, 3);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(0, 6), UnitDirection::South, 1, map_id::mapLynx, map_id::mapESG, 3);

	std::vector<map_id> cargo{ map_id::mapConVec, map_id::mapConVec, map_id::mapConVec,
		map_id::mapEvacuationTransport, map_id::mapEvacuationTransport, map_id::mapEvacuationTransport,
		map_id::mapConVec, map_id::mapConVec, map_id::mapConVec};

	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(1, 0), UnitDirection::South, 1, cargo);

	cargo.clear();
	cargo = { map_id::mapRoboMiner, map_id::mapRoboMiner, map_id::mapRoboDozer, 
		map_id::mapRoboSurveyor, map_id::mapRoboSurveyor,  map_id::mapScout, 
		map_id::mapSpider, map_id::mapSpider, map_id::mapEarthworker };

	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(2, 0), UnitDirection::South, 1, cargo);

	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(3, 0), UnitDirection::South, 1, map_id::mapPanther, map_id::mapMicrowave, 3);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(3, 3), UnitDirection::South, 1, map_id::mapPanther, map_id::mapRPG, 3);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(3, 6), UnitDirection::South, 1, map_id::mapPanther, map_id::mapESG, 3);

	if (multiplayer)
	{
		vehicleBuilderAI.Move(units, LOCATION(201, 29));
	}
	else
	{
		vehicleBuilderAI.MoveRelativeAmount(units, LOCATION(-2, 0));
	}
}

void InitializeStartingEnemyUnits(UnitHelper::VehicleBuilder& vehicleBuilderAI)
{
	int initialUnits = TethysGame::InitialUnits();

	// Build Bad Guy Initial Units
	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.SetVehicleDirection(UnitDirection::South);

	std::vector<Unit> units;
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(145 + X_, 55 + Y_), UnitDirection::South, 2, map_id::mapLynx, std::vector<map_id> { map_id::mapLaser, map_id::mapAcidCloud, map_id::mapEMP, map_id::mapRailGun, map_id::mapEMP });

	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.LynxPatrolFightGroup, units);

	LOCATION patrolPoints[]{ LOCATION(170 + X_, 17 + Y_), LOCATION(140 + X_, 59 + Y_), LOCATION(-1, -1) };

	PatrolRoute patrolRoute;
	patrolRoute.waypoints = patrolPoints;
	scriptGlobal.LynxPatrolFightGroup.SetPatrolMode(patrolRoute);


	units.clear();

	vehicleBuilderAI.SetPlayer(Player2);
	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(223 + X_, 23 + Y_), UnitDirection::South, 1, map_id::mapLynx, std::vector<map_id> { map_id::mapEMP, map_id::mapRailGun, map_id::mapLaser, map_id::mapEMP });
	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.FirstPatrolFightGroup, units);
	
	PatrolRoute patrolRoute2;
	LOCATION patrolPoints2[]{ LOCATION(223 + X_, 23 + Y_), LOCATION(222 + X_, 44 + Y_), LOCATION(-1, -1) };
	patrolRoute2.waypoints = patrolPoints2;

	scriptGlobal.FirstPatrolFightGroup.SetPatrolMode(patrolRoute2);

	units.clear();

	vehicleBuilderAI.CreateLineOfVehicles(units, LOCATION(48 + X_, 40 + Y_), UnitDirection::East, 2, map_id::mapPanther, std::vector<map_id> { map_id::mapEMP, map_id::mapAcidCloud, map_id::mapThorsHammer, map_id::mapRailGun});
	vehicleBuilderAI.PopulateFightGroup(scriptGlobal.StaticPantherFightGroup, units);

	MAP_RECT guardRect(36 + X_, 38 + Y_, 68 + X_, 58 + Y_);
	scriptGlobal.StaticPantherFightGroup.AddGuardedRect(guardRect);
	scriptGlobal.StaticPantherFightGroup.SetRect(guardRect);

}