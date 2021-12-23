#pragma once
#include "npch.h"
#include "key.h"
#include "mouse.h"
#include "event/mouse.h"

namespace Nova::input {
	NOVAPI bool poll(const Key key);
	NOVAPI bool poll(const Mouse button);
	NOVAPI MousePos poll();

}
