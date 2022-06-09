#pragma once
#include "event/key.h"
#include "event/mouse.h"
#include "event/window.h"
#include "input/state.h"

namespace Nova::platform::event {
	inline void key_down(const Nova::input::Key key) {
		Nova::input::set(key, true);
		Nova::event::KeyPress(key).fire();
	}

	inline void key_up(const Nova::input::Key key) {
		Nova::input::set(key, false);
		Nova::event::KeyRelease(key).fire();
	}

	inline void mouse_move(const unsigned int x, const unsigned int y) {
		Nova::input::MousePos pos(x, y);
		Nova::input::set(pos);
		Nova::event::MouseMove(pos).fire();
	}
	inline void mouse_down(const Nova::input::Mouse button) {
		Nova::input::set(button, true);
		Nova::event::MouseButtonPress(button).fire();
	}
	inline void mouse_up(const Nova::input::Mouse button) {
		Nova::input::set(button, false);
		Nova::event::MouseButtonRelease(button).fire();
	}
	inline void scroll(const int y) {
		Nova::event::MouseScroll(y).fire();
		Nova::event::KeyPress(y > 0 ? Nova::input::Key::SCROLL_UP : Nova::input::Key::SCROLL_DOWN).fire();
	}
}