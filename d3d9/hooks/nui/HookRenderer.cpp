#include "StdInc.h"
#include "NUI.h"

void Bla()
{

}

CallHook initNUIHook; // somewhere in R_BeginRegistration or so
DWORD initNUIHookLoc = 0x630740;

void __declspec(naked) InitNUIHookStub()
{
	__asm
	{
		call initNUIHook.pOriginal
		
		jmp Bla

		//jmp NUI_Init
	}
}

static HookFunction hookFunction([]()
{
	//initNUIHook.initialize(initNUIHookLoc, InitNUIHookStub);
	//initNUIHook.installHook();
});