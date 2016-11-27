#pragma once

#include "ScriptGlobal.h"
#include "VehicleCounter.h"
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
	vehicleCounter.PullVehiclesFromPlayer(PlayerUnitEnum(Player2));

	if (vehicleCounter.GetCombatVehicleCount() < scriptGlobal.MinConvoySurvivingUnits)
	{
		return true;
	}

	if (vehicleCounter.GetVehicleCount(map_id::mapEvacuationTransport) < scriptGlobal.MinEvacuationTransports)
	{
		return true;
	}

	return false;
}

bool IsScenarioWon()
{
	vehicleCounter.Clear();
	vehicleCounter.PullVehiclesFromPlayer(PlayerUnitEnum(Player2));
	int convoyVehicleCount = vehicleCounter.GetCombatVehicleCount();


	vehicleCounter.Clear();
	MAP_RECT convoyFinishRect(LOCATION(X_, Y_), LOCATION(X_, Y_));
	vehicleCounter.PullVehiclesFromRectangle(Player2, InRectEnumerator(convoyFinishRect));

	//Check if all remaining convoy vehicles have made it to the objective area.
	return vehicleCounter.GetVehicleCount() == convoyVehicleCount;
}

char* FormatVictoryConditionMessage(PlayerDifficulty playerDifficulty)
{
	switch (playerDifficulty)
	{
	case PlayerDifficulty::DiffEasy:
		return "Extract at least 2 evacuation transports and 50% of starting convoy units. Leave no functioning convoy unit behind.";
	case PlayerDifficulty::DiffNormal:
		return "Extract at least 3 evacuation transports and 70% of starting convoy units. Leave no functioning convoy unit behind.";
	default:
		return "Extract all evacuation transports and 80% of starting convoy units. Leave no functioning convoy unit behind.";
	}
}

void SetVictoryConvoyCounts(PlayerDifficulty playerDifficulty, int initialConvoyVehicleCount)
{
	switch (playerDifficulty)
	{
	case PlayerDifficulty::DiffEasy:
		scriptGlobal.MinConvoySurvivingUnits = (int)(initialConvoyVehicleCount * 0.5);
		scriptGlobal.MinEvacuationTransports = 2;
		return;
	case PlayerDifficulty::DiffNormal:
		scriptGlobal.MinConvoySurvivingUnits = (int)(initialConvoyVehicleCount * 0.7);
		scriptGlobal.MinEvacuationTransports = 3;
		return;
	default:
		scriptGlobal.MinConvoySurvivingUnits = (int)(initialConvoyVehicleCount * 0.8);
		scriptGlobal.MinEvacuationTransports = 4;
		return;
	}
}