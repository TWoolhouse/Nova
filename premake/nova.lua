dofile "nova_self.lua"

dependson "Nova"
includedirs { "../Nova/" }
links { "nova.lib" }
libdirs { "%{cfg.buildtarget.directory}" }
