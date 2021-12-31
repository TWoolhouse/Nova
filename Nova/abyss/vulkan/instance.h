#pragma once
#include "vk.h"
#include "context.h"

namespace Nova::abyss {

	void create_instance(Context& cxt, const std::string_view& name);
	void destroy_instance(const Context& cxt);

}