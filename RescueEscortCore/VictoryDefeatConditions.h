#pragma once

#include "ScriptGlobal.h"
#include "VehicleCounter.h"
#include "OP2Helper\OP2Helper.h"
#include "Outpost2DLL\Outpost2DLL.h"

UnitHelper::VehicleCounter vehicleCounter;

void CreateTimeVictoryCondition(Trigger& trigger, Trigger& victoryTrigger, int time, char* missionObjective)
{
	trigger = CreateTimeTrigger(false, false, time, "NoResponseToTrigger");
	victoryTrigger = CreateVictoryCondition(true, false, trigger, missionObjective);
}

bool IsScenarioLost()
{
	vehicleCounter.Clear();
	vehicleCounter.PullVehiclesFromPlayer(Player1);

	if (vehicleCounter.NonCombatVehicleCount() < scriptGlobal.MinConvoySurvivingUnits) {
		return true;
	}

	if (vehicleCounter.GetVehicleCount(map_id::mapEvacuationTransport) < scriptGlobal.MinEvacuationTransports) {
		return true;
	}

	if (!vehicleCounter.AllConVecsHaveKits()) {
		return true;
	}

	if (!vehicleCounter.AllTrucksHaveCargo()) {
		return true;
	}

	if (ExtPlayer[1].GetNumBuildingsBuilt() > 0) {
		return true;
	}

	return false;
}

bool IsScenarioWon()
{
	vehicleCounter.Clear();
	vehicleCounter.PullVehiclesFromPlayer(Player1);
	int convoyVehicleCount = vehicleCounter.CombatVehicleCount();


	vehicleCounter.Clear();
	MAP_RECT convoyFinishRect(LOCATION(X_, Y_), LOCATION(X_, Y_));
	vehicleCounter.PullVehiclesFromRectangle(Player1, convoyFinishRect);

	//Check if all remaining convoy vehicles have made it to the objective area.
	return vehicleCounter.GetVehicleCount() == convoyVehicleCount;
}

void InitializeVictoryConditions(int evacConvoyNonCombatVehicleCount)
{
	Trigger victoryTrigger;

	scriptGlobal.MinConvoySurvivingUnits = (int)(evacConvoyNonCombatVehicleCount * 0.7);
	scriptGlobal.MinEvacuationTransports = 3;

	char* victoryConditionText = "Extract at least 3 evac transports and 70% of convoy non-combat units. Leave no functioning convoy unit behind.";
	
	CreateTimeVictoryCondition(scriptGlobal.TrigVictoryWaitTime, victoryTrigger, 90, victoryConditionText);

	scriptGlobal.TrigFailureWaitTime = CreateTimeTrigger(false, false, 90, "NoResponseToTrigger");
	CreateFailureCondition(true, true, scriptGlobal.TrigFailureWaitTime, "Ignored");
}
