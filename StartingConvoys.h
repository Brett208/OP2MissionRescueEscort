#pragma once

#include "UnitHelper.h"
#include "Outpost2DLL\Outpost2DLL.h"
#include <vector>

void InitializeRescueConvoy(UnitHelper::VehicleBuilder& vehicleBuilderAI)
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

int InitializeEvacuationConvoy(UnitHelper::VehicleBuilder& vehicleBuilderAI)
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

