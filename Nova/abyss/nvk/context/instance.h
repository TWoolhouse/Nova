#pragma once
#include "vk.h"
#include "props.h"

namespace Nova::abyss::nvk {

	class Instance : public OPVK<Instance, vk::Instance> {
	public:
		vk::Instance self;
		vk::SurfaceKHR surface;

		#ifdef NOVA_ABYSS_DEBUG
		vk::DebugUtilsMessengerEXT logger;
		#endif // NOVA_ABYSS_DEBUG

		Instance(const prop::Setup&);
		~Instance();
	};

}
