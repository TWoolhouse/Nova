project "Flask"
	location "./"
	targetname "flask"
	filter "configurations:Debug"
		kind "ConsoleApp"
	filter "configurations:Release"
		kind "WindowedApp"
	filter {}
	language "C++"
	cppdialect "C++20"
	targetdir "../bin/%{cfg.buildcfg}"
	objdir "../build/%{cfg.buildcfg}/%{prj.name}"

	staticruntime "Off" --MultiThreadedDLL

	files { "**.h", "**.cpp" }
	includedirs { "./" }

	-- pchheader "fpch.h"
	-- pchsource "core/pch.cpp"

	-- defines { }
	dofile "../premake/nova.lua"
	dofile "../premake/config.lua"

project "*"
startproject "Flask"
