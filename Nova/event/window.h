#pragma once
#include "event.h"

namespace Nova::event {

	class WindowClose : public Handle {
	public:
		static constexpr auto descriptor = Descriptor::WindowClose;
		WindowClose() : Handle(descriptor) {}
	};

	class WindowFocusGain : public Handle {
	public:
		static constexpr auto descriptor = Descriptor::WindowFocusGain;
		WindowFocusGain() : Handle(descriptor) {}
	};
	class WindowFocusLost : public Handle {
	public:
		static constexpr auto descriptor = Descriptor::WindowFocusLost;
		WindowFocusLost() : Handle(descriptor) {}
	};

	class WindowMove : public Handle {
	public:
		static constexpr auto descriptor = Descriptor::WindowMove;
		WindowMove() : Handle(descriptor) {}
	};

	class WindowResize : public Handle {
	public:
		static constexpr auto descriptor = Descriptor::WindowResize;
		WindowResize(const unsigned int width, const unsigned int height) : Handle(descriptor), width(width), height(height) {}
		WindowResize(const unsigned int width, const unsigned int height, const Descriptor des) : Handle(des), width(width), height(height) {}
		const unsigned int width, height;
	};
	class WindowResizeScreen : public WindowResize {
	public:
		static constexpr auto descriptor = Descriptor::WindowResizeScreen;
		WindowResizeScreen(const unsigned int width, const unsigned int height) : WindowResize(width, height, descriptor) {}
	};
	class WindowResizeFrame : public WindowResize {
	public:
		static constexpr auto descriptor = Descriptor::WindowResizeFrame;
		WindowResizeFrame(const unsigned int width, const unsigned int height) : WindowResize(width, height, descriptor) {}
	};
}