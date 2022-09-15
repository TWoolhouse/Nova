project "Flask.Test"
	targetname "flask.test"
	kind "ConsoleApp"

	location "./"
	includedirs { "./" }
	files { "**.h", "**.cpp", "**.ixx" }

	pchheader "tpch.h"
	pchsource "pch.cpp"

	staticruntime "On"

	local gtest = "../vendor/googletest"
	local bin = gtest .. "/build"

	includedirs { gtest .. "/googletest/include/" }
	libdirs { bin .. "/lib/Debug/" }
	links { "gtest.lib", "gtest_main.lib" }


	local gtest_shared = "OFF"
	if (nova_build_static) then
		staticruntime "Off"
		gtest_shared = "ON"
	end

	prebuildcommands {
		"{MKDIR} " .. bin,
		"{CHDIR} " .. bin,
		"cmake .. -A x64 -DBUILD_GMOCK=OFF -Dgtest_force_shared_crt=" .. gtest_shared
	}
	filter { "system:windows" }
		prebuildcommands {
			"msbuild /maxcpucount /nodeReuse:True googletest-distribution.sln"
		}
	filter {}

	removeconfigurations { "Release" }
	-- defines { }
	dofile "../premake/nova.lua"
