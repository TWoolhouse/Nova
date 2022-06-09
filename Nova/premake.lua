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

	-- Nova Abyss Graphics API

	-- Vulkan
	filter "platforms:Vulkan"
		defines { "NOVA_ABYSS_VULKAN" }
		local vk_sdk = os.getenv("VULKAN_SDK")
		includedirs { vk_sdk .. "/Include" }
		links { "vulkan-1.lib" }
		libdirs { vk_sdk .. "/Lib" }

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
