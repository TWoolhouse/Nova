#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "layout.h"
#include "../context.h"
#include "layout_desc.h"

namespace Nova::abyss::nvk {

	Layout::Layout(Layout::Description& layout) {
		nova_bark_init("VK Descriptor Layout");

		std::vector<vk::DescriptorSetLayoutBinding> bindings{};
		bindings.reserve(layout.bindings.size());
		{
			uint32_t index = 0;
			for (const auto& binding : layout.bindings) {
				bindings.emplace_back(vk::DescriptorSetLayoutBinding{
					.binding = index++,
					.descriptorType = meta::enm::to<vk::DescriptorType>(binding.type),
					.descriptorCount = 1,
					.stageFlags = meta::enm::to<vk::ShaderStageFlagBits>(binding.stage),
				});
			}
		}

		vk::DescriptorSetLayoutCreateInfo info{
			.bindingCount = static_cast<uint32_t>(bindings.size()),
			.pBindings = bindings.data(),
		};

		self = NVK_CHECK(nova_abyss_api->dev.createDescriptorSetLayout(info, nova_abyss_api->alloc));
	}

	Layout::~Layout() {
		nova_bark_term("VK Descriptor Layout: {}", (void*)self);
		nova_abyss_api->dev.destroyDescriptorSetLayout(self, nova_abyss_api->alloc);
	}

}

#endif // NOVA_ABYSS_VULKAN
