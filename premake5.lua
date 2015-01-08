solution "lightning"
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
			"d3d9/**.cpp", "d3d9/**.h", "d3d9/d3d9.def", "d3d9/StdInc.cpp"
		}

		pchsource "d3d9/StdInc.cpp"
		pchheader "StdInc.h"
		
		includedirs { "deps/include/np/" }
		
		libdirs { "deps/lib/" }

		links { "libcurl.lib", "pdcurses.lib", "libnp.lib", "credui.lib", "detours.lib" }

		configuration "windows"
			linkoptions "/IGNORE:4248 /IGNORE:4049 /IGNORE:4099 /DYNAMICBASE:NO /SAFESEH:NO"

		prebuildcommands
		{
			"pushd \"$(SolutionDir)\\deps\\tools\"",
			"call \"$(SolutionDir)\\deps\\tools\\gitrev.cmd\"",
			"popd"
		}