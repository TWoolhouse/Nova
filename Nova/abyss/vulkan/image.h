#pragma once
#include "vk.h"

namespace Nova::abyss::vkn {

	struct Image {
		vk::Image handle;
		vk::ImageView view;
	};

}