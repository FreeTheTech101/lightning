/*
 * This file (PatchIW3.cpp) is part of Lightning client.
 * Purpose: Main patches for IW3
 * Original author: Archon, 2013-12-20
 * Copyright (C) 2013 triobit
 * --------------------------------------------------------------------------------
 * Lightning is licensed under the GNU General Public License.
 * You can view a copy of the license here: <http://www.gnu.org/licenses/>.
 * --------------------------------------------------------------------------------
 * You are allowed to redistribute Lightning and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 2 of the License, or (at your option) any later version.
 */

#include "StdInc.h"

typedef dvar_t* (__cdecl * Dvar_SetCommand_t)(const char* name, const char* value);
extern Dvar_SetCommand_t Dvar_SetCommand;

void PatchIW3();
void Auth_VerifyIdentity();

CallHook enableConsoleHook;
DWORD enableConsoleHookLoc = 0x4FF1F4;

#pragma optimize("", on)
void __declspec(naked) enableConsoleHookStub()
{
	__asm
	{
		mov eax, 57A730h
		call eax

		jmp enableConsoleHook.pOriginal
	}
}

void __declspec(naked) gameInitHookStub()
{
	// create console
	__asm
	{
		mov eax, 57A730h
		call eax
	}

	// run patches
	__asm call PatchIW3

	// go back to the original function
	__asm
	{
		mov eax, 55E676h
		push ecx
		push ebx
		mov ebx, dword ptr [esp + 8 + 4]
		jmp eax
	}
}
#pragma optimize("", off)

void Sys_RunInit()
{
	DetermineGameFlags();

	if (!GAME_FLAG(GAME_FLAG_DEDICATED))
	{
#ifndef NP_DISABLED
		Auth_VerifyIdentity();
#endif
	}

	// always enable system console, not just if generating reflection probes
	//memset((void*)0x4FF21C, 0x90, 5);

	// disabled as it's already in gameInitHookStub
	//enableConsoleHook.initialize(enableConsoleHookLoc, enableConsoleHookStub);
	//enableConsoleHook.installHook();

	// hooks our stuff in there (by RrrHaa)
	*(BYTE*)0x55E670 = 0xE9;
	*(DWORD*)0x55E671 = (DWORD)gameInitHookStub - 0x55E670 - 5;
	*(BYTE*)0x55E675 = 0x00;
}

bool NP_Initialize();

void PatchIW3_Hello();
void PatchIW3_Console();
void PatchIW3_ServerAuth();
void PatchIW3_GUIDValidation();
void PatchIW3_VA();

void PatchIW3()
{
	HookFunctionBase::RunAll();

#ifndef NP_DISABLED
	if (!NP_Initialize())
	{
		TerminateProcess(GetCurrentProcess(), 0);
	}
#endif

	// do not register lan_netauthorize
	memset((void*)0x507D80, 0x90, 5);

	// do not validate cd keys (by RrrHaa)
	// TODO: NP ticket preauthentication
	*(BYTE*)0x469B46 = 0xEB;
	*(BYTE*)0x47121D = 0xEB;

	// disable punkbuster
	*(DWORD*)0x545C55 = (DWORD)""; // startpb_popmenu
	memset((void*)0x5776BA, 0x90, 5); // PB check #1
	memset((void*)0x5776CF, 0x90, 5); // PB check #2
	//memset((void*)0x5776CA, 0x90, 5); // error msg #1 (PB not loaded)
	//memset((void*)0x5776EC, 0x90, 5); // error msg #2 (PB not loaded)

	if (GAME_FLAG(GAME_FLAG_DEDICATED))
	{
		// fix needed
		//PatchIW3_Console();
		PatchIW3_ServerAuth();
		PatchIW3_GUIDValidation();
	}
	else
	{
		//PatchIW3_UILoading();
	}

	// UI localized strings
	//UI_AddString("MENU_JOIN_GAME", "Server Browser");
	//UI_AddString("MENU_JOIN_SERVER_CAP", "SERVER BROWSER");
	//UI_AddString("MENU_START_NEW_SERVER", "Private Match");

	PatchIW3_Hello();
	PatchIW3_VA();
}

CallHook helloHook;
DWORD helloHookLoc = 0x4FF1E7;

CallHook helloHook2;
DWORD helloHook2Loc = 0x4FC9B6;

void HelloIW(int type)
{
    GameEngine::Com_Printf(type, "%s built on %s %s\n", VERSIONSTRING, __DATE__, __TIME__);
    GameEngine::Com_Printf(type, "http://triobit.net\n");
}

#pragma optimize("", off)
void __declspec(naked) HelloHookStub()
{
    HelloIW(0);

    __asm retn
}

void __declspec(naked) HelloHook2Stub()
{
    HelloIW(16);

    __asm jmp helloHook2.pOriginal
}
#pragma optimize("", on)

void PatchIW3_Hello()
{
    helloHook.initialize(helloHookLoc, HelloHookStub);
    helloHook.installHook();

    helloHook2.initialize(helloHook2Loc, HelloHook2Stub);
    helloHook2.installHook();
}

StompHook vaHook;
DWORD vaHookLoc = 0x571E30;

void PatchIW3_VA()
{
	vaHook.initialize(vaHookLoc, va);
	vaHook.installHook();
}