#pragma once
#include "meta/head.h"
#include "bark/bark.h"
#define VULKAN_HPP_ASSERT(cond) nova_assert(cond, "Vulkan: " #cond)
#define VULKAN_HPP_NO_CONSTRUCTORS
#define VULKAN_HPP_NO_SETTERS
#define VULKAN_HPP_NO_SMART_HANDLE
#include <vulkan/vulkan.hpp>
