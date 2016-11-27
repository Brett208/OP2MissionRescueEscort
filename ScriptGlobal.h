#pragma once

#include "Outpost2DLL\Outpost2DLL.h"

struct ScriptGlobal
{
	Trigger TrigVictoryWaitTime;
	Trigger TrigFailureWaitTime;

	int MinConvoySurvivingUnits;
	int MinEvacuationTransports;

	Trigger TrigFightGroup1;
	Trigger TrigFightGroup2;
	Trigger TrigFightGroup3;
	Trigger TrigFinalfightGroup;

	FightGroup AcidCloudSneakFightGroup;
	FightGroup FightGroup1;
	FightGroup FightGroup2;
	FightGroup FightGroup3;
	FightGroup FinalFightGroup;

};

// Global instance of ScriptGlobal
extern ScriptGlobal scriptGlobal;