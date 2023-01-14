#pragma once
#include "meta/head.h"
#include "../vk.h"

namespace Nova::abyss::nvk {

	struct LayoutDescription;

	struct Layout : public OPVK<Layout, vk::DescriptorSetLayout> {
		using Description = LayoutDescription;

		// Layout(LayoutCache::Control& control) // The control block from the layout cache

		Layout() : self(VK_NULL_HANDLE) {}
		Layout(Layout::Description& layout);
		~Layout();

		vk::DescriptorSetLayout self;
	};

	struct LayoutCache {};
}