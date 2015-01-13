#pragma once

#define CALL_NEAR32 0xE8U
#define JMP_NEAR32 0xE9U
#define NOP 0x90U

struct CallHook {
	BYTE bOriginalCode[5];
	PBYTE pPlace;
	void* pOriginal;
	void* hook;

	void initialize(DWORD place, void *hookToInstall = NULL);
	void installHook(void* hookToInstall = NULL);
	void releaseHook();
};
/*
struct PointerHook {
	PVOID* pPlace;
	PVOID pOriginal;

	void initialize(PVOID* place);
	int installHook(void (*hookToInstall)(), bool unprotect);
	int releaseHook(bool unprotect);
};
*/
struct StompHook {
	BYTE bOriginalCode[15];
	BYTE bCountBytes;
	PBYTE pPlace;
	void* hook;
	bool jump;

	void initialize(DWORD place, void *hookToInstall = NULL, BYTE countBytes = 5, bool useJump = true);
	void installHook(void* hookToInstall = NULL);
	void releaseHook();
};

void HookInstall(DWORD address, DWORD hookToInstall, int bCountBytes=5);

class hook
{
public:
	static void nop(uintptr_t pAddress, DWORD size);
	static void hook::patch(uintptr_t pAddress, DWORD data, DWORD iSize);
	static void jump(uintptr_t pAddress, void* data);
	static void call(uintptr_t pAddress, void* data);
	static void charptr(uintptr_t pAddress, const char* pChar);
};