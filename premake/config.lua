filter {}
	defines { "NOVA_WINDOW_NATIVE" }

filter "configurations:Debug"
	defines { "DEBUG", "_DEBUG" }
	removedefines { "NDEBUG" }
	symbols "Full"
	intrinsics "off"

filter "configurations:Release"
	defines { "NDEBUG" }
	removedefines { "DEBUG", "_DEBUG" }
	optimize "Speed"
	stringpooling "on"
	intrinsics "on"
	inlining "Auto"
	flags {
		"LinkTimeOptimization",
		"MultiProcessorCompile",
	}

filter { "configurations:Release", "action:vs*" }
	buildoptions { "/Ot" }

filter "platforms:OpenGL"
	defines { "NOVA_WINDOW_GLFW" }
	removedefines { "NOVA_WINDOW_NATIVE" }

filter {}
-- scanformoduledependencies "true"

-- defines "NOVA_BUILD_STATIC"
