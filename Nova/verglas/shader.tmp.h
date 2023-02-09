#pragma once
#include "meta/head.h"
#include "abyss/abyss.h"
#include "abyss/shader_graphics.h"

#include "abyss/nvk/descriptor/pool.h"
#include "abyss/flock.h"

namespace Nova::verglas {

	template<typename Vertex>
	class Shader {
	public:
		using vertex_type = Vertex;

		Shader(std::shared_ptr<abyss::nvk::descriptor::Manager::LayoutPool> descriptor_pool) :
			graphics(nova_abyss_app->tower.renderpass, {
				{ abyss::Shader::Stage::Vertex, "start/simple/.vert" },
				{ abyss::Shader::Stage::Fragment, "start/simple/.frag" },
			}, meta::pack<abyss::buffer::Vertex<vertex_type>>{}),
			lp(descriptor_pool),
			descriptors(lp->pool)
		{}

	protected:
		abyss::shader::Graphics graphics;
		std::shared_ptr<abyss::nvk::descriptor::Manager::LayoutPool> lp;
		abyss::Flock<abyss::nvk::descriptor::Set> descriptors;
	};

} // namespace Nova::verglas
