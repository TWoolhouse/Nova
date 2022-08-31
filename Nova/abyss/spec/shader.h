#pragma once
#include "meta/head.h"
#include "null.h"

namespace Nova::abyss::spec {

	template<typename T>
	concept Shader_Stage = std::is_scoped_enum_v<T> && requires {
		T::Vertex;
		T::Fragment;
	};

	template<typename T>
	concept Shader = Null<T> && requires (T shader) {
		typename T::Stage;
		requires Shader_Stage<typename T::Stage>;
	};

}
