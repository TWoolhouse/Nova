openmp "On"

-- Linkage
if(nova_build_static) then
	defines "NOVA_BUILD_LINK_STATIC"
else
	defines "NOVA_BUILD_LINK_DYNAMIC"
end

dofile "config.lua"
dofile "window.lua"
dofile "maths.lua"
dofile "abyss.lua"
