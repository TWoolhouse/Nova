#pragma once
#include "meta/head.h"
#include "../vk.h"
#include "../shader/layout.h"

namespace Nova::abyss::nvk::descriptor {

	struct Layout : public OPVK<Layout, vk::DescriptorSetLayout> {
		Layout() : self(VK_NULL_HANDLE) {}
		Layout(const shader::Layout& layout);
		~Layout();

		Layout(Layout&& other) noexcept : self(std::exchange(other.self, VK_NULL_HANDLE)) {}
		Layout& operator=(Layout&& other) noexcept {
			self = std::exchange(other.self, VK_NULL_HANDLE);
			return *this;
		}

		vk::DescriptorSetLayout self;
	};

}
