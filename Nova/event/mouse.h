#pragma once
#include "event.h"
#include "input/mouse.h"

namespace Nova::event {

	class MouseButton : public Base {
	public:
		static constexpr auto type = Type::MouseButton;
		MouseButton(const input::Mouse button) : Base(type), button(button) {}
		MouseButton(const input::Mouse button, const Type tag) : Base(tag), button(button) {}
		const input::Mouse button;
	};

	class MouseButtonPress : public MouseButton {
	public:
		static constexpr auto type = Type::MouseButtonPress;
		MouseButtonPress(const input::Mouse button) : MouseButton(button, type) {}
	};

	class MouseButtonRelease : public MouseButton {
	public:
		static constexpr auto type = Type::MouseButtonRelease;
		MouseButtonRelease(const input::Mouse button) : MouseButton(button, type) {}
	};

	class MouseMove : public Base {
	public:
		static constexpr auto type = Type::MouseMove;
		MouseMove(const unsigned int x, const unsigned int y) : Base(type), pos(std::make_pair(x, y)) {}
		const input::MousePos pos;
		const unsigned int& x = pos.first;
		const unsigned int& y = pos.second;
	};

}