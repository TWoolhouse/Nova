#pragma once
#include "event.h"

namespace Nova::event {

	class WindowClose : public Base {
	public:
		static constexpr auto type = Type::WindowClose;
		WindowClose() : Base(type) {}
	};

	class WindowFocusGain : public Base {
	public:
		static constexpr auto type = Type::WindowFocusGain;
		WindowFocusGain() : Base(type) {}
	};
	class WindowFocusLost : public Base {
	public:
		static constexpr auto type = Type::WindowFocusLost;
		WindowFocusLost() : Base(type) {}
	};

	class WindowMove : public Base {
	public:
		static constexpr auto type = Type::WindowMove;
		WindowMove() : Base(type) {}
	};

	class WindowResize : public Base {
	public:
		static constexpr auto type = Type::WindowResize;
		WindowResize(const unsigned int width, const unsigned int height) : Base(type), width(width), height(height) {}
		WindowResize(const unsigned int width, const unsigned int height, const Type tag) : Base(tag), width(width), height(height) {}
		const unsigned int width, height;
	};
	class WindowResizeScreen : public WindowResize {
	public:
		static constexpr auto type = Type::WindowResizeScreen;
		WindowResizeScreen(const unsigned int width, const unsigned int height) : WindowResize(width, height, type) {}
	};
	class WindowResizeFrame : public WindowResize {
	public:
		static constexpr auto type = Type::WindowResizeFrame;
		WindowResizeFrame(const unsigned int width, const unsigned int height) : WindowResize(width, height, type) {}
	};
}