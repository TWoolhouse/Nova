#pragma once
#include "meta/head.h"
#include "vk.h"
#include "abyss/target.h"
#include "event/window.h"

namespace Nova::abyss::nvk {

	struct Renderpass : OPVK<Renderpass, vk::RenderPass> {
		vk::RenderPass self;
		Targets target;

		Renderpass();
		~Renderpass();

	protected:
		event::Ticket event_ticket;
		void create_targets();
	};

}
