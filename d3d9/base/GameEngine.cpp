#include "StdInc.h"

#pragma CG_GameMessage
void GameEngine::CG_GameMessage(char* text)
{
	__asm
	{
		push text
		push 0
		mov esi, 43DDA0h
		call esi
		add esp, 8
	}
}
#pragma endregion

#pragma region Cmd_AddCommand
cmd_function_t** cmd_functions = (cmd_function_t**)0x1410B3C;

typedef int (__cdecl * Cmd_FindCommand_t)(const char* name);
Cmd_FindCommand_t Cmd_FindCommand = (Cmd_FindCommand_t)0x4F9950;

void GameEngine::Cmd_AddCommand(const char *cmd_name, CommandCB_t function)
{
	cmd_function_t *cmd;
	
	if (Cmd_FindCommand(cmd_name))
	{
		if (function != NULL)
		{
			GameEngine::Com_Printf(16, "Cmd_AddCommand: %s already defined\n", cmd_name);
		}

		return;
	}

	cmd = (cmd_function_t*)malloc(sizeof(struct cmd_function_s));
	cmd->name = cmd_name;
	cmd->function = function;
	cmd->next = *cmd_functions;
	*cmd_functions = cmd;
}
#pragma endregion

Cmd_AddServerCommand_t GameEngine::Cmd_AddServerCommand = (Cmd_AddServerCommand_t)0x4F9140;

Com_Printf_t GameEngine::Com_Printf = (Com_Printf_t)0x4FCBC0;
Com_PrintError_t GameEngine::Com_PrintError = (Com_PrintError_t)0x4FCC80;
Com_Error_t GameEngine::Com_Error = (Com_Error_t)0x4FD330;

DB_FindXAssetHeader_t GameEngine::DB_FindXAssetHeader = (DB_FindXAssetHeader_t)0x489570;
DB_LoadXAssets_t GameEngine::DB_LoadXAssets = (DB_LoadXAssets_t)0x48A2B0;

#pragma region Dvar_FindVar
typedef dvar_t* (__cdecl * Dvar_FindVar_t)(void);
Dvar_FindVar_t Dvar_FindVar_ = (Dvar_FindVar_t)0x4F9950;

dvar_t* GameEngine::Dvar_FindVar(char* name)
{
	__asm mov edi, name;

	return Dvar_FindVar_();
}

// get convar string
char* GameEngine::GetStringConvar(char* key)
{
	dvar_t* var = GameEngine::Dvar_FindVar(key);

	if (!var) return "";

	return var->current.string;
}

Image_LoadFromFileWithReader_t GameEngine::Image_LoadFromFileWithReader = (Image_LoadFromFileWithReader_t)0x642380;
Image_Release_t GameEngine::Image_Release = (Image_Release_t)0x6168E0;

Menus_FindByName_t GameEngine::Menus_FindByName = (Menus_FindByName_t)0x54C230;

NET_AdrToString_t GameEngine::NET_AdrToString = (NET_AdrToString_t)0x507990;

#pragma region NET_OutOfBandPrint
typedef void (__cdecl * sendOOB_t)(int, int, int, int, int, int, const char*);
sendOOB_t OOBPrint = (sendOOB_t)0x508BF0;

void OOBPrintT(int type, netadr_t netadr, const char* message)
{
	int* adr = (int*)&netadr;

	OOBPrint(type, *adr, *(adr + 1), *(adr + 2), 0xFFFFFFFF, *(adr + 4), message);
}

void GameEngine::NET_OutOfBandPrint(int type, netadr_t adr, const char* message, ...)
{
	va_list args;
	char buffer[65535];

	va_start(args, message);
	_vsnprintf(buffer, sizeof(buffer), message, args);
	va_end(args);

	OOBPrintT(type, adr, buffer);
}
#pragma endregion

#pragma region NET_StringToAdr
typedef bool (__cdecl * NET_StringToAdr_t)(netadr_t* adr);
NET_StringToAdr_t NET_StringToAdr_ = (NET_StringToAdr_t)0x508F40;

bool GameEngine::NET_StringToAdr(const char* address, netadr_t* adr)
{
	__asm mov eax, address;
	__asm mov ecx, 0xFFFFFFFF;

	NET_StringToAdr_(adr);
}
#pragma endregion

R_RegisterFont_t GameEngine::R_RegisterFont = (R_RegisterFont_t)0x5F1EC0;
