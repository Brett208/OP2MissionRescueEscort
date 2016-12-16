#pragma once

#include "Outpost2DLL\Outpost2DLL.h"

struct ScriptGlobal
{
	bool Multiplayer;

	Trigger DisasterTimeTrig;
	Trigger TrigVictoryWaitTime;
	Trigger TrigFailureWaitTime;

	int MinConvoySurvivingUnits;
	int MinEvacuationTransports;

	Trigger TrigFightGroupNE;
	Trigger TrigFightGroupSE;
	Trigger TrigFightGroupN;
	Trigger TrigFightGroupS;
	Trigger TrigFightGroupNW;
	Trigger TrigFightGroupSW;
	Trigger TrigChaseFightGroup;

	FightGroup FightGroupNE;
	FightGroup FightGroupSE;
	FightGroup FightGroupN;
	FightGroup FightGroupS;
	FightGroup FightGroupNW;
	FightGroup FightGroupSW;
	FightGroup FirstPatrolFightGroup;
	FightGroup FinalTigerFightGroup;
	FightGroup FinalLynxFightGroup;
	FightGroup StaticPantherFightGroup;

	int CurrentWaypointIndex;
	int LastTickMoveWaypointSet;

	FightGroup LynxPatrolFightGroup;

};

// Global instance of ScriptGlobal
extern ScriptGlobal scriptGlobal;