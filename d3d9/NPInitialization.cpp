/*
 * This file (NPInitialization.cpp) is part of Lightning client.
 * Purpose: initialization of Network Platform
 * Original author: Archon, 2013-12-23
 * Copyright (C) 2013 triobit
 * --------------------------------------------------------------------------------
 * Lightning is licensed under the GNU General Public License.
 * You can view a copy of the license here: <http://www.gnu.org/licenses/>.
 * --------------------------------------------------------------------------------
 * You are allowed to redistribute Lightning and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 2 of the License, or (at your option) any later version.
 */

#include "StdInc.h"

#ifndef NP_DISABLED
#define CURL_STATICLIB
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>

#undef Trace
#define Trace

size_t UDataReceived(void *ptr, size_t size, size_t nmemb, void *data)
{
	size_t rsize = (size * nmemb);
	char* text = (char*)ptr;
	int version = atoi(text);

	if (version > BUILDNUMBER)
	{
		Com_Error(1, "This demo version (%d) has expired. Please visit http://triobit.net/ (or run lightning.exe) to obtain a new version (%d).", BUILDNUMBER, version);
		TerminateProcess(GetCurrentProcess(), 0);
	}

	return rsize;
}

void DisableOldVersions()
{
	if (IsDebuggerPresent()) return;

	curl_global_init(CURL_GLOBAL_ALL);

	CURL* curl = curl_easy_init();

	if (curl)
	{
		char url[255];
		_snprintf(url, sizeof(url), "http://data.triobit.net/updater/version.txt");

		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, UDataReceived);
		//curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)&steamID);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, VERSIONSTRING);
		curl_easy_setopt(curl, CURLOPT_FAILONERROR, true);

		CURLcode code = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		curl_global_cleanup();

		if (code == CURLE_OK)
		{
			return;
		}
		else
		{
			// TODO: set some offline mode flag
		}
	}

	curl_global_cleanup();
}

void NP_LogCB(const char* message)
{
	Com_Printf(0, va("[NP] %s", message));
}

bool NP_Initialize()
{
	DisableOldVersions();

	NP_SetLogCallback(NP_LogCB);
	NP_Init();

	//NP_RegisterEACallback(NPA_StateSet);

	if (!NP_Connect(NP_SERVER, 3036))
	{
		// TODO: offer offline mode in this case/with an offline gameflag
		Com_Error(1, "Could not connect to NP server at " NP_SERVER);
		return false;
	}

	NPAuthenticateResult* result;

	if (!GAME_FLAG(GAME_FLAG_DEDICATED))
	{
		NPAsync<NPAuthenticateResult>* async = NP_AuthenticateWithToken(Auth_GetSessionID());
		result = async->Wait();
	}
	else
	{
		NPAsync<NPAuthenticateResult>* async = NP_AuthenticateWithLicenseKey("R8AMLpbZK4JpVmXjNKhptcLX");
		result = async->Wait();
	}

	if (result->result != AuthenticateResultOK)
	{
		switch (result->result)
		{
		case AuthenticateResultBadDetails:
			Com_Error(1, "Could not authenticate to NP server at " NP_SERVER " -- bad details.");
			break;
		case AuthenticateResultAlreadyLoggedIn:
			Com_Error(1, "Could not authenticate to NP server at " NP_SERVER " -- already logged in.");
			break;
		case AuthenticateResultServiceUnavailable:
			Com_Error(1, "Could not authenticate to NP server at " NP_SERVER " -- service unavailable.");
			break;
		case AuthenticateResultBanned:
			Com_Error(1, "Could not authenticate to NP server at " NP_SERVER " -- banned.");
			break;
		case AuthenticateResultUnknown:
			Com_Error(1, "Could not authenticate to NP server at " NP_SERVER " -- unknown error.");
			break;
		}

		return false;
	}

	//while (true)
	//{
	//	Sleep(1);
	//	NP_RunFrame();
	//}

	Sleep(1);
	NP_RunFrame();

	//g_extDLL = (IExtDLL*)NP_LoadGameModule(BUILDNUMBER);

	//if (!g_extDLL) Com_Error(1, "Could not load the extension DLL for revision number " BUILDNUMBER_STR);

	//g_extDLL->Initialize(_gameFlags, new ClientDLLAPI());

	//NP_RegisterKickCallback(NPA_KickClient);

	return true;
}
#endif