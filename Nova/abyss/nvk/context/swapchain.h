#pragma once
#include "vk.h"
#include "props.h"
#include "event/event.h"
#include "queues.h"
#include "../sync.h"

namespace Nova::abyss::nvk {

	class Swapchain : public OPVK<Swapchain, vk::SwapchainKHR> {
	public:
		using FrameIndex = uint8_t;
		// Number of frames that can be drawn to.
		constexpr static FrameIndex IMAGE_BUFFERING = 3;

		vk::SwapchainKHR self;
		vk::Format format;

		struct FrameImage {
			friend class Swapchain;
			vk::Image image;
			vk::ImageView view;
			~FrameImage();
		};
		std::vector<FrameImage> frames;

		Swapchain();
		~Swapchain();

		FrameIndex acquire_frame(Fence& in_flight, Semaphore& image_avalible);

		void resize();

	protected:
		bool create();
		void extract_images();

		vk::Extent2D extent(const vk::SurfaceCapabilitiesKHR& capabilities);
		void shared_families();

		// Revalidate the chosen settings in case the surface has drastically changed to aid in debugging
		static bool revalidate_format(const vk::SurfaceFormatKHR& format);
		static bool revalidate_present_mode(const vk::PresentModeKHR& present_mode);

	};

}
