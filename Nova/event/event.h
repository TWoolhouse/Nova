#pragma once
#include "meta/head.h"
#include "eden/eden.h"

namespace Nova::event {

	enum class Type : meta::smallest::uint<meta::bit(12)> {
		None = meta::bit(0),
		KeyPress = meta::bit(1),
		KeyRelease = meta::bit(2),
		MouseButtonPress = meta::bit(3),
		MouseButtonRelease = meta::bit(4),
		MouseScroll = meta::bit(5),
		MouseMove = meta::bit(6),
		WindowClose = meta::bit(7),
		WindowFocusGain = meta::bit(8),
		WindowFocusLost = meta::bit(9),
		WindowMove = meta::bit(10),
		WindowResizeScreen = meta::bit(11),
		WindowResizeFrame = meta::bit(12),
		MouseButton = MouseButtonPress | MouseButtonRelease,
		Mouse = MouseButton | MouseScroll | MouseMove,
		WindowFocus = WindowFocusGain | WindowFocusLost,
		WindowResize = WindowResizeScreen | WindowResizeFrame,
		Window = WindowFocus | WindowClose | WindowMove | WindowResize,
		Key = KeyPress | KeyRelease,
	};

	struct Handle : eden::Event<Type> {
		using Eden::Eden;
		bool fire();
	};
	using Dispatcher = eden::Dispatcher<Handle, 12>;
	extern NOVAPI Dispatcher dispatcher; // TODO: Spire
	using Ticket = Dispatcher::Ticket;
	inline bool Handle::fire() {
		return dispatcher.fire(*this);
	}

}

formatter_enum(Nova::event::Type);
