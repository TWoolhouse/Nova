#pragma once
#include "../vk.h"
#include "abyss/shader.h"
#include "abyss/shader_code.h"
#include "abyss/renderpass.h"
#include "abyss/buffer_vertex.h"
#include "layout.h"

namespace Nova::abyss::nvk::shader {

	class NOVAPI Graphics : public Shader {
	public:
		template<typename Vertex>
		Graphics(const abyss::Renderpass& renderpass, const std::initializer_list<abyss::ShaderCode>& stages, meta::pack<abyss::buffer::Vertex<Vertex>> buffer_type, Layout& layout)
			: Graphics(renderpass, stages,
				decltype(buffer_type)::get<0>::binding(),
				std::span{decltype(buffer_type)::get<0>::attributes().data(), decltype(buffer_type)::get<0>::attributes().size()},
				layout
			) {}
		virtual ~Graphics() override;
	protected:
		Graphics(const abyss::Renderpass& renderpass, const std::initializer_list<abyss::ShaderCode>& stages, vk::VertexInputBindingDescription binding, std::span<vk::VertexInputAttributeDescription> attributes, Layout& layout);
	};

}
