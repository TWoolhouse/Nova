#pragma once
#include "meta/head.h"
#include "bark/bark.h"
#include "vk.h"

#define VMA_ASSERT(expr) nova_assert(expr, "Vulkan VMA: " #expr)
#ifdef NOVA_DEBUG
#define VMA_DEBUG_DONT_EXCEED_MAX_MEMORY_ALLOCATION_COUNT (1)
#endif // NOVA_DEBUG

#include "vk_mem_alloc.h"
