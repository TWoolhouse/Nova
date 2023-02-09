#pragma once
#include "meta/head.h"
#include "../vk.h"
#include "pool.h"
#include "../buffer/uniform.h"

namespace Nova::abyss::nvk::descriptor {

	struct Set::PointQueue {
	public:
		PointQueue(Set& set);

	public:
		template<typename T>
		PointQueue& point(uint32_t location, const buffer::Uniform<T>& buffer) {
			info_buffers.emplace_back(
				location,
				vk::DescriptorBufferInfo{
					buffer.buffer.self, // buffer
					0, // offset
					sizeof(T), // range
				}
			);
			return *this;
		}

		void done() const;

	protected:
		Set& set;
		std::vector<std::pair<uint32_t, vk::DescriptorBufferInfo>> info_buffers;
	};

} // namespace Nova::abyss::nvk::descriptor
