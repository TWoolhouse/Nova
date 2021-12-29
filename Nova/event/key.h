#pragma once
#include "event.h"
#include "input/key.h"

namespace Nova::event {

	class Key : public Handle {
	public:
		static constexpr auto descriptor = Descriptor::Key;
		Key(const input::Key key) : Handle(descriptor), key(key) {}
		Key(const input::Key key, const Descriptor des) : Handle(des), key(key) {}
		const input::Key key;
	};

	class KeyPress : public Key {
	public:
		static constexpr auto descriptor = Descriptor::KeyPress;
		KeyPress(const input::Key key) : Key(key, descriptor) {}
	};

	class KeyRelease : public Key {
	public:
		static constexpr auto descriptor = Descriptor::KeyRelease;
		KeyRelease(const input::Key key) : Key(key, descriptor) {}
	};

}