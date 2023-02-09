#pragma once
#include "meta/head.h"
#include "../vk.h"

#include "abyss/buffer.h"
#include "format.h"

namespace Nova::abyss::nvk::buffer {

	template<typename T>
	struct Uniform;

	struct UniformGeneric {
	public:
		abyss::buffer::Buffer buffer;

		UniformGeneric(abyss::buffer::Buffer&& buffer) : buffer(std::move(buffer)) {}
		template<typename T>
		UniformGeneric(Uniform<T>& buffer) : buffer(std::move(buffer.buffer)) {}
	};

	template<typename T>
	struct Uniform {
	public:
		using uniform_type = T;
	protected:
	public:
		// TODO: Expose scopes
		Uniform() : buffer(sizeof(uniform_type), Type::Uniform, Scope::Bind | Scope::Write) {}
		Uniform(UniformGeneric& buffer) : buffer(std::move(buffer.buffer)) {
			nova_assert(
				sizeof(uniform_type) <= this->buffer.size,
				"The generic Uniform buffer is not the correct size for a Uniform buffer of this type T"
			);
		}
		~Uniform() {}

	public:
		abyss::buffer::Buffer buffer;
	};

}
