#pragma once
#include "event/key.h"
#include "event/mouse.h"
#include "event/window.h"
#include "input/state.h"

namespace Nova::plat::event {
	void key_down(const Nova::input::Key key) {
		Nova::input::set(key, true);
		Nova::event::KeyPress(key).fire();
	}

	void key_up(const Nova::input::Key key) {
		Nova::input::set(key, false);
		Nova::event::KeyRelease(key).fire();
	}

	void mouse_move(const unsigned int x, const unsigned int y) {
		Nova::input::MousePos pos(x, y);
		Nova::input::set(pos);
		Nova::event::MouseMove(pos).fire();
	}
	void mouse_down(const Nova::input::Mouse button) {
		Nova::input::set(button, true);
		Nova::event::MouseButtonPress(button).fire();
	}
	void mouse_up(const Nova::input::Mouse button) {
		Nova::input::set(button, false);
		Nova::event::MouseButtonRelease(button).fire();
	}
}