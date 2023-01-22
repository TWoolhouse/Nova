#pragma once
#include "meta/head.h"
#include "meta/version.h"
#include "window.h"

namespace Nova::core {

	struct Information {
		enum class WindowState : meta::smallest::uint<meta::bit(3)> {
			Window = meta::bit(0),
			Minimise = meta::bit(1),
			Maximise = meta::bit(2),
			Fullscreen = meta::bit(3),
		};
		std::string_view name;
		meta::version::Version version;
		Window& window;
		WindowState window_state;
	};

	struct Builder {
		friend class Application;
	protected:
		std::string_view name;
		meta::version::Version version;

		uint32_t width{ 64 }, height{ 64 };
		Information::WindowState window_state{ Information::WindowState::Window };
	public:

		Builder(const std::string_view& name, const meta::version::Version version) : name(name), version(version) {}
		inline auto& window_size(const uint32_t width, const uint32_t height) {
			this->width = width; this->height = height;
			return *this;
		}
		inline auto& window_size(const Information::WindowState state) {
			this->window_state = state;
			return *this;
		}
	};

} // namespace Nova::core
