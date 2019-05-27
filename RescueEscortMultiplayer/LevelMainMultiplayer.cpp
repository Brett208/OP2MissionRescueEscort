#include "InitializeScenario.h"
#include <OP2Helper/OP2Helper.h>
#include <HFL/Source/HFL.h>
#include <Outpost2DLL/Outpost2DLL.h>

ExportLevelDetailsFullEx("2P, Convoy, 'Rescue Escort'", "RescueEscort.map", "PursuedTechTree.txt", MultiLandRush, 2, 12, true, 1);

//extern void ShowBriefing();

static const bool Multiplayer = true; // Determines if the scenario is built as a colony game or as multiplayer.

Export int InitProc()
{
	//ShowBriefing();

	InitializeScenario(Multiplayer);

	return true;	// Level loaded successfully
}
