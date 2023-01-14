#pragma once
#include "meta/head.h"
#include "meta/meta.h"
#include "../vk.h"
#include "../context/vma.h"

namespace Nova::abyss::nvk::buffer {

	enum class Scope : VmaAllocatorCreateFlags {
		// No Scope
		None = 0,
		// Persistently mapped data
		Bind = cpp::to_underlying(VmaAllocationCreateFlagBits::VMA_ALLOCATION_CREATE_MAPPED_BIT),
		// Read from the mapped data
		Read = cpp::to_underlying(VmaAllocationCreateFlagBits::VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT),
		// Write to the mapped data
		Write = cpp::to_underlying(VmaAllocationCreateFlagBits::VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT),
	};

}

nova_meta_enum_str(Nova::abyss::nvk::buffer::Scope, scope);
