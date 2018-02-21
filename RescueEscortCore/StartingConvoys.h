#pragma once

#include "UnitHelper.h"
#include "Outpost2DLL\Outpost2DLL.h"
#include <vector>
#include <array>

int AdjustNumberOfVecs(int playerNum, int mediumNumber)
{
	if (Player[1].Difficulty() == PlayerDifficulty::DiffEasy) {
		return mediumNumber++;
	}
	else if (Player[1].Difficulty() == PlayerDifficulty::DiffHard) {
		mediumNumber--;
	}

	return mediumNumber;
}

void InitializeRescueConvoy(bool isEden, bool multiplayer, UnitHelper::VehicleBuilder& vehicleBuilderAI)
{	
	std::array<map_id, 5> turrets{ map_id::mapMicrowave, map_id::mapStickyfoam, map_id::mapRPG, map_id::mapEMP, map_id::mapESG };;
	if (isEden)
	{
		turrets = { map_id::mapLaser, map_id::mapRailGun, map_id::mapEMP, map_id::mapAcidCloud, map_id::mapThorsHammer };
	}
	
	std::vector<Unit> units;

	vehicleBuilderAI.SetPlayer(Player0);
	vehicleBuilderAI.SetVehicleDirection(UnitDirection::South);

	LOCATION startLoc(156 + X_, 1 + Y_);

	int numberOfVechs = 4;
	if (multiplayer)
		numberOfVechs = AdjustNumberOfVecs(Player0, 3);

	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc, UnitDirection::South, 2, map_id::mapLynx, turrets[0], numberOfVechs);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(2, 0), UnitDirection::South, 2, map_id::mapLynx, turrets[1], numberOfVechs);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(4, 0), UnitDirection::South, 2, map_id::mapLynx, turrets[2], numberOfVechs);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(6, 0), UnitDirection::South, 2, map_id::mapLynx, turrets[3], numberOfVechs);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(8, 0), UnitDirection::South, 2, map_id::mapLynx, turrets[4], numberOfVechs);

	numberOfVechs--;

	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(14, 0), UnitDirection::South, 2, map_id::mapPanther, turrets[0], numberOfVechs);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(16, 0), UnitDirection::South, 2, map_id::mapPanther, turrets[1], numberOfVechs);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(18, 0), UnitDirection::South, 2, map_id::mapPanther, turrets[2], numberOfVechs);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(20, 0), UnitDirection::South, 2, map_id::mapPanther, turrets[3], numberOfVechs);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(22, 0), UnitDirection::South, 2, map_id::mapPanther, turrets[4], numberOfVechs);

	if (!isEden)
	{
		vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(10, 0), UnitDirection::South, 2, map_id::mapSpider, map_id::mapNone, 3);
		vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(12, 0), UnitDirection::South, 2, map_id::mapSpider, map_id::mapNone, 3);
	}

	Unit unit;
	vehicleBuilderAI.CreateVechLightsOn(unit, map_id::mapScout, startLoc + LOCATION(10, 6), map_id::mapNone);
	units.push_back(unit);
	vehicleBuilderAI.CreateVechLightsOn(unit, map_id::mapScout, startLoc + LOCATION(12, 6), map_id::mapNone);
	units.push_back(unit);

	vehicleBuilderAI.MoveRelativeAmount(units, LOCATION(0, 2));
}

void InitializeEvacuationConvoyTurrets(bool isEden, std::array<map_id, 3>& turrets)
{
	if (isEden) {
		turrets = { map_id::mapLaser, map_id::mapRailGun, map_id::mapThorsHammer };
	}
	else {
		turrets = { map_id::mapMicrowave, map_id::mapRPG, map_id::mapESG };
	}
}

void InitializeEvacuationConvoy(bool multiplayer, bool isEden, UnitHelper::VehicleBuilder& vehicleBuilderAI)
{
	std::vector<Unit> units;

	vehicleBuilderAI.SetPlayer(Player1);
	vehicleBuilderAI.SetVehicleDirection(UnitDirection::West);

	LOCATION startLoc(256 - 5 + X_, 30 + Y_);

	std::array<map_id, 3> turrets;
	InitializeEvacuationConvoyTurrets(isEden, turrets);

	int numberOfVehicles = 3;
	if (multiplayer) {
		numberOfVehicles = AdjustNumberOfVecs(Player1, 2);
	}

	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc, UnitDirection::South, 1, map_id::mapLynx, turrets[0], numberOfVehicles);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(0, 3), UnitDirection::South, 1, map_id::mapLynx, turrets[1], numberOfVehicles);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(0, 6), UnitDirection::South, 1, map_id::mapLynx, turrets[2], numberOfVehicles);

	std::vector<map_id> unitTypes{ map_id::mapEvacuationTransport, map_id::mapEvacuationTransport, map_id::mapEvacuationTransport, map_id::mapEvacuationTransport};

	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(1, 0), UnitDirection::South, 1, unitTypes);

	std::vector<map_id> cargoTypes{ map_id::mapCommandCenter, map_id::mapStructureFactory, map_id::mapCommonOreSmelter,
			map_id::mapTokamak, map_id::mapAgridome, map_id::mapRareStorage };

	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(1, 3), UnitDirection::South, 1, map_id::mapConVec, cargoTypes);

	unitTypes.clear();
	unitTypes = { map_id::mapRoboMiner, map_id::mapRoboMiner, map_id::mapRoboDozer, 
		map_id::mapRoboSurveyor, map_id::mapRoboSurveyor,  map_id::mapEarthworker, map_id::mapEarthworker };

	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(2, 0), UnitDirection::South, 1, unitTypes);

	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(2, 7), UnitDirection::South, 1, map_id::mapRoboMiner, map_id::mapNone, 1);

	std::vector<Truck_Cargo> truckCargo{ Truck_Cargo::truckCommonMetal, Truck_Cargo::truckCommonMetal,
		Truck_Cargo::truckCommonMetal, Truck_Cargo::truckRareMetal, Truck_Cargo::truckFood, Truck_Cargo::truckFood, Truck_Cargo::truckFood };

	vehicleBuilderAI.CreateLineOfTrucksWithCargo(units, startLoc + LOCATION(3, 1), UnitDirection::South, 1, truckCargo);

	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(4, 0), UnitDirection::South, 1, map_id::mapPanther, turrets[0], numberOfVehicles);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(4, 3), UnitDirection::South, 1, map_id::mapPanther, turrets[1], numberOfVehicles);
	vehicleBuilderAI.CreateLineOfVehicles(units, startLoc + LOCATION(4, 6), UnitDirection::South, 1, map_id::mapPanther, turrets[2], numberOfVehicles);

	if (multiplayer)
	{
		vehicleBuilderAI.MoveRelativeAmount(units, LOCATION(-2, 0));
	}
}