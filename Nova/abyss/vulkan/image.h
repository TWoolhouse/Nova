#pragma once

namespace Nova::abyss::vkn {

	struct Image {
		Image(const unsigned int width, const unsigned int height, const vk::Format& format, const vk::ImageUsageFlags& usage);
		~Image();

		vk::Image handle;
		vk::ImageView view;
		vk::DeviceMemory memory;
	};

}