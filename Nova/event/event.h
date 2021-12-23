#pragma once

#include "npch.h"

namespace Nova::Event {
	class Base;
	struct Register;
}
bool operator==(const Nova::Event::Register& a, const Nova::Event::Register& b);

namespace Nova::Event {

	using TypeSize = uint16_t;

	enum class Type : TypeSize {
		None = 0b000000000000,
		KeyboardPress = 0b000000000001,
		KeyboardRelease = 0b000000000010,
		MouseButtonPress = 0b000000000100,
		MouseButtonRelease = 0b000000001000,
		MouseScroll = 0b000000010000,
		MouseMove = 0b000000100000,
		WindowClose = 0b000001000000,
		WindowFocusGain = 0b000010000000,
		WindowFocusLost = 0b000100000000,
		WindowMove = 0b001000000000,
		WindowResizeScreen = 0b010000000000,
		WindowResizeFrame = 0b100000000000,
		MouseButton = MouseButtonPress | MouseButtonRelease,
		Mouse = MouseButton | MouseScroll | MouseMove,
		WindowFocus = WindowFocusGain | WindowFocusLost,
		WindowResize = WindowResizeScreen | WindowResizeFrame,
		Window = WindowFocus | WindowClose | WindowMove | WindowResize,
		Keyboard = KeyboardPress | KeyboardRelease,
	};

	class Base;
	struct Register {
		template<typename F, typename T>
		Register(const Type tag, F func, T& member) : func(std::bind(func, &member, std::placeholders::_1)) {
			enroll(tag);
		}
		template<typename F>
		Register(const Type tag, F func) : func(func) {
			enroll(tag);
		}

		friend bool ::operator==(const Nova::Event::Register& a, const Nova::Event::Register& b);
		inline bool operator()(Base& event) { return func(event); }

	protected:
		std::function<bool(Base&)> func;
		NOVAPI void enroll(const Type tag);
	};

	template<typename T>
	concept Able = std::is_base_of_v<Base, T>;

	class Base {
	public:
		static constexpr auto type = Type::None;
	private:
		friend Register;
		friend bool fire(Base&, const Type);
		// Length of Base::Type Unique Count
		static std::array<std::deque<Register>, 12> callbacks;
		
		template<Able T> friend bool fire(T&);
		template<Able T>
		inline bool fire() { return fire(T::type); }
		NOVAPI bool fire(const Type etype);
	};

	template<Able T>
	inline bool fire(T& event) { return event.fire<T>(); }

}

bool operator==(const Nova::Event::Register& a, const Nova::Event::Register& b) {
	using Func = bool(*)(Nova::Event::Base&);
	return a.func.target<Func>() == a.func.target<Func>();
}