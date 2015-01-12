#include "StdInc.h"

static HWND WINAPI CreateWindowExAWrap_WC(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	if (strcmp(lpClassName, "CoD4 WinConsole"))
	{
		return CreateWindowExA(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
	}

	return CreateWindowExW(dwExStyle, L"CoD4 WinConsole", L"Lightning Console", dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

static HWND WINAPI CreateWindowExAWrap_G(DWORD dwExStyle, LPCSTR lpClassName, LPCSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam)
{
	return CreateWindowExW(dwExStyle, L"CoD4", L"Lightning", dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
}

static HookFunction hookFunction([] ()
{
	// createwindowexa on winconsole
	static DWORD wcCWEx = (DWORD)CreateWindowExAWrap_WC;
	static DWORD wcGEx = (DWORD)CreateWindowExAWrap_G;
	*(DWORD**)0x57A559 = &wcCWEx;
	*(DWORD**)0x5F49CC = &wcGEx;

	// displayed build tag in UI code
	hook::charptr(0x5434BC, VERSIONSTRING);

	// console '%s: %s> ' string
	hook::charptr(0x46060F, "IW3 MP> ");

	// console version string
	hook::charptr(0x461B84, VERSIONSTRING " " BUILDHOST " (built " __DATE__ " " __TIME__ ")");

	// version string
	hook::charptr(0x4FF1E1, VERSIONSTRING " (built " __DATE__ " " __TIME__ ")\n");

	// set fs_basegame to (will apply before fs_game)
	hook::charptr(0x55E4C9, FS_BASEGAME);

	// server list cache name
	hook::charptr(0x4764D9, FS_BASEGAME "/ServerCache.dat");
	hook::charptr(0x476545, FS_BASEGAME "/ServerCache.dat");
});