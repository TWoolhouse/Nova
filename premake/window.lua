filter {}
	defines { "NOVA_WINDOW_NATIVE" }
filter "platforms:OpenGL"
	defines { "NOVA_WINDOW_GLFW" }
	removedefines { "NOVA_WINDOW_NATIVE" }
