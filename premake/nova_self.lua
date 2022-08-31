openmp "On"

-- Linkage
if(nova_build_static) then
	defines "NOVA_BUILD_STATIC"
else
	removedefines "NOVA_BUILD_STATIC"
end

dofile "config.lua"
dofile "window.lua"
dofile "maths.lua"
dofile "abyss.lua"
