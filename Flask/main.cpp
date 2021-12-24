#include "fpch.h"

class Game : public Nova::Application {
public:
	Game() : Application("Flask") {
		nova_bark_debug("Creating Flask");
	}

	void update() {}
	void render() {}
};

#define NOVA_ENTRY Game
#include <nova_entry.h>
