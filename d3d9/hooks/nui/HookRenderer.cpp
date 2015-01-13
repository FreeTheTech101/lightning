#include "StdInc.h"
#include "NUI.h"

CallHook initNUIHook; // somewhere in R_BeginRegistration or so
DWORD initNUIHookLoc = 0x5F3E82;

void __declspec(naked) InitNUIHookStub()
{
	__asm
	{
		call initNUIHook.pOriginal
		jmp NUI_Init
	}
}

// additional FS threads
bool _workaroundThreadSync = false;

int FS_GetHandleOffset(int thread)
{
	switch (thread)
	{
	case 0:
		if (_workaroundThreadSync)
		{
			return 21;
		}

		return 1;
	case 1:
		return 49;
	case 2:
		return 61;
	case 3:
		return 62;
	case 4:
		return 63;
	case 5: // custom
		return 31;
	default:
		return 62;
	}
}

int FS_GetHandleCount(int thread)
{
	switch (thread)
	{
	case 0:
		return 30;
	case 1:
		return 12;
	case 5:
		return 18;
	default:
		return 1;
	}
}

void __declspec(naked) FS_GetHandleHookStub()
{
	__asm
	{
		push ebx
		push ebp
		mov ebp, [esp + 8 + 4]

		push ebp
		call FS_GetHandleOffset
		mov ebx, eax

		call FS_GetHandleCount
		pop ebp

		push 439E2Eh
		retn
	}
}

static HookFunction hookFunction([]()
{
	initNUIHook.initialize(initNUIHookLoc, InitNUIHookStub);
	initNUIHook.installHook();

	hook::call(0x55AED0, FS_GetHandleHookStub);
});