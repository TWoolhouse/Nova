#pragma once
#include "meta/head.h"
#include "vk.h"

namespace Nova::abyss::nvk {

	class NOVAPI Shader : public OPVK<Shader, vk::Pipeline> {
	public:
		enum class Stage {
			Vertex = static_cast<std::underlying_type_t<vk::ShaderStageFlagBits>>(vk::ShaderStageFlagBits::eVertex),
			Fragment = static_cast<std::underlying_type_t<vk::ShaderStageFlagBits>>(vk::ShaderStageFlagBits::eFragment),
		};
	
		Shader();
		virtual ~Shader();

		vk::Pipeline self;
		vk::PipelineLayout layout;
	};

}

nova_meta_enum_str(Nova::abyss::nvk::Shader::Stage, stage);