#include "StdInc.h"

#pragma unmanaged
void CallHook::initialize(DWORD place, void *hookToInstall)
{
	pPlace = (PBYTE)place;
	memcpy(bOriginalCode, pPlace, sizeof(bOriginalCode));
	pOriginal = pPlace + sizeof(bOriginalCode) + *(ptrdiff_t*) (bOriginalCode + 1);
	hook = hookToInstall;
}

void CallHook::installHook(void *hookToInstall)
{
	if (hookToInstall) hook = hookToInstall;
	if (hook) {
		*(ptrdiff_t*) (pPlace + 1) = (PBYTE) hook - pPlace - 5;
	}
}

void CallHook::releaseHook()
{
	//memcpy(pPlace + 1, bOriginalCode + 1, sizeof(bOriginalCode) - 1);
	*(ptrdiff_t*) (pPlace + 1) = (PBYTE) pOriginal - pPlace - 5;
}

/*
void PointerHook::initialize(PVOID* place)
{
	pPlace = place;
	pOriginal = NULL;
}

int PointerHook::installHook(void (*hookToInstall)(), bool unprotect)
{
	DWORD d = 0;

	if (pOriginal)
		return 0;
	if (unprotect &&
		!VirtualProtect(pPlace, sizeof(PVOID), PAGE_READWRITE, &d))
		return 0;
	pOriginal = *pPlace;
	*pPlace = (PVOID) hookToInstall;
	if (unprotect)
		VirtualProtect(pPlace, sizeof(PVOID), d, &d);
	return 1;
}

int PointerHook::releaseHook(bool unprotect)
{
	DWORD d = 0;

	if (!pOriginal)
		return 0;
	if (unprotect &&
		!VirtualProtect(pPlace, sizeof(PVOID), PAGE_READWRITE, &d))
		return 0;
	*pPlace = pOriginal;
	pOriginal = NULL;
	if (unprotect)
		VirtualProtect(pPlace, sizeof(PVOID), d, &d);
	return 1;
}

*/
void StompHook::initialize(DWORD place, void *hookToInstall, BYTE countBytes, bool useJump)
{
	pPlace = (PBYTE)place;
	bCountBytes = countBytes < sizeof(bOriginalCode) ? countBytes : sizeof(bOriginalCode);
	memcpy(bOriginalCode, pPlace, bCountBytes);
	hook = hookToInstall;
	jump = useJump;
}

void StompHook::installHook(void *hookToInstall)
{
	if (hookToInstall) hook = hookToInstall;
	if (hook) {
		memset(pPlace, NOP, bCountBytes);
		pPlace[0] = jump ? JMP_NEAR32 : CALL_NEAR32;
		*(ptrdiff_t*) (pPlace + 1) = (PBYTE) hook - pPlace - 5;
	}
}

void StompHook::releaseHook()
{
	memcpy(pPlace, bOriginalCode, bCountBytes);
}

void HookInstall(DWORD address, DWORD hookToInstall, int bCountBytes)
{
	PBYTE pPlace = (PBYTE)address;
	memset(pPlace, NOP, bCountBytes);
	pPlace[0] = CALL_NEAR32;
	*(ptrdiff_t*) (pPlace + 1) = (PBYTE) hookToInstall - pPlace - 5;
}

void hook::patch(uintptr_t pAddress, DWORD data, DWORD iSize)
{
	switch (iSize)
	{
	case 1:
		*(BYTE*)pAddress = (BYTE)data;
		break;
	case 2:
		*(WORD*)pAddress = (WORD)data;
		break;
	case 4:
		*(DWORD*)pAddress = (DWORD)data;
		break;
	}
}

void hook::nop(uintptr_t pAddress, DWORD size)
{
	memset((void*)pAddress, 0x90, size);
}

void hook::jump(uintptr_t pAddress, void* data)
{
	*(BYTE*)pAddress = (BYTE)0xE9;
	*(DWORD*)((DWORD)pAddress + 1) = (intptr_t)data - (DWORD)pAddress - 5;
}

void hook::call(uintptr_t pAddress, DWORD data)
{
	*(BYTE*)pAddress = (BYTE)0xE8;
	*(DWORD*)((DWORD)pAddress + 1) = (intptr_t)data - (DWORD)pAddress - 5;
}

void hook::charptr(uintptr_t pAddress, const char* pChar)
{
	*(DWORD*)pAddress = (DWORD)pChar;
}