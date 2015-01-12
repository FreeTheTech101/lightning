#include "StdInc.h"


Dvar_RegisterBool_t Dvar_RegisterBool = (Dvar_RegisterBool_t)0x56C350;
Dvar_RegisterInt_t Dvar_RegisterInt = (Dvar_RegisterInt_t)0x56C350;


Dvar_InfoString_Big_t Dvar_InfoString_Big = (Dvar_InfoString_Big_t)0x4D98A0;
Dvar_FindVar_t _Dvar_FindVar = (Dvar_FindVar_t)0x56B5D0;
dvar_t* Dvar_FindVar(char* name)
{
	__asm mov edi, name;

	return _Dvar_FindVar();
}


FS_ReadFile_t FS_ReadFile = (FS_ReadFile_t)0x55C440;
FS_Read_t FS_Read = (FS_Read_t)0x55C120; // 55C200 fastcall
FS_FOpenFileRead_t FS_FOpenFileRead = (FS_FOpenFileRead_t)0x421F00;
FS_FCloseFile_t FS_FCloseFile = (FS_FCloseFile_t)0x55B3B0;


NET_StringToAdr_t NET_StringToAdr_CoD4 = (NET_StringToAdr_t)0x508F40;
/*NET_OutOfBandPrint_t NET_OutOfBandPrint = (NET_OutOfBandPrint_t)0x508BF0;

bool NET_StringToAdr(const char* address, netadr_t* adr)
{
	__asm mov eax, address;
	__asm mov ecx, 0xFFFFFFFF;
	NET_StringToAdr_CoD4(adr);
}*/

typedef void (__cdecl* sendOOB_t)(int, int, int, int, int, int, const char*);
sendOOB_t OOBPrint = (sendOOB_t)0x508BF0; //0x4AEF00 IW4 159

void OOBPrintT(int type, netadr_t netadr, const char* message)
{
	int* adr = (int*)&netadr;

	OOBPrint(type, *adr, *(adr + 1), *(adr + 2), 0xFFFFFFFF, *(adr + 4), message);
}

void NET_OutOfBandPrint(int type, netadr_t adr, const char* message, ...)
{
	va_list args;
	char buffer[65535];

	va_start(args, message);
	_vsnprintf(buffer, sizeof(buffer), message, args);
	va_end(args);

	OOBPrintT(type, adr, buffer);
}

int* svs_numclients = (int*)0x1CBFC8C;

char* GetStringConvar(char* key) {
    dvar_t* var = Dvar_FindVar(key);

    if (!var) return "";

    return var->current.string;
}

// console commands
DWORD* cmd_id = (DWORD*)0x1410B40;
DWORD* cmd_argc = (DWORD*)0x1410B84;
DWORD** cmd_argv = (DWORD**)0x1410BA4;

/*
============
Cmd_Argc
============
*/
/*int		Cmd_Argc( void ) {
	return cmd_argc[*cmd_id];
}*/

/*
============
Cmd_Argv
============
*/
/*char	*Cmd_Argv( int arg ) {
	if ( (unsigned)arg >= cmd_argc[*cmd_id] ) {
		return "";
	}
	return (char*)(cmd_argv[*cmd_id][arg]);	
}*/

DWORD* cmd_id_sv = (DWORD*)0x1433408;
DWORD* cmd_argc_sv = (DWORD*)0x143344C;
DWORD** cmd_argv_sv = (DWORD**)0x143346C;

/*
============
Cmd_Argc
============
*/
int		Cmd_ArgcSV( void ) {
	return cmd_argc_sv[*cmd_id_sv];
}

/*
============
Cmd_Argv
============
*/
char	*Cmd_ArgvSV( int arg ) {
	if ( (unsigned)arg >= cmd_argc_sv[*cmd_id_sv] ) {
		return "";
	}
	return (char*)(cmd_argv_sv[*cmd_id_sv][arg]);	
}