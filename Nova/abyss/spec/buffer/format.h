#pragma once
#include "meta/head.h"
#include "meta/pack.h"
#include "../null.h"
#include "mlb/mlb.h"

namespace Nova::abyss::spec::buffer {

	template<typename T>
	concept Format = Null<T> && meta::pack<>::apply<nova_meta_concept(std::same_as), meta::pack<
		int32_t,
		uint32_t,
		float,
		double,
		mlb::vec1,
		mlb::vec2,
		mlb::vec3,
		mlb::vec4,
		mlb::fvec1,
		mlb::fvec2,
		mlb::fvec3,
		mlb::fvec4,
		mlb::dvec1,
		mlb::dvec2,
		mlb::dvec3,
		mlb::dvec4,
		mlb::ivec1,
		mlb::ivec2,
		mlb::ivec3,
		mlb::ivec4,
		mlb::uvec1,
		mlb::uvec2,
		mlb::uvec3,
		mlb::uvec4
	>, typename T::Map::key_types>();

}