#pragma once
#include "npch.h"
#include "key.h"
#include "mouse.h"
#include "event/mouse.h"

namespace Nova::input {
	NODISCARD NOVAPI bool poll(const Key key);
	NODISCARD NOVAPI bool poll(const Mouse button);
	NODISCARD NOVAPI MousePos poll();

}
