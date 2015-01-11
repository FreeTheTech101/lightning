/*
 * This file (PatchIW3Branding.cpp) is part of Lightning client.
 * Purpose: branding for IW3
 * Original author: NTAuthority, 2011-06-09
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

typedef void* (__cdecl * R_RegisterFont_t)(const char* asset, int);
R_RegisterFont_t R_RegisterFont = (R_RegisterFont_t)0x5F1EC0;

void DrawText(char* text, void* font, float* color, float x, float y, float sizeX, float sizeY, float f1, float f2)
{
	DWORD dwCall = 0x5F6B00;

	__asm
	{
		push 0
		push f2
		push f1
		push sizeY
		push sizeX
		push y
		push x 
		push font
		push 0x7FFFFFFF
		push text
		mov ecx, color
		call [dwCall]
		add esp, 0x28
	}
}

CallHook updateScreenHook;
DWORD updateScreenHookLoc = 0x475052;

void DrawBranding()
{
	float size = 1.0f;
	void* font = R_RegisterFont("fonts/bigFont", 7);

	float color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

	DrawText("^1Lightning / alpha build " BUILDNUMBER_STR, font, color, 150, 250, size, size, 0.0f, 0.0f);
}

#pragma optimize("", off)
void __declspec(naked) UpdateScreenHookStub()
{
	__asm
	{
		call DrawBranding
		jmp updateScreenHook.pOriginal
	}
}
#pragma optimize("", on)

HWND WINAPI CreateWindowExAWrap_WC(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	if (strcmp(lpClassName, "CoD4 WinConsole"))
	{
		return CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	}

	return CreateWindowExW(dwExStyle, L"CoD4 WinConsole", L"Lightning Console", dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

HWND WINAPI CreateWindowExAWrap_G(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	return CreateWindowExW(dwExStyle, L"CoD4", L"Lightning", dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

void PatchIW3_Branding()
{
	// hook SCR_UpdateFrame call in SCR_UpdateScreen
	updateScreenHook.initialize(updateScreenHookLoc, UpdateScreenHookStub);
	updateScreenHook.installHook();

	// createwindowexa on winconsole
	static DWORD wcCWEx = (DWORD)CreateWindowExAWrap_WC;
	static DWORD wcGEx = (DWORD)CreateWindowExAWrap_G;
	*(DWORD**)0x57A559 = &wcCWEx;
	*(DWORD**)0x5F49CC = &wcGEx;

	// displayed build tag in UI code
	*(DWORD*)0x5434BC = (DWORD)VERSIONSTRING;

	// console '%s: %s> ' string
	*(DWORD*)0x46060F = (DWORD)("IW3 MP> ");

	// console version string
	*(DWORD*)0x461B84 = (DWORD)(VERSIONSTRING " " BUILDHOST " (built " __DATE__ " " __TIME__ ")");

	// version string
	*(DWORD*)0x4FF1E1 = (DWORD)(VERSIONSTRING " (built " __DATE__ " " __TIME__ ")\n");

	// set fs_basegame to (will apply before fs_game)
	*(DWORD*)0x55E4C9 = (DWORD)FS_BASEGAME;

	// server list cache name
	*(DWORD*)0x4764D9 = (DWORD)(FS_BASEGAME "/ServerCache.dat");
	*(DWORD*)0x476545 = (DWORD)(FS_BASEGAME "/ServerCache.dat");
}