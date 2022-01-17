#pragma once
#include "meta/head.h"
#include "bark/bark.h"
#include "nvtl/nvtl.h"
#include "blip/blip.h"
#include "meta/concept.h"
#include "meta/function.h"

#include "mlb/maths.h" // Maybe the rest of the maths library

#ifdef NOVA_EXPORT
	#if defined(NOVA_ABYSS_VULKAN)
#include "abyss/vulkan/_vulkan.h"
	#endif // Abyss
#endif // NOVA_EXPORT
