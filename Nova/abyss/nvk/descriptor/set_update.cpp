#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "set_update.h"
#include "../context.h"

namespace Nova::abyss::nvk::descriptor {

	Set::PointQueue Set::set() { return *this; }
	Set::PointQueue::PointQueue(Set& set) : set(set) {}

	void Set::PointQueue::done() const {
		const auto size = info_buffers.size();
		auto writes_memory = std::make_unique_for_overwrite<vk::WriteDescriptorSet[]>(size);
		auto writes_it = writes_memory.get();

		const auto pool_type = set.chunk->pool.type();

		for (const auto& info : info_buffers) {
			*writes_it++ = vk::WriteDescriptorSet{
				.dstSet = set.self,
				.dstBinding = info.first,
				.dstArrayElement = 0, // TODO: What does this do?
				.descriptorCount = 1, // Ditto
				.descriptorType = pool_type,
				.pBufferInfo = &info.second,
			};
		}

		nova_abyss_api->dev.updateDescriptorSets(static_cast<uint32_t>(size), writes_memory.get(), 0, nullptr);

	}

} // Nova::abyss::nvk::descriptor

#endif // NOVA_ABYSS_VULKAN
