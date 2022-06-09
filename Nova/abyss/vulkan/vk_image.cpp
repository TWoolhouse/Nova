#include "npch.h"
#ifdef NOVA_ABYSS_VULKAN_NOPE
#include "image.h"

namespace Nova::abyss::vkn {

	Image::Image(const unsigned int width, const unsigned int height, const vk::Format& format, const vk::ImageUsageFlags& usage) {
		vk::ImageCreateInfo create_info{
			vk::ImageCreateFlags{},
			vk::ImageType::e2D,
			format,
			{ width, height, 1 }, //TODO: Depth
			4, // TODO: MipMap Levels
			1, // TODO: Array Layers
			vk::SampleCountFlagBits::e1, // TODO: SampleCount
			vk::ImageTiling::eOptimal, // TODO: Tiling
			usage,
			vk::SharingMode::eExclusive, // TODO: SharingMode
		};
		//create_info.setInitialLayout(vk::ImageLayout::eUndefined); // TODO: Translate Image Format

		svk->device.logical.createImage(create_info, svk->cxt.alloc);
	}

	Image::~Image() {
		svk->device.logical.destroyImage(handle, svk->cxt.alloc);
	}


}

#endif // NOVA_ABYSS_VULKAN
