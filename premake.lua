workspace "Nova"

	configurations { "Debug", "Release" }
	platforms "x64"
	architecture "x86_64"

	location("project/" .. _ACTION .. "/")

	characterset "Unicode"
	defines { "UNICODE", "_UNICODE" }

	libdirs { "lib/" }

local projects = {
	"Nova",
	"Flask",
	"Flask.Test"
}

for i,prj in ipairs(projects) do
	include(prj .. "/premake.lua")
end
