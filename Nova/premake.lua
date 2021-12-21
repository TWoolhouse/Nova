project "Nova"
	location "./"
	language "C++"
	cppdialect "C++20"
	targetname "nova"
	kind "SharedLib"
	targetdir "../bin/%{cfg.buildcfg}"
	objdir "../build/%{cfg.buildcfg}/%{prj.name}"

	staticruntime "Off" --MultiThreadedDLL

	files { "**.h", "**.cpp" }
	includedirs { "./" }

	pchheader "npch.h"
	pchsource "core/pch.cpp"

	defines { "NOVA_EXPORT" }
	dofile "../premake/config.lua"
