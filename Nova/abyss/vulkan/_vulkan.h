#pragma once
#include "log/log.h"
#define VULKAN_HPP_ASSERT(cond) nova_assert(cond, "Vulkan"sv)
#include <vulkan/vulkan.hpp>
