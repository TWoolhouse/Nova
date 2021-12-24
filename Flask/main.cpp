#include "fpch.h"
#include <core/application.h>
#include <event/event.h>
#include <event/key.h>
#include <event/mouse.h>
#include <event/window.h>
#include <input/poll.h>

class Game : public Nova::Application {
public:
	Game() : Application("Flask") {
		nova_bark_debug("Creating Flask");
	}

	void update() {}
	void render() {}
};

#define NOVA_ENTRY Game
#include <core/entry.h>
