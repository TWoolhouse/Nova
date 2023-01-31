#pragma once
#include "meta/head.h"
#include "../vk.h"

#include "abyss/buffer.h"
#include "format.h"

namespace Nova::abyss::nvk::buffer {

	template<typename T> requires requires {
		typename T::Spec;
	}
	struct Vertex;

	struct VertexGeneric {
	public:
		abyss::buffer::Buffer buffer;
		size_t size; // Number of vertices

		VertexGeneric(abyss::buffer::Buffer&& buffer, size_t size) : buffer(std::move(buffer)), size(size) {}
		template<typename T>
		VertexGeneric(Vertex<T>& buffer) : buffer(std::move(buffer.buffer)), size(buffer.buffer.size / sizeof(Vertex<T>::vertex_type)) {}
	};

	template<typename T> requires requires {
		typename T::Spec;
	}
	struct Vertex {
	public:
		using vertex_type = T;
		using Spec = T::Spec;

		static_assert(Spec::size_align == sizeof(vertex_type), "Vertex::Spec does not match the size of the Vertex T");
	protected:
		static consteval size_t attribute_count() { return Format::template get<Spec>().size(); }
		template<size_t I>
		static constexpr vk::VertexInputAttributeDescription attribute() {
			return vk::VertexInputAttributeDescription{
				.location = I,
				.binding = 0,
				.format = Format::template get<Spec>()[I],
				.offset = Format::template types<Spec>::template subpack<0, I>::size_align,
			};
		}
		template<size_t ...Is>
		static constexpr auto attributes(std::index_sequence<Is...>) {
			return std::array{ attribute<Is>()... };
		}
	public:
		static constexpr std::array<vk::VertexInputAttributeDescription, attribute_count()> attributes() { return attributes(std::make_index_sequence<attribute_count()>{}); }

		static constexpr vk::VertexInputBindingDescription binding() {
			return vk::VertexInputBindingDescription{
				.binding = 0,
				.stride = sizeof(vertex_type),
				.inputRate = vk::VertexInputRate::eVertex,
			};
		}

		// TODO: Expose scopes
		Vertex(size_t elements) : buffer(elements * sizeof(vertex_type), Type::Vertex, Scope::Bind | Scope::Write) {}
		Vertex(VertexGeneric& buffer) : buffer(std::move(buffer.buffer)) {
			nova_assert(
				buffer.size * sizeof(vertex_type) == this->buffer.size,
				"The generic Vertex buffer does not contain the correct number of elements for a Vertex buffer of this type T"
			);
		}
		~Vertex() {}

	public:
		abyss::buffer::Buffer buffer;
	};

}
