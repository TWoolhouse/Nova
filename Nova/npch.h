#pragma once
#include "defines.h"
#include "log/log.h"

#ifdef NOVA_EXPORT
	#if defined(NOVA_ABYSS_VULKAN)
#include "abyss/vulkan/_vulkan.h"
	#endif // Abyss
#endif // NOVA_EXPORT