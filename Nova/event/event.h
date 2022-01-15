#pragma once
#include "meta/head.h"
#include "eden/eden.h"

namespace Nova::event {

	enum class Type : uint16_t {
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

	struct Handle : eden::Event<Type> {
		Handle(const Descriptor des) : Eden(des) {}
		bool NOVAPI fire();
	};
	extern NOVAPI eden::Dispatcher<Handle, 12> dispatcher;

}

formatter_enum(Nova::event::Type);
