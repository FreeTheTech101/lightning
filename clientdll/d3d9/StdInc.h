#pragma once

#include "buildnumber.h"

#define VERSION "1.0-" BUILDNUMBER_STR
#define VERSIONSTRING "LN " VERSION

#define DPMASTER "fluxy.triobit.net"
#define NP_SERVER "fluxy.triobit.net"
#define MASTERSERVERIP 0x157C923F

#define FS_BASEGAME "lightning"

#define KEY_DISABLED

//#define MESS_WITH_CONNECT_MENU

// ---------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS
#define _USING_V110_SDK71_

// Windows headers
#define WIN32_LEAN_AND_MEAN
#define ReadDirectoryChangesW ReadDirectoryChangesW__
#define CreateRemoteThread CreateRemoteThread__
#include <windows.h>
#undef CreateRemoteThread
#undef ReadDirectoryChangesW

// Direct3D
#include "d3d9.h"
#include "myIDirect3D9.h"
#include "myIDirect3DDevice9.h"
#include "myIDirect3DSwapChain9.h"

// LibNP
#ifndef NP_DISABLED
#include <libnp.h>
#endif

// C/C++ headers
#include <stdlib.h>
#include <crtdbg.h>
//#include <stdint.h>

#define _SCL_SECURE_NO_WARNINGS

// C/C++ headers
#include <map>
#include <vector>
#include <string>
#include <unordered_map>
#include <list>

// Generic utilities
#include "Utils.h"

// MW2 structures
#include "IW3.h"

// Hooking
#include "Hooking.h"

// more names
void PatchIW3();
void Sys_RunInit();

// blah
char* Auth_GetUsername();
char* Auth_GetObfuscatedUsername();
char* Auth_GetSessionID();
int Auth_GetUserID();
char* Auth_GetCountry();