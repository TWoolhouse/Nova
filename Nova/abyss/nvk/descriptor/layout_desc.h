#pragma once
#include "meta/head.h"
#include "../vk.h"
#include "abyss/shader.h"

namespace Nova::abyss::nvk {

	struct LayoutDescription {
		struct Binding {
			vk::DescriptorType type;
			abyss::Shader::Stage stage;
		};
		std::vector<Binding> bindings;
	};

}