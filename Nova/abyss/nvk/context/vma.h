#pragma once
#include "meta/head.h"
#include "_vma.h"

namespace Nova::abyss::nvk {

	class VMA {
	public:
		VmaAllocator self;

		NODISCARD INLINE constexpr operator VmaAllocator() { return self; }
		NODISCARD INLINE constexpr operator const VmaAllocator() const { return self; }

		VMA();
		~VMA();
	protected:

	};

}
