#pragma once
#include "../vk.h"
#include "../shader.h"
#include "abyss/spirv/spirv.h"

namespace Nova::abyss::nvk {

	class NOVAPI ShaderCode : public OPVK<ShaderCode, vk::ShaderModule> {
	public:

		// Relative to the shader directory
		ShaderCode(const Shader::Stage stage, const std::filesystem::path& path);
		ShaderCode(const Shader::Stage stage, const spirv::Binary& binary);

		~ShaderCode();

		Shader::Stage stage;
		vk::ShaderModule self;
	};

}
