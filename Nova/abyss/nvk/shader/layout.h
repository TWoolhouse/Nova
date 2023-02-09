#pragma once
#include "meta/head.h"
#include "../vk.h"
#include "nvtl/cector.h"
#include "nvtl/hash.h"
#include "stage.h"

namespace Nova::abyss::nvk::shader {

	struct Layout {
		struct BindPoint {
			enum class Type : std::underlying_type_t<vk::DescriptorType> {
				Uniform = cpp::to_underlying(vk::DescriptorType::eUniformBuffer),
			} type;
			uint32_t size;
			shader::Stage stage;
			// TODO: Add location [0, 4)

			constexpr bool operator==(const BindPoint&) const = default;
			constexpr auto operator<=>(const BindPoint&) const = default;
		};

		Layout(std::initializer_list<BindPoint> points) : points(points) {}
		nvtl::Cector<BindPoint> points;

		constexpr bool operator==(const Layout&) const = default;
		constexpr auto operator<=>(const Layout&) const = default;
	};

}

template<>
struct ::std::hash<Nova::abyss::nvk::shader::Layout::BindPoint> {
	constexpr std::size_t operator()(Nova::abyss::nvk::shader::Layout::BindPoint const& point) const noexcept {
		return Nova::nvtl::hash_all(point.type, point.size, point.stage);
	}
};

template<>
struct ::std::hash<Nova::abyss::nvk::shader::Layout> {
	constexpr std::size_t operator()(Nova::abyss::nvk::shader::Layout const& layout) const noexcept {
		std::size_t hash = 0;
		for (const auto& bind_point : layout.points)
			hash = Nova::nvtl::hash_combine(hash, Nova::nvtl::hash(bind_point));
		return hash;
	}
};

nova_meta_enum_str(Nova::abyss::nvk::shader::Layout::BindPoint::Type, type);
