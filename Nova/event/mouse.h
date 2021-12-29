#pragma once
#include "event.h"
#include "input/mouse.h"

namespace Nova::event {

	class MouseButton : public Handle {
	public:
		static constexpr auto descriptor = Descriptor::MouseButton;
		MouseButton(const input::Mouse button) : Handle(descriptor), button(button) {}
		MouseButton(const input::Mouse button, const Descriptor des) : Handle(des), button(button) {}
		const input::Mouse button;
	};

	class MouseButtonPress : public MouseButton {
	public:
		static constexpr auto descriptor = Descriptor::MouseButtonPress;
		MouseButtonPress(const input::Mouse button) : MouseButton(button, descriptor) {}
	};

	class MouseButtonRelease : public MouseButton {
	public:
		static constexpr auto descriptor = Descriptor::MouseButtonRelease;
		MouseButtonRelease(const input::Mouse button) : MouseButton(button, descriptor) {}
	};

	class MouseMove : public Handle {
	public:
		static constexpr auto descriptor = Descriptor::MouseMove;
		MouseMove(const input::MousePos pos) : Handle(descriptor), pos(pos) {}
		MouseMove(const unsigned int x, const unsigned int y) : Handle(descriptor), pos(std::make_pair(x, y)) {}
		const input::MousePos pos;
		const unsigned int& x = pos.first;
		const unsigned int& y = pos.second;
	};

	class MouseScroll : public Handle {
	public:
		static constexpr auto descriptor = Descriptor::MouseScroll;
		MouseScroll(const int8_t z) : Handle(descriptor), dir(z) {}
		const int8_t dir;
	};

}