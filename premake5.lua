solution "iw3cli"
	configurations { "Debug", "Release" }
	
	flags { "StaticRuntime", "No64BitChecks", "Symbols", "Unicode" }
	
	flags { "NoIncrementalLink", "NoEditAndContinue" }

	includedirs { "deps/include/" }
		
	libdirs { "deps/lib/" }
	
	configuration "Debug*"
		targetdir "bin/debug"
		defines "NDEBUG"
		
	configuration "Release*"
		targetdir "bin/release"
		defines "NDEBUG"
			
	project "d3d9"
		targetname "d3d9"
		language "C++"
		kind "SharedLib"

		defines { "WIN32", "NDEBUG", "_WINDOWS", "_WINDLL", "_USRDLL" }

		flags { "NoMinimalRebuild" }
		
		files
		{
			"d3d9/**.cpp", "d3d9/**.h", "d3d9/d3d9.def", "d3d9/StdInc.cpp", "d3d9/nui/**.cpp", "d3d9/nui/**.h"
		}

		links { "libcurl", "pdcurses", "libnp", "credui", "detours", "delayimp", "libcef_dll", "libcef" }
		
		libdirs { "deps/lib/", "libcef/lib/" }
		includedirs { "deps/include/np/", "libcef/" }

		linkoptions "/DELAYLOAD:libcef.dll"

		pchsource "d3d9/StdInc.cpp"
		pchheader "StdInc.h"

		configuration "windows"
			linkoptions "/IGNORE:4248 /IGNORE:4049 /IGNORE:4099 /DYNAMICBASE:NO /SAFESEH:NO"

		prebuildcommands
		{
			"pushd \"$(SolutionDir)\\deps\\tools\"",
			"call \"$(SolutionDir)\\deps\\tools\\gitrev.cmd\"",
			"popd"
		}

		configuration "Debug*"
			links { "libcefd" }

		configuration "Release*"
			links { "libcef" }

	project "InfinityScript"
		targetname "InfinityScript"
		language "C#"
		kind "SharedLib"

		files
		{
			"InfinityScript/**.cs"
		}

		links { "System", "System.Core", "System.Data", "System.Xml", "Microsoft.CSharp" }

	project "libcef_dll"
			targetname "libcef_dll_wrapper"
			language "C++"
			kind "StaticLib"
			
			defines { "USING_CEF_SHARED", "NOMINMAX", "WIN32" }
			
			flags { "NoIncrementalLink", "NoMinimalRebuild" }
			
			includedirs { ".", "libcef" }
			
			buildoptions "/MP"
			
			files
			{
				"libcef/libcef_dll/**.cc", "libcef/libcef_dll/**.cpp", "libcef/libcef_dll/**.h"
			}