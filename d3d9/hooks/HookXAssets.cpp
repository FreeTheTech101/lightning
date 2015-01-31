#include "StdInc.h"

typedef void (*LoadInitialFF_t)(void);
LoadInitialFF_t LoadInitialFF = (LoadInitialFF_t)0x5F55E0;

void RendererInitHook()
{
	GameEngine::Com_Printf(14, "----- Initializing Renderer ----\n");
	
	int zoneCount = 5; // 6 if weap_iw3m
	XZoneInfo zoneInfo[6];
	
	zoneInfo[0].name = "code_post_gfx_mp";
	zoneInfo[0].type1 = 1;
	zoneInfo[0].type2 = 0;
	
	zoneInfo[2].name = "ui_mp";
	zoneInfo[2].type1 = 1024;
	zoneInfo[2].type2 = 0;
	
	zoneInfo[3].name = "common_mp";
	zoneInfo[3].type1 = 1023;
	zoneInfo[3].type2 = 0;
	
	zoneInfo[1].name = "localized_code_post_gfx_mp";
	zoneInfo[1].type1 = 1022;
	zoneInfo[1].type2 = 0;
	
	zoneInfo[4].name = "localized_common_mp";
	zoneInfo[4].type1 = 6;
	zoneInfo[4].type2 = 0;
	
	//zoneInfo[5].name = "weap_iw3m";
	//zoneInfo[5].type1 = 20;
	//zoneInfo[5].type2 = 0;
	
	memcpy((void*)0xCC9D110, &zoneInfo, sizeof(&zoneInfo));
	
	LoadInitialFF(); // this call causes out of memory error
	GameEngine::DB_LoadXAssets(&zoneInfo[0], zoneCount, 0);
}

static HookFunction hookFunction([] ()
{
	//hook::call(0x46A3EF, RendererInitHook);
	//hook::call(0x46FD00, RendererInitHook); // CL_Init
});