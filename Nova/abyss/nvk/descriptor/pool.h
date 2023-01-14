#pragma once
#include "meta/head.h"
#include "../vk.h"

namespace Nova::abyss::nvk::descriptor {

	struct Pool : public OPVK<Pool, vk::DescriptorPool> {
		vk::DescriptorPool self;

		Pool();
		~Pool();
	};

}