#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "pool.h"
#include "../context.h"

namespace Nova::abyss::nvk::descriptor {

	namespace exc {
		struct ChunkCapacity : public std::exception {
			virtual const char* what() const noexcept override {
				return "The Chunk has reached capacity!";
			}
		};
	}

	Set::~Set() {
		chunk->release(self);
	}

	Chunk::Chunk(Pool& parent) :
		pool(parent),
		self(NVK_CHECK(
			nova_abyss_api->dev.createDescriptorPool(parent.info_pool, nova_abyss_api->alloc),
			"Failed to create Descriptor Pool!"
		)) {}
	Chunk::~Chunk() {
		nova_abyss_api->dev.destroyDescriptorPool(self, nova_abyss_api->alloc);
	}

	Set Chunk::acquire() {
		if (!free_list.empty()) {
			auto set = free_list.top();
			free_list.pop();
			return { *this, set };
		}
		try {
			return Chunk::allocate();
		} catch (vk::OutOfPoolMemoryError exec) {
			throw exc::ChunkCapacity();
		}
	}
	Set Chunk::allocate() {
		auto info = pool.info_set;
		info.descriptorPool = self;
		return Set(*this, nova_abyss_api->dev.allocateDescriptorSets(info).front());
	}
	void Chunk::release(vk::DescriptorSet& set) {
		free_list.push(set);
		if (--count == 0)
			pool.release(*this);
	}

	Pool::Pool(const Layout& layout, Pool::Type type, uint32_t chunk_size) :
	_pool_sizes{
		{ type, chunk_size },
	}, info_pool{
		.maxSets = chunk_size,
		.poolSizeCount = static_cast<uint32_t>(_pool_sizes.size()),
		.pPoolSizes = _pool_sizes.data(),
	}, info_set{
		.descriptorSetCount = 1,
		.pSetLayouts = &layout.self,
	} {}

	Set Pool::acquire() {
		for (auto& chunk : chunks) {
			try {
				return chunk.acquire();
			} catch (const exc::ChunkCapacity&) {}
		}
		return expand().acquire();
	}
	Chunk& Pool::expand() {
		return chunks.emplace_back(*this);
	}
	void Pool::release(Chunk& chunk) {
		chunks.remove(chunk);
	}

	vk::DescriptorType Pool::type() const {
		return this->_pool_sizes.front().type;
	}


} // Nova::abyss::nvk::descriptor

#endif // NOVA_ABYSS_VULKAN
