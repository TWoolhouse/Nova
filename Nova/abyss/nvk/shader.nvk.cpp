#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN
#include "shader.h"
#include "context.h"

namespace Nova::abyss::nvk {

	Shader::Shader() {}

	Shader::~Shader() {
		nova_bark_term("VK Shader");
		nova_abyss_api->dev.destroyPipelineLayout(layout, nova_abyss_api->alloc);
		nova_abyss_api->dev.destroyPipeline(self, nova_abyss_api->alloc);
	}

}

#endif // NOVA_ABYSS_VULKAN
