project "Flask.Test"
	targetname "flask.test"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	targetdir "../bin/%{cfg.buildcfg}"
	objdir "../build/%{cfg.buildcfg}/%{prj.name}"

	staticruntime "On" --MultiThreadedDLL

	files { "**.h", "**.cpp" }
	includedirs { "./" }

	-- pchheader "fpch.h"
	-- pchsource "core/pch.cpp"

	links { "gtestd.lib", "gtest_maind.lib" }

	removeconfigurations { "Release" }
	-- defines { }
	dofile "../premake/nova.lua"
	dofile "../premake/config.lua"
