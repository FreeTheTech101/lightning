// ==========================================================
// project 'secretSchemes'
// 
// Component: clientdll
// Sub-component: steam_api
// Purpose: Manages the initialization of iw4cli.
//
// Initial author: NTAuthority
// Started: 2011-05-04
// ==========================================================

#include "StdInc.h"

HMODULE d3d9_dll;

//#if LINUX
//#pragma comment(linker,"/FIXED /BASE:0x8000000 /MERGE:.rdata=.text /SECTION:.text,EWR")
//#endif

static BYTE originalCode[5];
static PBYTE originalEP = 0;

//void HideCode_FindDeviceIoControl();

void Main_UnprotectModule(HMODULE hModule)
{
	PIMAGE_DOS_HEADER header = (PIMAGE_DOS_HEADER)hModule;
	PIMAGE_NT_HEADERS ntHeader = (PIMAGE_NT_HEADERS)((DWORD)hModule + header->e_lfanew);

	// unprotect the entire PE image
	SIZE_T size = ntHeader->OptionalHeader.SizeOfImage;
	DWORD oldProtect;
	VirtualProtect((LPVOID)hModule, size, PAGE_EXECUTE_READWRITE, &oldProtect);
}

void Main_DoInit()
{
	// unprotect our entire PE image
	HMODULE hModule;
	if (SUCCEEDED(GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCSTR)Main_DoInit, &hModule)))
	{
		Main_UnprotectModule(hModule);
	}

	//HideCode_FindDeviceIoControl();
	Sys_RunInit();

	// return to the original EP
	memcpy(originalEP, &originalCode, sizeof(originalCode));
	__asm jmp originalEP
}

void Main_SetSafeInit()
{
	// find the entry point for the executable process, set page access, and replace the EP
	HMODULE hModule = GetModuleHandle(NULL); // passing NULL should be safe even with the loader lock being held (according to ReactOS ldr.c)

	if (hModule)
	{
		PIMAGE_DOS_HEADER header = (PIMAGE_DOS_HEADER)hModule;
		PIMAGE_NT_HEADERS ntHeader = (PIMAGE_NT_HEADERS)((DWORD)hModule + header->e_lfanew);

		Main_UnprotectModule(hModule);

		// back up original code
		PBYTE ep = (PBYTE)((DWORD)hModule + ntHeader->OptionalHeader.AddressOfEntryPoint);
		memcpy(originalCode, ep, sizeof(originalCode));

		// patch to call our EP
		int newEP = (int)Main_DoInit - ((int)ep + 5);
		ep[0] = 0xE9; // for some reason this doesn't work properly when run under the debugger
		memcpy(&ep[1], &newEP, 4);

		originalEP = ep;
	}
}

void DetectD3DX9_34()
{
	if (FileExists("d3dx9_34.dll"))
	{
		MessageBoxA(NULL, "Delete d3dx9_34.dll from your game folder.", "Fatal Error", MB_OK | MB_ICONSTOP);
		TerminateProcess(GetCurrentProcess(), 0);
	}
}

#include "math.h"

#define CreateThreadArg(func, arg) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)func, (LPVOID)arg, NULL, NULL);
#define CreateThreadMin(func) CreateThreadArg(func, NULL);

#define sprintf sprintf_s

#define	GENTITYNUM_BITS			10
#define	MAX_GENTITIES			(1 << GENTITYNUM_BITS)

#define	ENTITYNUM_NONE			(MAX_GENTITIES - 1)

#define CG_SetNextSnap			0x44D860

typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];

typedef struct {
	char unused_1[28];
	vec3_t origin;
	char unused_2[72];
	int groundEntityNum;
	char unused_3[116];
	int weapon;
	char unused_4[11896];
} playerState_t; //size: 0x2F64 (12132)

typedef struct {
	char unused_1[12];
	playerState_t ps;
	char unused_2[131340];
} snapshot_t; //size: 0x2307C (143484)

#define METRES			true				//output the distance in metres (or otherwise, units)
#define PRECISION		3				//round the distance to this many decimal places
#define	THRESHOLD		100				//discard jumps with a distance under this value

#define BUFFER_SIZE		32 + PRECISION
#define UNIT_WORD		(METRES ? "metres" : "units")

bool jumped = false;
vec2_t launchOrigin;

StompHook jumpHook;
DWORD jumpHookLoc = 0x44D860;

void Hook() {
	snapshot_t * snap;

	_asm mov snap, ebx

	if (!snap)
	{
		return;
	}
	
	bool inAir = (snap->ps.groundEntityNum == ENTITYNUM_NONE) && (snap->ps.weapon != 0);

	if (inAir && !jumped)
	{
		launchOrigin[0] = snap->ps.origin[0];
		launchOrigin[1] = snap->ps.origin[1];
	}
	else if (!inAir && jumped)
	{
		float dist = sqrt(
			pow(fabs(snap->ps.origin[0] - launchOrigin[0]), 2)
				+
			pow(fabs(snap->ps.origin[1] - launchOrigin[1]), 2)
		);

		if (METRES)
		{
			dist *= 0.0254f;
		}

		if (dist >= THRESHOLD)
		{
			char* format = (char*)malloc(BUFFER_SIZE);
			char* buffer = (char*)malloc(BUFFER_SIZE);

			sprintf(format, BUFFER_SIZE, "You jumped ^2%%.%if ^7%%s", PRECISION);
			sprintf(buffer, BUFFER_SIZE, format, dist, UNIT_WORD);

			GameEngine::CG_GameMessage(buffer);
		}
	}

	jumped = inAir;
}

void DetourFunc(DWORD loc, void * func, int nops) {
	int size = 19 + nops;
	BYTE * mem = (BYTE *)malloc(size);

	mem[0] = 0x60; //PUSHAD
	mem[1] = 0x9C; //PUSHFD
	mem[2] = 0xE8; //CALL
	* (DWORD *)(mem + 3) = (DWORD)((DWORD)func - (DWORD)(mem + 7));
	mem[7] = 0x9D; //POPFD
	mem[8] = 0x61; //POPAD

	memcpy(mem + 9, (void *)loc, nops + 5);
	mem[size - 5] = 0xE9; //JMP
	* (DWORD *)(mem + (size - 4)) = (DWORD)((DWORD)(loc + 5 + nops) - (DWORD)(mem + size));

	DWORD dwBack;
	VirtualProtect((LPVOID)loc, 5 + nops, PAGE_READWRITE, &dwBack);

	* (BYTE *)loc = 0xE9;
	* (DWORD *)(loc + 1) = (DWORD)(mem - (loc + 5));
	
	memset((void *)(loc + 5), 0x90, nops);

	VirtualProtect((LPVOID)loc, 5 + nops, dwBack, &dwBack);
}

void Initialize() {
	//DetourFunc(CG_SetNextSnap + 24, &Hook, 0);

	jumpHook.initialize(jumpHookLoc + 24, Hook, 19, true);
	jumpHook.installHook();
}

bool __stdcall DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
			DetectD3DX9_34();
			Main_SetSafeInit();
			//CreateThreadMin(Initialize);
			break;

		case DLL_PROCESS_DETACH:
			FreeLibrary(d3d9_dll);
			break;
	}

	return true;
}