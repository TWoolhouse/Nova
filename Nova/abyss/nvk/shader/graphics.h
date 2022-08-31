#pragma once
#include "../vk.h"
#include "abyss/shader.h"
#include "abyss/shader_code.h"
#include "abyss/renderpass.h"

namespace Nova::abyss::nvk::shader {

	class NOVAPI Graphics : public Shader {
	public:
		Graphics(const abyss::Renderpass& renderpass, const std::initializer_list<abyss::ShaderCode>& stages);
		virtual ~Graphics() override;
	};

}