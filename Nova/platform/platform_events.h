#pragma once
#include "event/key.h"
#include "event/mouse.h"
#include "event/window.h"
#include "input/state.h"

namespace Nova::pevent {
	void key_down(const input::Key key) {
		input::set(key, true);
		event::KeyPress(key).fire();
	}

	void key_up(const input::Key key) {
		input::set(key, false);
		event::KeyRelease(key).fire();
	}

	void mouse_move(const unsigned int x, const unsigned int y) {
		input::MousePos pos(x, y);
		input::set(pos);
		event::MouseMove(pos).fire();
	}
	void mouse_down(const input::Mouse button) {
		input::set(button, true);
		event::MouseButtonPress(button).fire();
	}
	void mouse_up(const input::Mouse button) {
		input::set(button, false);
		event::MouseButtonRelease(button).fire();
	}
}