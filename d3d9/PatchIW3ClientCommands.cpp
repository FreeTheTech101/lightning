/*
 * This file (PatchIW3ClientCommands.cpp) is part of Lightning client.
 * Purpose: hooking existing commands and providing custom functionality
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

CallHook hKickHook;
CallHook hRemoteKickHook;

DWORD pKickCommand = 0x52802E;
DWORD pRemoteKickCommand = 0x52817B;

void KickCommandHook(char d1, char d2)
{
	GameEngine::Com_Printf(0, "Usage: kick <player> [reason]\n");
}

void PatchIW3_ClientCommands()
{
	hKickHook.initialize(pKickCommand, KickCommandHook);
    hKickHook.installHook();

    hRemoteKickHook.initialize(pRemoteKickCommand, KickCommandHook);
    hRemoteKickHook.installHook();
}