#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "code.h"
#include "abyss/spirv/spirv_compile.h"
#include "../context.h"

namespace Nova::abyss::nvk {

	ShaderCode::ShaderCode(const Shader::Stage stage, const std::filesystem::path& path) :
		ShaderCode(stage, spirv::file(path, stage))
	{}

	ShaderCode::ShaderCode(const Shader::Stage stage, const spirv::Binary& binary) :
		stage(stage),
		self(
			nova_abyss_api->dev.createShaderModule(
				vk::ShaderModuleCreateInfo{
					.codeSize = binary.size() * sizeof(spirv::Binary::value_type),
					.pCode = binary.data(),
				}, nova_abyss_api->alloc
			)
		)
	{ nova_bark_init("VK Shader Stage"); }

	ShaderCode::~ShaderCode() {
		nova_bark_term("VK Shader Stage");
		nova_abyss_api->dev.destroyShaderModule(self, nova_abyss_api->alloc);
	}

}

#endif // NOVA_ABYSS_VULKAN
