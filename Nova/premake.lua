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

	-- Vulkan
	local vk_sdk = os.getenv("VULKAN_SDK")
	includedirs { vk_sdk .. "/Include" }
	links { "vulkan-1.lib" }
	libdirs { vk_sdk .. "/Lib" }
	defines { "NOVA_ABYSS_VULKAN" }




	defines { "NOVA_EXPORT" }
	dofile "../premake/config.lua"
