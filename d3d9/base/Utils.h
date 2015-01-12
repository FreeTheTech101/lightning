// ==========================================================
// IW4M project
// 
// Component: clientdll
// Sub-component: steam_api
// Purpose: Various generic utility functions.
//
// Initial author: NTAuthority
// Started: 2010-09-10
// ==========================================================

//void Trace(char* source, char* message, ...);
//void Trace2(char* message, ...);
#define Trace(source, message, ...) Trace2("[" source "] " message, __VA_ARGS__)
#define Trace2(message, ...) GameEngine::Com_Printf(0, message, __VA_ARGS__)

bool FileExists(const char* file);
size_t FileSize(const char* file);
char *str_replace(char *orig, char *rep, char *with);
void CreateDirectoryAnyDepth(const char *path);

const char* va(const char* format, ...);

#define	MAX_INFO_STRING		1024
#define	MAX_INFO_KEY		  1024
#define	MAX_INFO_VALUE		1024

void Info_RemoveKey( char *s, const char *key );
void Info_SetValueForKey( char *s, const char *key, const char *value );
char *Info_ValueForKey( const char *s, const char *key );

// flag settings
#define GAME_FLAG_DEDICATED             (1 << 0)

#define GAME_FLAG(x)                    ((_gameFlags & x) == x)

extern unsigned int _gameFlags;
void DetermineGameFlags();

std::string GetCurrentDir();