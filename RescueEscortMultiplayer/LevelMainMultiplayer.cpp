#include "InitializeScenario.h"
#include <OP2Helper/OP2Helper.h>
#include <HFL\Source\HFL.h>
#include <Outpost2DLL/Outpost2DLL.h>

// Required data exports  (Description, Map, TechTree, GameType, NumPlayers)
ExportLevelDetailsEx("2P, Convoy, 'Rescue Escort'", "RescueEscort.map", "PursuedTechTree.txt", MissionTypes::MultiLandRush, 3, 12, true);
//Original map: ply07.map

//extern void ShowBriefing();

static const bool Multiplayer = false; // Determines if the scenario is built as a colony game or as multiplayer.

Export int InitProc()
{
	HFLInit();

	//ShowBriefing();

	InitializeScenario(Multiplayer);

	return true;	// Level loaded successfully
}