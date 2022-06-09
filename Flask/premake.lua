project "Flask"
	targetname "flask"
	filter "configurations:Debug"
	kind "ConsoleApp"
	filter "configurations:Release"
	kind "WindowedApp"
	filter {}

	location "./"
	includedirs { "./" }
	files { "**.h", "**.cpp", "**.ixx" }

	staticruntime "Off" --MultiThreadedDLL

	-- pchheader "fpch.h"
	-- pchsource "core/pch.cpp"

	-- defines { }
	dofile "../premake/config.lua"
	dofile "../premake/nova.lua"

project "*"
startproject "Flask"
