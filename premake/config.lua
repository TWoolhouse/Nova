filter "configurations:Debug"
	defines { "DEBUG", "_DEBUG" }
	removedefines { "NDEBUG" }
	symbols "Full"
	intrinsics "off"

filter { "configurations:Debug", "action:vs*" }
	buildoptions {
		"/w35240", -- Attribute is ignored in this position
		"/w34100", -- Unreference formal parameter
		"/w34834", -- Discarding nodiscard
		"/w34702", -- Code unreachable
		"/w34189", -- Local variable declared but not used
		"/w34946", -- Reinterpret cast on related classes
	}

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

filter {}
