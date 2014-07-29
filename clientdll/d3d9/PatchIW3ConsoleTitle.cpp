/*
 * This file (PatchIW3ConsoleTitle.cpp) is part of Lightning client.
 * Purpose: console title changing for dedicated servers
 * Original author: Pigophone, 2012-02-15 (copied from dediclient)
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

dvar_t** sv_hostname = (dvar_t**)0x185C424;

/*
============
StripColors
============
*/

#define Q_IsColorString( p )  ( ( p ) && *( p ) == '^' && *( ( p ) + 1 ) && isdigit( *( ( p ) + 1 ) ) ) // ^[0-9]

void StripColors(const char* in, char* out, int max)
{
	max--; // \0
	int current = 0;
	while (*in != 0 && current < max)
	{
		if (!Q_IsColorString(in))
		{ // u so color
			*out = *in;
			out++;
			current++;
		}
		else
		{
			*in++; // move THE in pointer one more along to remove THE digit character
				   // not ntauthority lol
		}
		*in++;
	}
	*out = '\0';
}

/* #define CONSOLE_WINDOW *(HWND*)0xCC1AD98
void SetWindowTitle()
{
	if (!GAME_FLAG(GAME_FLAG_CONSOLE) || CONSOLE_WINDOW == NULL)
	{
		return;
	}
		
	if (!(*sv_hostname))
	{
		SetWindowText(CONSOLE_WINDOW, "CoD4 Console");
		return;
	}

	char cleaned[1024];
	StripColors((*sv_hostname)->current.string, cleaned, sizeof(cleaned));
	const char* title = va("CoD4 Console - %s", cleaned);
	strcpy_s(cleaned, 1024, title);
	SetWindowText(CONSOLE_WINDOW, cleaned);
}*/