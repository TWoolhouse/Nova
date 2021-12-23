#include "npch.h"
#include "poll.h"
#include "state.h"

namespace Nova::input {

	static std::bitset<static_cast<size_t>(Key::COUNT)> keys;
	static std::bitset<static_cast<size_t>(Mouse::COUNT)> buttons;
	static MousePos position;

	bool poll(const Key key) {
		return keys[static_cast<size_t>(key)];
	}
	bool poll(const Mouse button) {
		return buttons[static_cast<size_t>(button)];
	}
	MousePos poll() {
		return position;
	}

	void set(const Key key, const bool flag) {
		keys[static_cast<size_t>(key)] = flag;
	}
	void set(const Mouse button, const bool flag) {
		buttons[static_cast<size_t>(button)] = flag;
	}
	void set(const MousePos pos) {
		position = pos;
	}


}