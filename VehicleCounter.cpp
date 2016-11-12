#include "VehicleCounter.h"

namespace UnitHelper
{
	int VehicleCounter::GetVehicleCount(map_id vehicleType)
	{
		std::vector<int> vehicleIndices;
		GetVehicleIndices(vehicleIndices, vehicleType);

		int count = 0;

		for (int index : vehicleIndices)
		{
			count += VehicleCountVector[index].Count;
		}

		return count;
	}

	int VehicleCounter::GetVehicleCount(map_id vehicleType, map_id cargoType)
	{
		int index = GetVehicleIndex(vehicleType, cargoType);

		if (index == -1)
		{
			return 0;
		}

		return VehicleCountVector[index].Count;
	}

	int VehicleCounter::GetCombatVehicleCount()
	{
		int combatVehicleCount = 0;

		for (size_t i = 0; i < VehicleCountVector.size(); ++i)
		{
			if (IsWeapon(VehicleCountVector[i].UnitCargo))
			{
				combatVehicleCount += VehicleCountVector[i].Count;
			}
		}

		return combatVehicleCount;
	}

	void VehicleCounter::PullVehiclesFromPlayer(PlayerUnitEnum playerUnitEnum)
	{
		Clear();

		Unit unit;
		while (playerUnitEnum.GetNext(unit))
		{
			AddVehicleToVector(unit.GetType(), unit.GetCargo());
		}
	}

	void VehicleCounter::PullVehiclesFromRectangle(PlayerNum playerNum, InRectEnumerator inRectEnumerator)
	{
		Clear();

		Unit unit;
		while (inRectEnumerator.GetNext(unit))
		{
			if ((playerNum != PlayerNum::PlayerAll) && (unit.OwnerID() != (int)playerNum))
			{
				continue;
			}

			AddVehicleToVector(unit.GetType(), unit.GetCargo());
		}
	}

	void VehicleCounter::Clear()
	{
		VehicleCount = 0;
		VehicleCountVector.clear();
	}

	// PRIVATE FUNCTIONS

	void VehicleCounter::GetVehicleIndices(std::vector<int>& vehicleIndices, map_id vehicleType)
	{
		for (size_t i = 0; i < VehicleCountVector.size(); ++i)
		{
			if (VehicleCountVector[i].UnitType == vehicleType)
			{
				vehicleIndices.push_back(i);
			}
		}
	}

	/*If Unit and cargo combination do not exist in vector, -1 is returned.*/
	int VehicleCounter::GetVehicleIndex(map_id vehicleType, map_id cargoType)
	{
		for (size_t i = 0; i < VehicleCountVector.size(); ++i)
		{
			if (VehicleCountVector[i].UnitType == vehicleType &&
				VehicleCountVector[i].UnitCargo == cargoType)
			{
				return i;
			}
		}

		return -1;
	}

	void VehicleCounter::AddVehicleToVector(map_id vehicleType, map_id cargoType)
	{
		int index = GetVehicleIndex(vehicleType, cargoType);

		if (index == -1)
		{
			UnitCount unitCount;
			unitCount.UnitType = vehicleType;
			unitCount.UnitCargo = cargoType;
			unitCount.Count = 1;

			VehicleCountVector.push_back(unitCount);
		}
		else
		{
			VehicleCountVector[index].Count++;
		}

		if (IsVehicle(vehicleType))
		{
			VehicleCount++;
		}

	}
}