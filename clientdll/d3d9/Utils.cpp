#include "StdInc.h"
#include <ShellAPI.h>
#include <sys/stat.h>
#include <direct.h>
#include <io.h>

/*
void Trace(char* source, char* message, ...)
{
	va_list args;
	char buffer[1024];
	char buffer2[1024];

	va_start(args, message);
	_vsnprintf(buffer, sizeof(buffer), message, args);
	va_end(args);

	_snprintf(buffer2, sizeof(buffer2), "[%s] %s", source, buffer);

	OutputDebugStringA(buffer2);
}

void Trace2(char* message, ...)
{
	va_list args;
	char buffer[1024];

	va_start(args, message);
	_vsnprintf(buffer, sizeof(buffer), message, args);
	va_end(args);

	OutputDebugStringA(buffer);
}
*/

bool FileExists(const char* file)
{
	struct stat st;

	// note that this doesn't count any of the other ways stat could fail, but that'd be more error checking elsewhere
	if (stat(file, &st) >= 0)
	{
		return true;
	}

	return false;
}

size_t FileSize(const char* file)
{
	struct stat st;

	if (stat(file, &st) >= 0)
	{
		return st.st_size;
	}

	return 0;
}

// a funny thing is how this va() function could possibly come from leaked IW code.
#define VA_BUFFER_COUNT		4
#define VA_BUFFER_SIZE		32768

static char g_vaBuffer[VA_BUFFER_COUNT][VA_BUFFER_SIZE];
static int g_vaNextBufferIndex = 0;

const char *va( const char *fmt, ... )
{
	va_list ap;
	char *dest = &g_vaBuffer[g_vaNextBufferIndex][0];
	g_vaNextBufferIndex = (g_vaNextBufferIndex + 1) % VA_BUFFER_COUNT;
	va_start(ap, fmt);
	int res = _vsnprintf( dest, VA_BUFFER_SIZE, fmt, ap );
	dest[VA_BUFFER_SIZE - 1] = '\0';
	va_end(ap);

	if (res < 0 || res >= VA_BUFFER_SIZE)
	{
		//Com_Error(1, "Attempted to overrun string in call to va() - return address 0x%x", _ReturnAddress());
	}

	return dest;
}

/*
===================
Info_RemoveKey
===================
*/
void Info_RemoveKey( char *s, const char *key ) {
	char	*start;
	char	pkey[MAX_INFO_KEY];
	char	value[MAX_INFO_VALUE];
	char	*o;

	if (strchr (key, '\\')) {
		return;
	}

	while (1)
	{
		start = s;
		if (*s == '\\')
			s++;
		o = pkey;
		while (*s != '\\')
		{
			if (!*s)
				return;
			*o++ = *s++;
		}
		*o = 0;
		s++;

		o = value;
		while (*s != '\\' && *s)
		{
			if (!*s)
				return;
			*o++ = *s++;
		}
		*o = 0;

		if (!strcmp (key, pkey) )
		{
			strcpy (start, s);	// remove this part
			return;
		}

		if (!*s)
			return;
	}

}

/*
==================
Info_SetValueForKey

Changes or adds a key/value pair
==================
*/
void Info_SetValueForKey( char *s, const char *key, const char *value ) {
        char    newi[MAX_INFO_STRING];
        const char* blacklist = "\\;\"";

        if ( strlen( s ) >= MAX_INFO_STRING ) {
                Com_Printf( 0, "Info_SetValueForKey: oversize infostring");
		return;
        }

        for(; *blacklist; ++blacklist)
        {
                if (strchr (key, *blacklist) || strchr (value, *blacklist))
                {
                        Com_Printf (0, "Can't use keys or values with a '%c': %s = %s\n", *blacklist, key, value);
                        return;
                }
        }

        Info_RemoveKey (s, key);
        if (!value || !strlen(value))
                return;

        _snprintf (newi, sizeof(newi), "\\%s\\%s", key, value);

        if (strlen(newi) + strlen(s) >= MAX_INFO_STRING)
        {
                Com_Printf (0, "Info string length exceeded\n");
                return;
        }

        strcat (newi, s);
        strcpy (s, newi);
}


#define	BIG_INFO_STRING		8192  // used for system info key only
#define	BIG_INFO_KEY		  8192
#define	BIG_INFO_VALUE		8192

/*
===============
Info_ValueForKey

Searches the string for the given
key and returns the associated value, or an empty string.
FIXME: overflow check?
===============
*/
char *Info_ValueForKey( const char *s, const char *key )
{
	char	pkey[BIG_INFO_KEY];
	static	char value[2][BIG_INFO_VALUE];	// use two buffers so compares
	// work without stomping on each other
	static	int	valueindex = 0;
	char	*o;

	if ( !s || !key ) {
		return "";
	}

	if ( strlen( s ) >= BIG_INFO_STRING ) {
		//Com_Error( ERR_DROP, "Info_ValueForKey: oversize infostring" );
		return "";
	}

	valueindex ^= 1;
	if (*s == '\\')
		s++;
	while (1)
	{
		o = pkey;
		while (*s != '\\')
		{
			if (!*s)
				return "";
			*o++ = *s++;
		}
		*o = 0;
		s++;

		o = value[valueindex];

		while (*s != '\\' && *s)
		{
			*o++ = *s++;
		}
		*o = 0;

		if (!_stricmp (key, pkey) )
			return value[valueindex];

		if (!*s)
			break;
		s++;
	}

	return "";
}

// flag detection - thanks to Bas from fourdeltaone.net
// determine which patchset to use
unsigned int _gameFlags;

typedef struct  
{
	const wchar_t* argument;
	unsigned int flag;
} flagDef_t;

flagDef_t flags[] =
{
	{ L"dedicated", GAME_FLAG_DEDICATED },
	{ 0, 0 }
};

void DetermineGameFlags()
{
	int numArgs;
	LPCWSTR commandLine = GetCommandLineW();
	LPWSTR* argv = CommandLineToArgvW(commandLine, &numArgs);

	for (int i = 0; i < numArgs; i++)
	{
		/*if (argv[i][0] == L'#' || argv[i][0] == L'@')
		{
			WideCharToMultiByte(CP_ACP, 0, argv[i], -1, licenseKey, sizeof(licenseKey), "?", NULL);
			
			hasLicenseKey = true;
		}*/

		if (argv[i][0] != L'-') continue;

		for (wchar_t* c = argv[i]; *c != L'\0'; c++)
		{
			if (*c != L'-')
			{
				for (flagDef_t* flag = flags; flag->argument; flag++)
				{
					if (!wcscmp(c, flag->argument))
					{
						_gameFlags |= flag->flag;
						break;
					}
				}
				break;
			}
		}
	}

	LocalFree(argv);
}

std::string GetCurrentDir()
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}

void* DetourFunction(BYTE *source, const BYTE *destination, const int length)
{
	BYTE *jmp = (BYTE *)malloc(length + 5);
    DWORD dwBack;
 
    VirtualProtect(source, length, PAGE_EXECUTE_READWRITE, &dwBack);
 
	memcpy(jmp, source, length);
    jmp += length;
 
    jmp[0] = 0xE9;
    *(DWORD *)(jmp + 1) = (DWORD)(source + length - jmp) - 5;
 
    source[0] = 0xE9;
    *(DWORD*)(source + 1) = (DWORD)(destination - source) - 5;
 
    for(int i = 5; i < length; i++)
    {
		source[i] = 0x90;
	}
 
    VirtualProtect(source, length, dwBack, &dwBack);
 
    return (jmp - length);
}