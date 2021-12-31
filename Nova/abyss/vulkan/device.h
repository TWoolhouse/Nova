#pragma once
#include "vk.h"
#include "context.h"

namespace Nova::abyss {

	class Device {
		public:
			vk::Device device;
		static void slct_dvc(const Context& cxt) {
			const auto devices = cxt.instance.enumeratePhysicalDevices();
			for (auto& device : devices) {
				nova_bark_debug("Device {}", device.getProperties().deviceName);
			}
		}
	};

}