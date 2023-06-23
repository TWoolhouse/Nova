#pragma once
#include "meta/head.h"
#include "vk.h"
#include "shader/stage.h"
#include "descriptor/layout.h"

namespace Nova::abyss::nvk {

	class NOVAPI Shader : public OPVK<Shader, vk::Pipeline> {
	public:
		using Stage = shader::Stage;

		Shader();
		virtual ~Shader();

		vk::Pipeline self;
		vk::PipelineLayout layout;
	};

}
