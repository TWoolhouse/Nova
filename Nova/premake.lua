project "Nova"
	targetname "nova"
	if (nova_build_static) then
		kind "StaticLib"
	else
		kind "SharedLib"
	end

	staticruntime "Off"

	location "./"
	includedirs { "./" }
	files { "**.h", "**.cpp", "**.ixx" }

	pchheader "npch.h"
	pchsource "meta/pch.cpp"

	-- Nova Building
	defines { "NOVA_BUILD_EXPORT" }

	dofile "../premake/nova_self.lua"
