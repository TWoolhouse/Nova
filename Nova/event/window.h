#pragma once
#include "event.h"

namespace Nova::event {

	class WindowClose : public Base {
	public:
		static constexpr auto type = Type::WindowClose;
		WindowClose() : Base(type) {}
	};

	class WindowFocusGain : public Base {
	public:
		static constexpr auto type = Type::WindowFocusGain;
		WindowFocusGain() : Base(type) {}
	};
	class WindowFocusLost : public Base {
	public:
		static constexpr auto type = Type::WindowFocusLost;
		WindowFocusLost() : Base(type) {}
	};

	class WindowMove : public Base {
	public:
		static constexpr auto type = Type::WindowMove;
		WindowMove() : Base(type) {}
	};

}