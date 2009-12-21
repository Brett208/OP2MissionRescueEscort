#include <Outpost2DLL/Outpost2DLL.h>	// Main Outpost 2 header to interface with the game
#include <OP2Helper/OP2Helper.h>		// Optional header to make level building easier


// Required data exports  (Description, Map, TechTree, GameType, NumPlayers)
ExportLevelDetails("6 Player, LastOne, '<map name>' map", "on6_01.map", "MULTITEK.TXT", MultiLastOneStanding, 6)


struct ScriptGlobal
{
};
ScriptGlobal scriptGlobal;


Export int InitProc()
{
	return true;	// Level loaded successfully
}


Export void AIProc() 
{
}

Export void __cdecl GetSaveRegions(BufferDesc& bufferDesc)
{
	// Buffer for Saved Game files
	bufferDesc.bufferStart = &scriptGlobal;
	bufferDesc.length = sizeof(scriptGlobal);
}

Export void NoResponseToTrigger()
{
}


