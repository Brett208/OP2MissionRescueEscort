#include "UnitHelper.h"

namespace UnitHelper
{
	void VehicleBuilder::SetPlayer(int player)
	{
		if (playerNumber > 6)
		{
			throw "Maximum of 6 players allowed.";
		}

		playerNumber = player;
	}

	int VehicleBuilder::GetPlayer()
	{
		return playerNumber;
	}

	void VehicleBuilder::SetVehicleDirection(UnitDirection direction)
	{
		unitDirection = direction;
	}

	UnitDirection VehicleBuilder::GetVehicleDirection()
	{
		return unitDirection;
	}

	void VehicleBuilder::CreateVechLightsOn(Unit &unit, map_id vehicleType, LOCATION location, map_id cargo)
	{
		TethysGame::CreateUnit(unit, vehicleType, location, playerNumber, cargo, unitDirection);
		unit.DoSetLights(true);
	}

	void VehicleBuilder::SetupMiningGroup(
		MiningGroup &miningGroup, const Unit &vehicleFactory, Unit &mine, Unit &smelter, MAP_RECT &oreIdleRect, int numbOfTrucks)
	{
		miningGroup = CreateMiningGroup(Player[1]);

		LOCATION smelterLoc = smelter.Location();
		miningGroup.Setup(mine, smelter, oreIdleRect);

		Unit truck;
		for (int i = 0; i < numbOfTrucks; ++i)
		{
			CreateVechLightsOn(truck, map_id::mapCargoTruck, oreIdleRect.RandPt(), map_id::mapNone);
			miningGroup.TakeUnit(truck);
		}

		miningGroup.SetTargCount(map_id::mapCargoTruck, map_id::mapNone, numbOfTrucks);
	}

	void VehicleBuilder::PopulateFightGroup(FightGroup &fightGroup, const std::vector<Unit> &units)
	{
		fightGroup = CreateFightGroup(playerNumber);

		for (Unit unit : units)
		{
			fightGroup.TakeUnit(unit);
		}
	}

	void VehicleBuilder::PopulateFightGroup(FightGroup &fightGroup, const std::vector<Unit> &units, map_id target)
	{
		PopulateFightGroup(fightGroup, units);

		fightGroup.SetAttackType(target);
		fightGroup.DoAttackEnemy();
	}

	std::function<LOCATION(LOCATION, int)> VehicleBuilder::getLineDirectionIterator(UnitDirection lineDirection)
	{
		switch (lineDirection)
		{
		case UnitDirection::South:
			return [](LOCATION startLoc, int spacing) { return startLoc + LOCATION(0, spacing); };

		case UnitDirection::SouthWest:
			return [](LOCATION startLoc, int spacing) { return startLoc + LOCATION(-spacing, spacing); };

		case UnitDirection::West:
			return [](LOCATION startLoc, int spacing) { return startLoc + LOCATION(-spacing, 0); };

		case UnitDirection::NorthWest:
			return [](LOCATION startLoc, int spacing) { return startLoc + LOCATION(-spacing, -spacing); };

		case UnitDirection::North:
			return [](LOCATION startLoc, int spacing) { return startLoc + LOCATION(0, -spacing); };

		case UnitDirection::NorthEast:
			return [](LOCATION startLoc, int spacing) { return startLoc + LOCATION(spacing, -spacing); };

		case UnitDirection::East:
			return [](LOCATION startLoc, int spacing) { return startLoc + LOCATION(spacing, 0); };

		case UnitDirection::SouthEast:
			return [](LOCATION startLoc, int spacing) { return startLoc + LOCATION(spacing, spacing); };
		}

		throw "Invalid UnitDirection passed into Function.";
	}

	void VehicleBuilder::CreateLineOfVehicles(std::vector<Unit> &units, LOCATION startLoc, UnitDirection lineDirection,
		int vehicleSpacing, const map_id vehicleType, const map_id cargo, int vehicleCount)
	{
		std::function<LOCATION(LOCATION, int)> directionIterator = getLineDirectionIterator(lineDirection);

		Unit unit;
		LOCATION currentLoc = startLoc;
		for (int i = 0; i < vehicleCount; ++i)
		{
			CreateVechLightsOn(unit, vehicleType, currentLoc, cargo);
			units.push_back(unit);

			currentLoc = directionIterator(currentLoc, vehicleSpacing);
		}
	}

	void VehicleBuilder::CreateLineOfVehicles(std::vector<Unit> &units, LOCATION startLoc, UnitDirection lineDirection,
		int vehicleSpacing, map_id vehicleType, const std::vector<map_id> &cargoVector)
	{
		std::function<LOCATION(LOCATION, int)> directionIterator = getLineDirectionIterator(lineDirection);

		Unit unit;
		LOCATION currentLoc = startLoc;

		for (size_t i = 0; i < cargoVector.size(); ++i)
		{
			CreateVechLightsOn(unit, vehicleType, currentLoc, cargoVector[i]);
			units.push_back(unit);

			currentLoc = directionIterator(currentLoc, vehicleSpacing);
		}
	}

	void VehicleBuilder::CreateLineOfVehicles(std::vector<Unit> &units, LOCATION startLoc, UnitDirection lineDirection,
		int vehicleSpacing, const std::vector<map_id> &vehicleTypes)
	{
		std::function<LOCATION(LOCATION, int)> directionIterator = getLineDirectionIterator(lineDirection);

		Unit unit;
		LOCATION currentLoc = startLoc;
		for (size_t i = 0; i < vehicleTypes.size(); ++i)
		{
			CreateVechLightsOn(unit, vehicleTypes[i], currentLoc, map_id::mapNone);
			units.push_back(unit);

			currentLoc = directionIterator(currentLoc, vehicleSpacing);
		}
	}

	void VehicleBuilder::CreateVehiclesInRect(std::vector<Unit> &units, MAP_RECT mapRect, map_id vehicleType,
		const std::vector<map_id> &cargoTypes)
	{
		UnitDirection startingUnitDirection = unitDirection;
		Unit unit;

		for (size_t i = 0; i < cargoTypes.size(); ++i)
		{
			unitDirection = (UnitDirection)TethysGame::GetRand(8);
			CreateVechLightsOn(unit, vehicleType, mapRect.RandPt(), cargoTypes[i]);
			units.push_back(unit);
		}

		unitDirection = startingUnitDirection;
	}

	void VehicleBuilder::CreateVehicleInRect(Unit &unit, const MAP_RECT &mapRect, map_id vehicleType, map_id cargoType)
	{
		UnitDirection startingUnitDirection = unitDirection;
		unitDirection = (UnitDirection)TethysGame::GetRand(8);

		CreateVechLightsOn(unit, vehicleType, mapRect.RandPt(), cargoType);

		unitDirection = startingUnitDirection;
	}

	void VehicleBuilder::CreateTrucksInRect(std::vector<Unit> &trucks, MAP_RECT mapRect,
		Truck_Cargo cargoType, const std::vector<int> &amounts)
	{
		UnitDirection startingUnitDirection = unitDirection;
		Unit truck;

		for (size_t i = 0; i < amounts.size(); ++i)
		{
			unitDirection = (UnitDirection)TethysGame::GetRand(8);
			CreateVechLightsOn(truck, map_id::mapCargoTruck, mapRect.RandPt(), map_id::mapNone);

			if (amounts[i] != 0)
			{
				truck.SetTruckCargo(cargoType, amounts[i]);
			}

			trucks.push_back(truck);
		}

		unitDirection = startingUnitDirection;
	}

	void VehicleBuilder::CreateLineOfTrucksWithCargo(std::vector<Unit> &units, LOCATION startLoc, UnitDirection lineDirection,
		int vehicleSpacing, const std::vector<Truck_Cargo> &cargoTypes)
	{
		std::function<LOCATION(LOCATION, int)> directionIterator = getLineDirectionIterator(lineDirection);

		Unit unit;
		LOCATION currentLoc = startLoc;
		for (size_t i = 0; i < cargoTypes.size(); ++i)
		{
			CreateVechLightsOn(unit, map_id::mapCargoTruck, currentLoc, map_id::mapNone);
			unit.SetTruckCargo(cargoTypes[i], 1000);
			units.push_back(unit);

			currentLoc = directionIterator(currentLoc, vehicleSpacing);
		}
	}

	void VehicleBuilder::SetPercentDamaged(UnitEx &unitEx, double percentDamaged)
	{
		int damage = static_cast<int>(percentDamaged * unitEx.GetUnitInfo().GetHitPoints(playerNumber) / 100);

		damage -= unitEx.GetDamage();

		unitEx.SetDamage(damage);
	}

	void VehicleBuilder::CauseRandomDamage(PlayerVehicleEnum &playerVehicEnum, double percentChanceDamaged,
		double percentMinDamage, double percentMaxDamage)
	{
		if (percentMaxDamage < percentMinDamage)
		{
			throw "maxDamage must be greater than minDamage.";
		}

		if (percentChanceDamaged > 100 || percentChanceDamaged < 0)
		{
			throw "percentChanceDamaged must be between 0 and 100.";
		}

		UnitEx unitEx;
		while (playerVehicEnum.GetNext(unitEx))
		{
			if (TethysGame::GetRand(100) <= percentChanceDamaged)
			{
				double percentOfMaxDamage = static_cast<double>(TethysGame::GetRand(100)) / static_cast<double>(100);

				double percentDamage = (percentMinDamage + (percentMaxDamage - percentMinDamage) * percentOfMaxDamage) / 100;

				int damage = static_cast<int>(percentDamage * unitEx.GetUnitInfo().GetHitPoints(playerNumber));
				unitEx.SetDamage(damage);
			}
		}
	}

	void VehicleBuilder::CreateVehicleInGarage(Unit &garage, int bayIndex, map_id vehicleType, map_id cargo)
	{
		UnitDirection oldDirection = unitDirection;
		unitDirection = UnitDirection::West;

		Unit vehicle;
		CreateVechLightsOn(vehicle, vehicleType, garage.Location(), cargo);
		vehicle.PutInGarage(bayIndex, garage.Location().x, garage.Location().y);

		unitDirection = oldDirection;
	}

	void VehicleBuilder::CreateVehicleInGarage(Unit &garage, int bayIndex, Truck_Cargo truckCargo, int cargoAmount)
	{
		UnitDirection oldDirection = unitDirection;
		unitDirection = UnitDirection::West;

		Unit vehicle;
		CreateVechLightsOn(vehicle, map_id::mapCargoTruck, garage.Location(), map_id::mapNone);

		if (cargoAmount > 0)
		{
			vehicle.SetTruckCargo(truckCargo, cargoAmount);
		}

		vehicle.PutInGarage(bayIndex, garage.Location().x, garage.Location().y);

		unitDirection = oldDirection;
	}

	void VehicleBuilder::CauseRandomDamage(std::vector<Unit> &units, int percentChanceDamaged, int minDamage, int maxDamage)
	{
		if (maxDamage < minDamage)
		{
			throw "maxDamage must be greater than minDamage.";
		}

		if (percentChanceDamaged > 100 || percentChanceDamaged < 0)
		{
			throw "percentChanceDamaged must be between 0 and 100.";
		}

		for (Unit unit : units)
		{
			if (TethysGame::GetRand(100) <= percentChanceDamaged)
			{
				double percentOfMaxDamage = static_cast<double>(TethysGame::GetRand(100)) / static_cast<double>(100);
				int damage = minDamage + static_cast<int>((percentOfMaxDamage * static_cast<double>((maxDamage - minDamage))));
				unit.SetDamage(damage);
			}
		}
	}

	void VehicleBuilder::MoveRelativeAmount(std::vector<Unit>& units, LOCATION relativeMoveAmount)
	{
		for (Unit& unit : units)
		{
			unit.DoMove(unit.Location() + relativeMoveAmount);
		}
	}

	void VehicleBuilder::Move(std::vector<Unit> &units, LOCATION location)
	{
		for (Unit& unit : units)
		{
			unit.DoMove(location);
		}
	}

	//Note: Returns true even if building is still under construction.
	bool BuildingConstructed(int playerNumber, map_id buildingType)
	{
		Unit unit;
		return GetFirstBuildingOfType(unit, playerNumber, buildingType);
	}

	bool GetFirstBuildingOfType(Unit &building, int playerNumber, map_id buildingType)
	{
		PlayerBuildingEnum playerBuildingEnum(playerNumber, buildingType);

		while (playerBuildingEnum.GetNext(building))
		{
			return true;
		}

		return false;
	}

	bool KitInConVec(int playerNumber, map_id structureKitType)
	{
		Unit vehicle;
		PlayerVehicleEnum playerVehicleEnum(playerNumber);

		while (playerVehicleEnum.GetNext(vehicle))
		{
			if (vehicle.GetType() == mapConVec && vehicle.GetCargo() == structureKitType)
			{
				return true;
			}
		}

		return false;
	}

	bool KitInStructFactory(int playerNumber, map_id structureKitType)
	{
		// Below Requires HFL/UnitEx for GetFactoryCargo.
		UnitEx nextSF;
		PlayerBuildingEnum findAllSFs(playerNumber, mapStructureFactory);

		while (findAllSFs.GetNext(nextSF))
		{
			for (int i = 0; i < 6; ++i)
			{
				if (nextSF.GetFactoryCargo(i) == structureKitType)
				{
					return true;
				}
			}
		}

		return false;
	}

	bool BuildingOrKitAvailable(int player, map_id buildingType)
	{
		return BuildingConstructed(player, buildingType) ||
			KitInConVec(player, buildingType) ||
			KitInStructFactory(player, buildingType);
	}

	bool IsCombatUnit(map_id unitType)
	{
		return unitType == map_id::mapLynx ||
			unitType == map_id::mapPanther ||
			unitType == map_id::mapTiger ||
			unitType == map_id::mapScorpion;
	}

	void FindBuildings(std::vector<Unit> &buildings, int playerNumber, const std::vector<map_id> &buildingTypes)
	{
		for (map_id mapID : buildingTypes)
		{
			PlayerBuildingEnum playerBuildingEnum = PlayerBuildingEnum(playerNumber, mapID);
			Unit unit;

			while (playerBuildingEnum.GetNext(unit))
			{
				buildings.push_back(unit);
				break;
			}
		}
	}

	void FindBuildingLocations(std::vector<LOCATION> &locations, int playerNumber, const std::vector<map_id> &buildingTypes)
	{
		std::vector<Unit> buildings;
		FindBuildings(buildings, playerNumber, buildingTypes);

		for (Unit unit : buildings)
		{
			locations.push_back(unit.Location());
		}
	}

	int FindSouthernYCoordOfCombatant(int playerNumber)
	{
		PlayerVehicleEnum vehicleEnum(playerNumber);
		Unit unit;
		int southernYCoordOfUnit = 0;

		while (vehicleEnum.GetNext(unit))
		{
			if (UnitHelper::IsCombatUnit(unit.GetType()) &&
				unit.Location().y > southernYCoordOfUnit)
			{
				southernYCoordOfUnit = unit.Location().y;
			}
		}

		return southernYCoordOfUnit;
	}

	int CountBuildings(int playerNumber, map_id buildingType)
	{
		Unit building;
		PlayerBuildingEnum playerBuildingEnum(playerNumber, buildingType);

		int buildingCount = 0;
		while (playerBuildingEnum.GetNext(building))
		{
			buildingCount++;
		}

		return buildingCount;
	}

	int CountAllBuildings(int playerNumber)
	{
		int buildingCount = 0;

		for (int i = map_id::mapCommonOreMine; i <= map_id::mapTokamak; ++i)
		{
			buildingCount += CountBuildings(playerNumber, (map_id)i);
		}

		//for (map_id mapID : BuildingTypes)
		//{
		//	buildingCount += CountBuildings(playerNumber, mapID);
		//}

		return buildingCount;
	}

	bool VehicleInRectangle(MAP_RECT mapRect, int playerNumber)
	{
		PlayerVehicleEnum playerVehicleEnum(playerNumber);

		Unit vehicle;
		while (playerVehicleEnum.GetNext(vehicle))
		{
			if (mapRect.Check(vehicle.Location()))
			{
				return true;
			}
		}

		return false;
	}

	UnitDirection GetRandomUnitDirection()
	{
		return (UnitDirection)TethysGame::GetRand(8);
	}

	map_id GetRandomTankType(bool includeTigers)
	{
		int numberOfTanks = 2;
		if (includeTigers) {
			numberOfTanks++;
		}

		int tankIndex = TethysGame::GetRand(numberOfTanks);

		switch (tankIndex)
		{
		case 0:
			return map_id::mapLynx;
		case 1:
			return map_id::mapPanther;
		default:
			return map_id::mapTiger;
		}
	}

	map_id ChooseRepairVehicleType(bool isEden)
	{
		if (isEden)
		{
			return map_id::mapRepairVehicle;
		}

		return map_id::mapSpider;
	}
}