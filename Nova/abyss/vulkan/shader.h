#pragma once
#include "vk.h"
#include "abyss/spirv/spirv.h"

namespace Nova::abyss::vkn {

	class Shader {
	public:
		enum class Type {
			Vertex,
			Fragment,
			Default,
		};

		// Relative to the shader directory
		Shader(const Type type, const std::filesystem::path& path);
		Shader(const Type type, const spirv::Binary& binary);

		~Shader();

		operator vk::PipelineShaderStageCreateInfo() const { return m_shader_stage_info; }
	protected:
		vk::ShaderModule m_module;
		vk::PipelineShaderStageCreateInfo m_shader_stage_info;
	};

}
