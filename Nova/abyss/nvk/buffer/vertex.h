#pragma once
#include "meta/head.h"
#include "../vk.h"

#include "abyss/buffer.h"
#include "abyss/interface/vertex_format.h"
#include "mlb/mlb.h"

namespace Nova::abyss::nvk::buffer {

	using Format = abyss::interface::Format<
		meta::pair::TV<int32_t,    vk::Format::eR32Sint>,
		meta::pair::TV<uint32_t,   vk::Format::eR32Uint>,
		meta::pair::TV<float,      vk::Format::eR32Sfloat>,
		meta::pair::TV<double,     vk::Format::eR64Sfloat>,
		meta::pair::TV<mlb::vec1,  vk::Format::eR32Sfloat>,
		meta::pair::TV<mlb::vec2,  vk::Format::eR32G32Sfloat>,
		meta::pair::TV<mlb::vec3,  vk::Format::eR32G32B32Sfloat>,
		meta::pair::TV<mlb::vec4,  vk::Format::eR32G32B32A32Sfloat>,
		meta::pair::TV<mlb::fvec1, vk::Format::eR32Sfloat>,
		meta::pair::TV<mlb::fvec2, vk::Format::eR32G32Sfloat>,
		meta::pair::TV<mlb::fvec3, vk::Format::eR32G32B32Sfloat>,
		meta::pair::TV<mlb::fvec4, vk::Format::eR32G32B32A32Sfloat>,
		meta::pair::TV<mlb::dvec1, vk::Format::eR64Sfloat>,
		meta::pair::TV<mlb::dvec2, vk::Format::eR64G64Sfloat>,
		meta::pair::TV<mlb::dvec3, vk::Format::eR64G64B64Sfloat>,
		meta::pair::TV<mlb::dvec4, vk::Format::eR64G64B64A64Sfloat>,
		meta::pair::TV<mlb::ivec1, vk::Format::eR32Sint>,
		meta::pair::TV<mlb::ivec2, vk::Format::eR32G32Sint>,
		meta::pair::TV<mlb::ivec3, vk::Format::eR32G32B32Sint>,
		meta::pair::TV<mlb::ivec4, vk::Format::eR32G32B32A32Sint>,
		meta::pair::TV<mlb::uvec1, vk::Format::eR32Uint>,
		meta::pair::TV<mlb::uvec2, vk::Format::eR32G32Uint>,
		meta::pair::TV<mlb::uvec3, vk::Format::eR32G32B32Uint>,
		meta::pair::TV<mlb::uvec4, vk::Format::eR32G32B32A32Uint>
	>;

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
