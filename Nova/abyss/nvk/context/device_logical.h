#pragma once
#include "vk.h"
#include "setup_props.h"
#include "queues.h"

namespace Nova::abyss::nvk::Logical {

	NODISCARD vk::Device create(const Setup& properties, vk::PhysicalDevice& physical, Queues& queues);

}
