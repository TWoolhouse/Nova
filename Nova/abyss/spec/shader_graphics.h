#pragma once
#include "meta/head.h"
#include "null.h"
#include "abyss/shader.h"
#include "abyss/shader_code.h"
#include "abyss/buffer_vertex.h"
#include "buffer/vertex.h" // For example Vertex

namespace Nova::abyss::spec::shader {

	template<typename T>
	concept Graphics = Null<T> && std::is_base_of_v<abyss::Shader, T> && requires (const abyss::Renderpass& renderpass, abyss::ShaderCode shader_code, abyss::nvk::buffer::Vertex<spec::buffer::_V> vertex_buffer) {
		T(renderpass, { shader_code, shader_code, shader_code }, vertex_buffer);
	};

}
