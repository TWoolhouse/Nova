#pragma once
#include "meta/head.h"
#include "../vk.h"

namespace Nova::abyss::nvk::shader {

	enum class Stage : std::underlying_type_t<vk::ShaderStageFlagBits> {
		Vertex = cpp::to_underlying(vk::ShaderStageFlagBits::eVertex),
		Fragment = cpp::to_underlying(vk::ShaderStageFlagBits::eFragment),
	};

}

nova_meta_enum_str(Nova::abyss::nvk::shader::Stage, stage);