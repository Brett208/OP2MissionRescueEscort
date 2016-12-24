#include "InitializeScenario.h"
#include <OP2Helper/OP2Helper.h>
#include <Outpost2DLL/Outpost2DLL.h>

// Required data exports  (Description, Map, TechTree, GameType, NumPlayers)
ExportLevelDetailsEx("Campaign - Ply, Pursued, Ep 3, Rescue Escort", "RescueEscort.map", "PursuedTechTree.txt", MissionTypes::Colony, 3, 12, true);

extern void ShowBriefing();

static const bool Multiplayer = false; // Determines if the scenario is built as a colony game or as multiplayer.

Export int InitProc()
{
	HFLInit();

	ShowBriefing();

	InitializeScenario(Multiplayer);

	return true; // Level loaded successfully
}





// Places a safeRectangle centered on all command centers currently in game.
void AutoSetBaseSafeRects(int safeAreaWidth, int safeAreaHeight)
{
	for (int i = 0; i < TethysGame::NoPlayers(); i++)
	{
		PlayerBuildingEnum playerBuildingEnum(i, map_id::mapCommandCenter);

		Unit unit;
		while (playerBuildingEnum.GetNext(unit))
		{
			LOCATION loc = unit.Location();
			MAP_RECT safeRect = MAP_RECT(loc.x - safeAreaWidth / 2, loc.y - safeAreaHeight / 2, loc.x + 30, loc.y + 30);

			disasterHelper.AddSafeRect(safeRect);
		}
	}
}



//NOTE: Sets mapWidth as 512 instead of 256. MapWidth appears to be set correctly.
//disasterHelper.SetMapProperties(GameMapEx::GetMapWidth(), GameMapEx::GetMapHeight(), false);