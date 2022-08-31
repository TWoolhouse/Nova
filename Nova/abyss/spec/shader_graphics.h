#pragma once
#include "meta/head.h"
#include "null.h"
#include "abyss/shader.h"
#include "abyss/shader_code.h"

namespace Nova::abyss::spec::shader {

	template<typename T>
	concept Graphics = Null<T> && std::is_base_of_v<abyss::Shader, T> && requires (const abyss::Renderpass& renderpass, abyss::ShaderCode shader_code) {
		T(renderpass, { shader_code, shader_code, shader_code });
	};

}
