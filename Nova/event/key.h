#pragma once
#include "event.h"
#include "input/key.h"

namespace Nova::event {

	class Key : public Base {
	public:
		static constexpr auto type = Type::Key;
		Key(const input::Key key) : Base(type), key(key) {}
		Key(const input::Key key, const Type tag) : Base(tag), key(key) {}
		const input::Key key;
	};

	class KeyPress : public Key {
	public:
		static constexpr auto type = Type::KeyPress;
		KeyPress(const input::Key key) : Key(key, type) {}
	};

	class KeyRelease : public Key {
	public:
		static constexpr auto type = Type::KeyRelease;
		KeyRelease(const input::Key key) : Key(key, type) {}
	};

}