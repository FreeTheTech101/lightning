#include "StdInc.h"

Com_Error_t Com_Error = (Com_Error_t)0x4FD330;
Com_Printf_t Com_Printf = (Com_Printf_t)0x4FCBC0;

Cmd_AddServerCommand_t Cmd_AddServerCommand = (Cmd_AddServerCommand_t)0x4F9140;

Com_PrintError_t Com_PrintError = (Com_PrintError_t)0x4FCC80;


DB_FindXAssetHeader_t DB_FindXAssetHeader = (DB_FindXAssetHeader_t)0x489570;


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

R_RegisterFont_t R_RegisterFont = (R_RegisterFont_t)0x5F1EC0;

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

cmd_function_t** cmd_functions = (cmd_function_t**)0x1410B3C;

void Cmd_AddCommand(const char *name, CommandCB_t function)
{
	// check if the command is already defined by
	// asking calling the original Cmd_AddCommand with the name argument
	if (((cmd_function_t*(*)(const char*))0x4F9950)(name))
	{
		if (function != NULL)
		{
			Com_Printf(16, "Cmd_AddCommand: %s already defined\n", name);
		}

		return;
	}

	cmd_function_t *cmd = (cmd_function_t*)malloc(sizeof(struct cmd_function_s));
	cmd->name = name;
	cmd->function = function;
	cmd->next = *cmd_functions;
	*cmd_functions = cmd;
}