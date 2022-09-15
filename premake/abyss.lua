filter {}

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
	includedirs { vk_sdk .. "/Include/" }
	libdirs { vk_sdk .. "/Lib/" }
	links { "vulkan-1.lib" }

	-- VMA
	includedirs { "../vendor/vma/include/" }

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
