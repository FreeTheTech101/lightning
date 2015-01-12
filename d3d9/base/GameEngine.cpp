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

typedef int (__cdecl * Cmd_AddCommand_t)(const char* name);
Cmd_AddCommand_t Cmd_AddCommand_ = (Cmd_AddCommand_t)0x4F9950;

void GameEngine::Cmd_AddCommand(const char* name, CommandCB_t function)
{
	if (Cmd_AddCommand_(name))
	{
		if (function != NULL)
		{
			GameEngine::Com_Printf(16, "Cmd_AddCommand: %s already defined\n", name);
		}

		return;
	}

	cmd_function_t *cmd = (cmd_function_t*)malloc(sizeof(struct cmd_function_s));
	cmd->name = name;
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

R_RegisterFont_t GameEngine::R_RegisterFont = (R_RegisterFont_t)0x5F1EC0;