#pragma once
#include "../vk.h"
#include "abyss/shader.h"
#include "abyss/shader_code.h"
#include "abyss/renderpass.h"
#include "abyss/buffer_vertex.h"

namespace Nova::abyss::nvk::shader {

	class NOVAPI Graphics : public Shader {
	public:
		template<typename Vertex>
		Graphics(const abyss::Renderpass& renderpass, const std::initializer_list<abyss::ShaderCode>& stages, abyss::buffer::Vertex<Vertex> buffer) 
			: Graphics(renderpass, stages, buffer.binding(), std::span{buffer.attributes().data(), buffer.attributes().size()}) {}
		virtual ~Graphics() override;
	protected:
		Graphics(const abyss::Renderpass& renderpass, const std::initializer_list<abyss::ShaderCode>& stages, vk::VertexInputBindingDescription binding, std::span<vk::VertexInputAttributeDescription> attributes);
	};

}