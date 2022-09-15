#pragma once
#include "meta/head.h"
#include "../vk.h"

#include "abyss/interface/buffer_vertex.h"
#include "abyss/interface/vertex_format.h"
#include "mlb/mlb.h"

namespace Nova::abyss::nvk::buffer {

	using Format = abyss::buffer::interface::Format<
		meta::TVPair<int32_t,    vk::Format::eR32Sint>,
		meta::TVPair<uint32_t,   vk::Format::eR32Uint>,
		meta::TVPair<float,      vk::Format::eR32Sfloat>,
		meta::TVPair<double,     vk::Format::eR64Sfloat>,
		meta::TVPair<mlb::vec1,  vk::Format::eR32Sfloat>,
		meta::TVPair<mlb::vec2,  vk::Format::eR32G32Sfloat>,
		meta::TVPair<mlb::vec3,  vk::Format::eR32G32B32Sfloat>,
		meta::TVPair<mlb::vec4,  vk::Format::eR32G32B32A32Sfloat>,
		meta::TVPair<mlb::fvec1, vk::Format::eR32Sfloat>,
		meta::TVPair<mlb::fvec2, vk::Format::eR32G32Sfloat>,
		meta::TVPair<mlb::fvec3, vk::Format::eR32G32B32Sfloat>,
		meta::TVPair<mlb::fvec4, vk::Format::eR32G32B32A32Sfloat>,
		meta::TVPair<mlb::dvec1, vk::Format::eR64Sfloat>,
		meta::TVPair<mlb::dvec2, vk::Format::eR64G64Sfloat>,
		meta::TVPair<mlb::dvec3, vk::Format::eR64G64B64Sfloat>,
		meta::TVPair<mlb::dvec4, vk::Format::eR64G64B64A64Sfloat>,
		meta::TVPair<mlb::ivec1, vk::Format::eR32Sint>,
		meta::TVPair<mlb::ivec2, vk::Format::eR32G32Sint>,
		meta::TVPair<mlb::ivec3, vk::Format::eR32G32B32Sint>,
		meta::TVPair<mlb::ivec4, vk::Format::eR32G32B32A32Sint>,
		meta::TVPair<mlb::uvec1, vk::Format::eR32Uint>,
		meta::TVPair<mlb::uvec2, vk::Format::eR32G32Uint>,
		meta::TVPair<mlb::uvec3, vk::Format::eR32G32B32Uint>,
		meta::TVPair<mlb::uvec4, vk::Format::eR32G32B32A32Uint>
	>;

	template<typename T> requires requires {
		typename T::Spec;
	}
	struct Vertex : public abyss::buffer::interface::Vertex {
	public:
		using Spec = T::Spec;

		static_assert(Spec::size_align == sizeof(T), "Vertex::Spec does not match the size of the Vertex T");
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
				.stride = sizeof(T),
				.inputRate = vk::VertexInputRate::eVertex,
			};
		}

		Vertex() {}
		~Vertex() {}

	};

}
