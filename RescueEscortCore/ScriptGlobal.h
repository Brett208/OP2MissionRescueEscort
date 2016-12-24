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
	Trigger TrigFightGroupS2;
	Trigger TrigFightGroupNW;
	Trigger TrigFightGroupNW2;
	Trigger TrigFightGroupSW;
	Trigger TrigChaseFightGroup;

	FightGroup FightGroupNE;
	FightGroup FightGroupSE;
	FightGroup FightGroupN;
	FightGroup FightGroupS;
	FightGroup FightGroupS2;
	FightGroup FightGroupNW;
	FightGroup FightGroupNW2;
	FightGroup FightGroupSW;
	FightGroup FinalTigerFightGroup;
	FightGroup FinalLynxFightGroup;
	
	FightGroup FirstPatrolFightGroup;
	FightGroup EastPatrolFightGroup;
	FightGroup CenterPatrolFightGroup;
	FightGroup WestPatrolFightGroup;
	

	int CurrentWaypointIndex;
	int LastTickMoveWaypointSet;

	

};

// Global instance of ScriptGlobal
extern ScriptGlobal scriptGlobal;