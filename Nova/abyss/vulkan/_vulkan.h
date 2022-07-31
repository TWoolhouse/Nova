#pragma once
#include "meta/head.h"
#include "bark/bark.h"
#define VULKAN_HPP_ASSERT(cond) nova_assert(cond, "Vulkan"sv)
#define VULKAN_HPP_NO_CONSTRUCTORS
#define VULKAN_HPP_NO_SETTERS
#include <vulkan/vulkan.hpp>
