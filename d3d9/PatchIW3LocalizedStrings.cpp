/*
 * This file (PatchIW3LocalizedStrings.cpp) is part of Lightning client.
 * Purpose: Custom UI localized strings.
 * Original author: RrrHaa, 2014-05-18
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

DWORD uiretn = 0x54ACA5;

void* DetourFunction(BYTE *source, const BYTE *destination, const int length);

const char*(*tTranslateString)(const char*);

std::map<const char*, const char*> uiStrings;
typedef std::map<const char*, const char*>::iterator uiStringsItr;

void UI_AddString(const char* str, const char* replc)
{
	if(str && replc)
	{
		uiStrings.insert(std::make_pair(str, replc));
	}
}

void UI_RemoveString(const char* str)
{
	if(str)
	{
		for(uiStringsItr itr = uiStrings.begin();
			itr != uiStrings.end(); itr++)
		{
			if(_stricmp(itr->first, str) == 0)
			{
				uiStrings.erase(itr++);
			}
			else
			{
				++itr;
			}
		}
	}
}

bool UI_IsStringAvailable()
{
	return !uiStrings.empty();
}

bool UI_CleanStringsList()
{
	if(!UI_IsStringAvailable())
	{
		return false;
	}

	uiStrings.clear();
	return true;
}

const char* Hook_TranslateString(const char* str)
{
	if(UI_IsStringAvailable())
	{
		for(uiStringsItr itr = uiStrings.begin();
			itr != uiStrings.end(); itr++)
		{
			if(_stricmp(itr->first, str) == 0)
			{
				return itr->second;
			}
		}
	}

	return tTranslateString(str);
}

__declspec(naked) void Stub_TranslateString()
{
	__asm
	{
		push eax
		call Hook_TranslateString
		add esp, 4

		test al, al
		retn
	}
}

void PatchIW3_LocalizedStrings()
{
	tTranslateString = (const char*(*)(const char*))
		DetourFunction((PBYTE)0x54ACA0, (PBYTE)Stub_TranslateString, 5);
}