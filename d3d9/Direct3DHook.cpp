#include "StdInc.h"
#include "Direct3DHook.h"

// global variables
#pragma data_seg (".d3d9_shared")
myIDirect3DSwapChain9*  gl_pmyIDirect3DSwapChain9;
myIDirect3DDevice9*		gl_pmyIDirect3DDevice9;
myIDirect3D9*			g_d3d9;
HINSTANCE				gl_hOriginalDll;
HINSTANCE				gl_hThisInstance;
#pragma data_seg ()

void LoadOriginalDll()
{
    char buffer[MAX_PATH];
    
    // Getting path to system dir and to d3d8.dll
	GetSystemDirectory(buffer, MAX_PATH);

	// Append dll name
	strcat(buffer, "\\d3d9.dll");
	
	// try to load the system's d3d9.dll, if pointer empty
	if (!gl_hOriginalDll)
	{
		gl_hOriginalDll = LoadLibrary(buffer);
	}

	// Debug
	if (!gl_hOriginalDll)
	{
		ExitProcess(0); // exit the hard way
	}
}

// Exported function (faking d3d9.dll's one-and-only export)
IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion)
{
	if (!gl_hOriginalDll)
	{
		LoadOriginalDll(); // looking for the "right d3d9.dll"
	}
	
	// Hooking IDirect3D Object from Original Library
	typedef IDirect3D9 *(WINAPI* D3D9_Type)(UINT SDKVersion);
	D3D9_Type D3DCreate9_fn = (D3D9_Type)GetProcAddress(gl_hOriginalDll, "Direct3DCreate9");
    
    // Debug
	if (!D3DCreate9_fn) 
    {
        ExitProcess(0);
    }
	
	IDirect3D9 *d3d9 = D3DCreate9_fn(SDKVersion);
	g_d3d9 = new myIDirect3D9(d3d9);

	return (g_d3d9);
}