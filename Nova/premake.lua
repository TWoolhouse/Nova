project "Nova"
	targetname "nova"
	if (nova_build_static) then
		kind "StaticLib"
	else
		kind "SharedLib"
	end
	location "./"
	includedirs { "./" }
	files { "**.h", "**.cpp", "**.ixx" }

	staticruntime "Off" --MultiThreadedDLL

	pchheader "npch.h"
	pchsource "meta/pch.cpp"

	-- Nova Building
	defines { "NOVA_BUILD_EXPORT" }

	dofile "../premake/nova_self.lua"
