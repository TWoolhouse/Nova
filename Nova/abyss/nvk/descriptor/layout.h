#pragma once
#include "meta/head.h"
#include "../vk.h"
#include "../shader/stage.h"

namespace Nova::abyss::nvk {

	struct Layout : public OPVK<Layout, vk::DescriptorSetLayout> {
		struct Binding {
			vk::DescriptorType type;
			shader::Stage stage;
		};
		struct Description {
			std::vector<Binding> bindings;
		};

		Layout() : self(VK_NULL_HANDLE) {}
		Layout(const Description& layout);
		~Layout();

		Layout(Layout&& other) noexcept : self(std::exchange(other.self, VK_NULL_HANDLE)) {}
		Layout& operator=(Layout&& other) noexcept {
			self = std::exchange(other.self, VK_NULL_HANDLE);
			return *this;
		}

		vk::DescriptorSetLayout self;
	};

}
