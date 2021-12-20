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
filter {}
