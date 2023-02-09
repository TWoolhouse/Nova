#pragma once
#include "meta/head.h"
#include "../vk.h"
#include "layout.h"
#include "abyss/flock.h"

namespace Nova::abyss::nvk::descriptor {

	struct NOVAPI Set;
	class NOVAPI Chunk;
	class NOVAPI Pool;

	struct NOVAPI Set : public OPVK<Set, vk::DescriptorSet> {
		//template<typemame Layout>
		// TODO: Typed Set
	protected:
		friend class Chunk;
		Set(Chunk& chunk, vk::DescriptorSet descriptor_set) : chunk(&chunk), self(descriptor_set) {}
	public:
		~Set();
		Set(Set&& other) noexcept : self(std::exchange(self, VK_NULL_HANDLE)), chunk(other.chunk) {}
		Set& operator=(Set&& other) noexcept {
			self = std::exchange(other.self, VK_NULL_HANDLE);
			chunk = other.chunk;
			return *this;
		}
	public:
		vk::DescriptorSet self;
	protected:
		Chunk* chunk;

	public:
		struct PointQueue;
		friend struct PointQueue;
		NODISCARD PointQueue set();
	};

	class NOVAPI Chunk {
	public:
		Chunk(Pool& parent);
		~Chunk();

		Set acquire();
		void release(vk::DescriptorSet& set);

	protected:
		Set allocate();

	protected:
		size_t count = 0;
		std::stack<vk::DescriptorSet> free_list{};
		friend struct Set::PointQueue;
		Pool& pool;
		vk::DescriptorPool self;

	public:
		constexpr auto operator==(const Chunk& other) const noexcept {
			return self == other.self;
		}
	};

	class NOVAPI Pool {
	public:
		using Type = vk::DescriptorType;
		// layout& must stay alive for the lifetime of this Pool.
		Pool(const Layout& layout, Pool::Type type, uint32_t chunk_size);

		Set acquire();
	protected:
		friend class Chunk;
		Chunk& expand();
		void release(Chunk& chunk);
	protected:
		std::list<Chunk> chunks;
		std::array<vk::DescriptorPoolSize, 1> _pool_sizes;
		vk::DescriptorPoolCreateInfo info_pool;
		vk::DescriptorSetAllocateInfo info_set;

		friend struct Set::PointQueue;
		vk::DescriptorType type() const;
	};

}

namespace Nova::abyss {

	template<>
	struct Flock<nvk::descriptor::Set> : protected nvtl::Cector<nvk::descriptor::Set> {
		// FIXME: Make this in the abyss section without reference to nvk?
	protected:
		using Super = nvtl::Cector<nvk::descriptor::Set>;
	public:
		using value_type = Super::value_type;
		Flock(nvk::descriptor::Pool& pool) : Super(interface::flock_size(), std::false_type{}) {
			for (auto& descriptor : *this)
				descriptor = pool.acquire();
		}

		Super::reference operator[](abyss::Flight& flight) {
			return Super::operator[](0);
		}
	};

} // namespace Nova::abyss
