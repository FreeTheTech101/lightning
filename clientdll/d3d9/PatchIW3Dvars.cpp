/*
 * This file (PatchIW3Dvars.cpp) is part of Lightning client.
 * Purpose: dvar flags changing and more
 * Original author: Archon, 2013-12-22
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
Dvar_SetCommand_t Dvar_SetCommand = (Dvar_SetCommand_t)0x56D2B0;

void PatchIW3_Dvars()
{
	// unlock cg_fovScale
	*(BYTE*)0x43AE1C = DVAR_FLAG_SAVED;

	// write protect cl_punkbuster
	*(BYTE*)0x52FDE5 = DVAR_FLAG_WRITEPROTECTED;

	// unlock r_filmUseTweaks
	*(BYTE*)0x62C8AA = DVAR_FLAG_SAVED;

	// disable "dvar set" string in console log
	memset((void*)0x56B203, 0x90, 5);

	// disable unknown dvar warning
	memset((void*)0x56D61A, 0x90, 5);

	// uncheat r_fullbright and add archive flags
	*(BYTE*)0x62A0B1 = DVAR_FLAG_SAVED;
}