#include "StdInc.h"

static HookFunction hookFunction([] ()
{
	// master server
	strcpy((char*)0x6D0554, DPMASTER);

	// return 'clients' key in all cases
	*(WORD*)0x531C8D = 0x9090;

	// hearthbeat tag
	hook::charptr(0x53357F, "LN");
	hook::charptr(0x5335B9, "LN");
});