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
	pchsource "meta/pch.cpp"

	-- NOVA Building
	defines { "NOVA_EXPORT" }

	-- Vulkan
	local vk_sdk = os.getenv("VULKAN_SDK")
	includedirs { vk_sdk .. "/Include" }
	links { "vulkan-1.lib" }
	libdirs { vk_sdk .. "/Lib" }
	defines { "NOVA_ABYSS_VULKAN" }

	-- Config

	dofile "../premake/nova_self.lua"
	dofile "../premake/config.lua"
