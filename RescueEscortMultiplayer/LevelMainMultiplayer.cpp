#include "InitializeScenario.h"
#include <OP2Helper/OP2Helper.h>
#include <HFL\Source\HFL.h>
#include <Outpost2DLL/Outpost2DLL.h>

// Required data exports  (Description, Map, TechTree, GameType, NumPlayers)
ExportLevelDetailsEx("2P, Convoy, 'Rescue Escort'", "RescueEscort.map", "PursuedTechTree.txt", MissionTypes::MultiLandRush, 2, 12, true);

// Allows an enemy AI in a multiplayer scenario.
struct SDescBlockEx {
	int unk0;
	int unk1;
	int unk2;
	int unk3;
	int unk4;
	int unk5;
	int unk6;
	int unk7;
};

SCRIPT_API SDescBlockEx DescBlockEx = { 1, 0, 0, 0, 0, 0, 0, 0 };

//extern void ShowBriefing();

static const bool Multiplayer = true; // Determines if the scenario is built as a colony game or as multiplayer.

Export int InitProc()
{
	HFLInit();

	//ShowBriefing();

	InitializeScenario(Multiplayer);

	return true;	// Level loaded successfully
}
