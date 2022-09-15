#pragma once
#include "meta/head.h"
#include "../vk.h"
#include "../context/vma.h"

namespace Nova::abyss::nvk::buffer {

	struct Raw{
		vk::Buffer buffer;
		VmaAllocation allocation;

		Raw(vk::Buffer&& buffer, VmaAllocation&& allocation) : buffer(buffer), allocation(allocation) {}
		Raw(Raw&& other) : buffer(std::exchange(other.buffer, VK_NULL_HANDLE)), allocation(std::exchange(other.allocation, VK_NULL_HANDLE)) {}
		Raw& operator=(Raw&& other) {
			buffer = std::exchange(other.buffer, VK_NULL_HANDLE);
			allocation = std::exchange(other.allocation, VK_NULL_HANDLE);
			return *this;
		}

		~Raw();
	};

	NODISCARD Raw create(size_t size);

}