#pragma once
#include "meta/head.h"
#include "vk.h"
#include "descriptor/layout.h"

namespace Nova::abyss::nvk {

	class NOVAPI Shader : public OPVK<Shader, vk::Pipeline> {
	public:
		enum class Stage : std::underlying_type_t<vk::ShaderStageFlagBits> {
			Vertex = cpp::to_underlying(vk::ShaderStageFlagBits::eVertex),
			Fragment = cpp::to_underlying(vk::ShaderStageFlagBits::eFragment),
		};

		Shader();
		virtual ~Shader();

		vk::Pipeline self;
		vk::PipelineLayout layout;
		Layout descriptor;
	};

}

nova_meta_enum_str(Nova::abyss::nvk::Shader::Stage, stage);
