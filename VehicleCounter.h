#pragma once

#pragma once

#include "OP2Helper\ColonyType.h"
#include "Outpost2DLL\Outpost2DLL.h"
#include <vector>

//Note: Currently only PlayerBuildingEnum returns buildings, so do not try and use this class to count buildings.
namespace UnitHelper
{
	struct UnitCount
	{
		map_id UnitType;
		map_id UnitCargo;
		int Count;
	};

	class VehicleCounter
	{
	public:
		int GetVehicleCount()
		{
			return VehicleCount;
		}

		int GetVehicleCount(map_id vehicleType);
		int GetVehicleCount(map_id vehicleType, map_id cargoType);
		int GetCombatVehicleCount();
		void PullVehiclesFromRectangle(PlayerNum playerNum, InRectEnumerator inRectEnumerator);
		void PullVehiclesFromPlayer(PlayerUnitEnum playerUnitEnum);
		void Clear();

	private:
		int VehicleCount = 0;
		std::vector<UnitCount> VehicleCountVector;

		void AddVehicleToVector(map_id vehicleType, map_id cargoType);
		void GetVehicleIndices(std::vector<int>& VehicleIndices, map_id vehicleType);
		int GetVehicleIndex(map_id vehicleType, map_id cargoType);
	};
}