workspace "Nova"

	configurations { "Debug", "Release" }
	platforms { "Vulkan" } -- "OpenGL"
	architecture "x86_64"

	toolset "clang"
	filter { "system:Windows" }
		toolset "msc"

	location("project/" .. _ACTION .. "/")

	characterset "Unicode"
	defines { "UNICODE", "_UNICODE" }

	-- libdirs { "vendor/*/lib/" }
	-- includedirs { "vendor/*/include/" }

	language "C++"
	cppdialect "C++20"
	targetdir "bin/%{cfg.buildcfg}/%{cfg.platform}/"
	objdir "build/%{cfg.buildcfg}/%{cfg.platform}/%{prj.name}/"

local projects = {
	"Nova",
	"Flask",
	"Flask.Test",
}

for i,prj in ipairs(projects) do
	include(prj .. "/premake.lua")
end
