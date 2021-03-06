project "Nova"
	targetname "nova"
	kind "SharedLib"
	location "./"
	includedirs { "./" }
	files { "**.h", "**.cpp", "**.ixx" }

	staticruntime "Off" --MultiThreadedDLL

	pchheader "npch.h"
	pchsource "meta/pch.cpp"

	-- Nova Building
	defines { "NOVA_EXPORT" }

	local vk_sdk = os.getenv("VULKAN_SDK")
	-- Spir-V
	includedirs { vk_sdk .. "/Include" }
	libdirs { vk_sdk .. "/Lib" }
	filter "configurations:Release"
		links { "shaderc_combined.lib" }
	filter "configurations:Debug"
		links { "shaderc_combinedd.lib" }
	filter {}

	-- Nova Abyss Graphics API

	-- Vulkan
	filter "platforms:Vulkan"
		defines { "NOVA_ABYSS_VULKAN" }
		includedirs { vk_sdk .. "/Include" }
		libdirs { vk_sdk .. "/Lib" }
		links { "vulkan-1.lib" }

	-- OpenGL
	filter "platforms:OpenGL"
		defines { "NOVA_ABYSS_OPENGL" }
		includedirs { "../vendor/glad/include/" }
		includedirs { "../vendor/glfw/include/" }
		includedirs { "../vendor/glad/src/" }
		links { "glfw3.lib" }
		filter "system:Windows"
			links { "opengl32.lib" }
		filter "system:Linux"
			links { "libGL.so" }
		filter {}

	filter {}

	dofile "../premake/nova_self.lua"
	dofile "../premake/config.lua"
