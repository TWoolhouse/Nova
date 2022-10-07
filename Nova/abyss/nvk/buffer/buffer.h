#pragma once
#include "meta/head.h"
#include "../vk.h"
#include "../context/vma.h"

namespace Nova::abyss::nvk::buffer {

	struct Raw : public OPVK<Raw, vk::Buffer> {
		Raw(size_t size);

		vk::Buffer self;
		VmaAllocation allocation;

		Raw(vk::Buffer&& buffer, VmaAllocation&& allocation) : self(buffer), allocation(allocation) {}
		Raw(Raw&& other) noexcept : self(std::exchange(other.self, VK_NULL_HANDLE)), allocation(std::exchange(other.allocation, VK_NULL_HANDLE)) {}
		Raw& operator=(Raw&& other) noexcept {
			self = std::exchange(other.self, VK_NULL_HANDLE);
			allocation = std::exchange(other.allocation, VK_NULL_HANDLE);
			return *this;
		}

		~Raw();
	};

}