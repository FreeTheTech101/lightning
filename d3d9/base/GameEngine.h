#pragma once

#pragma region Cmd_AddCommand
typedef void (__cdecl * CommandCB_t)(void);

typedef struct cmd_function_s
{
    cmd_function_s *next;
    const char *name;
    const char *autoCompleteDir;
    const char *autoCompleteExt;
    CommandCB_t function;
} cmd_function_t;
#pragma endregion

typedef void (__cdecl * Cmd_AddServerCommand_t)(const char* cmdName, CommandCB_t callback, cmd_function_t* data);

typedef void (__cdecl * Com_Printf_t)(int, const char*, ...);
typedef void (__cdecl * Com_PrintError_t)(int, const char*, ...);
typedef void (__cdecl * Com_Error_t)(int type, const char* message, ...);

typedef void* (__cdecl * DB_FindXAssetHeader_t)(int type, const char* filename);

typedef void* (__cdecl * R_RegisterFont_t)(const char* asset, int);

class GameEngine
{
public:
	static void CG_GameMessage(char* text);

	static void Cmd_AddCommand(const char *name, CommandCB_t function);
	static Cmd_AddServerCommand_t Cmd_AddServerCommand;

	static Com_Printf_t Com_Printf;
	static Com_PrintError_t Com_PrintError;
	static Com_Error_t Com_Error;

	static DB_FindXAssetHeader_t DB_FindXAssetHeader;

	static R_RegisterFont_t R_RegisterFont;
};