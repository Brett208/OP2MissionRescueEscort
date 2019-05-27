#include "InitializeScenario.h"
#include <OP2Helper/OP2Helper.h>
#include <Outpost2DLL/Outpost2DLL.h>

// Required data exports  (Description, Map, TechTree, GameType, NumPlayers)
ExportLevelDetailsEx("Campaign - Ply, Pursued, Ep 3 - Rescue Escort", "RescueEscort.map", "PursuedTechTree.txt", MissionTypes::Colony, 3, 12, true);

extern void ShowBriefing();

static const bool Multiplayer = false; // Determines if the scenario is built as a colony game or as multiplayer.

Export int InitProc()
{
	ShowBriefing();

	InitializeScenario(Multiplayer);

	return true; // Level loaded successfully
}
