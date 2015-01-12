#include "StdInc.h"

static HookFunction hookFunction([] ()
{
	// don't show splash screen
	hook::nop(0x57761C, 5);

	// remove improper quit message
	*(WORD*)0x577415 = 0xEB50;

    // remove computer changed message
	*(WORD*)0x576775 = 0xEB2F;
});