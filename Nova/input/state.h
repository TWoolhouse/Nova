#pragma once
#include "key.h"
#include "mouse.h"

namespace Nova::Input {

	void set(const Key key, const bool flag);
	void set(const Mouse button, const bool flag);
	void set(const MousePos pos);

}