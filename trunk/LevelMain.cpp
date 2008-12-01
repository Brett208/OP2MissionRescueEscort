
// For testing individual sub-header-file includes
//#include <Enumerators.h>
//#include <Enums.h>
//#include <GameMap.h>
//#include <Globals.h>
//#include <Groups.h>
//#include <MapIdEnum.h>
//#include <NonExportedEnums.h>
//#include <Player.h>
//#include <RequiredExports.h>
//#include <ScStub.h>
//#include <Structs.h>
//#include <TethysGame.h>
//#include <Trigger.h>
//#include <Unit.h>
//#include <UnitBlock.h>

#include <Outpost2DLL.h>	// Main Outpost 2 header to interface with the game
#include <OP2Helper.h>		// Optional header to make level building easier



// Note: These exports are required by Outpost2.exe from every level
//		 DLL. They give values for the map and tech trees used by the
//		 level and a description to place in the level listbox. The
//		 last export is used to define characteristics of the level.
//		 See RequiredExports.h for more details.
//		 ** Be sure to set these when you build your own level**

Export char MapName[]		= "on6_01.map";							// The .map file used for this level
Export char LevelDesc[]		= "6 Player, LastOne, '<map name>' map";// Description appearing in the game list box
Export char TechtreeName[]	= "MULTITEK.TXT";						// File to use for the tech tree
Export SDescBlock DescBlock	= { MultiLastOneStanding, 6, 12, 0 };	// Important level details


// Note: The following function is called once by Outpost2.exe when the
//		 level is first initialized. This is where you want to create
//		 all the initial units and structures as well as setup any 
//		 map/level environment settings such as day and night.
// Note: Returns true if level loaded successfully and is playable, false to abort
Export int InitProc()
{
	// **TODO**: Add your own code here.
	return true;	// Level loaded successfully
}


// Note: The following function seems to be intended for use in
//		 controlling an AI. It is called once every game cycle. 
//		 Use it for whatever code needs to run on a continual basis.
// Note: The standard level DLLs released by Sierra leave this function
//		 empty and handle all AI controls through triggers.

Export void AIProc() 
{
}


// Note: This function is called by Outpost2.exe to obtain a description
//		 of a buffer that is saved to saved game files. Outpost2.exe
//		 calls this function and passes it a pointer to a structure
//		 which describes this buffer. This function is required to set
//		 the fields of this structure. If no buffer needs to be saved
//		 to a saved game file, then the buffer pointer needs to be set
//		 to 0, and the length should also be set to 0.
// Note: This function is called once when the DLL is first initialized.
//		 This means that all data to be saved must have space reserved
//		 ahead of time at the start of the level. (Static sized storage)
//		 In other words, there is no way to dynamically grow the size of
//		 the buffer if more space is needed than originally specified.
// Note: You can probably stretch the above limitation by saving the
//		 pointer to the buffer description passed by Outpost2.exe. This
//		 may allow you to increase the buffer size dynamically but the
//		 idea is yet untested. Keep in mind that you have no idea when
//		 a game may be saved (or just loaded). 

Export void __cdecl GetSaveRegions(struct BufferDesc &bufDesc)
{
	bufDesc.bufferStart = 0;	// Pointer to a buffer that needs to be saved
	bufDesc.length = 0;			// sizeof(buffer)
}





// Note: These last two functions aren't absolutely required by a level
//		 but they found in almost all DLLs anyways.


// Note: This export usually exists, but does nothing other than return 0.
//		 It's use may have been for checking for victory/failure conditions
//		 that are not easily checked for by using triggers.

Export int StatusProc()
{
	return 0; // must return 0
}


// Note: This is a trigger callback function. This function is
//		 intentionally left empty and is used as the trigger
//		 callback function for triggers that don't want or need
//		 any special callback function.
// Note: The use of SCRIPT_API is used by all trigger functions
//		 to ensure they are exported correctly. (Although, 
//		 technically it's not needed in this case since this
//		 function has a function prototype defined in 
//		 RequiredExports.h which contains the SCRIPT_API macro
//		 in it. However, most other trigger callback functions
//		 won't have a function prototype anywhere (and you really
//		 don't need to declare a function prototype since you
//		 should never be calling a callback function yourself)
//		 so you should use the SCRIPT_API macro when you define
//		 the function.
//		 Might as well set a good example. =)

Export void NoResponseToTrigger()
{
}


