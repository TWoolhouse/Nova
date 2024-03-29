#pragma once
#include "vk.h"
#include "props.h"
#include "queues.h"

namespace Nova::abyss::nvk::Logical {

	NODISCARD vk::Device create(const prop::Setup& properties, vk::PhysicalDevice& physical, Queues& queues);

}
