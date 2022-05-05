#pragma once
#include "meta/head.h"
#include "key.h"
#include "mouse.h"
#include "event/mouse.h"

namespace Nova::input {
	NOVAPI NODISCARD bool poll(const Key key);
	NOVAPI NODISCARD bool poll(const Mouse button);
	NOVAPI NODISCARD MousePos poll();
}
