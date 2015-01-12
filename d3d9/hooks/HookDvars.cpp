#include "StdInc.h"

static HookFunction hookFunction([] ()
{
	// unlock cg_fovScale
	*(BYTE*)0x43AE1C = DVAR_FLAG_SAVED;

	// write protect cl_punkbuster
	*(BYTE*)0x52FDE5 = DVAR_FLAG_WRITEPROTECTED;

	// unlock r_filmUseTweaks
	*(BYTE*)0x62C8AA = DVAR_FLAG_SAVED;

	// disable "dvar set" string in console log
	hook::nop(0x56B203, 5);

	// disable unknown dvar warning
	hook::nop(0x56D61A, 5);
	
	// uncheat r_fullbright and add archive flags
	*(BYTE*)0x62A0B1 = DVAR_FLAG_SAVED;
});