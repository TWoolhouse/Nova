project "Flask.Test"
	targetname "flask.test"
	kind "ConsoleApp"

	location "./"
	includedirs { "./" }
	files { "**.h", "**.cpp", "**.ixx" }

	staticruntime "On" --MultiThreadedDebug

	pchheader "tpch.h"
	pchsource "pch.cpp"

	local gtest = "../vendor/googletest"
	local bin = gtest .. "/build"

	includedirs { gtest .. "/googletest/include/" }
	libdirs { bin .. "/lib/Debug/" }
	links { "gtest.lib", "gtest_main.lib" }

	prebuildcommands {
		"{MKDIR} " .. bin,
		"{CHDIR} " .. bin,
		"cmake .. -A x64 -DBUILD_GMOCK=OFF"
	}
	filter { "system:windows" }
		prebuildcommands {
			"msbuild /maxcpucount /nodeReuse:True googletest-distribution.sln"
		}
	filter {}

	removeconfigurations { "Release" }
	-- defines { }
	dofile "../premake/config.lua"
	dofile "../premake/nova.lua"
