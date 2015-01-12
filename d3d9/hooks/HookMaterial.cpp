#include "StdInc.h"

static void* Material_RegisterHandleHook(assetType_t type, const char* filename)
{
	/* Material* material = Material_Register(filename);

	if (material)
	{
		return material;
	} */

	return (Material*)GameEngine::DB_FindXAssetHeader(ASSET_TYPE_MATERIAL, filename);
}

static HookFunction hookFunction([] ()
{
	hook::jump(0x5F2A90, Material_RegisterHandleHook);
});