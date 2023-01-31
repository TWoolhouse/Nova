#pragma once
#include "meta/head.h"
#include "../vk.h"
#include "abyss/interface/buffer_format.h"
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

} // namespace Nova::abyss::nvk::buffer