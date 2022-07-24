#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "shader.h"
#include "app.h"
#include "abyss/spirv/spirv_compile.h"

namespace Nova::abyss::vkn {

	constexpr vk::ShaderStageFlagBits shader_stage_flag(const Shader::Type type) {
		switch (type) {
		case Shader::Type::Vertex:	return vk::ShaderStageFlagBits::eVertex;
		case Shader::Type::Fragment:	return vk::ShaderStageFlagBits::eFragment;
		default:
			nova_bark_error("vkn::Shader::Type {} is currently not handled!", static_cast<std::underlying_type_t<Shader::Type>>(type));
			return vk::ShaderStageFlagBits{0};
		}
	}

	Shader::Shader(const Type type, const std::filesystem::path& path) : Shader(type, spirv::file(path, type)) {}

	Shader::Shader(const Type type, const spirv::Binary& binary)
		: m_module(
			nvk(device).createShaderModule({
				{},
				binary.size() * sizeof(spirv::Binary::value_type),
				binary.data()
			}, nvk(alloc))
		), m_shader_stage_info(
			{},
			shader_stage_flag(type),
			m_module,
			"main"
		) {}

	Shader::~Shader() {
		nvk(device).destroyShaderModule(m_module, nvk(alloc));
	}

}

#endif // NOVA_ABYSS_VULKAN
