#pragma once

#include "npch.h"

namespace Nova::event {
	class Base;
	struct Register;
}

namespace Nova::event {

	using TypeSize = uint16_t;

	enum class Type : TypeSize {
		None = 0b000000000000,
		KeyPress = 0b000000000001,
		KeyRelease = 0b000000000010,
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
		Key = KeyPress | KeyRelease,
	};

	class Base;
	struct Register {
		template<typename F, typename T>
		Register(const Type tag, F func, T& member) : uid(++counter), func(std::bind(func, &member, std::placeholders::_1)) {
			enroll(tag);
		}
		template<typename F>
		Register(const Type tag, F func) : uid(++counter), func(func) {
			enroll(tag);
		}

		inline bool operator()(Base& event) { return func(event); }

		auto operator==(const Register& other) const {
			return uid == other.uid;
		}

	protected:
		NOVAPI static size_t counter;
		const size_t uid;
		const std::function<bool(Base&)> func;
		NOVAPI void enroll(const Type tag);
	};

	template<typename T>
	concept Able = std::is_base_of_v<Base, T>;

	class Base {
	public:
		static constexpr auto type = Type::None;
		const Type tag;
		Base(const Type tag) : tag(tag) {}
	private:
		friend Register;
		friend bool fire(Base&);
		// Length of Base::Type Unique Count
		static std::array<std::deque<Register>, 12> callbacks;
		
		NOVAPI bool fire();
	};

	inline bool fire(Base& event) { return event.fire(); }

}

inline constexpr bool operator&(const Nova::event::Type a, const Nova::event::Type b) {
	return static_cast<Nova::event::TypeSize>(a) & static_cast<Nova::event::TypeSize>(b);
}

template<class CharT>
struct std::formatter<Nova::event::Type, CharT> : std::formatter<Nova::event::TypeSize, CharT> {
	template<class FormatContext>
	auto format(Nova::event::Type tag, FormatContext& fc) {
		return std::formatter<Nova::event::TypeSize, CharT>::format(static_cast<Nova::event::TypeSize>(tag), fc);
	}
};
