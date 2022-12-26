#pragma once
#include "meta/head.h"
#include "../vk.h"
#include "../context/vma.h"
#include "type.h"
#include "scope.h"

namespace Nova::abyss::nvk::buffer {

	struct NOVAPI Buffer : public OPVK<Buffer, vk::Buffer> {
		size_t size;
		Type type;
		Scope scope;
		vk::Buffer self;
		VmaAllocation allocation;

		Buffer(size_t size, Type type, Scope scope);

		Buffer(Buffer&& other) noexcept : size(other.size), type(other.type), scope(other.scope), self(std::exchange(other.self, VK_NULL_HANDLE)), allocation(std::exchange(other.allocation, VK_NULL_HANDLE)) {}
		Buffer& operator=(Buffer&& other) noexcept {
			self = std::exchange(other.self, VK_NULL_HANDLE);
			allocation = std::exchange(other.allocation, VK_NULL_HANDLE);
			return *this;
		}

		void* acquire();
		void  release();
		void* map();

		~Buffer();
	};

	namespace variant {
		template<typename T>
		concept is = !std::same_as<Buffer, T>;

		inline constexpr bool acquirable(Scope scope) { return meta::etest(scope, Scope::Write | Scope::Read); }
		inline constexpr bool releasable(Scope scope) { return acquirable(scope); }
		inline constexpr bool mapped(Scope scope) { return meta::etest(scope, Scope::Bind | Scope::Write | Scope::Read); }
	}

	//template<Type T, Scope A> struct BufferT : public Buffer {
	//	static constexpr auto type = T;
	//	static constexpr auto scope = A;
	//	BufferT(size_t size) : Buffer(size, variant) {}


	//	void* map() {
	//		//static_assert(variant::)
	//		return Buffer::map();
	//	}

	//};


}
