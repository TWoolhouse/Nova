#pragma once
#include "meta/head.h"
#include "null.h"
#include "abyss/shader.h"
#include "abyss/spirv/spirv.h"

namespace Nova::abyss::spec {

	template<typename T>
	concept ShaderCode = Null<T> && requires () {
		T(abyss::Shader::Stage{}, "Path/to/shader/code"sv);
		T(abyss::Shader::Stage{}, spirv::Binary{});
	};

}
