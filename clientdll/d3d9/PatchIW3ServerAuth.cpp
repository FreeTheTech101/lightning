/*
 * This file (PatchIW3ServerAuth.cpp) is part of Lightning client.
 * Purpose: overriding Sys_IsLocalAddress to skip AuthServer authentication for clients
 * Original author: ArmedGuy
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

StompHook authServerHook;
DWORD authServerHookLoc = 0x531C83;

#pragma optimize("", off)
__declspec(naked) void AuthServerHookStub()
{
	__asm
	{
		sub esp, 0x14;
		cmp dword ptr ss:[esp+0x1c], MASTERSERVERIP;
		je ismasterserver;
		add esp, 0x14;
		mov eax, 0;
		retn;
ismasterserver:
		add esp, 0x14;
		mov eax, 1;
		retn;
	}
}
#pragma optimize("", on)

void PatchIW3_ServerAuth()
{
	authServerHook.initialize(authServerHookLoc, AuthServerHookStub);
	authServerHook.installHook();
}