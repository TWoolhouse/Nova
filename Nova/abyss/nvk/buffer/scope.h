#pragma once
#include "meta/head.h"
#include "meta/meta.h"
#include "../vk.h"
#include "../context/vma.h"

namespace Nova::abyss::nvk::buffer {

	enum class Scope : VmaAllocationCreateFlags {
		None = 0,
		Bind = VmaAllocationCreateFlagBits::VMA_ALLOCATION_CREATE_MAPPED_BIT,
		Read = VmaAllocationCreateFlagBits::VMA_ALLOCATION_CREATE_HOST_ACCESS_RANDOM_BIT,
		Write = VmaAllocationCreateFlagBits::VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT,
	};

}

nova_meta_enum_str(Nova::abyss::nvk::buffer::Scope, scope);