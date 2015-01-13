#include "StdInc.h"

char zone_language[MAX_PATH];
char* loadedPath = "";
char* zonePath = "";

#ifdef IW4M_OLD_CODE
char* zone_dlc = "zone\\dlc\\";
char* zone_alter = "zone\\alter\\";
#endif

dvar_t** fs_basepath = (dvar_t**)0xCB1AAB8;
dvar_t** fs_cdpath = (dvar_t**)0xCB19890;

char* GetZoneLocation(const char* name)
{
	static char path[MAX_PATH];

	_snprintf(path, MAX_PATH, "%s\\GameData\\XAssets\\%s\\%s.ff", (*fs_basepath)->current.string, "w2\\", name);

	if (FileExists(path)) {
		sprintf(path, "%s\\GameData\\XAssets\\w2\\", (*fs_basepath)->current.string);
		return path;
	}

	if ((*fs_cdpath)->current.string[0])
	{
		_snprintf(path, MAX_PATH, "%s\\GameData\\XAssets\\%s\\%s.ff", (*fs_cdpath)->current.string, "w2\\", name);

		if (FileExists(path)) {
			sprintf(path, "%s\\GameData\\XAssets\\w2\\", (*fs_cdpath)->current.string);
			return path;
		}
	}

	_snprintf(path, MAX_PATH, "%s\\GameData\\XAssets\\%s\\%s.ff", (*fs_basepath)->current.string, "dlc\\", name);

	if (FileExists(path)) {
		sprintf(path, "%s\\GameData\\XAssets\\dlc\\", (*fs_basepath)->current.string);
		return path;
	}

	if ((*fs_cdpath)->current.string[0])
	{
		_snprintf(path, MAX_PATH, "%s\\GameData\\XAssets\\%s\\%s.ff", (*fs_cdpath)->current.string, "dlc\\", name);

		if (FileExists(path)) {
			sprintf(path, "%s\\GameData\\XAssets\\dlc\\", (*fs_cdpath)->current.string);
			return path;
		}
	}

	DWORD getLang = 0x45CBA0;
	char* language;

	__asm {
		call getLang
			mov language, eax
	}

	_snprintf(path, MAX_PATH, "%s\\GameData\\XAssets\\%s\\%s.ff", (*fs_basepath)->current.string, language, name);

	if (FileExists(path)) {
		sprintf(path, "%s\\GameData\\XAssets\\%s\\", (*fs_basepath)->current.string, language);
		return path;
	}

	if ((*fs_cdpath)->current.string[0])
	{
		_snprintf(path, MAX_PATH, "%s\\GameData\\XAssets\\%s\\%s.ff", (*fs_cdpath)->current.string, language, name);

		if (FileExists(path)) {
			sprintf(path, "%s\\GameData\\XAssets\\%s\\", (*fs_cdpath)->current.string, language);
			return path;
		}
	}

	return NULL;
}

char* GetZonePath(const char* fileName)
{
	// we do it a lot simpler than IW did.
	return GetZoneLocation(fileName);
}